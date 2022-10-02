#include <Impl/Errors.hxx>
#include <UniverseLAN.hxx>

#include <Tracer.hxx>

#include <GalaxyFactory.h>

using namespace universelan::tracer;
namespace galaxy::api
{
	class GalaxyImpl : public IGalaxy
	{
	public:
		GalaxyImpl() {
			Trace trace{ __FUNCTION__ };
		}

		virtual ~GalaxyImpl() {
			Trace trace{ __FUNCTION__ };
		}

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
	
	class ErrorManager : public IErrorManager {
	public:
		int a = 0;
		int b = 0;
		int c = 0;

		virtual int Unknown1() override {
			Trace trace{ __FUNCTION__ };
			return 0;
		}

		virtual IErrorManager* Unknown2() override {
			Trace trace{ __FUNCTION__ };
			return this;
		}

		virtual int Unknown3() override {
			Trace trace{ __FUNCTION__ };
			return 0;
		}

		virtual ~ErrorManager() override {
			Trace trace{ __FUNCTION__ };
		}

		ErrorManager() {
			Trace trace{ __FUNCTION__ };
		}
	};

	IGalaxy* GalaxyFactory::instance{nullptr};
	IErrorManager* GalaxyFactory::errorManager{ nullptr };

	IGalaxy* GalaxyFactory::GetInstance(
		//uint32_t a, uint32_t b
	) {
		Trace trace{ __FUNCTION__ };

		//std::cout << __FUNCTION__ ": " << a << ", " << b << std::endl;

		//int __this;
		//using _DWORD = unsigned int;
		//
		//__this = (int)galaxy::api::GalaxyFactory::GetErrorManager();
		//
		//_DWORD vtable = *(_DWORD*)__this;
		//_DWORD func = vtable + 4;
		//
		//using some_t = void(__thiscall**)(int);
		//some_t casted_func = (some_t)func;
		//auto the_function = *casted_func;
		//the_function(__this);

		if (instance == nullptr) {
			instance = new GalaxyImpl();
		}

		return instance;
	}

	IErrorManager* GalaxyFactory::GetErrorManager() {
		Trace trace{ __FUNCTION__ };

		if (errorManager == nullptr) {
			errorManager = new ErrorManager();
		}

		const int x = sizeof(ErrorManager);
		static_assert(x == 0x10);

		return errorManager;
	}

	void GalaxyFactory::ResetInstance() {
		Trace trace{ __FUNCTION__ };

		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}

	IGalaxy* GalaxyFactory::CreateInstance() {
		Trace trace{ __FUNCTION__ };

		if (instance == nullptr) {
			instance = new GalaxyImpl();
		}

		return instance;
	}
}
