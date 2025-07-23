namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    [Flags]
    public enum LobbyMemberStateChange
    {
        LOBBY_MEMBER_STATE_CHANGED_ENTERED = 0x0001, ///< The user joined the lobby.
        LOBBY_MEMBER_STATE_CHANGED_LEFT = 0x0002, ///< The user left the lobby having announced it first.
        LOBBY_MEMBER_STATE_CHANGED_DISCONNECTED = 0x0004, ///< The user disconnected without leaving the lobby first.
        LOBBY_MEMBER_STATE_CHANGED_KICKED = 0x0008, ///< User was kicked from the lobby.
        LOBBY_MEMBER_STATE_CHANGED_BANNED = 0x0010 ///< User was kicked and banned from the lobby.
    };
}