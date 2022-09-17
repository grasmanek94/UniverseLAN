#pragma once

#include <GalaxyID.h>

#include <AchievementsAndStatsContainer.hxx>

#include <memory>
#include <unordered_map>

class GalaxyUserData {
public:
	struct Hash {
		std::size_t operator()(const galaxy::api::GalaxyID& k) const
		{
			return std::hash<uint64_t>()(k.ToUint64());
		}
	};

	using map_t = std::unordered_map<galaxy::api::GalaxyID, std::shared_ptr<GalaxyUserData>, Hash>;

	GalaxyUserData(galaxy::api::GalaxyID id);

	const galaxy::api::GalaxyID id;
	AchievementsAndStatsContainer stats;
};
