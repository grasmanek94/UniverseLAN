using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnOperationalStateChanged : Base
    {
        public static readonly string MATCH = "universelan::client::OperationalStateChangeListener::OnOperationalStateChanged";

        public OperationalState State;

        public OnOperationalStateChanged(Base original) : base(original) { }

        /* Example contents:
            operationalState: 3(OPERATIONAL_STATE_SIGNED_IN|OPERATIONAL_STATE_LOGGED_ON)
        */
        /* Example contents:
            operationalState: 0()
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "operationalState: {*}({ef})",
                out State))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
