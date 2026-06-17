using MessagePack;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Projections
{
    [MessagePackObject]
    public class UserStatsSnapshot
    {
        [Key(0)]
        public GalaxyID id = new GalaxyID(0);

        [Key(1)]
        public Dictionary<string, int> values = new();

        public UserStatsSnapshot DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }
}
