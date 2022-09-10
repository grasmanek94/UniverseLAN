#include "Stats.hxx"

namespace galaxy
{
	namespace api
	{

		Stats::~Stats()
		{
		}

		void Stats::RequestUserStatsAndAchievements(GalaxyID userID, IUserStatsAndAchievementsRetrieveListener* const listener) {

		}

		int32_t Stats::GetStatInt(const char* name, GalaxyID userID) {
			return 0;
		}

		float Stats::GetStatFloat(const char* name, GalaxyID userID) {
			return 0.0f;
		}

		void Stats::SetStatInt(const char* name, int32_t value) {

		}

		void Stats::SetStatFloat(const char* name, float value) {

		}

		void Stats::UpdateAvgRateStat(const char* name, float countThisSession, double sessionLength) {

		}

		void Stats::GetAchievement(const char* name, bool& unlocked, uint32_t& unlockTime, GalaxyID userID) {

		}

		void Stats::SetAchievement(const char* name) {

		}

		void Stats::ClearAchievement(const char* name) {

		}

		void Stats::StoreStatsAndAchievements(IStatsAndAchievementsStoreListener* const listener) {

		}

		void Stats::ResetStatsAndAchievements(IStatsAndAchievementsStoreListener* const listener) {

		}

		const char* Stats::GetAchievementDisplayName(const char* name) {
			return name;
		}

		void Stats::GetAchievementDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {

		}

		const char* Stats::GetAchievementDescription(const char* name) {
			return name;
		}

		void Stats::GetAchievementDescriptionCopy(const char* name, char* buffer, uint32_t bufferLength) {

		}

		bool Stats::IsAchievementVisible(const char* name) {
			return true;
		}

		bool Stats::IsAchievementVisibleWhileLocked(const char* name) {
			return true;
		}

		void Stats::RequestLeaderboards(ILeaderboardsRetrieveListener* const listener) {

		}

		const char* Stats::GetLeaderboardDisplayName(const char* name) {
			return name;
		}

		void Stats::GetLeaderboardDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {

		}

		LeaderboardSortMethod Stats::GetLeaderboardSortMethod(const char* name) {
			return LEADERBOARD_SORT_METHOD_NONE;
		}

		LeaderboardDisplayType Stats::GetLeaderboardDisplayType(const char* name) {
			return LEADERBOARD_DISPLAY_TYPE_NONE;
		}

		void Stats::RequestLeaderboardEntriesGlobal(
			const char* name,
			uint32_t rangeStart,
			uint32_t rangeEnd,
			ILeaderboardEntriesRetrieveListener* const listener) {

		}

		void Stats::RequestLeaderboardEntriesAroundUser(
			const char* name,
			uint32_t countBefore,
			uint32_t countAfter,
			GalaxyID userID,
			ILeaderboardEntriesRetrieveListener* const listener) {

		}

		void Stats::RequestLeaderboardEntriesForUsers(
			const char* name,
			GalaxyID* userArray,
			uint32_t userArraySize,
			ILeaderboardEntriesRetrieveListener* const listener) {

		}

		void Stats::GetRequestedLeaderboardEntry(uint32_t index, uint32_t& rank, int32_t& score, GalaxyID& userID) {

		}

		void Stats::GetRequestedLeaderboardEntryWithDetails(
			uint32_t index,
			uint32_t& rank,
			int32_t& score,
			void* details,
			uint32_t detailsSize,
			uint32_t& outDetailsSize,
			GalaxyID& userID) {

		}

		void Stats::SetLeaderboardScore(
			const char* name,
			int32_t score,
			bool forceUpdate,
			ILeaderboardScoreUpdateListener* const listener) {

		}

		void Stats::SetLeaderboardScoreWithDetails(
			const char* name,
			int32_t score,
			const void* details,
			uint32_t detailsSize,
			bool forceUpdate,
			ILeaderboardScoreUpdateListener* const listener) {

		}

		uint32_t Stats::GetLeaderboardEntryCount(const char* name) {
			return 0;
		}

		void Stats::FindLeaderboard(const char* name, ILeaderboardRetrieveListener* const listener) {

		}

		void Stats::FindOrCreateLeaderboard(
			const char* name,
			const char* displayName,
			const LeaderboardSortMethod& sortMethod,
			const LeaderboardDisplayType& displayType,
			ILeaderboardRetrieveListener* const listener) {

		}

		void Stats::RequestUserTimePlayed(GalaxyID userID, IUserTimePlayedRetrieveListener* const listener) {

		}

		uint32_t Stats::GetUserTimePlayed(GalaxyID userID) {
			return 0;
		}
	}
}


