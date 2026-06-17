using System.ComponentModel;

namespace UniverseLanLogAnalyzer.Compare
{
    public enum ComparisonTargetType
    {
        Lobby,
        LobbyData,
        LobbyMemberData,
        P2PChannel,
        LobbyList,
        UserInformation,
        UserStats,
        UserAchievements
    }

    public sealed class ProjectionSelection
    {
        public ComparisonTargetType TargetType { get; set; }
        public ulong? LobbyId { get; set; }
        public ulong? UserId { get; set; }
        public int? Channel { get; set; }

        public string Describe()
        {
            return TargetType switch
            {
                ComparisonTargetType.Lobby => $"Lobby {LobbyId}",
                ComparisonTargetType.LobbyData => $"Lobby data for lobby {LobbyId}",
                ComparisonTargetType.LobbyMemberData => $"Lobby member data for user {UserId} in lobby {LobbyId}",
                ComparisonTargetType.P2PChannel => $"P2P channel {Channel}",
                ComparisonTargetType.LobbyList => "Lobby list",
                ComparisonTargetType.UserInformation => $"User information for user {UserId}",
                ComparisonTargetType.UserStats => $"User stats for user {UserId}",
                ComparisonTargetType.UserAchievements => $"User achievements for user {UserId}",
                _ => TargetType.ToString()
            };
        }
    }

    public enum ComparedChangeStatus
    {
        Same,
        Different,
        MissingOnLeft,
        MissingOnRight
    }

    public sealed class ComparedChange
    {
        public int Ordinal { get; init; }
        public ComparedChangeStatus Status { get; init; }
        public string StatusText => Status switch
        {
            ComparedChangeStatus.Same => "Same",
            ComparedChangeStatus.Different => "Different",
            ComparedChangeStatus.MissingOnLeft => "Missing left",
            ComparedChangeStatus.MissingOnRight => "Missing right",
            _ => Status.ToString()
        };

        public int? LeftTimePointIndex { get; init; }
        public int? RightTimePointIndex { get; init; }
        public string LeftShort { get; init; } = string.Empty;
        public string RightShort { get; init; } = string.Empty;
        public string LeftDetails { get; init; } = string.Empty;
        public string RightDetails { get; init; } = string.Empty;

        public string BuildDetailedText()
        {
            return string.Join(Environment.NewLine, new[]
            {
                $"Ordinal: {Ordinal}",
                $"Status: {StatusText}",
                $"Left timepoint index: {(LeftTimePointIndex.HasValue ? LeftTimePointIndex.Value.ToString() : "<missing>")}",
                $"Right timepoint index: {(RightTimePointIndex.HasValue ? RightTimePointIndex.Value.ToString() : "<missing>")}",
                string.Empty,
                "LEFT",
                LeftDetails,
                string.Empty,
                "RIGHT",
                RightDetails
            });
        }
    }

    public sealed class ComparisonResult
    {
        public string Summary { get; init; } = string.Empty;
        public BindingList<ComparedChange> Changes { get; init; } = new();
    }
}
