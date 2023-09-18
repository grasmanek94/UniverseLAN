#include "TestCaseClientDetails.hxx"

#include <GalaxyApi.h>

#include <Tracer.hxx>

#include <chrono>
#include <thread>

namespace tracer = universelan::tracer;

class AuthListenerImplGlobal : public galaxy::api::GlobalAuthListener
{
public:
    AuthListenerImplGlobal() {

    }

    virtual ~AuthListenerImplGlobal() = default;

    virtual void OnAuthSuccess() override {

    }

    virtual void OnAuthFailure(FailureReason reason) override {

    }

    virtual void OnAuthLost() override {

    }
};

class AuthListenerImplLocal : public galaxy::api::IAuthListener
{
public:
    AuthListenerImplLocal() {

    }

    virtual ~AuthListenerImplLocal() = default;

    virtual void OnAuthSuccess() override {

    }

    virtual void OnAuthFailure(FailureReason reason) override {

    }

    virtual void OnAuthLost() override {

    }
};

class AccessTokenListenerImplGlobal : public galaxy::api::GlobalAccessTokenListener
{
public:
	AccessTokenListenerImplGlobal() {

	}

	virtual ~AccessTokenListenerImplGlobal() = default;

	virtual void OnAccessTokenChanged() {

	}
};

class AchievementChangeListenerImplGlobal : public galaxy::api::GlobalAchievementChangeListener
{
public:
	AchievementChangeListenerImplGlobal() {

	}

	virtual ~AchievementChangeListenerImplGlobal() = default;

	virtual void OnAchievementUnlocked(const char* name) {

	}
};

class AuthListenerImplGlobal : public galaxy::api::GlobalAuthListener
{
public:
	AuthListenerImplGlobal() {

	}

	virtual ~AuthListenerImplGlobal() = default;
};

class ChatRoomMessageSendListenerImplGlobal : public galaxy::api::GlobalChatRoomMessageSendListener
{
public:
	ChatRoomMessageSendListenerImplGlobal() {

	}

	virtual ~ChatRoomMessageSendListenerImplGlobal() = default;
};

class ChatRoomMessagesListenerImplGlobal : public galaxy::api::GlobalChatRoomMessagesListener
{
public:
	ChatRoomMessagesListenerImplGlobal() {

	}

	virtual ~ChatRoomMessagesListenerImplGlobal() = default;
};

class ChatRoomMessagesRetrieveListenerImplGlobal : public galaxy::api::GlobalChatRoomMessagesRetrieveListener
{
public:
	ChatRoomMessagesRetrieveListenerImplGlobal() {

	}

	virtual ~ChatRoomMessagesRetrieveListenerImplGlobal() = default;
};

class ChatRoomWithUserRetrieveListenerImplGlobal : public galaxy::api::GlobalChatRoomWithUserRetrieveListener
{
public:
	ChatRoomWithUserRetrieveListenerImplGlobal() {

	}

	virtual ~ChatRoomWithUserRetrieveListenerImplGlobal() = default;
};

class ConnectionCloseListenerImplGlobal : public galaxy::api::GlobalConnectionCloseListener
{
public:
	ConnectionCloseListenerImplGlobal() {

	}

	virtual ~ConnectionCloseListenerImplGlobal() = default;
};

class ConnectionDataListenerImplGlobal : public galaxy::api::GlobalConnectionDataListener
{
public:
	ConnectionDataListenerImplGlobal() {

	}

	virtual ~ConnectionDataListenerImplGlobal() = default;
};

class ConnectionOpenListenerImplGlobal : public galaxy::api::GlobalConnectionOpenListener
{
public:
	ConnectionOpenListenerImplGlobal() {

	}

	virtual ~ConnectionOpenListenerImplGlobal() = default;
};

class EncryptedAppTicketListenerImplGlobal : public galaxy::api::GlobalEncryptedAppTicketListener
{
public:
	EncryptedAppTicketListenerImplGlobal() {

	}

	virtual ~EncryptedAppTicketListenerImplGlobal() = default;
};

class FileShareListenerImplGlobal : public galaxy::api::GlobalFileShareListener
{
public:
	FileShareListenerImplGlobal() {

	}

