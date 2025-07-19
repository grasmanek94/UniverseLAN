namespace UniverseLanLogAnalyzer.LogEntries
{
    public class NetworkingImplWarning : Base
    {
        public static readonly string MATCH = "universelan::client::NetworkingImpl::NetworkingImpl::WARNING:";

        public NetworkingImplWarning(Base original) : base(original) { }
    }
}
