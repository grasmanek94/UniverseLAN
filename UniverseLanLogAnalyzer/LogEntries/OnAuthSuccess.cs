namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnAuthSuccess : Base
    {
        public static readonly string MATCH = "universelan::client::AuthListener::OnAuthSuccess";

        public OnAuthSuccess(Base original) : base(original) { }
    }
}
