#pragma once

#include "CustomConsole.hxx"
#include "Impl/InitOptionsModern.hxx"
#include "Impl/Errors.hxx"
#include "Impl/ListenerRegistrar.hxx"
#include "Impl/Apps.hxx"
#include "Impl/Chat.hxx"
#include "Impl/CloudStorage.hxx"
#include "Impl/CustomNetworking.hxx"
#include "Impl/Friends.hxx"
#include "Impl/Logger.hxx"
#include "Impl/Matchmaking.hxx"
#include "Impl/Networking.hxx"
#include "Impl/Stats.hxx"
#include "Impl/Storage.hxx"
#include "Impl/Telemetry.hxx"
#include "Impl/User.hxx"
#include "Impl/Utils.hxx"

#include <IniData.hxx>

#include <GalaxyApi.h>
#include <GalaxyExport.h>

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
#include <GalaxyGameServerApi.h>
#endif

#include <functional>
#include <memory>

namespace universelan::client {
	struct InterfaceInstances {
		std::function<GALAXY_DLL_EXPORT void GALAXY_CALLTYPE(InitOptionsImpl const& initOptions)> real_init = nullptr;
		std::function<GALAXY_DLL_EXPORT void GALAXY_CALLTYPE(void)> real_process_data = nullptr;
		std::function<GALAXY_DLL_EXPORT void GALAXY_CALLTYPE(void)> real_shutdown = nullptr;
		std::function<GALAXY_DLL_EXPORT uint32_t GALAXY_CALLTYPE(void)> real_load = nullptr;

		std::unique_ptr<ClientIniData>			config = nullptr;
		std::unique_ptr<InitOptionsModern>		init_options = nullptr;
		std::unique_ptr<UserImpl>				user = nullptr;
		std::unique_ptr<FriendsImpl>			friends = nullptr;
		std::unique_ptr<ListenerRegistrarImpl>	notification = nullptr;
		std::unique_ptr<MatchmakingImpl>		matchmaking = nullptr;
		std::unique_ptr<NetworkingImpl>			networking = nullptr;
		std::unique_ptr<NetworkingImpl>			server_networking = nullptr;
		std::unique_ptr<StatsImpl>				stats = nullptr;
		std::unique_ptr<Error>					error = nullptr;
		std::unique_ptr<LoggerImpl>				logger = nullptr;

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		std::unique_ptr<ChatImpl>				chat = nullptr;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		std::unique_ptr<UtilsImpl>				utils = nullptr;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
		std::unique_ptr<AppsImpl>				apps = nullptr;
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		std::unique_ptr<StorageImpl>			storage = nullptr;
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
		std::unique_ptr<CloudStorageImpl>		cloud_storage = nullptr;
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
		std::unique_ptr<CustomNetworkingImpl>	custom_networking = nullptr;
#endif

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
		std::unique_ptr<TelemetryImpl>			telemetry = nullptr;
#endif

		void init(const InitOptionsModern& initOptions, bool gameserver = false);
		void reset();

		~InterfaceInstances();
	};
}
