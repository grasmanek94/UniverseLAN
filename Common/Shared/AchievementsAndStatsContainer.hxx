#pragma once

#include "AchievementData.hxx"

#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>

namespace universelan {
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
		using achievements_t = map_t<AchievementData>;
		using stats_t = map_t<StatsDataContainer>;
		using user_data_t = map_t<std::string>;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(Achievements, Stats, UserData);
		}

		achievements_t Achievements;
		stats_t Stats;
		user_data_t UserData;

		AchievementsAndStatsContainer()
			: mtx_achievements{}, mtx_stats{}, mtx_userdata{},
			Achievements{}, Stats{}, UserData{}
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
}