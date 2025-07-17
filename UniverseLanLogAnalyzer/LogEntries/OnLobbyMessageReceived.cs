namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyMessageReceived : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyMessageListener::OnLobbyMessageReceived";

        public OnLobbyMessageReceived(Base original) : base(original)
        {
        }
    }
}
