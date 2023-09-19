#include "TestCaseClientDetails.hxx"

#include <GalaxyApi.h>

#include <Tracer.hxx>
#include <magic_enum/magic_enum.hpp>

#include <chrono>
#include <format>
#include <thread>

namespace tracer = universelan::tracer;
using namespace galaxy::api;

class AuthListenerImplGlobal : public galaxy::api::GlobalAuthListener
{
public:
	AuthListenerImplGlobal() = default;
	virtual ~AuthListenerImplGlobal() = default;

	virtual void OnAuthSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAuthFailure(FailureReason reason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"reason: {}",
			magic_enum::enum_name(reason)
		).c_str());
	}

	virtual void OnAuthLost() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}
};

class AccessTokenListenerImplGlobal : public galaxy::api::GlobalAccessTokenListener
{
public:
	AccessTokenListenerImplGlobal() = default;
	virtual ~AccessTokenListenerImplGlobal() = default;

	virtual void OnAccessTokenChanged() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}
};

class AchievementChangeListenerImplGlobal : public galaxy::api::GlobalAchievementChangeListener
{
public:
	AchievementChangeListenerImplGlobal() = default;
	virtual ~AchievementChangeListenerImplGlobal() = default;

	virtual void OnAchievementUnlocked(const char* name) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {}",
			name
		).c_str());
	}
};

class ChatRoomMessageSendListenerImplGlobal : public galaxy::api::GlobalChatRoomMessageSendListener
{
public:
	ChatRoomMessageSendListenerImplGlobal() = default;
	virtual ~ChatRoomMessageSendListenerImplGlobal() = default;

	virtual void OnChatRoomMessageSendSuccess(ChatRoomID chatRoomID, uint32_t sentMessageIndex, ChatMessageID messageID, uint32_t sendTime) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} sentMessageIndex: {} messageID:{} sendTime: {}",
			chatRoomID, sentMessageIndex, messageID, sendTime
		).c_str());
	}

	virtual void OnChatRoomMessageSendFailure(ChatRoomID chatRoomID, uint32_t sentMessageIndex, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} sentMessageIndex: {} failureReason: {}",
			chatRoomID, sentMessageIndex, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class ChatRoomMessagesListenerImplGlobal : public galaxy::api::GlobalChatRoomMessagesListener
{
public:
	ChatRoomMessagesListenerImplGlobal() = default;
	virtual ~ChatRoomMessagesListenerImplGlobal() = default;

	virtual void OnChatRoomMessagesReceived(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} messageCount: {} longestMessageLenght: {}",
			chatRoomID, messageCount, longestMessageLenght
		).c_str());
	}
};

class ChatRoomMessagesRetrieveListenerImplGlobal : public galaxy::api::GlobalChatRoomMessagesRetrieveListener
{
public:
	ChatRoomMessagesRetrieveListenerImplGlobal() = default;
	virtual ~ChatRoomMessagesRetrieveListenerImplGlobal() = default;

	virtual void OnChatRoomMessagesRetrieveSuccess(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} messageCount: {} longestMessageLenght: {}",
			chatRoomID, messageCount, longestMessageLenght
		).c_str());
	}

	virtual void OnChatRoomMessagesRetrieveFailure(ChatRoomID chatRoomID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} failureReason: {}",
			chatRoomID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class ChatRoomWithUserRetrieveListenerImplGlobal : public galaxy::api::GlobalChatRoomWithUserRetrieveListener
{
public:
	ChatRoomWithUserRetrieveListenerImplGlobal() = default;
	virtual ~ChatRoomWithUserRetrieveListenerImplGlobal() = default;

	virtual void OnChatRoomWithUserRetrieveSuccess(GalaxyID userID, ChatRoomID chatRoomID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} chatRoomID: {}",
			userID, chatRoomID
		).c_str());
	}

	virtual void OnChatRoomWithUserRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class ConnectionCloseListenerImplGlobal : public galaxy::api::GlobalConnectionCloseListener
{
public:
	ConnectionCloseListenerImplGlobal() = default;
	virtual ~ConnectionCloseListenerImplGlobal() = default;

	virtual void OnConnectionClosed(ConnectionID connectionID, CloseReason closeReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionID: {} closeReason: {}",
			connectionID, magic_enum::enum_name(closeReason)
		).c_str());
	}
};

