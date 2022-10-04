#ifndef GALAXY_I_MATCHMAKING_H
#define GALAXY_I_MATCHMAKING_H

/**
 * @file
 * Contains data structures and interfaces related to matchmaking.
 */

#include "GalaxyID.h"
#include "IListenerRegistrar.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * Lobby type. Used for specifying visibility of a lobby and protecting it.
		 */
		enum LobbyType
		{
			LOBBY_TYPE_PRIVATE = 0, ///< Only invited users are able to join the lobby. Forbidden for the Game Server.
			LOBBY_TYPE_FRIENDS_ONLY = 1, ///< Visible only to friends or invitees, but not in lobby list. Forbidden for the Game Server.
			LOBBY_TYPE_PUBLIC = 2, ///< Visible for friends and in lobby list.
			LOBBY_TYPE_INVISIBLE_TO_FRIENDS = 3 ///< Returned by search, but not visible to friends. Forbidden for the Game Server.
		};

		/**
		 * Lobby topology type. Used for specifying topology of user connections in lobby.
		 */
		enum LobbyTopologyType
		{
			DEPRECATED_LOBBY_TOPOLOGY_TYPE_FCM_HOST_MIGRATION = 0, ///< All users are connected with each other. Disconnection of lobby owner results in choosing a new one. Deprecated: use LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION instead.
			LOBBY_TOPOLOGY_TYPE_FCM = 1, ///< All users are connected with each other. Disconnection of lobby owner results in closing the lobby.
			LOBBY_TOPOLOGY_TYPE_STAR = 2, ///< All users are connected with lobby owner. Disconnection of lobby owner results in closing the lobby.
			LOBBY_TOPOLOGY_TYPE_CONNECTIONLESS = 3, ///< All users are connected only with server. Disconnection of lobby owner results in choosing a new one. Forbidden for the Game Server.
			LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION = 4 ///< All users are connected with each other. Disconnection of lobby owner results in choosing a new one. Forbidden for the Game Server.
		};

		/**
		 * Change of the state of a lobby member. Used in notifications.
		 */
		enum LobbyMemberStateChange
		{
			LOBBY_MEMBER_STATE_CHANGED_ENTERED = 0x0001, ///< The user joined the lobby.
			LOBBY_MEMBER_STATE_CHANGED_LEFT = 0x0002, ///< The user left the lobby having announced it first.
			LOBBY_MEMBER_STATE_CHANGED_DISCONNECTED = 0x0004, ///< The user disconnected without leaving the lobby first.
			LOBBY_MEMBER_STATE_CHANGED_KICKED = 0x0008, ///< User was kicked from the lobby.
			LOBBY_MEMBER_STATE_CHANGED_BANNED = 0x0010 ///< User was kicked and banned from the lobby.
		};

		/**
		 * Comparison type. Used for specifying filters that are supposed to be invoked
		 * to validate lobby properties when requesting for a list of matching lobbies.
		 */
		enum LobbyComparisonType
		{
			LOBBY_COMPARISON_TYPE_EQUAL = 0, ///< The lobby should have a property of a value that is equal to the one specified.
			LOBBY_COMPARISON_TYPE_NOT_EQUAL = 1, ///< The lobby should have a property of a value that is not equal to the one specified.
			LOBBY_COMPARISON_TYPE_GREATER = 2, ///< The lobby should have a property of a value that is greater than the one specified.
			LOBBY_COMPARISON_TYPE_GREATER_OR_EQUAL = 3, ///< The lobby should have a property of a value that is greater than or equal to the one specified.
			LOBBY_COMPARISON_TYPE_LOWER = 4, ///< The lobby should have a property of a value that is lower than the one specified.
			LOBBY_COMPARISON_TYPE_LOWER_OR_EQUAL = 5, ///< The lobby should have a property of a value that is lower than or equal to the one specified.
			LOBBY_COMPARISON_TYPE_NEAR = 6
		};

		/**
		 * Lobby creating result.
		 */
		enum LobbyCreateResult
		{
			LOBBY_CREATE_RESULT_SUCCESS, ///< Lobby was created.
			LOBBY_CREATE_RESULT_ERROR ///< Unexpected error.
		};

		/**
		 * Lobby entering result.
		 */
		enum LobbyEnterResult
		{
			LOBBY_ENTER_RESULT_SUCCESS, ///< The user has entered the lobby.
			LOBBY_ENTER_RESULT_LOBBY_DOES_NOT_EXIST, ///< Specified lobby does not exist.
			LOBBY_ENTER_RESULT_LOBBY_IS_FULL, ///< Specified lobby is full.
			LOBBY_ENTER_RESULT_ERROR ///< Unexpected error.
		};

		/**
		 * Listener for the event of receiving a list of lobbies.
		 */
		class ILobbyListListener : public GalaxyTypeAwareListener<LOBBY_LIST>
		{
		public:

			/**
			 * Notification for the event of receiving a list of lobbies.
			 *
			 * @param [in] lobbyCount The number of matched lobbies.
			 * @param [in] ioFailure The flag that indicates a failure.
			 */
			virtual void OnLobbyList(uint32_t lobbyCount, bool ioFailure) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyListListener.
		 */
		typedef SelfRegisteringListener<ILobbyListListener> GlobalLobbyListListener;

		/**
		 * Listener for the event of creating a lobby.
		 */
		class ILobbyCreatedListener : public GalaxyTypeAwareListener<LOBBY_CREATED>
		{
		public:

			/**
			 * Notification for the event of creating a lobby.
			 *
			 * When the lobby is successfully created it is joined and ready to use.
			 * Since the lobby is entered automatically, an explicit notification
			 * for ILobbyEnteredListener will follow immediately.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] result lobby create result.
			 */
			virtual void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyCreatedListener.
		 */
		typedef SelfRegisteringListener<ILobbyCreatedListener> GlobalLobbyCreatedListener;

		/**
		 * Globally self-registering version of ILobbyCreatedListener for the Game Server.
		 */
		typedef SelfRegisteringListener<ILobbyCreatedListener, GameServerListenerRegistrar> GameServerGlobalLobbyCreatedListener;

		/**
		 * Listener for the event of entering a lobby.
		 */
		class ILobbyEnteredListener : public GalaxyTypeAwareListener<LOBBY_ENTERED>
		{
		public:

			/**
			 * Notification for the event of entering a lobby.
			 *
			 * It is called both after joining an existing lobby and after creating one.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] result lobby enter result.
			 */
			virtual void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyEnteredListener.
		 */
		typedef SelfRegisteringListener<ILobbyEnteredListener> GlobalLobbyEnteredListener;

		/**
		 * Globally self-registering version of ILobbyEnteredListener for the GameServer.
		 */
		typedef SelfRegisteringListener<ILobbyEnteredListener, GameServerListenerRegistrar> GameServerGlobalLobbyEnteredListener;

		/**
		 * Listener for the event of leaving a lobby.
		 */
		class ILobbyLeftListener : public GalaxyTypeAwareListener<LOBBY_LEFT>
		{
		public:

			/**
			 * Notification for the event of leaving lobby.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] ioFailure The flag that indicates a failure.
			 */
			virtual void OnLobbyLeft(const GalaxyID& lobbyID, bool ioFailure) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyLeftListener.
		 */
		typedef SelfRegisteringListener<ILobbyLeftListener> GlobalLobbyLeftListener;

		/**
		 * Globally self-registering version of ILobbyLeftListener for the GameServer.
		 */
		typedef SelfRegisteringListener<ILobbyLeftListener, GameServerListenerRegistrar> GameServerGlobalLobbyLeftListener;

		/**
		 * Listener for the event of receiving an updated version of lobby data.
		 */
		class ILobbyDataListener : public GalaxyTypeAwareListener<LOBBY_DATA>
		{
		public:

			/**
			 * Notification for the event of receiving an updated version of lobby data.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] memberID The ID of the lobby member, valid only if it is a change in a lobby member data.
			 */
			virtual void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyDataListener.
		 */
		typedef SelfRegisteringListener<ILobbyDataListener> GlobalLobbyDataListener;

		/**
		 * Globally self-registering version of ILobbyDataListener for the Game Server.
		 */
		typedef SelfRegisteringListener<ILobbyDataListener, GameServerListenerRegistrar> GameServerGlobalLobbyDataListener;

		/**
		 * Listener for the event of retrieving lobby data.
		 */
		class ILobbyDataRetrieveListener : public GalaxyTypeAwareListener<LOBBY_DATA_RETRIEVE>
		{
		public:

			/**
			 * Notification for the event of success in retrieving lobby data.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 */
			virtual void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID) = 0;

			/**
			 * The reason of a failure in retrieving lobby data.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_LOBBY_DOES_NOT_EXIST ///< Specified lobby does not exist.
			};

			/**
			 * Notification for the event of a failure in retrieving lobby data.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnLobbyDataRetrieveFailure(const GalaxyID& lobbyID, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyDataRetrieveListener.
		 */
		typedef SelfRegisteringListener<ILobbyDataRetrieveListener> GlobalLobbyDataRetrieveListener;

		/**
		 * Globally self-registering version of ILobbyDataRetrieveListener for the Game Server.
		 */
		typedef SelfRegisteringListener<ILobbyDataRetrieveListener, GameServerListenerRegistrar> GameServerGlobalLobbyDataRetrieveListener;

		/**
		 * Listener for the event of a change of the state of a lobby member.
		 */
		class ILobbyMemberStateListener : public GalaxyTypeAwareListener<LOBBY_MEMBER_STATE>
		{
		public:

			/**
			 * Notification for the event of a change of the state of a lobby member.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] memberID The ID of the lobby member.
			 * @param [in] memberStateChange Change of the state of the lobby member.
			 */
			virtual void OnLobbyMemberStateChanged(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyMemberStateListener.
		 */
		typedef SelfRegisteringListener<ILobbyMemberStateListener> GlobalLobbyMemberStateListener;

		/**
		 * Globally self-registering version of ILobbyMemberStateListener for the Game Server.
		 */
		typedef SelfRegisteringListener<ILobbyMemberStateListener, GameServerListenerRegistrar> GameServerGlobalLobbyMemberStateListener;

		/**
		 * Listener for the event of changing the owner of a lobby.
		 *
		 * The event occurs when a lobby member is chosen to become the new owner
		 * of the lobby in place of the previous owner that apparently left the lobby,
		 * which should be explicitly indicated in a separate notification.
		 *
		 * @remark This listener should be implemented only if the game can handle the situation
		 * where the lobby owner leaves the lobby for any reason (e.g. is disconnected),
		 * letting the other users continue playing in the same lobby with the new owner
		 * knowing the state of the lobby and taking the responsibility for managing it.
		 */
		class ILobbyOwnerChangeListener : public GalaxyTypeAwareListener<LOBBY_OWNER_CHANGE>
		{
		public:

			/**
			 * Notification for the event of someone else becoming the owner of a lobby.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] newOwnerID The ID of the user who became new lobby owner.
			 */
			virtual void OnLobbyOwnerChanged(const GalaxyID& lobbyID, const GalaxyID& newOwnerID) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyOwnerChangeListener.
		 */
		typedef SelfRegisteringListener<ILobbyOwnerChangeListener> GlobalLobbyOwnerChangeListener;

		/**
		 * Listener for the event of receiving a lobby message.
		 */
		class ILobbyMessageListener : public GalaxyTypeAwareListener<LOBBY_MESSAGE>
		{
		public:

			/**
			 * Notification for the event of receiving a lobby message.
			 *
			 * To read the message you need to call IMatchmaking::GetLobbyMessage().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] senderID The ID of the sender.
			 * @param [in] messageID The ID of the message.
			 * @param [in] messageLength Length of the message.
			 */
			virtual void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyMessageListener.
		 */
		typedef SelfRegisteringListener<ILobbyMessageListener> GlobalLobbyMessageListener;

		/**
		 * Globally self-registering version of ILobbyMessageListener for the Game Server.
		 */
		typedef SelfRegisteringListener<ILobbyMessageListener, GameServerListenerRegistrar> GameServerGlobalLobbyMessageListener;

		/**
		 * The interface for managing game lobbies.
		 */
		class IMatchmaking
		{
		public:

			virtual ~IMatchmaking()
			{
			}

			/**
			 * Creates a lobby.
			 *
			 * Depending on the lobby type specified, the lobby will be visible for
			 * other users and joinable either for everyone or just specific users.
			 *
			 * This call is asynchronous. Responses come to the ILobbyCreatedListener,
			 * as well as ILobbyEnteredListener, provided that the lobby was created
			 * successfully, in which case the owning user enters it automatically.
			 *
			 * @param [in] lobbyType The type of the lobby.
			 * @param [in] maxMembers The maximum number of members allowed for the lobby with the limit of 250 members.
			 * @param [in] joinable Is the lobby joinable.
			 * @param [in] lobbyTopologyType The type of the lobby topology.
			 */
			virtual void CreateLobby(LobbyType lobbyType, uint32_t maxMembers, bool joinable, LobbyTopologyType lobbyTopologyType) = 0;

			/**
			 * Performs a request for a list of relevant lobbies.
			 *
			 * This call is asynchronous. When the list is received, a notification will
			 * come to the ILobbyListListener. The notification contains only the number
			 * of lobbies that were found and are available for reading.
			 *
			 * In order to read subsequent lobbies, call GetLobbyByIndex().
			 *
			 * @remark The resulting list of lobbies is filtered according to all the
			 * filters that were specified prior to this call and after the previous
			 * request for lobby list, since filters are consumed only once and not used
			 * again.
			 *
			 * @remark Full lobbies are never included in the list.
			 *
			 * @param [in] allowFullLobbies Are full lobbies allowed.
			 */
			virtual void RequestLobbyList(bool allowFullLobbies = false) = 0;

			/**
			 * Adds a string filter to be applied next time you call RequestLobbyList().
			 *
			 * You can add multiple filters. All filters operate on lobby properties.
			 *
			 * @remark After each call to RequestLobbyList() all filters are cleared.
			 *
			 * @param [in] keyToMatch The key to match.
			 * @param [in] valueToMatch The value to match.
			 * @param [in] comparisonType The type of comparison.
			 */
			virtual void AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, LobbyComparisonType comparisonType) = 0;

			/**
			 * Adds a numerical filter to be applied next time you call RequestLobbyList().
			 *
			 * You can add multiple filters. All filters operate on lobby properties.
			 *
			 * @remark After each call to RequestLobbyList() all filters are cleared.
			 *
			 * @param [in] keyToMatch The key to match.
			 * @param [in] valueToMatch The value to match.
			 * @param [in] comparisonType The type of comparison.
			 */
			virtual void AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) = 0;

			/**
			 * Adds a near value filter to be applied next time you call RequestLobbyList().
			 *
			 * You can add multiple filters. All filters operate on lobby properties.
			 *
			 * @remark After each call to RequestLobbyList() all filters are cleared.
			 *
			 * @param [in] keyToMatch The key to match.
			 * @param [in] valueToBeCloseTo The value to be close to.
			 */
			virtual void AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) = 0;

			/**
			 * Returns GalaxyID of a retrieved lobby by index.
			 *
			 * Use this call to iterate over last retrieved lobbies, indexed from 0.
			 *
			 * @remark This method can be used only inside of ILobbyListListener::OnLobbyList().
			 *
			 * @pre In order to retrieve lobbies and get their count, you need to call
			 * RequestLobbyList() first.
			 *
			 * @param [in] index Index as an integer in the range of [0, number of lobbies fetched).
			 * @return The ID of the lobby, valid only if the index is valid.
			 */
			virtual GalaxyID GetLobbyByIndex(uint32_t index) = 0;

			/**
			 * Joins a specified existing lobby.
			 *
			 * This call is asynchronous. Responses come to the ILobbyEnteredListener.
			 *
			 * For other lobby members notifications come to the ILobbyMemberStateListener.
			 *
			 * @param [in] lobbyID The ID of the lobby to join.
			 */
			virtual void JoinLobby(GalaxyID lobbyID) = 0;

			/**
			 * Leaves a specified lobby.
			 *
			 * ILobbyLeftListener will be called when lobby is left.
			 * For other lobby members notifications come to the ILobbyMemberStateListener.
			 *
			 * Lobby data and lobby messages will not be reachable for lobby that we left.
			 *
			 * @param [in] lobbyID The ID of the lobby to leave.
			 */
			virtual void LeaveLobby(GalaxyID lobbyID) = 0;

			/**
			 * Sets the maximum number of users that can be in a specified lobby.
			 *
			 * @param [in] lobbyID The ID of the lobby to check.
			 * @param [in] maxNumLobbyMembers The maximum number of members allowed for the lobby with the limit of 250 members.
			 * @return true if the request was scheduled for sending, false otherwise.
			 */
			virtual bool SetMaxNumLobbyMembers(GalaxyID lobbyID, uint32_t maxNumLobbyMembers) = 0;

			/**
			 * Returns the maximum number of users that can be in a specified lobby.
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby to check.
			 * @return The maximum number of members allowed for the lobby.
			 */
			virtual uint32_t GetMaxNumLobbyMembers(GalaxyID lobbyID) = 0;

			/**
			 * Returns the number of users in a specified lobby.
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby to check.
			 * @return The number of members of the lobby.
			 */
			virtual uint32_t GetNumLobbyMembers(GalaxyID lobbyID) = 0;

			/**
			 * Returns the GalaxyID of a user in a specified lobby.
			 *
			 * @pre The user must be in the lobby in order to retrieve the lobby members.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] index Index as an integer in the range of [0, number of lobby members).
			 * @return The ID of the lobby member, valid only if the index is valid.
			 */
			virtual GalaxyID GetLobbyMemberByIndex(GalaxyID lobbyID, uint32_t index) = 0;

			/**
			 * Sets the type of a specified lobby.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] lobbyType The type of the lobby.
			 * @return true if the request was scheduled for sending, false otherwise.
			 */
			virtual bool SetLobbyType(GalaxyID lobbyID, LobbyType lobbyType) = 0;

			/**
			 * Returns the type of a specified lobby.
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @return lobbyType The type of the lobby.
			 */
			virtual LobbyType GetLobbyType(GalaxyID lobbyID) = 0;

			/**
			 * Sets if a specified lobby is joinable.
			 *
			 * @remark When a lobby is not joinable, no user can join in even if there are still
			 * some empty slots for lobby members. The lobby is also hidden from matchmaking.
			 *
			 * @remark Newly created lobbies are joinable by default. Close a lobby by making it
			 * not joinable e.g. when the game has started and no new lobby members are allowed.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] joinable Is the lobby joinable.
			 * @return true if the request was scheduled for sending, false otherwise.
			 */
			virtual bool SetLobbyJoinable(GalaxyID lobbyID, bool joinable) = 0;

			/**
			 * Checks if a specified lobby is joinable.
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @return If the lobby is joinable.
			 */
			virtual bool IsLobbyJoinable(GalaxyID lobbyID) = 0;

			/**
			 * Refreshes info about a specified lobby.
			 *
			 * This is needed only for the lobbies that the user is not currently in,
			 * since for entered lobbies any info is updated automatically.
			 *
			 * This call is asynchronous. Responses come to the ILobbyDataListener.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @return true if the request was scheduled for sending, false otherwise.
			 */
			virtual bool RequestLobbyData(GalaxyID lobbyID) = 0;

			/**
			 * Returns an entry from the properties of a specified lobby.
			 *
			 * It returns an empty string if there is no such property of the lobby, or
			 * if the ID of the lobby is invalid.
			 *
			 * @remark This call is not thread-safe as opposed to GetLobbyDataCopy().
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] key The name of the property of the lobby.
			 * @return The value of the property, or an empty string if failed.
			 */
			virtual const char* GetLobbyData(GalaxyID lobbyID, const char* key) = 0;

			/**
			 * Copies an entry from the properties of a specified lobby.
			 *
			 * It copies an empty string if there is no such property of the lobby, or
			 * if the ID of the lobby is invalid.
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] key The name of the property of the lobby.
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 */
			virtual void GetLobbyDataCopy(GalaxyID lobbyID, const char* key, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Creates or updates an entry in the properties of a specified lobby.
			 *
			 * The properties can be used for matchmaking or broadcasting any lobby data
			 * (e.g. the name of the lobby) to other Galaxy Peers.
			 *
			 * The properties are assigned to the lobby and available for matchmaking.
			 * Each user that is a member of the lobby will receive a notification when
			 * the properties of the lobby are changed. The notifications come to ILobbyDataListener.
			 *
			 * Any user that joins the lobby will be able to read the data.
			 *
			 * @remark To clear a property, set it to an empty string.
			 *
			 * @pre Only the owner of the lobby can edit its properties.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] key The name of the property of the lobby with the limit of 1023 bytes.
			 * @param [in] value The value of the property to set with the limit of 4095 bytes.
			 * @return true if the request was scheduled for sending, false otherwise.
			 */
			virtual bool SetLobbyData(GalaxyID lobbyID, const char* key, const char* value) = 0;

			/**
			 * Returns the number of entries in the properties of a specified lobby.
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling
			 * RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @return The number of entries, or 0 if failed.
			 */
			virtual uint32_t GetLobbyDataCount(GalaxyID lobbyID) = 0;

			/**
			 * Returns a property of a specified lobby by index.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] index Index as an integer in the range of [0, number of entries).
			 * @param [in, out] key The name of the property of the lobby.
			 * @param [in] keyLength The length of the name of the property of the lobby.
			 * @param [in, out] value The value of the property of the lobby.
			 * @param [in] valueLength The length of the value of the property of the lobby.
			 * @return true if succeeded, false when there is no such property.
			 */
			virtual bool GetLobbyDataByIndex(GalaxyID lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) = 0;

			/**
			 * Clears a property of a specified lobby by its name.
			 *
			 * This is the same as calling SetLobbyData() and providing an empty string
			 * as the value of the property that is to be altered.
			 *
			 * Each user that is a member of the lobby will receive a notification when
			 * the properties of the lobby are changed. The notifications come to ILobbyDataListener.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] key The name of the property of the lobby.
			 * @return true if the request was scheduled for sending, false otherwise.
			 */
			virtual bool DeleteLobbyData(GalaxyID lobbyID, const char* key) = 0;

			/**
			 * Returns an entry from the properties of a specified member
			 * of a specified lobby.
			 *
			 * It returns an empty string if there is no such property of the member of
			 * the lobby, or if any of the specified IDs are invalid (including false
			 * membership).
			 *
			 * @remark This call is not thread-safe as opposed to GetLobbyMemberDataCopy().
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] memberID The ID of the lobby member.
			 * @param [in] key The name of the property of the lobby member.
			 * @return The value of the property, or an empty string if failed.
			 */
			virtual const char* GetLobbyMemberData(GalaxyID lobbyID, GalaxyID memberID, const char* key) = 0;

			/**
			 * Copies an entry from the properties of a specified member
			 * of a specified lobby.
			 *
			 * It copies an empty string if there is no such property of the member of
			 * the lobby, or if any of the specified IDs are invalid (including false
			 * membership).
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] memberID The ID of the lobby member.
			 * @param [in] key The name of the property of the lobby member.
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 */
			virtual void GetLobbyMemberDataCopy(GalaxyID lobbyID, GalaxyID memberID, const char* key, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Creates or updates an entry in the user's properties (as a lobby member)
			 * in a specified lobby.
			 *
			 * The properties can be used for broadcasting any data as the lobby member data
			 * (e.g. the name of the user in the lobby) to other lobby members.
			 *
			 * The properties are assigned to the user as a lobby member in the lobby.
			 * Each user that is a member of the lobby will receive a notification when
			 * the lobby member properties are changed. The notifications come to ILobbyDataListener.
			 *
			 * Any user that joins the lobby will be able to read the data.
			 *
			 * @remark To clear a property, set it to an empty string.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] key The name of the property of the lobby member with the limit of 1023 bytes.
			 * @param [in] value The value of the property to set with the limit of 4095 bytes.
			 */
			virtual void SetLobbyMemberData(GalaxyID lobbyID, const char* key, const char* value) = 0;

			/**
			 * Returns the number of entries in the properties of a specified member
			 * of a specified lobby.
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] memberID The ID of the lobby member.
			 * @return The number of entries, or 0 if failed.
			 */
			virtual uint32_t GetLobbyMemberDataCount(GalaxyID lobbyID, GalaxyID memberID) = 0;

			/**
			 * Returns a property of a specified lobby member by index.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] memberID The ID of the lobby member.
			 * @param [in] index Index as an integer in the range of [0, number of entries).
			 * @param [in, out] key The name of the property of the lobby member.
			 * @param [in] keyLength The length of the name of the property of the lobby member.
			 * @param [in, out] value The value of the property of the lobby member.
			 * @param [in] valueLength The length of the value of the property of the lobby member.
			 * @return true if succeeded, false when there is no such property.
			 */
			virtual bool GetLobbyMemberDataByIndex(GalaxyID lobbyID, GalaxyID memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) = 0;

			/**
			 * Clears a property of a specified lobby member by its name.
			 *
			 * This is the same as calling SetLobbyMemberData() and providing an empty
			 * string as the value of the property that is to be altered.
			 *
			 * Each user that is a member of the lobby will receive a notification when
			 * the lobby member properties are changed. The notifications come to ILobbyDataListener.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] key The name of the property of the lobby member.
			 */
			virtual void DeleteLobbyMemberData(GalaxyID lobbyID, const char* key) = 0;

			/**
			 * Returns the owner of a specified lobby.
			 *
			 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @return The ID of the lobby member who is also its owner, valid only when called by a member.
			 */
			virtual GalaxyID GetLobbyOwner(GalaxyID lobbyID) = 0;

			/**
			 * Sends a message to all lobby members, including the sender.
			 *
			 * For all the lobby members there comes a notification to the
			 * ILobbyMessageListener. Since that moment it is possible to retrieve the
			 * message by ID using GetLobbyMessage().
			 *
			 * @pre The user needs to be in the lobby in order to send a message to its members.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] data The data to send.
			 * @param [in] dataSize The length of the data.
			 * @return true if the message was scheduled for sending, false otherwise.
			 */
			virtual bool SendLobbyMessage(GalaxyID lobbyID, const void* data, uint32_t dataSize) = 0;

			/**
			 * Receives a specified message from one of the members of a specified lobby.
			 *
			 * @param [in] lobbyID The ID of the lobby.
			 * @param [in] messageID The ID of the message.
			 * @param [out] senderID The ID of the sender.
			 * @param [in, out] msg The buffer to pass the data to.
			 * @param [in] msgLength The size of the buffer.
			 * @return The number of bytes written to the buffer.
			 */
			virtual uint32_t GetLobbyMessage(GalaxyID lobbyID, uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) = 0;
		};

		/** @} */
	}
}

#endif
