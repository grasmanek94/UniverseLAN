namespace UniverseLanLogAnalyzer.Parser
{
    [Serializable]
    internal class InterceptorArgumentParsingException : Exception
    {
        public string Property { get; private set; }
        public string What { get; private set; }
        public LogEntries.Base Entry { get; private set; }

        public InterceptorArgumentParsingException(LogEntries.Base entry, string what) 
            : base($"Argument '{what}' parsing error occurred in object '{entry}'")
        {
            Entry = entry;
            What = what;
        }

        public InterceptorArgumentParsingException(LogEntries.Base entry, string what, Exception? innerException)
            : base($"Argument '{what}' parsing error occurred in object '{entry}'", innerException)
        {
            Entry = entry;
            What = what;
        }
    }
}
