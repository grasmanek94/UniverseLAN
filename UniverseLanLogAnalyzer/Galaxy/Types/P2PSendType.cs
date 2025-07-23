namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    public enum P2PSendType
    {
        P2P_SEND_UNRELIABLE = 0, ///< UDP-like packet transfer. The packet will be sent during the next call to ProcessData().
        P2P_SEND_RELIABLE = 1, ///< TCP-like packet transfer. The packet will be sent during the next call to ProcessData().
        P2P_SEND_UNRELIABLE_IMMEDIATE = 2, ///< UDP-like packet transfer. The packet will be sent instantly.
        P2P_SEND_RELIABLE_IMMEDIATE = 3 ///< TCP-like packet transfer. The packet will be sent instantly.
    };
}
