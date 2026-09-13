#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#ifdef GALAXY_EXPORT
#undef GALAXY_EXPORT
#endif

#include <GalaxyApi.h>

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
#include <ixwebsocket/IXNetSystem.h>
#endif

namespace
{
struct Arguments
{
    std::string role;
    std::string scenario;
    std::filesystem::path controlDirectory;
    std::string version;
    std::string architecture;
    std::string runtimeProvider;
    std::string credentialProfile;
    std::string lobbyToken;
    std::string webSocketUrl;
    std::vector<std::string> signals;
    std::vector<std::uint64_t> peerUserIds;
    std::vector<std::string> finishAfter;
    int timeoutSeconds = 0;
};

bool token(const std::string& value)
{
    if (value.empty()) return false;
    return std::all_of(value.begin(), value.end(), [](const unsigned char character)
    {
        return std::isalnum(character) || character == '-' || character == '_' || character == '.';
    });
}

bool appendToken(std::vector<std::string>& values, const std::string& value)
{
    if (!token(value) || std::find(values.begin(), values.end(), value) != values.end()) return false;
    values.push_back(value);
    return true;
}

bool galaxyRealId(const std::string& value, std::uint64_t& result)
{
    if (value.empty() || !std::all_of(value.begin(), value.end(), [](const unsigned char character) { return std::isdigit(character); })) return false;
    try { result = std::stoull(value); }
    catch (...) { return false; }
    return result > 0 && result <= 0x00FFFFFFFFFFFFFFULL;
}

bool webSocketUrl(const std::string& value)
{
    constexpr const char prefix[] = "ws://127.0.0.1:";
    constexpr const char suffix[] = "/echo";
    constexpr std::size_t prefixLength = sizeof(prefix) - 1;
    constexpr std::size_t suffixLength = sizeof(suffix) - 1;
    if (value.rfind(prefix, 0) != 0 || value.size() <= prefixLength + suffixLength
        || value.compare(value.size() - suffixLength, suffixLength, suffix) != 0) return false;
    const std::string port = value.substr(prefixLength, value.size() - prefixLength - suffixLength);
    std::uint64_t portNumber = 0;
    return galaxyRealId(port, portNumber) && portNumber <= 65535;
}

bool readArguments(int argc, char* argv[], Arguments& arguments)
{
    for (int index = 1; index < argc; ++index)
    {
        const std::string option = argv[index];
        if (++index == argc) return false;
        const std::string value = argv[index];
        if (option == "--role") arguments.role = value;
        else if (option == "--scenario") arguments.scenario = value;
        else if (option == "--control-dir") arguments.controlDirectory = std::filesystem::u8path(value);
        else if (option == "--version") arguments.version = value;
        else if (option == "--arch") arguments.architecture = value;
        else if (option == "--runtime-provider") arguments.runtimeProvider = value;
        else if (option == "--credential-profile") arguments.credentialProfile = value;
        else if (option == "--lobby-token") arguments.lobbyToken = value;
        else if (option == "--websocket-url") arguments.webSocketUrl = value;
        else if (option == "--peer-user-id")
        {
            std::uint64_t peerUserId = 0;
            if (!galaxyRealId(value, peerUserId) || std::find(arguments.peerUserIds.begin(), arguments.peerUserIds.end(), peerUserId) != arguments.peerUserIds.end()) return false;
            arguments.peerUserIds.push_back(peerUserId);
        }
        else if (option == "--signal")
        {
            if (!appendToken(arguments.signals, value)) return false;
        }
        else if (option == "--finish-after")
        {
            if (!appendToken(arguments.finishAfter, value)) return false;
        }
        else if (option == "--timeout-seconds")
        {
            try { arguments.timeoutSeconds = std::stoi(value); }
            catch (...) { return false; }
        }
        else return false;
    }
    return token(arguments.role) && token(arguments.scenario) && !arguments.controlDirectory.empty()
        && token(arguments.version) && (arguments.architecture == "x86" || arguments.architecture == "x64")
        && (arguments.runtimeProvider == "universelan" || arguments.runtimeProvider == "gog")
        && (arguments.credentialProfile.empty() || arguments.credentialProfile == "user1" || arguments.credentialProfile == "user2")
        && (arguments.lobbyToken.empty() || token(arguments.lobbyToken))
        && (arguments.webSocketUrl.empty() || webSocketUrl(arguments.webSocketUrl))
        && arguments.timeoutSeconds > 0;
}

bool waitForFile(const std::filesystem::path& path, int timeoutSeconds)
{
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds);
    while (std::chrono::steady_clock::now() < deadline)
    {
        if (std::filesystem::exists(path)) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    return std::filesystem::exists(path);
}

bool emit(const Arguments& arguments, const char* event)
{
    if (std::find(arguments.signals.begin(), arguments.signals.end(), event) == arguments.signals.end()) return false;
    std::cout << "SYSTEM_TEST EVENT name=" << event << std::endl;
    return true;
}

bool emit(const Arguments& arguments, const std::string& event)
{
    return emit(arguments, event.c_str());
}

struct Api
{
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
    galaxy::api::IGalaxy* galaxy = nullptr;
#endif
    galaxy::api::IUser* user = nullptr;

