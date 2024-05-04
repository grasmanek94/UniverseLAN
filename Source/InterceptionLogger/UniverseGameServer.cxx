#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

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

		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		if (gameserver_intf_inst.config->GetEnableConsole()) {
			EnableCustomConsole();
		}

		std::cout << " == UniverseLAN GameServer == " << std::endl;
		std::cout << "Version: " << Version_Number << std::endl;
	}
	void UniverseGameServer::ShutdownGameServer() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		gameserver_intf_inst.reset();
	}

	IUser* UniverseGameServer::GameServerUser() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		return gameserver_intf_inst.user.get();
	}

	IMatchmaking* UniverseGameServer::GameServerMatchmaking() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		return gameserver_intf_inst.matchmaking.get();
	}

	INetworking* UniverseGameServer::GameServerNetworking() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		return gameserver_intf_inst.networking.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
	IUtils* UniverseGameServer::GameServerUtils() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		return gameserver_intf_inst.utils.get();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_GAMESERVERTELEMETRY
	ITelemetry* UniverseGameServer::GameServerTelemetry() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		return gameserver_intf_inst.telemetry.get();
	}
#endif

	ILogger* UniverseGameServer::GameServerLogger() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		return gameserver_intf_inst.logger.get();
	}

	IListenerRegistrar* UniverseGameServer::GameServerListenerRegistrar() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		return gameserver_intf_inst.notification.get();
	}

	void UniverseGameServer::ProcessGameServerData() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };

		//if (gameserver_intf_inst.client != nullptr) {
		//	gameserver_intf_inst.client->ProcessEvents();
		//}

		//if (gameserver_intf_inst.delay_runner != nullptr) {
		//	gameserver_intf_inst.delay_runner->Run();
		//}
	}
}
#endif
