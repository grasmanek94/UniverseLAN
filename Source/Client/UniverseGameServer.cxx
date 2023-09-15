#include "CustomConsole.hxx"
#include "UniverseGameServer.hxx"

#include <Version.hxx>

#include <GalaxyApi.h>

#include <iostream>

namespace universelan::client {
	using namespace universelan;

	UniverseGameServer::UniverseGameServer():
		gameserver_intf_inst{} {

	}

	UniverseGameServer::~UniverseGameServer() {

	}

	void UniverseGameServer::InitGameServer(const InitOptions& initOptions) {
		gameserver_intf_inst.init(initOptions);

		tracer::Trace trace{ __FUNCTION__ };

		if (gameserver_intf_inst.config->GetEnableConsole()) {
			EnableCustomConsole();
		}

		std::cout << " == UniverseLAN GameServer == " << std::endl;
		std::cout << "Version: " << Version_Number << std::endl;
		std::cout << "Using username: " << gameserver_intf_inst.config->GetCustomPersonaName() << std::endl;
		std::cout << "Using key: " << const_hash64(intf_inst.config->GetAuthenticationKey()) << std::endl;
		std::cout << "Using GalaxyID: " << gameserver_intf_inst.config->GetCustomGalaxyID() << std::endl;

		gameserver_intf_inst.client->Start();
	}
	void UniverseGameServer::ShutdownGameServer() {
		tracer::Trace trace{ __FUNCTION__ };

		gameserver_intf_inst.reset();
	}

	IUser* UniverseGameServer::GameServerUser() {
		tracer::Trace trace{ __FUNCTION__ };

		return gameserver_intf_inst.user.get();
	}

	IMatchmaking* UniverseGameServer::GameServerMatchmaking() {
		tracer::Trace trace{ __FUNCTION__ };

		return gameserver_intf_inst.matchmaking.get();
	}

	INetworking* UniverseGameServer::GameServerNetworking() {
		tracer::Trace trace{ __FUNCTION__ };

		return gameserver_intf_inst.networking.get();
	}

	IUtils* UniverseGameServer::GameServerUtils() {
		tracer::Trace trace{ __FUNCTION__ };

		return gameserver_intf_inst.utils.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	ITelemetry* UniverseGameServer::GameServerTelemetry() {
		tracer::Trace trace{ __FUNCTION__ };

		return gameserver_intf_inst.telemetry.get();
	}
#endif

	ILogger* UniverseGameServer::GameServerLogger() {
		tracer::Trace trace{ __FUNCTION__ };

		return gameserver_intf_inst.logger.get();
	}

	IListenerRegistrar* UniverseGameServer::GameServerListenerRegistrar() {
		tracer::Trace trace{ __FUNCTION__ };

		return gameserver_intf_inst.notification.get();
	}

	void UniverseGameServer::ProcessGameServerData() {
		tracer::Trace trace{ __FUNCTION__ };

		if (gameserver_intf_inst.client != nullptr) {
			gameserver_intf_inst.client->ProcessEvents();
		}

		if (gameserver_intf_inst.delay_runner != nullptr) {
			gameserver_intf_inst.delay_runner->Run();
		}
	}
}
