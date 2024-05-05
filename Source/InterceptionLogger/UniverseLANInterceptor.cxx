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
		T::FuncPtr interceptor_make_unique(std::unique_ptr<T>& ptr, const char* name) {
			typename T::FuncPtr real_func = SharedLibUtils::get_func<typename T::FuncPtr>(SharedLibUtils::get_function_match(name));
			ptr = std::make_unique<T>(real_func);
			return real_func;
		}

		template <typename T, typename U>
		T::FuncPtr interceptor_make_unique(std::unique_ptr<T>& ptr, const char* name, U listener_registerar) {
			typename T::FuncPtr real_func = SharedLibUtils::get_func<typename T::FuncPtr>(SharedLibUtils::get_function_match(name));
			ptr = std::make_unique<T>(real_func, listener_registerar);
			return real_func;
		}

		template <typename T, typename U, typename W>
		T::FuncPtr interceptor_make_unique(std::unique_ptr<T>& ptr, const char* name, U listener_registerar, W additional) {
			typename T::FuncPtr real_func = SharedLibUtils::get_func<typename T::FuncPtr>(SharedLibUtils::get_function_match(name));
			ptr = std::make_unique<T>(real_func, listener_registerar, additional);
			return real_func;
		}

		template <typename T>
		void interceptor_make_unique(std::unique_ptr<T>& ptr, InterfaceInstances* t) {
			ptr = std::make_unique<T>(t);
		}

		template <typename T>
		void assign_func(std::function<T>& ptr, const char* name) {
			ptr = SharedLibUtils::get_func<T*>(SharedLibUtils::get_function_match(name));
		}
	}

	void InterfaceInstances::init(const InitOptionsModern& initOptions, bool gameserver) {
		if (config == nullptr) {
			config = std::make_unique<ClientIniData>();
		}

		tracer::Trace::InitTracing(
			(fs::path(config->GetGameDataPath()) / "Interceptor" / "Tracing").string().c_str(),
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

		if (config->OverrideInitKeysEnabled()) {
			init_options->clientID = config->GetOverrideInitKeyId();
			init_options->clientSecret = config->GetOverrideInitKeySecret();
		}

		assign_func(real_init, (gameserver ? "?InitGameServer@api@galaxy@" : "?Init@api@galaxy@"));
		assign_func(real_process_data, (gameserver ? "?ProcessGameServerData" : "?ProcessData@api@galaxy@"));
		assign_func(real_shutdown, (gameserver ? "?ShutdownGameServer@api@galaxy@" : "?Shutdown@api@galaxy@"));

		real_init(init_options->ToClassicOptions());

		auto real_notification_ptr = interceptor_make_unique(notification, (gameserver ? "?GameServerListenerRegistrar@api@galaxy@" : "?ListenerRegistrar@api@galaxy@"));
		auto real_notification = real_notification_ptr();

		interceptor_make_unique(error, "?GetError@api@galaxy@");
		interceptor_make_unique(user, (gameserver ? "?GameServerUser@api@galaxy@" : "?User@api@galaxy@"), real_notification, config.get());
		interceptor_make_unique(friends, "?Friends@api@galaxy@", real_notification);
		interceptor_make_unique(matchmaking, (gameserver ? "?GameServerMatchmaking@api@galaxy@" : "?Matchmaking@api@galaxy@"), real_notification);
		interceptor_make_unique(networking, (gameserver ? "?GameServerNetworking@api@galaxy@" : "?Networking@api@galaxy@"), real_notification);

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKINGLISTENER
		interceptor_make_unique(server_networking, "?ServerNetworking@api@galaxy@", real_notification);
#endif

		interceptor_make_unique(stats, "?Stats@api@galaxy@", real_notification);
		interceptor_make_unique(logger, this); // (gameserver ? "?GameServerLogger@api@galaxy@" : "?Logger@api@galaxy@")

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		interceptor_make_unique(chat, "?Chat@api@galaxy@", real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		interceptor_make_unique(utils, (gameserver ? "?GameServerUtils@api@galaxy@" : "?Utils@api@galaxy@"), real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
		interceptor_make_unique(apps, "?Apps@api@galaxy@", real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		interceptor_make_unique(storage, "?Storage@api@galaxy@", real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
		interceptor_make_unique(cloud_storage, "?CloudStorage@api@galaxy@", real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
		interceptor_make_unique(custom_networking, "?CustomNetworking@api@galaxy@", real_notification);
#endif
		
#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
		interceptor_make_unique(telemetry, (gameserver ? "?GameServerTelemetry@api@galaxy@" : "?Telemetry@api@galaxy@"), real_notification);
#endif

		// TODO: improve this
		// if (config->OverrideSignInEnabled()) {
		// 	user->USER_SIGN_IN_CREDENTIALS(
		// 		config->GetOverrideSignInId().c_str(),
		// 		config->GetOverrideSignInPassword().c_str()
		// 	);
		// }
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
		error = nullptr;
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
#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKINGLISTENER
		server_networking = nullptr;
#endif
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
