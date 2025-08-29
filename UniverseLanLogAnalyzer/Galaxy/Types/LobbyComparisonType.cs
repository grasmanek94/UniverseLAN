namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    public enum LobbyComparisonType
    {
        LOBBY_COMPARISON_TYPE_EQUAL = 0, ///< The lobby should have a property of a value that is equal to the one specified.
        LOBBY_COMPARISON_TYPE_NOT_EQUAL = 1, ///< The lobby should have a property of a value that is not equal to the one specified.
        LOBBY_COMPARISON_TYPE_GREATER = 2, ///< The lobby should have a property of a value that is greater than the one specified.
        LOBBY_COMPARISON_TYPE_GREATER_OR_EQUAL = 3, ///< The lobby should have a property of a value that is greater than or equal to the one specified.
        LOBBY_COMPARISON_TYPE_LOWER = 4, ///< The lobby should have a property of a value that is lower than the one specified.
        LOBBY_COMPARISON_TYPE_LOWER_OR_EQUAL = 5 ///< The lobby should have a property of a value that is lower than or equal to the one specified.
    };
}