class ConnectionDataListenerImplGlobal : public galaxy::api::GlobalConnectionDataListener
{
public:
	ConnectionDataListenerImplGlobal() = default;
	virtual ~ConnectionDataListenerImplGlobal() = default;

	virtual void OnConnectionDataReceived(ConnectionID connectionID, uint32_t dataSize) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionID: {} dataSize: {}",
			connectionID, dataSize
		).c_str());
	}
};

class ConnectionOpenListenerImplGlobal : public galaxy::api::GlobalConnectionOpenListener
{
public:
	ConnectionOpenListenerImplGlobal() = default;
	virtual ~ConnectionOpenListenerImplGlobal() = default;

	virtual void OnConnectionOpenSuccess(const char* connectionString, ConnectionID connectionID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionString: {} connectionID: {}",
			connectionString, connectionID
		).c_str());
	}

	virtual void OnConnectionOpenFailure(const char* connectionString, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionString: {} failureReason: {}",
			connectionString, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class EncryptedAppTicketListenerImplGlobal : public galaxy::api::GlobalEncryptedAppTicketListener
{
public:
	EncryptedAppTicketListenerImplGlobal() = default;
	virtual ~EncryptedAppTicketListenerImplGlobal() = default;

	virtual void OnEncryptedAppTicketRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnEncryptedAppTicketRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class FileShareListenerImplGlobal : public galaxy::api::GlobalFileShareListener
{
public:
	FileShareListenerImplGlobal() = default;
	virtual ~FileShareListenerImplGlobal() = default;

	virtual void OnFileShareSuccess(const char* fileName, SharedFileID sharedFileID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"fileName: {} sharedFileID: {}",
			fileName, sharedFileID
		).c_str());
	}

	virtual void OnFileShareFailure(const char* fileName, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"fileName: {} failureReason: {}",
			fileName, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class FriendAddListenerImplGlobal : public galaxy::api::GlobalFriendAddListener
{
public:
	FriendAddListenerImplGlobal() = default;
	virtual ~FriendAddListenerImplGlobal() = default;

	virtual void OnFriendAdded(GalaxyID userID, InvitationDirection invitationDirection) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} invitationDirection: {}",
			userID, magic_enum::enum_name(invitationDirection)
		).c_str());
	}
};

class FriendDeleteListenerImplGlobal : public galaxy::api::GlobalFriendDeleteListener
{
public:
	FriendDeleteListenerImplGlobal() = default;
	virtual ~FriendDeleteListenerImplGlobal() = default;

	virtual void OnFriendDeleteSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());
	}

	virtual void OnFriendDeleteFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class FriendInvitationListRetrieveListenerImplGlobal : public galaxy::api::GlobalFriendInvitationListRetrieveListener
{
public:
	FriendInvitationListRetrieveListenerImplGlobal() = default;
	virtual ~FriendInvitationListRetrieveListenerImplGlobal() = default;

	virtual void OnFriendInvitationListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class FriendInvitationListenerImplGlobal : public galaxy::api::GlobalFriendInvitationListener
{
public:
	FriendInvitationListenerImplGlobal() = default;
	virtual ~FriendInvitationListenerImplGlobal() = default;

	virtual void OnFriendInvitationReceived(GalaxyID userID, uint32_t sendTime) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} sendTime: {}",
			userID, sendTime
		).c_str());
	}
};

class FriendInvitationRespondToListenerImplGlobal : public galaxy::api::GlobalFriendInvitationRespondToListener
{
public:
	FriendInvitationRespondToListenerImplGlobal() = default;
	virtual ~FriendInvitationRespondToListenerImplGlobal() = default;

