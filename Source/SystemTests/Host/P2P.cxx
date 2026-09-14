#include "Host.hxx"

#include <algorithm>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
bool rawP2POfflineRecipient(Api& api, const Arguments& arguments)
{
    galaxy::api::INetworking* networking = api.networking();
    if (networking == nullptr) return false;
    const galaxy::api::GalaxyID undeployedUser = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, 2299);
    return networking->GetConnectionType(undeployedUser) == galaxy::api::CONNECTION_TYPE_NONE
        && networking->GetPingWith(undeployedUser) == -1
        && emit(arguments, "offline-recipient-verified");
}
#endif

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
namespace
{
constexpr std::uint8_t rawP2PChannel = 37;
constexpr std::uint8_t rawP2PBoundaryChannel = 255;
constexpr std::uint8_t rawP2PLeaveChannel = 38;

std::vector<std::uint8_t> p2pPayload(const char* name)
{
    std::vector<std::uint8_t> payload(name, name + std::char_traits<char>::length(name));
    payload.push_back(0);
    payload.push_back(0xA5);
    return payload;
}

std::vector<std::uint8_t> p2pBoundaryPayload()
{
    std::vector<std::uint8_t> payload(1200);
    for (std::size_t index = 0; index < payload.size(); ++index)
        payload[index] = static_cast<std::uint8_t>((index * 37) % 251);
    return payload;
}

bool sendPacket(Api& api, const std::uint64_t peerUserId, const std::vector<std::uint8_t>& payload, const std::uint8_t channel = rawP2PChannel)
{
    galaxy::api::INetworking* networking = api.networking();
    if (networking == nullptr) return false;
    const galaxy::api::GalaxyID peer = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, peerUserId);
    return networking->SendP2PPacket(peer, payload.data(), static_cast<uint32_t>(payload.size()), galaxy::api::P2P_SEND_RELIABLE, channel);
}

bool receivePacket(Api& api, const int timeoutSeconds, const std::uint64_t peerUserId, const std::vector<std::uint8_t>& expected,
    const std::uint8_t channel = rawP2PChannel)
{
    galaxy::api::INetworking* networking = api.networking();
    if (networking == nullptr) return false;
    const galaxy::api::GalaxyID expectedSender = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, peerUserId);
    return pumpUntil(api, timeoutSeconds, [&]
    {
        uint32_t available = 0;
        if (!networking->IsP2PPacketAvailable(&available, channel) || available == 0) return false;
        std::vector<std::uint8_t> received(available);
        uint32_t receivedSize = 0;
        galaxy::api::GalaxyID sender;
        if (!networking->ReadP2PPacket(received.data(), static_cast<uint32_t>(received.size()), &receivedSize, sender, channel)) return false;
        return sender == expectedSender && receivedSize == expected.size() && std::equal(expected.begin(), expected.end(), received.begin());
    });
}

