#pragma once

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS

#include "TestCaseClientDetails.hxx"

class RichPresenceRetrieveListenerImplGlobal : public galaxy::api::GlobalRichPresenceRetrieveListener
{
public:
	using on_rich_presence_retrieve_success_func_t = std::function<void(GalaxyID userID)>;
	using on_rich_presence_retrieve_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_rich_presence_retrieve_success_func_t on_rich_presence_retrieve_success;
	on_rich_presence_retrieve_failure_func_t on_rich_presence_retrieve_failure;

public:
	RichPresenceRetrieveListenerImplGlobal(
		on_rich_presence_retrieve_success_func_t on_rich_presence_retrieve_success = nullptr,
		on_rich_presence_retrieve_failure_func_t on_rich_presence_retrieve_failure = nullptr) :
		on_rich_presence_retrieve_success{ on_rich_presence_retrieve_success },
		on_rich_presence_retrieve_failure{ on_rich_presence_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~RichPresenceRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnRichPresenceRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_rich_presence_retrieve_success != nullptr) {
			on_rich_presence_retrieve_success(userID);
		}
	}

	virtual void OnRichPresenceRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_rich_presence_retrieve_failure != nullptr) {
			on_rich_presence_retrieve_failure(userID, failureReason);
		}
	}
};

class RichPresenceRetrieveListenerImplLocal : public galaxy::api::IRichPresenceRetrieveListener
{
public:
	using on_rich_presence_retrieve_success_func_t = std::function<void(GalaxyID userID)>;
	using on_rich_presence_retrieve_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_rich_presence_retrieve_success_func_t on_rich_presence_retrieve_success;
	on_rich_presence_retrieve_failure_func_t on_rich_presence_retrieve_failure;

public:
	RichPresenceRetrieveListenerImplLocal(
		on_rich_presence_retrieve_success_func_t on_rich_presence_retrieve_success = nullptr,
		on_rich_presence_retrieve_failure_func_t on_rich_presence_retrieve_failure = nullptr) :
		on_rich_presence_retrieve_success{ on_rich_presence_retrieve_success },
		on_rich_presence_retrieve_failure{ on_rich_presence_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~RichPresenceRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnRichPresenceRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_rich_presence_retrieve_success != nullptr) {
			on_rich_presence_retrieve_success(userID);
		}
	}

	virtual void OnRichPresenceRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_rich_presence_retrieve_failure != nullptr) {
			on_rich_presence_retrieve_failure(userID, failureReason);
		}
	}
};

#endif
