#pragma once

#include <GalaxyApi.h>

#include <Networking/Messages/KeyChallengeMessage.hxx>

#include <cstdint>

namespace universelan::server {
	struct Challenge {
		bool completed;
		uint64_t data;
		KeyChallengeMessage for_client;
		KeyChallengeMessage expected_response;

		Challenge();

		KeyChallengeMessage& Prepare(uint64_t key, uint64_t rnd);
		bool Validate(const KeyChallengeMessage& response);
	};
}
