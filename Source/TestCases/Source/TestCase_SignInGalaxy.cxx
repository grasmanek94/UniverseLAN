#include <TestCaseClientDetails.hxx>

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
#define GET_GALAXY_API(what) galaxy_api->Get ## what
#define GET_GALAXY_API_AS_IS(what) galaxy_api->what

galaxy::api::IGalaxy* galaxy_api = nullptr;
#else
#define GET_GALAXY_API(what) galaxy::api::what
#define GET_GALAXY_API_AS_IS(what) galaxy::api::what
#endif

#if !GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINGALAXY
#define SignInGalaxy SignIn
#endif

int main()
{
	tracer::Trace::InitTracing("TestLog", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(true);

	tracer::Trace trace{ "", __FUNCTION__ };

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
	galaxy::api::InitOptions options(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data());
#endif

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
	galaxy_api = galaxy::api::GalaxyFactory::CreateInstance();
#endif

	try {
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
		GET_GALAXY_API_AS_IS(Init(options));
#else
		GET_GALAXY_API_AS_IS(Init(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data()));
#endif
	}
	catch (const IError& err) {
		std::cerr << err.GetMsg() << std::endl;
	}

	bool signed_in = false;
    auto end_time = std::chrono::steady_clock::now();

	AuthListenerImplGlobal global_auth_listener{ [&](void) -> void {
		end_time = std::chrono::steady_clock::now() + std::chrono::seconds(5);
		signed_in = true;	
	} };

	GET_GALAXY_API(User())->SignInGalaxy();

	while (!signed_in || (end_time < std::chrono::steady_clock::now()))
	{
		GET_GALAXY_API_AS_IS(ProcessData());

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}
