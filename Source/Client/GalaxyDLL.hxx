#pragma once

#include "UniverseLAN.hxx"

namespace universelan::client {
	using namespace galaxy::api;
	using namespace universelan;

	void Init(const InitOptions& initOptions);
	void Shutdown();
	IUser* User();
	IFriends* Friends();
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	IChat* Chat();
#endif

	IMatchmaking* Matchmaking();
	INetworking* Networking();
#if !GALAXY_BUILD_FEATURE_GAME_SERVER_API
	INetworking* ServerNetworking();
#endif

	IStats* Stats();
	IUtils* Utils();
	IApps* Apps();
	IStorage* Storage();
	ICustomNetworking* CustomNetworking();
	ILogger* Logger();
#if (GALAXY_VERSION) > 112400
	ITelemetry* Telemetry();
#endif

	void ProcessData();
	IListenerRegistrar* ListenerRegistrar();
	const IError* GetError();
}
