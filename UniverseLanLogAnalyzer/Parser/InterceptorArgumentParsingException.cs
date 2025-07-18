namespace UniverseLanLogAnalyzer.Parser
{
    [Serializable]
    internal class InterceptorArgumentParsingException : Exception
    {
        public string Property { get; private set; }
        public string What { get; private set; }
        public LogEntries.Base Entry { get; private set; }

        public InterceptorArgumentParsingException(LogEntries.Base entry, string what, string property) 
            : base($"Argument '{what}' parsing error occurred at property '{property}' in object '{entry}'")
        {
            Entry = entry;
            Property = property;
            What = what;
        }

        public InterceptorArgumentParsingException(LogEntries.Base entry, string what, string property, Exception? innerException)
            : base($"Argument '{what}' parsing error occurred at property '{property}' in object '{entry}'", innerException)
        {
            Entry = entry;
            Property = property;
            What = what;
        }
    }
}
