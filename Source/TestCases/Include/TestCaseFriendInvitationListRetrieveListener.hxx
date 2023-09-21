#pragma once

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

#include "TestCaseClientDetails.hxx"

class FriendInvitationListRetrieveListenerImplGlobal : public galaxy::api::GlobalFriendInvitationListRetrieveListener
{
public:
	using on_friend_invitation_list_retrieve_success_func_t = std::function<void()>;
	using on_friend_invitation_list_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_friend_invitation_list_retrieve_success_func_t on_friend_invitation_list_retrieve_success;
	on_friend_invitation_list_retrieve_failure_func_t on_friend_invitation_list_retrieve_failure;

public:
	FriendInvitationListRetrieveListenerImplGlobal(
		on_friend_invitation_list_retrieve_success_func_t on_friend_invitation_list_retrieve_success = nullptr,
		on_friend_invitation_list_retrieve_failure_func_t on_friend_invitation_list_retrieve_failure = nullptr) :
		on_friend_invitation_list_retrieve_success{ on_friend_invitation_list_retrieve_success },
		on_friend_invitation_list_retrieve_failure{ on_friend_invitation_list_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendInvitationListRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_friend_invitation_list_retrieve_success != nullptr) {
			on_friend_invitation_list_retrieve_success();
		}
	}

	virtual void OnFriendInvitationListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_invitation_list_retrieve_failure != nullptr) {
			on_friend_invitation_list_retrieve_failure(failureReason);
		}
	}
};

class FriendInvitationListRetrieveListenerImplLocal : public galaxy::api::IFriendInvitationListRetrieveListener
{
public:
	using on_friend_invitation_list_retrieve_success_func_t = std::function<void()>;
	using on_friend_invitation_list_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_friend_invitation_list_retrieve_success_func_t on_friend_invitation_list_retrieve_success;
	on_friend_invitation_list_retrieve_failure_func_t on_friend_invitation_list_retrieve_failure;

public:
	FriendInvitationListRetrieveListenerImplLocal(
		on_friend_invitation_list_retrieve_success_func_t on_friend_invitation_list_retrieve_success = nullptr,
		on_friend_invitation_list_retrieve_failure_func_t on_friend_invitation_list_retrieve_failure = nullptr) :
		on_friend_invitation_list_retrieve_success{ on_friend_invitation_list_retrieve_success },
		on_friend_invitation_list_retrieve_failure{ on_friend_invitation_list_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendInvitationListRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_friend_invitation_list_retrieve_success != nullptr) {
			on_friend_invitation_list_retrieve_success();
		}
	}

	virtual void OnFriendInvitationListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_invitation_list_retrieve_failure != nullptr) {
			on_friend_invitation_list_retrieve_failure(failureReason);
		}
	}
};

#endif
