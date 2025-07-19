namespace UniverseLanLogAnalyzer.Parser
{
    [Serializable]
    internal class InterceptorPropertyParsingException : Exception
    {
        public LogEntries.Base Entry { get; private set; }

        public InterceptorPropertyParsingException(LogEntries.Base entry) 
            : base($"Parsing error occurred in object '{entry}'")
        {
            Entry = entry;
        }

        public InterceptorPropertyParsingException(LogEntries.Base entry, string what, Exception? innerException)
            : base($"Parsing error occurred in object '{entry}'", innerException)
        {
            Entry = entry;
        }
    }
}
