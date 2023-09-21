#pragma once

#include "TestCaseClientDetails.hxx"

class LeaderboardsRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardsRetrieveListener
{
public:
	using on_leaderboards_retrieve_success_func_t = std::function<void()>;
	using on_leaderboards_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_leaderboards_retrieve_success_func_t on_leaderboards_retrieve_success;
	on_leaderboards_retrieve_failure_func_t on_leaderboards_retrieve_failure;

public:
	LeaderboardsRetrieveListenerImplGlobal(
		on_leaderboards_retrieve_success_func_t on_leaderboards_retrieve_success = nullptr,
		on_leaderboards_retrieve_failure_func_t on_leaderboards_retrieve_failure = nullptr) :
		on_leaderboards_retrieve_success{ on_leaderboards_retrieve_success },
		on_leaderboards_retrieve_failure{ on_leaderboards_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LeaderboardsRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardsRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_leaderboards_retrieve_success != nullptr) {
			on_leaderboards_retrieve_success();
		}
	}

	virtual void OnLeaderboardsRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_leaderboards_retrieve_failure != nullptr) {
			on_leaderboards_retrieve_failure(failureReason);
		}
	}
};

class LeaderboardsRetrieveListenerImplLocal : public galaxy::api::ILeaderboardsRetrieveListener
{
public:
	using on_leaderboards_retrieve_success_func_t = std::function<void()>;
	using on_leaderboards_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_leaderboards_retrieve_success_func_t on_leaderboards_retrieve_success;
	on_leaderboards_retrieve_failure_func_t on_leaderboards_retrieve_failure;

public:
	LeaderboardsRetrieveListenerImplLocal(
		on_leaderboards_retrieve_success_func_t on_leaderboards_retrieve_success = nullptr,
		on_leaderboards_retrieve_failure_func_t on_leaderboards_retrieve_failure = nullptr) :
		on_leaderboards_retrieve_success{ on_leaderboards_retrieve_success },
		on_leaderboards_retrieve_failure{ on_leaderboards_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LeaderboardsRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardsRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_leaderboards_retrieve_success != nullptr) {
			on_leaderboards_retrieve_success();
		}
	}

	virtual void OnLeaderboardsRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_leaderboards_retrieve_failure != nullptr) {
			on_leaderboards_retrieve_failure(failureReason);
		}
	}
};
