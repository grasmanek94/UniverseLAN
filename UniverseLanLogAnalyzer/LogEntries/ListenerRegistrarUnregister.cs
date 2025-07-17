namespace UniverseLanLogAnalyzer.LogEntries
{
    public class ListenerRegistrarUnregister : Base
    {
        public static readonly string MATCH = "universelan::client::ListenerRegistrarImpl::Unregister";

        public ListenerRegistrarUnregister(Base original) : base(original)
        {
        }
    }
}
