using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.LogEntries;

namespace UniverseLanLogAnalyzer.Projections
{
    public sealed class UserAchievementsProjection
    {
        public Dictionary<ulong, TimelineProjection<UserAchievementsSnapshot>> ByUserId { get; } = new();

        public TimelineProjection<UserAchievementsSnapshot> this[ulong userId] => ByUserId[userId];

        public static UserAchievementsProjection Build(LoggerStateMachine stateMachine)
        {
            UserAchievementsProjection projection = new UserAchievementsProjection();
            Dictionary<ulong, UserAchievementsSnapshot> current = new();
            GalaxyID? currentSelfUser = null;

            for (int i = 0; i < stateMachine.Entries.Count; ++i)
            {
                Base entry = stateMachine.Entries[i];

                if (entry is GetGalaxyID getGalaxyID && getGalaxyID.Result != null)
                {
                    currentSelfUser = getGalaxyID.Result;
                }

                if (entry is not GetAchievement getAchievement)
                {
                    continue;
                }

                GalaxyID? userId = getAchievement.UserID ?? currentSelfUser;
                if (userId == null)
                {
                    continue;
                }

                UserAchievementsSnapshot snapshot = projection.GetOrCreateCurrent(current, userId);

                if (!snapshot.values.TryGetValue(getAchievement.Name, out AchievementState? existing)
                    || existing.unlocked != getAchievement.Unlocked
                    || existing.unlock_time != getAchievement.UnlockTime)
                {
                    snapshot.values[getAchievement.Name] = new AchievementState
                    {
                        unlocked = getAchievement.Unlocked,
                        unlock_time = getAchievement.UnlockTime,
                    };

                    projection.GetOrCreateTimeline(snapshot.id.raw).AddSnapshot(i, snapshot.DeepClone());
                }
            }

            return projection;
        }

        private TimelineProjection<UserAchievementsSnapshot> GetOrCreateTimeline(ulong userId)
        {
            if (!ByUserId.TryGetValue(userId, out TimelineProjection<UserAchievementsSnapshot>? timeline))
            {
                timeline = new TimelineProjection<UserAchievementsSnapshot>();
                ByUserId.Add(userId, timeline);
            }

            return timeline;
        }

        private UserAchievementsSnapshot GetOrCreateCurrent(Dictionary<ulong, UserAchievementsSnapshot> current, GalaxyID userId)
        {
            if (!current.TryGetValue(userId.raw, out UserAchievementsSnapshot? snapshot))
            {
                snapshot = new UserAchievementsSnapshot();
                snapshot.id = userId.DeepClone();
                current.Add(userId.raw, snapshot);
            }

            return snapshot;
        }
    }
}