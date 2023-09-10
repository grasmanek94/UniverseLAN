#pragma once

#include "Lobby.hxx"

#include <GalaxyID.h>
#include <IMatchMaking.h>

#include <GalaxyIDHash.hxx>

#include <memory>
#include <unordered_map>

namespace universelan {
	class LobbyManager {
	public:
		using lobby_t = std::shared_ptr<Lobby>;
		using lobbies_t = std::unordered_map<galaxy::api::GalaxyID, lobby_t, universelan::GalaxyIDHash>;
	
	private:
		lobbies_t lobbies;

	public:
		LobbyManager();

		lobby_t CreateLobby(galaxy::api::GalaxyID owner, galaxy::api::LobbyType lobby_type, uint32_t max_members, bool joinable, galaxy::api::LobbyTopologyType lobby_topology_type);
		lobby_t GetLobby(galaxy::api::GalaxyID lobby_id) const;
		const lobbies_t& GetLobbies() const;
		bool RemoveLobby(galaxy::api::GalaxyID lobby_id);
	};
}
