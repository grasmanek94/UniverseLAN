#include "AchievementsAndStatsContainer.hxx"

#include <chrono>
#include <functional>

namespace universelan {
	AchievementsAndStatsContainer::AchievementsAndStatsContainer()
		: mtx_achievements{}, mtx_stats{}, mtx_userdata{}, mtx_richpresence{},
		Achievements{}, Stats{}, UserData{},
		BootTime{ std::chrono::system_clock::now() }, PlayTime{ 0 },
		RichPresence{}
	{}

	AchievementsAndStatsContainer::AchievementsAndStatsContainer(const AchievementsAndStatsContainer& other)
		: mtx_achievements{}, mtx_stats{}, mtx_userdata{}, mtx_richpresence{},
		Achievements{ other.Achievements }, Stats{ other.Stats }, UserData{ other.UserData },
		BootTime{ other.BootTime }, PlayTime{ other.PlayTime },
		RichPresence{ other.RichPresence }
	{}

	void AchievementsAndStatsContainer::SetPlayTime(uint32_t play_time) {
		PlayTime = play_time;
	}

	uint32_t AchievementsAndStatsContainer::GetPlayTime() const
	{
		// cast the duration into seconds
		const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - BootTime);

		return PlayTime + (uint32_t)seconds.count();
	}

	AchievementsAndStatsContainer& AchievementsAndStatsContainer::operator=(const AchievementsAndStatsContainer& other)
	{
		this->Achievements = other.Achievements;
		this->Stats = other.Stats;
		this->UserData = other.UserData;
		this->BootTime = other.BootTime;
		this->PlayTime = other.PlayTime;
		this->RichPresence = other.RichPresence;

		return *this;
	}

	AchievementData* AchievementsAndStatsContainer::GetAchievementData(const std::string& name)
	{
		return run_locked_achievements<AchievementData*>([&](auto& Achievements) -> AchievementData* {
			auto it = Achievements.find(name);
			if (it == Achievements.end()) {
				AchievementData* data = &Achievements.emplace(name, AchievementData()).first->second;
				data->SetName(name);
				return data;
			}
			else {
				return &it->second;
			}
			});
	}

	const StatsDataContainer& AchievementsAndStatsContainer::GetStat(const std::string& name)
	{
		return run_locked_stats<const StatsDataContainer&>([&](auto& Stats) -> const StatsDataContainer& {
			auto it = Stats.find(name);
			if (it == Stats.end()) {
				return Stats.emplace(name, 0).first->second;
			}
			else {
				return it->second;
			}
			});
	}

	void AchievementsAndStatsContainer::SetStat(const std::string& name, int32_t value) {
		run_locked_stats<void>([&](auto& Stats) {
			auto it = Stats.find(name);
			if (it == Stats.end()) {
				StatsDataContainer c{ .i = value };
				it = Stats.emplace(name, c).first;
			}

			it->second.i = value;
			});
	}

	void AchievementsAndStatsContainer::SetStat(const std::string& name, float value) {
		run_locked_stats<void>([&](auto& Stats) {
			auto it = Stats.find(name);
			if (it == Stats.end()) {
				StatsDataContainer c{ .f = value };
				it = Stats.emplace(name, c).first;
			}

			it->second.f = value;
			});
	}

	const std::string& AchievementsAndStatsContainer::GetUserData(const std::string& name) {
		return run_locked_userdata<const std::string&>([&](auto& UserData) -> const std::string& {
			auto it = UserData.find(name);
			if (it == UserData.end()) {
				return UserData.emplace(name, "").first->second;
			}
			return it->second;
			});
	}

	void AchievementsAndStatsContainer::SetUserData(const std::string& name, const std::string& data) {
		run_locked_userdata<void>([&](auto& UserData) {
			auto it = UserData.find(name);
			if (it == UserData.end()) {
				UserData.emplace(name, data);
				return;
			}

			it->second = data;
			});
	}


	bool AchievementsAndStatsContainer::IsUserDataAvailable() {
		return run_locked_userdata<bool>([&](auto& map) -> bool {
			return !map.empty();
			});
	}

	const std::string& AchievementsAndStatsContainer::GetRichPresence(const std::string& name) {
		return run_locked_richpresence<const std::string&>([&](auto& RichPresence) -> const std::string& {
			auto it = RichPresence.find(name);
			if (it == RichPresence.end()) {
				return RichPresence.emplace(name, "").first->second;
			}
			return it->second;
			});
	}

	void AchievementsAndStatsContainer::SetRichPresence(const std::string& name, const std::string& data) {
		run_locked_richpresence<void>([&](auto& RichPresence) {
			auto it = RichPresence.find(name);
			if (it == RichPresence.end()) {
				RichPresence.emplace(name, data);
				return;
			}

			it->second = data;
			});
	}

	void AchievementsAndStatsContainer::EraseRichPresence(const std::string& name) {
		run_locked_richpresence<void>([&](auto& RichPresence) {
			RichPresence.erase(name);
			});
	}

	void AchievementsAndStatsContainer::ClearRichPresence() {
		run_locked_richpresence<void>([&](auto& RichPresence) {
			RichPresence.clear();
			});
	}

}