	virtual void OnFriendInvitationRespondToSuccess(GalaxyID userID, bool accept) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} accept: {}",
			userID, accept
		).c_str());
	}

	virtual void OnFriendInvitationRespondToFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class FriendInvitationSendListenerImplGlobal : public galaxy::api::GlobalFriendInvitationSendListener
{
public:
	FriendInvitationSendListenerImplGlobal() = default;
	virtual ~FriendInvitationSendListenerImplGlobal() = default;

	virtual void OnFriendInvitationSendSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());
	}

	virtual void OnFriendInvitationSendFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class FriendListListenerImplGlobal : public galaxy::api::GlobalFriendListListener
{
public:
	FriendListListenerImplGlobal() = default;
	virtual ~FriendListListenerImplGlobal() = default;

	virtual void OnFriendListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class GameInvitationReceivedListenerImplGlobal : public galaxy::api::GlobalGameInvitationReceivedListener
{
public:
	GameInvitationReceivedListenerImplGlobal() = default;
	virtual ~GameInvitationReceivedListenerImplGlobal() = default;

	virtual void OnGameInvitationReceived(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());
	}
};

class GameJoinRequestedListenerImplGlobal : public galaxy::api::GlobalGameJoinRequestedListener
{
public:
	GameJoinRequestedListenerImplGlobal() = default;
	virtual ~GameJoinRequestedListenerImplGlobal() = default;

	virtual void OnGameJoinRequested(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());
	}
};

#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
class GogServicesConnectionStateListenerImplGlobal : public galaxy::api::GlobalGogServicesConnectionStateListener
{
public:
	GogServicesConnectionStateListenerImplGlobal() = default;
	virtual ~GogServicesConnectionStateListenerImplGlobal() = default;

	virtual void OnConnectionStateChange(GogServicesConnectionState connectionState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionState: {}",
			magic_enum::enum_name(connectionState)
		).c_str());
	}
};
#endif

class LeaderboardEntriesRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardEntriesRetrieveListener
{
public:
	LeaderboardEntriesRetrieveListenerImplGlobal() = default;
	virtual ~LeaderboardEntriesRetrieveListenerImplGlobal() = default;

	virtual void OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} entryCount: {}",
			name, entryCount
		).c_str());
	}

	virtual void OnLeaderboardEntriesRetrieveFailure(const char* name, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} failureReason: {}",
			name, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class LeaderboardRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardRetrieveListener
{
public:
	LeaderboardRetrieveListenerImplGlobal() = default;
	virtual ~LeaderboardRetrieveListenerImplGlobal() = default;

	virtual void OnLeaderboardRetrieveSuccess(const char* name) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {}",
			name
		).c_str());
	}

	virtual void OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} failureReason: {}",
			name, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class LeaderboardScoreUpdateListenerImplGlobal : public galaxy::api::GlobalLeaderboardScoreUpdateListener
{
public:
	LeaderboardScoreUpdateListenerImplGlobal() = default;
	virtual ~LeaderboardScoreUpdateListenerImplGlobal() = default;

	virtual void OnLeaderboardScoreUpdateSuccess(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} score: {} oldRank: {} newRank: {}",
			name, score, oldRank, newRank
		).c_str());
	}

	virtual void OnLeaderboardScoreUpdateFailure(const char* name, int32_t score, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} score: {} failureReason: {}",
			name, score, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class LeaderboardsRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardsRetrieveListener
{
public:
	LeaderboardsRetrieveListenerImplGlobal() = default;
	virtual ~LeaderboardsRetrieveListenerImplGlobal() = default;

	virtual void OnLeaderboardsRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardsRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class LobbyCreatedListenerImplGlobal : public galaxy::api::GlobalLobbyCreatedListener
{
public:
	LobbyCreatedListenerImplGlobal() = default;
	virtual ~LobbyCreatedListenerImplGlobal() = default;

	virtual void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} failureReason: {}",
			lobbyID, magic_enum::enum_name(result)
		).c_str());
	}
};

