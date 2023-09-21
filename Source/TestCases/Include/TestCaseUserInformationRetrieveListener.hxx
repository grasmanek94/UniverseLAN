#pragma once

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS

#include "TestCaseClientDetails.hxx"

class UserInformationRetrieveListenerImplGlobal : public galaxy::api::GlobalUserInformationRetrieveListener
{
public:
	using on_user_information_retrieve_success_func_t = std::function<void(GalaxyID userID)>;
	using on_user_information_retrieve_failure_func_t = std::function<void(GalaxyID, FailureReason)>;

private:
	on_user_information_retrieve_success_func_t on_user_information_retrieve_success;
	on_user_information_retrieve_failure_func_t on_user_information_retrieve_failure;

public:
	UserInformationRetrieveListenerImplGlobal(
		on_user_information_retrieve_success_func_t on_user_information_retrieve_success = nullptr,
		on_user_information_retrieve_failure_func_t on_user_information_retrieve_failure = nullptr) :
		on_user_information_retrieve_success{ on_user_information_retrieve_success },
		on_user_information_retrieve_failure{ on_user_information_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserInformationRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserInformationRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_user_information_retrieve_success != nullptr) {
			on_user_information_retrieve_success(userID);
		}
	}

	virtual void OnUserInformationRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_information_retrieve_failure != nullptr) {
			on_user_information_retrieve_failure(userID, failureReason);
		}
	}
};

class UserInformationRetrieveListenerImplLocal : public galaxy::api::IUserInformationRetrieveListener
{
public:
	using on_user_information_retrieve_success_func_t = std::function<void(GalaxyID userID)>;
	using on_user_information_retrieve_failure_func_t = std::function<void(GalaxyID, FailureReason)>;

private:
	on_user_information_retrieve_success_func_t on_user_information_retrieve_success;
	on_user_information_retrieve_failure_func_t on_user_information_retrieve_failure;

public:
	UserInformationRetrieveListenerImplLocal(
		on_user_information_retrieve_success_func_t on_user_information_retrieve_success = nullptr,
		on_user_information_retrieve_failure_func_t on_user_information_retrieve_failure = nullptr) :
		on_user_information_retrieve_success{ on_user_information_retrieve_success },
		on_user_information_retrieve_failure{ on_user_information_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserInformationRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserInformationRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_user_information_retrieve_success != nullptr) {
			on_user_information_retrieve_success(userID);
		}
	}

	virtual void OnUserInformationRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_information_retrieve_failure != nullptr) {
			on_user_information_retrieve_failure(userID, failureReason);
		}
	}
};

#endif
