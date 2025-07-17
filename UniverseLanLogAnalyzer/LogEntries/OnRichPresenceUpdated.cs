namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnRichPresenceUpdated : Base
    {
        public static readonly string MATCH = "universelan::client::RichPresenceListener::OnRichPresenceUpdated";

        public OnRichPresenceUpdated(Base original) : base(original)
        {
        }
    }
}