	virtual ~FileShareListenerImplGlobal() = default;
};

class FriendAddListenerImplGlobal : public galaxy::api::GlobalFriendAddListener
{
public:
	FriendAddListenerImplGlobal() {

	}

	virtual ~FriendAddListenerImplGlobal() = default;
};

class FriendDeleteListenerImplGlobal : public galaxy::api::GlobalFriendDeleteListener
{
public:
	FriendDeleteListenerImplGlobal() {

	}

	virtual ~FriendDeleteListenerImplGlobal() = default;
};

class FriendInvitationListRetrieveListenerImplGlobal : public galaxy::api::GlobalFriendInvitationListRetrieveListener
{
public:
	FriendInvitationListRetrieveListenerImplGlobal() {

	}

	virtual ~FriendInvitationListRetrieveListenerImplGlobal() = default;
};

class FriendInvitationListenerImplGlobal : public galaxy::api::GlobalFriendInvitationListener
{
public:
	FriendInvitationListenerImplGlobal() {

	}

	virtual ~FriendInvitationListenerImplGlobal() = default;
};

class FriendInvitationRespondToListenerImplGlobal : public galaxy::api::GlobalFriendInvitationRespondToListener
{
public:
	FriendInvitationRespondToListenerImplGlobal() {

	}

	virtual ~FriendInvitationRespondToListenerImplGlobal() = default;
};

class FriendInvitationSendListenerImplGlobal : public galaxy::api::GlobalFriendInvitationSendListener
{
public:
	FriendInvitationSendListenerImplGlobal() {

	}

	virtual ~FriendInvitationSendListenerImplGlobal() = default;
};

class FriendListListenerImplGlobal : public galaxy::api::GlobalFriendListListener
{
public:
	FriendListListenerImplGlobal() {

	}

	virtual ~FriendListListenerImplGlobal() = default;
};

class GameInvitationReceivedListenerImplGlobal : public galaxy::api::GlobalGameInvitationReceivedListener
{
public:
	GameInvitationReceivedListenerImplGlobal() {

	}

	virtual ~GameInvitationReceivedListenerImplGlobal() = default;
};

class GameJoinRequestedListenerImplGlobal : public galaxy::api::GlobalGameJoinRequestedListener
{
public:
	GameJoinRequestedListenerImplGlobal() {

	}

	virtual ~GameJoinRequestedListenerImplGlobal() = default;
};

class GogServicesConnectionStateListenerImplGlobal : public galaxy::api::GlobalGogServicesConnectionStateListener
{
public:
	GogServicesConnectionStateListenerImplGlobal() {

	}

	virtual ~GogServicesConnectionStateListenerImplGlobal() = default;
};

class LeaderboardEntriesRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardEntriesRetrieveListener
{
public:
	LeaderboardEntriesRetrieveListenerImplGlobal() {

	}

	virtual ~LeaderboardEntriesRetrieveListenerImplGlobal() = default;
};

class LeaderboardRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardRetrieveListener
{
public:
	LeaderboardRetrieveListenerImplGlobal() {

	}

	virtual ~LeaderboardRetrieveListenerImplGlobal() = default;
};

class LeaderboardScoreUpdateListenerImplGlobal : public galaxy::api::GlobalLeaderboardScoreUpdateListener
{
public:
	LeaderboardScoreUpdateListenerImplGlobal() {

	}

	virtual ~LeaderboardScoreUpdateListenerImplGlobal() = default;
};

class LeaderboardsRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardsRetrieveListener
{
public:
	LeaderboardsRetrieveListenerImplGlobal() {

	}

	virtual ~LeaderboardsRetrieveListenerImplGlobal() = default;
};

class LobbyCreatedListenerImplGlobal : public galaxy::api::GlobalLobbyCreatedListener
{
public:
	LobbyCreatedListenerImplGlobal() {

	}

	virtual ~LobbyCreatedListenerImplGlobal() = default;
};

class LobbyDataListenerImplGlobal : public galaxy::api::GlobalLobbyDataListener
{
public:
	LobbyDataListenerImplGlobal() {

	}

