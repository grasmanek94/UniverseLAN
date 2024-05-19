#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

bool lobby_joined = false;

void OnLobbyList(uint32_t lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
	, LobbyListResult result
#else
	, bool ioFailure
#endif
) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	if (!lobbyCount) {
		return;
	}

	lobby_joined = true;
	matchmaking_ptr->JoinLobby(matchmaking_ptr->GetLobbyByIndex(0));
}

void perform_test() {
	delay_runner.Add([&]() {
		auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

		matchmaking_ptr->RequestLobbyList(
#if GALAXY_BUILD_FEATURE_HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL
			true
#endif
		);
		});
}
void register_listeners() {
	// leak it, don't care
	new LobbyListListenerImplGlobal{ OnLobbyList };
}

bool should_keep_running() {
	return true; 
}
