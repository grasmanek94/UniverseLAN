#include "Host.hxx"

#include <string>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
namespace
{
struct CreateLobbyListener final : galaxy::api::ILobbyCreatedListener
{
    bool completed = false;
    bool succeeded = false;
    galaxy::api::GalaxyID lobbyId;

    void OnLobbyCreated(const galaxy::api::GalaxyID& lobbyId, galaxy::api::LobbyCreateResult result) override
    {
        completed = true;
        succeeded = result == galaxy::api::LOBBY_CREATE_RESULT_SUCCESS && lobbyId.IsValid();
        if (succeeded) this->lobbyId = lobbyId;
    }
};

struct ListLobbyListener final : galaxy::api::ILobbyListListener
{
    explicit ListLobbyListener(galaxy::api::IMatchmaking* matchmaking) : matchmaking(matchmaking) {}
    galaxy::api::IMatchmaking* matchmaking;
    bool completed = false;
    bool succeeded = false;
    galaxy::api::GalaxyID lobbyId;

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
    void OnLobbyList(uint32_t lobbyCount, galaxy::api::LobbyListResult result) override
    {
        completed = true;
        if (result != galaxy::api::LOBBY_LIST_RESULT_SUCCESS || lobbyCount == 0) return;
        lobbyId = matchmaking->GetLobbyByIndex(0);
        succeeded = lobbyId.IsValid();
    }
#else
    void OnLobbyList(uint32_t lobbyCount, bool ioFailure) override
    {
        completed = true;
        if (ioFailure || lobbyCount == 0) return;
        lobbyId = matchmaking->GetLobbyByIndex(0);
        succeeded = lobbyId.IsValid();
    }
#endif
};

struct JoinLobbyListener final : galaxy::api::ILobbyEnteredListener
{
    bool completed = false;
    bool succeeded = false;
    void OnLobbyEntered(const galaxy::api::GalaxyID& lobbyId, galaxy::api::LobbyEnterResult result) override
    {
        completed = true;
        succeeded = result == galaxy::api::LOBBY_ENTER_RESULT_SUCCESS && lobbyId.IsValid();
    }
};

struct TaggedLobbyListListener final : galaxy::api::ILobbyListListener
{
    TaggedLobbyListListener(galaxy::api::IMatchmaking* matchmaking, const std::string& token) : matchmaking(matchmaking), token(token) {}
    galaxy::api::IMatchmaking* matchmaking;
    const std::string& token;
    bool completed = false;
    bool succeeded = false;
    galaxy::api::GalaxyID lobbyId;

