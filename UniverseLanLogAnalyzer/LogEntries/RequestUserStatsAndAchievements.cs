using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestUserStatsAndAchievements : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::RequestUserStatsAndAchievements";

        public GalaxyID UserID { get; set; }

        public RequestUserStatsAndAchievements(Base original) : base(original)
        {

            foreach (var entry in Properties)
            {
                string trimmed = entry.Trim();

            }

        }
    }
}
