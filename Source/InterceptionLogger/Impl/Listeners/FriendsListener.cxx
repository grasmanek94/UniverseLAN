#include "FriendsListener.hxx"

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
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	void UserInformationRetrieveListener::OnUserInformationRetrieveSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void UserInformationRetrieveListener::OnUserInformationRetrieveFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}
#endif

	void FriendListListener::OnFriendListRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void FriendListListener::OnFriendListRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3
	void FriendInvitationSendListener::OnFriendInvitationSendSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void FriendInvitationSendListener::OnFriendInvitationSendFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void FriendInvitationListRetrieveListener::OnFriendInvitationListRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void FriendInvitationListRetrieveListener::OnFriendInvitationListRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void FriendInvitationListener::OnFriendInvitationReceived(GalaxyID userID, uint32_t sendTime)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("sendTime: {}", sendTime));
		}
	}

	void FriendInvitationRespondToListener::OnFriendInvitationRespondToSuccess(GalaxyID userID, bool accept)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("accept: {}", accept));
		}
	}

	void FriendInvitationRespondToListener::OnFriendInvitationRespondToFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void FriendDeleteListener::OnFriendDeleteSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void FriendDeleteListener::OnFriendDeleteFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	void SentFriendInvitationListRetrieveListener::OnSentFriendInvitationListRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void SentFriendInvitationListRetrieveListener::OnSentFriendInvitationListRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
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
	}
#endif

	void RichPresenceChangeListener::OnRichPresenceChangeSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void RichPresenceChangeListener::OnRichPresenceChangeFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	void RichPresenceListener::OnRichPresenceUpdated(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	void RichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void RichPresenceRetrieveListener::OnRichPresenceRetrieveFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}
#endif

	void GameJoinRequestedListener::OnGameJoinRequested(GalaxyID userID, const char* connectionString)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER
	void GameInvitationReceivedListener::OnGameInvitationReceived(GalaxyID userID, const char* connectionString)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
		}
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
	}

	void SendInvitationListener::OnInvitationSendFailure(GalaxyID userID, const char* connectionString, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
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
	}

	void UserFindListener::OnUserFindFailure(const char* userSpecifier, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userSpecifier: {}", util::safe_fix_null_char_ptr_annotate_ret(userSpecifier)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}
#endif

}
