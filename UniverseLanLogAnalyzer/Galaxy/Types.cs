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

        public ulong id; // 0 as an argument to a function means usually SELF (logged in user), otherwise invalid

        public GalaxyID(ulong id)
        {
            this.id = id;
        }

        public GalaxyID(ulong id, Type type)
        {
            this.id = (id & 0x0FFFFFFFFFFFFFFF) | (((ulong)type << 56) & 0xF000000000000000);
        }

        public Type GetIDType()
        {
            return (Type)(id >> 56);
        }

        public void SetType(Type type)
        {
            this.id = (id & 0x0FFFFFFFFFFFFFFF) | (((ulong)type << 56) & 0xF000000000000000);
        }

        public void SetID(ulong id)
        {
            this.id = (id & 0x0FFFFFFFFFFFFFFF) | (((ulong)GetIDType() << 56) & 0xF000000000000000);
        }

        public void SetRaw(ulong num)
        {
            this.id = num;
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
    enum PersonaStateChange
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
    enum AvatarType
    {
        AVATAR_TYPE_NONE = 0x0000, ///< No avatar type specified.
        AVATAR_TYPE_SMALL = 0x0001, ///< Avatar resolution size: 32x32.
        AVATAR_TYPE_MEDIUM = 0x0002, ///< Avatar resolution size: 64x64.
        AVATAR_TYPE_LARGE = 0x0004 ///< Avatar resolution size: 184x184.
    };

    enum PersonaState
    {
        PERSONA_STATE_OFFLINE, ///< User is not currently logged on.
        PERSONA_STATE_ONLINE ///< User is logged on.
    };
}
