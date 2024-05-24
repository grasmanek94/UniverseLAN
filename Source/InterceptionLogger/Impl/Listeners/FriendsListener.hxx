#pragma once

#include "ProxifySingleShotListener.hxx"

#include <IFriends.h>

namespace universelan::client {
	using namespace galaxy::api;

#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED
	class PersonaDataChangedListener : public IPersonaDataChangedListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(PersonaDataChangedListener, IPersonaDataChangedListener);

	public:
		virtual void OnPersonaDataChanged(GalaxyID userID, uint32_t personaStateChange);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IFRIENDLISTLISTENER
	class FriendListListener : public IFriendListListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(FriendListListener, IFriendListListener);

	public:
		virtual void OnFriendListRetrieveSuccess();
		virtual void OnFriendListRetrieveFailure(FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IRICHPRECENSECHANGELISTENER
	class RichPresenceChangeListener : public IRichPresenceChangeListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(RichPresenceChangeListener, IRichPresenceChangeListener);

	public:
		virtual void OnRichPresenceChangeSuccess();
		virtual void OnRichPresenceChangeFailure(FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	class RichPresenceListener : public IRichPresenceListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(RichPresenceListener, IRichPresenceListener);

	public:
		virtual void OnRichPresenceUpdated(GalaxyID userID);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER
	class GameJoinRequestedListener : public IGameJoinRequestedListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(GameJoinRequestedListener, IGameJoinRequestedListener);

	public:
		virtual void OnGameJoinRequested(GalaxyID userID, const char* connectionString);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER
	class GameInvitationReceivedListener : public IGameInvitationReceivedListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(GameInvitationReceivedListener, IGameInvitationReceivedListener);

	public:
		virtual void OnGameInvitationReceived(GalaxyID userID, const char* connectionString);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER
	class SendInvitationListener : public ISendInvitationListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(SendInvitationListener, ISendInvitationListener);

	public:
		virtual void OnInvitationSendSuccess(GalaxyID userID, const char* connectionString);
		virtual void OnInvitationSendFailure(GalaxyID userID, const char* connectionString, FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	class UserInformationRetrieveListener : public IUserInformationRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(UserInformationRetrieveListener, IUserInformationRetrieveListener);

	public:
		virtual void OnUserInformationRetrieveSuccess(GalaxyID userID);
		virtual void OnUserInformationRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3
	class FriendInvitationSendListener : public IFriendInvitationSendListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(FriendInvitationSendListener, IFriendInvitationSendListener);

	public:
		virtual void OnFriendInvitationSendSuccess(GalaxyID userID);
		virtual void OnFriendInvitationSendFailure(GalaxyID userID, FailureReason failureReason);
	};

	class FriendInvitationListRetrieveListener : public IFriendInvitationListRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(FriendInvitationListRetrieveListener, IFriendInvitationListRetrieveListener);

	public:
		virtual void OnFriendInvitationListRetrieveSuccess();
		virtual void OnFriendInvitationListRetrieveFailure(FailureReason failureReason);

	};

	class FriendInvitationListener : public IFriendInvitationListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(FriendInvitationListener, IFriendInvitationListener);

	public:
		virtual void OnFriendInvitationReceived(GalaxyID userID, uint32_t sendTime);
	};

	class FriendInvitationRespondToListener : public IFriendInvitationRespondToListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(FriendInvitationRespondToListener, IFriendInvitationRespondToListener);

	public:
		virtual void OnFriendInvitationRespondToSuccess(GalaxyID userID, bool accept);
		virtual void OnFriendInvitationRespondToFailure(GalaxyID userID, FailureReason failureReason);
	};

	class FriendDeleteListener : public IFriendDeleteListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(FriendDeleteListener, IFriendDeleteListener);

	public:
		virtual void OnFriendDeleteSuccess(GalaxyID userID);
		virtual void OnFriendDeleteFailure(GalaxyID userID, FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	class SentFriendInvitationListRetrieveListener : public ISentFriendInvitationListRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(SentFriendInvitationListRetrieveListener, ISentFriendInvitationListRetrieveListener);

	public:
		virtual void OnSentFriendInvitationListRetrieveSuccess();
		virtual void OnSentFriendInvitationListRetrieveFailure(FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER
	class FriendAddListener : public IFriendAddListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(FriendAddListener, IFriendAddListener);

	public:
		virtual void OnFriendAdded(GalaxyID userID, InvitationDirection invitationDirection);
	};
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	class RichPresenceRetrieveListener : public IRichPresenceRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(RichPresenceRetrieveListener, IRichPresenceRetrieveListener);

	public:
		virtual void OnRichPresenceRetrieveSuccess(GalaxyID userID);
		virtual void OnRichPresenceRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_FIND_USER
	class UserFindListener : public IUserFindListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(UserFindListener, IUserFindListener);

	public:
		virtual void OnUserFindSuccess(const char* userSpecifier, GalaxyID userID);
		virtual void OnUserFindFailure(const char* userSpecifier, FailureReason failureReason);
	};
#endif
}
