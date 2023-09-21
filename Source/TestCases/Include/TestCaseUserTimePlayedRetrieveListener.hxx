#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER

#include "TestCaseClientDetails.hxx"

class UserTimePlayedRetrieveListenerImplGlobal : public galaxy::api::GlobalUserTimePlayedRetrieveListener
{
public:
	using on_user_time_played_retrieve_success_func_t = std::function<void(GalaxyID)>;
	using on_user_time_played_retrieve_failure_func_t = std::function<void(GalaxyID, FailureReason)>;

private:
	on_user_time_played_retrieve_success_func_t on_user_time_played_retrieve_success;
	on_user_time_played_retrieve_failure_func_t on_user_time_played_retrieve_failure;

public:
	UserTimePlayedRetrieveListenerImplGlobal(
		on_user_time_played_retrieve_success_func_t on_user_time_played_retrieve_success = nullptr,
		on_user_time_played_retrieve_failure_func_t on_user_time_played_retrieve_failure = nullptr) :
		on_user_time_played_retrieve_success{ on_user_time_played_retrieve_success },
		on_user_time_played_retrieve_failure{ on_user_time_played_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserTimePlayedRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserTimePlayedRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_user_time_played_retrieve_success != nullptr) {
			on_user_time_played_retrieve_success(userID);
		}
	}

	virtual void OnUserTimePlayedRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_time_played_retrieve_failure != nullptr) {
			on_user_time_played_retrieve_failure(userID, failureReason);
		}
	}
};

class UserTimePlayedRetrieveListenerImplLocal : public galaxy::api::IUserTimePlayedRetrieveListener
{
public:
	using on_user_time_played_retrieve_success_func_t = std::function<void(GalaxyID)>;
	using on_user_time_played_retrieve_failure_func_t = std::function<void(GalaxyID, FailureReason)>;

private:
	on_user_time_played_retrieve_success_func_t on_user_time_played_retrieve_success;
	on_user_time_played_retrieve_failure_func_t on_user_time_played_retrieve_failure;

public:
	UserTimePlayedRetrieveListenerImplLocal(
		on_user_time_played_retrieve_success_func_t on_user_time_played_retrieve_success = nullptr,
		on_user_time_played_retrieve_failure_func_t on_user_time_played_retrieve_failure = nullptr) :
		on_user_time_played_retrieve_success{ on_user_time_played_retrieve_success },
		on_user_time_played_retrieve_failure{ on_user_time_played_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserTimePlayedRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserTimePlayedRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_user_time_played_retrieve_success != nullptr) {
			on_user_time_played_retrieve_success(userID);
		}
	}

	virtual void OnUserTimePlayedRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_time_played_retrieve_failure != nullptr) {
			on_user_time_played_retrieve_failure(userID, failureReason);
		}
	}
};

#endif