    void processData() const
    {
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
        galaxy->ProcessData();
#else
        galaxy::api::ProcessData();
#endif
    }

    galaxy::api::IMatchmaking* matchmaking() const
    {
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
        return galaxy->GetMatchmaking();
#else
        return galaxy::api::Matchmaking();
#endif
    }

    galaxy::api::INetworking* networking() const
    {
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
        return galaxy->GetNetworking();
#else
        return galaxy::api::Networking();
#endif
    }

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
    galaxy::api::IChat* chat() const
    {
        return galaxy::api::Chat();
    }
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
    galaxy::api::ICustomNetworking* customNetworking() const
    {
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
        return galaxy->GetCustomNetworking();
#else
        return galaxy::api::CustomNetworking();
#endif
    }
#endif
};

enum class SignInResult
{
    Succeeded,
    Failed,
    CredentialProfileRequired,
    CredentialProfileUnavailable,
};

bool credentialProfile(const std::string& profile, const char*& login, const char*& password,
    const char*& clientId, const char*& clientSecret)
{
#if UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_AVAILABLE
    clientId = UNIVERSELAN_SYSTEM_TEST_CLIENT_ID;
    clientSecret = UNIVERSELAN_SYSTEM_TEST_CLIENT_SECRET;
    if (profile == "user1")
    {
        login = UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_USER1_NAME;
        password = UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_USER1_PASSWORD;
        return true;
    }
    if (profile == "user2")
    {
        login = UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_USER2_NAME;
        password = UNIVERSELAN_SYSTEM_TEST_CREDENTIALS_USER2_PASSWORD;
        return true;
    }
#else
    (void)profile;
    (void)login;
    (void)password;
    (void)clientId;
    (void)clientSecret;
#endif
    return false;
}

SignInResult initializeAndSignIn(Api& api, const Arguments& arguments)
{
    const char* clientId = "";
    const char* clientSecret = "";
    const char* login = nullptr;
    const char* password = nullptr;
    if (arguments.runtimeProvider == "gog")
    {
        if (arguments.credentialProfile.empty()) return SignInResult::CredentialProfileRequired;
        if (!credentialProfile(arguments.credentialProfile, login, password, clientId, clientSecret))
            return SignInResult::CredentialProfileUnavailable;
    }

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
    api.galaxy = galaxy::api::GalaxyFactory::CreateInstance();
    if (api.galaxy == nullptr) return SignInResult::Failed;
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
    api.galaxy->Init(galaxy::api::InitOptions{clientId, clientSecret, "."});
#else
    api.galaxy->Init(clientId, clientSecret);
#endif
    api.user = api.galaxy->GetUser();
#else
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
    galaxy::api::Init(galaxy::api::InitOptions{clientId, clientSecret, "."});
#else
    galaxy::api::Init(clientId, clientSecret);
#endif
    api.user = galaxy::api::User();
#endif
    if (api.user == nullptr) return SignInResult::Failed;
    if (arguments.runtimeProvider == "gog")
    {
#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINCREDENTIALS
        api.user->SignInCredentials(login, password);
#else
        api.user->SignIn(login, password);
#endif
    }
    else
    {
#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINGALAXY
#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_REQUIREONLINE
    api.user->SignInGalaxy(false);
#else
    api.user->SignInGalaxy();
#endif
#else
#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_REQUIREONLINE
    api.user->SignIn(false);
#else
    api.user->SignIn();
#endif
#endif
    }

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(arguments.timeoutSeconds);
    while (std::chrono::steady_clock::now() < deadline)
    {
        api.processData();
        if (api.user->SignedIn()
#if GALAXY_BUILD_FEATURE_IUSER_HAS_ISLOGGEDON
            && api.user->IsLoggedOn()
#endif
        ) return SignInResult::Succeeded;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return api.user->SignedIn()
#if GALAXY_BUILD_FEATURE_IUSER_HAS_ISLOGGEDON
        && api.user->IsLoggedOn()
#endif
        ? SignInResult::Succeeded : SignInResult::Failed;
}

template <typename Predicate>
bool pumpUntil(Api& api, int timeoutSeconds, Predicate completed)
{
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds);
    while (std::chrono::steady_clock::now() < deadline)
    {
        api.processData();
        if (completed()) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    api.processData();
    return completed();
}

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
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
    void OnLobbyList(uint32_t lobbyCount, galaxy::api::LobbyListResult result) override
    {
        process(lobbyCount, result == galaxy::api::LOBBY_LIST_RESULT_SUCCESS);
    }
 #else
    void OnLobbyList(uint32_t lobbyCount, bool ioFailure) override
    {
        process(lobbyCount, !ioFailure);
    }
 #endif
};

struct LobbyDataUpdateListener final : galaxy::api::ILobbyDataUpdateListener
{
    bool completed = false;
    bool succeeded = false;

