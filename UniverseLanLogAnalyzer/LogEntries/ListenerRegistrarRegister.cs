namespace UniverseLanLogAnalyzer.LogEntries
{
    public class ListenerRegistrarRegister : Base
    {
        public static readonly string MATCH = "universelan::client::ListenerRegistrarImpl::Register";

        public Galaxy.ListenerTypeInfo Info { get; set; }

        public ListenerRegistrarRegister(Base original) : base(original)
        {
            var temp = Parser.Arguments.ParseListenerRegister(this);
            if (temp == null)
            {
                throw new InterceptorEntryInitException(this, "ListenerTypeInfo");
            }
            Info = temp;
        }
    }
}
