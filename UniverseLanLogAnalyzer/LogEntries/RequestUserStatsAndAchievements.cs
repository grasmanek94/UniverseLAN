using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestUserStatsAndAchievements : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::RequestUserStatsAndAchievements";

        public GalaxyID? UserID { get; set; }

        public RequestUserStatsAndAchievements(Base original) : base(original)
        {

        }

        /* Example contents (prefix=userID):
            userID: 46781906533578385(ID_TYPE_USER)
        */
        public override void PostInit()
        {
            GalaxyID id;

            if (!PropertyParser.Parse(ref Properties, "userID: {gid}", out id))
            {
                throw new InterceptorArgumentParsingException(this, "userID");
            }

            UserID = id;
        }
    }
}
