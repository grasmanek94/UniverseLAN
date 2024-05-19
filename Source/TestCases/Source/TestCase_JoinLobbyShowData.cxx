#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

bool lobby_joined = false;

void OnLobbyList(uint32_t lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
	, LobbyListResult result
#else
	, bool result
#endif
) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	tracer::Trace::write_all(
		std::format(
			"OnLobbyList lobbyCount: {} result: {}",
			lobbyCount, 
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
			magic_enum::enum_name(result)
#else
			result
#endif
		));

	for (uint32_t i = 0; i < lobbyCount; ++i) {
		GalaxyID lobby_id = matchmaking_ptr->GetLobbyByIndex(i);

		tracer::Trace::write_all(
			std::format(
				"i: {} lobby_id: {}",
				i, lobby_id
			));

		delay_runner.Add([=]() {
			matchmaking_ptr->RequestLobbyData(lobby_id);
		});
	}
}

void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	for (auto& data_entry : LOBBY_TEST_DATA) {
		std::string result{ matchmaking_ptr->GetLobbyData(lobbyID, data_entry[0].data()) };

		tracer::Trace::write_all(
			std::format(
				"key: {} value: {} result: {} check: {}",
				data_entry[0], data_entry[1], result, (data_entry[1] == result)
			));
	}

	std::string result{ matchmaking_ptr->GetLobbyData(lobbyID, "timer")};

	tracer::Trace::write_all(
		std::format(
			"key: {} value: {}",
			"timer", result
		));

	if (result.length() > 0 && !lobby_joined) {
		lobby_joined = true;
		tracer::Trace::write_all(
			std::format(
				"Join: {}",
				lobbyID
			));
		matchmaking_ptr->JoinLobby(lobbyID);
	}
}

void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	for (auto& data_entry : LOBBY_TEST_DATA) {
		std::string result{ matchmaking_ptr->GetLobbyData(lobbyID, data_entry[0].data()) };

		tracer::Trace::write_all(
			std::format(
				"key: {} value: {} result: {} check: {}",
				data_entry[0], data_entry[1], result, (data_entry[1] == result)
			));
	}

	std::string result{ matchmaking_ptr->GetLobbyData(lobbyID, "timer") };

	tracer::Trace::write_all(
		std::format(
			"key: {} value: {}",
			"timer", result
		));
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
	// just leak it, don't care
	new LobbyDataListenerImplGlobal{ OnLobbyDataUpdated };
#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
	new LobbyDataRetrieveListenerImplGlobal{ OnLobbyDataRetrieveSuccess };
#endif
	new LobbyListListenerImplGlobal{ OnLobbyList };
}

bool should_keep_running() {
	return true;
}
