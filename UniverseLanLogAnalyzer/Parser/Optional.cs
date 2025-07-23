namespace UniverseLanLogAnalyzer.Parser
{
    public class Optional<T>
    {
        public T Value { get; set; } = default!;
        public bool Available { get; set; } = false;

        public static implicit operator T(Optional<T> opt) => opt.Value;

        public override string ToString() => Available ? Value?.ToString() ?? "null" : "<unknown>";
    }
}
