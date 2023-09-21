#pragma once

#if GALAXY_BUILD_FEATURE_HAS_IUSERFINDLISTENER

#include "TestCaseClientDetails.hxx"

class UserFindListenerImplGlobal : public galaxy::api::GlobalUserFindListener
{
public:
	using on_user_find_success_func_t = std::function<void(const char* userSpecifier, GalaxyID userID)>;
	using on_user_find_failure_func_t = std::function<void(const char* userSpecifier, FailureReason)>;

private:
	on_user_find_success_func_t on_user_find_success;
	on_user_find_failure_func_t on_user_find_failure;

public:
	UserFindListenerImplGlobal(
		on_user_find_success_func_t on_user_find_success = nullptr,
		on_user_find_failure_func_t on_user_find_failure = nullptr) :
		on_user_find_success{ on_user_find_success },
		on_user_find_failure{ on_user_find_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserFindListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserFindSuccess(const char* userSpecifier, GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userSpecifier: {} userID: {}",
			userSpecifier, userID
		).c_str());


		if (on_user_find_success != nullptr) {
			on_user_find_success(userSpecifier, userID);
		}
	}
	virtual void OnUserFindFailure(const char* userSpecifier, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userSpecifier: {} failureReason: {}",
			userSpecifier, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_find_failure != nullptr) {
			on_user_find_failure(userSpecifier, failureReason);
		}
	}
};

class UserFindListenerImplLocal : public galaxy::api::IUserFindListener
{
public:
	using on_user_find_success_func_t = std::function<void(const char* userSpecifier, GalaxyID userID)>;
	using on_user_find_failure_func_t = std::function<void(const char* userSpecifier, FailureReason)>;

private:
	on_user_find_success_func_t on_user_find_success;
	on_user_find_failure_func_t on_user_find_failure;

public:
	UserFindListenerImplLocal(
		on_user_find_success_func_t on_user_find_success = nullptr,
		on_user_find_failure_func_t on_user_find_failure = nullptr) :
		on_user_find_success{ on_user_find_success },
		on_user_find_failure{ on_user_find_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserFindListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserFindSuccess(const char* userSpecifier, GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userSpecifier: {} userID: {}",
			userSpecifier, userID
		).c_str());


		if (on_user_find_success != nullptr) {
			on_user_find_success(userSpecifier, userID);
		}
	}
	virtual void OnUserFindFailure(const char* userSpecifier, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userSpecifier: {} failureReason: {}",
			userSpecifier, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_find_failure != nullptr) {
			on_user_find_failure(userSpecifier, failureReason);
		}
	}
};

#endif
