using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SetLobbyMemberData : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::SetLobbyMemberData";

        public GalaxyID? LobbyID;
        public string Key = "";
        public string Value = "";
        public Optional<long> ListenerAddress = new();

        public SetLobbyMemberData(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            key: skin
            value:
            listener: 0x1234567890
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties, 
                "lobbyID: {gid}\nkey: {s}\nvalue: {s}\nlistener: {x}", 
                out LobbyID, out Key, out Value, out ListenerAddress))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
