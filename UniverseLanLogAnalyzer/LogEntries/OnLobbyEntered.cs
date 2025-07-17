namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyEntered : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyEnteredListener::OnLobbyEntered";

        public OnLobbyEntered(Base original) : base(original)
        {
        }
    }
}
