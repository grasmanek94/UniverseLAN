namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestLobbyList : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::RequestLobbyList";

        public RequestLobbyList(Base original) : base(original)
        {
        }
    }
}
