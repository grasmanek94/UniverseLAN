#include "PeerData.hxx"

#include <GalaxyApi.h>

#include <cstdint>
#include <chrono>

namespace universelan::server {
	using namespace galaxy::api;

	PeerData::PeerData() : peer{}, id{ 0ULL }, challenge{}, connected_time{ std::chrono::system_clock::now() }
	{}

	PeerData::Challenge::Challenge() : completed{ false }, data{ 0ULL }, for_client{}, expected_response{} {}

	KeyChallengeMessage& PeerData::Challenge::Prepare(uint64_t key, uint64_t rnd) {
		data = rnd;
		for_client = KeyChallengeMessage{}.challenge(key, data);
		expected_response = KeyChallengeMessage{}.response(key, for_client.encrypted);

		return for_client;
	}

	bool PeerData::Challenge::Validate(const KeyChallengeMessage& response) {
		completed = (response.encrypted == expected_response.encrypted);
		return completed;
	}

	PeerData::~PeerData() {}

	PeerData* PeerData::get(ENetPeer* peer) {
		assert(peer != nullptr);
		assert(peer->data != nullptr);

		return (PeerData*)peer->data;
	}

	PeerData* PeerData::get(const GalaxyID& id, const map_t& map) {
		auto it = map.find(id);
		if (it == map.end()) {
			return nullptr;
		}

		ENetPeer* peer = it->second;

		assert(peer != nullptr);
		assert(peer->data != nullptr);

		return (PeerData*)peer->data;
	}

	PeerData* PeerData::construct(ENetPeer* peer) {
		assert(peer != nullptr);
		assert(peer->data == nullptr);

		PeerData* peer_data = new PeerData();
		peer_data->peer = peer;
		peer->data = (void*)peer_data;

		return peer_data;
	}

	bool PeerData::link(ENetPeer* peer, const GalaxyID& id, map_t& map) {
		assert(peer != nullptr);
		assert(peer->data == nullptr);

		if (!id.IsValid()) {
			return false;
		}

		auto it = map.find(id);
		if (it != map.end()) {
			return false;
		}

		PeerData* peer_data = get(peer);
		peer_data->id = id;
		map.emplace(id, peer);

		return true;
	}

	void PeerData::destruct(ENetPeer* peer, map_t& map) {
		assert(peer != nullptr);
		assert(peer->data != nullptr);

		PeerData* peer_data = (PeerData*)peer->data;

		map.erase(peer_data->id);
		peer->data = nullptr;
		delete peer_data;
	}
}
