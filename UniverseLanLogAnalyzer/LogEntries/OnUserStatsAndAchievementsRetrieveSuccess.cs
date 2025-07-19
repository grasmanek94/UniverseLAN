using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnUserStatsAndAchievementsRetrieveSuccess : Base
    {
        public static readonly string MATCH = "universelan::client::UserStatsAndAchievementsRetrieveListener::OnUserStatsAndAchievementsRetrieveSuccess";

        public GalaxyID? UserID;

        public OnUserStatsAndAchievementsRetrieveSuccess(Base original) : base(original) { }

        /* Example contents:
            userID: 46781908214750428(ID_TYPE_USER)
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "userID: {gid}",
                out UserID))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