	virtual ~LobbyDataListenerImplGlobal() = default;
};

class LobbyDataRetrieveListenerImplGlobal : public galaxy::api::GlobalLobbyDataRetrieveListener
{
public:
	LobbyDataRetrieveListenerImplGlobal() {

	}

	virtual ~LobbyDataRetrieveListenerImplGlobal() = default;
};

class LobbyEnteredListenerImplGlobal : public galaxy::api::GlobalLobbyEnteredListener
{
public:
	LobbyEnteredListenerImplGlobal() {

	}

	virtual ~LobbyEnteredListenerImplGlobal() = default;
};

class LobbyLeftListenerImplGlobal : public galaxy::api::GlobalLobbyLeftListener
{
public:
	LobbyLeftListenerImplGlobal() {

	}

	virtual ~LobbyLeftListenerImplGlobal() = default;
};

class LobbyListListenerImplGlobal : public galaxy::api::GlobalLobbyListListener
{
public:
	LobbyListListenerImplGlobal() {

	}

	virtual ~LobbyListListenerImplGlobal() = default;
};

class LobbyMemberStateListenerImplGlobal : public galaxy::api::GlobalLobbyMemberStateListener
{
public:
	LobbyMemberStateListenerImplGlobal() {

	}

	virtual ~LobbyMemberStateListenerImplGlobal() = default;
};

class LobbyMessageListenerImplGlobal : public galaxy::api::GlobalLobbyMessageListener
{
public:
	LobbyMessageListenerImplGlobal() {

	}

	virtual ~LobbyMessageListenerImplGlobal() = default;
};

class LobbyOwnerChangeListenerImplGlobal : public galaxy::api::GlobalLobbyOwnerChangeListener
{
public:
	LobbyOwnerChangeListenerImplGlobal() {

	}

	virtual ~LobbyOwnerChangeListenerImplGlobal() = default;
};

class NatTypeDetectionListenerImplGlobal : public galaxy::api::GlobalNatTypeDetectionListener
{
public:
	NatTypeDetectionListenerImplGlobal() {

	}

	virtual ~NatTypeDetectionListenerImplGlobal() = default;
};

class NetworkingListenerImplGlobal : public galaxy::api::GlobalNetworkingListener
{
public:
	NetworkingListenerImplGlobal() {

	}

	virtual ~NetworkingListenerImplGlobal() = default;
};

class NotificationListenerImplGlobal : public galaxy::api::GlobalNotificationListener
{
public:
	NotificationListenerImplGlobal() {

	}

	virtual ~NotificationListenerImplGlobal() = default;
};

class OperationalStateChangeListenerImplGlobal : public galaxy::api::GlobalOperationalStateChangeListener
{
public:
	OperationalStateChangeListenerImplGlobal() {

	}

	virtual ~OperationalStateChangeListenerImplGlobal() = default;
};

class OtherSessionStartListenerImplGlobal : public galaxy::api::GlobalOtherSessionStartListener
{
public:
	OtherSessionStartListenerImplGlobal() {

	}

	virtual ~OtherSessionStartListenerImplGlobal() = default;
};

class OverlayInitializationStateChangeListenerImplGlobal : public galaxy::api::GlobalOverlayInitializationStateChangeListener
{
public:
	OverlayInitializationStateChangeListenerImplGlobal() {

	}

	virtual ~OverlayInitializationStateChangeListenerImplGlobal() = default;
};

// class OverlayStateChangeListenerImplGlobal : public galaxy::api::GlobalOverlayStateChangeListener
// {
// public:
// 	OverlayStateChangeListenerImplGlobal() {
// 
// 	}
// 
// 	virtual ~OverlayStateChangeListenerImplGlobal() = default;
// };

class OverlayVisibilityChangeListenerImplGlobal : public galaxy::api::GlobalOverlayVisibilityChangeListener
{
public:
	OverlayVisibilityChangeListenerImplGlobal() {

	}

	virtual ~OverlayVisibilityChangeListenerImplGlobal() = default;
};

