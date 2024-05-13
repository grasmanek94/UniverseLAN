#include "Stats.hxx"

#include "UniverseLAN.hxx"

#include <SafeStringCopy.hxx>

namespace universelan::client {
	using namespace galaxy::api;
	StatsImpl::StatsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() }
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };
	}

	StatsImpl::~StatsImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };
	}

	void StatsImpl::RequestUserStatsAndAchievements(GalaxyID userID
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, IUserStatsAndAchievementsRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
				listener,
#endif
				&IUserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveSuccess, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listeners->AddRequestListener(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeAchievementsAndStats, request_id, userID });
		}
	}

	void StatsImpl::SpecificUserStatsAndAchievementsRequestProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		IUserStatsAndAchievementsRetrieveListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;

			listeners->NotifyAllNow(listener, &IUserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveSuccess, data->id);
		}
		else {
			listeners->NotifyAllNow(listener, &IUserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveFailure, data->id, IUserStatsAndAchievementsRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	int32_t StatsImpl::GetStatInt(const char* name, GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		return intf->user->GetGalaxyUserData(userID)->stats.GetStat(name).i;
	}

	float StatsImpl::GetStatFloat(const char* name, GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		return intf->user->GetGalaxyUserData(userID)->stats.GetStat(name).f;
	}

	void StatsImpl::SetStatInt(const char* name, int32_t value) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		intf->config->GetLocalUserData()->stats.SetStat(name, value);
	}

	void StatsImpl::SetStatFloat(const char* name, float value) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		intf->config->GetLocalUserData()->stats.SetStat(name, value);
	}

	void StatsImpl::UpdateAvgRateStat(const char* name, float countThisSession, double sessionLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		intf->config->GetLocalUserData()->stats.SetStat(name, (float)(intf->config->GetLocalUserData()->stats.GetStat(name).f + (countThisSession / sessionLength)));
	}

	void StatsImpl::GetAchievement(const char* name, bool& unlocked, uint32_t& unlockTime, GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		auto* data = intf->user->GetGalaxyUserData(userID)->stats.GetAchievementData(name);

		if (data) {
			unlocked = data->GetUnlocked();
			unlockTime = data->GetUnlockTime();
		}
	}

	void StatsImpl::SetAchievement(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);

		if (data) {
			data->SetUnlocked(true);
			data->SetUnlockTimeNow();
		}

		listeners->NotifyAll(&IAchievementChangeListener::OnAchievementUnlocked, name);
	}

	void StatsImpl::ClearAchievement(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);
		if (data) {
			data->SetUnlocked(false);
			data->SetUnlockTime(0);
		}
	}

	void StatsImpl::StoreStatsAndAchievements(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		IStatsAndAchievementsStoreListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		intf->config->SaveStatsAndAchievements();

		intf->client->GetConnection().SendAsync(UserHelloDataMessage{ intf->config->GetLocalUserData()->stats });

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener,
#endif
			&IStatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreSuccess);
	}

	void StatsImpl::ResetStatsAndAchievements(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		IStatsAndAchievementsStoreListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		intf->config->ResetStatsAndAchievements();

		intf->client->GetConnection().SendAsync(UserHelloDataMessage{ intf->config->GetLocalUserData()->stats });

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener,
#endif
			&IStatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreSuccess);
	}

	const char* StatsImpl::GetAchievementDisplayName(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		return name;
	}

#if GALAXY_BUILD_FEATURE_ISTATS_GET_ACHIEVEMENT_LEADERBOARD_COPY
	void StatsImpl::GetAchievementDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		universelan::util::safe_copy_str_n(name, buffer, bufferLength);
	}
#endif

	const char* StatsImpl::GetAchievementDescription(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);
		if (data) {
			return data->GetDescription().c_str();
		}

		return "";
	}

#if GALAXY_BUILD_FEATURE_ISTATS_GET_ACHIEVEMENT_LEADERBOARD_COPY
	void StatsImpl::GetAchievementDescriptionCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);

		if (data) {
			const std::string& desc = data->GetDescription();
			universelan::util::safe_copy_str_n(desc, buffer, bufferLength);
		}
	}
