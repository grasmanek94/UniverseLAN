#pragma once

#include "TestCaseClientDetails.hxx"

class StatsAndAchievementsStoreListenerImplGlobal : public galaxy::api::GlobalStatsAndAchievementsStoreListener
{
public:
	using on_user_stats_and_achievements_store_success_func_t = std::function<void()>;
	using on_user_stats_and_achievements_store_failure_func_t = std::function<void(FailureReason)>;

private:
	on_user_stats_and_achievements_store_success_func_t on_user_stats_and_achievements_store_success;
	on_user_stats_and_achievements_store_failure_func_t on_user_stats_and_achievements_store_failure;

public:
	StatsAndAchievementsStoreListenerImplGlobal(
		on_user_stats_and_achievements_store_success_func_t on_user_stats_and_achievements_store_success = nullptr,
		on_user_stats_and_achievements_store_failure_func_t on_user_stats_and_achievements_store_failure = nullptr) :
		on_user_stats_and_achievements_store_success{ on_user_stats_and_achievements_store_success },
		on_user_stats_and_achievements_store_failure{ on_user_stats_and_achievements_store_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~StatsAndAchievementsStoreListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserStatsAndAchievementsStoreSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_user_stats_and_achievements_store_success != nullptr) {
			on_user_stats_and_achievements_store_success();
		}
	}

	virtual void OnUserStatsAndAchievementsStoreFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_stats_and_achievements_store_failure != nullptr) {
			on_user_stats_and_achievements_store_failure(failureReason);
		}
	}
};

class StatsAndAchievementsStoreListenerImplLocal : public galaxy::api::IStatsAndAchievementsStoreListener
{
public:
	using on_user_stats_and_achievements_store_success_func_t = std::function<void()>;
	using on_user_stats_and_achievements_store_failure_func_t = std::function<void(FailureReason)>;

private:
	on_user_stats_and_achievements_store_success_func_t on_user_stats_and_achievements_store_success;
	on_user_stats_and_achievements_store_failure_func_t on_user_stats_and_achievements_store_failure;

public:
	StatsAndAchievementsStoreListenerImplLocal(
		on_user_stats_and_achievements_store_success_func_t on_user_stats_and_achievements_store_success = nullptr,
		on_user_stats_and_achievements_store_failure_func_t on_user_stats_and_achievements_store_failure = nullptr) :
		on_user_stats_and_achievements_store_success{ on_user_stats_and_achievements_store_success },
		on_user_stats_and_achievements_store_failure{ on_user_stats_and_achievements_store_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~StatsAndAchievementsStoreListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserStatsAndAchievementsStoreSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_user_stats_and_achievements_store_success != nullptr) {
			on_user_stats_and_achievements_store_success();
		}
	}

	virtual void OnUserStatsAndAchievementsStoreFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_stats_and_achievements_store_failure != nullptr) {
			on_user_stats_and_achievements_store_failure(failureReason);
		}
	}
};
