/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "CustomConsole.hxx"
#include "UniverseLAN.hxx"

#include <Version.hxx>

namespace universelan::client {
	void Init(const InitOptionsModern& initOptions)
	{
#ifdef _WIN32
		{
			TCHAR szFileName[MAX_PATH];
			if (GetModuleFileName(NULL, szFileName, MAX_PATH) == ERROR_SUCCESS) {
				std::cout << "Process: " << szFileName << std::endl;
			}
		}
#endif

		try
		{
			intf_inst.init(initOptions);
		}
		catch (std::exception& ex) {

#ifdef _WIN32
			MessageBox(NULL, ex.what(), "UniverseLAN - Error", 0);
#else
			std::cout << "Exception occurred during init: " << ex.what() << std::endl;
#endif

		}

		tracer::Trace::SetLogToCout(intf_inst.config->ShouldTraceToConsole());

		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		if (intf_inst.config->GetEnableConsole()) {
			EnableCustomConsole();
		}

		std::cout << " == UniverseLAN Client == " << std::endl;
		std::cout << "Build: " << Version_Number << std::endl;
		std::cout << "Using username: " << intf_inst.config->GetCustomPersonaName() << std::endl;
		std::cout << "Using key: " << const_hash64(intf_inst.config->GetAuthenticationKey()) << std::endl;
		std::cout << "Using GalaxyID: " << intf_inst.config->GetCustomGalaxyID() << std::endl;

		intf_inst.client->Start();
	}

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
	void Init(const galaxy::api::InitOptions& initOptions) {
		universelan::client::Init(InitOptionsModern{ initOptions });
	}
#endif

	void Shutdown() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		intf_inst.reset();
	}

	IUser* User() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.user.get();
	}

	IFriends* Friends() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.friends.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	IChat* Chat() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.chat.get();
	}
#endif

	IMatchmaking* Matchmaking() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.matchmaking.get();
	}

	INetworking* Networking() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.networking.get();
	}

	INetworking* ServerNetworking() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.server_networking.get();
	}

	IStats* Stats() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.stats.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
	IUtils* Utils() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.utils.get();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
	IApps* Apps() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.apps.get();
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	IStorage* Storage() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.storage.get();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
	ICustomNetworking* CustomNetworking() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.custom_networking.get();
	}
#endif

	ILogger* Logger() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.logger.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	ITelemetry* Telemetry() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.telemetry.get();
	}
#endif

	void ProcessData() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		if (intf_inst.client != nullptr) {
			intf_inst.client->ProcessEvents();
		}

		if (intf_inst.delay_runner != nullptr) {
			intf_inst.delay_runner->Run();
		}
	}

	IListenerRegistrar* ListenerRegistrar() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return intf_inst.notification.get();
	}

	/*
	* Seems this gets called after each ProcessData call.
	*/
	const IError* GetError() {
		//tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

		return nullptr;
	}
}

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
#include <IGalaxy.h>

namespace galaxy::api
{
	using namespace universelan::tracer;
	class GalaxyImpl : public IGalaxy
	{
	public:
		GalaxyImpl() {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };
		}

		virtual ~GalaxyImpl() {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };
		}

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
		virtual void Init(const galaxy::api::InitOptions& initOptions) override {
			universelan::client::Init(initOptions);
		}
#endif

		virtual void Init(const char* clientID, const char* clientSecret, bool throwExceptions = true) override {
			universelan::client::InitOptionsImpl init_options{nullptr, nullptr};
			init_options.clientID = clientID;
			init_options.clientSecret = clientSecret;
			init_options.configFilePath = ".";
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_STORAGEPATH
			init_options.storagePath = "";
#endif

			// TODO: Implement throwExceptions

			universelan::client::Init(init_options);
		}

		virtual void InitLocal(const char* clientID, const char* clientSecret, const char* galaxyPeerPath = ".", bool throwExceptions = true) override {
			universelan::client::InitOptionsImpl init_options{ nullptr, nullptr };
			init_options.clientID = clientID;
			init_options.clientSecret = clientSecret;
			init_options.configFilePath = ".";
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_STORAGEPATH
			init_options.storagePath = "";
#endif

			// TODO: Implement throwExceptions

			universelan::client::Init(init_options);
		}

		virtual void Shutdown() override {
			universelan::client::Shutdown();
		}

		virtual IUser* GetUser() const override {
			return universelan::client::User();
		}

		virtual IFriends* GetFriends() const override {
			return universelan::client::Friends();
		}

		virtual IMatchmaking* GetMatchmaking() const override {
			return universelan::client::Matchmaking();
		}

		virtual INetworking* GetNetworking() const override {
			return universelan::client::Networking();
		}

		virtual INetworking* GetServerNetworking() const override {
			return universelan::client::ServerNetworking();
		}

		virtual IStats* GetStats() const override {
			return universelan::client::Stats();
		}

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		virtual IUtils* GetUtils() const override {
			return universelan::client::Utils();
		}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IAPPS
		virtual IApps* GetApps() const override {
			return universelan::client::Apps();
		}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		virtual IStorage* GetStorage() const override {
			return universelan::client::Storage();
		}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
		virtual ICustomNetworking* GetCustomNetworking() const override {
			return universelan::client::CustomNetworking();
		}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
		virtual IChat* GetChat() const override {
			return universelan::client::Chat();
		}
#endif

		virtual IListenerRegistrar* GetListenerRegistrar() const override {
			return universelan::client::ListenerRegistrar();
		}

		virtual ILogger* GetLogger() const override {
			return universelan::client::Logger();
		}

		virtual void ProcessData() override {
			universelan::client::ProcessData();
		}

		virtual const IError* GetError() const override {
			return universelan::client::GetError();
		}
	};

	class ErrorManager : public IErrorManager {
	public:
		virtual ~ErrorManager() override {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };
		}

		ErrorManager() {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };
		}

		virtual api::IError* GetLastError() override {
			return nullptr;
		}
	};

	IGalaxy* GalaxyFactory::instance{ nullptr };
	IErrorManager* GalaxyFactory::errorManager{ nullptr };

	IGalaxy* GalaxyFactory::GetInstance() {
		if (instance == nullptr) {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

			instance = new GalaxyImpl();
		}

		return instance;
	}

	IErrorManager* GalaxyFactory::GetErrorManager() {
		if (errorManager == nullptr) {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

			errorManager = new ErrorManager();
		}

		return errorManager;
	}

	void GalaxyFactory::ResetInstance() {
		if (instance != nullptr) {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

			delete instance;
			instance = nullptr;
		}
	}

	IGalaxy* GalaxyFactory::CreateInstance() {
		if (instance == nullptr) {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

			instance = new GalaxyImpl();
		}

		return instance;
	}
}
#endif

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	universelan::tracer::Trace trace { nullptr, __FUNCTION__, universelan::tracer::Trace::GALAXYDLL };

	return 0;
}
