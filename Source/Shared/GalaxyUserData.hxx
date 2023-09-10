#pragma once

#include <GalaxyID.h>

#include <AchievementsAndStatsContainer.hxx>
#include <GalaxyIDHash.hxx>

#include <memory>
#include <string>
#include <unordered_map>

namespace universelan {
	class GalaxyUserData {
	public:
		using ptr_t = std::shared_ptr<GalaxyUserData>;
		using map_t = std::unordered_map<galaxy::api::GalaxyID, ptr_t, universelan::GalaxyIDHash>;

		GalaxyUserData(galaxy::api::GalaxyID id);

		const galaxy::api::GalaxyID id;

		AchievementsAndStatsContainer stats;
		std::string nickname;
		bool online;
	};
}
