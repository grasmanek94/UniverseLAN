#pragma once

#include "TestCaseClientDetails.hxx"

#if GALAXY_BUILD_FEATURE_HAS_IRICHPRECENSECHANGELISTENER

class RichPresenceChangeListenerImplGlobal : public galaxy::api::GlobalRichPresenceChangeListener
{
public:
	using on_rich_presence_change_success_func_t = std::function<void()>;
	using on_rich_presence_change_failure_func_t = std::function<void(FailureReason)>;

private:
	on_rich_presence_change_success_func_t on_rich_presence_change_success;
	on_rich_presence_change_failure_func_t on_rich_presence_change_failure;

public:
	RichPresenceChangeListenerImplGlobal(
		on_rich_presence_change_success_func_t on_rich_presence_change_success = nullptr,
		on_rich_presence_change_failure_func_t on_rich_presence_change_failure = nullptr) :
		on_rich_presence_change_success{ on_rich_presence_change_success },
		on_rich_presence_change_failure{ on_rich_presence_change_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~RichPresenceChangeListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnRichPresenceChangeSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_rich_presence_change_success != nullptr) {
			on_rich_presence_change_success();
		}
	}

	virtual void OnRichPresenceChangeFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_rich_presence_change_failure != nullptr) {
			on_rich_presence_change_failure(failureReason);
		}
	}
};

class RichPresenceChangeListenerImplLocal : public galaxy::api::IRichPresenceChangeListener
{
public:
	using on_rich_presence_change_success_func_t = std::function<void()>;
	using on_rich_presence_change_failure_func_t = std::function<void(FailureReason)>;

private:
	on_rich_presence_change_success_func_t on_rich_presence_change_success;
	on_rich_presence_change_failure_func_t on_rich_presence_change_failure;

public:
	RichPresenceChangeListenerImplLocal(
		on_rich_presence_change_success_func_t on_rich_presence_change_success = nullptr,
		on_rich_presence_change_failure_func_t on_rich_presence_change_failure = nullptr) :
		on_rich_presence_change_success{ on_rich_presence_change_success },
		on_rich_presence_change_failure{ on_rich_presence_change_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~RichPresenceChangeListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnRichPresenceChangeSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_rich_presence_change_success != nullptr) {
			on_rich_presence_change_success();
		}
	}

	virtual void OnRichPresenceChangeFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_rich_presence_change_failure != nullptr) {
			on_rich_presence_change_failure(failureReason);
		}
	}
};

#endif