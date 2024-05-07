#pragma once

#include "UniverseLAN.hxx"

namespace universelan::client {
	void Init(const InitOptionsModern& initOptions);
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
	void Init(const galaxy::api::InitOptions& initOptions);
#endif
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
#if GALAXY_BUILD_FEATURE_HAS_IUTILS
	IUtils* Utils();
#endif
#if GALAXY_BUILD_FEATURE_HAS_IAPPS
	IApps* Apps();
#endif
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	IStorage* Storage();
#endif
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
	ICloudStorage* CloudStorage();
#endif
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
	ICustomNetworking* CustomNetworking();
#endif
	ILogger* Logger();
#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	ITelemetry* Telemetry();
#endif

	void ProcessData();
	IListenerRegistrar* ListenerRegistrar();
	const IError* GetError();
	uint32_t load();
}
