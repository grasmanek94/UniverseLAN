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
			// REVIEW: throwExceptions is ignored, so callers cannot select the
			// documented throwing/non-throwing behavior. Honor the flag or
			// consistently translate failures to the documented error.

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
			// REVIEW: galaxyPeerPath is accepted by the ABI but discarded; InitLocal
			// therefore cannot load the caller-selected Galaxy peer/configuration.
			// Preserve and pass this path through the initialization options.

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
			// REVIEW: Always returning nullptr hides every initialization/API error,
			// violating IErrorManager's observable contract. Store and return the
			// last translated error (or explicitly report unsupported behavior).
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
			// REVIEW: This lazy singleton is a plain pointer. Concurrent first calls
			// race on the read/write and can publish different GalaxyImpl objects;
			// use std::call_once (and synchronize Reset) or require single-threaded use.
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
#if GALAXY_BUILD_FEATURE_HAS_IERRORMANAGER
		// REVIEW: GetErrorManager allocates a separate factory-owned object, but
		// Reset currently leaves it alive. Release it under the same synchronized
		// lifecycle policy as instance to avoid a leak across resets.
#endif
	}

	IGalaxy* FACTORY_CALLTYPE GalaxyFactory::CreateInstance() {
		if (instance == nullptr) {
			// REVIEW: CreateInstance duplicates the unsynchronized lazy publication
			// in GetInstance. Concurrent callers can race and leak one instance;
			// share a synchronized initialization path with GetInstance.
			instance = new GalaxyImpl();
		}

		return instance;
	}
}

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	return universelan::client::load();
}
#endif
