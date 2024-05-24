#ifndef GALAXY_I_FRIENDS_H
#define GALAXY_I_FRIENDS_H

/**
 * @file
 * Contains data structures and interfaces related to social activities.
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
		 * The type of avatar.
		 */
		enum AvatarType
		{
			SMALL = 0,
			SMALL_HIGH_RESOLUTION = 1,
			MEDIUM = 2,
			MEDIUM_HIGH_RESOLUTION = 3,
			LARGE = 4,
			LARGE_HIGH_RESOLUTION = 5
		};

		/**
		 * Listener for the event of changing persona data.
		 */
		class IPersonaDataChangedListener : public GalaxyTypeAwareListener<PERSONA_DATA_CHANGED>
		{
		public:

			/**
			 * Describe what's changed about a user.
			 */
			enum PersonaStateChange
			{
				PERSONA_CHANGE_NONE = 0x0000,
				PERSONA_CHANGE_NAME = 0x0001,
				PERSONA_CHANGE_AVATAR = 0x0002
			};

			/**
			 * Notification for the event of changing persona data.
			 *
			 * @param userID The ID of the user.
			 * @param personaStateChange The bit sum of the PersonaStateChange.
			 */
			virtual void OnPersonaDataChanged(GalaxyID userID, uint32_t personaStateChange) = 0;
		};

		/**
		 * Globally self-registering version of IPersonaDataChangedListener.
		 */
		typedef SelfRegisteringListener<IPersonaDataChangedListener> GlobalPersonaDataChangedListener;

		/**
		 * Listener for the event of retrieving requested list of friends.
		 */
		class IFriendListListener : public GalaxyTypeAwareListener<FRIEND_LIST_RETRIEVE>
		{
		public:

			/**
			 * Notification for the event of a success in retrieving the user's list of friends.
			 *
			 * In order to read subsequent friend IDs, call GetFriendCount() and GetFriendByIndex().
			 */
			virtual void OnFriendListRetrieveSuccess() = 0;

			/**
			 * The reason of a failure in retrieving the user's list of friends.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			 * Notification for the event of a failure in retrieving the user's list of friends.
			 *
			 * @param failureReason The cause of the failure.
			 */
			virtual void OnFriendListRetrieveFailure(FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IFriendListListener.
		 */
		typedef SelfRegisteringListener<IFriendListListener> GlobalFriendListListener;

		/**
		 * Listener for the event of rich presence modification.
		 */
		class IRichPresenceChangeListener : public GalaxyTypeAwareListener<RICH_PRESENCE_CHANGE_LISTENER>
		{
		public:

			/**
			 * Notification for the event of successful rich presence change.
			 */
			virtual void OnRichPresenceChangeSuccess() = 0;

			/**
			 * The reason of a failure in rich presence modification.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			 * Notification for the event of failure to modify rich presence.
			 */
			virtual void OnRichPresenceChangeFailure(FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IRichPresenceChangeListener.
		 */
		typedef SelfRegisteringListener<IRichPresenceChangeListener> GlobalRichPresenceChangeListener;

		/**
		 * Event of requesting a game join by user.
		 *
		 * This can be triggered by accepting a game invitation
		 * or by user's request to join a friend's game.
		 */
		class IGameJoinRequestedListener : public GalaxyTypeAwareListener<GAME_JOIN_REQUESTED_LISTENER>
		{
		public:

			/**
			 * Notification for the event of receiving a game invitation.
			 *
			 * @param userID The ID of the user who sent invitation.
			 * @param connectionString The string which contains connection info.
			 */
			virtual void OnGameJoinRequested(GalaxyID userID, const char* connectionString) = 0;
		};

		/**
		 * Globally self-registering version of IGameJoinRequestedListener.
		 */
		typedef SelfRegisteringListener<IGameJoinRequestedListener> GlobalGameJoinRequestedListener;

		/**
		 * The interface for managing social info and activities.
		 */
		class IFriends
		{
		public:

			virtual ~IFriends()
			{
			}

			/**
			 * Returns the user's nickname.
			 *
			 * @return The nickname of the user.
			 */
			virtual const char* GetPersonaName() = 0;

			/**
			 * Performs a request for information about specified user.
			 *
			 * This call is asynchronous. Responses come to the IPersonaDataChangedListener.
			 *
			 * @param userID The ID of the user.
			 */
			virtual void RequestUserInformation(GalaxyID userID) = 0;

			/**
			 * Returns the nickname of specified user.
			 *
			 * @param userID The ID of the user.
			 * @return The nickname of the user.
			 */
			virtual const char* GetFriendPersonaName(GalaxyID userID) = 0;

			/**
			 * Returns URL of the avatar of specified user.
			 *
			 * @param userID The ID of the user.
			 * @param avatarType The type of avatar.
			 * @return The URL to the avatar.
			 */
			virtual const char* GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) = 0;

			/**
			 * Performs a request for the user's list of friends.
			 *
			 * This call is asynchronous. Responses come to the IFriendListListener.
			 */
			virtual void RequestFriendList() = 0;

			/**
			 * Returns the number of retrieved friends in the user's list of friends.
			 *
			 * @return The number of retrieved friends, or 0 if failed.
			 */
			virtual uint32_t GetFriendCount() = 0;

			/**
			 * Returns the GalaxyID for a friend.
			 *
			 * @remark Retrieve the list of friends first by calling RequestFriendList().
			 * @remark Provided friendIndex have to be less than GetFriendCount().
			 *
			 * @param friendIndex The position of the friend's GalaxyID in the retrieved list of friends.
			 * @return The GalaxyID of the friend.
			 */
			virtual GalaxyID GetFriendByIndex(uint32_t friendIndex) = 0;

			/**
			 * Sets the variable value under specified name.
			 * There are two keys that can be used:
			 * - "status" - will be visible in Galaxy Client.
			 * - "connect" - should contain connection string that allows to join a multiplayer
			 * game when passed to game as a parameter.
			 * Passing NULL value removes the entry.
			 *
			 * This call in asynchronous. Responses come to the IRichPresenceChangeListener.
			 *
			 * @param key The name of the property of the user's rich presence.
			 * @param value The value of the property to set.
			 */
			virtual void SetRichPresence(const char* key, const char* value) = 0;

			/**
			 * Removes the variable value under specified name.
			 *
			 * If the variable doesn't exist method call has no effect.
			 *
			 * This call in asynchronous. Responses come to the IRichPresenceChangeListener.
			 *
			 * @param key The name of the variable to be removed.
			 */
			virtual void DeleteRichPresence(const char* key) = 0;

			/**
			 * Removes all rich presence data for the user.
			 *
			 * This call in asynchronous. Responses come to the IRichPresenceChangeListener.
			 */
			virtual void ClearRichPresence() = 0;

			/**
			 * Shows game invitation dialog that allows to invite users to game.
			 *
			 * If invited user accepts the invitation, the connection string
			 * gets added to the command-line parameters for launching the game.
			 * If the game is already running, the connection string comes
			 * to the IGameJoinRequestedListener instead.
			 *
			 * @param connectionString The string which contains connection info.
			 **/
			virtual void ShowOverlayInviteDialog(const char* connectionString) = 0;
		};

		/** @} */
	}
}

#endif
