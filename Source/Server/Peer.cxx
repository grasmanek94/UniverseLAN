#include "Peer.hxx"

#include <Tracer.hxx>

#include <GalaxyApi.h>

#include <cstdint>
#include <chrono>

namespace universelan::server::peer {
	using namespace galaxy::api;

	Mapper::Mapper() : map{}, connected_peers{} {}

	ptr Mapper::Get(ENetPeer* peer) {
		assert(peer != nullptr);
		assert(peer->data != nullptr);

		return static_cast<ptr>(peer->data);
	}

	ptr Mapper::Get(const galaxy::api::GalaxyID& id) {
		auto it = map.find(id);
		if (it == map.end()) {
			return nullptr;
		}

		return Get(it->second);
	}

	ptr Mapper::Connect(ENetPeer* peer) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		assert(peer != nullptr);
		ptr x = (ptr)peer->data;
		assert(peer->data == nullptr);

		connected_peers.insert(peer);
		return new Data(peer, this);
	}

	void Mapper::Disconnect(ENetPeer* peer) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		assert(peer != nullptr);

		delete static_cast<ptr>(peer->data);
		connected_peers.erase(peer);
	}

	Data::Data(ENetPeer* peer, Mapper* mapper) :
		mapper{ mapper}, peer{ peer }, id{ 0ULL }, challenge{},
		connected_time{ std::chrono::system_clock::now() },
		user_data{ nullptr }, hello_performed{false},
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		chat_rooms{},
#endif
		lobbies{}
	{
		assert(peer != nullptr);
		assert(peer->data == nullptr);
		peer->data = static_cast<void*>(this);
	}

	Data::~Data() {
		mapper->map.erase(id);
		peer->data = nullptr;
	}

	bool Data::link(const GalaxyID& id) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (peer->data == nullptr) {
			return false;
		}

		if (!id.IsValid()) {
			return false;
		}

		if (!mapper->map.emplace(id, peer).second) {
			return false;
		}

		mapper->Get(peer)->id = id;

		return true;
	}

	LobbyManager::lobby_t Data::GetLobby(const galaxy::api::GalaxyID& lobby_id) const {
		auto it = lobbies.find(lobby_id);
		if (it == lobbies.end()) {
			return nullptr;
		}

		return it->second;
	}

	bool Data::AddLobby(const LobbyManager::lobby_t& lobby) {
		if (lobby == nullptr) {
			return false;
		}

		auto it = lobbies.find(lobby->GetID());
		if (it != lobbies.end()) {
			return false;
		}

		lobbies.emplace(lobby->GetID(), lobby);

		return true;
	}

	bool Data::RemoveLobby(const galaxy::api::GalaxyID& lobby_id) {
		return lobbies.erase(lobby_id) > 0;
	}

	bool Data::RemoveLobby(const LobbyManager::lobby_t& lobby) {
		if (lobby == nullptr) {
			return false;
		}

		return RemoveLobby(lobby->GetID());
	}
}