    void process(uint32_t lobbyCount, bool requestSucceeded)
    {
        completed = true;
        if (!requestSucceeded) return;
        for (uint32_t index = 0; index < lobbyCount; ++index)
        {
            const galaxy::api::GalaxyID candidate = matchmaking->GetLobbyByIndex(index);
            const char* lobbyToken = matchmaking->GetLobbyData(candidate, "universelan.systemtest.lobby");
            if (candidate.IsValid() && lobbyToken != nullptr && token == lobbyToken)
            {
                lobbyId = candidate;
                succeeded = true;
                return;
            }
        }
    }

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
    void OnLobbyList(uint32_t lobbyCount, galaxy::api::LobbyListResult result) override { process(lobbyCount, result == galaxy::api::LOBBY_LIST_RESULT_SUCCESS); }
#else
    void OnLobbyList(uint32_t lobbyCount, bool ioFailure) override { process(lobbyCount, !ioFailure); }
#endif
};

struct LobbyDataUpdateListener final : galaxy::api::ILobbyDataUpdateListener
{
    bool completed = false;
    bool succeeded = false;
    void OnLobbyDataUpdateSuccess(const galaxy::api::GalaxyID&) override { completed = true; succeeded = true; }
    void OnLobbyDataUpdateFailure(const galaxy::api::GalaxyID&, FailureReason) override { completed = true; }
};

constexpr const char lobbyMemberDataKey[] = "universelan.systemtest.member";
constexpr const char lobbyMemberDataValue[] = "joiner-member-value";
constexpr const char lobbyOwnerDataKey[] = "universelan.systemtest.owner";
constexpr const char lobbyOwnerDataValue[] = "owner-lobby-value";

struct LobbyMemberDataUpdateListener final : galaxy::api::ILobbyMemberDataUpdateListener
{
    explicit LobbyMemberDataUpdateListener(const galaxy::api::GalaxyID& lobbyId) : lobbyId(lobbyId) {}
    galaxy::api::GalaxyID lobbyId;
    bool completed = false;
    bool succeeded = false;
    void OnLobbyMemberDataUpdateSuccess(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID&) override
    {
        completed = true;
        succeeded = updatedLobbyId == lobbyId;
    }
    void OnLobbyMemberDataUpdateFailure(const galaxy::api::GalaxyID&, const galaxy::api::GalaxyID&, FailureReason) override { completed = true; }
};

struct LobbyJoinerStateListener final : galaxy::api::GlobalLobbyMemberStateListener
{
    LobbyJoinerStateListener(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId, std::uint64_t ownerUserId, std::uint64_t joinerUserId)
        : matchmaking(matchmaking), lobbyId(lobbyId), ownerUserId(ownerUserId), joinerUserId(joinerUserId) {}
    galaxy::api::IMatchmaking* matchmaking;
    galaxy::api::GalaxyID lobbyId;
    std::uint64_t ownerUserId;
    std::uint64_t joinerUserId;
    bool confirmed = false;
    void OnLobbyMemberStateChanged(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID& memberId, galaxy::api::LobbyMemberStateChange change) override
    {
        if (updatedLobbyId != lobbyId || memberId.GetRealID() != joinerUserId || change != galaxy::api::LOBBY_MEMBER_STATE_CHANGED_ENTERED || matchmaking->GetNumLobbyMembers(lobbyId) != 2) return;
        bool sawOwner = false;
        bool sawJoiner = false;
        for (std::uint32_t index = 0; index < 2; ++index)
        {
            const std::uint64_t userId = matchmaking->GetLobbyMemberByIndex(lobbyId, index).GetRealID();
            sawOwner = sawOwner || userId == ownerUserId;
            sawJoiner = sawJoiner || userId == joinerUserId;
        }
        confirmed = sawOwner && sawJoiner;
    }
};

struct LobbyLeaveOwnerStateListener final : galaxy::api::GlobalLobbyMemberStateListener
{
    LobbyLeaveOwnerStateListener(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId, std::uint64_t ownerUserId, std::uint64_t joinerUserId)
        : matchmaking(matchmaking), lobbyId(lobbyId), ownerUserId(ownerUserId), joinerUserId(joinerUserId) {}
    galaxy::api::IMatchmaking* matchmaking;
    galaxy::api::GalaxyID lobbyId;
    std::uint64_t ownerUserId;
    std::uint64_t joinerUserId;
    bool entered = false;
    bool left = false;
    void OnLobbyMemberStateChanged(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID& memberId, galaxy::api::LobbyMemberStateChange change) override
    {
        if (updatedLobbyId != lobbyId || memberId.GetRealID() != joinerUserId) return;
        if (change == galaxy::api::LOBBY_MEMBER_STATE_CHANGED_ENTERED)
        {
            bool sawOwner = false;
            bool sawJoiner = false;
            if (matchmaking->GetNumLobbyMembers(lobbyId) != 2) return;
            for (std::uint32_t index = 0; index < 2; ++index)
            {
                const std::uint64_t userId = matchmaking->GetLobbyMemberByIndex(lobbyId, index).GetRealID();
                sawOwner = sawOwner || userId == ownerUserId;
                sawJoiner = sawJoiner || userId == joinerUserId;
            }
            entered = sawOwner && sawJoiner;
        }
        else if (change == galaxy::api::LOBBY_MEMBER_STATE_CHANGED_LEFT)
        {
            left = matchmaking->GetNumLobbyMembers(lobbyId) == 1 && matchmaking->GetLobbyMemberByIndex(lobbyId, 0).GetRealID() == ownerUserId;
        }
    }
};

struct LobbyLeftListener final : galaxy::api::ILobbyLeftListener
{
    explicit LobbyLeftListener(const galaxy::api::GalaxyID& lobbyId) : lobbyId(lobbyId) {}
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

struct OwnershipTransferOwnerChangeListener final : galaxy::api::GlobalLobbyOwnerChangeListener
{
    OwnershipTransferOwnerChangeListener(const galaxy::api::GalaxyID& lobbyId, const std::uint64_t joinerUserId)
        : lobbyId(lobbyId), joinerUserId(joinerUserId) {}
    galaxy::api::GalaxyID lobbyId;
    std::uint64_t joinerUserId;
    bool changed = false;
    void OnLobbyOwnerChanged(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID& newOwnerId) override
    {
        changed = updatedLobbyId == lobbyId && newOwnerId.GetRealID() == joinerUserId;
    }
};

struct OwnershipTransferMemberStateListener final : galaxy::api::GlobalLobbyMemberStateListener
{
    OwnershipTransferMemberStateListener(const galaxy::api::GalaxyID& lobbyId, const std::uint64_t ownerUserId)
        : lobbyId(lobbyId), ownerUserId(ownerUserId) {}
    galaxy::api::GalaxyID lobbyId;
    std::uint64_t ownerUserId;
    bool ownerLeft = false;
    void OnLobbyMemberStateChanged(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID& memberId,
        galaxy::api::LobbyMemberStateChange change) override
    {
        ownerLeft = updatedLobbyId == lobbyId && memberId.GetRealID() == ownerUserId
            && change == galaxy::api::LOBBY_MEMBER_STATE_CHANGED_LEFT;
    }
};

struct LobbyClosedListener final : galaxy::api::GlobalLobbyLeftListener
{
    explicit LobbyClosedListener(const galaxy::api::GalaxyID& lobbyId) : lobbyId(lobbyId) {}
    galaxy::api::GalaxyID lobbyId;
    bool closed = false;
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
    void OnLobbyLeft(const galaxy::api::GalaxyID& receivedLobbyId, galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason) override
    {
        closed = receivedLobbyId == lobbyId && reason == galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_LOBBY_CLOSED;
    }
#else
    void OnLobbyLeft(const galaxy::api::GalaxyID& receivedLobbyId, bool ioFailure) override
    {
        // Legacy SDKs do not expose a close reason; the gated owner leave is the only leave source.
        closed = receivedLobbyId == lobbyId && !ioFailure;
    }
#endif
};

bool lobbyHasMembers(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId,
    const std::uint64_t firstUserId, const std::uint64_t secondUserId)
{
    if (matchmaking->GetNumLobbyMembers(lobbyId) != 2) return false;
    const std::uint64_t firstMemberId = matchmaking->GetLobbyMemberByIndex(lobbyId, 0).GetRealID();
    const std::uint64_t secondMemberId = matchmaking->GetLobbyMemberByIndex(lobbyId, 1).GetRealID();
    return (firstMemberId == firstUserId && secondMemberId == secondUserId)
        || (firstMemberId == secondUserId && secondMemberId == firstUserId);
}

bool lobbyHasOnlyMember(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId, const std::uint64_t userId)
{
    return matchmaking->GetNumLobbyMembers(lobbyId) == 1
        && matchmaking->GetLobbyMemberByIndex(lobbyId, 0).GetRealID() == userId;
}

struct RemoteMemberDataListener final : galaxy::api::GlobalLobbyDataListener
{
    RemoteMemberDataListener(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId, std::uint64_t memberUserId)
        : matchmaking(matchmaking), lobbyId(lobbyId), memberUserId(memberUserId) {}
    galaxy::api::IMatchmaking* matchmaking;
    galaxy::api::GalaxyID lobbyId;
    std::uint64_t memberUserId;
    bool received = false;
    void OnLobbyDataUpdated(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID& memberId) override
    {
        if (updatedLobbyId != lobbyId || memberId.GetRealID() != memberUserId) return;
        const char* value = matchmaking->GetLobbyMemberData(lobbyId, memberId, lobbyMemberDataKey);
        received = value != nullptr && std::string(value) == lobbyMemberDataValue;
    }
};

struct RemoteLobbyDataListener final : galaxy::api::GlobalLobbyDataListener
{
    RemoteLobbyDataListener(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId) : matchmaking(matchmaking), lobbyId(lobbyId) {}
    galaxy::api::IMatchmaking* matchmaking;
    galaxy::api::GalaxyID lobbyId;
    bool received = false;
    void OnLobbyDataUpdated(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID& memberId) override
    {
        if (updatedLobbyId != lobbyId || memberId.IsValid()) return;
        const char* value = matchmaking->GetLobbyData(lobbyId, lobbyOwnerDataKey);
        received = value != nullptr && std::string(value) == lobbyOwnerDataValue;
    }
};
}

bool createLobby(Api& api, const Arguments& arguments)
{
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    CreateLobbyListener listener;
    matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 4, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM, &listener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.completed; }) || !listener.succeeded) return false;
    if (!emit(arguments, "lobby-ready")) return false;
    if (arguments.finishAfter.empty()) return true;
    return pumpUntil(api, arguments.timeoutSeconds, [&arguments] { return std::filesystem::exists(arguments.controlDirectory / (arguments.role + ".complete")); });
}

