namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetNumLobbyMembers : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::GetNumLobbyMembers";

        public GetNumLobbyMembers(Base original) : base(original)
        {
        }
    }
}
