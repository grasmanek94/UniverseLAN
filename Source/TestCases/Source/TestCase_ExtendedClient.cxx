#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

bool lobby_joined = false;
GalaxyID my_lobby_id = 0;
GalaxyID my_galaxy_id = 0;
int counter = 0;
char buffer[1024];

long long GetTimeNow() {
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

long long GetRunTime() {
	static auto start = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch() - start).count();
}

void UpdateTimer() {
	delay_runner.Add(std::chrono::seconds(5), []() { UpdateTimer(); });
	++counter;

	std::string message{ std::format("This is lobby message nr {} from client {} in {}", counter, my_galaxy_id, my_lobby_id) };

	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());
	matchmaking_ptr->SetLobbyData(my_lobby_id, "timer_client", std::to_string(GetTimeNow()).c_str());
	matchmaking_ptr->SetLobbyMemberData(my_lobby_id, "my_runtime", std::to_string(GetRunTime()).c_str());
	matchmaking_ptr->SendLobbyMessage(my_lobby_id, message.c_str(), (uint32_t)message.size());

	auto networking_ptr = GET_GALAXY_API(Networking());
	for (uint8_t channel = 0; channel < 9; channel += 3) {
		uint32_t out_msg_size = 0;
		while (networking_ptr->IsP2PPacketAvailable(&out_msg_size, channel)) {
			GalaxyID sender = 0;
			while (networking_ptr->ReadP2PPacket((void*)buffer, sizeof(buffer), &out_msg_size, sender, channel)) {
				tracer::Trace::write_all(
					std::format(
						"Client Received P2P packet from {} @ channel {} with contents: '{}'",
						sender, (int)channel, std::string(buffer, out_msg_size)
					));
				std::string response = "CLIENT ACK: " + std::string(buffer, out_msg_size);

				networking_ptr->SendP2PPacket(sender, response.c_str(), (uint32_t)response.size(), P2P_SEND_UNRELIABLE, channel);
			}
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
	auto server_networking_ptr = GET_GALAXY_API(ServerNetworking());
	for (uint8_t channel = 0; channel < 9; channel += 3) {
		uint32_t out_msg_size = 0;
		while (server_networking_ptr->IsP2PPacketAvailable(&out_msg_size, channel)) {
			GalaxyID sender = 0;
			while (server_networking_ptr->ReadP2PPacket((void*)buffer, sizeof(buffer), &out_msg_size, sender, channel)) {
				tracer::Trace::write_all(
					std::format(
						"Received SERVER P2P packet from {} @ channel {} with contents: '{}'",
						sender, (int)channel, std::string(buffer, out_msg_size)
					));
				std::string response = "SHOULDN'T HAPPEN CLIENT ACK: " + std::string(buffer, out_msg_size);
				networking_ptr->SendP2PPacket(sender, response.c_str(), (uint32_t)response.size(), P2P_SEND_UNRELIABLE, channel);
			}
		}
	}
#endif
}

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

void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result) {
	if (result == LOBBY_ENTER_RESULT_SUCCESS) {
		my_lobby_id = lobbyID;

		auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

		matchmaking_ptr->SetLobbyMemberData(my_lobby_id, "my_galaxy_id", std::to_string(my_galaxy_id.ToUint64()).c_str());

		UpdateTimer();
	}
	else {
		lobby_joined = false;
	}
}

void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	if (memberID.IsValid()) {
		tracer::Trace::write_all(std::format(
			"OnLobbyDataUpdated LobbyID: {} memberID: {} my_runtime: {} my_galaxy_id: {}",
			lobbyID, memberID,
			matchmaking_ptr->GetLobbyMemberData(lobbyID, memberID, "my_runtime"),
			matchmaking_ptr->GetLobbyMemberData(lobbyID, memberID, "my_galaxy_id")
		));
	}
	else if (lobbyID.IsValid()) {
		tracer::Trace::write_all(std::format(
			"OnLobbyDataUpdated LobbyID: {} timer: {}",
			lobbyID, matchmaking_ptr->GetLobbyData(lobbyID, "timer")
		));
	}
	else {
		tracer::Trace::write_all(std::format("OnLobbyDataUpdated huh?"));
	}
}

void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	for (auto& data_entry : LOBBY_TEST_DATA) {
		std::string result{ matchmaking_ptr->GetLobbyData(lobbyID, data_entry[0].data()) };
	}

	std::string result{ matchmaking_ptr->GetLobbyData(lobbyID, "lobby_identifier")};

	if (result.length() > 0 && result == "uvlan-test" && !lobby_joined) {
		lobby_joined = true;
		tracer::Trace::write_all(
			std::format(
				"Join: {}",
				lobbyID
			));
		matchmaking_ptr->JoinLobby(lobbyID);
	}
}

void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	GalaxyID senderID2;
	uint32_t message_read_len = matchmaking_ptr->GetLobbyMessage(lobbyID, messageID, senderID2, buffer, sizeof(buffer));

	tracer::Trace::write_all(std::format(
		"LobbyID: {} SenderID: {} SenderID2: {} messageID: {} messageLength: {} messageReadLen: {} contents: '{}'",
		lobbyID, senderID, senderID2, messageID, messageLength, message_read_len, std::string(buffer, message_read_len)
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
	new LobbyEnteredListenerImplGlobal{ OnLobbyEntered };
	new LobbyDataListenerImplGlobal{ OnLobbyDataUpdated };
#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
	new LobbyDataRetrieveListenerImplGlobal{ OnLobbyDataRetrieveSuccess };
#endif
	new LobbyListListenerImplGlobal{ OnLobbyList };
	new LobbyMessageListenerImplGlobal{ OnLobbyMessageReceived };
	new LobbyLeftListenerImplGlobal{};
	new LobbyMemberStateListenerImplGlobal{};
}

bool should_keep_running() {
	return true;
}
