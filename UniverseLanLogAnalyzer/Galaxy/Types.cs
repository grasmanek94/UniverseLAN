namespace UniverseLanLogAnalyzer.Galaxy
{
    public class GalaxyID
    {
        public enum Type
        {
            ID_TYPE_UNASSIGNED,
            ID_TYPE_LOBBY,
            ID_TYPE_USER
        }

        public ulong raw; // 0 as an argument to a function means usually SELF (logged in user), otherwise invalid
        public static readonly ulong mask_id = 0x00FFFFFFFFFFFFFFUL;
        public static readonly ulong mask_type = ~mask_id;
        public static readonly int shift_type = 56;

        public GalaxyID(ulong id)
        {
            this.raw = id;
        }

        public GalaxyID(ulong id, Type type)
        {
            this.raw = (((ulong)type << shift_type) & mask_type) | (id & mask_id);
        }

        public Type GetIDType()
        {
            return (Type)(raw >> 56);
        }

        public ulong GetID()
        {
            return (raw & mask_id);
        }

        public void SetType(Type type)
        {
            this.raw = (raw & mask_id) | (((ulong)type << shift_type) & mask_type);
        }

        public void SetID(ulong id)
        {
            this.raw = (raw & mask_id) | (((ulong)GetIDType() << shift_type) & mask_type);
        }

        public void SetRaw(ulong num)
        {
            this.raw = num;
        }
    }

    [Flags]
    public enum OperationalState
    {
        OPERATIONAL_STATE_NONE = 0x0000,
        OPERATIONAL_STATE_SIGNED_IN = 0x0001, ///< User signed in.
        OPERATIONAL_STATE_LOGGED_ON = 0x0002 ///< User logged on.
    };

    [Flags]
    public enum PersonaStateChange
    {
        PERSONA_CHANGE_NONE = 0x0000, ///< No information has changed.
        PERSONA_CHANGE_NAME = 0x0001, ///< Persona name has changed.
        PERSONA_CHANGE_AVATAR = 0x0002, ///< Avatar, i.e. its URL, has changed.
        PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_SMALL = 0x0004, ///< Small avatar image has been downloaded.
        PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_MEDIUM = 0x0008, ///< Medium avatar image has been downloaded.
        PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_LARGE = 0x0010, ///< Large avatar image has been downloaded.
        PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_ANY = PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_SMALL | PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_MEDIUM | PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_LARGE ///< Any avatar images have been downloaded.
    };

    [Flags]
    public enum AvatarType
    {
        AVATAR_TYPE_NONE = 0x0000, ///< No avatar type specified.
        AVATAR_TYPE_SMALL = 0x0001, ///< Avatar resolution size: 32x32.
        AVATAR_TYPE_MEDIUM = 0x0002, ///< Avatar resolution size: 64x64.
        AVATAR_TYPE_LARGE = 0x0004 ///< Avatar resolution size: 184x184.
    };

    public enum PersonaState
    {
        PERSONA_STATE_OFFLINE, ///< User is not currently logged on.
        PERSONA_STATE_ONLINE ///< User is logged on.
    };

    public enum LobbyCreateResult
    {
        LOBBY_CREATE_RESULT_SUCCESS, ///< Lobby was created.
        LOBBY_CREATE_RESULT_ERROR ///< Unexpected error.
    };

    public enum LobbyEnterResult
    {
        LOBBY_ENTER_RESULT_SUCCESS, ///< The user has entered the lobby.
        LOBBY_ENTER_RESULT_LOBBY_DOES_NOT_EXIST, ///< Specified lobby does not exist.
        LOBBY_ENTER_RESULT_LOBBY_IS_FULL, ///< Specified lobby is full.
        LOBBY_ENTER_RESULT_ERROR ///< Unexpected error.
    };

    [Flags]
    public enum LobbyMemberStateChange
    {
        LOBBY_MEMBER_STATE_CHANGED_ENTERED = 0x0001, ///< The user joined the lobby.
        LOBBY_MEMBER_STATE_CHANGED_LEFT = 0x0002, ///< The user left the lobby having announced it first.
        LOBBY_MEMBER_STATE_CHANGED_DISCONNECTED = 0x0004, ///< The user disconnected without leaving the lobby first.
        LOBBY_MEMBER_STATE_CHANGED_KICKED = 0x0008, ///< User was kicked from the lobby.
        LOBBY_MEMBER_STATE_CHANGED_BANNED = 0x0010 ///< User was kicked and banned from the lobby.
    };

    public enum LobbyComparisonType
    {
        LOBBY_COMPARISON_TYPE_EQUAL = 0, ///< The lobby should have a property of a value that is equal to the one specified.
        LOBBY_COMPARISON_TYPE_NOT_EQUAL = 1, ///< The lobby should have a property of a value that is not equal to the one specified.
        LOBBY_COMPARISON_TYPE_GREATER = 2, ///< The lobby should have a property of a value that is greater than the one specified.
        LOBBY_COMPARISON_TYPE_GREATER_OR_EQUAL = 3, ///< The lobby should have a property of a value that is greater than or equal to the one specified.
        LOBBY_COMPARISON_TYPE_LOWER = 4, ///< The lobby should have a property of a value that is lower than the one specified.
        LOBBY_COMPARISON_TYPE_LOWER_OR_EQUAL = 5 ///< The lobby should have a property of a value that is lower than or equal to the one specified.
    };

    public enum LobbyListResult
    {
        LOBBY_LIST_RESULT_SUCCESS,
        LOBBY_LIST_RESULT_ERROR,
        LOBBY_LIST_RESULT_CONNECTION_FAILURE
    };

    public enum P2PSendType
    {
        P2P_SEND_UNRELIABLE = 0, ///< UDP-like packet transfer. The packet will be sent during the next call to ProcessData().
        P2P_SEND_RELIABLE = 1, ///< TCP-like packet transfer. The packet will be sent during the next call to ProcessData().
        P2P_SEND_UNRELIABLE_IMMEDIATE = 2, ///< UDP-like packet transfer. The packet will be sent instantly.
        P2P_SEND_RELIABLE_IMMEDIATE = 3 ///< TCP-like packet transfer. The packet will be sent instantly.
    };
}
