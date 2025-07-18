using System.Data;
using System.Globalization;
using System.Windows.Forms;
using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.Parser
{
    public static class Arguments
    {
        /* Example contents (prefix=userID):
            userID: 46781906533578385(ID_TYPE_USER)
        */
        /* Example contents (prefix=lobbyID):
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
        */
        public static GalaxyID ParseGalaxyID(string prefix, LogEntries.Base entry)
        {
            GalaxyID.Type id_type;
            ulong id_num;

            if(!PropertyParser.Parse(ref entry.Properties, $"{prefix}: {{d}}({{e}})", out id_num, out id_type))
            {
                throw new InterceptorArgumentParsingException(entry, prefix);
            }

            return new GalaxyID(id_num, id_type);
        }

        /* Example contents:
            listenerType: AUTH
            listener: 0x137e668
        */
        public static ListenerTypeInfo ParseListenerRegister(LogEntries.Base entry)
        {
            ListenerType type;
            ulong listener_address;

            if (!PropertyParser.Parse(ref entry.Properties, "listenerType: {e}\nlistener: {x}", out type, out listener_address))
            {
                throw new InterceptorArgumentParsingException(entry, "listener");
            }

            return new ListenerTypeInfo { Type = type, ListenerAddress = listener_address };
        }

        /* Example contents:
            operationalState: 3(OPERATIONAL_STATE_SIGNED_IN|OPERATIONAL_STATE_LOGGED_ON)
        */
        /* Example contents:
            operationalState: 0()
        */
        public static void ParseOperationalState(LogEntries.Base entry, out OperationalState state)
        {
            if (!PropertyParser.Parse(ref entry.Properties, "operationalState: {d}({ef})", out long num, out state))
            {
                throw new InterceptorArgumentParsingException(entry, "operationalState");
            }
        }
    }
}
