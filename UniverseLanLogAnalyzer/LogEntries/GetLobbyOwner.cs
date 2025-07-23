using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetLobbyOwner : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetLobbyOwner";

        public GalaxyID? LobbyID;
        public GalaxyID? OwnerID;

        public GetLobbyOwner(Base original) : base(original)
        {
            CollapseRepeat = true;
        }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            result: 46781906533578385(ID_TYPE_USER)
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties, 
                "lobbyID: {gid}\nresult: {gid}",
                out LobbyID, out OwnerID))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
