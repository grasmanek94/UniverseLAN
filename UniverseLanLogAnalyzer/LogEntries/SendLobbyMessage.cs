namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SendLobbyMessage : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::SendLobbyMessage";

        public SendLobbyMessage(Base original) : base(original)
        {
        }
    }
}
