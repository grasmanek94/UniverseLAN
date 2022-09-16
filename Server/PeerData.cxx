#include "PeerData.hxx"

#include <GalaxyApi.h>

#include <cstdint>
#include <chrono>

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

PeerData* PeerData::construct(ENetPeer* peer) {
	if (peer == nullptr) {
		return nullptr;
	}

	PeerData* peer_data = new PeerData();
	peer_data->peer = peer;
	peer->data = (void*)peer_data;

	return peer_data;
}

void PeerData::destruct(ENetPeer* peer) {
	if (peer == nullptr) {
		return;
	}

	PeerData* peer_data = (PeerData*)peer->data;
	if (peer_data) {
		peer->data = nullptr;
		delete peer_data;
	}
}
