using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class ReadP2PPacket_C : Base
    {
        public static readonly string MATCH = "universelan::client::NetworkingImpl::ReadP2PPacket[C]";

        public int Channel;
        public bool Result = false;
        public Optional<GalaxyID> From = new();
        public Optional<int> DataSize = new();
        public Optional<ulong> DataHash = new();
        public Optional<string> DataHex = new();
        public Optional<string> DataEnc = new();

        public ReadP2PPacket_C(Base original) : base(original) { }

        /* Example contents:
            dest: 0x1234567890
            destSize: 32
            outMsgSize(addr): 0x1234567890
            channel: 0
            result: true
            outGalaxyID: 46781906533578385(ID_TYPE_USER)
            outMsgSize: 6
            data_hash: 4d25767f9dce13f5
            data_contents_hex: 00000000
            data_contents_enc: %00%00%00%00
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "dest: {*}\ndestSize: {*}\noutMsgSize(addr): {*}\nchannel: {d}\nresult: {b}\noutGalaxyID: {gid}\noutMsgSize: {d}\ndata_hash: {x}\ndata_contents_hex: {s}\ndata_contents_enc: {s}",
                out Channel, out Result, out From, out DataSize, out DataHash, out DataHex, out DataEnc))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
