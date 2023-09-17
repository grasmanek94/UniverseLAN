/**
 * @file
 * Includes all other files that are needed to work with the Galaxy library.
 */

#include "CustomConsole.hxx"
#include "UniverseLAN.hxx"

#include <Version.hxx>

namespace universelan::client {
	void Init(const InitOptions& initOptions) 
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
			MessageBox(NULL, ex.what(), "UniverseLAN - Error", 0);
		}

		tracer::Trace trace{  };

		if (intf_inst.config->GetEnableConsole()) {
			EnableCustomConsole();
		}

		std::cout << " == UniverseLAN Client == " << std::endl;
		std::cout << "Version: " << Version_Number << std::endl;
		std::cout << "Using username: " << intf_inst.config->GetCustomPersonaName() << std::endl;
		std::cout << "Using key: " << const_hash64(intf_inst.config->GetAuthenticationKey()) << std::endl;
		std::cout << "Using GalaxyID: " << intf_inst.config->GetCustomGalaxyID() << std::endl;

		intf_inst.client->Start();
	}

	void Shutdown() {
		tracer::Trace trace{  };

		intf_inst.reset();
	}

	IUser* User() {
		//tracer::Trace trace{  };

		return intf_inst.user.get();
	}

	IFriends* Friends() {
		//tracer::Trace trace{  };

		return intf_inst.friends.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	IChat* Chat() {
		//tracer::Trace trace{  };

		return intf_inst.chat.get();
	}
#endif

	IMatchmaking* Matchmaking() {
		//tracer::Trace trace{  };

		return intf_inst.matchmaking.get();
	}

	INetworking* Networking() {
		//tracer::Trace trace{  };

		return intf_inst.networking.get();
	}

	INetworking* ServerNetworking() {
		//tracer::Trace trace{  };

		return intf_inst.server_networking.get();
	}

	IStats* Stats() {
		//tracer::Trace trace{  };

		return intf_inst.stats.get();
	}

	IUtils* Utils() {
		//tracer::Trace trace{  };

		return intf_inst.utils.get();
	}

	IApps* Apps() {
		//tracer::Trace trace{  };

		return intf_inst.apps.get();
	}

	IStorage* Storage() {
		//tracer::Trace trace{  };

		return intf_inst.storage.get();
	}

	ICustomNetworking* CustomNetworking() {
		//tracer::Trace trace{  };

		return intf_inst.custom_networking.get();
	}

	ILogger* Logger() {
		//tracer::Trace trace{  };

		return intf_inst.logger.get();
	}

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	ITelemetry* Telemetry() {
		//tracer::Trace trace{  };

		return intf_inst.telemetry.get();
	}
#endif

	void ProcessData() {
		//tracer::Trace trace{  };

		if (intf_inst.client != nullptr) {
			intf_inst.client->ProcessEvents();
		}

		if (intf_inst.delay_runner != nullptr) {
			intf_inst.delay_runner->Run();
		}
	}

	IListenerRegistrar* ListenerRegistrar() {
		//tracer::Trace trace{  };

		return intf_inst.notification.get();
	}

	/*
	* Seems this gets called after each ProcessData call.
	*/
	const IError* GetError() {
		//tracer::Trace trace{  };

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
			Trace trace{  };
		}

		virtual ~GalaxyImpl() {
			Trace trace{  };
		}

		virtual void Init(const InitOptions& initOptions) override {
			universelan::client::Init(initOptions);
		}

		virtual void Init(const char* clientID, const char* clientSecret, bool throwExceptions = true) override {
			universelan::client::Init(InitOptions{ clientID, clientSecret, "", throwExceptions, "." });
		}

		virtual void InitLocal(const char* clientID, const char* clientSecret, const char* galaxyPeerPath = ".", bool throwExceptions = true) override {
			universelan::client::Init(InitOptions{ clientID, clientSecret, galaxyPeerPath, throwExceptions, "." });
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

		virtual IUtils* GetUtils() const override {
			return universelan::client::Utils();
		}

		virtual IApps* GetApps() const override {
			return universelan::client::Apps();
		}

		virtual IStorage* GetStorage() const override {
			return universelan::client::Storage();
		}

		virtual ICustomNetworking* GetCustomNetworking() const override {
			return universelan::client::CustomNetworking();
		}

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
			Trace trace{  };
		}

		ErrorManager() {
			Trace trace{  };
		}

		virtual api::IError* GetLastError() override {
			return nullptr;
		}
	};

	IGalaxy* GalaxyFactory::instance{ nullptr };
	IErrorManager* GalaxyFactory::errorManager{ nullptr };

	IGalaxy* GalaxyFactory::GetInstance() {
		if (instance == nullptr) {
			Trace trace{  };

			instance = new GalaxyImpl();
		}

		return instance;
	}

	IErrorManager* GalaxyFactory::GetErrorManager() {
		if (errorManager == nullptr) {
			Trace trace{  };

			errorManager = new ErrorManager();
		}

		return errorManager;
	}

	void GalaxyFactory::ResetInstance() {
		if (instance != nullptr) {
			Trace trace{  };

			delete instance;
			instance = nullptr;
		}
	}

	IGalaxy* GalaxyFactory::CreateInstance() {
		if (instance == nullptr) {
			Trace trace{  };

			instance = new GalaxyImpl();
		}

		return instance;
	}
}
#endif

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	universelan::tracer::Trace trace{  };

	return 0;
}
