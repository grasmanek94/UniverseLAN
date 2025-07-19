using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class AddRequestLobbyListNumericalFilter : Base
    {
        public static readonly string MATCH = "universelan::client::MatchmakingImpl::AddRequestLobbyListNumericalFilter";

        public AddRequestLobbyListNumericalFilter(Base original) : base(original) { }

        public string KeyToMatch = "";
        public int ValueToMatch;
        public LobbyComparisonType ComparisonType;

        /* Example contents:
            keyToMatch: game-version
            valueToMatch: 187
            comparisonType: LOBBY_COMPARISON_TYPE_EQUAL
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "keyToMatch: {s}\nvalueToMatch: {d}\ncomparisonType: {e}",
                out KeyToMatch, out ValueToMatch, out ComparisonType))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
