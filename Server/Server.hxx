#pragma once

#include "ChatRoomManager.hxx"
#include "GalaxyUserData.hxx"
#include "LobbyManager.hxx"
#include "PeerData.hxx"
#include "SharedFileUtils.hxx"

#include <IniData.hxx>
#include <Networking/Networking.hxx>

#include <GalaxyApi.h>

#include <random>
#include <set>

namespace universelan::server {
	class Server : public MessageReceiver
	{
	public:

	private:
		ServerIniData config;
		GalaxyNetworkServer connection;
		size_t max_connections;
		std::set<ENetPeer*> connected_peers;
		std::set<ENetPeer*> unauthenticated_peers;
		uint64_t authentication_key;
		std::mt19937_64 random;
		size_t ticks;
		size_t minimum_tick_wait_time;

		GalaxyUserData::map_t user_data;
		ChatRoomManager chat_room_manager;
		LobbyManager lobby_manager;
		PeerData::map_t peer_map;

		SharedFileUtils sfu;
		uint32_t shared_file_counter;
		const std::string shared_file_counter_file{ "shared-id.counter" };

		bool KickUnauthenticated(ENetPeer* peer);

		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override;
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override;

		SHARED_NETWORK_OVERRIDE_MESSAGE_HANDLERS();

	public:
		Server();
		virtual ~Server();

		void Tick();
		uint32_t GetMaxTickRate() const;
	};
}
