#include "UniverseLANInterceptor.hxx"

#include <Tracer.hxx>
#include <GalaxyApi.h>

#include <GalaxyDLL.hxx>

namespace galaxy::api {

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Init(struct InitOptions const& initOptions)
	{
		return universelan::client::Init(initOptions);
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessData(void)
	{
		universelan::client::ProcessData();
	}

	GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Shutdown(void)
	{
		universelan::client::Shutdown();
	}

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
	GALAXY_DLL_EXPORT IApps* GALAXY_CALLTYPE Apps(void)
	{
		return universelan::client::Apps();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	GALAXY_DLL_EXPORT IChat* GALAXY_CALLTYPE Chat(void)
	{
		return universelan::client::Chat();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
	GALAXY_DLL_EXPORT ICustomNetworking* GALAXY_CALLTYPE CustomNetworking(void)
	{
		return universelan::client::CustomNetworking();
	}
#endif

	GALAXY_DLL_EXPORT IFriends* GALAXY_CALLTYPE Friends(void)
	{
		return universelan::client::Friends();
	}

	GALAXY_DLL_EXPORT IError const* GALAXY_CALLTYPE GetError(void)
	{
		return universelan::client::GetError();
	}

	GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar(void)
	{
		return universelan::client::ListenerRegistrar();
	}

	GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE Logger(void)
	{
		return universelan::client::Logger();
	}

	GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE Matchmaking(void)
	{
		return universelan::client::Matchmaking();
	}

	GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE Networking(void)
	{
		return universelan::client::Networking();
	}

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKINGLISTENER
	GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE ServerNetworking(void)
	{
		return universelan::client::ServerNetworking();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE Telemetry(void) {
		return universelan::client::Telemetry();
	}
#endif

	GALAXY_DLL_EXPORT IStats* GALAXY_CALLTYPE Stats(void)
	{
		return universelan::client::Stats();
	}

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	GALAXY_DLL_EXPORT IStorage* GALAXY_CALLTYPE Storage(void)
	{
		return universelan::client::Storage();
	}
#endif

	GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE User(void)
	{
		return universelan::client::User();
	}

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
	GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE Utils(void)
	{
		return universelan::client::Utils();
	}
#endif
}

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	return universelan::client::load();
}
