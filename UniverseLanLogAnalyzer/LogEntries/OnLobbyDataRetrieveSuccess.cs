using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyDataRetrieveSuccess : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyDataRetrieveListener::OnLobbyDataRetrieveSuccess";

        public GalaxyID? LobbyID;

        public OnLobbyDataRetrieveSuccess(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}",
                out LobbyID))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
