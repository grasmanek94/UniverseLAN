using System.Text.RegularExpressions;

namespace UniverseLanLogAnalyzer.Parser
{
    public static class PropertyParser
    {
        private static readonly Regex PlaceholderRegex = new(@"\{(d|x|e|ef|b|s)(\?([a-zA-Z_][a-zA-Z0-9_]*)==(.+?))?\}");

        public static bool Parse(ref string[] properties, string template, object[] outputs, Type[] types)
        {
            var lines = template.Split('\n');
            var matchedIndices = new HashSet<int>();
            var outputIndex = 0;
            var context = new Dictionary<string, object>();

            foreach (var line in lines)
            {
                var placeholders = new List<(string type, string? condVar, string? condVal)>();
                string pattern = line;
                pattern = PlaceholderRegex.Replace(pattern, match =>
                {
                    placeholders.Add((
                        match.Groups[1].Value,
                        match.Groups[3].Success ? match.Groups[3].Value : null,
                        match.Groups[4].Success ? match.Groups[4].Value : null
                    ));
                    return "(.+?)";
                });
                pattern = Regex.Escape(pattern);
                pattern = pattern.Replace(Regex.Escape("(.+?)"), "(.+?)");

                var regex = new Regex("^" + pattern + "$");

                bool matched = false;

                for (int i = 0; i < properties.Length; i++)
                {
                    if (matchedIndices.Contains(i)) continue;

                    var prop = properties[i];
                    var match = regex.Match(prop);
                    if (!match.Success) continue;

                    // Check condition
                    bool skip = false;
                    foreach (var (_, condVar, condVal) in placeholders)
                    {
                        if (condVar != null)
                        {
                            if (!context.TryGetValue(condVar, out var actualVal) ||
                                !actualVal.ToString().Equals(condVal, StringComparison.OrdinalIgnoreCase))
                            {
                                skip = true;
                                break;
                            }
                        }
                    }

                    if (skip) continue;

                    matched = true;
                    matchedIndices.Add(i);

                    for (int j = 0; j < placeholders.Count; j++)
                    {
                        var (type, condVar, _) = placeholders[j];
                        var value = match.Groups[j + 1].Value;

                        if (type == "*") continue;
                        if (outputIndex >= outputs.Length)
                            throw new InvalidOperationException("Too few output parameters.");

                        object parsed = type switch
                        {
                            "d" => ParseNumber(types[outputIndex], value),
                            "x" => ParseHex(types[outputIndex], value),
                            "b" => ParseBool(value),
                            "e" => ParseEnum(types[outputIndex], value),
                            "ef" => ParseEnumFlags(types[outputIndex], value),
                            "s" => value,
                            _ => throw new NotSupportedException($"Unsupported placeholder: {type}")
                        };


                        outputs[outputIndex] = parsed;
                        context[$"arg{outputIndex}"] = parsed;
                        outputIndex++;
                    }

                    break;
                }

                if (!matched)
                    return false;
            }

            // Remove matched entries
            properties = properties.Where((_, i) => !matchedIndices.Contains(i)).ToArray();
            return true;
        }

        private static bool ParseBool(string value)
        {
            return value.Trim().ToLowerInvariant() switch
            {
                "true" or "1" or "yes" or "y" => true,
                "false" or "0" or "no" or "n" => false,
                _ => throw new FormatException($"Invalid boolean: {value}")
            };
        }

        private static object ParseNumber(Type type, string value)
        {
            if (type.IsEnum)
            {
                var underlying = Enum.GetUnderlyingType(type);
                var numeric = Convert.ChangeType(value, underlying);
                return Enum.ToObject(type, numeric);
            }
            return Convert.ChangeType(value, type);
        }

        private static object ParseHex(Type type, string value)
        {
            string simplified_value = value.StartsWith("0x") ? value[2..] : value;
            ulong num = Convert.ToUInt64(simplified_value, 16);

            if (type.IsEnum)
            {
                var underlying = Enum.GetUnderlyingType(type);
                var numeric = Convert.ChangeType(num, underlying);
                return Enum.ToObject(type, numeric);
            }
            return Convert.ChangeType(num, type);
        }

        private static object ParseEnum(Type enumType, string value)
        {
            if (!enumType.IsEnum)
            {
                throw new ArgumentException("Target type is not an enum.");
            }
            return Enum.Parse(enumType, value, ignoreCase: true);
        }