bool listAndJoinLobby(Api& api, const Arguments& arguments)
{
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    ListLobbyListener listListener(matchmaking);
    matchmaking->RequestLobbyList(false, &listListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&listListener] { return listListener.completed; }) || !listListener.succeeded) return false;
    JoinLobbyListener joinListener;
    matchmaking->JoinLobby(listListener.lobbyId, &joinListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&joinListener] { return joinListener.completed; }) || !joinListener.succeeded) return false;
    return emit(arguments, "lobby-joined");
}

bool createTaggedLobby(Api& api, const Arguments& arguments, galaxy::api::GalaxyID* createdLobbyId)
{
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr || arguments.lobbyToken.empty()) return false;
    CreateLobbyListener createListener;
    matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 4, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM, &createListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&createListener] { return createListener.completed; }) || !createListener.succeeded) return false;
    LobbyDataUpdateListener dataListener;
    matchmaking->SetLobbyData(createListener.lobbyId, "universelan.systemtest.lobby", arguments.lobbyToken.c_str(), &dataListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&dataListener] { return dataListener.completed; }) || !dataListener.succeeded) return false;
    const char* savedToken = matchmaking->GetLobbyData(createListener.lobbyId, "universelan.systemtest.lobby");
    if (savedToken == nullptr || arguments.lobbyToken != savedToken) return false;
    if (createdLobbyId != nullptr) *createdLobbyId = createListener.lobbyId;
    return emit(arguments, "lobby-tagged");
}

