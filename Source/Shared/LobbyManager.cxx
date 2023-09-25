#include "LobbyManager.hxx"
#include "Lobby.hxx"

#include <GalaxyID.h>
#include <IMatchmaking.h>

#include <memory>
#include <unordered_map>

namespace universelan {
	LobbyManager::LobbyManager() : lobbies{} {}

	LobbyManager::lobby_t LobbyManager::CreateLobby(galaxy::api::GalaxyID owner, galaxy::api::LobbyType lobby_type, uint32_t max_members, bool joinable, galaxy::api::LobbyTopologyType lobby_topology_type) {
		lobby_t lobby = std::make_shared<Lobby>(owner, lobby_type, max_members, joinable, lobby_topology_type);
		lobbies.emplace(lobby->GetID(), lobby);
		return lobby;
	}

	LobbyManager::lobby_t LobbyManager::GetLobby(galaxy::api::GalaxyID lobby_id) const {
		auto lobby = lobbies.find(lobby_id);
		if (lobby == lobbies.end()) {
			return nullptr;
		}

		return lobby->second;
	}

	const LobbyManager::lobbies_t& LobbyManager::GetLobbies() const {
		return lobbies;
	}

	bool LobbyManager::RemoveLobby(galaxy::api::GalaxyID lobby_id) {
		return lobbies.erase(lobby_id) > 0;
	}
}
