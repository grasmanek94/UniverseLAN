#if GALAXY_BUILD_FEATURE_HAS_IGALAXY

#define CLIENT_FACTORY

#include "UniverseLAN.hxx"

#include <Tracer.hxx>
#include <GalaxyApi.h>

#include <GalaxyDLL.hxx>

#include <IGalaxy.h>

#if !GALAXY_BUILD_FEATURE_FACTORY_HAS_CALLTYPE
#define FACTORY_CALLTYPE 
#else
#define FACTORY_CALLTYPE GALAXY_CALLTYPE
#endif

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

#if GALAXY_BUILD_FEATURE_HAS_IERRORMANAGER
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
#endif

	IGalaxy* GalaxyFactory::instance{ nullptr };

#if GALAXY_BUILD_FEATURE_HAS_IERRORMANAGER
	IErrorManager* GalaxyFactory::errorManager{ nullptr };
#endif

	IGalaxy* FACTORY_CALLTYPE GalaxyFactory::GetInstance() {
		if (instance == nullptr) {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

			instance = new GalaxyImpl();
		}

		return instance;
	}

#if GALAXY_BUILD_FEATURE_HAS_IERRORMANAGER
	IErrorManager* FACTORY_CALLTYPE GalaxyFactory::GetErrorManager() {
		if (errorManager == nullptr) {
			//Trace trace { nullptr, __FUNCTION__, tracer::Trace::GALAXYDLL };

			errorManager = new ErrorManager();
		}

		return errorManager;
	}
#endif

#if GALAXY_BUILD_FEATURE_FACTORY_RESET_RENAMED_TO_RESETINSTANCE
	void FACTORY_CALLTYPE GalaxyFactory::ResetInstance()
#else
	void FACTORY_CALLTYPE GalaxyFactory::Reset()
#endif
	{
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}

	IGalaxy* FACTORY_CALLTYPE GalaxyFactory::CreateInstance() {
		if (instance == nullptr) {
			instance = new GalaxyImpl();
		}

		return instance;
	}
}

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	return universelan::client::load();
}
#endif
