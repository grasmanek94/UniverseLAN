#pragma once

#include <GalaxyID.h>

#include <cstddef>
#include <cstdint>
#include <functional>

namespace universelan {
	struct GalaxyIDHash {
		std::size_t operator()(const galaxy::api::GalaxyID& k) const
		{
			return std::hash<uint64_t>()(k.GetRealID());
		}
	};
}
