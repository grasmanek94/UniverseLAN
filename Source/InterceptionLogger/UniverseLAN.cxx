#include "UniverseLAN.hxx"

#include "SharedLibUtils.hxx"

#include <IniData.hxx>
#include <Tracer.hxx>

#include <filesystem>
#include <memory>

namespace universelan::client {
	using namespace galaxy::api;
	namespace fs = std::filesystem;
	InterfaceInstances intf_inst;

	namespace {
		template <typename T>
		void interceptor_make_unique(std::unique_ptr<T>& ptr, const char* name) {
			ptr = std::make_unique<T>(SharedLibUtils::get_func<T::FuncPtr>(name));
		}
	}

	void InterfaceInstances::init(const InitOptionsModern& initOptions) {
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

		auto real_init = SharedLibUtils::get_func<std::function<GALAXY_DLL_EXPORT void GALAXY_CALLTYPE(struct InitOptions const& initOptions)>>("Init");

		if (config->OverrideInitKeysEnabled()) {
			init_options->clientID = config->GetOverrideInitKeyId();
			init_options->clientSecret = config->GetOverrideInitKeySecret();
		}

		interceptor_make_unique(notification, "ListenerRegistrar");

		interceptor_make_unique(user, "User");
		interceptor_make_unique(friends, "Friends");
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		interceptor_make_unique(chat, "Chat");
#endif
		interceptor_make_unique(matchmaking, "MatchMaking");
		interceptor_make_unique(networking, "Networking");
		interceptor_make_unique(server_networking, "ServerNetworking");
		interceptor_make_unique(stats, "Stats");
#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		interceptor_make_unique(utils, "Utils");
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
		interceptor_make_unique(logger, "Logger");
#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
		interceptor_make_unique(telemetry, "Telemetry");
#endif

		galaxy::api::InitOptions classic_init_options{
			init_options->clientID.c_str(),
			init_options->clientSecret.c_str(),
			init_options->configFilePath.c_str(),
			init_options->galaxyAllocator,
			init_options->storagePath.c_str(),
			init_options->host.c_str(),
			init_options->port,
			init_options->galaxyThreadFactory
		};

		real_init(classic_init_options);
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