    void OnLobbyDataUpdateSuccess(const galaxy::api::GalaxyID&) override
    {
        completed = true;
        succeeded = true;
    }

    void OnLobbyDataUpdateFailure(const galaxy::api::GalaxyID&, FailureReason) override
    {
        completed = true;
    }
};

bool createTaggedLobby(Api& api, const Arguments& arguments)
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
    return savedToken != nullptr && arguments.lobbyToken == savedToken && emit(arguments, "lobby-tagged");
}

bool joinTaggedLobby(Api& api, const Arguments& arguments, galaxy::api::GalaxyID* joinedLobbyId = nullptr)
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
    return emit(arguments, arguments.role + "-joined");
}

bool waitForAction(const Arguments& arguments);
bool waitForCompletion(const Arguments& arguments);

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

    void OnLobbyMemberDataUpdateFailure(const galaxy::api::GalaxyID&, const galaxy::api::GalaxyID&, FailureReason) override
    {
        completed = true;
    }
};

struct LobbyJoinerStateListener final : galaxy::api::GlobalLobbyMemberStateListener
{
    LobbyJoinerStateListener(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId,
        std::uint64_t ownerUserId, std::uint64_t joinerUserId)
        : matchmaking(matchmaking), lobbyId(lobbyId), ownerUserId(ownerUserId), joinerUserId(joinerUserId) {}

    galaxy::api::IMatchmaking* matchmaking;
    galaxy::api::GalaxyID lobbyId;
    std::uint64_t ownerUserId;
    std::uint64_t joinerUserId;
    bool confirmed = false;

