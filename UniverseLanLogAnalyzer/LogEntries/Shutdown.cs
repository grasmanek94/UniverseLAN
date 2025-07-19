namespace UniverseLanLogAnalyzer.LogEntries
{
    public class Shutdown : Base
    {
        public static readonly string MATCH = "universelan::client::Shutdown";

        public Shutdown(Base original) : base(original) { }
    }
}
