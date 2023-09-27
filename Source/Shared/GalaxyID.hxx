#pragma once

#include <GalaxyID.h>

#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <magic_enum/magic_enum.hpp>

namespace universelan {
	struct GalaxyIDHash {
		std::size_t operator()(const galaxy::api::GalaxyID& k) const
		{
			return std::hash<uint64_t>()(k.ToUint64());
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
	/**
	 * Returns the type of the ID.
	 *
	 * @return The type of the ID.
	 */
	inline IDType GetIDType(uint64_t value)
	{
		return static_cast<IDType>(value >> 56);
	}

	/**
	 * Returns the type of the ID.
	 *
	 * @return The type of the ID.
	 */
	inline IDType GetIDType(GalaxyID value)
	{
		return static_cast<IDType>(value.ToUint64() >> 56);
	}

	inline GalaxyID FromRealID(IDType type, uint64_t value)
	{
		return GalaxyID(static_cast<uint64_t>(type) << 56 | (value & 0xffffffffffffff));
	}
}

template <>
struct std::formatter<galaxy::api::GalaxyID> : std::formatter<std::string> {
	auto format(galaxy::api::GalaxyID p, format_context& ctx) const {
		return formatter<string>::format(
			std::format("{}({})", p.GetRealID(), magic_enum::enum_name(galaxy::api::GetIDType(p))), ctx);
	}
};
