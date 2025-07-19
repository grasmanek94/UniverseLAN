using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class ListenerRegistrarRegister : Base
    {
        public static readonly string MATCH = "universelan::client::ListenerRegistrarImpl::Register";

        public Galaxy.ListenerTypeInfo? Info { get; set; }

        public ListenerRegistrarRegister(Base original) : base(original)
        {
        }

        /* Example contents:
            listenerType: AUTH
            listener: 0x137e668
        */
        public override void PostInit()
        {
            ListenerType type;
            ulong listener_address;

            if (!PropertyParser.Parse(ref Properties, "listenerType: {e}\nlistener: {x}", out type, out listener_address))
            {
                throw new InterceptorArgumentParsingException(this, "listener");
            }

            Info = new ListenerTypeInfo { Type = type, ListenerAddress = listener_address };
        }
    }
}
