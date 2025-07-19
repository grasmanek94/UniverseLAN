using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SendP2PPacket_C : Base
    {
        public static readonly string MATCH = "universelan::client::NetworkingImpl::SendP2PPacket[C]";

        public GalaxyID? Target;
        public int DataSize;
        public P2PSendType P2PSendType;
        public int Channel;
        public ulong DataHash;
        public string DataHex = "";
        public string DataEnc = "";
        public bool Result = false;

        public SendP2PPacket_C(Base original) : base(original) {}

        /* Example contents:
            galaxyID: 46781906533578385(ID_TYPE_USER)
            data: 0xf5f4ac
            dataSize: 4
            sendType: P2P_SEND_UNRELIABLE_IMMEDIATE
            channel: 0
            data_hash: 4d25767f9dce13f5
            data_contents_hex: 00000000
            data_contents_enc: %00%00%00%00
            result: true
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "galaxyID: {gid}\ndata: {*}\ndataSize: {d}\nsendType: {e}\nchannel: {d}\ndata_hash: {x}\ndata_contents_hex: {s}\ndata_contents_enc: {s}",
                out Target, out DataSize, out P2PSendType, out Channel, out DataHash, out DataHex, out DataEnc, out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
