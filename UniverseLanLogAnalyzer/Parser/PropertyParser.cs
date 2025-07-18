using System.Text.RegularExpressions;

namespace UniverseLanLogAnalyzer.Parser
{
    public class Optional<T>
    {
        public T Value { get; set; } = default!;
        public bool Available { get; set; } = false;

        public static implicit operator T(Optional<T> opt) => opt.Value;
    }

    public static class PropertyParser
    {
        private static readonly Regex PlaceholderRegex = new(@"\{(d|x|e|ef|b|s)\}");

        public static bool Parse(ref string[] properties, string template, object[] outputs, Type[] types)
        {
            var lines = template.Split('\n');
            var matchedIndices = new HashSet<int>();
            var outputIndex = 0;

            foreach (var line in lines)
            {
                var placeholders = new List<string>();

                string pattern = line;
                pattern = PlaceholderRegex.Replace(pattern, match =>
                {
                    placeholders.Add((
                        match.Groups[1].Value
                    ));
                    return "(.+?)";
                });
                pattern = Regex.Escape(pattern);
                pattern = pattern.Replace(Regex.Escape("(.+?)"), "(.+?)");

                var regex = new Regex("^" + pattern + "$");

                bool matched = false;

                for (int i = 0; i < properties.Length; i++)
                {
                    if (matchedIndices.Contains(i))
                    {
                        continue;
                    }

                    var prop = properties[i];
                    var match = regex.Match(prop);
                    if (!match.Success)
                    {
                        continue;
                    }

                    matched = true;

                    for (int j = 0; j < placeholders.Count; j++)
                    {
                        var type = placeholders[j];
                        var value = match.Groups[j + 1].Value;

                        if (type == "*")
                        {
                            continue;
                        }

                        if (outputIndex >= outputs.Length)
                        {
                            throw new InvalidOperationException("Too few output parameters.");
                        }

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

                        /* Only remove successfully parsed properties */
                        matchedIndices.Add(i);

                        if (IsOptional(types[outputIndex]))
                        {
                            var innerType = types[outputIndex].GetGenericArguments()[0];
                            var optionalInstance = Activator.CreateInstance(types[outputIndex])!;
                            types[outputIndex].GetProperty("Value")!.SetValue(optionalInstance, Convert.ChangeType(parsed, innerType));
                            types[outputIndex].GetProperty("Available")!.SetValue(optionalInstance, true);
                            outputs[outputIndex] = optionalInstance;
                        }
                        else
                        {
                            outputs[outputIndex] = parsed;
                        }

                        outputIndex++;
                    }

                    break;
                }

                if (!matched)
                {
                    // Check if all placeholders are for Optional<T>
                    bool allOptional = true;
                    foreach (var _ in placeholders)
                    {
                        if (outputIndex >= types.Length) { continue; }
                        if (!IsOptional(types[outputIndex]))
                        {
                            allOptional = false;
                            break;
                        }
                        outputIndex++;
                    }

                    if (!allOptional)
                    {
                        return false;
                    }

                    continue; // skip optional line
                }
            }

            // Remove matched entries
            properties = properties.Where((_, i) => !matchedIndices.Contains(i)).ToArray();
            return true;
        }

        private static bool IsOptional(Type type)
        {
            return type.IsGenericType && type.GetGenericTypeDefinition() == typeof(Optional<>);
        }

        private static Type UnwrapOptional(Type type)
        {
            return IsOptional(type)
                ? type.GetGenericArguments()[0]
                : type;
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

        private static object ParseInternalNum(Type type, object value)
        {
            type = UnwrapOptional(type);

            if (type.IsEnum)
            {
                var underlying = Enum.GetUnderlyingType(type);
                var numeric = Convert.ChangeType(value, underlying);
                return Enum.ToObject(type, numeric);
            }
            return Convert.ChangeType(value, type);
        }

        private static object ParseNumber(Type type, string value)
        {
            return ParseInternalNum(type, value);
        }

        private static object ParseHex(Type type, string value)
        {
            string simplified_value = value.StartsWith("0x") ? value[2..] : value;
            ulong num = Convert.ToUInt64(simplified_value, 16);

            return ParseInternalNum(type, num);
        }

        private static object ParseEnum(Type enumType, string value)
        {
            enumType = UnwrapOptional(enumType);

            if (!enumType.IsEnum)
            {
                throw new ArgumentException("Target type is not an enum.");
            }
            return Enum.Parse(enumType, value, ignoreCase: true);
        }

        private static object ParseEnumFlags(Type enumType, string value)
        {
            enumType = UnwrapOptional(enumType);

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

        private static void AssignOrDefault<T>(bool success, out T arg, object[] outputs, int index)
        {
            arg = success ? (T)outputs[index]! : default!;
            if ((arg == null) && IsOptional(typeof(T)))
            {
                arg = (T)Activator.CreateInstance(typeof(T))!;
            }
        }

        public static bool Parse<T1>(ref string[] properties, string template, out T1 arg1)
        {
            Type[] types = new[] { typeof(T1) };

            object[] outputs = new object[1];
            bool result = Parse(ref properties, template, outputs, types);

            AssignOrDefault(result, out arg1, outputs, 0);

            return result;
        }

        public static bool Parse<T1, T2>(ref string[] properties, string template, out T1 arg1, out T2 arg2)
        {
            Type[] types = new[] { typeof(T1), typeof(T2) };

            object[] outputs = new object[2];
            bool result = Parse(ref properties, template, outputs, types);

            AssignOrDefault(result, out arg1, outputs, 0);
            AssignOrDefault(result, out arg2, outputs, 1);

            return result;
        }

        public static bool Parse<T1, T2, T3>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3) };