bool joinTaggedLobby(Api& api, const Arguments& arguments, galaxy::api::GalaxyID* joinedLobbyId, const bool emitJoined)
{
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr || arguments.lobbyToken.empty()) return false;
    TaggedLobbyListListener listListener(matchmaking, arguments.lobbyToken);
    matchmaking->AddRequestLobbyListStringFilter("universelan.systemtest.lobby", arguments.lobbyToken.c_str(), galaxy::api::LOBBY_COMPARISON_TYPE_EQUAL);
    matchmaking->RequestLobbyList(false, &listListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&listListener] { return listListener.completed; }) || !listListener.succeeded) return false;
    JoinLobbyListener joinListener;
    matchmaking->JoinLobby(listListener.lobbyId, &joinListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&joinListener] { return joinListener.completed; }) || !joinListener.succeeded) return false;
    const char* savedToken = matchmaking->GetLobbyData(listListener.lobbyId, "universelan.systemtest.lobby");
    if (savedToken == nullptr || arguments.lobbyToken != savedToken) return false;
    if (joinedLobbyId != nullptr) *joinedLobbyId = listListener.lobbyId;
    return !emitJoined || emit(arguments, arguments.role + "-joined");
}

bool lobbyDataMemberOwner(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1 || arguments.lobbyToken.empty()) return false;
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    CreateLobbyListener createListener;
    matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 4, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM, &createListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&createListener] { return createListener.completed; }) || !createListener.succeeded) return false;
    LobbyJoinerStateListener memberStateListener(matchmaking, createListener.lobbyId, api.user->GetGalaxyID().GetRealID(), arguments.peerUserIds.front());
    RemoteMemberDataListener memberDataListener(matchmaking, createListener.lobbyId, arguments.peerUserIds.front());
    LobbyDataUpdateListener tagListener;
    matchmaking->SetLobbyData(createListener.lobbyId, "universelan.systemtest.lobby", arguments.lobbyToken.c_str(), &tagListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&tagListener] { return tagListener.completed; }) || !tagListener.succeeded || !emit(arguments, "lobby-tagged")) return false;
    if (!pumpUntil(api, arguments.timeoutSeconds, [&memberStateListener] { return memberStateListener.confirmed; }) || !emit(arguments, "owner-observed-joiner")) return false;
    if (!pumpUntil(api, arguments.timeoutSeconds, [&memberDataListener] { return memberDataListener.received; })) return false;
    LobbyDataUpdateListener ownerDataListener;
    matchmaking->SetLobbyData(createListener.lobbyId, lobbyOwnerDataKey, lobbyOwnerDataValue, &ownerDataListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&ownerDataListener] { return ownerDataListener.completed; }) || !ownerDataListener.succeeded) return false;
    return emit(arguments, "owner-lobby-data-written") && waitForCompletion(arguments);
}

