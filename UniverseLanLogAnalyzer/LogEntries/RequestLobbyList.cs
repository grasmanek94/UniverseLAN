using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestLobbyList : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::RequestLobbyList";

        public Optional<bool> AllowFullLobbies = new ();
        public Optional<ulong> ListenerAddress = new();

        public RequestLobbyList(Base original) : base(original) { }

        /* Example contents:
            allowFullLobbies: true
            listener: 0x1234567890abcde
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "allowFullLobbies: {b}\nlistener: {x}",
                out AllowFullLobbies, out ListenerAddress))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
