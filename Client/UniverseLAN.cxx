#include "UniverseLAN.hxx"

#include "Client.hxx"

#include <IniData.hxx>
#include <Tracer.hxx>

#include <filesystem>
#include <memory>

namespace universelan::client {
	using namespace galaxy::api;
	namespace fs = std::filesystem;
	InterfaceInstances intf_inst;

	void InterfaceInstances::init(const InitOptions& initOptions) {
		if (config == nullptr) {
			config = std::make_unique<ClientIniData>();
		}

		tracer::Trace::InitTracing(
			(fs::path(config->GetGameDataPath()) / "Tracing").string().c_str(),
			config->IsUnhandledExceptionLoggingEnabled(),
			config->IsCallTracingEnabled(),
			config->CreateMiniDumpOnUnhandledException(),
			config->GetMiniDumpVerbosityLevel(),
			config->ShouldAlwaysFlushTracing()
		);

		tracer::Trace::SetTracingEnabled(true);

		tracer::Trace trace{ __FUNCTION__ };

		delay_runner = std::make_unique<DelayRunner>(); // No 'this' on purpose

		init_options = std::make_unique<InitOptionsModern>(initOptions);
		notification = std::make_unique<ListenerRegistrarImpl>(this, delay_runner.get());
		client = std::make_unique<Client>(this);
		user = std::make_unique<UserImpl>(this);
		friends = std::make_unique<FriendsImpl>(this);
		chat = std::make_unique<ChatImpl>(this);
		matchmaking = std::make_unique<MatchmakingImpl>(this);
		networking = std::make_unique<NetworkingImpl>(this);
		stats = std::make_unique<StatsImpl>(this);
		utils = std::make_unique<UtilsImpl>(this);
		apps = std::make_unique<AppsImpl>(this);
		storage = std::make_unique<StorageImpl>(this);
		custom_networking = std::make_unique<CustomNetworkingImpl>(this);
		logger = std::make_unique<LoggerImpl>(this);
		telemetry = std::make_unique<TelemetryImpl>(this);
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

		tracer::Trace::InitTracing(
			(fs::path(config->GetGameDataPath()) / "Tracing").string().c_str(),
			config->IsUnhandledExceptionLoggingEnabled(),
			config->IsCallTracingEnabled(),
			config->CreateMiniDumpOnUnhandledException(),
			config->GetMiniDumpVerbosityLevel(),
			config->ShouldAlwaysFlushTracing()
		);

		delay_runner = nullptr;

		if (client) {
			client->Stop();
		}

		telemetry = nullptr;
		logger = nullptr;
		custom_networking = nullptr;
		storage = nullptr;
		apps = nullptr;
		utils = nullptr;
		stats = nullptr;
		networking = nullptr;
		matchmaking = nullptr;
		chat = nullptr;
		friends = nullptr;
		user = nullptr;
		init_options = nullptr;
		client = nullptr;
		notification = nullptr;
	}
}