    void OnLobbyMemberStateChanged(const galaxy::api::GalaxyID& updatedLobbyId, const galaxy::api::GalaxyID& memberId,
        galaxy::api::LobbyMemberStateChange change) override
    {
        if (updatedLobbyId != lobbyId || memberId.GetRealID() != joinerUserId
            || change != galaxy::api::LOBBY_MEMBER_STATE_CHANGED_ENTERED
            || matchmaking->GetNumLobbyMembers(lobbyId) != 2) return;
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
    RemoteLobbyDataListener(galaxy::api::IMatchmaking* matchmaking, const galaxy::api::GalaxyID& lobbyId)
        : matchmaking(matchmaking), lobbyId(lobbyId) {}

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
    if (!pumpUntil(api, arguments.timeoutSeconds, [&tagListener] { return tagListener.completed; }) || !tagListener.succeeded
        || !emit(arguments, "lobby-tagged")) return false;
    if (!pumpUntil(api, arguments.timeoutSeconds, [&memberStateListener] { return memberStateListener.confirmed; })
        || !emit(arguments, "owner-observed-joiner")) return false;
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
    if (!pumpUntil(api, arguments.timeoutSeconds, [&memberDataListener] { return memberDataListener.completed; }) || !memberDataListener.succeeded
        || !emit(arguments, "joiner-member-data-written")) return false;
    return pumpUntil(api, arguments.timeoutSeconds, [&lobbyDataListener] { return lobbyDataListener.received; })
        && emit(arguments, "joiner-verified-owner-data");
}

bool waitForAction(const Arguments& arguments)
{
    return waitForFile(arguments.controlDirectory / (arguments.role + ".action"), arguments.timeoutSeconds);
}

bool waitForCompletion(const Arguments& arguments)
{
    return arguments.finishAfter.empty() || waitForFile(arguments.controlDirectory / (arguments.role + ".complete"), arguments.timeoutSeconds);
}

std::vector<std::uint8_t> p2pPayload(const char* name)
{
    std::vector<std::uint8_t> payload(name, name + std::char_traits<char>::length(name));
    payload.push_back(0);
    payload.push_back(0xA5);
    return payload;
}

constexpr std::uint8_t rawP2PChannel = 37;

bool sendPacket(Api& api, std::uint64_t peerUserId, const std::vector<std::uint8_t>& payload)
{
    galaxy::api::INetworking* networking = api.networking();
    if (networking == nullptr) return false;
    const galaxy::api::GalaxyID peer = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, peerUserId);
    return networking->SendP2PPacket(peer, payload.data(), static_cast<uint32_t>(payload.size()), galaxy::api::P2P_SEND_RELIABLE, rawP2PChannel);
}

bool receivePacket(Api& api, int timeoutSeconds, std::uint64_t peerUserId, const std::vector<std::uint8_t>& expected)
{
    galaxy::api::INetworking* networking = api.networking();
    if (networking == nullptr) return false;
    const galaxy::api::GalaxyID expectedSender = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, peerUserId);
    return pumpUntil(api, timeoutSeconds, [&]
    {
        uint32_t available = 0;
        if (!networking->IsP2PPacketAvailable(&available, rawP2PChannel)) return false;
        if (available == 0 || available > 256) return false;
        std::array<std::uint8_t, 256> received{};
        uint32_t receivedSize = 0;
        galaxy::api::GalaxyID sender;
        if (!networking->ReadP2PPacket(received.data(), static_cast<uint32_t>(received.size()), &receivedSize, sender, rawP2PChannel)) return false;
        return sender == expectedSender && receivedSize == expected.size()
            && std::equal(expected.begin(), expected.end(), received.begin());
    });
}

