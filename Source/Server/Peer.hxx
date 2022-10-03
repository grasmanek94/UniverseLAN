#pragma once

#include "Challenge.hxx"

#include <GalaxyID.h>

#include <GalaxyUserData.hxx>
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
		using map_t = std::unordered_map<galaxy::api::GalaxyID, ENetPeer*, galaxy::api::GalaxyID::Hash>;

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
		ChatRoomManager::chatrooms_t chat_rooms;
		LobbyManager::lobby_t lobby;

		bool link(const galaxy::api::GalaxyID& id);
	};
}
