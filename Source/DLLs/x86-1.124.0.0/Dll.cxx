#include <GalaxyDLL.hxx>

namespace galaxy::api {
	void GALAXY_CALLTYPE Init(struct InitOptions const& initOptions) 
	{
		return universelan::client::Init(initOptions);
	}

	void GALAXY_CALLTYPE ProcessData(void) 
	{
		universelan::client::ProcessData();
	}

	void GALAXY_CALLTYPE Shutdown(void)
	{
		universelan::client::Shutdown();
	}

	IApps* GALAXY_CALLTYPE Apps(void)
	{
		return universelan::client::Apps();
	}

	IChat* GALAXY_CALLTYPE Chat(void)
	{
		return universelan::client::Chat();
	}

	ICustomNetworking* GALAXY_CALLTYPE CustomNetworking(void)
	{
		return universelan::client::CustomNetworking();
	}

	IFriends* GALAXY_CALLTYPE Friends(void)
	{
		return universelan::client::Friends();
	}

	IError const* GALAXY_CALLTYPE GetError(void)
	{
		return universelan::client::GetError();
	}

	IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar(void)
	{
		return universelan::client::ListenerRegistrar();
	}

	ILogger* GALAXY_CALLTYPE Logger(void)
	{
		return universelan::client::Logger();
	}

	IMatchmaking* GALAXY_CALLTYPE Matchmaking(void)
	{
		return universelan::client::Matchmaking();
	}

	INetworking* GALAXY_CALLTYPE Networking(void)
	{
		return universelan::client::Networking();
	}

	INetworking* GALAXY_CALLTYPE ServerNetworking(void)
	{
		return universelan::client::ServerNetworking();
	}

	IStats* GALAXY_CALLTYPE Stats(void)
	{
		return universelan::client::Stats();
	}

	IStorage* GALAXY_CALLTYPE Storage(void)
	{
		return universelan::client::Storage();
	}

	IUser* GALAXY_CALLTYPE User(void)
	{
		return universelan::client::User();
	}

	IUtils* GALAXY_CALLTYPE Utils(void)
	{
		return universelan::client::Utils();
	}
}
