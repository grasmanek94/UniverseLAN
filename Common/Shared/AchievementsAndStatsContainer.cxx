#pragma once

#include "AchievementsAndStatsContainer.hxx"

#include <chrono>
#include <functional>

namespace universelan {
	AchievementsAndStatsContainer::AchievementsAndStatsContainer()
		: mtx_achievements{}, mtx_stats{}, mtx_userdata{},
		Achievements{}, Stats{}, UserData{},
		BootTime{ std::chrono::system_clock::now() }, PlayTime{ 0 }
	{}

	AchievementsAndStatsContainer::AchievementsAndStatsContainer(const AchievementsAndStatsContainer& other)
		: mtx_achievements{}, mtx_stats{}, mtx_userdata{},
		Achievements{ other.Achievements }, Stats{ other.Stats }, UserData{ other.UserData },
		BootTime{ other.BootTime }, PlayTime{ other.PlayTime }
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

		return *this;
	}
}