bool observeP2PQuiet(Api& api, int timeoutSeconds)
{
    galaxy::api::INetworking* networking = api.networking();
    if (networking == nullptr) return false;
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(std::min(timeoutSeconds * 1000, 750));
    while (std::chrono::steady_clock::now() < deadline)
    {
        api.processData();
        uint32_t available = 0;
        while (networking->IsP2PPacketAvailable(&available, rawP2PChannel))
        {
            std::array<std::uint8_t, 256> ignored{};
            uint32_t receivedSize = 0;
            galaxy::api::GalaxyID sender;
            if (available > ignored.size() || !networking->ReadP2PPacket(ignored.data(), static_cast<uint32_t>(ignored.size()), &receivedSize, sender, rawP2PChannel)) return false;
            return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return true;
}

bool runRawP2PScenario(Api& api, const Arguments& arguments)
{
    const bool creator = arguments.scenario == "raw-p2p-two-creator" || arguments.scenario == "raw-p2p-three-sender";
    if ((creator ? !createTaggedLobby(api, arguments) : !joinTaggedLobby(api, arguments)) || !waitForAction(arguments)) return false;
    if (arguments.scenario == "raw-p2p-two-creator" || arguments.scenario == "raw-p2p-two-joiner")
    {
        if (arguments.peerUserIds.size() != 1) return false;
        const bool isCreator = arguments.scenario == "raw-p2p-two-creator";
        if (!sendPacket(api, arguments.peerUserIds.front(), p2pPayload(isCreator ? "raw-two-creator" : "raw-two-joiner"))
            || !receivePacket(api, arguments.timeoutSeconds, arguments.peerUserIds.front(), p2pPayload(isCreator ? "raw-two-joiner" : "raw-two-creator"))) return false;
        return emit(arguments, arguments.role + "-exchanged") && waitForCompletion(arguments);
    }
    if (arguments.scenario == "raw-p2p-three-sender")
    {
        if (arguments.peerUserIds.size() != 1 || !sendPacket(api, arguments.peerUserIds.front(), p2pPayload("raw-three-target"))) return false;
        if (!emit(arguments, "sender-sent")) return false;
        return receivePacket(api, arguments.timeoutSeconds, arguments.peerUserIds.front(), p2pPayload("raw-three-ack"))
            && emit(arguments, "sender-acked") && waitForCompletion(arguments);
    }
    if (arguments.scenario == "raw-p2p-three-target")
    {
        if (arguments.peerUserIds.size() != 1 || !receivePacket(api, arguments.timeoutSeconds, arguments.peerUserIds.front(), p2pPayload("raw-three-target"))) return false;
        return sendPacket(api, arguments.peerUserIds.front(), p2pPayload("raw-three-ack")) && emit(arguments, "target-acked")
            && waitForCompletion(arguments);
    }
    return arguments.scenario == "raw-p2p-three-observer" && observeP2PQuiet(api, arguments.timeoutSeconds)
        && emit(arguments, "observer-quiet");
}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING && GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
struct ConnectionOpenListener final : galaxy::api::GlobalConnectionOpenListener
{
    bool completed = false;
    bool succeeded = false;
    galaxy::api::ConnectionID connectionId = 0;

    void OnConnectionOpenSuccess(const char*, galaxy::api::ConnectionID id) override
    {
        completed = true;
        succeeded = id != 0;
        connectionId = id;
    }

    void OnConnectionOpenFailure(const char*, FailureReason) override
    {
        completed = true;
    }
};

bool customNetworkingEcho(Api& api, const Arguments& arguments)
{
    galaxy::api::ICustomNetworking* networking = api.customNetworking();
    if (networking == nullptr || arguments.webSocketUrl.empty()) return false;
    if (!ix::initNetSystem()) return false;
    ConnectionOpenListener openListener;
    networking->OpenConnection(arguments.webSocketUrl.c_str(), &openListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&openListener] { return openListener.completed; }) || !openListener.succeeded)
    {
        ix::uninitNetSystem();
        return false;
    }
    const std::vector<std::uint8_t> payload{'e', 'c', 'h', 'o', 0, 'b', 'i', 'n', 'a', 'r', 'y'};
    networking->SendData(openListener.connectionId, payload.data(), static_cast<uint32_t>(payload.size()));
    const bool echoed = pumpUntil(api, arguments.timeoutSeconds, [&]
    {
        const uint32_t available = networking->GetAvailableDataSize(openListener.connectionId);
        if (available == 0) return false;
        if (available != payload.size()) return false;
        std::vector<std::uint8_t> echoed(available);
        networking->ReadData(openListener.connectionId, echoed.data(), available);
        return echoed == payload;
    });
    ix::uninitNetSystem();
    return echoed;
}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICHAT && GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
constexpr const char chatRoomMessage[] = "universelan-system-chat-room-message-v1";
constexpr std::size_t chatRoomMessageLength = sizeof(chatRoomMessage) - 1;

struct ChatRoomMessagesListener final : galaxy::api::GlobalChatRoomMessagesListener
{
    ChatRoomMessagesListener(galaxy::api::IChat* chat, const galaxy::api::GalaxyID& expectedSender)
        : chat(chat), expectedSender(expectedSender) {}

    galaxy::api::IChat* chat;
    galaxy::api::GalaxyID expectedSender;
    bool received = false;

