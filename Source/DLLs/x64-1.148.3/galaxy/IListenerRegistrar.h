#ifndef GALAXY_I_LISTENER_REGISTRAR_H
#define GALAXY_I_LISTENER_REGISTRAR_H

/**
 * @file
 * Contains data structures and interfaces related to callback listeners.
 */

#include "stdint.h"
#include <stdlib.h>
#include "GalaxyExport.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * Listener type. Used when registering or unregistering instances of listeners.
		 *
		 * Specific listener interfaces are type-aware, i.e. they provide a convenience
		 * method that returns their type.
		 */
		enum ListenerType
		{
			LISTENER_TYPE_BEGIN, ///< Used for iterating over listener types.
			LOBBY_LIST = LISTENER_TYPE_BEGIN, ///< Used by ILobbyListListener.
			LOBBY_CREATED, ///< Used by ILobbyCreatedListener.
			LOBBY_ENTERED, ///< Used by ILobbyEnteredListener.
			LOBBY_LEFT, ///< Used by ILobbyLeftListener.
			LOBBY_DATA, ///< Used by ILobbyDataListener.
			LOBBY_MEMBER_STATE, ///< Used by ILobbyMemberStateListener.
			LOBBY_OWNER_CHANGE, ///< Used by ILobbyOwnerChangeListener.
			AUTH, ///< Used by IAuthListener.
			LOBBY_MESSAGE, ///< Used by ILobbyMessageListener.
			NETWORKING, ///< Used by INetworkingListener.
			USER_DATA, ///< Used by IUserDataListener.
			USER_STATS_AND_ACHIEVEMENTS_RETRIEVE, ///< Used by IUserStatsAndAchievementsRetrieveListener.
			STATS_AND_ACHIEVEMENTS_STORE, ///< Used by IStatsAndAchievementsStoreListener.
			ACHIEVEMENT_CHANGE, ///< Used by IAchievementChangeListener.
			LEADERBOARDS_RETRIEVE, ///< Used by ILeaderboardsRetrieveListener.
			LEADERBOARD_ENTRIES_RETRIEVE, ///< Used by ILeaderboardEntriesRetrieveListener.
			LEADERBOARD_SCORE_UPDATE_LISTENER, ///< Used by ILeaderboardScoreUpdateListener.
			PERSONA_DATA_CHANGED, ///< Used by IPersonaDataChangedListener.
			RICH_PRESENCE_CHANGE_LISTENER, ///< Used by IRichPresenceChangeListener.
			GAME_JOIN_REQUESTED_LISTENER, ///< Used by IGameJoinRequested.
			OPERATIONAL_STATE_CHANGE, ///< Used by IOperationalStateChangeListener.
			FRIEND_LIST_RETRIEVE, ///< Used by IFriendListListener.
			ENCRYPTED_APP_TICKET_RETRIEVE, ///< Used by IEncryptedAppTicketListener.
			ACCESS_TOKEN_CHANGE, ///< Used by IAccessTokenListener.
			LEADERBOARD_RETRIEVE, ///< Used by ILeaderboardRetrieveListener.
			SPECIFIC_USER_DATA, ///< Used by ISpecificUserDataListener.
			INVITATION_SEND, ///< Used by ISendInvitationListener.
			RICH_PRESENCE_LISTENER, ///< Used by IRichPresenceListener.
			GAME_INVITATION_RECEIVED_LISTENER, ///< Used by IGameInvitationReceivedListener.
			NOTIFICATION_LISTENER, ///< Used by INotificationListener.
			LOBBY_DATA_RETRIEVE, ///< Used by ILobbyDataRetrieveListener.
			USER_TIME_PLAYED_RETRIEVE, ///< Used by IUserTimePlayedRetrieveListener.
			OTHER_SESSION_START, ///< Used by IOtherSessionStartListener.
			FILE_SHARE, ///< Used by IFileShareListener.
			SHARED_FILE_DOWNLOAD, ///< Used by ISharedFileDownloadListener.
			CUSTOM_NETWORKING_CONNECTION_OPEN, ///< Used by IConnectionOpenListener.
			CUSTOM_NETWORKING_CONNECTION_CLOSE, ///< Used by IConnectionCloseListener.
			CUSTOM_NETWORKING_CONNECTION_DATA, ///< Used by IConnectionDataListener.
			OVERLAY_INITIALIZATION_STATE_CHANGE, ///< Used by IOverlayInitializationStateChangeListener.
			OVERLAY_VISIBILITY_CHANGE, ///< Used by IOverlayVisibilityChangeListener.
			CHAT_ROOM_WITH_USER_RETRIEVE_LISTENER, ///< Used by IChatRoomWithUserRetrieveListener.
			CHAT_ROOM_MESSAGE_SEND_LISTENER, ///< Used by IChatRoomMessageSendListener.
			CHAT_ROOM_MESSAGES_LISTENER, ///< Used by IChatRoomMessagesListener.
			FRIEND_INVITATION_SEND_LISTENER, ///< Used by IFriendInvitationSendListener.
			FRIEND_INVITATION_LIST_RETRIEVE_LISTENER, ///< Used by IFriendInvitationListRetrieveListener.
			FRIEND_INVITATION_LISTENER, ///< Used by IFriendInvitationListener.
			FRIEND_INVITATION_RESPOND_TO_LISTENER, ///< Used by IFriendInvitationRespondToListener.
			FRIEND_ADD_LISTENER, ///< Used by IFriendAddListener.
			FRIEND_DELETE_LISTENER, ///< Used by IFriendDeleteListener.
			CHAT_ROOM_MESSAGES_RETRIEVE_LISTENER, ///< Used by IChatRoomMessagesRetrieveListener.
			USER_FIND_LISTENER, ///< Used by IUserFindListener.
			NAT_TYPE_DETECTION, ///< Used by INatTypeDetectionListener.
			SENT_FRIEND_INVITATION_LIST_RETRIEVE_LISTENER, ///< Used by ISentFriendInvitationListRetrieveListener.
			LOBBY_DATA_UPDATE_LISTENER, /// < Used by ILobbyDataUpdateListener.
			LOBBY_MEMBER_DATA_UPDATE_LISTENER, /// < Used by ILobbyDataUpdateListener.
			USER_INFORMATION_RETRIEVE_LISTENER, ///< Used by IUserInformationRetrieveListener.
			RICH_PRESENCE_RETRIEVE_LISTENER, ///< Used by IRichPresenceRetrieveListener.
			GOG_SERVICES_CONNECTION_STATE_LISTENER, ///< Used by IGogServicesConnectionStateListener.
			TELEMETRY_EVENT_SEND_LISTENER, ///< Used by ITelemetryEventSendListener.
			LISTENER_TYPE_END ///< Used for iterating over listener types.
		};

		/**
		 * The interface that is implemented by all specific callback listeners.
		 */
		class IGalaxyListener
		{
		public:

			virtual ~IGalaxyListener()
			{
			}
		};

		/**
		 * The class that is inherited by all specific callback listeners and provides
		 * a static method that returns the type of the specific listener.
		 */
		template<ListenerType type> class GalaxyTypeAwareListener : public IGalaxyListener
		{
		public:

			/**
			 * Returns the type of the listener.
			 *
			 * @return The type of the listener. A value of ListenerType.
			 */
			static ListenerType GetListenerType()
			{
				return type;
			}
		};

		/**
		 * The class that enables and disables global registration of the instances of
		 * specific listeners. You can either use it explicitly, or implicitly by
		 * inheriting from a self-registering basic listener of desired type.
		 */
		class IListenerRegistrar
		{
		public:

			virtual ~IListenerRegistrar()
			{
			}

			/**
			 * Globally registers a callback listener that inherits from IGalaxyListener
			 * and is of any of the standard listener types specified in ListenerType.
			 *
			 * @remark Call Unregister() for all registered listeners before calling
			 * Shutdown().
			 *
			 * @param [in] listenerType The type of the listener. A value of ListenerType.
			 * @param [in] listener The specific listener of the specified type.
			 */
			virtual void Register(ListenerType listenerType, IGalaxyListener* listener) = 0;

			/**
			 * Unregisters a listener previously globally registered with Register()
			 * or registered for specific action.
			 *
			 * Call Unregister() unregisters listener from all pending asynchonous calls.
			 *
			 * @param [in] listenerType The type of the listener. A value of ListenerType.
			 * @param [in] listener The specific listener of the specified type.
			 */
			virtual void Unregister(ListenerType listenerType, IGalaxyListener* listener) = 0;
		};

		/**
		 * @addtogroup Peer
		 * @{
		 */

		/**
		 * Returns an instance of IListenerRegistrar.
		 *
		 * @return An instance of IListenerRegistrar.
		 */
		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar();

		/** @} */

		/**
		 * @addtogroup GameServer
		 * @{
		 */

		/**
		 * Returns an instance of IListenerRegistrar interface the for Game Server entity.
		 *
		 * @return An instance of IListenerRegistrar.
		 */
		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE GameServerListenerRegistrar();

		/** @} */

		/**
		 * The class that is inherited by the self-registering versions of all specific
		 * callback listeners. An instance of a listener that derives from it
		 * automatically globally registers itself for proper callback notifications,
		 * and unregisters when destroyed, which is done with IListenerRegistrar.
		 *
		 * @remark You can provide a custom IListenerRegistrar, yet that would
		 * not make the listener visible for Galaxy Peer. For that the listener
		 * needs to be registered with the IListenerRegistrar of Galaxy Peer.
		 *
		 * @param [in] _Registrar The instance of IListenerRegistrar to use
		 * for registering and unregistering. Defaults to the one provided by Galaxy Peer.
		 */
		template<typename _TypeAwareListener, IListenerRegistrar*(*_Registrar)() = ListenerRegistrar>
		class SelfRegisteringListener : public _TypeAwareListener
		{
		public:

			/**
			 * Creates an instance of SelfRegisteringListener and registers it with the
			 * IListenerRegistrar provided by Galaxy Peer.
			 *
			 * @remark Delete all registered listeners before calling Shutdown().
			 */
			SelfRegisteringListener()
			{
				if (_Registrar())
					_Registrar()->Register(_TypeAwareListener::GetListenerType(), this);
			}

			/**
			 * Destroys the instance of SelfRegisteringListener and unregisters it with
			 * the instance of IListenerRegistrar that was used to register the
			 * listener when it was created.
			 */
			~SelfRegisteringListener()
			{
				if (_Registrar())
					_Registrar()->Unregister(_TypeAwareListener::GetListenerType(), this);
			}
		};

		/** @} */
	}
}

#endif
