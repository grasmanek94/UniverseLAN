#include <TestCaseClientDetails.hxx>

#include <unordered_map>
#include <string>
#include <vector>

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
#define GET_GALAXY_API(what) galaxy_api->Get ## what
#define GET_GALAXY_API_AS_IS(what) galaxy_api->what

galaxy::api::IGalaxy* galaxy_api = nullptr;
#else
#define GET_GALAXY_API(what) galaxy::api::what
#define GET_GALAXY_API_AS_IS(what) galaxy::api::what
#endif

#if !GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINCREDENTIALS
#define SignInCredentials SignIn
#endif

bool has_access_token_refreshed = true;
bool has_signed_in = false;
bool has_connected = false;
bool has_operational_state_change = false;
bool has_person_data_unchanged = false;
bool performed_init = false;
bool user_data_received = true;
std::unique_ptr<tracer::Trace> trace{ nullptr };

using file_data_t = std::vector<unsigned char>;
using file_map_t = std::unordered_map<std::string, file_data_t>;
using file_entry_t = file_map_t::value_type;

file_data_t create_entry(const std::string& data) {
	return file_data_t{ data.begin(), data.end() };
}

file_map_t files;

void perform_test() {
	files["test1.txt"] = create_entry(R"STR(
Test data
With a few newlines
To check if this works
And maybe add some UTF-8 encoded characters here: łakomo
żyć też się tutaj da.
		)STR");

	files["test2.bin"] = { 
		0x9B,0x3E,0x34,0x87,
		0xFD,0x24,0xB4,0x64,
		0xBA,0x80,0x04,0xFD,
		0xDF,0x23,0x41,0xEE,
		0x00,0x00,0x00,0x00,
		0xAC,0xF9,0x8F,0x00 
	};


	auto storage_ptr = GET_GALAXY_API(Storage());
	
	for (auto& file : files) {
		storage_ptr->FileDelete(file.first.c_str());
	}

	for (auto& file : files) {
		bool status = 
			(storage_ptr->FileExists(file.first.c_str()) == false) &&
			(storage_ptr->GetFileSize(file.first.c_str()) == 0)
		;

		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} FileSize: {} FileCount: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), storage_ptr->GetFileSize(file.first.c_str()), storage_ptr->GetFileCount(),
				status
			));
	}

	char buffer[256];

	for (auto& file : files) {
		uint32_t read_bytes = storage_ptr->FileRead(file.first.c_str(), buffer, sizeof(buffer));
		bool status = read_bytes == 0;
		tracer::Trace::write_all(
			std::format(
				"File: {} FileRead: {} Status: {}",
				file.first, read_bytes, status
			));
	}

	for (auto& file : files) {
		bool status = storage_ptr->FileExists(file.first.c_str()) == false;
		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), status
			));
	}

	char start_char = 'f';
	for (auto& file : files) {
		static char i = 0;
		++i;
		std::string out(20, start_char + i);
		storage_ptr->FileWrite(file.first.c_str(), out.c_str(), (uint32_t)(out.length() + 1));

		tracer::Trace::write_all(
			std::format(
				"File: {} FileWrite: {} Size: {}",
				file.first, out, out.length() + 1
			));
	}

	for (auto& file : files) {
		bool status = 
			(storage_ptr->FileExists(file.first.c_str()) == true) &&
			(storage_ptr->GetFileSize(file.first.c_str()) == 21)
			;
		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} FileSize: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), storage_ptr->GetFileSize(file.first.c_str()),
				status
			));
	}

	for (auto& file : files) {
		static char i = 0;
		++i;
		std::string out(20, start_char + i);

		std::memset(buffer, 0xCC, sizeof(buffer));

		uint32_t read_bytes = storage_ptr->FileRead(file.first.c_str(), buffer, sizeof(buffer));
		bool match = compare_equal(buffer, out);
		bool check = compare_equal(buffer + read_bytes, 0xCC, sizeof(buffer) - read_bytes);
		bool status = match && check && (read_bytes == (out.length() + 1));
		tracer::Trace::write_all(
			std::format(
				"File: {} FileRead: {} Match: {} Check: {} Status: {}",
				file.first, read_bytes, match, check, status
			));
	}

	for (auto& file : files) {
		storage_ptr->FileDelete(file.first.c_str());
	}

	for (auto& file : files) {
		bool status = storage_ptr->FileExists(file.first.c_str()) == false;
		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), status
			));
	}

	for (auto& file : files) {
		storage_ptr->FileWrite(file.first.c_str(), file.second.data(), (uint32_t)file.second.size());

		tracer::Trace::write_all(
			std::format(
				"File: {} FileWrite: (size){}",
				file.first, file.second.size()
			));
	}

	for (auto& file : files) {
		bool status =
			(storage_ptr->FileExists(file.first.c_str()) == true) &&
			(storage_ptr->GetFileSize(file.first.c_str()) == file.second.size()) &&
			(storage_ptr->GetFileCount() > 1)
		;

		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} FileSize: {} FileCount: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), storage_ptr->GetFileSize(file.first.c_str()), storage_ptr->GetFileCount(),
				status
			));
	}

	for (size_t i = 0; i < storage_ptr->GetFileCount(); ++i) {
		tracer::Trace::write_all(
			std::format(
				"GetFileByIndex{}: {}",
				i, storage_ptr->GetFileNameByIndex((uint32_t)i)
			));
	}

	for (auto& file : files) {
		std::memset(buffer, 0xCC, sizeof(buffer));

		uint32_t read_bytes = storage_ptr->FileRead(file.first.c_str(), buffer, sizeof(buffer));
		bool match = compare_equal(buffer, file.second);
		bool check = compare_equal(buffer + read_bytes, 0xCC, sizeof(buffer) - read_bytes);
		bool status = match && check && (read_bytes == file.second.size());

		tracer::Trace::write_all(
			std::format(
				"File: {} FileRead: {} Match: {} Check: {} Status: {}",
				file.first, read_bytes, match, check, status
			));
	}
}

