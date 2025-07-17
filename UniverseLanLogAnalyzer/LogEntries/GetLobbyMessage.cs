namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetLobbyMessage : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetLobbyMessage";

        public GetLobbyMessage(Base original) : base(original)
        {
        }
    }
}
