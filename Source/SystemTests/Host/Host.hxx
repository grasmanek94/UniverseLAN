#pragma once

#include "Common/Protocol.hxx"

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>
#include <thread>
#include <vector>

#ifdef GALAXY_EXPORT
#undef GALAXY_EXPORT
#endif

#include <GalaxyApi.h>

namespace universelan::systemtest::host
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

    galaxy::api::IFriends* friends() const { return galaxy::api::Friends(); }
    galaxy::api::IStats* stats() const { return galaxy::api::Stats(); }

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
    galaxy::api::IUtils* utils() const
    {
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
        return galaxy->GetUtils();
#else
        return galaxy::api::Utils();
#endif
    }
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
    galaxy::api::IApps* apps() const { return galaxy::api::Apps(); }
#endif

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
    galaxy::api::ITelemetry* telemetry() const { return galaxy::api::Telemetry(); }
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
    galaxy::api::IStorage* storage() const
    {
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
        return galaxy->GetStorage();
#else
        return galaxy::api::Storage();
#endif
    }
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
    galaxy::api::ICloudStorage* cloudStorage() const { return galaxy::api::CloudStorage(); }
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
    galaxy::api::IChat* chat() const { return galaxy::api::Chat(); }
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

enum class SignInResult { Succeeded, Failed, CredentialProfileRequired, CredentialProfileUnavailable };

bool waitForFile(const std::filesystem::path& path, int timeoutSeconds);
bool waitForAction(const Arguments& arguments);
bool waitForCompletion(const Arguments& arguments);
bool emit(const Arguments& arguments, const char* event);
bool emit(const Arguments& arguments, const std::string& event);
SignInResult initializeAndSignIn(Api& api, const Arguments& arguments);

#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
bool rawP2POfflineRecipient(Api& api, const Arguments& arguments);
#endif

template <typename Predicate>
bool pumpUntil(Api& api, const int timeoutSeconds, Predicate completed)
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
bool createLobby(Api& api, const Arguments& arguments);
bool listAndJoinLobby(Api& api, const Arguments& arguments);
bool createTaggedLobby(Api& api, const Arguments& arguments, galaxy::api::GalaxyID* createdLobbyId = nullptr);
bool joinTaggedLobby(Api& api, const Arguments& arguments, galaxy::api::GalaxyID* joinedLobbyId = nullptr, bool emitJoined = true);
bool lobbyDataMemberOwner(Api& api, const Arguments& arguments);
bool lobbyDataMemberJoiner(Api& api, const Arguments& arguments);
bool lobbyMemberLeaveOwner(Api& api, const Arguments& arguments);
bool lobbyMemberLeaveJoiner(Api& api, const Arguments& arguments);
bool runRawP2PScenario(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS && GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
	bool lobbyOwnerOwnershipTransferOwner(Api& api, const Arguments& arguments);
	bool lobbyOwnerOwnershipTransferJoiner(Api& api, const Arguments& arguments);
	bool lobbyOwnerCloseLifecycleOwner(Api& api, const Arguments& arguments);
	bool lobbyOwnerCloseLifecycleJoiner(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING && GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
bool customNetworkingEcho(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
bool customNetworkingClose(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
bool fileShareServerPersistedRoundtrip(Api& api, const Arguments& arguments);
bool fileShareServerPolicyDenied(Api& api, const Arguments& arguments);
bool fileShareServerDownloadPolicyDenied(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
bool cloudStorageLocalRoundtrip(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS && GALAXY_BUILD_FEATURE_HAS_GETCURRENTGAMELANGUAGE
bool appsConfigAndDlcOwnership(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
bool telemetryLocalEventResult(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUTILS && GALAXY_BUILD_FEATURE_HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE && GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM && GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
bool utilsOverlayDisabledInvariant(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICHAT && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
bool chatRoomMessageReceiver(Api& api, const Arguments& arguments);
bool chatRoomMessageSender(Api& api, const Arguments& arguments);
bool chatRoomReuseRequester(Api& api, const Arguments& arguments);
bool chatRoomReusePeer(Api& api, const Arguments& arguments);
bool chatRoomUnknownSendFailure(Api& api, const Arguments& arguments);
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_ROOMLISTENERS
#if GALAXY_BUILD_FEATURE_HAS_ICHATROOMMESSAGERETRIEVELISTENER && GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
bool chatRoomHistoryReceiver(Api& api, const Arguments& arguments);
bool chatRoomHistorySender(Api& api, const Arguments& arguments);
#endif
#endif
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED && GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS && GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER && GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER && GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER && GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
bool onlinePersonaGameInvitationSender(Api& api, const Arguments& arguments);
bool onlinePersonaGameInvitationReceiver(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE && GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
bool richPresenceLivePropagationWriter(Api& api, const Arguments& arguments);
bool richPresenceLivePropagationReceiver(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE && GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS && GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
bool statsAchievementUserDataPropagationWriter(Api& api, const Arguments& arguments);
bool statsAchievementUserDataPropagationReader(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
bool statsAchievementDurablePersistenceWriter(Api& api, const Arguments& arguments);
bool statsAchievementDurablePersistenceReader(Api& api, const Arguments& arguments);
#endif

#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
bool userDataLivePropagationWriter(Api& api, const Arguments& arguments);
bool userDataLivePropagationReceiver(Api& api, const Arguments& arguments);
#endif
}
