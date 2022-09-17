/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "Client.hxx"
#include "UniverseLAN.hxx"
#include "InterfaceInstances.hxx"

#include <IniData.hxx>

#include <memory>

namespace universelan::client {
	using namespace galaxy::api;
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
}