void try_init() {
	if (!has_signed_in ||
		!has_connected ||
		!has_operational_state_change ||
		!has_person_data_unchanged ||
		!has_access_token_refreshed ||
		!user_data_received ||
		performed_init)
	{
		return;
	}

	performed_init = true;
}

int main()
{
	tracer::Trace::InitTracing(".", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(true);
	tracer::Trace::SetTracingEnabled(false);

	galaxy::api::InitOptions options(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data());

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
	galaxy_api = galaxy::api::GalaxyFactory::CreateInstance();
#endif

	GET_GALAXY_API_AS_IS(Init(options));

	trace = std::make_unique<tracer::Trace>("", "main");

	AccessTokenListenerImplGlobal accesstokenlistener{ [&]() {
		has_access_token_refreshed = true;
		try_init();
		} };

	AchievementChangeListenerImplGlobal achievementchangelistener{};
	AuthListenerImplGlobal authlistener{ [&]() {
		has_signed_in = true;
		try_init();
		} };

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 
	ChatRoomMessageSendListenerImplGlobal chatroommessagesendlistener{};
	ChatRoomMessagesListenerImplGlobal chatroommessageslistener{};
	ChatRoomMessagesRetrieveListenerImplGlobal chatroommessagesretrievelistener{};
	ChatRoomWithUserRetrieveListenerImplGlobal chatroomwithuserretrievelistener{};
#endif

	ConnectionCloseListenerImplGlobal connectioncloselistener{};
	ConnectionDataListenerImplGlobal connectiondatalistener{};
	ConnectionOpenListenerImplGlobal connectionopenlistener{};
	EncryptedAppTicketListenerImplGlobal encryptedappticketlistener{};
	FileShareListenerImplGlobal filesharelistener{};

#if GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER
	FriendAddListenerImplGlobal friendaddlistener{};
#endif

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3
	FriendDeleteListenerImplGlobal frienddeletelistener{};
	FriendInvitationListRetrieveListenerImplGlobal friendinvitationlistretrievelistener{};
	FriendInvitationListenerImplGlobal friendinvitationlistener{};
	FriendInvitationRespondToListenerImplGlobal friendinvitationrespondtolistener{};
	FriendInvitationSendListenerImplGlobal friendinvitationsendlistener{};
#endif

	FriendListListenerImplGlobal friendlistlistener{};
	GameInvitationReceivedListenerImplGlobal gameinvitationreceivedlistener{};
#if GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER
	GameJoinRequestedListenerImplGlobal gamejoinrequestedlistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	GogServicesConnectionStateListenerImplGlobal gogservicesconnectionstatelistener{ [&](GogServicesConnectionState state) {
		if (state != GOG_SERVICES_CONNECTION_STATE_CONNECTED) {
			return;
		}
		has_connected = true;
		try_init();
		} };
#endif

	LeaderboardEntriesRetrieveListenerImplGlobal leaderboardentriesretrievelistener{};
	LeaderboardRetrieveListenerImplGlobal leaderboardretrievelistener{};
	LeaderboardScoreUpdateListenerImplGlobal leaderboardscoreupdatelistener{};
	LeaderboardsRetrieveListenerImplGlobal leaderboardsretrievelistener{};
	LobbyCreatedListenerImplGlobal lobbycreatedlistener{};
	LobbyDataListenerImplGlobal lobbydatalistener{};
	LobbyDataRetrieveListenerImplGlobal lobbydataretrievelistener{};
	LobbyEnteredListenerImplGlobal lobbyenteredlistener{};
	LobbyLeftListenerImplGlobal lobbyleftlistener{};
	LobbyListListenerImplGlobal lobbylistlistener{};
	LobbyMemberStateListenerImplGlobal lobbymemberstatelistener{};
	LobbyMessageListenerImplGlobal lobbymessagelistener{};
	LobbyOwnerChangeListenerImplGlobal lobbyownerchangelistener{};

#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
	NatTypeDetectionListenerImplGlobal nattypedetectionlistener{};
#endif

	NetworkingListenerImplGlobal networkinglistener{};
	NotificationListenerImplGlobal notificationlistener{};
	OperationalStateChangeListenerImplGlobal operationalstatechangelistener{ [&](uint32_t operationalState) {
		if (!(operationalState & IOperationalStateChangeListener::OperationalState::OPERATIONAL_STATE_SIGNED_IN &&
			operationalState & IOperationalStateChangeListener::OperationalState::OPERATIONAL_STATE_LOGGED_ON)) {
			return;
		}
		has_operational_state_change = true;
		try_init();
		} };

	OtherSessionStartListenerImplGlobal othersessionstartlistener{};

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	OverlayInitializationStateChangeListenerImplGlobal overlayinitializationstatechangelistener{};
	OverlayVisibilityChangeListenerImplGlobal overlayvisibilitychangelistener{};
#endif

	PersonaDataChangedListenerImplGlobal personadatachangedlistener{ [&](GalaxyID userID, uint32_t personaStateChange) {
		if (personaStateChange != 0 || userID != GET_GALAXY_API(User())->GetGalaxyID()) {
			return;
		}
		has_person_data_unchanged = true;
		try_init();
		}
	};
	//RichPresenceChangeListenerImplGlobal richpresencechangelistener{};

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	//RichPresenceListenerImplGlobal richpresencelistener{};
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	//RichPresenceRetrieveListenerImplGlobal richpresenceretrievelistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	SendInvitationListenerImplGlobal sendinvitationlistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	SentFriendInvitationListRetrieveListenerImplGlobal sentfriendinvitationlistretrievelistener{};
#endif

	SharedFileDownloadListenerImplGlobal sharedfiledownloadlistener{};
	SpecificUserDataListenerImplGlobal specificuserdatalistener{
		[&](GalaxyID userID) {
		user_data_received = true;
		try_init();
		}
	};
	StatsAndAchievementsStoreListenerImplGlobal statsandachievementsstorelistener{};

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	TelemetryEventSendListenerImplGlobal telemetryeventsendlistener{};
#endif

	UserDataListenerImplGlobal userdatalistener{ [&]() {
		user_data_received = true;
		try_init();
		}
	};

#if GALAXY_BUILD_FEATURE_HAS_IUSERFINDLISTENER
	UserFindListenerImplGlobal userfindlistener{};
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	UserInformationRetrieveListenerImplGlobal userinformationretrievelistener{};
	UserStatsAndAchievementsRetrieveListenerImplGlobal userstatsandachievementsretrievelistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
	UserTimePlayedRetrieveListenerImplGlobal usertimeplayedretrievelistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKINGLISTENER
	ServerNetworkingListenerImplGlobal servernetworkinglistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IOVERLAYSTATECHANGELISTENER
	OverlayStateChangeListenerImplGlobal overlaystatechangelistener{};
#endif

	auto credentials = USER_CREDENTIALS[0];

	GET_GALAXY_API(User())->SignInCredentials(credentials[0].data(), credentials[1].data());
	bool sub_init_done = false;

	while (true)
	{
		GET_GALAXY_API_AS_IS(ProcessData());
		if (performed_init && !sub_init_done) {
			sub_init_done = true;

			tracer::Trace::SetTracingEnabled(true);
			trace = std::make_unique<tracer::Trace>("::INIT", "main");

			perform_test();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}
