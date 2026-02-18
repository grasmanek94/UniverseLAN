#pragma once

/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "Impl/InitOptionsModern.hxx"

#include <IniData.hxx>
#include <SharedFileUtils.hxx>

#include <memory>

namespace universelan::client {
	class Client;
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
	class DelayRunner;

	// interface instances;
	struct InterfaceInstances {
		std::unique_ptr<SharedFileUtils>		sfu = nullptr;
		std::unique_ptr<ClientIniData>			config = nullptr;
		std::unique_ptr<InitOptionsModern>		init_options = nullptr;
		std::unique_ptr<Client>					client = nullptr;
		std::unique_ptr<UserImpl>				user = nullptr;
		std::unique_ptr<FriendsImpl>			friends = nullptr;

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		std::unique_ptr<ChatImpl>				chat = nullptr;
#endif

		std::unique_ptr<MatchmakingImpl>		matchmaking = nullptr;
		std::unique_ptr<NetworkingImpl>			networking = nullptr;
#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
		std::unique_ptr<NetworkingImpl>			server_networking = nullptr;
#endif
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
		std::unique_ptr<DelayRunner>			delay_runner = nullptr;

		void init(const InitOptionsModern& initOptions, bool is_gameserver = false);
		void reset();

		~InterfaceInstances();

	private:
		void internal_reset();
	};

	extern InterfaceInstances intf_inst;
	extern InterfaceInstances gameserver_intf_inst;
}

#include <Tracer.hxx>

#include <GalaxyApi.h>

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
#include <GalaxyGameServerApi.h>
#endif

#include "Client.hxx"
#include "CustomConsole.hxx"

#include "Impl/DelayRunner.hxx"
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
