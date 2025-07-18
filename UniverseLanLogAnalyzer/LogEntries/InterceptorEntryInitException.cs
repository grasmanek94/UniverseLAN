namespace UniverseLanLogAnalyzer.LogEntries
{
    [Serializable]
    internal class InterceptorEntryInitException : Exception
    {
        public string What { get; private set; }
        public Base Entry { get; private set; }

        public InterceptorEntryInitException(Base entry, string what) 
            : base($"Initialization error for property '{what}' in object '{entry}'")
        {
            Entry = entry;
            What = what;
        }

        public InterceptorEntryInitException(Base entry, string what, Exception? innerException)
            : base($"Initialization error for property '{what}' in object '{entry}'", innerException)
        {
            Entry = entry;
            What = what;
        }
    }
}
