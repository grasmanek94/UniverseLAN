#pragma once

#include "TestCaseClientDetails.hxx"

class LeaderboardRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardRetrieveListener
{
public:
	using on_leaderboard_retrieve_success_func_t = std::function<void(const char* name)>;
	using on_leaderboard_retrieve_failure_func_t = std::function<void(const char* name, FailureReason)>;

private:
	on_leaderboard_retrieve_success_func_t on_leaderboard_retrieve_success;
	on_leaderboard_retrieve_failure_func_t on_leaderboard_retrieve_failure;

public:
	LeaderboardRetrieveListenerImplGlobal(
		on_leaderboard_retrieve_success_func_t on_leaderboard_retrieve_success = nullptr,
		on_leaderboard_retrieve_failure_func_t on_leaderboard_retrieve_failure = nullptr) :
		on_leaderboard_retrieve_success{ on_leaderboard_retrieve_success },
		on_leaderboard_retrieve_failure{ on_leaderboard_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LeaderboardRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardRetrieveSuccess(const char* name) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {}",
			name
		).c_str());


		if (on_leaderboard_retrieve_success != nullptr) {
			on_leaderboard_retrieve_success(name);
		}
	}

	virtual void OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} failureReason: {}",
			name, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_leaderboard_retrieve_failure != nullptr) {
			on_leaderboard_retrieve_failure(name, failureReason);
		}
	}
};

class LeaderboardRetrieveListenerImplLocal : public galaxy::api::ILeaderboardRetrieveListener
{
public:
	using on_leaderboard_retrieve_success_func_t = std::function<void(const char* name)>;
	using on_leaderboard_retrieve_failure_func_t = std::function<void(const char* name, FailureReason)>;

private:
	on_leaderboard_retrieve_success_func_t on_leaderboard_retrieve_success;
	on_leaderboard_retrieve_failure_func_t on_leaderboard_retrieve_failure;

public:
	LeaderboardRetrieveListenerImplLocal(
		on_leaderboard_retrieve_success_func_t on_leaderboard_retrieve_success = nullptr,
		on_leaderboard_retrieve_failure_func_t on_leaderboard_retrieve_failure = nullptr) :
		on_leaderboard_retrieve_success{ on_leaderboard_retrieve_success },
		on_leaderboard_retrieve_failure{ on_leaderboard_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LeaderboardRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardRetrieveSuccess(const char* name) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {}",
			name
		).c_str());


		if (on_leaderboard_retrieve_success != nullptr) {
			on_leaderboard_retrieve_success(name);
		}
	}

	virtual void OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} failureReason: {}",
			name, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_leaderboard_retrieve_failure != nullptr) {
			on_leaderboard_retrieve_failure(name, failureReason);
		}
	}
};
