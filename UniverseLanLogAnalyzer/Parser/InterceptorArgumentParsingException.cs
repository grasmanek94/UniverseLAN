namespace UniverseLanLogAnalyzer.Parser
{
    [Serializable]
    internal class InterceptorArgumentParsingException : Exception
    {
        public string Property { get; private set; }
        public string What { get; private set; }

        public InterceptorArgumentParsingException(string what, string property) 
            : base($"Argument '{what}' parsing error occurred at property '{property}'")
        {
            Property = property;
            What = what;
        }

        public InterceptorArgumentParsingException(string what, string property, Exception? innerException)
            : base($"Argument '{what}' parsing error occurred at property '{property}'", innerException)
        {
            Property = property;
            What = what;
        }
    }
}
