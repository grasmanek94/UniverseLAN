using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class ListenerRegistrarUnregister : Base
    {
        public static readonly string MATCH = "universelan::client::ListenerRegistrarImpl::Unregister";

        public ListenerType ListenerType;
        public ulong ListenerAddress;

        public ListenerRegistrarUnregister(Base original) : base(original) {}

        /* Example contents:
            listenerType: AUTH
            listener: 0x137e668
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties, "listenerType: {e}\nlistener: {x}", out ListenerType, out ListenerAddress))
            {
                throw new InterceptorArgumentParsingException(this, "listener");
            }
        }
    }
}
