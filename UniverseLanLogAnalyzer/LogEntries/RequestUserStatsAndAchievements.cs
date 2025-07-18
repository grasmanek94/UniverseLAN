using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestUserStatsAndAchievements : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::RequestUserStatsAndAchievements";

        public GalaxyID UserID { get; set; }

        public RequestUserStatsAndAchievements(Base original) : base(original)
        {
            var temp = Parser.Arguments.ParseGalaxyID("userID", this);
            if (temp == null)
            {
                throw new InterceptorEntryInitException(this, "userID");
            }
            UserID = temp;
        }
    }
}
