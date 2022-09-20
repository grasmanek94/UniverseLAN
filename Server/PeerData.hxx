#pragma once

#include <GalaxyApi.h>

#include <Networking/Networking.hxx>
#include <GalaxyUserData.hxx>

#include <cstdint>
#include <chrono>

namespace universelan::server {
	class PeerData {
	private:
		PeerData();

	public:
		using map_t = std::unordered_map<galaxy::api::GalaxyID, ENetPeer*, galaxy::api::GalaxyID::Hash>;

		struct Challenge {
			bool completed;
			uint64_t data;
			KeyChallengeMessage for_client;
			KeyChallengeMessage expected_response;

			Challenge();

			KeyChallengeMessage& Prepare(uint64_t key, uint64_t rnd);
			bool Validate(const KeyChallengeMessage& response);
		};

		ENetPeer* peer;
		galaxy::api::GalaxyID id;
		Challenge challenge;
		std::chrono::system_clock::time_point connected_time;
		GalaxyUserData::ptr_t user_data;

		virtual ~PeerData();

		static PeerData* get(ENetPeer* peer);
		static PeerData* get(const galaxy::api::GalaxyID& id, const map_t& map);
		static bool link(ENetPeer* peer, const galaxy::api::GalaxyID& id, map_t& map);
		static PeerData* construct(ENetPeer* peer);
		static void destruct(ENetPeer* peer, map_t& map);
	};
}
