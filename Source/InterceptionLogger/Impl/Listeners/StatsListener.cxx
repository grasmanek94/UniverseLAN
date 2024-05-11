#include "StatsListener.hxx"
#include "ProxifySingleShotListener.hxx"

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

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserStatsAndAchievementsRetrieveSuccess(userID));
	}

	void UserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserStatsAndAchievementsRetrieveFailure(userID, failureReason));
	}

	void StatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserStatsAndAchievementsStoreSuccess());
	}

	void StatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserStatsAndAchievementsStoreFailure(failureReason));
	}

	void AchievementChangeListener::OnAchievementProgressChanged(const char* name, uint32_t currentProgress, uint32_t maxProgress)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("currentProgress: {}", currentProgress));
			trace.write_all(std::format("maxProgress: {}", maxProgress));
		}

		//IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnAchievementProgressChanged(name, currentProgress, maxProgress));
	}

	void AchievementChangeListener::OnAchievementUnlocked(const char* name)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnAchievementUnlocked(name));
	}

	void LeaderboardsRetrieveListener::OnLeaderboardsRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnLeaderboardsRetrieveSuccess());
	}

	void LeaderboardsRetrieveListener::OnLeaderboardsRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnLeaderboardsRetrieveFailure(failureReason));
	}

	void LeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("entryCount: {}", entryCount));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnLeaderboardEntriesRetrieveSuccess(name, entryCount));
	}

	void LeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure(const char* name, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnLeaderboardEntriesRetrieveFailure(name, failureReason));
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

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnLeaderboardScoreUpdateSuccess(name, score, oldRank, newRank));
	}

	void LeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateFailure(const char* name, int32_t score, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("score: {}", score));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnLeaderboardScoreUpdateFailure(name, score, failureReason));
	}

#if GALAXY_BUILD_FEATURE_HAS_ILEADERBOARDRETRIEVELISTENER
	void LeaderboardRetrieveListener::OnLeaderboardRetrieveSuccess(const char* name)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnLeaderboardRetrieveSuccess(name));
	}

	void LeaderboardRetrieveListener::OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnLeaderboardRetrieveFailure(name, failureReason));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
	void UserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserTimePlayedRetrieveSuccess(userID));
	}

	void UserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveFailure(GalaxyID userID, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnUserTimePlayedRetrieveFailure(userID, failureReason));
	}
#endif
}
