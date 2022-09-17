#pragma once

#include <GalaxyID.h>

#include <AchievementsAndStatsContainer.hxx>

#include <memory>
#include <unordered_map>

namespace universelan {
	using namespace galaxy::api;
	class GalaxyUserData {
	public:
		using map_t = std::unordered_map<GalaxyID, std::shared_ptr<GalaxyUserData>, GalaxyID::Hash>;

		GalaxyUserData(galaxy::api::GalaxyID id);

		const galaxy::api::GalaxyID id;
		AchievementsAndStatsContainer stats;
	};
}