#include "StatsListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::ISTATS;
	}

	void UserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void UserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void StatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void StatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void AchievementChangeListener::OnAchievementProgressChanged(const char* name, uint32_t currentProgress, uint32_t maxProgress)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("currentProgress: {}", currentProgress));
			trace.write_all(std::format("maxProgress: {}", maxProgress));
		}
	}

	void AchievementChangeListener::OnAchievementUnlocked(const char* name)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}
	}

	void LeaderboardsRetrieveListener::OnLeaderboardsRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void LeaderboardsRetrieveListener::OnLeaderboardsRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void LeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("entryCount: {}", entryCount));
		}
	}

	void LeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure(const char* name, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void LeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateSuccess(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("score: {}", score));
			trace.write_all(std::format("oldRank: {}", oldRank));
			trace.write_all(std::format("newRank: {}", newRank));
		}
	}

	void LeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateFailure(const char* name, int32_t score, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("score: {}", score));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_ILEADERBOARDRETRIEVELISTENER
	void LeaderboardRetrieveListener::OnLeaderboardRetrieveSuccess(const char* name)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}
	}

	void LeaderboardRetrieveListener::OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
	void UserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void UserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}
#endif
}
