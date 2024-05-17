#include "UniverseLAN.hxx"

#include "Client.hxx"

#include <EnvUtils.hxx>
#include <IniData.hxx>
#include <SharedFileUtils.hxx>
#include <Tracer.hxx>

#include <filesystem>
#include <memory>

namespace universelan::client {
	using namespace galaxy::api;
	namespace fs = std::filesystem;
	InterfaceInstances intf_inst;

	void InterfaceInstances::init(const InitOptionsModern& initOptions, bool is_gameserver) {
		if (config == nullptr) {
			config = std::make_unique<ClientIniData>();
		}

		if (sfu == nullptr) {
			sfu = std::make_unique<SharedFileUtils>(env_utils::get_gamedata_path_prefix() + config->GetGameDataPath());
		}

		tracer::Trace::InitTracing(
			(fs::path(config->GetGameDataPath()) / "Tracing").string().c_str(),
			config->IsUnhandledExceptionLoggingEnabled(),
			config->IsCallTracingEnabled(),
			config->CreateMiniDumpOnUnhandledException(),
			config->GetMiniDumpVerbosityLevel(),
			config->ShouldAlwaysFlushTracing(),
			config->GetCallTracingFlags()
		);

		tracer::Trace::SetTracingEnabled(true);

		tracer::Trace trace { nullptr, __FUNCTION__ };
		
		delay_runner = std::make_unique<DelayRunner>(); // No 'this' on purpose

		init_options = std::make_unique<InitOptionsModern>(initOptions);
		notification = std::make_unique<ListenerRegistrarImpl>(this, delay_runner.get());
		client = std::make_unique<Client>(this);
		user = std::make_unique<UserImpl>(this);
		friends = std::make_unique<FriendsImpl>(this);
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		chat = std::make_unique<ChatImpl>(this);
#endif
		matchmaking = std::make_unique<MatchmakingImpl>(this);
		networking = std::make_unique<NetworkingImpl>(this, is_gameserver ? 'G' : 'C');
#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
		server_networking = std::make_unique<NetworkingImpl>(this, is_gameserver ? 'G' : 'S');
#endif
		stats = std::make_unique<StatsImpl>(this);
#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		utils = std::make_unique<UtilsImpl>(this);
#endif
#if GALAXY_BUILD_FEATURE_HAS_IAPPS
		apps = std::make_unique<AppsImpl>(this);
#endif
#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		storage = std::make_unique<StorageImpl>(this);
#endif
#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE
		cloud_storage = std::make_unique<CloudStorageImpl>(this);
#endif
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
		custom_networking = std::make_unique<CustomNetworkingImpl>(this);
#endif
		logger = std::make_unique<LoggerImpl>(this);

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
		telemetry = std::make_unique<TelemetryImpl>(this);
#endif
	}

	InterfaceInstances::~InterfaceInstances() {
		tracer::Trace::SetTracingEnabled(false);

		if (client) {
			client->Stop();
		}
	}

	void InterfaceInstances::reset() {
		if (config == nullptr) {
			config = std::make_unique<ClientIniData>();
		}

		if (sfu == nullptr) {
			sfu = std::make_unique<SharedFileUtils>(env_utils::get_gamedata_path_prefix() + config->GetGameDataPath());
		}

		tracer::Trace::InitTracing(
			(fs::path(config->GetGameDataPath()) / "Tracing").string().c_str(),
			config->IsUnhandledExceptionLoggingEnabled(),
			config->IsCallTracingEnabled(),
			config->CreateMiniDumpOnUnhandledException(),
			config->GetMiniDumpVerbosityLevel(),
			config->ShouldAlwaysFlushTracing(),
			config->GetCallTracingFlags()
		);

		delay_runner = nullptr;

		if (client) {
			client->Stop();
		}

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
		client = nullptr;
		notification = nullptr;
	}
}
