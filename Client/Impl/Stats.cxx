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

	void StatsImpl::RequestUserStatsAndAchievements(GalaxyID userID, IUserStatsAndAchievementsRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(listener, &IUserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveSuccess, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

			specific_user_stats_and_achievements_requests.emplace(request_id, listener);
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

		return intf->user->GetGalaxyUserData(userID)->stats.run_locked_stats<uint32_t>([&](auto& stats) -> uint32_t {
			auto it = stats.find(name);
			if (it != stats.end()) {
				return it->second.i;
			}
			return 0;
			});
	}

	float StatsImpl::GetStatFloat(const char* name, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->stats.run_locked_stats<float>([&](auto& stats) -> float {
			auto it = stats.find(name);
			if (it != stats.end()) {
				return it->second.f;
			}
			return 0.0f;
			});
	}

	void StatsImpl::SetStatInt(const char* name, int32_t value) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->SetStat(name, value);
	}

	void StatsImpl::SetStatFloat(const char* name, float value) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->SetStat(name, value);
	}

	void StatsImpl::UpdateAvgRateStat(const char* name, float countThisSession, double sessionLength) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->SetStat(name, (float)(intf->config->GetStat(name).f + (countThisSession / sessionLength)));
	}

	void StatsImpl::GetAchievement(const char* name, bool& unlocked, uint32_t& unlockTime, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->user->GetGalaxyUserData(userID)->stats.run_locked_achievements<void>([&](auto& achievements) {
			auto it = achievements.find(name);
			if (it != achievements.end()) {
				unlocked = it->second.GetUnlocked();
				unlockTime = it->second.GetUnlockTime();
			}
			});
	}

	void StatsImpl::SetAchievement(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		auto data = intf->config->GetAchievementData(name);
		data->SetUnlocked(true);
		data->SetUnlockTimeNow();

		listeners->NotifyAll(&IAchievementChangeListener::OnAchievementUnlocked, name);
	}

	void StatsImpl::ClearAchievement(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		auto data = intf->config->GetAchievementData(name);
		data->SetUnlocked(false);
		data->SetUnlockTime(0);
	}

	void StatsImpl::StoreStatsAndAchievements(IStatsAndAchievementsStoreListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->SaveStatsAndAchievements();

		intf->client->GetConnection().SendAsync(UserHelloDataMessage{ intf->config->GetLocalUserData()->stats});

		listeners->NotifyAll(listener, &IStatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreSuccess);
	}

	void StatsImpl::ResetStatsAndAchievements(IStatsAndAchievementsStoreListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->ResetStatsAndAchievements();

		intf->client->GetConnection().SendAsync(UserHelloDataMessage{ intf->config->GetLocalUserData()->stats });

		listeners->NotifyAll(listener, &IStatsAndAchievementsStoreListener::OnUserStatsAndAchievementsStoreSuccess);
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

		return intf->config->GetAchievementData(name)->GetDescription().c_str();
	}

	void StatsImpl::GetAchievementDescriptionCopy(const char* name, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		const std::string& desc = intf->config->GetAchievementData(name)->GetDescription();
		std::copy_n(desc.c_str(), std::min(bufferLength, (uint32_t)desc.size()), buffer);
	}

	bool StatsImpl::IsAchievementVisible(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetAchievementData(name)->GetVisible();
	}

	bool StatsImpl::IsAchievementVisibleWhileLocked(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetAchievementData(name)->GetVisibleWhileLocked();
	}

	void StatsImpl::RequestLeaderboards(ILeaderboardsRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ILeaderboardsRetrieveListener::OnLeaderboardsRetrieveFailure, ILeaderboardsRetrieveListener::FAILURE_REASON_UNDEFINED);
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
		const char* name,
		uint32_t rangeStart,
		uint32_t rangeEnd,
		ILeaderboardEntriesRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::RequestLeaderboardEntriesAroundUser(
		const char* name,
		uint32_t countBefore,
		uint32_t countAfter,
		GalaxyID userID,
		ILeaderboardEntriesRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::RequestLeaderboardEntriesForUsers(
		const char* name,
		GalaxyID* userArray,
		uint32_t userArraySize,
		ILeaderboardEntriesRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ILeaderboardEntriesRetrieveListener::OnLeaderboardEntriesRetrieveFailure, name, ILeaderboardEntriesRetrieveListener::FAILURE_REASON_UNDEFINED);
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
		const char* name,
		int32_t score,
		bool forceUpdate,
		ILeaderboardScoreUpdateListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ILeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateFailure, name, score, ILeaderboardScoreUpdateListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::SetLeaderboardScoreWithDetails(
		const char* name,
		int32_t score,
		const void* details,
		uint32_t detailsSize,
		bool forceUpdate,
		ILeaderboardScoreUpdateListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ILeaderboardScoreUpdateListener::OnLeaderboardScoreUpdateFailure, name, score, ILeaderboardScoreUpdateListener::FAILURE_REASON_UNDEFINED);
	}

	uint32_t StatsImpl::GetLeaderboardEntryCount(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void StatsImpl::FindLeaderboard(const char* name, ILeaderboardRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ILeaderboardRetrieveListener::OnLeaderboardRetrieveFailure, name, ILeaderboardRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::FindOrCreateLeaderboard(
		const char* name,
		const char* displayName,
		const LeaderboardSortMethod& sortMethod,
		const LeaderboardDisplayType& displayType,
		ILeaderboardRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ILeaderboardRetrieveListener::OnLeaderboardRetrieveFailure, name, ILeaderboardRetrieveListener::FAILURE_REASON_UNDEFINED);
	}

	void StatsImpl::RequestUserTimePlayed(GalaxyID userID, IUserTimePlayedRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		// no need to refresh play time because it's the diff between 'submitted_time_played + (time_now - connect_time)'
		if (intf->user->IsGalaxyUserDataPresent(userID)) {
			listeners->NotifyAll(listener, &IUserTimePlayedRetrieveListener::OnUserTimePlayedRetrieveSuccess, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

			specific_user_time_played_requests.emplace(request_id, listener);
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
