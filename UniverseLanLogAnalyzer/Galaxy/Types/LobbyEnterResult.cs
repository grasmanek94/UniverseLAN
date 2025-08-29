namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    public enum LobbyEnterResult
    {
        LOBBY_ENTER_RESULT_SUCCESS, ///< The user has entered the lobby.
        LOBBY_ENTER_RESULT_LOBBY_DOES_NOT_EXIST, ///< Specified lobby does not exist.
        LOBBY_ENTER_RESULT_LOBBY_IS_FULL, ///< Specified lobby is full.
        LOBBY_ENTER_RESULT_ERROR ///< Unexpected error.
    };
}