class LobbyDataListenerImplGlobal : public galaxy::api::GlobalLobbyDataListener
{
public:
	LobbyDataListenerImplGlobal() = default;
	virtual ~LobbyDataListenerImplGlobal() = default;

	virtual void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} memberID: {}",
			lobbyID, memberID
		).c_str());
	}
};

class LobbyDataRetrieveListenerImplGlobal : public galaxy::api::GlobalLobbyDataRetrieveListener
{
public:
	LobbyDataRetrieveListenerImplGlobal() = default;
	virtual ~LobbyDataRetrieveListenerImplGlobal() = default;

	virtual void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {}",
			lobbyID
		).c_str());
	}

	virtual void OnLobbyDataRetrieveFailure(const GalaxyID& lobbyID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} failureReason: {}",
			lobbyID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class LobbyEnteredListenerImplGlobal : public galaxy::api::GlobalLobbyEnteredListener
{
public:
	LobbyEnteredListenerImplGlobal() = default;
	virtual ~LobbyEnteredListenerImplGlobal() = default;

	virtual void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} result: {}",
			lobbyID, magic_enum::enum_name(result)
		).c_str());
	}
};

class LobbyLeftListenerImplGlobal : public galaxy::api::GlobalLobbyLeftListener
{
public:
	LobbyLeftListenerImplGlobal() = default;
	virtual ~LobbyLeftListenerImplGlobal() = default;

	virtual void OnLobbyLeft(const GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		, LobbyLeaveReason leaveReason
#endif
	) {
		tracer::Trace trace{ "", __FUNCTION__ };

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		trace.write_all(std::format(
			"lobbyID: {} leaveReason: {}",
			lobbyID, magic_enum::enum_name(leaveReason)
		).c_str());
#else
		trace.write_all(std::format(
			"lobbyID: {}",
			lobbyID
		).c_str());
#endif
	}
};

class LobbyListListenerImplGlobal : public galaxy::api::GlobalLobbyListListener
{
public:
	LobbyListListenerImplGlobal() = default;
	virtual ~LobbyListListenerImplGlobal() = default;

	virtual void OnLobbyList(uint32_t lobbyCount
#if HAS_IMATCHMAKING_LOBBY_LIST_RESULT
		, LobbyListResult result
#else
		, bool ioFailure
#endif
	) override {
		tracer::Trace trace{ "", __FUNCTION__ };
#if HAS_IMATCHMAKING_LOBBY_LIST_RESULT
		trace.write_all(std::format(
			"lobbyCount: {} result: {}",
			lobbyCount, magic_enum::enum_name(result)
		).c_str());
#else
		trace.write_all(std::format(
			"lobbyCount: {} ioFailure: {}",
			lobbyCount, ioFailure
		).c_str());
#endif
	}
};

class LobbyMemberStateListenerImplGlobal : public galaxy::api::GlobalLobbyMemberStateListener
{
public:
	LobbyMemberStateListenerImplGlobal() = default;
	virtual ~LobbyMemberStateListenerImplGlobal() = default;

	virtual void OnLobbyMemberStateChanged(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} memberID: {} memberStateChange: {}",
			lobbyID, memberID, magic_enum::enum_name(memberStateChange)
		).c_str());
	}
};

class LobbyMessageListenerImplGlobal : public galaxy::api::GlobalLobbyMessageListener
{
public:
	LobbyMessageListenerImplGlobal() = default;
	virtual ~LobbyMessageListenerImplGlobal() = default;

	virtual void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} senderID: {} messageID: {} messageLength: {}",
			lobbyID, senderID, messageID, messageLength
		).c_str());
	}
};

