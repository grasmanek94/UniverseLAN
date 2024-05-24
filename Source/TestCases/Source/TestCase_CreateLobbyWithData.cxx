#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

GalaxyID my_lobby_id = 0;

std::string GetTimeNow() {
	auto time_now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return std::to_string(time_now);
}

void TimerThread() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		delay_runner.Add([]() {
			std::string time_now = GetTimeNow();
			tracer::Trace::write_all(
				std::format(
					"key: {} value: {}",
					"timer", time_now
				));

			auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());
			matchmaking_ptr->SetLobbyData(my_lobby_id, "timer", time_now.c_str());
			});
	}
}

void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result)
{
	if (result != LobbyCreateResult::LOBBY_CREATE_RESULT_SUCCESS) {
		return;
	}

	my_lobby_id = lobbyID;

	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	for (auto& data_entry : LOBBY_TEST_DATA) {
		matchmaking_ptr->SetLobbyData(lobbyID, data_entry[0].data(), data_entry[1].data());
	}

	matchmaking_ptr->SetLobbyData(lobbyID, "timer", GetTimeNow().c_str());

	std::thread{ TimerThread }.detach(); // !!! LEAK !!! (until thread exits)
}

void perform_test() {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	matchmaking_ptr->CreateLobby(LobbyType::LOBBY_TYPE_PUBLIC, 4
#if GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
		, true, LobbyTopologyType::LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION
#endif
	);
}

void register_listeners() {
	// just leak it, don't care
	new LobbyCreatedListenerImplGlobal{ OnLobbyCreated };
}

bool should_keep_running() {
	return true;
}
