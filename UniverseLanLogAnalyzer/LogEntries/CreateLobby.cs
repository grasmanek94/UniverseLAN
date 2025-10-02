using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class CreateLobby : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::CreateLobby";

        public LobbyType LobbyType;
        public uint LobbyMaxMembers = 0;
        public Optional<bool> LobbyJoinable = new();
        public Optional<LobbyTopologyType> LobbyTopology = new();
        public Optional<ulong> LobbyCreatedListener = new();
        public Optional<ulong> LobbyEnteredListener = new();

        public CreateLobby(Base original) : base(original)
        {
            IsKeyFrame = true;
        }

        /* Example contents:
            lobbyType: LOBBY_TYPE_PUBLIC
            maxMembers: 250
            joinable: true
            lobbyTopologyType: LOBBY_TOPOLOGY_TYPE_FCM
            lobbyCreatedListener: 0x0123456789abcde
            lobbyEnteredListener: 0x0123456789abcde
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyType: {e}\nmaxMembers: {d}\njoinable: {b}\nlobbyTopologyType: {e}\nlobbyCreatedListener: {x}\nlobbyEnteredListener: {x}",
                out LobbyType, out LobbyMaxMembers, out LobbyJoinable, out LobbyTopology, out LobbyCreatedListener, out LobbyEnteredListener))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }

        public override void ProcessState(State state)
        {
            base.ProcessState(state);
            Lobby lobby = new Lobby();
            lobby.max_members = LobbyMaxMembers;
            lobby.joinable = LobbyJoinable;
            lobby.topology_type = LobbyTopology;
            lobby.entered_listener = LobbyEnteredListener;
            lobby.created_listener = LobbyCreatedListener;

            state.UnassignedLobbies.Add(lobby);
        }
    }
}
