using MessagePack;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Projections
{
    [MessagePackObject]
    public class P2PPacketSnapshot
    {
        [Key(0)]
        public GalaxyID from = new GalaxyID(0);

        [Key(1)]
        public string data_hex = string.Empty;

        public P2PPacketSnapshot DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }
}
