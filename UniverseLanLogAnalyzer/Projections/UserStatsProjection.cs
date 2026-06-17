using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.LogEntries;

namespace UniverseLanLogAnalyzer.Projections
{
    public sealed class UserStatsProjection
    {
        public Dictionary<ulong, TimelineProjection<UserStatsSnapshot>> ByUserId { get; } = new();

        public TimelineProjection<UserStatsSnapshot> this[ulong userId] => ByUserId[userId];

        public static UserStatsProjection Build(LoggerStateMachine stateMachine)
        {
            UserStatsProjection projection = new UserStatsProjection();
            Dictionary<ulong, UserStatsSnapshot> current = new();
            GalaxyID? currentSelfUser = null;

            for (int i = 0; i < stateMachine.Entries.Count; ++i)
            {
                Base entry = stateMachine.Entries[i];

                if (entry is GetGalaxyID getGalaxyID && getGalaxyID.Result != null)
                {
                    currentSelfUser = getGalaxyID.Result;
                }

                switch (entry)
                {
                    case GetStatInt getStatInt when getStatInt.UserID != null:
                        {
                            UserStatsSnapshot snapshot = projection.GetOrCreateCurrent(current, getStatInt.UserID);

                            if (!snapshot.values.TryGetValue(getStatInt.Name, out int existing) || existing != getStatInt.Result)
                            {
                                snapshot.values[getStatInt.Name] = getStatInt.Result;
                                projection.GetOrCreateTimeline(snapshot.id.raw).AddSnapshot(i, snapshot.DeepClone());
                            }

                            break;
                        }

                    case SetStatInt setStatInt when currentSelfUser != null:
                        {
                            UserStatsSnapshot snapshot = projection.GetOrCreateCurrent(current, currentSelfUser);

                            if (!snapshot.values.TryGetValue(setStatInt.Name, out int existing) || existing != setStatInt.Value)
                            {
                                snapshot.values[setStatInt.Name] = setStatInt.Value;
                                projection.GetOrCreateTimeline(snapshot.id.raw).AddSnapshot(i, snapshot.DeepClone());
                            }

                            break;
                        }
                }
            }

            return projection;
        }

        private TimelineProjection<UserStatsSnapshot> GetOrCreateTimeline(ulong userId)
        {
            if (!ByUserId.TryGetValue(userId, out TimelineProjection<UserStatsSnapshot>? timeline))
            {
                timeline = new TimelineProjection<UserStatsSnapshot>();
                ByUserId.Add(userId, timeline);
            }

            return timeline;
        }

        private UserStatsSnapshot GetOrCreateCurrent(Dictionary<ulong, UserStatsSnapshot> current, GalaxyID userId)
        {
            if (!current.TryGetValue(userId.raw, out UserStatsSnapshot? snapshot))
            {
                snapshot = new UserStatsSnapshot();
                snapshot.id = userId.DeepClone();
                current.Add(userId.raw, snapshot);
            }

            return snapshot;
        }
    }
}
