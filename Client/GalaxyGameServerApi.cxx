#include "GalaxyGameServerApi.hxx"

namespace galaxy
{
	namespace api
	{
		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE InitGameServer(const InitOptions& initOptions) {

		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServer() {

		}

		GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE GameServerUser() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE GameServerMatchmaking() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE GameServerNetworking() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE ServerNetworking() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE GameServerUtils() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE GameServerTelemetry() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE GameServerLogger() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessGameServerData() {
			
		}
	}
}
