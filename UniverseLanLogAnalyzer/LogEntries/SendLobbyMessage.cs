using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SendLobbyMessage : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::SendLobbyMessage";

        public GalaxyID? LobbyID;
        public ulong DataSize;
        public string Message = "";
        public Optional<ulong> MessageHash = new();
        public Optional<string> MessageHex = new();
        public Optional<string> MessageEnc = new();
        public bool Result = false;

        public SendLobbyMessage(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            data: 0xf5f410
            dataSize: 6
            msg: hello
            msg_hash: 4d25767f9dce13f5
            msg_hex: aabbccddee00
            msg_enc: hello%00
            result: true
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\ndata: {*}\ndataSize: {d}\nmsg: {s}\nmsg_hash: {x}\nmsg_hex: {s}\nmsg_enc: {s}\nresult: {b}",
                out LobbyID, out DataSize, out Message, out MessageHash, out MessageHex, out MessageEnc, out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