bool lobbyDataMemberJoiner(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::GalaxyID lobbyId;
    if (!joinTaggedLobby(api, arguments, &lobbyId) || !waitForAction(arguments)) return false;
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    RemoteLobbyDataListener lobbyDataListener(matchmaking, lobbyId);
    LobbyMemberDataUpdateListener memberDataListener(lobbyId);
    matchmaking->SetLobbyMemberData(lobbyId, lobbyMemberDataKey, lobbyMemberDataValue, &memberDataListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&memberDataListener] { return memberDataListener.completed; }) || !memberDataListener.succeeded || !emit(arguments, "joiner-member-data-written")) return false;
    return pumpUntil(api, arguments.timeoutSeconds, [&lobbyDataListener] { return lobbyDataListener.received; }) && emit(arguments, "joiner-verified-owner-data");
}

bool lobbyMemberLeaveOwner(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1 || arguments.lobbyToken.empty()) return false;
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    CreateLobbyListener createListener;
    matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 4, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM, &createListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&createListener] { return createListener.completed; }) || !createListener.succeeded) return false;
    LobbyLeaveOwnerStateListener memberStateListener(matchmaking, createListener.lobbyId, api.user->GetGalaxyID().GetRealID(), arguments.peerUserIds.front());
    LobbyDataUpdateListener tagListener;
    matchmaking->SetLobbyData(createListener.lobbyId, "universelan.systemtest.lobby", arguments.lobbyToken.c_str(), &tagListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&tagListener] { return tagListener.completed; }) || !tagListener.succeeded || !emit(arguments, "lobby-tagged")) return false;
    if (!pumpUntil(api, arguments.timeoutSeconds, [&memberStateListener] { return memberStateListener.entered; }) || !emit(arguments, "owner-observed-joiner")) return false;
    if (!pumpUntil(api, arguments.timeoutSeconds, [&memberStateListener] { return memberStateListener.left; }) || !emit(arguments, "owner-observed-left")) return false;
    return waitForCompletion(arguments);
}

bool lobbyMemberLeaveJoiner(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::GalaxyID lobbyId;
    if (!joinTaggedLobby(api, arguments, &lobbyId, false)) return false;
    LobbyLeftListener leaveListener(lobbyId);
    if (!emit(arguments, "joiner-joined") || !waitForAction(arguments)) return false;
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    matchmaking->LeaveLobby(lobbyId, &leaveListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&leaveListener] { return leaveListener.completed; }) || !leaveListener.succeeded) return false;
    const char* token = matchmaking->GetLobbyData(lobbyId, "universelan.systemtest.lobby");
    return token != nullptr && token[0] == '\0' && emit(arguments, "joiner-left") && waitForCompletion(arguments);
}
#endif

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS && GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
bool lobbyOwnerOwnershipTransferOwner(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1 || arguments.lobbyToken.empty()) return false;
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    CreateLobbyListener createListener;
    matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 4, true,
        galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION, &createListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&createListener] { return createListener.completed; }) || !createListener.succeeded) return false;
    LobbyDataUpdateListener tagListener;
    matchmaking->SetLobbyData(createListener.lobbyId, "universelan.systemtest.lobby", arguments.lobbyToken.c_str(), &tagListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&tagListener] { return tagListener.completed; }) || !tagListener.succeeded
        || !emit(arguments, "lobby-tagged") || !waitForAction(arguments)) return false;
    LobbyLeftListener leaveListener(createListener.lobbyId);
    matchmaking->LeaveLobby(createListener.lobbyId, &leaveListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&leaveListener] { return leaveListener.completed; }) || !leaveListener.succeeded) return false;
    return emit(arguments, "owner-left") && waitForCompletion(arguments);
}

