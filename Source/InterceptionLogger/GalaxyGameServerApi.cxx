#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
#include "UniverseGameServer.hxx"

#include <Tracer.hxx>
#include <GalaxyApi.h>

namespace galaxy::api {
	using namespace universelan;
	using namespace universelan::client;
	using namespace universelan::tracer;

	// REVIEW: All exports share this mutable server instance without synchronization;
	// ProcessGameServerData/getters can race InitGameServer or ShutdownGameServer and
	// observe destroyed interface pointers. Serialize the game-server lifecycle.
	static UniverseGameServer gameserver;

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE InitGameServer(const InitOptions& initOptions) {
		Trace trace{ nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };
		gameserver.InitGameServer(initOptions);
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServer() {
		Trace trace{ nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };
		gameserver.ShutdownGameServer();
	}

#if GALAXY_BUILD_FEATURE_HAS_SHUTDOWNOPTIONS
	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServerEx(const ShutdownOptions& shutdownOptions) {
		Trace trace{ nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL_GAMESERVERAPI };
		// REVIEW: shutdownOptions is ignored and this entry point calls the
		// non-Ex shutdown path; forward the options or document/implement equivalent
		// behavior to preserve the exported SDK contract.
		gameserver.ShutdownGameServer();
	}
#endif

	GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE GameServerUser() {
		return gameserver.GameServerUser();
	}

	GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE GameServerMatchmaking() {
		return gameserver.GameServerMatchmaking();
	}

	GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE GameServerNetworking() {
		return gameserver.GameServerNetworking();
	}

	// REVIEW: UniverseGameServer::GameServerUtils is feature-gated by
	// HAS_IUTILS, but this export is not. A game-server build without IUtils
	// therefore references a missing member; use the same conditional guard.
	GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE GameServerUtils() {
		return gameserver.GameServerUtils();
	}

#if GALAXY_BUILD_FEATURE_HAS_GAMESERVERTELEMETRY
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
