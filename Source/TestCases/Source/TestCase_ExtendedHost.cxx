#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

#include <format>

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

	std::string message{ std::format("This is lobby message nr {} from host {} in {}", counter, my_galaxy_id, my_lobby_id) };

	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());
	matchmaking_ptr->SetLobbyData(my_lobby_id, "timer", std::to_string(GetTimeNow()).c_str());
	matchmaking_ptr->SetLobbyMemberData(my_lobby_id, "my_runtime", std::to_string(GetRunTime()).c_str());
	matchmaking_ptr->SendLobbyMessage(my_lobby_id, message.c_str(), (uint32_t)message.size());

	auto networking_ptr = GET_GALAXY_API(Networking());
	uint32_t member_count = matchmaking_ptr->GetNumLobbyMembers(my_lobby_id);
	for (uint32_t i = 0; i < member_count; ++i) {
		GalaxyID member = matchmaking_ptr->GetLobbyMemberByIndex(my_lobby_id, i);
		if (member != my_galaxy_id) {
			for (uint8_t channel = 0; channel < 9; channel += 3) {
				std::string p2p_packet{ std::format("This is P2P packet nr {} from host {} in {} destined to {} @ channel {}", counter, my_galaxy_id, my_lobby_id, member, (int)channel) };
				networking_ptr->SendP2PPacket(member, p2p_packet.c_str(), (uint32_t)p2p_packet.size(), P2P_SEND_UNRELIABLE, channel);
			}
		}
	}

	for (uint8_t channel = 0; channel < 9; channel += 3) {
		uint32_t out_msg_size = 0;
		while (networking_ptr->IsP2PPacketAvailable(&out_msg_size, channel)) {
			GalaxyID sender = 0;
			while (networking_ptr->ReadP2PPacket((void*)buffer, sizeof(buffer), &out_msg_size, sender, channel)) {
				tracer::Trace::write_all(
					std::format(
						"Host Received P2P packet from {} @ channel {} with contents: '{}'",
						sender, (int)channel, std::string(buffer, out_msg_size)
					));
			}
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
	auto server_networking_ptr = GET_GALAXY_API(ServerNetworking());
	for (uint8_t channel = 0; channel < 9; channel += 3) {
		std::string p2p_packet{ std::format("This is a lobby packet nr {} from host {} in {} @ channel {}", counter, my_galaxy_id, my_lobby_id, (int)channel) };
		server_networking_ptr->SendP2PPacket(my_lobby_id, p2p_packet.c_str(), p2p_packet.size(), P2P_SEND_UNRELIABLE, channel);
	}

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
			}
		}
	}
#endif
}

void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result) {
	if (result == LOBBY_ENTER_RESULT_SUCCESS) {
		auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

		matchmaking_ptr->SetLobbyMemberData(my_lobby_id, "my_galaxy_id", std::to_string(my_galaxy_id.ToUint64()).c_str());

		UpdateTimer();
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

void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	GalaxyID senderID2;
	uint32_t message_read_len = matchmaking_ptr->GetLobbyMessage(lobbyID, messageID, senderID2, buffer, sizeof(buffer));

	tracer::Trace::write_all(std::format(
		"LobbyID: {} SenderID: {} SenderID2: {} messageID: {} messageLength: {} messageReadLen: {} contents: '{}'",
		lobbyID, senderID, senderID2, messageID, messageLength, message_read_len, std::string(buffer, message_read_len)
	));
}

void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result)
{
	if (result != LobbyCreateResult::LOBBY_CREATE_RESULT_SUCCESS) {
		return;
	}

	my_lobby_id = lobbyID;

	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	for (auto& data_entry : LOBBY_TEST_DATA) {
		matchmaking_ptr->SetLobbyData(my_lobby_id, data_entry[0].data(), data_entry[1].data());
	}

	matchmaking_ptr->SetLobbyJoinable(my_lobby_id, true);
}

void perform_test() {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());
	auto user_ptr = GET_GALAXY_API(User());

	my_galaxy_id = user_ptr->GetGalaxyID();

	matchmaking_ptr->CreateLobby(LobbyType::LOBBY_TYPE_PUBLIC, 4
#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
		, true, LobbyTopologyType::LOBBY_TOPOLOGY_TYPE_STAR
#endif
	);
}

void register_listeners() {
	// just leak it, don't care
	new LobbyEnteredListenerImplGlobal{ OnLobbyEntered };
	new LobbyDataListenerImplGlobal{ OnLobbyDataUpdated };
	new LobbyCreatedListenerImplGlobal{ OnLobbyCreated };
	new LobbyMessageListenerImplGlobal{ OnLobbyMessageReceived };
}

bool should_keep_running() {
	return true;
}
