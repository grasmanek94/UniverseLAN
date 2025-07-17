namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyDataUpdated : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyDataListener::OnLobbyDataUpdated";

        public OnLobbyDataUpdated(Base original) : base(original)
        {
        }
    }
}
