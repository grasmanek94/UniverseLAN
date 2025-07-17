namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyMemberStateChanged : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyMemberStateListener::OnLobbyMemberStateChanged";

        public OnLobbyMemberStateChanged(Base original) : base(original)
        {
        }
    }
}
