using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetPersonaName : Base
    {
        public static readonly string MATCH = "universelan::client::FriendsImpl::GetPersonaName";

        public string Name = "";

        public GetPersonaName(Base original) : base(original) {}

        /* Example contents:
             result: TestGalaxyUserA
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "result: {s}", 
                out Name))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
