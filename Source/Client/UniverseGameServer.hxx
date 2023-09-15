#pragma once

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

		IUtils* GameServerUtils();

#if (GALAXY_VERSION) > 11240
		ITelemetry* GameServerTelemetry();
#endif

		ILogger* GameServerLogger();
		IListenerRegistrar* GameServerListenerRegistrar();
		void ProcessGameServerData();
	};
}
