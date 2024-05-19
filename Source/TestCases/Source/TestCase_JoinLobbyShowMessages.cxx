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

	for (uint32_t i = 0; i < lobbyCount; ++i) {
		GalaxyID lobby_id = matchmaking_ptr->GetLobbyByIndex(i);

		delay_runner.Add([=]() {
			matchmaking_ptr->RequestLobbyData(lobby_id);
		});
	}
}

void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	for (auto& data_entry : LOBBY_TEST_DATA) {
		std::string result{ matchmaking_ptr->GetLobbyData(lobbyID, data_entry[0].data()) };
	}

	std::string result{ matchmaking_ptr->GetLobbyData(lobbyID, "timer")};

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

static std::string hexStr(const uint8_t* data, int len)
{
	std::stringstream ss;
	ss << std::hex;

	for (int i(0); i < len; ++i)
		ss << std::setw(2) << std::setfill('0') << (int)data[i];

	return ss.str();
}

void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	GalaxyID senderID2;
	char data[32];
	uint32_t message_read_len = matchmaking_ptr->GetLobbyMessage(lobbyID, messageID, senderID2, data, sizeof(data));

	tracer::Trace::write_all(
		std::format(
			"LobbyID: {} SenderID: {} SenderID2: {} messageID: {} messageLength: {} messageReadLen: {}",
			lobbyID, senderID, senderID2, messageID, messageLength, message_read_len
		));

	tracer::Trace::write_all(hexStr((const uint8_t*)data, message_read_len));
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
#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
	new LobbyDataRetrieveListenerImplGlobal{ OnLobbyDataRetrieveSuccess };
#endif
	new LobbyListListenerImplGlobal{ OnLobbyList };
	new LobbyMessageListenerImplGlobal{ OnLobbyMessageReceived };
}

bool should_keep_running() {
	return true;
}
