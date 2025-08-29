namespace UniverseLanLogAnalyzer.Galaxy
{
    public class State
    {
        Dictionary<GalaxyID, Lobby> Lobbies;
        Dictionary<GalaxyID, User> Users;
        Dictionary<ulong, ListenerType> ActiveListenerTypes;
    }
}
