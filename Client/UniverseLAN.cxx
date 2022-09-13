/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "Client.hxx"
#include "CustomConsole.hxx"
#include "UniverseLAN.hxx"

#include <IniData.hxx>

#include <memory>

namespace galaxy
{
	namespace api
	{
		std::unique_ptr <ClientIniData> config = nullptr;
		std::unique_ptr<InitOptionsModern> init_options = nullptr;

		static std::unique_ptr<Client> client = nullptr;
		static std::unique_ptr<UserImpl> user_impl = nullptr;
		static std::unique_ptr<FriendsImpl> friends_impl = nullptr;
		static std::unique_ptr<ChatImpl> chat_impl = nullptr;
		static std::unique_ptr<MatchmakingImpl> matchmaking_impl = nullptr;
		static std::unique_ptr<NetworkingImpl> networking_impl = nullptr;
		static std::unique_ptr<StatsImpl> stats_impl = nullptr;
		static std::unique_ptr<UtilsImpl> utils_impl = nullptr;
		static std::unique_ptr<AppsImpl> apps_impl = nullptr;
		static std::unique_ptr<StorageImpl> storage_impl = nullptr;
		static std::unique_ptr<CustomNetworkingImpl> custom_networking_impl = nullptr;
		static std::unique_ptr<LoggerImpl> logger_impl = nullptr;
		static std::unique_ptr<TelemetryImpl> telemetry_impl = nullptr;

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Init(const InitOptions& initOptions) {
			if (config == nullptr) {
				config = std::make_unique<ClientIniData>();
			}

			init_options = std::make_unique<InitOptionsModern>(initOptions);
			client = std::make_unique<Client>(config->GetServerAddress(), config->GetPort());
			user_impl = std::make_unique<UserImpl>();
			friends_impl = std::make_unique<FriendsImpl>();
			chat_impl = std::make_unique<ChatImpl>();
			matchmaking_impl = std::make_unique<MatchmakingImpl>();
			networking_impl = std::make_unique<NetworkingImpl>();
			stats_impl = std::make_unique<StatsImpl>();
			utils_impl = std::make_unique<UtilsImpl>();
			apps_impl = std::make_unique<AppsImpl>();
			storage_impl = std::make_unique<StorageImpl>();
			custom_networking_impl = std::make_unique<CustomNetworkingImpl>();
			logger_impl = std::make_unique<LoggerImpl>();
			telemetry_impl = std::make_unique<TelemetryImpl>();

			if (config->GetEnableConsole())
			{
				EnableCustomConsole();
			}

			std::cout << "Using username: " << config->GetCustomPersonaName() << std::endl;
			std::cout << "Using GalaxyID: " << config->GetCustomGalaxyID() << std::endl;

			client->Start();
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Shutdown() {
			client->Stop();

			telemetry_impl = nullptr;
			logger_impl = nullptr;
			custom_networking_impl = nullptr;
			storage_impl = nullptr;
			apps_impl = nullptr;
			utils_impl = nullptr;
			stats_impl = nullptr;
			networking_impl = nullptr;
			matchmaking_impl = nullptr;
			chat_impl = nullptr;
			friends_impl = nullptr;
			user_impl = nullptr;
			init_options = nullptr;
			client = nullptr;
		}

		GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE User() {
			return user_impl.get();
		}

		GALAXY_DLL_EXPORT IFriends* GALAXY_CALLTYPE Friends() {

			return friends_impl.get();
		}

		GALAXY_DLL_EXPORT IChat* GALAXY_CALLTYPE Chat() {

			return chat_impl.get();
		}

		GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE Matchmaking() {

			return matchmaking_impl.get();
		}

		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE Networking() {

			return networking_impl.get();
		}

		GALAXY_DLL_EXPORT IStats* GALAXY_CALLTYPE Stats() {

			return stats_impl.get();
		}

		GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE Utils() {

			return utils_impl.get();
		}

		GALAXY_DLL_EXPORT IApps* GALAXY_CALLTYPE Apps() {

			return apps_impl.get();
		}

		GALAXY_DLL_EXPORT IStorage* GALAXY_CALLTYPE Storage() {

			return storage_impl.get();
		}

		GALAXY_DLL_EXPORT ICustomNetworking* GALAXY_CALLTYPE CustomNetworking() {

			return custom_networking_impl.get();
		}

		GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE Logger() {

			return logger_impl.get();
		}

		GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE Telemetry() {

			return telemetry_impl.get();
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessData() {
			if (client != nullptr) {
				client->ProcessEvents();
			}
		}

		GALAXY_DLL_EXPORT const IError* GALAXY_CALLTYPE GetError() {
			return nullptr;
		}
	}
}

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	return 0;
}
