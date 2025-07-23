using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetLobbyMemberByIndex : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetLobbyMemberByIndex";

        public GalaxyID? LobbyID;
        public int Index;
        public GalaxyID? UserID;

        public GetLobbyMemberByIndex(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            index: 0
            result: 46781908214750428(ID_TYPE_USER)
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nindex: {d}\nresult: {gid}",
                out LobbyID, out Index, out UserID))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
