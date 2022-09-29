#ifndef LSFDRMFG_IMPL_FRIENDS_H
#define LSFDRMFG_IMPL_FRIENDS_H

/**
 * @file
 * Contains data structures and interfaces related to social activities.
 */

#include "ListenerRegistrar.hxx"

#include <IFriends.h>
#include <GalaxyID.h>
#include <IListenerRegistrar.h>

namespace universelan::client {
	using namespace galaxy::api;
	struct InterfaceInstances;

	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	  * The interface for managing social info and activities.
	  */
	class FriendsImpl : public IFriends
	{
	private:
		InterfaceInstances* intf;
		ListenerRegistrarImpl* listeners;

		AvatarCriteria avatar_criteria;
	public:

		FriendsImpl(InterfaceInstances* intf);
		virtual ~FriendsImpl();

		/**
		 * Returns the default avatar criteria.
		 *
		 * @return The bit sum of default AvatarType.
		 */
		virtual AvatarCriteria GetDefaultAvatarCriteria() override;

		/**
		 * Sets the default avatar criteria.
		 *
		 * @remark The avatar criteria will be used for automated downloads of user information,
		 * as well as additional criteria in case of calling RequestUserInformation().
		 *
		 * @param [in] defaultAvatarCriteria The bit sum of default AvatarType.
		 */
		virtual void SetDefaultAvatarCriteria(AvatarCriteria defaultAvatarCriteria) override;

		/**
		 * Performs a request for information about specified user.
		 *
		 * This call is asynchronous. Responses come both to the IPersonaDataChangedListener
		 * and to the IUserInformationRetrieveListener.
		 *
		 * @remark This call is performed automatically for friends (after requesting the list
		 * of friends) and fellow lobby members (after entering a lobby or getting a notification
		 * about some other user joining it), therefore in many cases there is no need for you
		 * to call it manually and all you should do is wait for the appropriate callback
		 * to come to the IPersonaDataChangedListener.
		 *
		 * @remark User avatar will be downloaded according to bit sum of avatarCriteria and
		 * defaultAvatarCriteria set by calling SetDefaultAvatarCriteria().
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] avatarCriteria The bit sum of the AvatarType.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RequestUserInformation(
			GalaxyID userID,
			AvatarCriteria avatarCriteria = AVATAR_TYPE_NONE,
			IUserInformationRetrieveListener* const listener = NULL) override;

		/**
		 * Checks if the information of specified user is available.
		 *
		 * @pre Retrieve the information by calling RequestUserInformation().
		 *
		 * @param [in] userID The ID of the user.
		 * @return true if the information of the user is available, false otherwise.
		 */
		virtual bool IsUserInformationAvailable(GalaxyID userID) override;

		/**
		 * Returns the user's nickname.
		 *
		 * @remark This call is not thread-safe as opposed to GetPersonaNameCopy().
		 *
		 * @return The nickname of the user.
		 */
		virtual const char* GetPersonaName() override;

		/**
		 * Copies the user's nickname to a buffer.
		 *
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetPersonaNameCopy(char* buffer, uint32_t bufferLength) override;

		/**
		 * Returns the user's state.
		 *
		 * @return The state of the user.
		 */
		virtual PersonaState GetPersonaState() override;

		/**
		 * Returns the nickname of a specified user.
		 *
		 * @remark This call is not thread-safe as opposed to GetFriendPersonaNameCopy().
		 *
		 * @pre You might need to retrieve the data first by calling RequestUserInformation().
		 *
		 * @param [in] userID The ID of the user.
		 * @return The nickname of the user.
		 */
		virtual const char* GetFriendPersonaName(GalaxyID userID) override;

		/**
		 * Copies the nickname of a specified user.
		 *
		 * @pre You might need to retrieve the data first by calling RequestUserInformation().
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetFriendPersonaNameCopy(GalaxyID userID, char* buffer, uint32_t bufferLength) override;

		/**
		 * Returns the state of a specified user.
		 *
		 * @pre You might need to retrieve the data first by calling RequestUserInformation().
		 *
		 * @param [in] userID The ID of the user.
		 * @return The state of the user.
		 */
		virtual PersonaState GetFriendPersonaState(GalaxyID userID)override;

		/**
		 * Returns the URL of the avatar of a specified user.
		 *
		 * @remark This call is not thread-safe as opposed to GetFriendAvatarUrlCopy().
		 *
		 * @pre You might need to retrieve the data first by calling RequestUserInformation().
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] avatarType The type of avatar.
		 * @return The URL of the avatar.
		 */
		virtual const char* GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) override;

		/**
		 * Copies URL of the avatar of a specified user.
		 *
		 * @pre You might need to retrieve the data first by calling RequestUserInformation().
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] avatarType The type of avatar.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetFriendAvatarUrlCopy(GalaxyID userID, AvatarType avatarType, char* buffer, uint32_t bufferLength) override;

		/**
		 * Returns the ID of the avatar of a specified user.
		 *
		 * @pre Retrieve the avatar image first by calling RequestUserInformation()
		 * with appropriate avatar criteria.
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] avatarType The type of avatar.
		 * @return The ID of the avatar image.
		 */
		virtual uint32_t GetFriendAvatarImageID(GalaxyID userID, AvatarType avatarType) override;

