using System.Globalization;
using System.Windows.Forms;
using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.Parser
{
    public static class Arguments
    {
        public static bool TryParseKeyValueExtra(
            string input,
            out string key,
            out string value,
            out string? extra)
        {
            key = string.Empty;
            value = string.Empty;
            extra = null;

            int colonIndex = input.Trim().IndexOf(':');
            if (colonIndex == -1 || colonIndex + 1 >= input.Length)
                return false;

            key = input.Substring(0, colonIndex).Trim();

            int openParen = input.IndexOf('(', colonIndex);
            if (openParen == -1)
            {
                value = input.Substring(colonIndex + 1).Trim();
                return true;
            }

            value = input.Substring(colonIndex + 1, openParen - colonIndex - 1).Trim();

            int closeParen = input.IndexOf(')', openParen);
            if (closeParen == -1)
            {
                return false;
            }

            extra = input.Substring(openParen + 1, closeParen - openParen - 1).Trim();
            return true;
        }

        public static bool TryParseProperty<T>(
            LogEntries.Base entry,
            string keyName,
            Func<string, string?, T> converter,
            out T result)
        {
            for (int i = 0; i < entry.Properties.Count; i++)
            {
                string prop = entry.Properties[i];
                if (!TryParseKeyValueExtra(prop, out var key, out var value, out var extra))
                    continue;

                if (!key.Equals(keyName, StringComparison.Ordinal))
                    continue;

                try
                {
                    result = converter(value, extra);
                    entry.Properties.RemoveAt(i);
                    return true;
                }
                catch
                {
                    throw new InterceptorArgumentParsingException(entry, key, prop);
                }
            }

            result = default!;
            return false;
        }

        public static bool TryParseGrouped<T>(
            LogEntries.Base entry,
            Func<List<(string key, string value, string? extra)>, T?> builder,
            out T? result)
        {
            var parsed = new List<(string key, string value, string? extra, int index)>();

            for (int i = 0; i < entry.Properties.Count; i++)
            {
                if (!TryParseKeyValueExtra(entry.Properties[i], out var key, out var value, out var extra))
                {
                    continue;
                }

                parsed.Add((key, value, extra, i));

                var simplified = parsed.Select(p => (p.key, p.value, p.extra)).ToList();
                result = builder(simplified);
                if (result != null)
                {
                    // Remove only the matched entries
                    foreach (var (_, _, _, index) in parsed)
                    {
                        entry.Properties[index] = null!; // Mark for removal
                    }

                    entry.Properties.RemoveAll(p => p == null);
                    return true;
                }
            }

            result = default;
            return false;
        }

        /* Example contents (prefix=userID):
            userID: 46781906533578385(ID_TYPE_USER)
        */
        /* Example contents (prefix=lobbyID):
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
        */
        public static GalaxyID? ParseGalaxyID(string prefix, LogEntries.Base entry)
        {
            return TryParseProperty(entry, prefix, (value, extra) =>
            {
                if (extra == null)
                {
                    throw new InterceptorArgumentParsingException(entry, prefix, "");
                }

                if (!ulong.TryParse(value, out var id))
                {
                    throw new InterceptorArgumentParsingException(entry, prefix, value);
                }

                if (!Enum.TryParse(extra, out GalaxyID.Type type))
                {
                    throw new InterceptorArgumentParsingException(entry, prefix, extra);
                }

                return new GalaxyID(id, type);
            }, out var result) ? result : null;
        }

        /* Example contents:
            listenerType: AUTH
            listener: 0x137e668
        */
        public static ListenerTypeInfo? ParseListenerRegister(LogEntries.Base entry)
        {
            TryParseGrouped(entry, parsed =>
            {
                if (parsed.Count < 2)
                {
                    return null;
                }

                var (key1, value1, _) = parsed[0];
                var (key2, value2, _) = parsed[1];

                if (key1 != "listenerType" || key2 != "listener")
                {
                    return null;
                }

                if (!Enum.TryParse(value1, out ListenerType type))
                {
                    throw new InterceptorArgumentParsingException(entry, key1, value1);
                }

                if (!ulong.TryParse(value2.Substring(2), NumberStyles.HexNumber, CultureInfo.InvariantCulture, out var addr))
                {
                    throw new InterceptorArgumentParsingException(entry, key2, value2);
                }

                return new ListenerTypeInfo { Type = type, ListenerAddress = addr };
            }, out var result);

            return result;
        }

        /* Example contents:
            operationalState: 3(OPERATIONAL_STATE_SIGNED_IN|OPERATIONAL_STATE_LOGGED_ON)
        */
        /* Example contents:
            operationalState: 0()
        */
        public static bool ParseOperationalState(LogEntries.Base entry, out OperationalState state)
        {
            return TryParseProperty(entry, "operationalState", (value, _) =>
            {
                if (!ulong.TryParse(value, out var num))
                {
                    throw new InterceptorArgumentParsingException(entry, "operationalState", value);
                }
                return (OperationalState)num;
            }, out state);
        }
    }
}
