#pragma once

#include "ProxifySingleShotListener.hxx"

#include <IStats.h>

namespace universelan::client {
	using namespace galaxy::api;

	class UserStatsAndAchievementsRetrieveListener : public IUserStatsAndAchievementsRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(UserStatsAndAchievementsRetrieveListener, IUserStatsAndAchievementsRetrieveListener);

	public:
		virtual void OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID);
		virtual void OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};

	class StatsAndAchievementsStoreListener : public IStatsAndAchievementsStoreListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(StatsAndAchievementsStoreListener, IStatsAndAchievementsStoreListener);

	public:
		virtual void OnUserStatsAndAchievementsStoreSuccess();
		virtual void OnUserStatsAndAchievementsStoreFailure(FailureReason failureReason);
	};

	class AchievementChangeListener : public IAchievementChangeListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(AchievementChangeListener, IAchievementChangeListener);

	public:
		virtual void OnAchievementProgressChanged(const char* name, uint32_t currentProgress, uint32_t maxProgress);
		virtual void OnAchievementUnlocked(const char* name);
	};

	class LeaderboardsRetrieveListener : public ILeaderboardsRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LeaderboardsRetrieveListener, ILeaderboardsRetrieveListener);

	public:
		virtual void OnLeaderboardsRetrieveSuccess();
		virtual void OnLeaderboardsRetrieveFailure(FailureReason failureReason);
	};

	class LeaderboardEntriesRetrieveListener : public ILeaderboardEntriesRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LeaderboardEntriesRetrieveListener, ILeaderboardEntriesRetrieveListener);

	public:
		virtual void OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount);
		virtual void OnLeaderboardEntriesRetrieveFailure(const char* name, FailureReason failureReason);
	};

	class LeaderboardScoreUpdateListener : public ILeaderboardScoreUpdateListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LeaderboardScoreUpdateListener, ILeaderboardScoreUpdateListener);

	public:
		virtual void OnLeaderboardScoreUpdateSuccess(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank);
		virtual void OnLeaderboardScoreUpdateFailure(const char* name, int32_t score, FailureReason failureReason);
	};

#if GALAXY_BUILD_FEATURE_HAS_ILEADERBOARDRETRIEVELISTENER
	class LeaderboardRetrieveListener : public ILeaderboardRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LeaderboardRetrieveListener, ILeaderboardRetrieveListener);

	public:
		virtual void OnLeaderboardRetrieveSuccess(const char* name);
		virtual void OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
	class UserTimePlayedRetrieveListener : public IUserTimePlayedRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(UserTimePlayedRetrieveListener, IUserTimePlayedRetrieveListener);

	public:
		virtual void OnUserTimePlayedRetrieveSuccess(GalaxyID userID);
		virtual void OnUserTimePlayedRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};
#endif
}
