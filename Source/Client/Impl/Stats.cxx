#include "Stats.hxx"

#include "UniverseLAN.hxx"

namespace universelan::client {
	using namespace galaxy::api;
	StatsImpl::StatsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		specific_user_stats_and_achievements_requests{},
		specific_user_time_played_requests{}
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	StatsImpl::~StatsImpl()
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	void StatsImpl::RequestUserStatsAndAchievements(GalaxyID userID
#if (GALAXY_VERSION) > 112400
		, IUserStatsAndAchievementsRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
				listener,
#endif
				&IUserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveSuccess, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 112400
			specific_user_stats_and_achievements_requests.emplace(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeAchievementsAndStats, request_id, userID });
		}
	}

	void StatsImpl::SpecificUserStatsAndAchievementsRequestProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		IUserStatsAndAchievementsRetrieveListener* listener = specific_user_stats_and_achievements_requests.pop(data->request_id);

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;

			listeners->NotifyAll(listener, &IUserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveSuccess, data->id);
		}
		else {
			listeners->NotifyAll(listener, &IUserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveFailure, data->id, IUserStatsAndAchievementsRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	int32_t StatsImpl::GetStatInt(const char* name, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->stats.GetStat(name).i;
	}

	float StatsImpl::GetStatFloat(const char* name, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->stats.GetStat(name).f;
	}

	void StatsImpl::SetStatInt(const char* name, int32_t value) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.SetStat(name, value);
	}

	void StatsImpl::SetStatFloat(const char* name, float value) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.SetStat(name, value);
	}

	void StatsImpl::UpdateAvgRateStat(const char* name, float countThisSession, double sessionLength) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.SetStat(name, (float)(intf->config->GetLocalUserData()->stats.GetStat(name).f + (countThisSession / sessionLength)));
	}

	void StatsImpl::GetAchievement(const char* name, bool& unlocked, uint32_t& unlockTime, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		auto* data = intf->user->GetGalaxyUserData(userID)->stats.GetAchievementData(name);

		if (data) {
			unlocked = data->GetUnlocked();
			unlockTime = data->GetUnlockTime();
		}
	}

	void StatsImpl::SetAchievement(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);

		if (data) {
			data->SetUnlocked(true);
			data->SetUnlockTimeNow();
		}

		listeners->NotifyAll(&IAchievementChangeListener::OnAchievementUnlocked, name);
	}

	void StatsImpl::ClearAchievement(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);
		if (data) {
			data->SetUnlocked(false);
			data->SetUnlockTime(0);
		}
	}

	void StatsImpl::StoreStatsAndAchievements(
#if (GALAXY_VERSION) > 112400
		IStatsAndAchievementsStoreListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->SaveStatsAndAchievements();

		intf->client->GetConnection().SendAsync(UserHelloDataMessage{ intf->config->GetLocalUserData()->stats });

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&IStatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreSuccess);
	}

	void StatsImpl::ResetStatsAndAchievements(
#if (GALAXY_VERSION) > 112400
		IStatsAndAchievementsStoreListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->ResetStatsAndAchievements();

		intf->client->GetConnection().SendAsync(UserHelloDataMessage{ intf->config->GetLocalUserData()->stats });

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&IStatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreSuccess);
	}

	const char* StatsImpl::GetAchievementDisplayName(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		return name;
	}

	void StatsImpl::GetAchievementDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::copy_n(name, std::min(bufferLength, (uint32_t)strlen(name)), buffer);
	}

	const char* StatsImpl::GetAchievementDescription(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);
		if (data) {
			return data->GetDescription().c_str();
		}

		return "";
	}

	void StatsImpl::GetAchievementDescriptionCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);

		if (data) {
			const std::string& desc = data->GetDescription();
			std::copy_n(desc.c_str(), std::min(bufferLength, (uint32_t)desc.size()), buffer);
		}
	}

	bool StatsImpl::IsAchievementVisible(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);

		if (data) {
			return data->GetVisible();
		}

		return false;
	}

#if (GALAXY_VERSION) > 112400
	bool StatsImpl::IsAchievementVisibleWhileLocked(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		auto* data = intf->config->GetLocalUserData()->stats.GetAchievementData(name);

		if (data) {
			return data->GetVisibleWhileLocked();
		}

		return false;
	}
