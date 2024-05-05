#pragma once

#include <IFriends.h>

namespace universelan::client {
	using namespace galaxy::api;

	class PersonaDataChangedListener : public IPersonaDataChangedListener
	{
	public:
		virtual void OnPersonaDataChanged(GalaxyID userID, uint32_t personaStateChange);
	};

	class UserInformationRetrieveListener : public IUserInformationRetrieveListener
	{
	public:
		virtual void OnUserInformationRetrieveSuccess(GalaxyID userID);
		virtual void OnUserInformationRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};

	class FriendListListener : public IFriendListListener
	{
	public:
		virtual void OnFriendListRetrieveSuccess();
		virtual void OnFriendListRetrieveFailure(FailureReason failureReason);
	};

	class FriendInvitationSendListener : public IFriendInvitationSendListener
	{
	public:
		virtual void OnFriendInvitationSendSuccess(GalaxyID userID);
		virtual void OnFriendInvitationSendFailure(GalaxyID userID, FailureReason failureReason);
	};

	class FriendInvitationListRetrieveListener : public IFriendInvitationListRetrieveListener
	{
	public:
		virtual void OnFriendInvitationListRetrieveSuccess();
		virtual void OnFriendInvitationListRetrieveFailure(FailureReason failureReason);

	};

	class SentFriendInvitationListRetrieveListener : public ISentFriendInvitationListRetrieveListener
	{
	public:
		virtual void OnSentFriendInvitationListRetrieveSuccess();
		virtual void OnSentFriendInvitationListRetrieveFailure(FailureReason failureReason);
	};

	class FriendInvitationListener : public IFriendInvitationListener
	{
	public:
		virtual void OnFriendInvitationReceived(GalaxyID userID, uint32_t sendTime);
	};

	class FriendInvitationRespondToListener : public IFriendInvitationRespondToListener
	{
	public:
		virtual void OnFriendInvitationRespondToSuccess(GalaxyID userID, bool accept);
		virtual void OnFriendInvitationRespondToFailure(GalaxyID userID, FailureReason failureReason);
	};

	class FriendAddListener : public IFriendAddListener
	{
	public:
		virtual void OnFriendAdded(GalaxyID userID, InvitationDirection invitationDirection);
	};

	class FriendDeleteListener : public IFriendDeleteListener
	{
	public:
		virtual void OnFriendDeleteSuccess(GalaxyID userID);
		virtual void OnFriendDeleteFailure(GalaxyID userID, FailureReason failureReason);
	};

	class RichPresenceChangeListener : public IRichPresenceChangeListener
	{
	public:
		virtual void OnRichPresenceChangeSuccess();
		virtual void OnRichPresenceChangeFailure(FailureReason failureReason);
	};

	class RichPresenceListener : public IRichPresenceListener
	{
	public:
		virtual void OnRichPresenceUpdated(GalaxyID userID);
	};

	class RichPresenceRetrieveListener : public IRichPresenceRetrieveListener
	{
	public:
		virtual void OnRichPresenceRetrieveSuccess(GalaxyID userID);
		virtual void OnRichPresenceRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};

	class GameJoinRequestedListener : public IGameJoinRequestedListener
	{
		virtual void OnGameJoinRequested(GalaxyID userID, const char* connectionString);
	};

	class GameInvitationReceivedListener : public IGameInvitationReceivedListener
	{
	public:
		virtual void OnGameInvitationReceived(GalaxyID userID, const char* connectionString);
	};

	class SendInvitationListener : public ISendInvitationListener
	{
	public:
		virtual void OnInvitationSendSuccess(GalaxyID userID, const char* connectionString);
		virtual void OnInvitationSendFailure(GalaxyID userID, const char* connectionString, FailureReason failureReason);
	};

	class UserFindListener : public IUserFindListener
	{
	public:
		virtual void OnUserFindSuccess(const char* userSpecifier, GalaxyID userID);
		virtual void OnUserFindFailure(const char* userSpecifier, FailureReason failureReason);
	};
}
