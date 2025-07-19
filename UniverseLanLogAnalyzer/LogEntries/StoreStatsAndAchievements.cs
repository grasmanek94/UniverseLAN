using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class StoreStatsAndAchievements : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::StoreStatsAndAchievements";
        
        public Optional<long> ListenerAddress = new();

        public StoreStatsAndAchievements(Base original) : base(original) { }

        /* Example contents:
            listener: 0x1234567890
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "listener: {x}",
                out ListenerAddress))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
