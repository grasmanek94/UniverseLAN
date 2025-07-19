using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetMaxNumLobbyMembers : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetMaxNumLobbyMembers";
        
        public GalaxyID? LobbyID;
        public int MaxNumLobbyMembers;

        public GetMaxNumLobbyMembers(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            result: 250
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nresult {d}",
                out LobbyID, out MaxNumLobbyMembers))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
