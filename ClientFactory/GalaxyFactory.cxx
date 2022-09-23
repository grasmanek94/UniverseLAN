#define IErrorManager void

#include <GalaxyFactory.h>
#include <IGalaxy.h>

#include <UniverseLAN.hxx>

namespace galaxy::api
{
	class GALAXY_DLL_EXPORT GalaxyImpl : public IGalaxy
	{
	public:
		GalaxyImpl() {}

		virtual ~GalaxyImpl() {}

		virtual void Init(const char* clientID, const char* clientSecret, bool throwExceptions = true) {
			InitOptions options{ clientID, clientSecret };
			galaxy::api::Init(options);
		}

		virtual void InitLocal(const char* clientID, const char* clientSecret, const char* galaxyPeerPath = ".", bool throwExceptions = true) {
			InitOptions options{ clientID, clientSecret };
			galaxy::api::Init(options);
		}

		virtual void Shutdown() {
			galaxy::api::Shutdown();
		}

		virtual IUser* GetUser() const {
			return galaxy::api::User();
		}

		virtual IFriends* GetFriends() const {
			return galaxy::api::Friends();
		}

		virtual IMatchmaking* GetMatchmaking() const {
			return galaxy::api::Matchmaking();
		}

		virtual INetworking* GetNetworking() const {
			return galaxy::api::Networking();
		}

		virtual INetworking* GetServerNetworking() const {
			return galaxy::api::GameServerNetworking();
		}

		virtual IStats* GetStats() const {
			return galaxy::api::Stats();
		}

		virtual IUtils* GetUtils() const {
			return galaxy::api::Utils();
		}

		virtual IApps* GetApps() const {
			return galaxy::api::Apps();
		}

		virtual IListenerRegistrar* GetListenerRegistrar() const {
			return galaxy::api::ListenerRegistrar();
		}

		virtual ILogger* GetLogger() const {
			return galaxy::api::Logger();
		}

		virtual void ProcessData() {
			galaxy::api::ProcessData();
		}

		virtual const IError* GetError() const {
			return galaxy::api::GetError();
		}
	};

	IGalaxy* GalaxyFactory::instance{nullptr}; 
	IErrorManager* GalaxyFactory::errorManager{ nullptr };

	IGalaxy* GALAXY_CALLTYPE GalaxyFactory::GetInstance() {
		return instance;
	}

	IErrorManager* GALAXY_CALLTYPE GalaxyFactory::GetErrorManager() {
		return nullptr;
	}

	void GALAXY_CALLTYPE GalaxyFactory::ResetInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}

	IGalaxy* GALAXY_CALLTYPE GalaxyFactory::CreateInstance() {
		if (instance == nullptr) {
			instance = new GalaxyImpl();
		}

		return instance;
	}
}