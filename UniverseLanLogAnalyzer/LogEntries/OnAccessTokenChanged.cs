namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnAccessTokenChanged : Base
    {
        public static readonly string MATCH = "universelan::client::AccessTokenListener::OnAccessTokenChanged";

        public OnAccessTokenChanged(Base original) : base(original) { }
    }
}
