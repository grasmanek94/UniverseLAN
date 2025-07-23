using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetLobbyData : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetLobbyData";

        public GalaxyID? LobbyID;
        public string Key = "";
        public string Value = "";

        public GetLobbyData(Base original) : base(original) {}

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            key: name
            result: TestGalaxyUserA's lobby
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nkey: {s}\nresult: {s}",
                out LobbyID, out Key, out Value))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
