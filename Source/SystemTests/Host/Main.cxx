#include "Host.hxx"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>

namespace universelan::systemtest::host
{
namespace
{
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
    return common::galaxyRealId(port, portNumber) && portNumber <= 65535;
}

bool readArguments(const int argc, char* argv[], Arguments& arguments)
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
            if (!common::galaxyRealId(value, peerUserId)
                || std::find(arguments.peerUserIds.begin(), arguments.peerUserIds.end(), peerUserId) != arguments.peerUserIds.end()) return false;
            arguments.peerUserIds.push_back(peerUserId);
        }
        else if (option == "--signal")
        {
            if (!common::appendToken(arguments.signals, value)) return false;
        }
        else if (option == "--finish-after")
        {
            if (!common::appendToken(arguments.finishAfter, value)) return false;
        }
        else if (option == "--timeout-seconds")
        {
            try { arguments.timeoutSeconds = std::stoi(value); }
            catch (...) { return false; }
        }
        else return false;
    }
    return common::token(arguments.role) && common::token(arguments.scenario) && !arguments.controlDirectory.empty()
        && common::token(arguments.version) && (arguments.architecture == "x86" || arguments.architecture == "x64")
        && (arguments.runtimeProvider == "universelan" || arguments.runtimeProvider == "gog")
        && (arguments.credentialProfile.empty() || arguments.credentialProfile == "user1" || arguments.credentialProfile == "user2")
        && (arguments.lobbyToken.empty() || common::token(arguments.lobbyToken))
        && (arguments.webSocketUrl.empty() || webSocketUrl(arguments.webSocketUrl))
        && arguments.timeoutSeconds > 0;
}

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

void fail(const std::string& role, const char* reason)
{
    std::cout << "SYSTEM_TEST FAIL role=" << role << " reason=" << reason << std::endl;
}
}

bool waitForFile(const std::filesystem::path& path, const int timeoutSeconds)
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
    std::cout << common::eventPrefix << event << std::endl;
    return true;
}

bool emit(const Arguments& arguments, const std::string& event)
{
    return emit(arguments, event.c_str());
}

bool waitForAction(const Arguments& arguments)
{
    return waitForFile(arguments.controlDirectory / (arguments.role + ".action"), arguments.timeoutSeconds);
}

bool waitForCompletion(const Arguments& arguments)
{
    return arguments.finishAfter.empty() || waitForFile(arguments.controlDirectory / (arguments.role + ".complete"), arguments.timeoutSeconds);
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
}

