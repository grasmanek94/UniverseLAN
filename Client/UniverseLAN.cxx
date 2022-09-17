/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "Client.hxx"
#include "CustomConsole.hxx"
#include "UniverseLAN.hxx"

#include <IniData.hxx>
#include <Version.hxx>

#include <memory>

namespace galaxy
{
	namespace api
	{
		InterfaceInstances intf_inst;

		void InterfaceInstances::init(const InitOptions& initOptions) {
			if (config == nullptr) {
				config = std::make_unique<ClientIniData>();
			}

			init_options = std::make_unique<InitOptionsModern>(initOptions);
			notification = std::make_unique<ListenerRegistrarImpl>(this);
			client = std::make_unique<Client>(this);
			user = std::make_unique<UserImpl>(this);
			friends = std::make_unique<FriendsImpl>(this);
			chat = std::make_unique<ChatImpl>(this);
			matchmaking = std::make_unique<MatchmakingImpl>(this);
			networking = std::make_unique<NetworkingImpl>(this);
			stats = std::make_unique<StatsImpl>(this);
			utils = std::make_unique<UtilsImpl>(this);
			apps = std::make_unique<AppsImpl>(this);
			storage = std::make_unique<StorageImpl>(this);
			custom_networking = std::make_unique<CustomNetworkingImpl>(this);
			logger = std::make_unique<LoggerImpl>(this);
			telemetry = std::make_unique<TelemetryImpl>(this);
		}

		void InterfaceInstances::reset() {
			if (client) {
				client->Stop();
			}

			telemetry = nullptr;
			logger = nullptr;
			custom_networking = nullptr;
			storage = nullptr;
			apps = nullptr;
			utils = nullptr;
			stats = nullptr;
			networking = nullptr;
			matchmaking = nullptr;
			chat = nullptr;
			friends = nullptr;
			user = nullptr;
			init_options = nullptr;
			client = nullptr;
			notification = nullptr;
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Init(const InitOptions& initOptions) {
			intf_inst.init(initOptions);

			if (intf_inst.config->GetEnableConsole()) {
				EnableCustomConsole();
			}

			std::cout << "Version: " << Version_Number << std::endl;
			std::cout << "Using username: " << intf_inst.config->GetCustomPersonaName() << std::endl;
			std::cout << "Using GalaxyID: " << intf_inst.config->GetCustomGalaxyID() << std::endl;

			intf_inst.client->Start();
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE Shutdown() {
			intf_inst.reset();
		}

		GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE User() {
			return intf_inst.user.get();
		}

		GALAXY_DLL_EXPORT IFriends* GALAXY_CALLTYPE Friends() {
			return intf_inst.friends.get();
		}

		GALAXY_DLL_EXPORT IChat* GALAXY_CALLTYPE Chat() {
			return intf_inst.chat.get();
		}

		GALAXY_DLL_EXPORT IMatchmaking* GALAXY_CALLTYPE Matchmaking() {
			return intf_inst.matchmaking.get();
		}

		GALAXY_DLL_EXPORT INetworking* GALAXY_CALLTYPE Networking() {
			return intf_inst.networking.get();
		}

		GALAXY_DLL_EXPORT IStats* GALAXY_CALLTYPE Stats() {
			return intf_inst.stats.get();
		}

		GALAXY_DLL_EXPORT IUtils* GALAXY_CALLTYPE Utils() {
			return intf_inst.utils.get();
		}

		GALAXY_DLL_EXPORT IApps* GALAXY_CALLTYPE Apps() {
			return intf_inst.apps.get();
		}

		GALAXY_DLL_EXPORT IStorage* GALAXY_CALLTYPE Storage() {
			return intf_inst.storage.get();
		}

		GALAXY_DLL_EXPORT ICustomNetworking* GALAXY_CALLTYPE CustomNetworking() {
			return intf_inst.custom_networking.get();
		}

		GALAXY_DLL_EXPORT ILogger* GALAXY_CALLTYPE Logger() {
			return intf_inst.logger.get();
		}

		GALAXY_DLL_EXPORT ITelemetry* GALAXY_CALLTYPE Telemetry() {
			return intf_inst.telemetry.get();
		}

		GALAXY_DLL_EXPORT void GALAXY_CALLTYPE ProcessData() {
			if (intf_inst.client != nullptr) {
				intf_inst.client->ProcessEvents();
			}
		}

		GALAXY_DLL_EXPORT IListenerRegistrar* GALAXY_CALLTYPE ListenerRegistrar() {
			return intf_inst.notification.get();
		}

		GALAXY_DLL_EXPORT const IError* GALAXY_CALLTYPE GetError() {
			return nullptr;
		}
	}
}

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	return 0;
}
