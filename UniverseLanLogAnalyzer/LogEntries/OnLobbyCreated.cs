using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyCreated : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyCreatedListener::OnLobbyCreated";

        public GalaxyID? LobbyID;
        public LobbyCreateResult Result;

        public OnLobbyCreated(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            result: LOBBY_CREATE_RESULT_SUCCESS
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nresult: {e}",
                out LobbyID, out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
