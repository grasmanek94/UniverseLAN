#ifndef LSFDRMFG_UNIVERSE_LAN_API_H
#define LSFDRMFG_UNIVERSE_LAN_API_H

/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "Impl/InitOptionsModern.hxx"

#include <IniData.hxx>

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
	class UtilsImpl;
	class AppsImpl;
	class StorageImpl;
	class CustomNetworkingImpl;
	class LoggerImpl;

#if (GALAXY_VERSION) > 112400
	class TelemetryImpl;
#endif

	class ListenerRegistrarImpl;
	class DelayRunner;

	// interface instances;
	struct InterfaceInstances {
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
		std::unique_ptr<StatsImpl>				stats = nullptr;
		std::unique_ptr<UtilsImpl>				utils = nullptr;
		std::unique_ptr<AppsImpl>				apps = nullptr;
		std::unique_ptr<StorageImpl>			storage = nullptr;
		std::unique_ptr<CustomNetworkingImpl>	custom_networking = nullptr;
		std::unique_ptr<LoggerImpl>				logger = nullptr;

#if (GALAXY_VERSION) > 112400
		std::unique_ptr<TelemetryImpl>			telemetry = nullptr;
#endif

		std::unique_ptr<ListenerRegistrarImpl>	notification = nullptr;
		std::unique_ptr<DelayRunner>			delay_runner = nullptr;

		void init(const InitOptionsImpl& initOptions);
		void reset();

		~InterfaceInstances();
	};

	extern InterfaceInstances intf_inst;
	extern InterfaceInstances gameserver_intf_inst;
}

#include "Client.hxx"
#include "CustomConsole.hxx"

#include "Impl/DelayRunner.hxx"
#include "Impl/Errors.hxx"
#include "Impl/ListenerRegistrar.hxx"

#include "Impl/Apps.hxx"
#include "Impl/Chat.hxx"
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

#include <GalaxyApi.h>

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
#include <GalaxyGameServerApi.h>
#endif

#include <Tracer.hxx>

#endif