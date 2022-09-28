#pragma once

#include "AchievementData.hxx"

#include <chrono>
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
	public:
		template <typename T>
		using map_t = std::unordered_map<std::string, T>;
		using achievements_t = map_t<AchievementData>;
		using stats_t = map_t<StatsDataContainer>;
		using user_data_t = map_t<std::string>;
		using time_point = std::chrono::system_clock::time_point;

	private:
		using mutex_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mutex_t>;

		mutex_t mtx_achievements;
		mutex_t mtx_stats;
		mutex_t mtx_userdata;

		achievements_t Achievements;
		stats_t Stats;
		user_data_t UserData;
		time_point BootTime;
		uint32_t PlayTime;

	public:

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(Achievements, Stats, UserData, BootTime, PlayTime);
		}

		AchievementsAndStatsContainer();
		AchievementsAndStatsContainer(const AchievementsAndStatsContainer& other);

		template<typename T>
		T run_locked_achievements(std::function<T(map_t<AchievementData>&)> func) {
			lock_t lock(mtx_achievements);
			return func(Achievements);
		}

		template<typename T>
		T  run_locked_stats(std::function<T(map_t<StatsDataContainer>&)> func) {
			lock_t lock(mtx_stats);
			return func(Stats);
		}

		template<typename T>
		T  run_locked_userdata(std::function<T(map_t<std::string>&)> func) {
			lock_t lock(mtx_userdata);
			return func(UserData);
		}

		void SetPlayTime(uint32_t play_time);
		uint32_t GetPlayTime() const;

		AchievementsAndStatsContainer& operator=(const AchievementsAndStatsContainer& other);
	};
}