using MessagePack;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Projections
{

    [MessagePackObject]
    public class UserAchievementsSnapshot
    {
        [Key(0)]
        public GalaxyID id = new GalaxyID(0);

        [Key(1)]
        public Dictionary<string, AchievementState> values = new();

        public UserAchievementsSnapshot DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }
}
