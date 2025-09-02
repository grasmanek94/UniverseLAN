using MessagePack;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Galaxy
{
    [MessagePackObject]
    public class State
    {
        [Key(0)]
        public Dictionary<GalaxyID, Lobby> Lobbies = new();
        [Key(1)]
        public Dictionary<GalaxyID, User> Users = new();
        [Key(2)]
        public Dictionary<ulong, ListenerType> ActiveListenerTypes = new();

        public State() { }

        public State DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }
}