    void OnChatRoomMessagesReceived(galaxy::api::ChatRoomID chatRoomId, uint32_t messageCount, uint32_t longestMessageLength) override
    {
        if (chatRoomId == 0 || messageCount != 1 || longestMessageLength != chatRoomMessageLength) return;
        galaxy::api::ChatMessageID messageId = 0;
        galaxy::api::ChatMessageType messageType = galaxy::api::CHAT_MESSAGE_TYPE_UNKNOWN;
        galaxy::api::GalaxyID senderId;
        uint32_t sendTime = 0;
        std::array<char, chatRoomMessageLength + 1> contents{};
        const uint32_t length = chat->GetChatRoomMessageByIndex(0, messageId, messageType, senderId, sendTime,
            contents.data(), static_cast<uint32_t>(contents.size()));
        received = messageId != 0 && messageType == galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE
            && senderId == expectedSender && length == chatRoomMessageLength
            && std::string(contents.data(), length) == chatRoomMessage;
    }
};

struct ChatRoomWithUserListener final : galaxy::api::IChatRoomWithUserRetrieveListener
{
    explicit ChatRoomWithUserListener(const galaxy::api::GalaxyID& expectedPeer) : expectedPeer(expectedPeer) {}

    galaxy::api::GalaxyID expectedPeer;
    bool completed = false;
    bool succeeded = false;
    galaxy::api::ChatRoomID chatRoomId = 0;

    void OnChatRoomWithUserRetrieveSuccess(galaxy::api::GalaxyID peerId, galaxy::api::ChatRoomID receivedChatRoomId) override
    {
        completed = true;
        succeeded = peerId == expectedPeer && receivedChatRoomId != 0;
        if (succeeded) chatRoomId = receivedChatRoomId;
    }

    void OnChatRoomWithUserRetrieveFailure(galaxy::api::GalaxyID, FailureReason) override
    {
        completed = true;
    }
};

struct ChatRoomMessageSendListener final : galaxy::api::IChatRoomMessageSendListener
{
    explicit ChatRoomMessageSendListener(galaxy::api::ChatRoomID expectedChatRoomId) : expectedChatRoomId(expectedChatRoomId) {}

    galaxy::api::ChatRoomID expectedChatRoomId;
    uint32_t expectedMessageIndex = 0;
    bool completed = false;
    bool succeeded = false;

    void OnChatRoomMessageSendSuccess(galaxy::api::ChatRoomID chatRoomId, uint32_t sentMessageIndex,
        galaxy::api::ChatMessageID messageId, uint32_t) override
    {
        completed = true;
        succeeded = chatRoomId == expectedChatRoomId && sentMessageIndex == expectedMessageIndex && messageId != 0;
    }

    void OnChatRoomMessageSendFailure(galaxy::api::ChatRoomID, uint32_t, FailureReason) override
    {
        completed = true;
    }
};

bool chatRoomMessageReceiver(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IChat* chat = api.chat();
    if (chat == nullptr) return false;
    const galaxy::api::GalaxyID expectedSender = galaxy::api::GalaxyID::FromRealID(
        galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    ChatRoomMessagesListener listener(chat, expectedSender);
    if (!emit(arguments, "receiver-ready")) return false;
    return pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.received; })
        && emit(arguments, "receiver-received");
}

bool chatRoomMessageSender(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IChat* chat = api.chat();
    if (chat == nullptr) return false;
    const galaxy::api::GalaxyID peerId = galaxy::api::GalaxyID::FromRealID(
        galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    ChatRoomWithUserListener roomListener(peerId);
    chat->RequestChatRoomWithUser(peerId, &roomListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&roomListener] { return roomListener.completed; }) || !roomListener.succeeded) return false;
    ChatRoomMessageSendListener sendListener(roomListener.chatRoomId);
    sendListener.expectedMessageIndex = chat->SendChatRoomMessage(roomListener.chatRoomId, chatRoomMessage, &sendListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&sendListener] { return sendListener.completed; }) || !sendListener.succeeded) return false;
    return emit(arguments, "sender-send-succeeded") && waitForCompletion(arguments);
}
#endif

void fail(const std::string& role, const char* reason)
{
    std::cout << "SYSTEM_TEST FAIL role=" << role << " reason=" << reason << std::endl;
}
}