        private static object ParseEnumFlags(Type enumType, string value)
        {
            if (!enumType.IsEnum)
            {
                throw new ArgumentException("Target type is not an enum.");
            }

            var parts = value.Split(new[] { '|', ',', ' ' }, StringSplitOptions.RemoveEmptyEntries);
            ulong result = 0;

            foreach (var part in parts)
            {
                var parsed = (Enum)Enum.Parse(enumType, part, ignoreCase: true);
                result |= Convert.ToUInt64(parsed);
            }

            return Enum.ToObject(enumType, result);
        }


        public static bool Parse<T1>(ref string[] properties, string template, out T1 arg1)
        {
            Type[] types = new[] { typeof(T1) };

            object[] outputs = new object[1];
            bool result = Parse(ref properties, template, outputs, types);
            arg1 = (T1)outputs[0]!;
            return result;
        }

        public static bool Parse<T1, T2>(ref string[] properties, string template, out T1 arg1, out T2 arg2)
        {
            Type[] types = new[] { typeof(T1), typeof(T2) };

            object[] outputs = new object[2];
            bool result = Parse(ref properties, template, outputs, types);
            arg1 = (T1)outputs[0]!;
            arg2 = (T2)outputs[1]!;
            return result;
        }

        public static bool Parse<T1, T2, T3>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3) };

            object[] outputs = new object[3];
            bool result = Parse(ref properties, template, outputs, types);
            arg1 = (T1)outputs[0]!;
            arg2 = (T2)outputs[1]!;
            arg3 = (T3)outputs[2]!;
            return result;
        }

        public static bool Parse<T1, T2, T3, T4>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4) };

            object[] outputs = new object[4];
            bool result = Parse(ref properties, template, outputs, types);
            arg1 = (T1)outputs[0]!;
            arg2 = (T2)outputs[1]!;
            arg3 = (T3)outputs[2]!;
            arg4 = (T4)outputs[3]!;
            return result;
        }

        public static bool Parse<T1, T2, T3, T4, T5>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4, out T5 arg5)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4), typeof(T5) };

            object[] outputs = new object[5];
            bool result = Parse(ref properties, template, outputs, types);
            arg1 = (T1)outputs[0]!;
            arg2 = (T2)outputs[1]!;
            arg3 = (T3)outputs[2]!;
            arg4 = (T4)outputs[3]!;
            arg5 = (T5)outputs[4]!;
            return result;
        }

        public static bool Parse<T1, T2, T3, T4, T5, T6>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4, out T5 arg5, out T6 arg6)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4), typeof(T5), typeof(T6) };

            object[] outputs = new object[6];
            bool result = Parse(ref properties, template, outputs, types);
            arg1 = (T1)outputs[0]!;
            arg2 = (T2)outputs[1]!;
            arg3 = (T3)outputs[2]!;
            arg4 = (T4)outputs[3]!;
            arg5 = (T5)outputs[4]!;
            arg6 = (T6)outputs[5]!;
            return result;
        }

        public static bool Parse<T1, T2, T3, T4, T5, T6, T7>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4, out T5 arg5, out T6 arg6, out T7 arg7)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4), typeof(T5), typeof(T6), typeof(T7) };

            object[] outputs = new object[7];
            bool result = Parse(ref properties, template, outputs, types);
            arg1 = (T1)outputs[0]!;
            arg2 = (T2)outputs[1]!;
            arg3 = (T3)outputs[2]!;
            arg4 = (T4)outputs[3]!;
            arg5 = (T5)outputs[4]!;
            arg6 = (T6)outputs[5]!;
            arg7 = (T7)outputs[6]!;

            return result;
        }

        public static bool Parse<T1, T2, T3, T4, T5, T6, T7, T8>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4, out T5 arg5, out T6 arg6, out T7 arg7, out T8 arg8)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4), typeof(T5), typeof(T6), typeof(T7), typeof(T8) };

            object[] outputs = new object[8];
            bool result = Parse(ref properties, template, outputs, types);
            arg1 = (T1)outputs[0]!;
            arg2 = (T2)outputs[1]!;
            arg3 = (T3)outputs[2]!;
            arg4 = (T4)outputs[3]!;
            arg5 = (T5)outputs[4]!;
            arg6 = (T6)outputs[5]!;
            arg7 = (T7)outputs[6]!;
            arg8 = (T8)outputs[7]!;

            return result;
        }
    }
}
