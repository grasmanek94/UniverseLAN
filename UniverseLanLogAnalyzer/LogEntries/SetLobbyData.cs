using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SetLobbyData : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::SetLobbyData";

        public GalaxyID? LobbyID;
        public string Key = "";
        public string Value = "";
        public Optional<long> ListenerAddress = new();
        public bool Result = false;

        public SetLobbyData(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            key: name
            value: TestGalaxyUserA's lobby
            listener: 0x1234567890
            result: true
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nkey: {s}\nvalue: {s}\nlistener: {x}\nresult: {b}", 
                out LobbyID, out Key, out Value, out ListenerAddress, out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
