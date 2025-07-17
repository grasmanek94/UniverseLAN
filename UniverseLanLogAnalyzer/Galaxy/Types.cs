namespace UniverseLanLogAnalyzer.Galaxy
{
    public class GalaxyID
    {
        public enum Type
        {
            Unassigned = 0,
            Lobby = 1,
            User = 2
        }

        public ulong id;

        public GalaxyID(ulong id)
        {
            this.id = id;
        }

        public GalaxyID(ulong id, Type type)
        {
            this.id = (id & 0x0FFFFFFFFFFFFFFF) | ((ulong)type << 56);
        }

        public Type GetIDType()
        {
            return (Type)(id >> 56);
        }
    }

    public enum LobbyTopologyType
    {
        FCM_HOST_MIGRATION = 0,
        FCM = 1,
        STAR = 2,
        CONNECTIONLESS = 3,
        FCM_OWNERSHIP_TRANSITION = 4
    }

    public enum LobbyType
    {
        PRIVATE = 0,
        FRIENDS_ONLY = 1,
        PUBLIC = 2,
        INVISIBLE_TO_FRIENDS = 3 
    };
}
