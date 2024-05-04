#include "Stats.hxx"

#include <Tracer.hxx>
#include <GalaxyDLL.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;
	StatsImpl::StatsImpl(InterfaceInstances* intf) : intf{ intf }
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };
	}

	StatsImpl::~StatsImpl()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };
	}

	void StatsImpl::RequestUserStatsAndAchievements(GalaxyID userID
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, IUserStatsAndAchievementsRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Stats()->RequestUserStatsAndAchievements(userID
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);
	}

	int32_t StatsImpl::GetStatInt(const char* name, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Stats()->GetStatInt(name, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	float StatsImpl::GetStatFloat(const char* name, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Stats()->GetStatFloat(name, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void StatsImpl::SetStatInt(const char* name, int32_t value) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("value: {}", value));
		}

		RealGalaxyDLL_Stats()->SetStatInt(name, value);
	}

	void StatsImpl::SetStatFloat(const char* name, float value) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("value: {}", value));
		}

		RealGalaxyDLL_Stats()->SetStatFloat(name, value);
	}

	void StatsImpl::UpdateAvgRateStat(const char* name, float countThisSession, double sessionLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("countThisSession: {}", countThisSession));
			trace.write_all(std::format("sessionLength: {}", sessionLength));
		}

		RealGalaxyDLL_Stats()->UpdateAvgRateStat(name, countThisSession, sessionLength);
	}

	void StatsImpl::GetAchievement(const char* name, bool& unlocked, uint32_t& unlockTime, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("userID: {}", userID));
		}

		RealGalaxyDLL_Stats()->GetAchievement(name, unlocked, unlockTime, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("unlocked: {}", unlocked));
			trace.write_all(std::format("unlockTime: {}", unlockTime));
		}
	}

	void StatsImpl::SetAchievement(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		RealGalaxyDLL_Stats()->SetAchievement(name);
	}

	void StatsImpl::ClearAchievement(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		RealGalaxyDLL_Stats()->ClearAchievement(name);
	}

	void StatsImpl::StoreStatsAndAchievements(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		IStatsAndAchievementsStoreListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif

		}

		RealGalaxyDLL_Stats()->StoreStatsAndAchievements();
	}

	void StatsImpl::ResetStatsAndAchievements(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		IStatsAndAchievementsStoreListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif

		}

		RealGalaxyDLL_Stats()->ResetStatsAndAchievements(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener
#endif
		);
	}

	const char* StatsImpl::GetAchievementDisplayName(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		auto result = RealGalaxyDLL_Stats()->GetAchievementDisplayName(name);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_ISTATS_GET_ACHIEVEMENT_LEADERBOARD_COPY
	void StatsImpl::GetAchievementDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		RealGalaxyDLL_Stats()->GetAchievementDisplayNameCopy(name, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

	const char* StatsImpl::GetAchievementDescription(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		auto result = RealGalaxyDLL_Stats()->GetAchievementDescription(name);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_ISTATS_GET_ACHIEVEMENT_LEADERBOARD_COPY
	void StatsImpl::GetAchievementDescriptionCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		RealGalaxyDLL_Stats()->GetAchievementDescriptionCopy(name, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

	bool StatsImpl::IsAchievementVisible(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		auto result = RealGalaxyDLL_Stats()->IsAchievementVisible(name);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_ISTATS_UPDATE_1_127_0
	bool StatsImpl::IsAchievementVisibleWhileLocked(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		auto result = RealGalaxyDLL_Stats()->IsAchievementVisibleWhileLocked(name);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

	void StatsImpl::RequestLeaderboards(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		ILeaderboardsRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif

		}

		RealGalaxyDLL_Stats()->RequestLeaderboards(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener
#endif	
		);
	}

	const char* StatsImpl::GetLeaderboardDisplayName(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		auto result = RealGalaxyDLL_Stats()->GetLeaderboardDisplayName(name);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_ISTATS_GET_ACHIEVEMENT_LEADERBOARD_COPY
	void StatsImpl::GetLeaderboardDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		RealGalaxyDLL_Stats()->GetLeaderboardDisplayNameCopy(name, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

	LeaderboardSortMethod StatsImpl::GetLeaderboardSortMethod(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		auto result = RealGalaxyDLL_Stats()->GetLeaderboardSortMethod(name);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}

	LeaderboardDisplayType StatsImpl::GetLeaderboardDisplayType(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		auto result = RealGalaxyDLL_Stats()->GetLeaderboardDisplayType(name);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}

	void StatsImpl::RequestLeaderboardEntriesGlobal(
		const char* name
		, uint32_t rangeStart
		, uint32_t rangeEnd
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardEntriesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("rangeStart: {}", rangeStart));
			trace.write_all(std::format("rangeEnd: {}", rangeEnd));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Stats()->RequestLeaderboardEntriesGlobal(name, rangeStart, rangeEnd
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);
	}

	void StatsImpl::RequestLeaderboardEntriesAroundUser(
		const char* name
		, uint32_t countBefore
		, uint32_t countAfter
		, GalaxyID userID
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardEntriesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("countBefore: {}", countBefore));
			trace.write_all(std::format("countAfter: {}", countAfter));
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Stats()->RequestLeaderboardEntriesAroundUser(name, countBefore, countAfter, userID
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);
	}

	void StatsImpl::RequestLeaderboardEntriesForUsers(
		const char* name
		, GalaxyID* userArray
		, uint32_t userArraySize
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardEntriesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("userArray: {}", (void*)userArray));
			trace.write_all(std::format("userArraySize: {}", userArraySize));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
			if ((userArray != nullptr) && (userArraySize > 0)) {
				for (uint32_t i = 0; i < userArraySize; ++i) {
					trace.write_all(std::format("userArray[{}]: {}", i, userArray[i]));
				}
			}
		}

		RealGalaxyDLL_Stats()->RequestLeaderboardEntriesForUsers(name, userArray, userArraySize
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);
	}

	void StatsImpl::GetRequestedLeaderboardEntry(uint32_t index, uint32_t& rank, int32_t& score, GalaxyID& userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };
		
		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		RealGalaxyDLL_Stats()->GetRequestedLeaderboardEntry(index, rank, score, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("rank: {}", rank));
			trace.write_all(std::format("score: {}", score));
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void StatsImpl::SetLeaderboardScore(
		const char* name
		, int32_t score
		, bool forceUpdate
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardScoreUpdateListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("score: {}", score));
			trace.write_all(std::format("forceUpdate: {}", forceUpdate));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Stats()->SetLeaderboardScore(name, score, forceUpdate
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);
	}

#if GALAXY_BUILD_FEATURE_HAS_LEADERBOARD_WITH_DETAILS
	void StatsImpl::GetRequestedLeaderboardEntryWithDetails(
		uint32_t index,
		uint32_t& rank,
		int32_t& score,
		void* details,
		uint32_t detailsSize,
		uint32_t& outDetailsSize,
		GalaxyID& userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("details: {}", details));
			trace.write_all(std::format("detailsSize: {}", detailsSize));
		}

		RealGalaxyDLL_Stats()->GetRequestedLeaderboardEntryWithDetails(index, rank, score, details, detailsSize, outDetailsSize, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("rank: {}", rank));
			trace.write_all(std::format("score: {}", score));
			trace.write_all(std::format("outDetailsSize: {}", outDetailsSize));
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void StatsImpl::SetLeaderboardScoreWithDetails(
		const char* name
		, int32_t score
		, const void* details
		, uint32_t detailsSize
		, bool forceUpdate
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardScoreUpdateListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("score: {}", score));
			trace.write_all(std::format("details: {}", details));
			trace.write_all(std::format("detailsSize: {}", detailsSize));
			trace.write_all(std::format("forceUpdate: {}", forceUpdate));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Stats()->SetLeaderboardScoreWithDetails(name, score, details, detailsSize, forceUpdate
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);
	}