class PersonaDataChangedListenerImplGlobal : public galaxy::api::GlobalPersonaDataChangedListener
{
public:
	PersonaDataChangedListenerImplGlobal() {

	}

	virtual ~PersonaDataChangedListenerImplGlobal() = default;
};

class RichPresenceChangeListenerImplGlobal : public galaxy::api::GlobalRichPresenceChangeListener
{
public:
	RichPresenceChangeListenerImplGlobal() {

	}

	virtual ~RichPresenceChangeListenerImplGlobal() = default;
};

class RichPresenceListenerImplGlobal : public galaxy::api::GlobalRichPresenceListener
{
public:
	RichPresenceListenerImplGlobal() {

	}

	virtual ~RichPresenceListenerImplGlobal() = default;
};

class RichPresenceRetrieveListenerImplGlobal : public galaxy::api::GlobalRichPresenceRetrieveListener
{
public:
	RichPresenceRetrieveListenerImplGlobal() {

	}

	virtual ~RichPresenceRetrieveListenerImplGlobal() = default;
};

class SendInvitationListenerImplGlobal : public galaxy::api::GlobalSendInvitationListener
{
public:
	SendInvitationListenerImplGlobal() {

	}

	virtual ~SendInvitationListenerImplGlobal() = default;
};

class SentFriendInvitationListRetrieveListenerImplGlobal : public galaxy::api::GlobalSentFriendInvitationListRetrieveListener
{
public:
	SentFriendInvitationListRetrieveListenerImplGlobal() {

	}

	virtual ~SentFriendInvitationListRetrieveListenerImplGlobal() = default;
};

// class ServerNetworkingListenerImplGlobal : public galaxy::api::GlobalServerNetworkingListener
// {
// public:
// 	ServerNetworkingListenerImplGlobal() {
// 
// 	}
// 
// 	virtual ~ServerNetworkingListenerImplGlobal() = default;
// };

class SharedFileDownloadListenerImplGlobal : public galaxy::api::GlobalSharedFileDownloadListener
{
public:
	SharedFileDownloadListenerImplGlobal() {

	}

	virtual ~SharedFileDownloadListenerImplGlobal() = default;
};

class SpecificUserDataListenerImplGlobal : public galaxy::api::GlobalSpecificUserDataListener
{
public:
	SpecificUserDataListenerImplGlobal() {

	}

	virtual ~SpecificUserDataListenerImplGlobal() = default;
};

class StatsAndAchievementsStoreListenerImplGlobal : public galaxy::api::GlobalStatsAndAchievementsStoreListener
{
public:
	StatsAndAchievementsStoreListenerImplGlobal() {

	}

	virtual ~StatsAndAchievementsStoreListenerImplGlobal() = default;
};

class TelemetryEventSendListenerImplGlobal : public galaxy::api::GlobalTelemetryEventSendListener
{
public:
	TelemetryEventSendListenerImplGlobal() {

	}

	virtual ~TelemetryEventSendListenerImplGlobal() = default;
};

class UserDataListenerImplGlobal : public galaxy::api::GlobalUserDataListener
{
public:
	UserDataListenerImplGlobal() {

	}

	virtual ~UserDataListenerImplGlobal() = default;
};

class UserFindListenerImplGlobal : public galaxy::api::GlobalUserFindListener
{
public:
	UserFindListenerImplGlobal() {

	}

	virtual ~UserFindListenerImplGlobal() = default;
};

class UserInformationRetrieveListenerImplGlobal : public galaxy::api::GlobalUserInformationRetrieveListener
{
public:
	UserInformationRetrieveListenerImplGlobal() {

	}

	virtual ~UserInformationRetrieveListenerImplGlobal() = default;
};

class UserStatsAndAchievementsRetrieveListenerImplGlobal : public galaxy::api::GlobalUserStatsAndAchievementsRetrieveListener
{
public:
	UserStatsAndAchievementsRetrieveListenerImplGlobal() {

	}

	virtual ~UserStatsAndAchievementsRetrieveListenerImplGlobal() = default;
};

class UserTimePlayedRetrieveListenerImplGlobal : public galaxy::api::GlobalUserTimePlayedRetrieveListener
{
public:
	UserTimePlayedRetrieveListenerImplGlobal() {

	}

