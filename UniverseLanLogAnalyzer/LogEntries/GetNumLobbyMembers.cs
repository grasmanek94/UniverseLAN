using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetNumLobbyMembers : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetNumLobbyMembers";

        public GalaxyID? LobbyID;
        public int NumLobbyMembers;

        public GetNumLobbyMembers(Base original) : base(original)
        {
            CollapseRepeat = true;
        }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            result: 1
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nresult: {d}",
                out LobbyID, out NumLobbyMembers))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
