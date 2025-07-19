using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SetRichPresence : Base
    {
        public static readonly string MATCH = "universelan::client::FriendsImpl::SetRichPresence";

        public string Key = "";
        public string Value = "";
        public Optional<long> ListenerAddress = new();

        public SetRichPresence(Base original) : base(original) {}

        /* Example contents:
            key: status
            value: Creating a lobby
            listener: 0x1234567890
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "key: {s}\nvalue: {s}\nlistener: {x}", 
                out Key, out Value, out ListenerAddress))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