int main(int argc, char* argv[])
{
    using namespace universelan::systemtest::host;

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

    const bool rawP2PLobbyScenario = arguments.scenario == "raw-p2p-two-creator" || arguments.scenario == "raw-p2p-two-joiner"
        || arguments.scenario == "raw-p2p-three-sender" || arguments.scenario == "raw-p2p-three-target"
        || arguments.scenario == "raw-p2p-three-observer" || arguments.scenario == "raw-p2p-channel-boundary-creator"
        || arguments.scenario == "raw-p2p-channel-boundary-joiner" || arguments.scenario == "raw-p2p-leave-sender"
        || arguments.scenario == "raw-p2p-leave-receiver";
    const bool rawP2POfflineRecipientScenario = arguments.scenario == "raw-p2p-offline-recipient";
    const bool rawP2PScenario = rawP2PLobbyScenario || rawP2POfflineRecipientScenario;
    const bool lobbyDataMemberScenario = arguments.scenario == "lobby-data-member-owner" || arguments.scenario == "lobby-data-member-joiner";
	const bool lobbyMemberLeaveScenario = arguments.scenario == "lobby-member-leave-owner" || arguments.scenario == "lobby-member-leave-joiner";
	const bool lobbyOwnerOwnershipTransferScenario = arguments.scenario == "lobby-owner-ownership-transfer-owner"
		|| arguments.scenario == "lobby-owner-ownership-transfer-joiner";
	const bool lobbyOwnerCloseLifecycleScenario = arguments.scenario == "lobby-owner-close-lifecycle-owner"
		|| arguments.scenario == "lobby-owner-close-lifecycle-joiner";
	const bool lobbyScenario = arguments.scenario == "create-lobby" || arguments.scenario == "list-and-join-lobby"
        || rawP2PLobbyScenario || lobbyDataMemberScenario || lobbyMemberLeaveScenario || lobbyOwnerOwnershipTransferScenario || lobbyOwnerCloseLifecycleScenario;
    const bool customNetworkingEchoScenario = arguments.scenario == "custom-networking-echo";
    const bool customNetworkingCloseScenario = arguments.scenario == "custom-networking-close";
    const bool customNetworkingScenario = customNetworkingEchoScenario || customNetworkingCloseScenario;
    const bool fileShareScenario = arguments.scenario == "file-share-server-persisted-roundtrip"
        || arguments.scenario == "file-share-server-policy-denied"
        || arguments.scenario == "file-share-server-download-policy-denied";
    const bool cloudStorageScenario = arguments.scenario == "cloud-storage-local-roundtrip";
    const bool appsScenario = arguments.scenario == "apps-config-and-dlc-ownership";
    const bool telemetryScenario = arguments.scenario == "telemetry-local-event-result";
    const bool utilsOverlayDisabledInvariantScenario = arguments.scenario == "utils-overlay-disabled-invariant";
    const bool chatRoomMessageScenario = arguments.scenario == "chat-room-message-receiver" || arguments.scenario == "chat-room-message-sender";
    const bool chatRoomReuseScenario = arguments.scenario == "chat-room-reuse-requester" || arguments.scenario == "chat-room-reuse-peer";
    const bool chatRoomUnknownSendFailureScenario = arguments.scenario == "chat-room-unknown-send-failure";
    const bool chatRoomHistoryScenario = arguments.scenario == "chat-room-history-receiver" || arguments.scenario == "chat-room-history-sender";
    const bool onlinePersonaGameInvitationScenario = arguments.scenario == "online-persona-game-invitation-sender"
        || arguments.scenario == "online-persona-game-invitation-receiver";
    const bool richPresenceLivePropagationScenario = arguments.scenario == "rich-presence-live-propagation-writer"
        || arguments.scenario == "rich-presence-live-propagation-receiver";
    const bool statsAchievementUserDataPropagationScenario = arguments.scenario == "stats-achievement-user-data-propagation-writer"
        || arguments.scenario == "stats-achievement-user-data-propagation-reader";
    const bool statsAchievementDurablePersistenceScenario = arguments.scenario == "stats-achievement-durable-persistence-writer"
        || arguments.scenario == "stats-achievement-durable-persistence-reader";
    const bool userDataLivePropagationScenario = arguments.scenario == "user-data-live-propagation-writer"
        || arguments.scenario == "user-data-live-propagation-receiver";
    if (arguments.scenario != "initialize-and-sign-in" && !lobbyScenario && !rawP2POfflineRecipientScenario && !customNetworkingScenario && !chatRoomMessageScenario
        && !chatRoomReuseScenario && !chatRoomUnknownSendFailureScenario
        && !chatRoomHistoryScenario && !onlinePersonaGameInvitationScenario && !richPresenceLivePropagationScenario
        && !statsAchievementUserDataPropagationScenario && !statsAchievementDurablePersistenceScenario && !userDataLivePropagationScenario && !fileShareScenario && !cloudStorageScenario && !appsScenario && !telemetryScenario
        && !utilsOverlayDisabledInvariantScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#if !GALAXY_BUILD_FEATURE_LOBBY_LISTENERS || !GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
    if (lobbyScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
    if (statsAchievementDurablePersistenceScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE || !GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    if (rawP2POfflineRecipientScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE || !GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS || !GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
    if (statsAchievementUserDataPropagationScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER || !GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    if (userDataLivePropagationScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED || !GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS || !GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER || !GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER || !GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER || !GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER || !GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    if (onlinePersonaGameInvitationScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE || !GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
    if (richPresenceLivePropagationScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ICHAT || !GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    if (chatRoomMessageScenario || chatRoomReuseScenario || chatRoomUnknownSendFailureScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ICHAT || !GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS || !GALAXY_BUILD_FEATURE_HAS_ICHATROOMMESSAGERETRIEVELISTENER || !GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE || !GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    if (chatRoomHistoryScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
    if (customNetworkingScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
    if (customNetworkingEchoScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ISTORAGE
    if (fileShareScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
    if (cloudStorageScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_IAPPS || !GALAXY_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE
    if (appsScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
    if (telemetryScenario)
    {
        fail(arguments.role, "UnsupportedScenario");
        return 5;
    }
#endif
#if !GALAXY_BUILD_FEATURE_HAS_IUTILS || !GALAXY_BUILD_FEATURE_HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE || !GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM || !GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
    if (utilsOverlayDisabledInvariantScenario)
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
        if (!createLobby(api, arguments)) { fail(arguments.role, "CreateLobbyFailedOrCompletionTimeout"); return 4; }
#endif
    }
    else if (arguments.scenario == "list-and-join-lobby")
    {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
        if (!listAndJoinLobby(api, arguments)) { fail(arguments.role, "LobbyListOrJoinFailed"); return 4; }
#endif
    }
    else if (rawP2POfflineRecipientScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
        if (!rawP2POfflineRecipient(api, arguments)) { fail(arguments.role, "RawP2POfflineRecipientFailed"); return 4; }
#endif
    }
    else if (rawP2PScenario)
    {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
        if (!runRawP2PScenario(api, arguments)) { fail(arguments.role, "RawP2PFailed"); return 4; }
#endif
    }
    else if (lobbyDataMemberScenario)
    {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
        const bool succeeded = arguments.scenario == "lobby-data-member-owner" ? lobbyDataMemberOwner(api, arguments) : lobbyDataMemberJoiner(api, arguments);
        if (!succeeded) { fail(arguments.role, "LobbyDataMemberPropagationFailed"); return 4; }
#endif
    }
    else if (lobbyMemberLeaveScenario)
    {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
        const bool succeeded = arguments.scenario == "lobby-member-leave-owner" ? lobbyMemberLeaveOwner(api, arguments) : lobbyMemberLeaveJoiner(api, arguments);
        if (!succeeded) { fail(arguments.role, "LobbyMemberLeaveLifecycleFailed"); return 4; }
#endif
    }
	else if (lobbyOwnerOwnershipTransferScenario)
	{
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS && GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
		const bool succeeded = arguments.scenario == "lobby-owner-ownership-transfer-owner"
			? lobbyOwnerOwnershipTransferOwner(api, arguments) : lobbyOwnerOwnershipTransferJoiner(api, arguments);
		if (!succeeded) { fail(arguments.role, "LobbyOwnerOwnershipTransferFailed"); return 4; }
#endif
	}
	else if (lobbyOwnerCloseLifecycleScenario)
	{
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS && GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
		const bool succeeded = arguments.scenario == "lobby-owner-close-lifecycle-owner"
			? lobbyOwnerCloseLifecycleOwner(api, arguments) : lobbyOwnerCloseLifecycleJoiner(api, arguments);
		if (!succeeded) { fail(arguments.role, "LobbyOwnerCloseLifecycleFailed"); return 4; }
#endif
	}
    else if (customNetworkingEchoScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING && GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
        if (!customNetworkingEcho(api, arguments)) { fail(arguments.role, "CustomNetworkingEchoFailed"); return 4; }
#endif
    }
    else if (customNetworkingCloseScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
        if (!customNetworkingClose(api, arguments)) { fail(arguments.role, "CustomNetworkingCloseFailed"); return 4; }
#endif
    }
    else if (fileShareScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
        const bool succeeded = arguments.scenario == "file-share-server-persisted-roundtrip"
            ? fileShareServerPersistedRoundtrip(api, arguments)
            : arguments.scenario == "file-share-server-policy-denied"
                ? fileShareServerPolicyDenied(api, arguments) : fileShareServerDownloadPolicyDenied(api, arguments);
        if (!succeeded) { fail(arguments.role, "FileShareServerPolicyFailed"); return 4; }
#endif
    }
    else if (cloudStorageScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
        if (!cloudStorageLocalRoundtrip(api, arguments)) { fail(arguments.role, "CloudStorageLocalRoundtripFailed"); return 4; }
#endif
    }
    else if (appsScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_IAPPS && GALAXY_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE
        if (!appsConfigAndDlcOwnership(api, arguments)) { fail(arguments.role, "AppsConfigAndDlcOwnershipFailed"); return 4; }
#endif
    }
    else if (telemetryScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
        if (!telemetryLocalEventResult(api, arguments)) { fail(arguments.role, "TelemetryLocalEventResultFailed"); return 4; }
#endif
    }
    else if (utilsOverlayDisabledInvariantScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_IUTILS && GALAXY_BUILD_FEATURE_HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE && GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM && GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
        if (!utilsOverlayDisabledInvariant(api, arguments)) { fail(arguments.role, "UtilsOverlayDisabledInvariantFailed"); return 4; }
#endif
    }
    else if (chatRoomHistoryScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICHAT && GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS && GALAXY_BUILD_FEATURE_HAS_ICHATROOMMESSAGERETRIEVELISTENER && GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
        const bool succeeded = arguments.scenario == "chat-room-history-receiver" ? chatRoomHistoryReceiver(api, arguments) : chatRoomHistorySender(api, arguments);
        if (!succeeded) { fail(arguments.role, "ChatRoomHistoryRetrievalFailed"); return 4; }
#endif
    }
    else if (chatRoomMessageScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICHAT && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
        const bool succeeded = arguments.scenario == "chat-room-message-receiver" ? chatRoomMessageReceiver(api, arguments) : chatRoomMessageSender(api, arguments);
        if (!succeeded) { fail(arguments.role, "ChatRoomMessageDeliveryFailed"); return 4; }
#endif
    }
    else if (chatRoomReuseScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICHAT && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
        const bool succeeded = arguments.scenario == "chat-room-reuse-requester" ? chatRoomReuseRequester(api, arguments) : chatRoomReusePeer(api, arguments);
        if (!succeeded) { fail(arguments.role, "ChatRoomReuseFailed"); return 4; }
#endif
    }
    else if (chatRoomUnknownSendFailureScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_ICHAT && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
        if (!chatRoomUnknownSendFailure(api, arguments)) { fail(arguments.role, "ChatRoomUnknownSendFailureFailed"); return 4; }
#endif
    }
    else if (onlinePersonaGameInvitationScenario)
    {
#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED && GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS && GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER && GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER && GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER && GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
        const bool succeeded = arguments.scenario == "online-persona-game-invitation-sender" ? onlinePersonaGameInvitationSender(api, arguments) : onlinePersonaGameInvitationReceiver(api, arguments);
        if (!succeeded) { fail(arguments.role, "OnlinePersonaGameInvitationFailed"); return 4; }
#endif
    }
    else if (richPresenceLivePropagationScenario)
    {
#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE && GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
        const bool succeeded = arguments.scenario == "rich-presence-live-propagation-writer"
            ? richPresenceLivePropagationWriter(api, arguments) : richPresenceLivePropagationReceiver(api, arguments);
        if (!succeeded) { fail(arguments.role, "RichPresenceLivePropagationFailed"); return 4; }
#endif
    }
    else if (statsAchievementUserDataPropagationScenario)
    {
#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE && GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS && GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
        const bool succeeded = arguments.scenario == "stats-achievement-user-data-propagation-writer"
            ? statsAchievementUserDataPropagationWriter(api, arguments) : statsAchievementUserDataPropagationReader(api, arguments);
        if (!succeeded) { fail(arguments.role, "StatsAchievementUserDataPropagationFailed"); return 4; }
#endif
    }
    else if (statsAchievementDurablePersistenceScenario)
    {
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
        const bool succeeded = arguments.scenario == "stats-achievement-durable-persistence-writer"
            ? statsAchievementDurablePersistenceWriter(api, arguments) : statsAchievementDurablePersistenceReader(api, arguments);
        if (!succeeded) { fail(arguments.role, "StatsAchievementDurablePersistenceFailed"); return 4; }
#endif
    }
    else if (userDataLivePropagationScenario)
    {
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
        const bool succeeded = arguments.scenario == "user-data-live-propagation-writer"
            ? userDataLivePropagationWriter(api, arguments) : userDataLivePropagationReceiver(api, arguments);
        if (!succeeded) { fail(arguments.role, "UserDataLivePropagationFailed"); return 4; }
#endif
    }

    std::cout << "SYSTEM_TEST PASS role=" << arguments.role << std::endl;
    // The runner owns cleanup; avoid version-specific DLL static teardown after PASS.
    std::_Exit(0);
}
