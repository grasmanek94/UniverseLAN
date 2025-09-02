using MessagePack;
using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    [MessagePackObject]
    public class User
    {
        [Key(0)]
        public GalaxyID id;

        public User(GalaxyID id)
        {
            this.id = id;
        }

        public User(ulong id)
        {
            this.id = new GalaxyID(id, GalaxyID.Type.ID_TYPE_USER);
        }

        public User DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }
}
