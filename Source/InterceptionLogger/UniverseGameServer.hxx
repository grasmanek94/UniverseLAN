#pragma once

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

#include "UniverseLAN.hxx"

namespace universelan::client {
	class UniverseGameServer {
	private:
		InterfaceInstances gameserver_intf_inst;

	public:
		UniverseGameServer();
		virtual ~UniverseGameServer();

		void InitGameServer(const InitOptions& initOptions);
		void ShutdownGameServer();
		IUser* GameServerUser();
		IMatchmaking* GameServerMatchmaking();

		INetworking* GameServerNetworking();

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		IUtils* GameServerUtils();
#endif

#if GALAXY_BUILD_FEATURE_HAS_GAMESERVERTELEMETRY
		ITelemetry* GameServerTelemetry();
#endif

		ILogger* GameServerLogger();
		IListenerRegistrar* GameServerListenerRegistrar();
		void ProcessGameServerData();
	};
}

#endif
