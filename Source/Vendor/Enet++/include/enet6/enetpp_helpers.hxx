#pragma once

#ifndef ENETPP_HELPERS_HEADER
#define ENETPP_HELPERS_HEADER

#include <enet6/enet.h>

#include <format>
#include <ostream>
#include <string>

extern "C" {
	ENET_API void enet_host_broadcast_except(ENetHost*, enet_uint8, ENetPacket*, ENetPeer*);
}

// REVIEW: The custom broadcast helper is an ABI-visible declaration but does
// not document ownership on failure or null-argument behavior. Its implementation
// may destroy the packet when no peer accepts it; callers need one clear ownership
// contract to avoid leaks/double frees.
template <>
struct std::formatter<ENetAddress> : std::formatter<std::string> {
	auto format(const ENetAddress& p, std::format_context& ctx) const {
		switch (p.type) {
		case ENET_ADDRESS_TYPE_IPV4:
			return formatter<std::string>::format(
				std::format("{:d}.{:d}.{:d}.{:d}:{:d}",
					p.host.v4[0], p.host.v4[1], p.host.v4[2], p.host.v4[3], p.port),
				ctx);
		case ENET_ADDRESS_TYPE_IPV6:
			return formatter<std::string>::format(
				std::format("[{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}]:{:d}",
					p.host.v6[0], p.host.v6[1], p.host.v6[2], p.host.v6[3], p.host.v6[4], p.host.v6[5], p.host.v6[6], p.host.v6[7], p.port),
				ctx);
		case ENET_ADDRESS_TYPE_ANY:
			return formatter<std::string>::format(
				std::format("IPv6:[{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}:{:04x}]:{:d} | IPv4:{:d}.{:d}.{:d}.{:d}:{:d}",
					p.host.v6[0], p.host.v6[1], p.host.v6[2], p.host.v6[3], p.host.v6[4], p.host.v6[5], p.host.v6[6], p.host.v6[7], p.port,
					p.host.v4[0], p.host.v4[1], p.host.v4[2], p.host.v4[3], p.port),
				ctx);
		default:
			throw std::format_error("Unkown ENET_ADDRESS_TYPE");
		}
	}
};

inline std::ostream& operator << (std::ostream& os, const ENetAddress& p)
{
	os << std::format("{}", p);

	return os;
}

#endif /* ENETPP_HELPERS_HEADER */