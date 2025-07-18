namespace UniverseLanLogAnalyzer.LogEntries
{
    public class ListenerRegistrarRegister : Base
    {
        public static readonly string MATCH = "universelan::client::ListenerRegistrarImpl::Register";

        public Galaxy.ListenerTypeInfo? Info { get; set; }

        public ListenerRegistrarRegister(Base original) : base(original)
        {
        }

        public override void PostInit()
        {
            Info = Parser.Arguments.ParseListenerRegister(this);
            if (Info == null)
            {
                throw new InterceptorEntryInitException(this, "ListenerTypeInfo");
            }
        }
    }
}
