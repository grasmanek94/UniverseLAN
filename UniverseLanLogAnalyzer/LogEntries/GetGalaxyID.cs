using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetGalaxyID : Base
    {
        public static readonly string MATCH = "universelan::client::UserImpl::GetGalaxyID";

        public GalaxyID? Result;

        public GetGalaxyID(Base original) : base(original)
        {
            CollapseRepeat = true;
        }

        /* Example contents:
            result: 46781906533578385(ID_TYPE_USER)
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties, 
                "result: {gid}", 
                out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
