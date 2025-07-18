using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnOperationalStateChanged : Base
    {
        public static readonly string MATCH = "universelan::client::OperationalStateChangeListener::OnOperationalStateChanged";

        public OperationalState State { get; set; }

        public OnOperationalStateChanged(Base original) : base(original)
        {
        }

        public override void PostInit()
        {
            if (!Parser.Arguments.ParseOperationalState(this, out var state))
            {
                throw new InterceptorEntryInitException(this, "OperationalState");
            }
            State = state;
        }
    }
}
