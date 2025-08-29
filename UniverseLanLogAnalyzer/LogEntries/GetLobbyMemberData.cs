using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetLobbyMemberData : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetLobbyMemberData";

        public GalaxyID? LobbyID;
        public GalaxyID? MemberID;
        public string Key = "";
        public string Value = "";

        public GetLobbyMemberData(Base original) : base(original) {}

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            memberID: 46781906533578385(ID_TYPE_USER)
            key: name
            result: TestGalaxyUserA
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nmemberID: {gid}\nkey: {s}\nresult: {s}",
                out LobbyID, out MemberID, out Key, out Value))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
