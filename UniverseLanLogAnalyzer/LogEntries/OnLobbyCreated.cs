using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyCreated : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyCreatedListener::OnLobbyCreated";

        public GalaxyID? LobbyID;
        public LobbyCreateResult Result;

        public OnLobbyCreated(Base original) : base(original) 
        {
            IsKeyFrame = true;
        }

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

        public override void ProcessState(State state)
        {
            base.ProcessState(state);

            if(Result == LobbyCreateResult.LOBBY_CREATE_RESULT_SUCCESS)
            {
                Lobby lobby = state.UnassignedLobbies.ElementAt(0);
                lobby.id = LobbyID;
                state.Lobbies.Add(LobbyID, lobby);
            }

            state.UnassignedLobbies.RemoveAt(0);
        }
    }
}
