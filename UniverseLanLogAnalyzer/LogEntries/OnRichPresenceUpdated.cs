using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnRichPresenceUpdated : Base
    {
        public static readonly string MATCH = "universelan::client::RichPresenceListener::OnRichPresenceUpdated";

        public GalaxyID? UserID;

        public OnRichPresenceUpdated(Base original) : base(original) {}

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