#endif

	uint32_t StatsImpl::GetLeaderboardEntryCount(const char* name) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		auto result = RealGalaxyDLL_Stats()->GetLeaderboardEntryCount(name);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_HAS_ILEADERBOARDRETRIEVELISTENER
	void StatsImpl::FindLeaderboard(const char* name
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Stats()->FindLeaderboard(name
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);
	}

	void StatsImpl::FindOrCreateLeaderboard(
		const char* name
		, const char* displayName
		, const LeaderboardSortMethod& sortMethod
		, const LeaderboardDisplayType& displayType
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("displayName: {}", util::safe_fix_null_char_ptr_annotate_ret(displayName)));
			trace.write_all(std::format("sortMethod: {}", magic_enum::enum_name(sortMethod)));
			trace.write_all(std::format("displayType: {}", magic_enum::enum_name(displayType)));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Stats()->FindOrCreateLeaderboard(name, displayName, sortMethod, displayType
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("sortMethod: {}", magic_enum::enum_name(sortMethod)));
			trace.write_all(std::format("displayType: {}", magic_enum::enum_name(displayType)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
	void StatsImpl::RequestUserTimePlayed(GalaxyID userID
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, IUserTimePlayedRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Stats()->RequestUserTimePlayed(userID
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			, listener
#endif	
		);
	}

	uint32_t StatsImpl::GetUserTimePlayed(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Stats()->GetUserTimePlayed(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif
}
