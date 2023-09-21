#pragma once

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

#include "TestCaseClientDetails.hxx"

class FriendInvitationSendListenerImplGlobal : public galaxy::api::GlobalFriendInvitationSendListener
{
public:
	using on_friend_invitation_send_success_func_t = std::function<void(GalaxyID userID)>;
	using on_friend_invitation_send_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_friend_invitation_send_success_func_t on_friend_invitation_send_success;
	on_friend_invitation_send_failure_func_t on_friend_invitation_send_failure;

public:
	FriendInvitationSendListenerImplGlobal(
		on_friend_invitation_send_success_func_t on_friend_invitation_send_success = nullptr,
		on_friend_invitation_send_failure_func_t on_friend_invitation_send_failure = nullptr) :
		on_friend_invitation_send_success{ on_friend_invitation_send_success },
		on_friend_invitation_send_failure{ on_friend_invitation_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendInvitationSendListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationSendSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_friend_invitation_send_success != nullptr) {
			on_friend_invitation_send_success(userID);
		}
	}

	virtual void OnFriendInvitationSendFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_invitation_send_failure != nullptr) {
			on_friend_invitation_send_failure(userID, failureReason);
		}
	}
};

class FriendInvitationSendListenerImplLocal : public galaxy::api::IFriendInvitationSendListener
{
public:
	using on_friend_invitation_send_success_func_t = std::function<void(GalaxyID userID)>;
	using on_friend_invitation_send_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_friend_invitation_send_success_func_t on_friend_invitation_send_success;
	on_friend_invitation_send_failure_func_t on_friend_invitation_send_failure;

public:
	FriendInvitationSendListenerImplLocal(
		on_friend_invitation_send_success_func_t on_friend_invitation_send_success = nullptr,
		on_friend_invitation_send_failure_func_t on_friend_invitation_send_failure = nullptr) :
		on_friend_invitation_send_success{ on_friend_invitation_send_success },
		on_friend_invitation_send_failure{ on_friend_invitation_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendInvitationSendListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationSendSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_friend_invitation_send_success != nullptr) {
			on_friend_invitation_send_success(userID);
		}
	}

	virtual void OnFriendInvitationSendFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_invitation_send_failure != nullptr) {
			on_friend_invitation_send_failure(userID, failureReason);
		}
	}
};
#endif