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

	GALAXY_DLL_EXPORT IApps* GALAXY_CALLTYPE Apps(void)
	{
		return universelan::client::Apps();
	}

	GALAXY_DLL_EXPORT IChat* GALAXY_CALLTYPE Chat(void)
	{
		return universelan::client::Chat();
	}

	GALAXY_DLL_EXPORT ICustomNetworking* GALAXY_CALLTYPE CustomNetworking(void)
	{
		return universelan::client::CustomNetworking();
	}

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

	GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE ServerNetworking(void)
	{
		return universelan::client::ServerNetworking();
	}

	GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE Telemetry(void) {
		return universelan::client::Telemetry();
	}

	GALAXY_DLL_EXPORT IStats* GALAXY_CALLTYPE Stats(void)
	{
		return universelan::client::Stats();
	}

	GALAXY_DLL_EXPORT IStorage* GALAXY_CALLTYPE Storage(void)
	{
		return universelan::client::Storage();
	}

	GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE User(void)
	{
		return universelan::client::User();
	}

	GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE Utils(void)
	{
		return universelan::client::Utils();
	}
}
