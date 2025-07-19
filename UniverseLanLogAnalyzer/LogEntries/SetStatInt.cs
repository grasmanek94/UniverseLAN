using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class SetStatInt : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::SetStatInt";
        
        public string Name = "";
        public int Value;

        public SetStatInt(Base original) : base(original) { }

        /* Example contents:
            name: found_weapons
            value: 1
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "name: {s}\nvalue: {d}",
                out Name, out Value))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
