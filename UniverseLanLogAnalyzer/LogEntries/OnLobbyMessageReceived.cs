using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyMessageReceived : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyMessageListener::OnLobbyMessageReceived";
        
        public GalaxyID? LobbyID;
        public GalaxyID? SenderID;
        public ulong MessageID;
        public int MessageLength;

        public OnLobbyMessageReceived(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            senderID: 46781906533578385(ID_TYPE_USER)
            messageID: 0
            messageLength: 5
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nsenderID: {gid}\nmessageID: {d}\nmessageLength: {d}",
                out LobbyID, out SenderID, out MessageID, out MessageLength))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
