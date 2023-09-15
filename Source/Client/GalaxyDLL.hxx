#pragma once

#include "UniverseLAN.hxx"

namespace universelan::client {
	void Init(const InitOptions& initOptions);
	void Shutdown();
	IUser* User();
	IFriends* Friends();
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	IChat* Chat();
#endif

	IMatchmaking* Matchmaking();
	INetworking* Networking();
	INetworking* ServerNetworking();

	IStats* Stats();
	IUtils* Utils();
	IApps* Apps();
	IStorage* Storage();
	ICustomNetworking* CustomNetworking();
	ILogger* Logger();
#if (GALAXY_VERSION) > 11240
	ITelemetry* Telemetry();
#endif

	void ProcessData();
	IListenerRegistrar* ListenerRegistrar();
	const IError* GetError();
}
