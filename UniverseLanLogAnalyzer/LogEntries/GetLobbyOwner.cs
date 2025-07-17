namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetLobbyOwner : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetLobbyOwner";

        public GetLobbyOwner(Base original) : base(original)
        {
        }
    }
}
