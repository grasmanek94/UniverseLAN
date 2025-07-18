using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestUserStatsAndAchievements : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::RequestUserStatsAndAchievements";

        public GalaxyID? UserID { get; set; }

        public RequestUserStatsAndAchievements(Base original) : base(original)
        {

        }

        public override void PostInit()
        {
            UserID = Parser.Arguments.ParseGalaxyID("userID", this);
            if (UserID == null)
            {
                throw new InterceptorEntryInitException(this, "userID");
            }
        }
    }
}
