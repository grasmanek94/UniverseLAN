namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyCreated : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyCreatedListener::OnLobbyCreated";

        public OnLobbyCreated(Base original) : base(original)
        {
        }
    }
}