            object[] outputs = new object[3];
            bool result = Parse(ref properties, template, outputs, types);

            AssignOrDefault(result, out arg1, outputs, 0);
            AssignOrDefault(result, out arg2, outputs, 1);
            AssignOrDefault(result, out arg3, outputs, 2);

            return result;
        }

        public static bool Parse<T1, T2, T3, T4>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4) };

            object[] outputs = new object[4];
            bool result = Parse(ref properties, template, outputs, types);

            AssignOrDefault(result, out arg1, outputs, 0);
            AssignOrDefault(result, out arg2, outputs, 1);
            AssignOrDefault(result, out arg3, outputs, 2);
            AssignOrDefault(result, out arg4, outputs, 3);

            return result;
        }

        public static bool Parse<T1, T2, T3, T4, T5>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4, out T5 arg5)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4), typeof(T5) };

            object[] outputs = new object[5];
            bool result = Parse(ref properties, template, outputs, types);

            AssignOrDefault(result, out arg1, outputs, 0);
            AssignOrDefault(result, out arg2, outputs, 1);
            AssignOrDefault(result, out arg3, outputs, 2);
            AssignOrDefault(result, out arg4, outputs, 3);
            AssignOrDefault(result, out arg5, outputs, 4);

            return result;
        }

        public static bool Parse<T1, T2, T3, T4, T5, T6>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4, out T5 arg5, out T6 arg6)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4), typeof(T5), typeof(T6) };

            object[] outputs = new object[6];
            bool result = Parse(ref properties, template, outputs, types);

            AssignOrDefault(result, out arg1, outputs, 0);
            AssignOrDefault(result, out arg2, outputs, 1);
            AssignOrDefault(result, out arg3, outputs, 2);
            AssignOrDefault(result, out arg4, outputs, 3);
            AssignOrDefault(result, out arg5, outputs, 4);
            AssignOrDefault(result, out arg6, outputs, 5);

            return result;
        }

        public static bool Parse<T1, T2, T3, T4, T5, T6, T7>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4, out T5 arg5, out T6 arg6, out T7 arg7)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4), typeof(T5), typeof(T6), typeof(T7) };

            object[] outputs = new object[7];
            bool result = Parse(ref properties, template, outputs, types);

            AssignOrDefault(result, out arg1, outputs, 0);
            AssignOrDefault(result, out arg2, outputs, 1);
            AssignOrDefault(result, out arg3, outputs, 2);
            AssignOrDefault(result, out arg4, outputs, 3);
            AssignOrDefault(result, out arg5, outputs, 4);
            AssignOrDefault(result, out arg6, outputs, 5);
            AssignOrDefault(result, out arg7, outputs, 6);

            return result;
        }

        public static bool Parse<T1, T2, T3, T4, T5, T6, T7, T8>(ref string[] properties, string template, out T1 arg1, out T2 arg2, out T3 arg3, out T4 arg4, out T5 arg5, out T6 arg6, out T7 arg7, out T8 arg8)
        {
            Type[] types = new[] { typeof(T1), typeof(T2), typeof(T3), typeof(T4), typeof(T5), typeof(T6), typeof(T7), typeof(T8) };

            object[] outputs = new object[8];
            bool result = Parse(ref properties, template, outputs, types);

            AssignOrDefault(result, out arg1, outputs, 0);
            AssignOrDefault(result, out arg2, outputs, 1);
            AssignOrDefault(result, out arg3, outputs, 2);
            AssignOrDefault(result, out arg4, outputs, 3);
            AssignOrDefault(result, out arg5, outputs, 4);
            AssignOrDefault(result, out arg6, outputs, 5);
            AssignOrDefault(result, out arg7, outputs, 6);
            AssignOrDefault(result, out arg8, outputs, 7);

            return result;
        }
    }
}
