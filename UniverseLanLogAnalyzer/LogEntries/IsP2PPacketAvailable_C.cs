using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class IsP2PPacketAvailable_C : Base
    {
        public static readonly string MATCH = "universelan::client::NetworkingImpl::IsP2PPacketAvailable[C]";

        public ulong OutMsgSizeAddr;
        public ulong OutMsgSize;
        public int Channel;
        public bool Result = false;

        public IsP2PPacketAvailable_C(Base original) : base(original) { }

        /* Example contents:
            outMsgSize(addr): 0xf5f90c
            channel: 1
            result: false
            outMsgSize: 0
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "outMsgSize(addr): {x}\nchannel: {d}\nresult: {b}\noutMsgSize: {d}",
                out OutMsgSizeAddr, out Channel, out Result, out OutMsgSize))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
