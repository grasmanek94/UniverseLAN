using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SetMaxNumLobbyMembers : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::SetMaxNumLobbyMembers";

        public GalaxyID? LobbyID;
        public int MaxNumLobbyMembers;
        public bool Result;
        public Optional<long> ListenerAddress = new();

        public SetMaxNumLobbyMembers(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            maxNumLobbyMembers: 4
            listener: 0x1234567890
            result: true
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nmaxNumLobbyMembers: {d}\nlistener: {x}\nresult: {b}",
                out LobbyID, out MaxNumLobbyMembers, out Result, out ListenerAddress))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