		/**
		 * Copies the avatar of a specified user.
		 *
		 * @pre Retrieve the avatar image first by calling RequestUserInformation()
		 * with appropriate avatar criteria.
		 *
		 * @pre The size of the output buffer should be 4 * height * width * sizeof(char).
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] avatarType The type of avatar.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetFriendAvatarImageRGBA(GalaxyID userID, AvatarType avatarType, void* buffer, uint32_t bufferLength) override;

		/**
		 * Checks if a specified avatar image is available.
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] avatarType The type of avatar.
		 * @return true if the specified avatar image is available, false otherwise.
		 */
		virtual bool IsFriendAvatarImageRGBAAvailable(GalaxyID userID, AvatarType avatarType) override;

		/**
		 * Performs a request for the user's list of friends.
		 *
		 * This call is asynchronous. Responses come to the IFriendListListener.
		 *
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RequestFriendList(IFriendListListener* const listener = NULL) override;

		/**
		 * Checks if a specified user is a friend.
		 *
		 * @pre Retrieve the list of friends first by calling RequestFriendList().
		 *
		 * @param [in] userID The ID of the user.
		 * @return true if the specified user is a friend, false otherwise.
		 */
		virtual bool IsFriend(GalaxyID userID) override;

		/**
		 * Returns the number of retrieved friends in the user's list of friends.
		 *
		 * @pre Retrieve the list of friends first by calling RequestFriendList().
		 *
		 * @return The number of retrieved friends, or 0 if failed.
		 */
		virtual uint32_t GetFriendCount() override;

		/**
		 * Returns the GalaxyID for a friend.
		 *
		 * @pre Retrieve the list of friends first by calling RequestFriendList().
		 *
		 * @param [in] index Index as an integer in the range of [0, number of friends).
		 * @return The GalaxyID of the friend.
		 */
		virtual GalaxyID GetFriendByIndex(uint32_t index) override;

		/**
		 * Sends a friend invitation.
		 *
		 * This call is asynchronous. Responses come to the IFriendInvitationSendListener.
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SendFriendInvitation(GalaxyID userID, IFriendInvitationSendListener* const listener = NULL) override;

		/**
		 * Performs a request for the user's list of incoming friend invitations.
		 *
		 * This call is asynchronous. Responses come to the IFriendInvitationListRetrieveListener.
		 *
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RequestFriendInvitationList(IFriendInvitationListRetrieveListener* const listener = NULL) override;

		/**
		 * Performs a request for the user's list of outgoing friend invitations.
		 *
		 * This call is asynchronous. Responses come to the ISentFriendInvitationListRetrieveListener.
		 *
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RequestSentFriendInvitationList(ISentFriendInvitationListRetrieveListener* const listener = NULL) override;

		/**
		 * Returns the number of retrieved friend invitations.
		 *
		 * @remark This function can be used only in IFriendInvitationListRetrieveListener callback.
		 *
		 * @return The number of retrieved friend invitations, or 0 if failed.
		 */
		virtual uint32_t GetFriendInvitationCount() override;

		/**
		 * Reads the details of the friend invitation.
		 *
		 * @remark This function can be used only in IFriendInvitationListRetrieveListener callback.
		 *
		 * @param [in] index Index as an integer in the range of [0, number of friend invitations).
		 * @param [out] userID The ID of the user who sent the invitation.
		 * @param [out] sendTime The time at which the friend invitation was sent.
		 */
		virtual void GetFriendInvitationByIndex(uint32_t index, GalaxyID& userID, uint32_t& sendTime) override;

