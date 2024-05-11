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

int main()
{
	tracer::Trace::InitTracing(".", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(true);

	tracer::Trace trace{ "", __FUNCTION__ };

#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
	galaxy::api::InitOptions options(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data());
#endif

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
	galaxy_api = galaxy::api::GalaxyFactory::CreateInstance();
#endif

	try {
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS
		GET_GALAXY_API_AS_IS(Init(options));
#else
		GET_GALAXY_API_AS_IS(Init(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data()));
#endif
}
	catch (const IError& err) {
		std::cerr << err.GetMsg() << std::endl;
	}

	trace.write_all("galaxy::api::Init performed");

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
	AccessTokenListenerImplGlobal accesstokenlistener{};
#endif

	AchievementChangeListenerImplGlobal achievementchangelistener{};
	AuthListenerImplGlobal authlistener{};

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 
	ChatRoomMessageSendListenerImplGlobal chatroommessagesendlistener{};
	ChatRoomMessagesListenerImplGlobal chatroommessageslistener{};
	ChatRoomMessagesRetrieveListenerImplGlobal chatroommessagesretrievelistener{};
	ChatRoomWithUserRetrieveListenerImplGlobal chatroomwithuserretrievelistener{};
#endif
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
	ConnectionCloseListenerImplGlobal connectioncloselistener{};
	ConnectionDataListenerImplGlobal connectiondatalistener{};
	ConnectionOpenListenerImplGlobal connectionopenlistener{};
#endif
	EncryptedAppTicketListenerImplGlobal encryptedappticketlistener{};

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	FileShareListenerImplGlobal filesharelistener{};
#endif

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
#if GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER
	GameInvitationReceivedListenerImplGlobal gameinvitationreceivedlistener{};
#endif
#if GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER
	GameJoinRequestedListenerImplGlobal gamejoinrequestedlistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	GogServicesConnectionStateListenerImplGlobal gogservicesconnectionstatelistener{};
#endif

	LeaderboardEntriesRetrieveListenerImplGlobal leaderboardentriesretrievelistener{};
#if GALAXY_BUILD_FEATURE_HAS_ILEADERBOARDRETRIEVELISTENER
	LeaderboardRetrieveListenerImplGlobal leaderboardretrievelistener{};
#endif
	LeaderboardScoreUpdateListenerImplGlobal leaderboardscoreupdatelistener{};
	LeaderboardsRetrieveListenerImplGlobal leaderboardsretrievelistener{};
	LobbyCreatedListenerImplGlobal lobbycreatedlistener{};
	LobbyDataListenerImplGlobal lobbydatalistener{};
#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
	LobbyDataRetrieveListenerImplGlobal lobbydataretrievelistener{ };
#endif
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
#if GALAXY_BUILD_FEATURE_HAS_INOTIFICATIONLISTENER
	NotificationListenerImplGlobal notificationlistener{};
#endif
	OperationalStateChangeListenerImplGlobal operationalstatechangelistener{};

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
	OtherSessionStartListenerImplGlobal othersessionstartlistener{};
#endif

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	OverlayInitializationStateChangeListenerImplGlobal overlayinitializationstatechangelistener{};
	OverlayVisibilityChangeListenerImplGlobal overlayvisibilitychangelistener{};
#endif

	PersonaDataChangedListenerImplGlobal personadatachangedlistener{};
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

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
	SharedFileDownloadListenerImplGlobal sharedfiledownloadlistener{};
#endif
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
	SpecificUserDataListenerImplGlobal specificuserdatalistener{};
#endif
	StatsAndAchievementsStoreListenerImplGlobal statsandachievementsstorelistener{};

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	TelemetryEventSendListenerImplGlobal telemetryeventsendlistener{};
#endif

	UserDataListenerImplGlobal userdatalistener{};

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

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
	ServerNetworkingListenerImplGlobal servernetworkinglistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IOVERLAYSTATECHANGELISTENER
	OverlayStateChangeListenerImplGlobal overlaystatechangelistener{};
#endif

	trace.write_all("Listeners registered");

	auto credentials = USER_CREDENTIALS[0];

	trace.write_all("SignInCredentials..");
#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINCREDENTIALS
	galaxy::api::User()->SignInCredentials(credentials[0].data(), credentials[1].data());
#else
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
	galaxy_api->GetUser()
#else
	galaxy::api::User()
#endif
		->SignIn(credentials[0].data(), credentials[1].data());
#endif
	trace.write_all(".OK");

	while (true)
	{
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
		galaxy_api->ProcessData();
#else
		galaxy::api::ProcessData();
#endif

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	return 0;
}
