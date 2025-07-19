using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyList : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyListListener::OnLobbyList";

        public int LobbyCount;
        public Optional<LobbyListResult> ListResult = new();
        public Optional<bool> IOFailure = new();

        public OnLobbyList(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            result: LOBBY_LIST_RESULT_SUCCESS
        */
        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            ioFailure: false
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyCount: {d}\nresult: {e}\nioFailure: {b}",
                out LobbyCount, out ListResult, out IOFailure))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
