#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER

#include "TestCaseClientDetails.hxx"

class SentFriendInvitationListRetrieveListenerImplGlobal : public galaxy::api::GlobalSentFriendInvitationListRetrieveListener
{
public:
	using on_sent_friend_invitation_list_retrieve_success_func_t = std::function<void()>;
	using on_sent_friend_invitation_list_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_sent_friend_invitation_list_retrieve_success_func_t on_sent_friend_invitation_list_retrieve_success;
	on_sent_friend_invitation_list_retrieve_failure_func_t on_sent_friend_invitation_list_retrieve_failure;

public:
	SentFriendInvitationListRetrieveListenerImplGlobal(
		on_sent_friend_invitation_list_retrieve_success_func_t on_sent_friend_invitation_list_retrieve_success = nullptr,
		on_sent_friend_invitation_list_retrieve_failure_func_t on_sent_friend_invitation_list_retrieve_failure = nullptr) :
		on_sent_friend_invitation_list_retrieve_success{ on_sent_friend_invitation_list_retrieve_success },
		on_sent_friend_invitation_list_retrieve_failure{ on_sent_friend_invitation_list_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~SentFriendInvitationListRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnSentFriendInvitationListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_sent_friend_invitation_list_retrieve_success != nullptr) {
			on_sent_friend_invitation_list_retrieve_success();
		}
	}

	virtual void OnSentFriendInvitationListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_sent_friend_invitation_list_retrieve_failure != nullptr) {
			on_sent_friend_invitation_list_retrieve_failure(failureReason);
		}
	}
};

class SentFriendInvitationListRetrieveListenerImplLocal : public galaxy::api::ISentFriendInvitationListRetrieveListener
{
public:
	using on_sent_friend_invitation_list_retrieve_success_func_t = std::function<void()>;
	using on_sent_friend_invitation_list_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_sent_friend_invitation_list_retrieve_success_func_t on_sent_friend_invitation_list_retrieve_success;
	on_sent_friend_invitation_list_retrieve_failure_func_t on_sent_friend_invitation_list_retrieve_failure;

public:
	SentFriendInvitationListRetrieveListenerImplLocal(
		on_sent_friend_invitation_list_retrieve_success_func_t on_sent_friend_invitation_list_retrieve_success = nullptr,
		on_sent_friend_invitation_list_retrieve_failure_func_t on_sent_friend_invitation_list_retrieve_failure = nullptr) :
		on_sent_friend_invitation_list_retrieve_success{ on_sent_friend_invitation_list_retrieve_success },
		on_sent_friend_invitation_list_retrieve_failure{ on_sent_friend_invitation_list_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~SentFriendInvitationListRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnSentFriendInvitationListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_sent_friend_invitation_list_retrieve_success != nullptr) {
			on_sent_friend_invitation_list_retrieve_success();
		}
	}

	virtual void OnSentFriendInvitationListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_sent_friend_invitation_list_retrieve_failure != nullptr) {
			on_sent_friend_invitation_list_retrieve_failure(failureReason);
		}
	}
};

#endif
