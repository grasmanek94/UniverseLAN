namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestLobbyData : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::RequestLobbyData";

        public RequestLobbyData(Base original) : base(original)
        {
        }
    }
}
