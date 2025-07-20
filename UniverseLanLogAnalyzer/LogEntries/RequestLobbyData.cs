using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestLobbyData : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::RequestLobbyData";

        public GalaxyID? LobbyID;
        public Optional<ulong> ListenerAddress = new();
        public Optional<bool> Result = new ();

        public RequestLobbyData(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            result: true
        */
        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            listener: 0x1234567890abcd
            result: true
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nlistener: {x}\nresult: {b}",
                out LobbyID, out ListenerAddress, out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
