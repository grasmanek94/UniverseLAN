namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestUserInformation : Base
    {
        public static readonly string MATCH = "universelan::client::FriendsImpl::RequestUserInformation";

        public RequestUserInformation(Base original) : base(original)
        {
        }
    }
}
