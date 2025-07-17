namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnOperationalStateChanged : Base
    {
        public static readonly string MATCH = "universelan::client::OperationalStateChangeListener::OnOperationalStateChanged";

        public OnOperationalStateChanged(Base original) : base(original)
        {
        }
    }
}
