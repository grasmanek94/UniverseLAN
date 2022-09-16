#pragma once

#include <GalaxyApi.h>

#include <AchievementsAndStatsContainer.hxx>

#include <unordered_map>

class GalaxyUserData {
public:
	struct Hash {
		std::size_t operator()(const galaxy::api::GalaxyID& k) const
		{
			return std::hash<uint64_t>()(k.ToUint64());
		}
	};

	using map_t = std::unordered_map<galaxy::api::GalaxyID, GalaxyUserData, Hash>;

	GalaxyUserData(galaxy::api::GalaxyID id);

	const galaxy::api::GalaxyID id;
	AchievementsAndStatsContainer stats;
};