class LobbyOwnerChangeListenerImplGlobal : public galaxy::api::GlobalLobbyOwnerChangeListener
{
public:
	LobbyOwnerChangeListenerImplGlobal() = default;
	virtual ~LobbyOwnerChangeListenerImplGlobal() = default;

	virtual void OnLobbyOwnerChanged(const GalaxyID& lobbyID, const GalaxyID& newOwnerID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} newOwnerID: {}",
			lobbyID, newOwnerID
		).c_str());
	}
};

class NatTypeDetectionListenerImplGlobal : public galaxy::api::GlobalNatTypeDetectionListener
{
public:
	NatTypeDetectionListenerImplGlobal() = default;
	virtual ~NatTypeDetectionListenerImplGlobal() = default;

	virtual void OnNatTypeDetectionSuccess(NatType natType) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"natType: {}",
			magic_enum::enum_name(natType)
		).c_str());
	}

	virtual void OnNatTypeDetectionFailure() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}
};

class NetworkingListenerImplGlobal : public galaxy::api::GlobalNetworkingListener
{
public:
	NetworkingListenerImplGlobal() = default;
	virtual ~NetworkingListenerImplGlobal() = default;

	virtual void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"msgSize: {} channel: {}",
			msgSize, channel
		).c_str());
	}
};

class NotificationListenerImplGlobal : public galaxy::api::GlobalNotificationListener
{
public:
	NotificationListenerImplGlobal() = default;
	virtual ~NotificationListenerImplGlobal() = default;

	virtual void OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"notificationID: {} typeLength: {} contentSize: {}",
			notificationID, typeLength, contentSize
		).c_str());
	}
};

class OperationalStateChangeListenerImplGlobal : public galaxy::api::GlobalOperationalStateChangeListener
{
public:
	OperationalStateChangeListenerImplGlobal() = default;
	virtual ~OperationalStateChangeListenerImplGlobal() = default;

	virtual void OnOperationalStateChanged(uint32_t operationalState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"operationalState: {}",
			operationalState
		).c_str());
	}
};

class OtherSessionStartListenerImplGlobal : public galaxy::api::GlobalOtherSessionStartListener
{
public:
	OtherSessionStartListenerImplGlobal() = default;
	virtual ~OtherSessionStartListenerImplGlobal() = default;

	virtual void OnOtherSessionStarted() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}
};

class OverlayInitializationStateChangeListenerImplGlobal : public galaxy::api::GlobalOverlayInitializationStateChangeListener
{
public:
	OverlayInitializationStateChangeListenerImplGlobal() = default;
	virtual ~OverlayInitializationStateChangeListenerImplGlobal() = default;

	virtual void OnOverlayStateChanged(OverlayState overlayState) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"overlayState: {}",
			magic_enum::enum_name(overlayState)
		).c_str());
	}
};

// class OverlayStateChangeListenerImplGlobal : public galaxy::api::GlobalOverlayStateChangeListener
// {
// public:
// 	OverlayStateChangeListenerImplGlobal() = default;
// 	virtual ~OverlayStateChangeListenerImplGlobal() = default;
// };

class OverlayVisibilityChangeListenerImplGlobal : public galaxy::api::GlobalOverlayVisibilityChangeListener
{
public:
	OverlayVisibilityChangeListenerImplGlobal() = default;
	virtual ~OverlayVisibilityChangeListenerImplGlobal() = default;

	virtual void OnOverlayVisibilityChanged(bool overlayVisible) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"overlayVisible: {}",
			overlayVisible
		).c_str());
	}
};

class PersonaDataChangedListenerImplGlobal : public galaxy::api::GlobalPersonaDataChangedListener
{
public:
	PersonaDataChangedListenerImplGlobal() = default;
	virtual ~PersonaDataChangedListenerImplGlobal() = default;

	virtual void OnPersonaDataChanged(GalaxyID userID, uint32_t personaStateChange) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} personaStateChange: {}",
			userID, personaStateChange
		).c_str());
	}
};

