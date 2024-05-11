#include "FriendsListener.hxx"
#include "ProxifySingleShotListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IFRIENDS;
	}

	void PersonaDataChangedListener::OnPersonaDataChanged(GalaxyID userID, uint32_t personaStateChange)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("personaStateChange: {}", personaStateChange));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnPersonaDataChanged(userID, personaStateChange));
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	void UserInformationRetrieveListener::OnUserInformationRetrieveSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserInformationRetrieveSuccess(userID));
	}

	void UserInformationRetrieveListener::OnUserInformationRetrieveFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserInformationRetrieveFailure(userID, failureReason));
	}
#endif

	void FriendListListener::OnFriendListRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendListRetrieveSuccess());
	}

	void FriendListListener::OnFriendListRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendListRetrieveFailure(failureReason));
	}

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3
	void FriendInvitationSendListener::OnFriendInvitationSendSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendInvitationSendSuccess(userID));
	}

	void FriendInvitationSendListener::OnFriendInvitationSendFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendInvitationSendFailure(userID, failureReason));
	}

	void FriendInvitationListRetrieveListener::OnFriendInvitationListRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendInvitationListRetrieveSuccess());
	}

	void FriendInvitationListRetrieveListener::OnFriendInvitationListRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendInvitationListRetrieveFailure(failureReason));
	}

	void FriendInvitationListener::OnFriendInvitationReceived(GalaxyID userID, uint32_t sendTime)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("sendTime: {}", sendTime));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendInvitationReceived(userID, sendTime));
	}

	void FriendInvitationRespondToListener::OnFriendInvitationRespondToSuccess(GalaxyID userID, bool accept)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("accept: {}", accept));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendInvitationRespondToSuccess(userID, accept));
	}

	void FriendInvitationRespondToListener::OnFriendInvitationRespondToFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendInvitationRespondToFailure(userID, failureReason));
	}

	void FriendDeleteListener::OnFriendDeleteSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendDeleteSuccess(userID));
	}

	void FriendDeleteListener::OnFriendDeleteFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendDeleteFailure(userID, failureReason));
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	void SentFriendInvitationListRetrieveListener::OnSentFriendInvitationListRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnSentFriendInvitationListRetrieveSuccess());
	}

	void SentFriendInvitationListRetrieveListener::OnSentFriendInvitationListRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnSentFriendInvitationListRetrieveFailure(failureReason));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER
	void FriendAddListener::OnFriendAdded(GalaxyID userID, InvitationDirection invitationDirection)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("invitationDirection: {}", magic_enum::enum_name(invitationDirection)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnFriendAdded(userID, invitationDirection));
	}
#endif

	void RichPresenceChangeListener::OnRichPresenceChangeSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnRichPresenceChangeSuccess());
	}

	void RichPresenceChangeListener::OnRichPresenceChangeFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnRichPresenceChangeFailure(failureReason));
	}

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	void RichPresenceListener::OnRichPresenceUpdated(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnRichPresenceUpdated(userID));
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	void RichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnRichPresenceRetrieveSuccess(userID));
	}

	void RichPresenceRetrieveListener::OnRichPresenceRetrieveFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnRichPresenceRetrieveFailure(userID, failureReason));
	}
#endif

	void GameJoinRequestedListener::OnGameJoinRequested(GalaxyID userID, const char* connectionString)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnGameJoinRequested(userID, connectionString));
	}

#if GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER
	void GameInvitationReceivedListener::OnGameInvitationReceived(GalaxyID userID, const char* connectionString)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnGameInvitationReceived(userID, connectionString));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER
	void SendInvitationListener::OnInvitationSendSuccess(GalaxyID userID, const char* connectionString)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnInvitationSendSuccess(userID, connectionString));
	}

	void SendInvitationListener::OnInvitationSendFailure(GalaxyID userID, const char* connectionString, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnInvitationSendFailure(userID, connectionString, failureReason));
	}
#endif

#if GALAXY_BUILD_FEATURE_FIND_USER
	void UserFindListener::OnUserFindSuccess(const char* userSpecifier, GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("userSpecifier: {}", util::safe_fix_null_char_ptr_annotate_ret(userSpecifier)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserFindSuccess(userSpecifier, userID));
	}

	void UserFindListener::OnUserFindFailure(const char* userSpecifier, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userSpecifier: {}", util::safe_fix_null_char_ptr_annotate_ret(userSpecifier)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserFindFailure(userSpecifier, failureReason));
	}
#endif
}
