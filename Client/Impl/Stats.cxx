#include "Stats.hxx"

namespace galaxy
{
	namespace api
	{

		StatsImpl::~StatsImpl()
		{
		}

		void StatsImpl::RequestUserStatsAndAchievements(GalaxyID userID, IUserStatsAndAchievementsRetrieveListener* const listener) {

		}

		int32_t StatsImpl::GetStatInt(const char* name, GalaxyID userID) {
			return 0;
		}

		float StatsImpl::GetStatFloat(const char* name, GalaxyID userID) {
			return 0.0f;
		}

		void StatsImpl::SetStatInt(const char* name, int32_t value) {

		}

		void StatsImpl::SetStatFloat(const char* name, float value) {

		}

		void StatsImpl::UpdateAvgRateStat(const char* name, float countThisSession, double sessionLength) {

		}

		void StatsImpl::GetAchievement(const char* name, bool& unlocked, uint32_t& unlockTime, GalaxyID userID) {

		}

		void StatsImpl::SetAchievement(const char* name) {

		}

		void StatsImpl::ClearAchievement(const char* name) {

		}

		void StatsImpl::StoreStatsAndAchievements(IStatsAndAchievementsStoreListener* const listener) {

		}

		void StatsImpl::ResetStatsAndAchievements(IStatsAndAchievementsStoreListener* const listener) {

		}

		const char* StatsImpl::GetAchievementDisplayName(const char* name) {
			return name;
		}

		void StatsImpl::GetAchievementDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {

		}

		const char* StatsImpl::GetAchievementDescription(const char* name) {
			return name;
		}

		void StatsImpl::GetAchievementDescriptionCopy(const char* name, char* buffer, uint32_t bufferLength) {

		}

		bool StatsImpl::IsAchievementVisible(const char* name) {
			return true;
		}

		bool StatsImpl::IsAchievementVisibleWhileLocked(const char* name) {
			return true;
		}

		void StatsImpl::RequestLeaderboards(ILeaderboardsRetrieveListener* const listener) {

		}

		const char* StatsImpl::GetLeaderboardDisplayName(const char* name) {
			return name;
		}

		void StatsImpl::GetLeaderboardDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {

		}

		LeaderboardSortMethod StatsImpl::GetLeaderboardSortMethod(const char* name) {
			return LEADERBOARD_SORT_METHOD_NONE;
		}

		LeaderboardDisplayType StatsImpl::GetLeaderboardDisplayType(const char* name) {
			return LEADERBOARD_DISPLAY_TYPE_NONE;
		}

		void StatsImpl::RequestLeaderboardEntriesGlobal(
			const char* name,
			uint32_t rangeStart,
			uint32_t rangeEnd,
			ILeaderboardEntriesRetrieveListener* const listener) {

		}

		void StatsImpl::RequestLeaderboardEntriesAroundUser(
			const char* name,
			uint32_t countBefore,
			uint32_t countAfter,
			GalaxyID userID,
			ILeaderboardEntriesRetrieveListener* const listener) {

		}

		void StatsImpl::RequestLeaderboardEntriesForUsers(
			const char* name,
			GalaxyID* userArray,
			uint32_t userArraySize,
			ILeaderboardEntriesRetrieveListener* const listener) {

		}

		void StatsImpl::GetRequestedLeaderboardEntry(uint32_t index, uint32_t& rank, int32_t& score, GalaxyID& userID) {

		}

		void StatsImpl::GetRequestedLeaderboardEntryWithDetails(
			uint32_t index,
			uint32_t& rank,
			int32_t& score,
			void* details,
			uint32_t detailsSize,
			uint32_t& outDetailsSize,
			GalaxyID& userID) {

		}

		void StatsImpl::SetLeaderboardScore(
			const char* name,
			int32_t score,
			bool forceUpdate,
			ILeaderboardScoreUpdateListener* const listener) {

		}

		void StatsImpl::SetLeaderboardScoreWithDetails(
			const char* name,
			int32_t score,
			const void* details,
			uint32_t detailsSize,
			bool forceUpdate,
			ILeaderboardScoreUpdateListener* const listener) {

		}

		uint32_t StatsImpl::GetLeaderboardEntryCount(const char* name) {
			return 0;
		}

		void StatsImpl::FindLeaderboard(const char* name, ILeaderboardRetrieveListener* const listener) {

		}

		void StatsImpl::FindOrCreateLeaderboard(
			const char* name,
			const char* displayName,
			const LeaderboardSortMethod& sortMethod,
			const LeaderboardDisplayType& displayType,
			ILeaderboardRetrieveListener* const listener) {

		}

		void StatsImpl::RequestUserTimePlayed(GalaxyID userID, IUserTimePlayedRetrieveListener* const listener) {

		}

		uint32_t StatsImpl::GetUserTimePlayed(GalaxyID userID) {
			return 0;
		}
	}
}


