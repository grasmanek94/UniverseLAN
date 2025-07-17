namespace UniverseLanLogAnalyzer.LogEntries
{
    public class OnPersonaDataChanged : Base
    {
        public static readonly string MATCH = "universelan::client::PersonaDataChangedListener::OnPersonaDataChanged";

        public OnPersonaDataChanged(Base original) : base(original)
        {
        }
    }
}