class RichPresenceChangeListenerImplGlobal : public galaxy::api::GlobalRichPresenceChangeListener
{
public:
	RichPresenceChangeListenerImplGlobal() = default;
	virtual ~RichPresenceChangeListenerImplGlobal() = default;

	virtual void OnRichPresenceChangeSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnRichPresenceChangeFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class RichPresenceListenerImplGlobal : public galaxy::api::GlobalRichPresenceListener
{
public:
	RichPresenceListenerImplGlobal() = default;
	virtual ~RichPresenceListenerImplGlobal() = default;

	virtual void OnRichPresenceUpdated(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());
	}
};

class RichPresenceRetrieveListenerImplGlobal : public galaxy::api::GlobalRichPresenceRetrieveListener
{
public:
	RichPresenceRetrieveListenerImplGlobal() = default;
	virtual ~RichPresenceRetrieveListenerImplGlobal() = default;

	virtual void OnRichPresenceRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());
	}

	virtual void OnRichPresenceRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class SendInvitationListenerImplGlobal : public galaxy::api::GlobalSendInvitationListener
{
public:
	SendInvitationListenerImplGlobal() = default;
	virtual ~SendInvitationListenerImplGlobal() = default;

	virtual void OnInvitationSendSuccess(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());
	}

	virtual void OnInvitationSendFailure(GalaxyID userID, const char* connectionString, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {} failureReason: {}",
			userID, connectionString, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class SentFriendInvitationListRetrieveListenerImplGlobal : public galaxy::api::GlobalSentFriendInvitationListRetrieveListener
{
public:
	SentFriendInvitationListRetrieveListenerImplGlobal() = default;
	virtual ~SentFriendInvitationListRetrieveListenerImplGlobal() = default;

	virtual void OnSentFriendInvitationListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnSentFriendInvitationListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());
	}
};

// class ServerNetworkingListenerImplGlobal : public galaxy::api::GlobalServerNetworkingListener
// {
// public:
// 	ServerNetworkingListenerImplGlobal() = default;
// 	virtual ~ServerNetworkingListenerImplGlobal() = default;
// };

class SharedFileDownloadListenerImplGlobal : public galaxy::api::GlobalSharedFileDownloadListener
{
public:
	SharedFileDownloadListenerImplGlobal() = default;
	virtual ~SharedFileDownloadListenerImplGlobal() = default;

	virtual void OnSharedFileDownloadSuccess(SharedFileID sharedFileID, const char* fileName) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"sharedFileID: {} fileName: {}",
			sharedFileID, fileName
		).c_str());
	}

	virtual void OnSharedFileDownloadFailure(SharedFileID sharedFileID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"sharedFileID: {} failureReason: {}",
			sharedFileID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class SpecificUserDataListenerImplGlobal : public galaxy::api::GlobalSpecificUserDataListener
{
public:
	SpecificUserDataListenerImplGlobal() = default;
	virtual ~SpecificUserDataListenerImplGlobal() = default;

	virtual void OnSpecificUserDataUpdated(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());
	}
};

class StatsAndAchievementsStoreListenerImplGlobal : public galaxy::api::GlobalStatsAndAchievementsStoreListener
{
public:
	StatsAndAchievementsStoreListenerImplGlobal() = default;
	virtual ~StatsAndAchievementsStoreListenerImplGlobal() = default;

	virtual void OnUserStatsAndAchievementsStoreSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserStatsAndAchievementsStoreFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class TelemetryEventSendListenerImplGlobal : public galaxy::api::GlobalTelemetryEventSendListener
{
public:
	TelemetryEventSendListenerImplGlobal() = default;
	virtual ~TelemetryEventSendListenerImplGlobal() = default;

	virtual void OnTelemetryEventSendSuccess(const char* eventType, uint32_t sentEventIndex) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"eventType: {} sentEventIndex: {}",
			eventType, sentEventIndex
		).c_str());
	}

	virtual void OnTelemetryEventSendFailure(const char* eventType, uint32_t sentEventIndex, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"eventType: {} sentEventIndex: {} failureReason: {}",
			eventType, sentEventIndex, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class UserDataListenerImplGlobal : public galaxy::api::GlobalUserDataListener
{
public:
	UserDataListenerImplGlobal() = default;
	virtual ~UserDataListenerImplGlobal() = default;

	virtual void OnUserDataUpdated() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}
};

