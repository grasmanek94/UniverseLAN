#include <Unet.h>

#include <TestCaseClientDetails.hxx>

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
bool lobby_joined = false;
std::unique_ptr<tracer::Trace> trace{ nullptr };
std::unique_ptr<Unet::IContext> unet_ctx{ nullptr };
DelayRunner delay_runner{};


class UNET : public Unet::ICallbacks
{
	virtual void OnLogError(const std::string& str) {
		tracer::Trace::write_all(std::format(
			"[UNET] {}: {}",
			__FUNCTION__,
			str
		));
	}

	virtual void OnLogWarn(const std::string& str) {
		tracer::Trace::write_all(std::format(
			"[UNET] {}: {}",
			__FUNCTION__,
			str
		));
	}

	virtual void OnLogInfo(const std::string& str) {
		tracer::Trace::write_all(std::format(
			"[UNET] {}: {}",
			__FUNCTION__,
			str
		));
	}

	virtual void OnLogDebug(const std::string& str) {
		tracer::Trace::write_all(std::format(
			"[UNET] {}: {}",
			__FUNCTION__,
			str
		));
	}

	// Callbacks for results
	virtual void OnLobbyCreated(const Unet::CreateLobbyResult& result) {}
	virtual void OnLobbyList(const Unet::LobbyListResult& result) {
		
		tracer::Trace::write_all(
			std::format(
				"[UNET] {} lobbyCount: {} result: {}",
				__FUNCTION__,
				result.Lobbies.size(), magic_enum::enum_name(result.Code)
			));

		
		for (const auto& lobby : result.Lobbies) {
			tracer::Trace::write_all(
				std::format(
					"[UNET] lobby_id: {}",
					lobby.UnetGuid.str()
				));

			//delay_runner.Add([=]() {
			//	matchmaking_ptr->RequestLobbyData(lobby_id);
			//	});
		}
	}

	virtual void OnLobbyInfoFetched(const Unet::LobbyInfoFetchResult& result) {}
	virtual void OnLobbyJoined(const Unet::LobbyJoinResult& result) {}
	virtual void OnLobbyLeft(const Unet::LobbyLeftResult& result) {}

	// Lobby change events
	virtual void OnLobbyNameChanged(const std::string& oldname, const std::string& newname) {}
	virtual void OnLobbyMaxPlayersChanged(int oldamount, int newamount) {}

	// Lobby member events
	virtual void OnLobbyPlayerJoined(Unet::LobbyMember* member) {}
	virtual void OnLobbyPlayerLeft(Unet::LobbyMember* member) {}

	// Lobby data events
	virtual void OnLobbyDataChanged(const std::string& name) {
		tracer::Trace::write_all(
			std::format(
				"[UNET] key: {} value: {}",
				name, "??"
			));

		//if (result.length() > 0 && !lobby_joined) {
		//	lobby_joined = true;
		//	tracer::Trace::write_all(
		//		std::format(
		//			"Join: {}",
		//			lobbyID
		//		));
		//	matchmaking_ptr->JoinLobby(lobbyID);
		//}
	}
	virtual void OnLobbyMemberDataChanged(Unet::LobbyMember* member, const std::string& name) {}

	// Lobby member info events
	virtual void OnLobbyMemberNameChanged(Unet::LobbyMember* member, const std::string& oldname) {}

	// Lobby file events
	virtual void OnLobbyFileAdded(Unet::LobbyMember* member, const Unet::LobbyFile* file) {}
	virtual void OnLobbyFileRemoved(Unet::LobbyMember* member, const std::string& filename) {}
	virtual void OnLobbyFileRequested(Unet::LobbyMember* receiver, const Unet::LobbyFile* file) {}

	// Lobby file data sending
	virtual void OnLobbyFileDataSendProgress(const Unet::OutgoingFileTransfer& transfer) {}
	virtual void OnLobbyFileDataSendFinished(const Unet::OutgoingFileTransfer& transfer) {}

	// Lobby file data receiving
	virtual void OnLobbyFileDataReceiveProgress(Unet::LobbyMember* sender, const Unet::LobbyFile* file) {}
	virtual void OnLobbyFileDataReceiveFinished(Unet::LobbyMember* sender, const Unet::LobbyFile* file, bool isValid) {}

	// Lobby chat
	virtual void OnLobbyChat(Unet::LobbyMember* sender, const char* text) {}
};

void OnLobbyList(uint32_t lobbyCount, LobbyListResult result) {
	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	tracer::Trace::write_all(
		std::format(
			"OnLobbyList lobbyCount: {} result: {}",
			lobbyCount, magic_enum::enum_name(result)
		));

	for (uint32_t i = 0; i < lobbyCount; ++i) {
		GalaxyID lobby_id = matchmaking_ptr->GetLobbyByIndex(i);

		tracer::Trace::write_all(
			std::format(
				"i: {} lobby_id: {}",
				i, lobby_id
			));

		//delay_runner.Add([=]() {
		//	matchmaking_ptr->RequestLobbyData(lobby_id);
		//});
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

	//if (result.length() > 0 && !lobby_joined) {
	//	lobby_joined = true;
	//	tracer::Trace::write_all(
	//		std::format(
	//			"Join: {}",
	//			lobbyID
	//		));
	//	matchmaking_ptr->JoinLobby(lobbyID);
	//}
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

	delay_runner.Add([&]() {
		Unet::LobbyListFilter filter{};
		unet_ctx->GetLobbyList(filter);
	});
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
	LobbyDataListenerImplGlobal lobbydatalistener{ OnLobbyDataUpdated };
	LobbyDataRetrieveListenerImplGlobal lobbydataretrievelistener{ OnLobbyDataRetrieveSuccess };
	LobbyEnteredListenerImplGlobal lobbyenteredlistener{};
	LobbyLeftListenerImplGlobal lobbyleftlistener{};
	LobbyListListenerImplGlobal lobbylistlistener{ OnLobbyList };
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

	// ... initialize Steam/Galaxy/Enet here ...
	auto credentials = USER_CREDENTIALS[1];

	GET_GALAXY_API(User())->SignInCredentials(credentials[0].data(), credentials[1].data());
	bool sub_init_done = false;

	// Create the Unet context
	unet_ctx = std::make_unique<Unet::IContext>(Unet::CreateContext());

	// Prepare context callbacks
	unet_ctx->SetCallbacks(new UNET);

	// Initialize the services we'll be using (the first EnableService call will be the "primary" service)
	unet_ctx->EnableService(Unet::ServiceType::Galaxy);


	// Create a lobby
	unet_ctx->CreateLobby(Unet::LobbyPrivacy::Public, 4, "whatever room");

	while (true)
	{
		GET_GALAXY_API_AS_IS(ProcessData());

		// Run callbacks and keep the context updated
		unet_ctx->RunCallbacks();

		if (performed_init && !sub_init_done) {
			sub_init_done = true;

			tracer::Trace::SetTracingEnabled(true);
			trace = std::make_unique<tracer::Trace>("::INIT", "main");
		}

		delay_runner.Run();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	// Leave the lobby if we're still in it
	//unet_ctx->LeaveLobby();

	return 0;
}
