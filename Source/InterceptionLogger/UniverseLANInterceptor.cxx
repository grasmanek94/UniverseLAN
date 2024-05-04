#include "UniverseLANInterceptor.hxx"

#include "Impl/InitOptionsModern.hxx"

#include "SharedLibUtils.hxx"

#include <IniData.hxx>
#include <Tracer.hxx>

#include <filesystem>
#include <memory>

namespace universelan::client {
	using namespace galaxy::api;
	namespace fs = std::filesystem;

	namespace {
		template <typename T>
		void interceptor_make_unique(std::unique_ptr<T>& ptr, const char* name) {
			ptr = std::make_unique<T>(SharedLibUtils::get_func<typename T::FuncPtr>(name));
		}

		template <typename T>
		void interceptor_make_unique(std::unique_ptr<T>& ptr, InterfaceInstances* t) {
			ptr = std::make_unique<T>(t);
		}

		template <typename T>
		void assign_func(std::function<T>& ptr, const char* name) {
			ptr = SharedLibUtils::get_func<T*>(name);
		}
	}

	void InterfaceInstances::init(const InitOptionsModern& initOptions, bool gameserver) {
		if (config == nullptr) {
			config = std::make_unique<ClientIniData>();
		}

		tracer::Trace::InitTracing(
			(fs::path(config->GetGameDataPath()) / "Interceptor").string().c_str(),
			config->IsUnhandledExceptionLoggingEnabled(),
			config->IsCallTracingEnabled(),
			config->CreateMiniDumpOnUnhandledException(),
			config->GetMiniDumpVerbosityLevel(),
			config->ShouldAlwaysFlushTracing(),
			config->GetCallTracingFlags()
		);

		tracer::Trace::SetTracingEnabled(true);

		tracer::Trace trace { nullptr, __FUNCTION__ };

		init_options = std::make_unique<InitOptionsModern>(initOptions);

		assign_func(real_init, (gameserver ? "InitGameServer" : "Init"));
		assign_func(real_process_data, (gameserver ? "ProcessGameServerData" : "ProcessData"));
		assign_func(real_shutdown, (gameserver ? "ShutdownGameServer" : "Shutdown"));

		if (config->OverrideInitKeysEnabled()) {
			init_options->clientID = config->GetOverrideInitKeyId();
			init_options->clientSecret = config->GetOverrideInitKeySecret();
		}

		interceptor_make_unique(notification, (gameserver ? "GameServerListenerRegistrar" : "ListenerRegistrar"));
		interceptor_make_unique(user, (gameserver ? "GameServerUser" : "User"));
		interceptor_make_unique(friends, "Friends");
		interceptor_make_unique(matchmaking, (gameserver ? "GameServerMatchmaking" : "MatchMaking"));
		interceptor_make_unique(networking, (gameserver ? "GameServerNetworking" : "Networking"));
		interceptor_make_unique(server_networking, "ServerNetworking");
		interceptor_make_unique(stats, "Stats");
		interceptor_make_unique(logger, this); // (gameserver ? "GameServerLogger" : "Logger")

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		interceptor_make_unique(chat, "Chat");
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		interceptor_make_unique(utils, (gameserver ? "GameServerUtils" : "Utils"));
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
		interceptor_make_unique(apps, "Apps");
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		interceptor_make_unique(storage, "Storage");
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
		interceptor_make_unique(cloud_storage, "CloudStorage");
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
		interceptor_make_unique(custom_networking, "CustomNetworking");
#endif
		
#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
		interceptor_make_unique(telemetry, (gameserver ? "GameServerTelemetry" : "Telemetry"));
#endif

		real_init(init_options->ToClassicOptions());

		if (config->OverrideSignInEnabled()) {
			user->USER_SIGN_IN_CREDENTIALS(
				config->GetOverrideSignInId().c_str(),
				config->GetOverrideSignInPassword().c_str()
			);
		}
	}

	InterfaceInstances::~InterfaceInstances() {
		tracer::Trace::SetTracingEnabled(false);
	}

	void InterfaceInstances::reset() {
		if (config == nullptr) {
			config = std::make_unique<ClientIniData>();
		}

		tracer::Trace::InitTracing(
			(fs::path(config->GetGameDataPath()) / "Interceptor").string().c_str(),
			config->IsUnhandledExceptionLoggingEnabled(),
			config->IsCallTracingEnabled(),
			config->CreateMiniDumpOnUnhandledException(),
			config->GetMiniDumpVerbosityLevel(),
			config->ShouldAlwaysFlushTracing(),
			config->GetCallTracingFlags()
		);

		real_init = nullptr;
		real_process_data = nullptr;
		real_shutdown = nullptr;

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
		telemetry = nullptr;
#endif

		logger = nullptr;
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
		custom_networking = nullptr;
#endif
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		storage = nullptr;
#endif
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
		cloud_storage = nullptr;
#endif
#if GALAXY_BUILD_FEATURE_HAS_IAPPS
		apps = nullptr;
#endif
#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		utils = nullptr;
#endif
		stats = nullptr;
		networking = nullptr;
		server_networking = nullptr;
		matchmaking = nullptr;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		chat = nullptr;
#endif
		friends = nullptr;
		user = nullptr;
		init_options = nullptr;
		notification = nullptr;
	}
}
