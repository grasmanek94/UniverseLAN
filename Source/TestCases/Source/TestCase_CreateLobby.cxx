#include <TestCaseClientDetails.hxx>

#if !GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINGALAXY
#define SignInGalaxy SignIn
#endif

std::unique_ptr<tracer::Trace> trace{ nullptr };

int main()
{
	tracer::Trace::InitTracing("TestLog", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(false);
	tracer::Trace::SetTracingEnabled(false);

	GALAXY_INIT();

	trace = std::make_unique<tracer::Trace>("", "main");

	GET_GALAXY_API(User())->SignInGalaxy();

	TestInitListenerGlobal test_start_listener{ [&](void) -> void {
		tracer::Trace::SetTracingEnabled(true);
		trace = std::make_unique<tracer::Trace>("::INIT", "main");

		auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

		matchmaking_ptr->CreateLobby(LobbyType::LOBBY_TYPE_PUBLIC, 4
#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
			, true, LobbyTopologyType::LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION
#endif
		);
	} };

	while (true)
	{
		GET_GALAXY_API_AS_IS(ProcessData());

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	GALAXY_DEINIT();

	return 0;
}
