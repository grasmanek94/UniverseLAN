using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestUserStatsAndAchievements : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::RequestUserStatsAndAchievements";

        public GalaxyID? UserID;
        public Optional<long> ListenerAddress = new();

        public RequestUserStatsAndAchievements(Base original) : base(original) {}

        /* Example contents (prefix=userID):
            userID: 46781906533578385(ID_TYPE_USER)
            listener: 0x1234567890
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties, "userID: {gid}\nlistener: {x}", out UserID, out ListenerAddress))
            {
                throw new InterceptorArgumentParsingException(this, "userID");
            }
        }
    }
}
