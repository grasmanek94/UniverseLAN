#pragma once

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

#include "TestCaseClientDetails.hxx"

class FriendInvitationRespondToListenerImplGlobal : public galaxy::api::GlobalFriendInvitationRespondToListener
{
public:
	using on_friend_invitation_respond_to_success_func_t = std::function<void(GalaxyID userID, bool accept)>;
	using on_friend_invitation_respond_to_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_friend_invitation_respond_to_success_func_t on_friend_invitation_respond_to_success;
	on_friend_invitation_respond_to_failure_func_t on_friend_invitation_respond_to_failure;

public:
	FriendInvitationRespondToListenerImplGlobal(
		on_friend_invitation_respond_to_success_func_t on_friend_invitation_respond_to_success = nullptr,
		on_friend_invitation_respond_to_failure_func_t on_friend_invitation_respond_to_failure = nullptr) :
		on_friend_invitation_respond_to_success{ on_friend_invitation_respond_to_success },
		on_friend_invitation_respond_to_failure{ on_friend_invitation_respond_to_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendInvitationRespondToListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationRespondToSuccess(GalaxyID userID, bool accept) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} accept: {}",
			userID, accept
		).c_str());


		if (on_friend_invitation_respond_to_success != nullptr) {
			on_friend_invitation_respond_to_success(userID, accept);
		}
	}

	virtual void OnFriendInvitationRespondToFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_invitation_respond_to_failure != nullptr) {
			on_friend_invitation_respond_to_failure(userID, failureReason);
		}
	}
};

class FriendInvitationRespondToListenerImplLocal : public galaxy::api::IFriendInvitationRespondToListener
{
public:
	using on_friend_invitation_respond_to_success_func_t = std::function<void(GalaxyID userID, bool accept)>;
	using on_friend_invitation_respond_to_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_friend_invitation_respond_to_success_func_t on_friend_invitation_respond_to_success;
	on_friend_invitation_respond_to_failure_func_t on_friend_invitation_respond_to_failure;

public:
	FriendInvitationRespondToListenerImplLocal(
		on_friend_invitation_respond_to_success_func_t on_friend_invitation_respond_to_success = nullptr,
		on_friend_invitation_respond_to_failure_func_t on_friend_invitation_respond_to_failure = nullptr) :
		on_friend_invitation_respond_to_success{ on_friend_invitation_respond_to_success },
		on_friend_invitation_respond_to_failure{ on_friend_invitation_respond_to_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendInvitationRespondToListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationRespondToSuccess(GalaxyID userID, bool accept) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} accept: {}",
			userID, accept
		).c_str());


		if (on_friend_invitation_respond_to_success != nullptr) {
			on_friend_invitation_respond_to_success(userID, accept);
		}
	}

	virtual void OnFriendInvitationRespondToFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_invitation_respond_to_failure != nullptr) {
			on_friend_invitation_respond_to_failure(userID, failureReason);
		}
	}
};

#endif
