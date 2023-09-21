#pragma once

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS

#include "TestCaseClientDetails.hxx"

class UserStatsAndAchievementsRetrieveListenerImplGlobal : public galaxy::api::GlobalUserStatsAndAchievementsRetrieveListener
{
public:
	using on_user_stats_and_achievements_retrieve_success_func_t = std::function<void(GalaxyID userID)>;
	using on_user_stats_and_achievements_retrieve_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_user_stats_and_achievements_retrieve_success_func_t on_user_stats_and_achievements_retrieve_success;
	on_user_stats_and_achievements_retrieve_failure_func_t on_user_stats_and_achievements_retrieve_failure;

public:
	UserStatsAndAchievementsRetrieveListenerImplGlobal(
		on_user_stats_and_achievements_retrieve_success_func_t on_user_stats_and_achievements_retrieve_success = nullptr,
		on_user_stats_and_achievements_retrieve_failure_func_t on_user_stats_and_achievements_retrieve_failure = nullptr) :
		on_user_stats_and_achievements_retrieve_success{ on_user_stats_and_achievements_retrieve_success },
		on_user_stats_and_achievements_retrieve_failure{ on_user_stats_and_achievements_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserStatsAndAchievementsRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_user_stats_and_achievements_retrieve_success != nullptr) {
			on_user_stats_and_achievements_retrieve_success(userID);
		}
	}

	virtual void OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_stats_and_achievements_retrieve_failure != nullptr) {
			on_user_stats_and_achievements_retrieve_failure(userID, failureReason);
		}
	}
};

class UserStatsAndAchievementsRetrieveListenerImplLocal : public galaxy::api::IUserStatsAndAchievementsRetrieveListener
{
public:
	using on_user_stats_and_achievements_retrieve_success_func_t = std::function<void(GalaxyID userID)>;
	using on_user_stats_and_achievements_retrieve_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_user_stats_and_achievements_retrieve_success_func_t on_user_stats_and_achievements_retrieve_success;
	on_user_stats_and_achievements_retrieve_failure_func_t on_user_stats_and_achievements_retrieve_failure;

public:
	UserStatsAndAchievementsRetrieveListenerImplLocal(
		on_user_stats_and_achievements_retrieve_success_func_t on_user_stats_and_achievements_retrieve_success = nullptr,
		on_user_stats_and_achievements_retrieve_failure_func_t on_user_stats_and_achievements_retrieve_failure = nullptr) :
		on_user_stats_and_achievements_retrieve_success{ on_user_stats_and_achievements_retrieve_success },
		on_user_stats_and_achievements_retrieve_failure{ on_user_stats_and_achievements_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~UserStatsAndAchievementsRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {}",
			userID
		).c_str());


		if (on_user_stats_and_achievements_retrieve_success != nullptr) {
			on_user_stats_and_achievements_retrieve_success(userID);
		}
	}

	virtual void OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_user_stats_and_achievements_retrieve_failure != nullptr) {
			on_user_stats_and_achievements_retrieve_failure(userID, failureReason);
		}
	}
};

#endif
