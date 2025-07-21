using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class RequestUserInformation : Base
    {
        public static readonly string MATCH = "universelan::client::FriendsImpl::RequestUserInformation";
        
        public GalaxyID? UserID;
        public Optional<AvatarType> AvatartCriteria = new();
        public Optional<long> ListenerAddress = new();

        public RequestUserInformation(Base original) : base(original) {}

        /* Example contents:
            userID: 46781906533578385(ID_TYPE_USER)
            avatarCriteria: 0()
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "userID: {gid}\navatarCriteria: {*}({ef})\nlistener: {x}",
                out UserID, out AvatartCriteria, out ListenerAddress))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