bool lobbyOwnerOwnershipTransferJoiner(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::GalaxyID lobbyId;
    if (!joinTaggedLobby(api, arguments, &lobbyId, false)) return false;
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    const std::uint64_t ownerUserId = arguments.peerUserIds.front();
    const std::uint64_t joinerUserId = api.user->GetGalaxyID().GetRealID();
    OwnershipTransferOwnerChangeListener ownerChangeListener(lobbyId, joinerUserId);
    OwnershipTransferMemberStateListener memberStateListener(lobbyId, ownerUserId);
    if (matchmaking->GetLobbyOwner(lobbyId).GetRealID() != ownerUserId
        || !lobbyHasMembers(matchmaking, lobbyId, ownerUserId, joinerUserId) || !emit(arguments, "joiner-ready")) return false;
    if (!pumpUntil(api, arguments.timeoutSeconds, [&]
    {
        return ownerChangeListener.changed && memberStateListener.ownerLeft
            && matchmaking->GetLobbyOwner(lobbyId).GetRealID() == joinerUserId
            && lobbyHasOnlyMember(matchmaking, lobbyId, joinerUserId);
    })) return false;
    LobbyDataUpdateListener promotedOwnerDataListener;
    matchmaking->SetLobbyData(lobbyId, "universelan.systemtest.promoted-owner", "authorized", &promotedOwnerDataListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&promotedOwnerDataListener] { return promotedOwnerDataListener.completed; })
        || !promotedOwnerDataListener.succeeded) return false;
    const char* value = matchmaking->GetLobbyData(lobbyId, "universelan.systemtest.promoted-owner");
    return value != nullptr && std::string(value) == "authorized" && emit(arguments, "joiner-promoted-owner-data-written");
}

bool lobbyOwnerCloseLifecycleOwner(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1 || arguments.lobbyToken.empty()) return false;
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    CreateLobbyListener createListener;
    matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 4, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM, &createListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&createListener] { return createListener.completed; }) || !createListener.succeeded) return false;
    LobbyDataUpdateListener tagListener;
    matchmaking->SetLobbyData(createListener.lobbyId, "universelan.systemtest.lobby", arguments.lobbyToken.c_str(), &tagListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&tagListener] { return tagListener.completed; }) || !tagListener.succeeded
        || !emit(arguments, "lobby-tagged") || !waitForAction(arguments)) return false;
    LobbyLeftListener leaveListener(createListener.lobbyId);
    matchmaking->LeaveLobby(createListener.lobbyId, &leaveListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&leaveListener] { return leaveListener.completed; }) || !leaveListener.succeeded) return false;
    return emit(arguments, "owner-left") && waitForCompletion(arguments);
}

bool lobbyOwnerCloseLifecycleJoiner(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::GalaxyID lobbyId;
    if (!joinTaggedLobby(api, arguments, &lobbyId, false)) return false;
    galaxy::api::IMatchmaking* matchmaking = api.matchmaking();
    if (matchmaking == nullptr) return false;
    LobbyClosedListener closeListener(lobbyId);
    const std::uint64_t ownerUserId = arguments.peerUserIds.front();
    const std::uint64_t joinerUserId = api.user->GetGalaxyID().GetRealID();
    if (matchmaking->GetLobbyOwner(lobbyId).GetRealID() != ownerUserId
        || !lobbyHasMembers(matchmaking, lobbyId, ownerUserId, joinerUserId) || !emit(arguments, "joiner-ready")) return false;
    if (!pumpUntil(api, arguments.timeoutSeconds, [&] { return closeListener.closed; })) return false;
    const char* token = matchmaking->GetLobbyData(lobbyId, "universelan.systemtest.lobby");
    const char probe = 0;
    return token != nullptr && token[0] == '\0'
        && matchmaking->GetLobbyByIndex(0) != lobbyId
        && !matchmaking->SendLobbyMessage(lobbyId, &probe, 1)
        && matchmaking->GetNumLobbyMembers(lobbyId) == 0
        && !matchmaking->GetLobbyMemberByIndex(lobbyId, 0).IsValid()
        && !matchmaking->GetLobbyOwner(lobbyId).IsValid()
        && emit(arguments, "joiner-observed-close");
}
#endif
}
