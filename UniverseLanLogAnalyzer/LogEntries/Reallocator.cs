using System.Reflection;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public static class Reallocator
    {
        private static readonly Dictionary<string, Type> matchMap;

        static Reallocator()
        {
            matchMap = AppDomain.CurrentDomain.GetAssemblies()
                .SelectMany(a => a.GetTypes())
                .Where(t => t.IsSubclassOf(typeof(Base)) && !t.IsAbstract)
                .Select(t => new
                {
                    Type = t,
                    Match = t.GetField("MATCH", BindingFlags.Public | BindingFlags.Static)?.GetValue(null) as string
                })
                .Where(x => x.Match != null)
                .ToDictionary(x => x.Match!, x => x.Type);
        }

        public static Base ReMap(Base original)
        {
            if (matchMap.TryGetValue(original.Function, out var type))
            {
                return (Base)Activator.CreateInstance(type, original)!;
            }

            return original;
        }
    }
}
