#pragma once

#include "TestCaseClientDetails.hxx"

class FriendListListenerImplGlobal : public galaxy::api::GlobalFriendListListener
{
public:
	using on_friend_list_retrieve_success_func_t = std::function<void()>;
	using on_friend_list_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_friend_list_retrieve_success_func_t on_friend_list_retrieve_success;
	on_friend_list_retrieve_failure_func_t on_friend_list_retrieve_failure;

public:
	FriendListListenerImplGlobal(
		on_friend_list_retrieve_success_func_t on_friend_list_retrieve_success = nullptr,
		on_friend_list_retrieve_failure_func_t on_friend_list_retrieve_failure = nullptr) :
		on_friend_list_retrieve_success{ on_friend_list_retrieve_success },
		on_friend_list_retrieve_failure{ on_friend_list_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendListListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_friend_list_retrieve_success != nullptr) {
			on_friend_list_retrieve_success();
		}
	}

	virtual void OnFriendListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_list_retrieve_failure != nullptr) {
			on_friend_list_retrieve_failure(failureReason);
		}
	}
};

class FriendListListenerImplLocal : public galaxy::api::IFriendListListener
{
public:
	using on_friend_list_retrieve_success_func_t = std::function<void()>;
	using on_friend_list_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_friend_list_retrieve_success_func_t on_friend_list_retrieve_success;
	on_friend_list_retrieve_failure_func_t on_friend_list_retrieve_failure;

public:
	FriendListListenerImplLocal(
		on_friend_list_retrieve_success_func_t on_friend_list_retrieve_success = nullptr,
		on_friend_list_retrieve_failure_func_t on_friend_list_retrieve_failure = nullptr) :
		on_friend_list_retrieve_success{ on_friend_list_retrieve_success },
		on_friend_list_retrieve_failure{ on_friend_list_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendListListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendListRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_friend_list_retrieve_success != nullptr) {
			on_friend_list_retrieve_success();
		}
	}

	virtual void OnFriendListRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_list_retrieve_failure != nullptr) {
			on_friend_list_retrieve_failure(failureReason);
		}
	}
};