#endif

	bool StatsImpl::IsAchievementVisible(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);

		if (data) {
			return data->GetVisible();
		}

		return false;
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_ISTATS_UPDATE_1_127_0
	bool StatsImpl::IsAchievementVisibleWhileLocked(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);

		if (data) {
			return data->GetVisibleWhileLocked();
		}

		return false;
	}
#endif

	void StatsImpl::RequestLeaderboards(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		ILeaderboardsRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener,
#endif
			&ILeaderboardsRetrieveListener::OnLeaderboardsRetrieveFailure, ILeaderboardsRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	const char* StatsImpl::GetLeaderboardDisplayName(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		return name;
	}

#if GALAXY_BUILD_FEATURE_ISTATS_GET_ACHIEVEMENT_LEADERBOARD_COPY
	void StatsImpl::GetLeaderboardDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		universelan::util::safe_copy_str_n(name, buffer, bufferLength);
	}
#endif

	LeaderboardSortMethod StatsImpl::GetLeaderboardSortMethod(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		return LEADERBOARD_SORT_METHOD_NONE;
	}

	LeaderboardDisplayType StatsImpl::GetLeaderboardDisplayType(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		return LEADERBOARD_DISPLAY_TYPE_NONE;
	}

	void StatsImpl::RequestLeaderboardEntriesGlobal(
		const char* name
		, uint32_t rangeStart
		, uint32_t rangeEnd
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardEntriesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener,
#endif
			&ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
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
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener,
#endif
			&ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::RequestLeaderboardEntriesForUsers(
		const char* name
		, GalaxyID* userArray
		, uint32_t userArraySize
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardEntriesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener, 
#endif
			&ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::GetRequestedLeaderboardEntry(uint32_t index, uint32_t& rank, int32_t& score, GalaxyID& userID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };
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

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener,
#endif
			&ILeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateFailure, name, score, ILeaderboardScoreUpdateListener::FAILURE_REASON_UNDEFINED);
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
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener, 
#endif
			&ILeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateFailure, name, score, ILeaderboardScoreUpdateListener::FAILURE_REASON_UNDEFINED);
	}
#endif

	uint32_t StatsImpl::GetLeaderboardEntryCount(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		return 0;
	}

#if GALAXY_BUILD_FEATURE_HAS_ILEADERBOARDRETRIEVELISTENER
	void StatsImpl::FindLeaderboard(const char* name
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, ILeaderboardRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener, 
#endif
			&ILeaderboardRetrieveListener::OnLeaderboardRetrieveFailure, name, ILeaderboardRetrieveListener::FAILURE_REASON_UNDEFINED);
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
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listener, 
#endif
			&ILeaderboardRetrieveListener::OnLeaderboardRetrieveFailure, name, ILeaderboardRetrieveListener::FAILURE_REASON_UNDEFINED);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
	void StatsImpl::RequestUserTimePlayed(GalaxyID userID
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
		, IUserTimePlayedRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		// no need to refresh play time because it's the diff between 'submitted_time_played + (time_now - connect_time)'
		if (intf->user->IsGalaxyUserDataPresent(userID)) {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
				listener, 
#endif
				&IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
			listeners->AddRequestListener(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypePlayTime, request_id, userID });
		}
	}

	uint32_t StatsImpl::GetUserTimePlayed(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ISTATS };

		return intf->user->GetGalaxyUserData(userID)->stats.GetPlayTime();
	}
#endif

	void StatsImpl::RequestUserTimePlayedProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ISTATS };

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
		IUserTimePlayedRetrieveListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
			listeners->NotifyAllNow(listener, &IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess, data->id);
		}
		else {
			listeners->NotifyAllNow(listener, &IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveFailure, data->id, IUserTimePlayedRetrieveListener::FAILURE_REASON_UNDEFINED);
#endif
		}
	}
}
