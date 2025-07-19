using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class ListenerRegistrarRegister : Base
    {
        public static readonly string MATCH = "universelan::client::ListenerRegistrarImpl::Register";

        public ListenerType ListenerType;
        public ulong ListenerAddress;

        public ListenerRegistrarRegister(Base original) : base(original) {}

        /* Example contents:
            listenerType: AUTH
            listener: 0x137e668
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "listenerType: {e}\nlistener: {x}",
                out ListenerType, out ListenerAddress))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
