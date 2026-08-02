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
		using steady_clock_t = peer::Data::steady_clock_t;
		using timepoint_t = peer::Data::timepoint_t;
		using duration_t = peer::Data::duration_t;

		static constexpr duration_t UNAUTHENTICATED_TIMEOUT_TIME = std::chrono::seconds(60);

	private:
		ServerIniData config;
		GalaxyNetworkServer connection;
		size_t max_connections;
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

		duration_t network_timeout;

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

		void PerformUnauthenticatedPeerCleanup();
		void PerformTimeoutPeerCleanup();
		void UpdatePeerNetworkTimeout(ENetPeer* peer);

	public:
		Server();
		virtual ~Server();

		void Tick();
		uint32_t GetMaxTickRate() const;
	};
}
