#pragma once

/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include <GalaxyExport.h>

#include "Impl/InitOptionsModern.hxx"

#include <IniData.hxx>

#include <functional>
#include <memory>

namespace universelan::client {
	class UserImpl;
	class FriendsImpl;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	class ChatImpl;
#endif
	class MatchmakingImpl;
	class NetworkingImpl;
	class StatsImpl;
#if GALAXY_BUILD_FEATURE_HAS_IUTILS
	class UtilsImpl;
#endif
#if GALAXY_BUILD_FEATURE_HAS_IAPPS
	class AppsImpl;
#endif
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	class StorageImpl;
#endif
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
	class CloudStorageImpl;
#endif
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
	class CustomNetworkingImpl;
#endif
	class LoggerImpl;

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	class TelemetryImpl;
#endif

	class ListenerRegistrarImpl;

	// interface instances;
	struct InterfaceInstances {
		std::function<GALAXY_DLL_EXPORT void GALAXY_CALLTYPE(struct InitOptionsImpl const& initOptions)> real_init;
		std::function<GALAXY_DLL_EXPORT void GALAXY_CALLTYPE(void)> real_process_data;
		std::function<GALAXY_DLL_EXPORT void GALAXY_CALLTYPE(void)> real_shutdown;

		std::unique_ptr<ClientIniData>			config = nullptr;
		std::unique_ptr<InitOptionsModern>		init_options = nullptr;
		std::unique_ptr<UserImpl>				user = nullptr;
		std::unique_ptr<FriendsImpl>			friends = nullptr;

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		std::unique_ptr<ChatImpl>				chat = nullptr;
#endif

		std::unique_ptr<MatchmakingImpl>		matchmaking = nullptr;
		std::unique_ptr<NetworkingImpl>			networking = nullptr;
		std::unique_ptr<NetworkingImpl>			server_networking = nullptr;
		std::unique_ptr<StatsImpl>				stats = nullptr;

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

		std::unique_ptr<LoggerImpl>				logger = nullptr;

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
		std::unique_ptr<TelemetryImpl>			telemetry = nullptr;
#endif

		std::unique_ptr<ListenerRegistrarImpl>	notification = nullptr;

		void init(const InitOptionsModern& initOptions);
		void init_gameserver(const InitOptionsModern& initOptions);
		void reset();

		~InterfaceInstances();
	};

	extern InterfaceInstances intf_inst;
	extern InterfaceInstances gameserver_intf_inst;
}

#include <Tracer.hxx>

#include <GalaxyApi.h>

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
#include <GalaxyGameServerApi.h>
#endif

#include "CustomConsole.hxx"

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
