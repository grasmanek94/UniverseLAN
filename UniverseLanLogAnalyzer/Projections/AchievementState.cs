using MessagePack;

namespace UniverseLanLogAnalyzer.Projections
{
    [MessagePackObject]
    public class AchievementState
    {
        [Key(0)]
        public bool unlocked;

        [Key(1)]
        public uint unlock_time;
    }
}