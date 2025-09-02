namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    using MessagePack;
    using UniverseLanLogAnalyzer.Util;

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

    [MessagePackObject]
    public class Lobby
    {
        [Key(0)]
        public GalaxyID id;
        [Key(1)]
        public GalaxyID owner_id;
        [Key(2)]
        public bool joinable;
        [Key(3)]
        public uint max_members;
        [Key(4)]
        public LobbyKVType kv_store = new();
        [Key(5)]
        public LobbyUserKVType user_kv_store = new();
        [Key(6)]
        public LobbyMessagesType messages = new();
        [Key(7)]
        public LobbyTopologyType topology_type;
        [Key(8)]
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

        /* Don't use, only for serialization */
        public Lobby() : this(0, LobbyTopologyType.LOBBY_TOPOLOGY_TYPE_FCM_HOST_MIGRATION, LobbyType.LOBBY_TYPE_PRIVATE) {}

        public Lobby DeepClone()
        {      
            return CloneUtils.DeepClone(this);
        }
    }
}
