#include "GalaxyGameServerApi.hxx"

#include "CustomConsole.hxx"
#include "UniverseLAN.hxx"

#include <Version.hxx>

#include <GalaxyApi.h>

#include <memory>

namespace galaxy::api {
	using namespace universelan;
	using namespace universelan::client;

	InterfaceInstances gameserver_intf_inst;

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE InitGameServer(const InitOptions& initOptions) {
		gameserver_intf_inst.init(initOptions);

		if (gameserver_intf_inst.config->GetEnableConsole()) {
			EnableCustomConsole();
		}

		std::cout << "Version: " << Version_Number << std::endl;
		std::cout << "Using username: " << gameserver_intf_inst.config->GetCustomPersonaName() << std::endl;
		std::cout << "Using GalaxyID: " << gameserver_intf_inst.config->GetCustomGalaxyID() << std::endl;

		gameserver_intf_inst.client->Start();
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServer() {
		gameserver_intf_inst.reset();
	}

	GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE GameServerUser() {
		return gameserver_intf_inst.user.get();
	}

	GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE GameServerMatchmaking() {
		return gameserver_intf_inst.matchmaking.get();
	}

	GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE GameServerNetworking() {
		return gameserver_intf_inst.networking.get();
	}

	GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE ServerNetworking() {
		return gameserver_intf_inst.networking.get();
	}

	GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE GameServerUtils() {
		return gameserver_intf_inst.utils.get();
	}

	GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE GameServerTelemetry() {
		return gameserver_intf_inst.telemetry.get();
	}

	GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE GameServerLogger() {
		return gameserver_intf_inst.logger.get();
	}

	GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE GameServerListenerRegistrar() {
		return gameserver_intf_inst.notification.get();
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessGameServerData() {
		if (gameserver_intf_inst.client != nullptr) {
			gameserver_intf_inst.client->ProcessEvents();
		}

		if (gameserver_intf_inst.delay_runner != nullptr) {
			gameserver_intf_inst.delay_runner->Run();
		}
	}
}
