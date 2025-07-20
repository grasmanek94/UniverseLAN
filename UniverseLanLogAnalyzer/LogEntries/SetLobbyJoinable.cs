using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SetLobbyJoinable : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::SetLobbyJoinable";

        public GalaxyID? LobbyID;
        public bool Joinable = false;
        public Optional<long> ListenerAddress = new();
        public bool Result = false;

        public SetLobbyJoinable(Base original) : base(original) {}

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            joinable: true
            listener: 0x1234567890
            result: true
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\njoinable: {b}\nlistener: {x}\nresult: {b}",
                out LobbyID, out Joinable, out ListenerAddress, out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
