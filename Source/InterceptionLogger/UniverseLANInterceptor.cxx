#include "UniverseLANInterceptor.hxx"

#include "Impl/InitOptionsModern.hxx"

#include "SharedLibUtils.hxx"

#include <IniData.hxx>
#include <Tracer.hxx>

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
#include <Errors.h>
#endif

#include <filesystem>
#include <memory>

#ifdef _WIN32
#include <Windows.h>
#endif
/*
  x86 Factory:

  ??0IGalaxy@api@galaxy@@QAE@ABV012@@Z									== public:			__thiscall galaxy::api::IGalaxy::IGalaxy(class galaxy::api::IGalaxy const &)											[constructor]
  ??0IGalaxy@api@galaxy@@QAE@XZ											== public:			__thiscall galaxy::api::IGalaxy::IGalaxy(void)																			[constructor]
  ??1IGalaxy@api@galaxy@@UAE@XZ											== public: virtual	__thiscall galaxy::api::IGalaxy::~IGalaxy(void)																			[destructor]
  ??4GalaxyFactory@api@galaxy@@QAEAAV012@ABV012@@Z						== public: class galaxy::api::GalaxyFactory &	__thiscall galaxy::api::GalaxyFactory::operator=(class galaxy::api::GalaxyFactory const &)	[assignment operator]
  ??4IGalaxy@api@galaxy@@QAEAAV012@ABV012@@Z							== public: class galaxy::api::IGalaxy &			__thiscall galaxy::api::IGalaxy::operator=(class galaxy::api::IGalaxy const &)				[assignment operator]

  ??_7IGalaxy@api@galaxy@@6B@											== const galaxy::api::IGalaxy::`vftable'																									[vtable]

  ?CreateInstance@GalaxyFactory@api@galaxy@@SAPAVIGalaxy@23@XZ			== public: static class galaxy::api::IGalaxy * __cdecl galaxy::api::GalaxyFactory::CreateInstance(void)										[public method]
  ?GetErrorManager@GalaxyFactory@api@galaxy@@SAPAVIErrorManager@23@XZ	== public: static class galaxy::api::IErrorManager * __cdecl galaxy::api::GalaxyFactory::GetErrorManager(void)								[public method]
  ?GetInstance@GalaxyFactory@api@galaxy@@SAPAVIGalaxy@23@XZ				== public: static class galaxy::api::IGalaxy * __cdecl galaxy::api::GalaxyFactory::GetInstance(void)										[public method]
  ?ResetInstance@GalaxyFactory@api@galaxy@@SAXXZ						== public: static void __cdecl galaxy::api::GalaxyFactory::ResetInstance(void)																[public method]

  ?errorManager@GalaxyFactory@api@galaxy@@0PAVIErrorManager@23@A		== private: static class galaxy::api::IErrorManager * galaxy::api::GalaxyFactory::errorManager												[private static variable]
  ?instance@GalaxyFactory@api@galaxy@@0PAVIGalaxy@23@A					== private: static class galaxy::api::IGalaxy * galaxy::api::GalaxyFactory::instance														[private static variable]

  ---

  x64 Factory:

  ??0IGalaxy@api@galaxy@@QEAA@AEBV012@@Z								== public: __cdecl galaxy::api::IGalaxy::IGalaxy(class galaxy::api::IGalaxy const & __ptr64) __ptr64																				
  ??0IGalaxy@api@galaxy@@QEAA@XZ 										== public: __cdecl galaxy::api::IGalaxy::IGalaxy(void) __ptr64 										 
  ??1IGalaxy@api@galaxy@@UEAA@XZ 										== public: virtual __cdecl galaxy::api::IGalaxy::~IGalaxy(void) __ptr64 										 
  ??4GalaxyFactory@api@galaxy@@QEAAAEAV012@AEBV012@@Z 					== public: class galaxy::api::GalaxyFactory & __ptr64 __cdecl galaxy::api::GalaxyFactory::operator=(class galaxy::api::GalaxyFactory const & __ptr64) __ptr64 					 
  ??4IGalaxy@api@galaxy@@QEAAAEAV012@AEBV012@@Z 						== public: class galaxy::api::IGalaxy & __ptr64 __cdecl galaxy::api::IGalaxy::operator=(class galaxy::api::IGalaxy const & __ptr64) __ptr64 	

  ??_7IGalaxy@api@galaxy@@6B@ 											== const galaxy::api::IGalaxy::`vftable' 			

  ?CreateInstance@GalaxyFactory@api@galaxy@@SAPEAVIGalaxy@23@XZ 		== public: static class galaxy::api::IGalaxy * __ptr64 __cdecl galaxy::api::GalaxyFactory::CreateInstance(void) 		 
  ?GetErrorManager@GalaxyFactory@api@galaxy@@SAPEAVIErrorManager@23@XZ 	== public: static class galaxy::api::IErrorManager * __ptr64 __cdecl galaxy::api::GalaxyFactory::GetErrorManager(void) 	 
  ?GetInstance@GalaxyFactory@api@galaxy@@SAPEAVIGalaxy@23@XZ 			== public: static class galaxy::api::IGalaxy * __ptr64 __cdecl galaxy::api::GalaxyFactory::GetInstance(void) 			 
  ?ResetInstance@GalaxyFactory@api@galaxy@@SAXXZ 						== public: static void __cderecl galaxy::api::GalaxyFactory::ResetInstance(void) 		

  ?errorManager@GalaxyFactory@api@galaxy@@0PEAVIErrorManager@23@EA 		== private: static class galaxy::api::IErrorManager * __ptr64 __ptr64 galaxy::api::GalaxyFactory::errorManager 		 
  ?instance@GalaxyFactory@api@galaxy@@0PEAVIGalaxy@23@EA 				== private: static class galaxy::api::IGalaxy * __ptr64 __ptr64 galaxy::api::GalaxyFactory::instance 				 

*/

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
		void interceptor_make_unique(std::unique_ptr<T>& ptr, ClientIniData* t) {
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

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY

		assign_func(real_factory_create_instance, "?CreateInstance@GalaxyFactory@api@galaxy@");
		assign_func(real_factory_get_error_manager, "?GetErrorManager@GalaxyFactory@api@galaxy@");
		assign_func(real_factory_get_instance, "?GetInstance@GalaxyFactory@api@galaxy@");
		assign_func(real_factory_reset_instance, "?ResetInstance@GalaxyFactory@api@galaxy@");

		real_igalaxy_instance = real_factory_create_instance();
		real_ierror_manager = real_factory_get_error_manager();

		real_init = [this](InitOptionsImpl initOptions) -> void {
			try {
				if (initOptions.galaxyPeerPath == nullptr || *initOptions.galaxyPeerPath == '\0') {
					initOptions.galaxyPeerPath = ".";
				}
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
				real_igalaxy_instance->Init(initOptions);
#else
				real_igalaxy_instance->Init(initOptions.clientID, initOptions.clientSecret, initOptions.galaxyPeerPath);
#endif
			}
			catch (const IError& error) {
#ifdef _WIN32
				MessageBoxA(NULL, error.GetMsg(), error.GetName(), 0);
#endif
				std::cerr << "Error: " << error.GetMsg() << std::endl;
			}
		};

		real_process_data = std::bind(&IGalaxy::ProcessData, real_igalaxy_instance);
		real_shutdown = std::bind(&IGalaxy::Shutdown, real_igalaxy_instance);

		real_init(init_options->ToClassicOptions());

		auto real_notification_ptr = std::bind(&IGalaxy::GetListenerRegistrar, real_igalaxy_instance);
		auto real_notification = real_notification_ptr();

		notification = std::make_unique<ListenerRegistrarImpl>(real_notification_ptr);
		error = std::make_unique<Error>(std::bind(&IGalaxy::GetError, real_igalaxy_instance));
		user = std::make_unique<UserImpl>(std::bind(&IGalaxy::GetUser, real_igalaxy_instance), real_notification, config.get());
		friends = std::make_unique<FriendsImpl>(std::bind(&IGalaxy::GetFriends, real_igalaxy_instance), real_notification);
		matchmaking = std::make_unique<MatchmakingImpl>(std::bind(&IGalaxy::GetMatchmaking, real_igalaxy_instance), real_notification);
		networking = std::make_unique<NetworkingImpl>(std::bind(&IGalaxy::GetNetworking, real_igalaxy_instance), real_notification, gameserver ? 'G' : 'C');

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
		server_networking = std::make_unique<NetworkingImpl>(std::bind(&IGalaxy::GetServerNetworking, real_igalaxy_instance), real_notification, gameserver ? 'G' : 'S');
#endif

		stats = std::make_unique<StatsImpl>(std::bind(&IGalaxy::GetStats, real_igalaxy_instance), real_notification);
		logger = std::make_unique<LoggerImpl>(config.get());

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		chat = std::make_unique<ChatImpl>(std::bind(&IGalaxy::GetChat, real_igalaxy_instance), real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		utils = std::make_unique<UtilsImpl>(std::bind(&IGalaxy::GetUtils, real_igalaxy_instance), real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
		apps = std::make_unique<AppsImpl>(std::bind(&IGalaxy::GetApps, real_igalaxy_instance), real_notification, config->GetEnableAllDLC());
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		storage = std::make_unique<StorageImpl>(std::bind(&IGalaxy::GetStorage, real_igalaxy_instance), real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
		cloud_storage = std::make_unique<CloudStorageImpl>(std::bind(&IGalaxy::GetCloudStorage, real_igalaxy_instance), real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
		custom_networking = std::make_unique<CustomNetworkingImpl>(std::bind(&IGalaxy::GetCustomNetworking, real_igalaxy_instance), real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
		telemetry = std::make_unique<TelemetryImpl>(std::bind(&IGalaxy::GetTelemetry, real_igalaxy_instance), real_notification);
#endif

#else

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
		interceptor_make_unique(networking, (gameserver ? "?GameServerNetworking@api@galaxy@" : "?Networking@api@galaxy@"), real_notification, gameserver ? 'G' : 'C');

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
		interceptor_make_unique(server_networking, "?ServerNetworking@api@galaxy@", real_notification, gameserver ? 'G' : 'S');
#endif

		interceptor_make_unique(stats, "?Stats@api@galaxy@", real_notification);
		interceptor_make_unique(logger, config.get()); // (gameserver ? "?GameServerLogger@api@galaxy@" : "?Logger@api@galaxy@")

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		interceptor_make_unique(chat, "?Chat@api@galaxy@", real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		interceptor_make_unique(utils, (gameserver ? "?GameServerUtils@api@galaxy@" : "?Utils@api@galaxy@"), real_notification);
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
		interceptor_make_unique(apps, "?Apps@api@galaxy@", real_notification, config->GetEnableAllDLC());
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

#endif
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
#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
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
