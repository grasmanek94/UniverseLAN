using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyDataUpdated : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyDataListener::OnLobbyDataUpdated";

        public GalaxyID? LobbyID;
        public GalaxyID? MemberID;

        public OnLobbyDataUpdated(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            memberID: 0(ID_TYPE_UNASSIGNED)
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nmemberID: {gid}",
                out LobbyID, out MemberID))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
