/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "GalaxyApi.hxx"

namespace galaxy
{
	namespace api
	{
		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Init(const InitOptions& initOptions) {

		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Shutdown() {

		}

		GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE User() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IFriends* GALAXY_CALLTYPE Friends() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IChat* GALAXY_CALLTYPE Chat() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE Matchmaking() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE Networking() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IStats* GALAXY_CALLTYPE Stats() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE Utils() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IApps* GALAXY_CALLTYPE Apps() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT IStorage* GALAXY_CALLTYPE Storage() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT ICustomNetworking* GALAXY_CALLTYPE CustomNetworking() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE Logger() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE Telemetry() {
			return nullptr;
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessData() {

		}

		GALAXY_DLL_EXPORT const IError* GALAXY_CALLTYPE GetError() {
			return nullptr;
		}
	}
}
