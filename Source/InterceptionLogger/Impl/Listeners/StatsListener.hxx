#pragma once

#include <IStats.h>

namespace universelan::client {
	using namespace galaxy::api;

	class UserStatsAndAchievementsRetrieveListener : public IUserStatsAndAchievementsRetrieveListener
	{
	public:
		virtual void OnUserStatsAndAchievementsRetrieveSuccess(GalaxyID userID);
		virtual void OnUserStatsAndAchievementsRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};

	class StatsAndAchievementsStoreListener : public IStatsAndAchievementsStoreListener
	{
	public:
		virtual void OnUserStatsAndAchievementsStoreSuccess();
		virtual void OnUserStatsAndAchievementsStoreFailure(FailureReason failureReason);
	};

	class AchievementChangeListener : public IAchievementChangeListener
	{
	public:
		virtual void OnAchievementProgressChanged(const char* name, uint32_t currentProgress, uint32_t maxProgress);
		virtual void OnAchievementUnlocked(const char* name);
	};

	class LeaderboardsRetrieveListener : public ILeaderboardsRetrieveListener
	{
	public:
		virtual void OnLeaderboardsRetrieveSuccess();
		virtual void OnLeaderboardsRetrieveFailure(FailureReason failureReason);
	};

	class LeaderboardEntriesRetrieveListener : public ILeaderboardEntriesRetrieveListener
	{
	public:
		virtual void OnLeaderboardEntriesRetrieveSuccess(const char* name, uint32_t entryCount);
		virtual void OnLeaderboardEntriesRetrieveFailure(const char* name, FailureReason failureReason);
	};

	class LeaderboardScoreUpdateListener : public ILeaderboardScoreUpdateListener
	{
	public:
		virtual void OnLeaderboardScoreUpdateSuccess(const char* name, int32_t score, uint32_t oldRank, uint32_t newRank);
		virtual void OnLeaderboardScoreUpdateFailure(const char* name, int32_t score, FailureReason failureReason);
	};

	class LeaderboardRetrieveListener : public ILeaderboardRetrieveListener
	{
	public:
		virtual void OnLeaderboardRetrieveSuccess(const char* name);
		virtual void OnLeaderboardRetrieveFailure(const char* name, FailureReason failureReason);
	};

	class UserTimePlayedRetrieveListener : public IUserTimePlayedRetrieveListener
	{
	public:
		virtual void OnUserTimePlayedRetrieveSuccess(GalaxyID userID);
		virtual void OnUserTimePlayedRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};
}
