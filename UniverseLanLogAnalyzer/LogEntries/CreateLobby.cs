using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class CreateLobby : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::CreateLobby";

        public LobbyType LobbyType;
        public int LobbyMaxMembers = 0;
        public Optional<bool> LobbyJoinable = new();
        public Optional<LobbyTopologyType> LobbyTopology = new();
        public Optional<ulong> LobbyCreatedListener = new();
        public Optional<ulong> LobbyEnteredListener = new();

        public CreateLobby(Base original) : base(original) {}

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
    }
}
