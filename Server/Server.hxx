#pragma once

#include "GalaxyUserData.hxx"

#include <IdCounter.hxx>
#include <IniData.hxx>
#include <Networking/Networking.hxx>

#include <GalaxyApi.h>

#include <random>
#include <set>

namespace universelan::server {

	class Server : public MessageReceiver
	{
	private:
		ServerIniData config;
		GalaxyNetworkServer connection;
		IdCounter id_generator;
		size_t max_connections;
		std::set<ENetPeer*> connected_peers;
		std::set<ENetPeer*> unauthenticated_peers;
		uint64_t authentication_key;
		std::mt19937_64 random;
		size_t ticks;
		size_t minimum_tick_wait_time;

		GalaxyUserData::map_t user_data;

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
