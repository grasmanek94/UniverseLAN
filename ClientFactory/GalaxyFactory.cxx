#include <UniverseLAN.hxx>

#define IErrorManager void

#undef GALAXY_CALLTYPE
#undef GALAXY_DLL_EXPORT

#define GALAXY_DLL_EXPORT __declspec(dllexport)
#define GALAXY_CALLTYPE __cdecl

#include <GalaxyFactory.h>

namespace galaxy::api
{
	class GalaxyImpl : public IGalaxy
	{
	public:
		GalaxyImpl() {}

		virtual ~GalaxyImpl() {}

		virtual void Init(const char* clientID, const char* clientSecret, bool throwExceptions = true) override {
			InitOptions options{ clientID, clientSecret };
			galaxy::api::Init(options);
		}

		virtual void InitLocal(const char* clientID, const char* clientSecret, const char* galaxyPeerPath = ".", bool throwExceptions = true) override {
			InitOptions options{ clientID, clientSecret };
			galaxy::api::Init(options);
		}

		virtual void Shutdown() override {
			galaxy::api::Shutdown();
		}

		virtual IUser* GetUser() const override {
			return galaxy::api::User();
		}

		virtual IFriends* GetFriends() const override {
			return galaxy::api::Friends();
		}

		virtual IMatchmaking* GetMatchmaking() const override {
			return galaxy::api::Matchmaking();
		}

		virtual INetworking* GetNetworking() const override {
			return galaxy::api::Networking();
		}

		virtual INetworking* GetServerNetworking() const override {
			return galaxy::api::GameServerNetworking();
		}

		virtual IStats* GetStats() const override {
			return galaxy::api::Stats();
		}

		virtual IUtils* GetUtils() const override {
			return galaxy::api::Utils();
		}

		virtual IApps* GetApps() const override {
			return galaxy::api::Apps();
		}

		virtual IListenerRegistrar* GetListenerRegistrar() const override {
			return galaxy::api::ListenerRegistrar();
		}

		virtual ILogger* GetLogger() const override {
			return galaxy::api::Logger();
		}

		virtual void ProcessData() override {
			galaxy::api::ProcessData();
		}

		virtual const IError* GetError() const override {
			return galaxy::api::GetError();
		}
	};
	 
	IGalaxy* GalaxyFactory::instance{nullptr}; 
	IErrorManager* GalaxyFactory::errorManager{ nullptr };

	IGalaxy* GalaxyFactory::GetInstance() {
		return CreateInstance();
	}

	IErrorManager* GalaxyFactory::GetErrorManager() {
		return (IErrorManager*)1;
	}

	void GalaxyFactory::ResetInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}

	IGalaxy* GalaxyFactory::CreateInstance() {
		if (instance == nullptr) {
			instance = new GalaxyImpl();
		}

		return instance;
	}
}