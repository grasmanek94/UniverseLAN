using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnLobbyMemberStateChanged : Base
    {
        public static readonly string MATCH = "universelan::client::LobbyMemberStateListener::OnLobbyMemberStateChanged";
        
        public GalaxyID? LobbyID;
        public GalaxyID? MemberID;
        public LobbyMemberStateChange MemberStateChange;

        public OnLobbyMemberStateChanged(Base original) : base(original) { }

        /* Example contents:
            lobbyID: 58815465033870437(ID_TYPE_LOBBY)
            memberID: 46781908214750428(ID_TYPE_USER)
            memberStateChange: LOBBY_MEMBER_STATE_CHANGED_ENTERED
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "lobbyID: {gid}\nmemberID: {gid}\nmemberStateChange: {ef}",
                out LobbyID, out MemberID, out MemberStateChange))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