#endif

	void StatsImpl::RequestLeaderboards(
#if (GALAXY_VERSION) > 112400
		ILeaderboardsRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&ILeaderboardsRetrieveListener::OnLeaderboardsRetrieveFailure, ILeaderboardsRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	const char* StatsImpl::GetLeaderboardDisplayName(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		return name;
	}

	void StatsImpl::GetLeaderboardDisplayNameCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::copy_n(name, std::min(bufferLength, (uint32_t)strlen(name)), buffer);
	}

	LeaderboardSortMethod StatsImpl::GetLeaderboardSortMethod(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		return LEADERBOARD_SORT_METHOD_NONE;
	}

	LeaderboardDisplayType StatsImpl::GetLeaderboardDisplayType(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		return LEADERBOARD_DISPLAY_TYPE_NONE;
	}

	void StatsImpl::RequestLeaderboardEntriesGlobal(
		const char* name
		, uint32_t rangeStart
		, uint32_t rangeEnd
#if (GALAXY_VERSION) > 112400
		, ILeaderboardEntriesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::RequestLeaderboardEntriesAroundUser(
		const char* name
		, uint32_t countBefore
		, uint32_t countAfter
		, GalaxyID userID
#if (GALAXY_VERSION) > 112400
		, ILeaderboardEntriesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::RequestLeaderboardEntriesForUsers(
		const char* name
		, GalaxyID* userArray
		, uint32_t userArraySize
#if (GALAXY_VERSION) > 112400
		, ILeaderboardEntriesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener, 
#endif
			&ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::GetRequestedLeaderboardEntry(uint32_t index, uint32_t& rank, int32_t& score, GalaxyID& userID) {
		tracer::Trace trace{ __FUNCTION__ };
	}

	void StatsImpl::GetRequestedLeaderboardEntryWithDetails(
		uint32_t index,
		uint32_t& rank,
		int32_t& score,
		void* details,
		uint32_t detailsSize,
		uint32_t& outDetailsSize,
		GalaxyID& userID) {
		tracer::Trace trace{ __FUNCTION__ };
	}

	void StatsImpl::SetLeaderboardScore(
		const char* name
		, int32_t score
		, bool forceUpdate
#if (GALAXY_VERSION) > 112400
		, ILeaderboardScoreUpdateListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&ILeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateFailure, name, score, ILeaderboardScoreUpdateListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::SetLeaderboardScoreWithDetails(
		const char* name
		, int32_t score
		, const void* details
		, uint32_t detailsSize
		, bool forceUpdate
#if (GALAXY_VERSION) > 112400
		, ILeaderboardScoreUpdateListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener, 
#endif
			&ILeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateFailure, name, score, ILeaderboardScoreUpdateListener::FAILURE_REASON_UNDEFINED);
	}

	uint32_t StatsImpl::GetLeaderboardEntryCount(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void StatsImpl::FindLeaderboard(const char* name
#if (GALAXY_VERSION) > 112400
		, ILeaderboardRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener, 
#endif
			&ILeaderboardRetrieveListener::OnLeaderboardRetrieveFailure, name, ILeaderboardRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::FindOrCreateLeaderboard(
		const char* name
		, const char* displayName
		, const LeaderboardSortMethod& sortMethod
		, const LeaderboardDisplayType& displayType
#if (GALAXY_VERSION) > 112400
		, ILeaderboardRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener, 
#endif
			&ILeaderboardRetrieveListener::OnLeaderboardRetrieveFailure, name, ILeaderboardRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::RequestUserTimePlayed(GalaxyID userID
#if (GALAXY_VERSION) > 112400
		, IUserTimePlayedRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		// no need to refresh play time because it's the diff between 'submitted_time_played + (time_now - connect_time)'
		if (intf->user->IsGalaxyUserDataPresent(userID)) {
			listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
				listener, 
#endif
				&IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 112400
			specific_user_time_played_requests.emplace(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypePlayTime, request_id, userID });
		}
	}

	void StatsImpl::RequestUserTimePlayedProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		IUserTimePlayedRetrieveListener* listener = specific_user_time_played_requests.pop(data->request_id);

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;

			listeners->NotifyAll(listener, &IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess, data->id);
		}
		else {
			listeners->NotifyAll(listener, &IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveFailure, data->id, IUserTimePlayedRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	uint32_t StatsImpl::GetUserTimePlayed(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->stats.GetPlayTime();
	}
}
