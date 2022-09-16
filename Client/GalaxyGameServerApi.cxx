#include "GalaxyGameServerApi.hxx"

#include "CustomConsole.hxx"
#include "UniverseLAN.hxx"

#include <Version.hxx>

#include <GalaxyApi.h>

#include <memory>

namespace galaxy
{
	namespace api
	{
		namespace gameserver
		{
			std::unique_ptr<ClientIniData>					config = nullptr;
			std::unique_ptr<InitOptionsModern>				init_options = nullptr;
			std::unique_ptr<Client>							client = nullptr;

			static std::unique_ptr<UserImpl>				user_impl = nullptr;
			static std::unique_ptr<MatchmakingImpl>			matchmaking_impl = nullptr;
			static std::unique_ptr<NetworkingImpl>			networking_impl = nullptr;
			static std::unique_ptr<UtilsImpl>				utils_impl = nullptr;
			static std::unique_ptr<LoggerImpl>				logger_impl = nullptr;
			static std::unique_ptr<TelemetryImpl>			telemetry_impl = nullptr;
			static std::unique_ptr<ListenerRegistrarImpl>	listener_registrar_impl = nullptr;
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE InitGameServer(const InitOptions& initOptions) {
			if (gameserver::config == nullptr) {
				gameserver::config = std::make_unique<ClientIniData>();
			}

			gameserver::init_options = std::make_unique<InitOptionsModern>(initOptions);
			gameserver::listener_registrar_impl = std::make_unique<ListenerRegistrarImpl>();
			gameserver::client = std::make_unique<Client>(gameserver::config->GetServerAddress(), gameserver::config->GetPort());
			gameserver::user_impl = std::make_unique<UserImpl>(gameserver::listener_registrar_impl.get());
			gameserver::matchmaking_impl = std::make_unique<MatchmakingImpl>(gameserver::listener_registrar_impl.get());
			gameserver::networking_impl = std::make_unique<NetworkingImpl>(gameserver::listener_registrar_impl.get());
			gameserver::utils_impl = std::make_unique<UtilsImpl>(gameserver::listener_registrar_impl.get());
			gameserver::logger_impl = std::make_unique<LoggerImpl>();
			gameserver::telemetry_impl = std::make_unique<TelemetryImpl>(gameserver::listener_registrar_impl.get());

			if (gameserver::config->GetEnableConsole()) {
				EnableCustomConsole();
			}

			std::cout << "Version: " << Version_Number << std::endl;
			std::cout << "Using username: " << gameserver::config->GetCustomPersonaName() << std::endl;
			std::cout << "Using GalaxyID: " << gameserver::config->GetCustomGalaxyID() << std::endl;

			gameserver::client->Start();
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ShutdownGameServer() {
			gameserver::client->Stop();

			gameserver::telemetry_impl = nullptr;
			gameserver::logger_impl = nullptr;
			gameserver::utils_impl = nullptr;
			gameserver::networking_impl = nullptr;
			gameserver::matchmaking_impl = nullptr;
			gameserver::user_impl = nullptr;
			gameserver::init_options = nullptr;
			gameserver::client = nullptr;
			gameserver::listener_registrar_impl = nullptr;
		}

		GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE GameServerUser() {
			return gameserver::user_impl.get();
		}

		GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE GameServerMatchmaking() {
			return gameserver::matchmaking_impl.get();
		}

		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE GameServerNetworking() {
			return gameserver::networking_impl.get();
		}

		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE ServerNetworking() {
			return gameserver::networking_impl.get();
		}

		GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE GameServerUtils() {
			return gameserver::utils_impl.get();
		}

		GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE GameServerTelemetry() {
			return gameserver::telemetry_impl.get();
		}

		GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE GameServerLogger() {
			return gameserver::logger_impl.get();
		}

		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE GameServerListenerRegistrar() {
			return gameserver::listener_registrar_impl.get();
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessGameServerData() {
			if (gameserver::client != nullptr) {
				gameserver::client->ProcessEvents();
			}
		}
	}
}
