#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

GalaxyID my_lobby_id = 0;

long long GetTimeNow() {
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void TimerThread() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		delay_runner.Add([]() {
			uint64_t time_now = GetTimeNow();

			tracer::Trace::write_all(
				std::format(
					"key: {} value: {}",
					"timer", time_now
				));

			auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

			char* time_now_c = (char*)&time_now;
			char data[] = {
				0x42, // 'B'inary
				0x54, // 'T'ime
				0x00,
				0x00,
				time_now_c[0],
				time_now_c[1],
				time_now_c[2],
				time_now_c[3],
				time_now_c[4],
				time_now_c[5],
				time_now_c[6],
				time_now_c[7],
				0x00,
				0x00,
				0x00,
				0x00,
				0x3F,
				0x3F,
				0x00,
				0x00,
				(char)0xAA
			};

			matchmaking_ptr->SendLobbyMessage(my_lobby_id, data, sizeof(data));
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

	matchmaking_ptr->SetLobbyData(lobbyID, "timer", std::to_string(GetTimeNow()).c_str());

	std::thread{ TimerThread }.detach(); // !!! LEAK !!! (until thread exits)
}

void perform_test() {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	matchmaking_ptr->CreateLobby(LobbyType::LOBBY_TYPE_PUBLIC, 4
#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
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
