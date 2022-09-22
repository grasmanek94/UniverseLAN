#include "Challenge.hxx"

#include <cstdint>

namespace universelan::server {
	Challenge::Challenge() 
		: completed{ false }, data{ 0ULL }, for_client{}, expected_response{} 
	{}

	KeyChallengeMessage& Challenge::Prepare(uint64_t key, uint64_t rnd) {
		data = rnd;
		for_client = KeyChallengeMessage{}.challenge(key, data);
		expected_response = KeyChallengeMessage{}.response(key, for_client.encrypted);

		return for_client;
	}

	bool Challenge::Validate(const KeyChallengeMessage& response) {
		completed = (response.encrypted == expected_response.encrypted);
		return completed;
	}
}
