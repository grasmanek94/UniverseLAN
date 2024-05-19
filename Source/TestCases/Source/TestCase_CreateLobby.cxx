#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

void perform_test() {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	matchmaking_ptr->CreateLobby(LobbyType::LOBBY_TYPE_PUBLIC, 4
#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
		, true, LobbyTopologyType::LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION
#endif
	);
}

void register_listeners() {}
bool should_keep_running() { return true; }
