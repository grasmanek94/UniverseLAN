using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyEntered : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyEnteredListener::OnLobbyEntered";
        
        public GalaxyID? LobbyID;
        public LobbyEnterResult LobbyEnterResult;

        public OnLobbyEntered(Base original) : base(original) {}

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            result: LOBBY_ENTER_RESULT_SUCCESS
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nresult: {e}",
                out LobbyID, out LobbyEnterResult))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
