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

        public static GalaxyID? ParseGalaxyID(string prefix, LogEntries.Base entry)
        {
            foreach (var prop in entry.Properties)
            {
                string key = string.Empty;
                string value = string.Empty;
                string? type_str = null;

                ulong id = 0;
                GalaxyID.Type type;

                if (!TryParseKeyValueExtra(prop, out key, out value, out type_str))
                {
                    continue;
                }

                if (!key.Equals(prefix, StringComparison.Ordinal))
                {
                    continue;
                }

                if (type_str == null)
                {
                    throw new InterceptorArgumentParsingException(entry, key, prop);
                }

                if (!Enum.TryParse(type_str, out type))
                {
                    throw new InterceptorArgumentParsingException(entry, key, prop);
                }

                if (!ulong.TryParse(value, out id))
                {
                    throw new InterceptorArgumentParsingException(entry, key, prop);
                }

                return new GalaxyID(id, type);
            }

            return null;
        }

        public static ListenerTypeInfo? ParseListenerRegister(LogEntries.Base entry)
        {
            ListenerTypeInfo? listener_info = null;
            string prefix = "listenerType";

            foreach (var prop in entry.Properties)
            {
                string key = string.Empty;
                string value = string.Empty;
                string? type_str = null;

                ulong id = 0;
                ListenerType type;

                if (!TryParseKeyValueExtra(prop, out key, out value, out type_str))
                {
                    if (listener_info == null)
                    {
                        continue;
                    }
                    else
                    {
                        throw new InterceptorArgumentParsingException(entry, key, prop);
                    }
                }

                if (!key.Equals(prefix, StringComparison.Ordinal))
                {
                    if (listener_info == null)
                    {
                        continue;
                    }
                    else
                    {
                        throw new InterceptorArgumentParsingException(entry, key, prop);
                    }
                }

                if (!ulong.TryParse(value, out id))
                {
                    throw new InterceptorArgumentParsingException(entry, key, prop);
                }

                if (listener_info == null)
                {
                    if (type_str == null)
                    {
                        throw new InterceptorArgumentParsingException(entry, key, prop);
                    }

                    if (!Enum.TryParse(type_str, out type))
                    {
                        throw new InterceptorArgumentParsingException(entry, key, prop);
                    }

                    listener_info = new();
                    listener_info.Type = type;
                    listener_info.RawTypeId = id;

                    prefix = "listener";
                    continue;
                }
                else
                {
                    listener_info.ListenerAddress = id;
                    return listener_info;
                }
            }

            return listener_info;
        }
    }
}