		/**
		 * Responds to the friend invitation.
		 *
		 * This call is asynchronous. Responses come to the IFriendInvitationRespondToListener.
		 *
		 * @param [in] userID The ID of the user who sent the friend invitation.
		 * @param [in] accept True when accepting the invitation, false when declining.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RespondToFriendInvitation(GalaxyID userID, bool accept, IFriendInvitationRespondToListener* const listener = NULL) override;

		/**
		 * Removes a user from the friend list.
		 *
		 * This call in asynchronous. Responses come to the IFriendDeleteListener.
		 *
		 * @param [in] userID The ID of the user to be removed from the friend list.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void DeleteFriend(GalaxyID userID, IFriendDeleteListener* const listener = NULL) override;

		/**
		 * Sets the variable value under a specified name.
		 *
		 * There are three keys that can be used:
		 * - "status" - The description visible in Galaxy Client with the limit of 3000 bytes.
		 * - "metadata" - The metadata that describes the status to other instances of the game with the limit of 2048 bytes.
		 * - "connect" - The string which contains connection info with the limit of 4095 bytes.
		 *   It can be regarded as a passive version of IFriends::SendInvitation() because
		 *   it allows friends that notice the rich presence to join a multiplayer game.
		 *
		 * User must be signed in through Galaxy.
		 *
		 * Passing NULL value removes the entry.
		 *
		 * This call in asynchronous. Responses come to the IRichPresenceChangeListener.
		 *
		 * @param [in] key The name of the property of the user's rich presence.
		 * @param [in] value The value of the property to set.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SetRichPresence(const char* key, const char* value, IRichPresenceChangeListener* const listener = NULL) override;

		/**
		 * Removes the variable value under a specified name.
		 *
		 * If the variable doesn't exist method call has no effect.
		 *
		 * This call in asynchronous. Responses come to the IRichPresenceChangeListener.
		 *
		 * @param [in] key The name of the variable to be removed.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void DeleteRichPresence(const char* key, IRichPresenceChangeListener* const listener = NULL) override;

		/**
		 * Removes all rich presence data for the user.
		 *
		 * This call in asynchronous. Responses come to the IRichPresenceChangeListener.
		 *
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void ClearRichPresence(IRichPresenceChangeListener* const listener = NULL) override;

		/**
		 * Performs a request for the user's rich presence.
		 *
		 * This call is asynchronous. Responses come both to the IRichPresenceListener
		 * and IRichPresenceRetrieveListener.
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RequestRichPresence(GalaxyID userID = GalaxyID(), IRichPresenceRetrieveListener* const listener = NULL) override;

		/**
		 * Returns the rich presence of a specified user.
		 *
		 * @remark This call is not thread-safe as opposed to GetRichPresenceCopy().
		 *
		 * @pre Retrieve the rich presence first by calling RequestRichPresence().
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] key The name of the property of the user's rich presence.
		 * @return The rich presence of the user.
		 */
		virtual const char* GetRichPresence(const char* key, GalaxyID userID = GalaxyID()) override;

		/**
		 * Copies the rich presence of a specified user to a buffer.
		 *
		 * @pre Retrieve the rich presence first by calling RequestRichPresence().
		 *
		 * @param [in] key The name of the property of the user's rich presence.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 * @param [in] userID The ID of the user.
		 */
		virtual void GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID = GalaxyID()) override;

		/**
		 * Returns the number of retrieved properties in user's rich presence.
		 *
		 * @param [in] userID The ID of the user.
		 * @return The number of retrieved keys, or 0 if failed.
		 */
		virtual uint32_t GetRichPresenceCount(GalaxyID userID = GalaxyID()) override;

		/**
		 * Returns a property from the rich presence storage by index.
		 *
		 * @pre Retrieve the rich presence first by calling RequestRichPresence().
		 *
		 * @param [in] index Index as an integer in the range of [0, number of entries).
		 * @param [in, out] key The name of the property of the rich presence storage.
		 * @param [in] keyLength The length of the name of the property of the rich presence storage.
		 * @param [in, out] value The value of the property of the rich presence storage.
		 * @param [in] valueLength The length of the value of the property of the rich presence storage.
		 * @param [in] userID The ID of the user.
		 */
		virtual void GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID = GalaxyID()) override;

		/**
		 * Shows game invitation dialog that allows to invite users to game.
		 *
		 * If invited user accepts the invitation, the connection string
		 * gets added to the command-line parameters for launching the game.
		 * If the game is already running, the connection string comes to the IGameInvitationReceivedListener,
		 * or to the IGameJoinRequestedListener if accepted by the user on the overlay.
		 *
		 * @pre For this call to work, the overlay needs to be initialized first.
		 * To check whether the overlay is initialized, call IUtils::GetOverlayState().
		 *
		 * @param [in] connectionString The string which contains connection info with the limit of 4095 bytes.
		 */
		virtual void ShowOverlayInviteDialog(const char* connectionString) override;

		/**
		 * Sends a game invitation without using the overlay.
		 *
		 * This call is asynchronous. Responses come to the ISendInvitationListener.
		 *
		 * If invited user accepts the invitation, the connection string
		 * gets added to the command-line parameters for launching the game.
		 * If the game is already running, the connection string comes to the IGameInvitationReceivedListener,
		 * or to the IGameJoinRequestedListener if accepted by the user on the overlay.
		 *
		 * @param [in] userID The ID of the user.
		 * @param [in] connectionString The string which contains connection info with the limit of 4095 bytes.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SendInvitation(GalaxyID userID, const char* connectionString, ISendInvitationListener* const listener = NULL) override;

		/**
		 * Finds a specified user.
		 *
		 * This call is asynchronous. Responses come to the IUserFindListener.
		 *
		 * Searches for the user given either a username or an email address.
		 * Only exact match will be returned.
		 *
		 * @param [in] userSpecifier The specifier of the user.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void FindUser(const char* userSpecifier, IUserFindListener* const listener = NULL) override;

		/**
		 * Checks if a specified user is playing the same game.
		 *
		 * @pre Retrieve the rich presence first by calling RequestRichPresence().
		 *
		 * @param [in] userID The ID of the user.
		 * @return true if the specified user is playing the same game, false otherwise.
		 */
		virtual bool IsUserInTheSameGame(GalaxyID userID) const override;
	};

	/** @} */
}

#endif