int main(int argc, char* argv[])
{
    Arguments arguments;
    if (!readArguments(argc, argv, arguments))
    {
        fail("unknown", "InvalidArguments");
        return 2;
    }
    if (!waitForFile(arguments.controlDirectory / (arguments.role + ".release"), arguments.timeoutSeconds))
    {
        fail(arguments.role, "ReleaseTimeout");
        return 3;
    }
    if (arguments.version != UNIVERSELAN_SYSTEM_TEST_VERSION || arguments.architecture != UNIVERSELAN_SYSTEM_TEST_ARCH)
    {
        fail(arguments.role, "VersionArchitectureMismatch");
        return 6;
    }

    const bool rawP2PScenario = arguments.scenario == "raw-p2p-two-creator" || arguments.scenario == "raw-p2p-two-joiner"
        || arguments.scenario == "raw-p2p-three-sender" || arguments.scenario == "raw-p2p-three-target"
        || arguments.scenario == "raw-p2p-three-observer";
    const bool lobbyDataMemberScenario = arguments.scenario == "lobby-data-member-owner" || arguments.scenario == "lobby-data-member-joiner";
    const bool lobbyScenario = arguments.scenario == "create-lobby" || arguments.scenario == "list-and-join-lobby"
        || rawP2PScenario || lobbyDataMemberScenario;
    const bool customNetworkingScenario = arguments.scenario == "custom-networking-echo";
    const bool chatRoomMessageScenario = arguments.scenario == "chat-room-message-receiver" || arguments.scenario == "chat-room-message-sender";
    if (arguments.scenario != "initialize-and-sign-in" && !lobbyScenario && !customNetworkingScenario && !chatRoomMessageScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#if !GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
    if (lobbyScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ICHAT || !GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS || !GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    if (chatRoomMessageScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING || !GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
    if (customNetworkingScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif

    Api api;
    const SignInResult signIn = initializeAndSignIn(api, arguments);
    if (signIn != SignInResult::Succeeded)
    {
        if (signIn == SignInResult::CredentialProfileRequired) fail(arguments.role, "CredentialProfileRequired");
        else if (signIn == SignInResult::CredentialProfileUnavailable) fail(arguments.role, "CredentialProfileUnavailable");
        else fail(arguments.role, "SignInTimeout");
        return 4;
    }
    if (arguments.scenario == "create-lobby")
    {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
        if (!createLobby(api, arguments))
        {
            fail(arguments.role, "CreateLobbyFailedOrCompletionTimeout");
            return 4;
        }
#endif
    }
    else if (arguments.scenario == "list-and-join-lobby")
    {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
        if (!listAndJoinLobby(api, arguments))
        {
            fail(arguments.role, "LobbyListOrJoinFailed");
            return 4;
        }
#endif
    }
    else if (rawP2PScenario)
    {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
        if (!runRawP2PScenario(api, arguments))
        {
            fail(arguments.role, "RawP2PFailed");
            return 4;
        }
#endif
    }
    else if (lobbyDataMemberScenario)
    {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
        const bool succeeded = arguments.scenario == "lobby-data-member-owner"
            ? lobbyDataMemberOwner(api, arguments) : lobbyDataMemberJoiner(api, arguments);
        if (!succeeded)
        {
            fail(arguments.role, "LobbyDataMemberPropagationFailed");
            return 4;
        }
#endif
    }
    else if (customNetworkingScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING && GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
        if (!customNetworkingEcho(api, arguments))
        {
            fail(arguments.role, "CustomNetworkingEchoFailed");
            return 4;
        }
#endif
    }
    else if (chatRoomMessageScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICHAT && GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
        const bool succeeded = arguments.scenario == "chat-room-message-receiver"
            ? chatRoomMessageReceiver(api, arguments) : chatRoomMessageSender(api, arguments);
        if (!succeeded)
        {
            fail(arguments.role, "ChatRoomMessageDeliveryFailed");
            return 4;
        }
#endif
    }

    std::cout << "SYSTEM_TEST PASS role=" << arguments.role << std::endl;
    // The runner owns cleanup; avoid version-specific DLL static teardown after PASS.
    std::_Exit(0);
}
