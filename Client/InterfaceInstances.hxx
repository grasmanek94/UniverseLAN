#pragma once

#include "Impl/InitOptionsModern.hxx"

#include <IniData.hxx>

#include <memory>

class Client;

namespace galaxy
{
	namespace api
	{
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
		struct InitOptions;

		// interface instances;
		struct InterfaceInstances {
			std::unique_ptr<ClientIniData>			config = nullptr;
			std::unique_ptr<InitOptionsModern>		init_options = nullptr;
			std::unique_ptr<Client>					client = nullptr;
			std::unique_ptr<UserImpl>				user_impl = nullptr;
			std::unique_ptr<FriendsImpl>			friends_impl = nullptr;
			std::unique_ptr<ChatImpl>				chat_impl = nullptr;
			std::unique_ptr<MatchmakingImpl>		matchmaking_impl = nullptr;
			std::unique_ptr<NetworkingImpl>			networking_impl = nullptr;
			std::unique_ptr<StatsImpl>				stats_impl = nullptr;
			std::unique_ptr<UtilsImpl>				utils_impl = nullptr;
			std::unique_ptr<AppsImpl>				apps_impl = nullptr;
			std::unique_ptr<StorageImpl>			storage_impl = nullptr;
			std::unique_ptr<CustomNetworkingImpl>	custom_networking_impl = nullptr;
			std::unique_ptr<LoggerImpl>				logger_impl = nullptr;
			std::unique_ptr<TelemetryImpl>			telemetry_impl = nullptr;
			std::unique_ptr<ListenerRegistrarImpl>	listener_registrar_impl = nullptr;

			void init(const InitOptions& initOptions);
			void reset();
		};
	}
}