namespace UniverseLanLogAnalyzer.LogEntries
{
    public class LoggerImplDestructor : Base
    {
        public static readonly string MATCH = "universelan::client::LoggerImpl::~LoggerImpl";

        public LoggerImplDestructor(Base original) : base(original) { }
    }
}
