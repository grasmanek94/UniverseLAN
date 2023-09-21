#pragma once

#include "TestCaseClientDetails.hxx"

class LeaderboardEntriesRetrieveListenerImplGlobal : public galaxy::api::GlobalLeaderboardEntriesRetrieveListener
{
public:
	using on_leaderboard_entries_retrieve_success_func_t = std::function<void(const char* name, uint32_t entryCount)>;
	using on_leaderboard_entries_retrieve_failure_func_t = std::function<void(const char* name, FailureReason)>;

private:
	on_leaderboard_entries_retrieve_success_func_t on_leaderboard_entries_retrieve_success;
	on_leaderboard_entries_retrieve_failure_func_t on_leaderboard_entries_retrieve_failure;

public:
	LeaderboardEntriesRetrieveListenerImplGlobal(
		on_leaderboard_entries_retrieve_success_func_t on_leaderboard_entries_retrieve_success = nullptr,
		on_leaderboard_entries_retrieve_failure_func_t on_leaderboard_entries_retrieve_failure = nullptr) :
		on_leaderboard_entries_retrieve_success{ on_leaderboard_entries_retrieve_success },
		on_leaderboard_entries_retrieve_failure{ on_leaderboard_entries_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LeaderboardEntriesRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} entryCount: {}",
			name, entryCount
		).c_str());


		if (on_leaderboard_entries_retrieve_success != nullptr) {
			on_leaderboard_entries_retrieve_success(name, entryCount);
		}
	}

	virtual void OnLeaderboardEntriesRetrieveFailure(const char* name, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} failureReason: {}",
			name, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_leaderboard_entries_retrieve_failure != nullptr) {
			on_leaderboard_entries_retrieve_failure(name, failureReason);
		}
	}
};

class LeaderboardEntriesRetrieveListenerImplLocal : public galaxy::api::ILeaderboardEntriesRetrieveListener
{
public:
	using on_leaderboard_entries_retrieve_success_func_t = std::function<void(const char* name, uint32_t entryCount)>;
	using on_leaderboard_entries_retrieve_failure_func_t = std::function<void(const char* name, FailureReason)>;

private:
	on_leaderboard_entries_retrieve_success_func_t on_leaderboard_entries_retrieve_success;
	on_leaderboard_entries_retrieve_failure_func_t on_leaderboard_entries_retrieve_failure;

public:
	LeaderboardEntriesRetrieveListenerImplLocal(
		on_leaderboard_entries_retrieve_success_func_t on_leaderboard_entries_retrieve_success = nullptr,
		on_leaderboard_entries_retrieve_failure_func_t on_leaderboard_entries_retrieve_failure = nullptr) :
		on_leaderboard_entries_retrieve_success{ on_leaderboard_entries_retrieve_success },
		on_leaderboard_entries_retrieve_failure{ on_leaderboard_entries_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LeaderboardEntriesRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} entryCount: {}",
			name, entryCount
		).c_str());


		if (on_leaderboard_entries_retrieve_success != nullptr) {
			on_leaderboard_entries_retrieve_success(name, entryCount);
		}
	}

	virtual void OnLeaderboardEntriesRetrieveFailure(const char* name, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} failureReason: {}",
			name, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_leaderboard_entries_retrieve_failure != nullptr) {
			on_leaderboard_entries_retrieve_failure(name, failureReason);
		}
	}
};
