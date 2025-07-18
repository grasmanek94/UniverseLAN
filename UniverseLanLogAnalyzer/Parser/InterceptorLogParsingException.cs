namespace UniverseLanLogAnalyzer.Parser
{
    [Serializable]
    internal class InterceptorLogParsingException : Exception
    {
        public string File { get; private set; }
        public int LineNumber { get; private set; }
        public string Line {  get; private set; }

        public InterceptorLogParsingException(string file, int line_number, string line) 
            : base($"Parsing error occurred at line {line_number} in file '{file}':\n{line}")
        {
            File = file;
            LineNumber = line_number;
            Line = line;
        }

        public InterceptorLogParsingException(string file, int line_number, string line, Exception? innerException)
            : base($"Parsing error occurred at line {line_number} in file '{file}':\n{line}", innerException)
        {
            File = file;
            LineNumber = line_number;
            Line = line;
        }
    }
}