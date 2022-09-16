#pragma once

#include "AchievementData.hxx"

#include <map>
#include <string>

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

	std::map<std::string, AchievementData> Achievements;
	std::map<std::string, StatsDataContainer> Stats;
	std::map<std::string, std::string> UserData;

	AchievementsAndStatsContainer() : Achievements{}, Stats{}, UserData{}
	{}
};
