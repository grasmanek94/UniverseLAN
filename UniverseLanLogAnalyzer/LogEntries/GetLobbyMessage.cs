using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetLobbyMessage : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetLobbyMessage";

        public GalaxyID? LobbyID;
        public int MessageID;
        public ulong BufferAddress;
        public ulong BufferSize;
        public ulong DataSizeResult;
        public Optional<string> Message = new();
        public Optional<ulong> MessageHash = new();
        public Optional<string> MessageHex = new();
        public Optional<string> MessageEnc = new();

        public GetLobbyMessage(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            messageID: 0
            msg: 0xf5ecd4
            msgLength: 32
            result: 6
            result_msg: hello
            result_msg_hash: 4d25767f9dce13f5
            result_msg_hex: aabbccddee00
            result_msg_enc: hello%00
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nmessageID: {d}\nmsg: {x}\nmsgLength: {d}\nresult: {d}\nresult_msg: {s}\nresult_msg_hash: {x}\nresult_msg_hex: {s}\nresult_msg_enc: {s}",
                out LobbyID, out MessageID, out BufferAddress, out BufferSize, out DataSizeResult, out Message, out MessageHash, out MessageHex, out MessageEnc))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
