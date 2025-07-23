using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnPersonaDataChanged : Base
    {
        public static readonly string MATCH = "universelan::client::PersonaDataChangedListener::OnPersonaDataChanged";

        public GalaxyID? UserID;
        public PersonaStateChange StateChange;

        public OnPersonaDataChanged(Base original) : base(original) {}

        /* Example contents:
            userID: 46781906533578385(ID_TYPE_USER)
            personaStateChange: 0()
        */
        /* Example contents:
            userID: 46781908214750428(ID_TYPE_USER)
            personaStateChange: 3(PERSONA_CHANGE_NAME|PERSONA_CHANGE_AVATAR)
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "userID: {gid}\npersonaStateChange: {*}({ef})", 
                out UserID, out StateChange))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
