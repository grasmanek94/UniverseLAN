using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.Projections
{
    public sealed class ProjectionSuite
    {
        public LobbyProjection Lobby { get; }
        public LobbyDataProjection LobbyData { get; }
        public LobbyMemberDataProjection LobbyMemberData { get; }
        public P2PNetworkingPacketProjection P2PNetworkingPacket { get; }
        public LobbyListProjection LobbyList { get; }
        public UserInformationProjection UserInformation { get; }
        public UserStatsProjection UserStats { get; }
        public UserAchievementsProjection UserAchievements { get; }

        private ProjectionSuite(
            LobbyProjection lobby,
            LobbyDataProjection lobbyData,
            LobbyMemberDataProjection lobbyMemberData,
            P2PNetworkingPacketProjection p2pNetworkingPacket,
            LobbyListProjection lobbyList,
            UserInformationProjection userInformation,
            UserStatsProjection userStats,
            UserAchievementsProjection userAchievements)
        {
            Lobby = lobby;
            LobbyData = lobbyData;
            LobbyMemberData = lobbyMemberData;
            P2PNetworkingPacket = p2pNetworkingPacket;
            LobbyList = lobbyList;
            UserInformation = userInformation;
            UserStats = userStats;
            UserAchievements = userAchievements;
        }

        public static ProjectionSuite Build(LoggerStateMachine stateMachine)
        {
            return new ProjectionSuite(
                LobbyProjection.Build(stateMachine),
                LobbyDataProjection.Build(stateMachine),
                LobbyMemberDataProjection.Build(stateMachine),
                P2PNetworkingPacketProjection.Build(stateMachine),
                LobbyListProjection.Build(stateMachine),
                UserInformationProjection.Build(stateMachine),
                UserStatsProjection.Build(stateMachine),
                UserAchievementsProjection.Build(stateMachine));
        }
    }
}
