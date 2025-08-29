namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    using LobbyKVType = Dictionary<string, byte[]>;
    using LobbyMessagesType = Dictionary<uint, byte[]>;
    using LobbyUserKVType = Dictionary<GalaxyID, Dictionary<string, byte[]>>;

    public enum LobbyTopologyType
    {
        LOBBY_TOPOLOGY_TYPE_FCM_HOST_MIGRATION = 0,
        LOBBY_TOPOLOGY_TYPE_FCM = 1,
        LOBBY_TOPOLOGY_TYPE_STAR = 2,
        LOBBY_TOPOLOGY_TYPE_CONNECTIONLESS = 3,
        LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION = 4
    }

    public enum LobbyType
    {
        LOBBY_TYPE_PRIVATE = 0,
        LOBBY_TYPE_FRIENDS_ONLY = 1,
        LOBBY_TYPE_PUBLIC = 2,
        LOBBY_TYPE_INVISIBLE_TO_FRIENDS = 3
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
            max_members = 0;
            joinable = true;
            owner_id = new GalaxyID(0);
            this.id = id;
            this.topology_type = topology_type;
            this.type = type;
        }

        public Lobby(ulong id, LobbyTopologyType topology_type, LobbyType type)
        {
            max_members = 0;
            joinable = true;
            owner_id = new GalaxyID(0);
            this.id = new GalaxyID(id, GalaxyID.Type.ID_TYPE_LOBBY);
            this.topology_type = topology_type;
            this.type = type;
        }
    }
}
