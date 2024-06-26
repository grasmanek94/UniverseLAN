#pragma once

#include "ChatRoomManager.hxx"
#include "GalaxyUserData.hxx"
#include "LobbyManager.hxx"
#include "Peer.hxx"
#include "SharedFileUtils.hxx"

#include <IniData.hxx>
#include <Networking/Networking.hxx>

#include <random>
#include <unordered_set>

namespace universelan::server {
	class Server : public MessageReceiver
	{
	public:

	private:
		ServerIniData config;
		GalaxyNetworkServer connection;
		size_t max_connections;
		std::unordered_set<ENetPeer*> connected_peers;
		std::unordered_set<ENetPeer*> unauthenticated_peers;
		uint64_t authentication_key;
		std::mt19937_64 random;
		size_t ticks;
		size_t minimum_tick_wait_time;

		GalaxyUserData::map_t user_data;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		ChatRoomManager chat_room_manager;
#endif
		LobbyManager lobby_manager;
		peer::Mapper peer_mapper;

		SharedFileUtils sfu;
		uint32_t shared_file_counter;
		const std::string shared_file_counter_file{ "shared-id.counter" };

		bool KickUnauthenticated(ENetPeer* peer);

		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override;
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override;

	// Here all 'virtual void Handle(ENetPeer* peer, const std::shared_ptr<T>&data) override; are declared
#include <Networking/MessageHandlersDeclareOverride.hxx>

		bool HandleMemberLobbyLeave(ENetPeer* peer, const galaxy::api::GalaxyID& lobby_id, bool disconnected);
		bool HandleMemberAllLobbiesLeave(ENetPeer* peer, bool disconnected);

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		bool HandleMemberChatLeave(ENetPeer* peer);
		bool HandleMemberChatLeave(ENetPeer* peer, galaxy::api::ChatRoomID chat_room_id);
#endif

		void PerformPeerCleanup();

	public:
		Server();
		virtual ~Server();

		void Tick();
		uint32_t GetMaxTickRate() const;
	};
}
