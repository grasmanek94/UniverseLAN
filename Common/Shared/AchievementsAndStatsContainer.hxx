#pragma once

#include "AchievementData.hxx"

#include <string>
#include <unordered_map>

union StatsDataContainer {
	int32_t i;
	float f;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(i);
	}
};

struct AchievementsAndStatsContainer {
	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(Achievements, Stats);
	}

	std::unordered_map<std::string, AchievementData> Achievements;
	std::unordered_map<std::string, StatsDataContainer> Stats;
	std::unordered_map<std::string, std::string> UserData;

	AchievementsAndStatsContainer() : Achievements{}, Stats{}, UserData{}
	{}
};
