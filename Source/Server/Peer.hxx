#pragma once

#include "Challenge.hxx"

#include <GalaxyID.h>

#include <GalaxyUserData.hxx>
#include <GalaxyID.hxx>
#include <Networking/Networking.hxx>
#include <ChatRoomManager.hxx>
#include <LobbyManager.hxx>

#include <cstdint>
#include <chrono>

namespace universelan::server::peer {
	class Data;
	using ptr = Data*;

	class Mapper {
		friend class Data;

	public:
		using map_t = std::unordered_map<galaxy::api::GalaxyID, ENetPeer*, universelan::GalaxyIDHash>;

	private:
		map_t map;

	public:
		Mapper();

		ptr Get(ENetPeer* peer);
		ptr Get(const galaxy::api::GalaxyID& id);

		ptr Connect(ENetPeer* peer);
		void Disconnect(ENetPeer* peer);

		std::unordered_set<ENetPeer*> connected_peers;
	};

	class Data {
		friend class Mapper;

	private:
		Mapper* mapper;

		Data(ENetPeer* peer, Mapper* map);
		~Data();

	public:
		ENetPeer* peer;
		galaxy::api::GalaxyID id;
		Challenge challenge;
		std::chrono::system_clock::time_point connected_time;
		GalaxyUserData::ptr_t user_data;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		ChatRoomManager::chatrooms_t chat_rooms;
#endif
		LobbyManager::lobby_t lobby;

		bool link(const galaxy::api::GalaxyID& id);
	};
}
