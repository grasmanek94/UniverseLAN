using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class DeleteLobbyData : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::DeleteLobbyData";
        
        public GalaxyID? LobbyID;
        public string Key = "";
        public Optional<long> ListenerAddress = new();
        public bool Result = false;

        public DeleteLobbyData(Base original) : base(original) {}

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            key: modifier-0
            result: true
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nkey: {s}\nlistener: {x}\nresult: {b}",
                out LobbyID, out Key, out ListenerAddress, out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
