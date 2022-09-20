#pragma once

#include "Impl/InitOptionsModern.hxx"
#include "Impl/DelayRunner.hxx"

#include <IniData.hxx>

#include <memory>

namespace universelan::client {
	class Client;
	struct InitOptionsModern;
	class  UserImpl;
	class  FriendsImpl;
	class  ChatImpl;
	class  MatchmakingImpl;
	class  NetworkingImpl;
	class  StatsImpl;
	class  UtilsImpl;
	class  AppsImpl;
	class  StorageImpl;
	class  CustomNetworkingImpl;
	class  LoggerImpl;
	class  TelemetryImpl;
	class  ListenerRegistrarImpl;
	struct galaxy::api::InitOptions;

	// interface instances;
	struct InterfaceInstances {
		std::unique_ptr<ClientIniData>			config = nullptr;
		std::unique_ptr<InitOptionsModern>		init_options = nullptr;
		std::unique_ptr<Client>					client = nullptr;
		std::unique_ptr<UserImpl>				user = nullptr;
		std::unique_ptr<FriendsImpl>			friends = nullptr;
		std::unique_ptr<ChatImpl>				chat = nullptr;
		std::unique_ptr<MatchmakingImpl>		matchmaking = nullptr;
		std::unique_ptr<NetworkingImpl>			networking = nullptr;
		std::unique_ptr<StatsImpl>				stats = nullptr;
		std::unique_ptr<UtilsImpl>				utils = nullptr;
		std::unique_ptr<AppsImpl>				apps = nullptr;
		std::unique_ptr<StorageImpl>			storage = nullptr;
		std::unique_ptr<CustomNetworkingImpl>	custom_networking = nullptr;
		std::unique_ptr<LoggerImpl>				logger = nullptr;
		std::unique_ptr<TelemetryImpl>			telemetry = nullptr;
		std::unique_ptr<ListenerRegistrarImpl>	notification = nullptr;
		std::unique_ptr<DelayRunner>			delay_runner = nullptr;

		void init(const InitOptions& initOptions);
		void reset();
	};
}
