#include <TestCaseClientDetails.hxx>

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
#define GET_GALAXY_API galaxy_api->
#define User GetUser
#else
#define GET_GALAXY_API galaxy::api::
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

void perform_test() {
	char access_token[1024];
	access_token[0] = '\0';

	auto user_ptr = GET_GALAXY_API User();
	user_ptr->GetAccessTokenCopy(access_token, sizeof(access_token));

	auto si = user_ptr->SignedIn();
	auto lo = false; //user_ptr->IsLoggedOn();
	auto gid = user_ptr->GetGalaxyID();
	auto iuda = user_ptr->IsUserDataAvailable();
	auto gudc = 0; //user_ptr->GetUserDataCount();

	tracer::Trace::write_all(
		std::format(
			"SignedIn: {} IsLoggedOn: {} GetAccessToken: {} GetGalaxyID: {} IsUserDataAvailable: {} GetUserDataCount: {}",
			si,
			lo,
			access_token,
			gid,
			iuda,
			gudc
		).c_str());
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
	galaxy::api::IGalaxy* galaxy_api = galaxy::api::GalaxyFactory::CreateInstance();
#endif

	GET_GALAXY_API Init(options);

	trace = std::make_unique<tracer::Trace>("", "main");

	{
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
			if (personaStateChange != 0 || userID != galaxy::api::User()->GetGalaxyID()) {
				return;
			}
			has_person_data_unchanged = true;
			try_init();
			}
		};
		RichPresenceChangeListenerImplGlobal richpresencechangelistener{};

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		RichPresenceListenerImplGlobal richpresencelistener{};
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		RichPresenceRetrieveListenerImplGlobal richpresenceretrievelistener{};
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

		GET_GALAXY_API User()->SignInCredentials(credentials[0].data(), credentials[1].data());
		//bool requested_data = false;

		while (!performed_init)
		{
			GET_GALAXY_API ProcessData();

			//if (has_signed_in && has_connected && !requested_data) {
			//	requested_data = true;
			//	GET_GALAXY_API User()->RequestUserData();
			//}

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}

	tracer::Trace::SetTracingEnabled(true);
	trace = std::make_unique<tracer::Trace>("::INIT", "main");

	perform_test();

	while (true)
	{
		GET_GALAXY_API ProcessData();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}