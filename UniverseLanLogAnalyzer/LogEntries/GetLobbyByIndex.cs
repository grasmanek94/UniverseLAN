using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetLobbyByIndex : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetLobbyByIndex";

        public int Index;
        public GalaxyID? LobbyID;
 
        public GetLobbyByIndex(Base original) : base(original) { }

        /* Example contents:
            index: 0
            result: 58815465033870437(ID_TYPE_LOBBY)
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "index: {d}\nresult: {gid}",
                out Index, out LobbyID))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
