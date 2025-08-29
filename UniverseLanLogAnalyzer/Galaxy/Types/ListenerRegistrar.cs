namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    /* don't use the numbers, --
     * because after 1.134.10 SERVER_NETWORKING has been removed and numbers shifted --
     * use Enum.TryParse from string */
    public enum ListenerType
    {
        /* Swapped due to correct name showing */
        LOBBY_LIST,  ///< Used by ILobbyListListener.
        LISTENER_TYPE_BEGIN = LOBBY_LIST, ///< Used for iterating over listener types.
        LOBBY_CREATED, ///< Used by ILobbyCreatedListener.
        LOBBY_ENTERED, ///< Used by ILobbyEnteredListener.
        LOBBY_LEFT, ///< Used by ILobbyLeftListener.
        LOBBY_DATA, ///< Used by ILobbyDataListener.
        LOBBY_MEMBER_STATE, ///< Used by ILobbyMemberStateListener.
        LOBBY_OWNER_CHANGE, ///< Used by ILobbyOwnerChangeListener.
        AUTH, ///< Used by IAuthListener.
        LOBBY_MESSAGE, ///< Used by ILobbyMessageListener.
        NETWORKING, ///< Used by INetworkingListener.
        USER_DATA, ///< Used by IUserDataListener.
        USER_STATS_AND_ACHIEVEMENTS_RETRIEVE, ///< Used by IUserStatsAndAchievementsRetrieveListener.
        STATS_AND_ACHIEVEMENTS_STORE, ///< Used by IStatsAndAchievementsStoreListener.
        ACHIEVEMENT_CHANGE, ///< Used by IAchievementChangeListener.
        LEADERBOARDS_RETRIEVE, ///< Used by ILeaderboardsRetrieveListener.
        LEADERBOARD_ENTRIES_RETRIEVE, ///< Used by ILeaderboardEntriesRetrieveListener.
        LEADERBOARD_SCORE_UPDATE_LISTENER, ///< Used by ILeaderboardScoreUpdateListener.
        PERSONA_DATA_CHANGED, ///< Used by IPersonaDataChangedListener.
        RICH_PRESENCE_CHANGE_LISTENER, ///< Used by IRichPresenceChangeListener.
        GAME_JOIN_REQUESTED_LISTENER, ///< Used by IGameJoinRequested.
        OPERATIONAL_STATE_CHANGE, ///< Used by IOperationalStateChangeListener.
        FRIEND_LIST_RETRIEVE, ///< Used by IFriendListListener.
        ENCRYPTED_APP_TICKET_RETRIEVE, ///< Used by IEncryptedAppTicketListener.
        ACCESS_TOKEN_CHANGE, ///< Used by IAccessTokenListener.
        LEADERBOARD_RETRIEVE, ///< Used by ILeaderboardRetrieveListener.
        SPECIFIC_USER_DATA, ///< Used by ISpecificUserDataListener.
        INVITATION_SEND, ///< Used by ISendInvitationListener.
        RICH_PRESENCE_LISTENER, ///< Used by IRichPresenceListener.
        GAME_INVITATION_RECEIVED_LISTENER, ///< Used by IGameInvitationReceivedListener.
        NOTIFICATION_LISTENER, ///< Used by INotificationListener.
        LOBBY_DATA_RETRIEVE, ///< Used by ILobbyDataRetrieveListener.
        USER_TIME_PLAYED_RETRIEVE, ///< Used by IUserTimePlayedRetrieveListener.
        OTHER_SESSION_START, ///< Used by IOtherSessionStartListener.
        FILE_SHARE, ///< Used by IFileShareListener.
        SHARED_FILE_DOWNLOAD, ///< Used by ISharedFileDownloadListener.
        CUSTOM_NETWORKING_CONNECTION_OPEN, ///< Used by IConnectionOpenListener.
        CUSTOM_NETWORKING_CONNECTION_CLOSE, ///< Used by IConnectionCloseListener.
        CUSTOM_NETWORKING_CONNECTION_DATA, ///< Used by IConnectionDataListener.
        OVERLAY_INITIALIZATION_STATE_CHANGE, ///< Used by IOverlayInitializationStateChangeListener.
        OVERLAY_VISIBILITY_CHANGE, ///< Used by IOverlayVisibilityChangeListener.
        CHAT_ROOM_WITH_USER_RETRIEVE_LISTENER, ///< Used by IChatRoomWithUserRetrieveListener.
        CHAT_ROOM_MESSAGE_SEND_LISTENER, ///< Used by IChatRoomMessageSendListener.
        CHAT_ROOM_MESSAGES_LISTENER, ///< Used by IChatRoomMessagesListener.
        FRIEND_INVITATION_SEND_LISTENER, ///< Used by IFriendInvitationSendListener.
        FRIEND_INVITATION_LIST_RETRIEVE_LISTENER, ///< Used by IFriendInvitationListRetrieveListener.
        FRIEND_INVITATION_LISTENER, ///< Used by IFriendInvitationListener.
        FRIEND_INVITATION_RESPOND_TO_LISTENER, ///< Used by IFriendInvitationRespondToListener.
        FRIEND_ADD_LISTENER, ///< Used by IFriendAddListener.
        FRIEND_DELETE_LISTENER, ///< Used by IFriendDeleteListener.
        CHAT_ROOM_MESSAGES_RETRIEVE_LISTENER, ///< Used by IChatRoomMessagesRetrieveListener.
        USER_FIND_LISTENER, ///< Used by IUserFindListener.
        NAT_TYPE_DETECTION, ///< Used by INatTypeDetectionListener.
        SENT_FRIEND_INVITATION_LIST_RETRIEVE_LISTENER, ///< Used by ISentFriendInvitationListRetrieveListener.
        LOBBY_DATA_UPDATE_LISTENER, /// < Used by ILobbyDataUpdateListener.
        LOBBY_MEMBER_DATA_UPDATE_LISTENER, /// < Used by ILobbyDataUpdateListener.
        USER_INFORMATION_RETRIEVE_LISTENER, ///< Used by IUserInformationRetrieveListener.
        RICH_PRESENCE_RETRIEVE_LISTENER, ///< Used by IRichPresenceRetrieveListener.
        GOG_SERVICES_CONNECTION_STATE_LISTENER, ///< Used by IGogServicesConnectionStateListener.
        TELEMETRY_EVENT_SEND_LISTENER, ///< Used by ITelemetryEventSendListener.
        CLOUD_STORAGE_GET_FILE_LIST, ///< Used by ICloudStorageGetFileListListener.
        CLOUD_STORAGE_GET_FILE, ///< Used by ICloudStorageGetFileListener.
        CLOUD_STORAGE_PUT_FILE, ///< Used by ICloudStoragePutFileListener.
        CLOUD_STORAGE_DELETE_FILE, ///< Used by ICloudStorageDeleteFileListener.
        IS_DLC_OWNED, ///< Used for IIsDlcOwnedListener.
        PLAYFAB_CREATE_OPENID_CONNECTION, ///< Used by IPlayFabCreateOpenIDConnectionListener.
        PLAYFAB_LOGIN_WITH_OPENID_CONNECT, ///< Used by IPlayFabLoginWithOpenIDConnectListener.
        LISTENER_TYPE_END ///< Used for iterating over listener types.
    };
}
