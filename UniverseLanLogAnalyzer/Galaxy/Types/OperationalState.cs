namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    [Flags]
    public enum OperationalState
    {
        OPERATIONAL_STATE_NONE = 0x0000,
        OPERATIONAL_STATE_SIGNED_IN = 0x0001, ///< User signed in.
        OPERATIONAL_STATE_LOGGED_ON = 0x0002 ///< User logged on.
    };
}