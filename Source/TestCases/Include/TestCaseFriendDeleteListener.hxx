#pragma once

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

#include "TestCaseClientDetails.hxx"

class FriendDeleteListenerImplGlobal : public galaxy::api::GlobalFriendDeleteListener
{
public:
	using on_friend_delete_success_func_t = std::function<void(GalaxyID userID)>;
	using on_friend_delete_failure_func_t = std::function<void(GalaxyID, FailureReason)>;

private:
	on_friend_delete_success_func_t on_friend_delete_success;
	on_friend_delete_failure_func_t on_friend_delete_failure;

public:
	FriendDeleteListenerImplGlobal(
		on_friend_delete_success_func_t on_friend_delete_success = nullptr,
		on_friend_delete_failure_func_t on_friend_delete_failure = nullptr) :
		on_friend_delete_success{ on_friend_delete_success },
		on_friend_delete_failure{ on_friend_delete_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendDeleteListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendDeleteSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_friend_delete_success != nullptr) {
			on_friend_delete_success(userID);
		}
	}

	virtual void OnFriendDeleteFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_delete_failure != nullptr) {
			on_friend_delete_failure(userID, failureReason);
		}
	}
};

class FriendDeleteListenerImplLocal: public galaxy::api::IFriendDeleteListener
{
public:
	using on_friend_delete_success_func_t = std::function<void(GalaxyID userID)>;
	using on_friend_delete_failure_func_t = std::function<void(GalaxyID, FailureReason)>;

private:
	on_friend_delete_success_func_t on_friend_delete_success;
	on_friend_delete_failure_func_t on_friend_delete_failure;

public:
	FriendDeleteListenerImplLocal(
		on_friend_delete_success_func_t on_friend_delete_success = nullptr,
		on_friend_delete_failure_func_t on_friend_delete_failure = nullptr) :
		on_friend_delete_success{ on_friend_delete_success },
		on_friend_delete_failure{ on_friend_delete_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendDeleteListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendDeleteSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_friend_delete_success != nullptr) {
			on_friend_delete_success(userID);
		}
	}

	virtual void OnFriendDeleteFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_friend_delete_failure != nullptr) {
			on_friend_delete_failure(userID, failureReason);
		}
	}
};

#endif
