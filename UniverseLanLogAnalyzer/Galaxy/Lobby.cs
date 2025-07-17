namespace UniverseLanLogAnalyzer.Galaxy
{
    using LobbyKVType = Dictionary<string, byte[]>;
    using LobbyMessagesType = Dictionary<uint, byte[]>;
    using LobbyUserKVType = Dictionary<User, Dictionary<string, byte[]>>;

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

    public class Lobby
    {
        public GalaxyID id;
        public GalaxyID owner_id;
        public bool joinable;
        public uint max_members;
        public LobbyKVType kv_store = new();
        public LobbyUserKVType user_kv_store = new();
        public LobbyMessagesType messages = new();
        public LobbyTopologyType topology_type;
        public LobbyType type;

        public Lobby(GalaxyID id, LobbyTopologyType topology_type, LobbyType type)
        {
            this.max_members = 0;
            this.joinable = true;
            this.owner_id = new GalaxyID(0);
            this.id = id;
            this.topology_type = topology_type;
            this.type = type;
        }

        public Lobby(ulong id, LobbyTopologyType topology_type, LobbyType type)
        {
            this.max_members = 0;
            this.joinable = true;
            this.owner_id = new GalaxyID(0);
            this.id = new GalaxyID(id, GalaxyID.Type.Lobby);
            this.topology_type = topology_type;
            this.type = type;
        }
    }
}
