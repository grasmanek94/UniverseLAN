#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
#include "UniverseGameServer.hxx"

#include <GalaxyApi.h>

namespace galaxy::api {
	using namespace universelan;
	using namespace universelan::client;

	static UniverseGameServer gameserver;

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE InitGameServer(const InitOptions& initOptions) {
		gameserver.InitGameServer(initOptions);
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServer() {
		gameserver.ShutdownGameServer();
	}

	GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE GameServerUser() {
		return gameserver.GameServerUser();
	}

	GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE GameServerMatchmaking() {
		return gameserver.GameServerMatchmaking();
	}

	GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE GameServerNetworking() {
		return gameserver.GameServerNetworking();
	}

	GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE GameServerUtils() {
		return gameserver.GameServerUtils();
	}

#if (GALAXY_VERSION) > 11240
	GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE GameServerTelemetry() {
		return gameserver.GameServerTelemetry();
	}
#endif

	GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE GameServerLogger() {
		return gameserver.GameServerLogger();
	}

	GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE GameServerListenerRegistrar() {
		return gameserver.GameServerListenerRegistrar();
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessGameServerData() {
		gameserver.ProcessGameServerData();
	}
}

#endif
