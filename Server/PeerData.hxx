#pragma once

#include <GalaxyApi.h>

#include <Networking/Networking.hxx>

#include <cstdint>
#include <chrono>

namespace universelan::server {
	using namespace galaxy::api;
	class PeerData {
	private:
		PeerData();

	public:
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
		GalaxyID id;
		Challenge challenge;
		std::chrono::system_clock::time_point connected_time;

		virtual ~PeerData();

		static PeerData* get(ENetPeer* peer);
		static PeerData* construct(ENetPeer* peer);
		static void destruct(ENetPeer* peer);
	};
}