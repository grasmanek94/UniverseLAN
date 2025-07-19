using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetStatInt : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::GetStatInt";

        public string Name = "";
        public GalaxyID? UserID;
        public int Result;

        public GetStatInt(Base original) : base(original) { }

        /* Example contents:
            name: found_weapons
            userID: 0(ID_TYPE_UNASSIGNED)
            result: 1
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "name: {s}\nuserID: {gid}\nresult: {d}",
                out Name, out UserID, out Result))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
