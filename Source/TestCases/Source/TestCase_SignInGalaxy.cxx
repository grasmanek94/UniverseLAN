#include <TestCaseClientDetails.hxx>

#if !GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINGALAXY
#define SignInGalaxy SignIn
#endif

int main()
{
	tracer::Trace::InitTracing("TestLog", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(false);

	tracer::Trace trace{ "", __FUNCTION__ };

	GALAXY_INIT();

	bool signed_in = false;
    auto end_time = std::chrono::steady_clock::now();

	AuthListenerImplGlobal global_auth_listener{ [&](void) -> void {
		end_time = std::chrono::steady_clock::now() + std::chrono::seconds(5);
		signed_in = true;	
	} };

	GET_GALAXY_API(User())->SignInGalaxy();

	while (!signed_in || (std::chrono::steady_clock::now() < end_time))
	{
		GET_GALAXY_API_AS_IS(ProcessData());

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	GALAXY_DEINIT();

	return 0;
}
