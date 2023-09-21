#pragma once

#include "TestCaseClientDetails.hxx"

class LeaderboardScoreUpdateListenerImplGlobal : public galaxy::api::GlobalLeaderboardScoreUpdateListener
{
public:
	using on_leaderboard_score_update_success_func_t = std::function<void(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank)>;
	using on_leaderboard_score_update_failure_func_t = std::function<void(const char* name, int32_t score, FailureReason failureReason)>;

private:
	on_leaderboard_score_update_success_func_t on_leaderboard_score_update_success;
	on_leaderboard_score_update_failure_func_t on_leaderboard_score_update_failure;

public:
	LeaderboardScoreUpdateListenerImplGlobal(
		on_leaderboard_score_update_success_func_t on_leaderboard_score_update_success = nullptr,
		on_leaderboard_score_update_failure_func_t on_leaderboard_score_update_failure = nullptr) :
		on_leaderboard_score_update_success{ on_leaderboard_score_update_success },
		on_leaderboard_score_update_failure{ on_leaderboard_score_update_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LeaderboardScoreUpdateListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardScoreUpdateSuccess(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} score: {} oldRank: {} newRank: {}",
			name, score, oldRank, newRank
		).c_str());


		if (on_leaderboard_score_update_success != nullptr) {
			on_leaderboard_score_update_success(name, score, oldRank, newRank);
		}
	}

	virtual void OnLeaderboardScoreUpdateFailure(const char* name, int32_t score, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} score: {} failureReason: {}",
			name, score, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_leaderboard_score_update_failure != nullptr) {
			on_leaderboard_score_update_failure(name, score, failureReason);
		}
	}
};

class LeaderboardScoreUpdateListenerImplLocal : public galaxy::api::ILeaderboardScoreUpdateListener
{
public:
	using on_leaderboard_score_update_success_func_t = std::function<void(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank)>;
	using on_leaderboard_score_update_failure_func_t = std::function<void(const char* name, int32_t score, FailureReason failureReason)>;

private:
	on_leaderboard_score_update_success_func_t on_leaderboard_score_update_success;
	on_leaderboard_score_update_failure_func_t on_leaderboard_score_update_failure;

public:
	LeaderboardScoreUpdateListenerImplLocal(
		on_leaderboard_score_update_success_func_t on_leaderboard_score_update_success = nullptr,
		on_leaderboard_score_update_failure_func_t on_leaderboard_score_update_failure = nullptr) :
		on_leaderboard_score_update_success{ on_leaderboard_score_update_success },
		on_leaderboard_score_update_failure{ on_leaderboard_score_update_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LeaderboardScoreUpdateListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLeaderboardScoreUpdateSuccess(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} score: {} oldRank: {} newRank: {}",
			name, score, oldRank, newRank
		).c_str());


		if (on_leaderboard_score_update_success != nullptr) {
			on_leaderboard_score_update_success(name, score, oldRank, newRank);
		}
	}

	virtual void OnLeaderboardScoreUpdateFailure(const char* name, int32_t score, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"name: {} score: {} failureReason: {}",
			name, score, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_leaderboard_score_update_failure != nullptr) {
			on_leaderboard_score_update_failure(name, score, failureReason);
		}
	}
};
