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

namespace galaxy::api {

#if GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
	using IDType = GalaxyID::IDType;
#else
	enum IDType {
		ID_TYPE_UNASSIGNED,
		ID_TYPE_LOBBY,
		ID_TYPE_USER
	};
#endif

	static GalaxyID FromRealID(IDType type, uint64_t value)
	{
		/**
		 * The numerical value used when the instance of GalaxyID is not valid.
		 */
		static const uint64_t UNASSIGNED_VALUE = 0;

		assert(type != IDType::ID_TYPE_UNASSIGNED);
		assert(value != UNASSIGNED_VALUE);
		assert(static_cast<IDType>(value >> 56) == IDType::ID_TYPE_UNASSIGNED);
		return GalaxyID(static_cast<uint64_t>(type) << 56 | value);
	}
}