	virtual ~UserTimePlayedRetrieveListenerImplGlobal() = default;
};


int main()
{
    tracer::Trace::InitTracing(".", false, true, false, 0, true);
    tracer::Trace::SetLogToCout(true);

    tracer::Trace trace{"", __FUNCTION__};

    galaxy::api::InitOptions options(galaxy::api::CLIENT_ID_STR.data(), galaxy::api::CLIENT_SECRET.data());

    galaxy::api::Init(options);

    while (true)
    {
        galaxy::api::ProcessData();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    return 0;
}

// GameServerGlobalAccessTokenListener
// GameServerGlobalAuthListener
// GameServerGlobalEncryptedAppTicketListener
// GameServerGlobalGogServicesConnectionStateListener
// GameServerGlobalLobbyCreatedListener
// GameServerGlobalLobbyDataListener
// GameServerGlobalLobbyDataRetrieveListener
// GameServerGlobalLobbyEnteredListener
// GameServerGlobalLobbyLeftListener
// GameServerGlobalLobbyMemberStateListener
// GameServerGlobalLobbyMessageListener
// GameServerGlobalNatTypeDetectionListener
// GameServerGlobalNetworkingListener
// GameServerGlobalOperationalStateChangeListener
// GameServerGlobalOtherSessionStartListener
// GameServerGlobalServerNetworkingListener
// GameServerGlobalSpecificUserDataListener
// GameServerGlobalTelemetryEventSendListener
// GameServerGlobalUserDataListener
// 
// GlobalAccessTokenListener
// GlobalAchievementChangeListener
// GlobalAuthListener
// GlobalChatRoomMessageSendListener
// GlobalChatRoomMessagesListener
// GlobalChatRoomMessagesRetrieveListener
// GlobalChatRoomWithUserRetrieveListener
// GlobalConnectionCloseListener
// GlobalConnectionDataListener
// GlobalConnectionOpenListener
// GlobalEncryptedAppTicketListener
// GlobalFileShareListener
// GlobalFriendAddListener
// GlobalFriendDeleteListener
// GlobalFriendInvitationListRetrieveListener
// GlobalFriendInvitationListener
// GlobalFriendInvitationRespondToListener
// GlobalFriendInvitationSendListener
// GlobalFriendListListener
// GlobalGameInvitationReceivedListener
// GlobalGameJoinRequestedListener
// GlobalGogServicesConnectionStateListener
// GlobalLeaderboardEntriesRetrieveListener
// GlobalLeaderboardRetrieveListener
// GlobalLeaderboardScoreUpdateListener
// GlobalLeaderboardsRetrieveListener
// GlobalLobbyCreatedListener
// GlobalLobbyDataListener
// GlobalLobbyDataRetrieveListener
// GlobalLobbyEnteredListener
// GlobalLobbyLeftListener
// GlobalLobbyListListener
// GlobalLobbyMemberStateListener
// GlobalLobbyMessageListener
// GlobalLobbyOwnerChangeListener
// GlobalNatTypeDetectionListener
// GlobalNetworkingListener
// GlobalNotificationListener
// GlobalOperationalStateChangeListener
// GlobalOtherSessionStartListener
// GlobalOverlayInitializationStateChangeListener
// GlobalOverlayStateChangeListener
// GlobalOverlayVisibilityChangeListener
// GlobalPersonaDataChangedListener
// GlobalRichPresenceChangeListener
// GlobalRichPresenceListener
// GlobalRichPresenceRetrieveListener
// GlobalSendInvitationListener
// GlobalSentFriendInvitationListRetrieveListener
// GlobalServerNetworkingListener
// GlobalSharedFileDownloadListener
// GlobalSpecificUserDataListener
// GlobalStatsAndAchievementsStoreListener
// GlobalTelemetryEventSendListener
// GlobalUserDataListener
// GlobalUserFindListener
// GlobalUserInformationRetrieveListener
// GlobalUserStatsAndAchievementsRetrieveListener
// GlobalUserTimePlayedRetrieveListener