bool observeP2PQuiet(Api& api, const int timeoutSeconds, const std::uint8_t channel = rawP2PChannel)
{
    galaxy::api::INetworking* networking = api.networking();
    if (networking == nullptr) return false;
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(std::min(timeoutSeconds * 1000, 750));
    while (std::chrono::steady_clock::now() < deadline)
    {
        api.processData();
        uint32_t available = 0;
        while (networking->IsP2PPacketAvailable(&available, channel))
        {
            std::vector<std::uint8_t> ignored(available);
            uint32_t receivedSize = 0;
            galaxy::api::GalaxyID sender;
            if (!networking->ReadP2PPacket(ignored.data(), static_cast<uint32_t>(ignored.size()), &receivedSize, sender, channel)) return false;
            return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return true;
}

struct P2PLeaveMemberStateListener final : galaxy::api::GlobalLobbyMemberStateListener
{
    P2PLeaveMemberStateListener(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId,
        const std::uint64_t senderUserId, const std::uint64_t receiverUserId)
        : matchmaking(matchmaking), lobbyId(lobbyId), senderUserId(senderUserId), receiverUserId(receiverUserId) {}
    galaxy::api::IMatchmaking* matchmaking;
    galaxy::api::GalaxyID lobbyId;
    std::uint64_t senderUserId;
    std::uint64_t receiverUserId;
    bool receiverJoined = false;
    bool receiverLeft = false;

    void OnLobbyMemberStateChanged(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID& memberId,
        galaxy::api::LobbyMemberStateChange change) override
    {
        if (updatedLobbyId != lobbyId || memberId.GetRealID() != receiverUserId) return;
        if (change == galaxy::api::LOBBY_MEMBER_STATE_CHANGED_ENTERED)
            receiverJoined = matchmaking->GetNumLobbyMembers(lobbyId) == 2;
        else if (change == galaxy::api::LOBBY_MEMBER_STATE_CHANGED_LEFT)
            receiverLeft = matchmaking->GetNumLobbyMembers(lobbyId) == 1
                && matchmaking->GetLobbyMemberByIndex(lobbyId, 0).GetRealID() == senderUserId;
    }
};

struct P2PLeaveListener final : galaxy::api::ILobbyLeftListener
{
    explicit P2PLeaveListener(const galaxy::api::GalaxyID& lobbyId) : lobbyId(lobbyId) {}
    galaxy::api::GalaxyID lobbyId;
    bool completed = false;
    bool succeeded = false;

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
    void OnLobbyLeft(const galaxy::api::GalaxyID& receivedLobbyId, galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason) override
    {
        completed = true;
        succeeded = receivedLobbyId == lobbyId && reason == galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_USER_LEFT;
    }
#else
    void OnLobbyLeft(const galaxy::api::GalaxyID& receivedLobbyId, bool ioFailure) override
    {
        completed = true;
        succeeded = receivedLobbyId == lobbyId && !ioFailure;
    }
#endif
};
}

bool runRawP2PScenario(Api& api, const Arguments& arguments)
{
    const bool creator = arguments.scenario == "raw-p2p-two-creator" || arguments.scenario == "raw-p2p-three-sender"
        || arguments.scenario == "raw-p2p-channel-boundary-creator" || arguments.scenario == "raw-p2p-leave-sender";
    galaxy::api::GalaxyID lobbyId;
    if ((creator ? !createTaggedLobby(api, arguments, &lobbyId) : !joinTaggedLobby(api, arguments, &lobbyId))
        || (arguments.scenario != "raw-p2p-leave-sender" && !waitForAction(arguments))) return false;
    if (arguments.scenario == "raw-p2p-two-creator" || arguments.scenario == "raw-p2p-two-joiner")
    {
        if (arguments.peerUserIds.size() != 1) return false;
        const bool isCreator = arguments.scenario == "raw-p2p-two-creator";
        if (!sendPacket(api, arguments.peerUserIds.front(), p2pPayload(isCreator ? "raw-two-creator" : "raw-two-joiner"))
            || !receivePacket(api, arguments.timeoutSeconds, arguments.peerUserIds.front(), p2pPayload(isCreator ? "raw-two-joiner" : "raw-two-creator"))) return false;
        return emit(arguments, arguments.role + "-exchanged") && waitForCompletion(arguments);
    }
    if (arguments.scenario == "raw-p2p-channel-boundary-creator" || arguments.scenario == "raw-p2p-channel-boundary-joiner")
    {
        if (arguments.peerUserIds.size() != 1) return false;
        const std::vector<std::uint8_t> payload = p2pBoundaryPayload();
        if (arguments.scenario == "raw-p2p-channel-boundary-creator")
            return sendPacket(api, arguments.peerUserIds.front(), payload, rawP2PBoundaryChannel)
                && emit(arguments, "channel-boundary-send-scheduled") && waitForCompletion(arguments);
        return receivePacket(api, arguments.timeoutSeconds, arguments.peerUserIds.front(), payload, rawP2PBoundaryChannel)
            && emit(arguments, "channel-boundary-received");
    }
    if (arguments.scenario == "raw-p2p-three-sender")
    {
        if (arguments.peerUserIds.size() != 1 || !sendPacket(api, arguments.peerUserIds.front(), p2pPayload("raw-three-target"))) return false;
        if (!emit(arguments, "sender-sent")) return false;
        return receivePacket(api, arguments.timeoutSeconds, arguments.peerUserIds.front(), p2pPayload("raw-three-ack")) && emit(arguments, "sender-acked") && waitForCompletion(arguments);
    }
    if (arguments.scenario == "raw-p2p-three-target")
    {
        if (arguments.peerUserIds.size() != 1 || !receivePacket(api, arguments.timeoutSeconds, arguments.peerUserIds.front(), p2pPayload("raw-three-target"))) return false;
        return sendPacket(api, arguments.peerUserIds.front(), p2pPayload("raw-three-ack")) && emit(arguments, "target-acked") && waitForCompletion(arguments);
    }
    if (arguments.scenario == "raw-p2p-leave-sender")
    {
        if (arguments.peerUserIds.size() != 1 || api.networking() == nullptr) return false;
        galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
        if (matchmaking == nullptr) return false;
        P2PLeaveMemberStateListener memberStateListener(matchmaking, lobbyId,
            api.user->GetGalaxyID().GetRealID(), arguments.peerUserIds.front());
        if (!pumpUntil(api, arguments.timeoutSeconds, [&memberStateListener] { return memberStateListener.receiverJoined; })
            || !emit(arguments, "sender-observed-receiver")
            || !pumpUntil(api, arguments.timeoutSeconds, [&memberStateListener] { return memberStateListener.receiverLeft; })
            || !emit(arguments, "sender-observed-left") || !waitForAction(arguments)) return false;
        (void)sendPacket(api, arguments.peerUserIds.front(), p2pPayload("raw-leave-revokes-routing"), rawP2PLeaveChannel);
        return emit(arguments, "sender-send-scheduled") && waitForCompletion(arguments) && api.user->SignedIn();
    }
    if (arguments.scenario == "raw-p2p-leave-receiver")
    {
        if (arguments.peerUserIds.size() != 1) return false;
        galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
        if (matchmaking == nullptr) return false;
        P2PLeaveListener leaveListener(lobbyId);
        matchmaking->LeaveLobby(lobbyId, &leaveListener);
        if (!pumpUntil(api, arguments.timeoutSeconds, [&leaveListener] { return leaveListener.completed; }) || !leaveListener.succeeded) return false;
        const char* token = matchmaking->GetLobbyData(lobbyId, "universelan.systemtest.lobby");
        if (token == nullptr || token[0] != '\0' || !emit(arguments, "receiver-left") || !waitForCompletion(arguments)) return false;
        return observeP2PQuiet(api, arguments.timeoutSeconds, rawP2PLeaveChannel) && api.user->SignedIn() && emit(arguments, "receiver-quiet");
    }
    return arguments.scenario == "raw-p2p-three-observer" && observeP2PQuiet(api, arguments.timeoutSeconds) && emit(arguments, "observer-quiet");
}
#endif
}
