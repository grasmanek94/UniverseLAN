#include "Server.hxx"

#include "Peer.hxx"

#include <Networking/Networking.hxx>
#include <Tracer.hxx>

#include <chrono>
#include <exception>
#include <filesystem>
#include <iostream>

namespace universelan::server {
	bool Server::KickUnauthenticated(ENetPeer* peer) {
		peer::ptr pd = peer_mapper.Get(peer);

		if (pd == nullptr) {
			return false;
		}

		if (pd->challenge.completed) {
			return true;
		}

		connection.Disconnect(peer);

		return false;
	}

	Server::Server()
		: config{}, connection{}, max_connections{ 1024 },
		connected_peers{}, authentication_key{ 0 }, random{}, ticks{ 0 },
		minimum_tick_wait_time{ 0 }, user_data{}, chat_room_manager{},
		lobby_manager{}, peer_mapper{}, sfu{ config.GetServerDataPath() },
		shared_file_counter{ 1 }
	{
		tracer::Trace::InitTracing(
			(std::filesystem::path(config.GetServerDataPath()) / "Tracing").string().c_str(),
			config.IsUnhandledExceptionLoggingEnabled(),
			config.IsCallTracingEnabled(),
			config.CreateMiniDumpOnUnhandledException(),
			config.GetMiniDumpVerbosityLevel(),
			config.ShouldAlwaysFlushTracing()
		);

		tracer::Trace server_constructor{ __FUNCTION__ };

		int init_code = connection.GetInitCode();

		if (init_code)
		{
			// TODO custom exception class
			throw std::exception(
#ifdef _WIN32
			("Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str()
#endif
			);
		}

		connection.SetHost(config.GetBindAddress(), config.GetPort());

		std::cout << "Binding address: " << config.GetBindAddress() << ":" << config.GetPort() << std::endl;

		max_connections = config.GetMaxConnections();

		std::cout << "Max Connections: " << max_connections << std::endl;
		if (!connection.Create(max_connections) || !connection.Good())
		{
			// TODO custom exception class
			throw std::exception(
#ifdef _WIN32
				"ENET host member creation failed"
#endif
			);
		}

		authentication_key = const_hash64(config.GetAuthenticationKey());
		uint64_t milliseconds_since_epoch =
			std::chrono::system_clock::now().time_since_epoch() /
			std::chrono::milliseconds(1);

		random.seed(authentication_key ^ milliseconds_since_epoch);

		if (sfu.ExistsShared(shared_file_counter_file)) {
			std::string counter_txt{};
			sfu.OpenShared(shared_file_counter_file, std::ios::in) >> counter_txt;
			shared_file_counter = std::stoul(counter_txt);
		}

		std::cout << "Using key: " << authentication_key << std::endl;
		std::cout << "Listening..." << std::endl;
		//ready
	}

	void Server::PerformPeerCleanup() {
		tracer::Trace trace{ __FUNCTION__ };

		auto now = std::chrono::system_clock::now();

		for (auto& peer : unauthenticated_peers) {
			peer::ptr pd = peer_mapper.Get(peer);
			if (pd == nullptr) {
				connection.Disconnect(peer);
			}
			else {
				auto time = ((now - pd->connected_time) / std::chrono::milliseconds(1));
				if (time > 2500) {
					connection.Disconnect(peer);
				}
			}
		}
	}

	void Server::Tick()
	{
		while (connection.Pull())
		{
			ProcessEvent(connection.Event());
		}

		if (++ticks > 50) {
			ticks = 0;
			if (!unauthenticated_peers.empty()) {
				PerformPeerCleanup();
			}
		}
	}

	uint32_t Server::GetMaxTickRate() const {
		return config.GetMaxTickRate();
	}

	Server::~Server()
	{
		tracer::Trace destructor{ __FUNCTION__ };
	}
}