class UserFindListenerImplGlobal : public galaxy::api::GlobalUserFindListener
{
public:
	UserFindListenerImplGlobal() = default;
	virtual ~UserFindListenerImplGlobal() = default;

	virtual void OnUserFindSuccess(const char* userSpecifier, GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userSpecifier: {} userID: {}",
			userSpecifier, userID
		).c_str());
	}
	virtual void OnUserFindFailure(const char* userSpecifier, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userSpecifier: {} failureReason: {}",
			userSpecifier, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class UserInformationRetrieveListenerImplGlobal : public galaxy::api::GlobalUserInformationRetrieveListener
{
public:
	UserInformationRetrieveListenerImplGlobal() = default;
	virtual ~UserInformationRetrieveListenerImplGlobal() = default;

	virtual void OnUserInformationRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());
	}

	virtual void OnUserInformationRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class UserStatsAndAchievementsRetrieveListenerImplGlobal : public galaxy::api::GlobalUserStatsAndAchievementsRetrieveListener
{
public:
	UserStatsAndAchievementsRetrieveListenerImplGlobal() = default;
	virtual ~UserStatsAndAchievementsRetrieveListenerImplGlobal() = default;

	virtual void OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());
	}

	virtual void OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class UserTimePlayedRetrieveListenerImplGlobal : public galaxy::api::GlobalUserTimePlayedRetrieveListener
{
public:
	UserTimePlayedRetrieveListenerImplGlobal() = default;
	virtual ~UserTimePlayedRetrieveListenerImplGlobal() = default;

	virtual void OnUserTimePlayedRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());
	}

	virtual void OnUserTimePlayedRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());
	}
};

class AuthListenerImplLocal : public galaxy::api::IAuthListener
{
public:
	AuthListenerImplLocal() = default;
	virtual ~AuthListenerImplLocal() = default;

	virtual void OnAuthSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAuthFailure(FailureReason reason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"reason: {}",
			magic_enum::enum_name(reason)
		).c_str());
	}

	virtual void OnAuthLost() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}
};

