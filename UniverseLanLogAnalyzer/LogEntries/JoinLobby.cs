using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class JoinLobby : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::JoinLobby";

        public GalaxyID? LobbyID;
        public Optional<ulong> ListenerAddress = new();

        public JoinLobby(Base original) : base(original)
        {
            IsKeyFrame = true;
        }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            listener: 0x1234567890abc
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nlistener: {x}",
                out LobbyID, out ListenerAddress))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
