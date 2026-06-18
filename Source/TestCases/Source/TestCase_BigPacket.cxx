#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

#include <format>

GalaxyID my_lobby_id = 0;
GalaxyID my_galaxy_id = 0;
int counter = 30000;
char buffer[1 * 1024 * 1024];

long long GetTimeNow() {
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

long long GetRunTime() {
	static auto start = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch() - start).count();
}

void UpdateTimer() {
	delay_runner.Add(std::chrono::milliseconds(1), []() { UpdateTimer(); });
	++counter;

	auto networking_ptr = GET_GALAXY_API(Networking());

	tracer::Trace::write_all(
		std::format(
			"Sending packet with size: '{}'",
			(uint32_t)(counter < sizeof(buffer) ? counter : sizeof(buffer))
		));

	networking_ptr->SendP2PPacket(my_galaxy_id, buffer, (uint32_t)(counter < sizeof(buffer) ? counter : sizeof(buffer)), P2P_SEND_UNRELIABLE, 0);

	uint32_t out_msg_size = 0;
	while (networking_ptr->IsP2PPacketAvailable(&out_msg_size, 0)) {
		GalaxyID sender = 0;
		while (networking_ptr->ReadP2PPacket((void*)buffer, sizeof(buffer), &out_msg_size, sender, 0)) {
			tracer::Trace::write_all(
				std::format(
					"Host Received P2P packet from {} @ with size: '{}'",
					sender, out_msg_size
				));
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
	auto server_networking_ptr = GET_GALAXY_API(ServerNetworking());
	/* TODO */
#endif
}

void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result) {
	if (result == LOBBY_ENTER_RESULT_SUCCESS) {
		auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

		matchmaking_ptr->SetLobbyMemberData(my_lobby_id, "my_galaxy_id", std::to_string(my_galaxy_id.ToUint64()).c_str());

		UpdateTimer();
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
		matchmaking_ptr->SetLobbyData(my_lobby_id, data_entry[0].data(), data_entry[1].data());
	}

#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
	matchmaking_ptr->SetLobbyJoinable(my_lobby_id, true);
#endif
}

void perform_test() {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());
	auto user_ptr = GET_GALAXY_API(User());

	my_galaxy_id = user_ptr->GetGalaxyID();

	matchmaking_ptr->CreateLobby(LobbyType::LOBBY_TYPE_PUBLIC, 4
#if GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
		, true, LobbyTopologyType::LOBBY_TOPOLOGY_TYPE_STAR
#endif
	);

	tracer::Trace::SetLogToCout(true);
}

void register_listeners() {
	// just leak it, don't care
	new LobbyEnteredListenerImplGlobal{ OnLobbyEntered };
	new LobbyCreatedListenerImplGlobal{ OnLobbyCreated };
}

bool should_keep_running() {
	return true;
}