int main()
{
	tracer::Trace::InitTracing(".", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(true);

	tracer::Trace trace{ "", __FUNCTION__ };

	galaxy::api::InitOptions options(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data());

	galaxy::api::Init(options);

	std::cout << "galaxy::api::Init performed" << std::endl;

	AccessTokenListenerImplGlobal accesstokenlistener{};
	AchievementChangeListenerImplGlobal achievementchangelistener{};
	AuthListenerImplGlobal authlistener{};
	ChatRoomMessageSendListenerImplGlobal chatroommessagesendlistener{};
	ChatRoomMessagesListenerImplGlobal chatroommessageslistener{};
	ChatRoomMessagesRetrieveListenerImplGlobal chatroommessagesretrievelistener{};
	ChatRoomWithUserRetrieveListenerImplGlobal chatroomwithuserretrievelistener{};
	ConnectionCloseListenerImplGlobal connectioncloselistener{};
	ConnectionDataListenerImplGlobal connectiondatalistener{};
	ConnectionOpenListenerImplGlobal connectionopenlistener{};
	EncryptedAppTicketListenerImplGlobal encryptedappticketlistener{};
	FileShareListenerImplGlobal filesharelistener{};
	FriendAddListenerImplGlobal friendaddlistener{};
	FriendDeleteListenerImplGlobal frienddeletelistener{};
	FriendInvitationListRetrieveListenerImplGlobal friendinvitationlistretrievelistener{};
	FriendInvitationListenerImplGlobal friendinvitationlistener{};
	FriendInvitationRespondToListenerImplGlobal friendinvitationrespondtolistener{};
	FriendInvitationSendListenerImplGlobal friendinvitationsendlistener{};
	FriendListListenerImplGlobal friendlistlistener{};
	GameInvitationReceivedListenerImplGlobal gameinvitationreceivedlistener{};
	GameJoinRequestedListenerImplGlobal gamejoinrequestedlistener{};
#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	GogServicesConnectionStateListenerImplGlobal gogservicesconnectionstatelistener{};
#endif
	LeaderboardEntriesRetrieveListenerImplGlobal leaderboardentriesretrievelistener{};
	LeaderboardRetrieveListenerImplGlobal leaderboardretrievelistener{};
	LeaderboardScoreUpdateListenerImplGlobal leaderboardscoreupdatelistener{};
	LeaderboardsRetrieveListenerImplGlobal leaderboardsretrievelistener{};
	LobbyCreatedListenerImplGlobal lobbycreatedlistener{};
	LobbyDataListenerImplGlobal lobbydatalistener{};
	LobbyDataRetrieveListenerImplGlobal lobbydataretrievelistener{};
	LobbyEnteredListenerImplGlobal lobbyenteredlistener{};
	LobbyLeftListenerImplGlobal lobbyleftlistener{};
	LobbyListListenerImplGlobal lobbylistlistener{};
	LobbyMemberStateListenerImplGlobal lobbymemberstatelistener{};
	LobbyMessageListenerImplGlobal lobbymessagelistener{};
	LobbyOwnerChangeListenerImplGlobal lobbyownerchangelistener{};
	NatTypeDetectionListenerImplGlobal nattypedetectionlistener{};
	NetworkingListenerImplGlobal networkinglistener{};
	NotificationListenerImplGlobal notificationlistener{};
	OperationalStateChangeListenerImplGlobal operationalstatechangelistener{};
	OtherSessionStartListenerImplGlobal othersessionstartlistener{};
	OverlayInitializationStateChangeListenerImplGlobal overlayinitializationstatechangelistener{};
	OverlayVisibilityChangeListenerImplGlobal overlayvisibilitychangelistener{};
	PersonaDataChangedListenerImplGlobal personadatachangedlistener{};
	RichPresenceChangeListenerImplGlobal richpresencechangelistener{};
	RichPresenceListenerImplGlobal richpresencelistener{};
	RichPresenceRetrieveListenerImplGlobal richpresenceretrievelistener{};
	SendInvitationListenerImplGlobal sendinvitationlistener{};
	SentFriendInvitationListRetrieveListenerImplGlobal sentfriendinvitationlistretrievelistener{};
	SharedFileDownloadListenerImplGlobal sharedfiledownloadlistener{};
	SpecificUserDataListenerImplGlobal specificuserdatalistener{};
	StatsAndAchievementsStoreListenerImplGlobal statsandachievementsstorelistener{};
	TelemetryEventSendListenerImplGlobal telemetryeventsendlistener{};
	UserDataListenerImplGlobal userdatalistener{};
	UserFindListenerImplGlobal userfindlistener{};
	UserInformationRetrieveListenerImplGlobal userinformationretrievelistener{};
	UserStatsAndAchievementsRetrieveListenerImplGlobal userstatsandachievementsretrievelistener{};
	UserTimePlayedRetrieveListenerImplGlobal usertimeplayedretrievelistener{};

	//ServerNetworkingListenerImplGlobal ServerNetworkingListener();
	//OverlayStateChangeListenerImplGlobal OverlayStateChangeListener();

	AuthListenerImplLocal authlistener_local{};

	std::cout << "Listenerd registered" << std::endl;

	auto credentials = USER_CREDENTIALS[0];
	galaxy::api::User()->SignInCredentials(credentials[0].data(), credentials[1].data());

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
