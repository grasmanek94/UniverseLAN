#pragma once

#include "AchievementData.hxx"

#include <functional>
#include <mutex>
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
private:
	using mutex_t = std::recursive_mutex;
	using lock_t = std::scoped_lock<mutex_t>;

	mutex_t mtx_achievements;
	mutex_t mtx_stats;
	mutex_t mtx_userdata;
public:
	template <typename T>
	using map_t = std::unordered_map<std::string, T>;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(Achievements, Stats, UserData);
	}

	map_t<AchievementData> Achievements;
	map_t<StatsDataContainer> Stats;
	map_t<std::string> UserData;

	AchievementsAndStatsContainer() 
		: mtx_achievements{}, mtx_stats{}, mtx_userdata{},
		  Achievements {}, Stats{}, UserData{}
	{}

	inline void run_locked_achievements(std::function<void(map_t<AchievementData>&)> func) {
		lock_t lock(mtx_achievements);
		func(Achievements);
	}

	inline void run_locked_stats(std::function<void(map_t<StatsDataContainer>&)> func) {
		lock_t lock(mtx_achievements);
		func(Stats);
	}

	inline void run_locked_userdata(std::function<void(map_t<std::string>&)> func) {
		lock_t lock(mtx_achievements);
		func(UserData);
	}

	AchievementsAndStatsContainer& operator=(const AchievementsAndStatsContainer& other)
	{
		this->Achievements = other.Achievements;
		this->Stats = other.Stats;
		this->UserData = other.UserData;
		return *this;
	}
};
