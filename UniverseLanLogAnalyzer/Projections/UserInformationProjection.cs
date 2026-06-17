using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.LogEntries;

namespace UniverseLanLogAnalyzer.Projections
{
    public sealed class UserInformationProjection
    {
        public Dictionary<ulong, TimelineProjection<UserInformationSnapshot>> ByUserId { get; } = new();

        public TimelineProjection<UserInformationSnapshot> this[ulong userId] => ByUserId[userId];

        public static UserInformationProjection Build(LoggerStateMachine stateMachine)
        {
            UserInformationProjection projection = new UserInformationProjection();
            Dictionary<ulong, UserInformationSnapshot> current = new();
            GalaxyID? currentSelfUser = null;

            for (int i = 0; i < stateMachine.Entries.Count; ++i)
            {
                Base entry = stateMachine.Entries[i];

                if (entry is GetGalaxyID getGalaxyID && getGalaxyID.Result != null)
                {
                    currentSelfUser = getGalaxyID.Result;

                    // Optional: seed once, but do NOT create duplicate timeline entries every time.
                    if (!current.ContainsKey(getGalaxyID.Result.raw))
                    {
                        UserInformationSnapshot initial = projection.GetOrCreateCurrent(current, getGalaxyID.Result);
                        projection.AddIfChanged(getGalaxyID.Result.raw, i, initial);
                    }

                    continue;
                }

                switch (entry)
                {
                    case RequestUserInformation requestUserInformation when requestUserInformation.UserID != null:
                        {
                            UserInformationSnapshot snapshot =
                                projection.GetOrCreateCurrent(current, requestUserInformation.UserID);

                            AvatarType next = requestUserInformation.AvatartCriteria.Available
                                ? requestUserInformation.AvatartCriteria.Value
                                : AvatarType.AVATAR_TYPE_NONE;

                            if (snapshot.avatar_criteria != next)
                            {
                                snapshot.avatar_criteria = next;
                                projection.AddIfChanged(snapshot.id.raw, i, snapshot);
                            }

                            break;
                        }

                    case OnPersonaDataChanged onPersonaDataChanged when onPersonaDataChanged.UserID != null:
                        {
                            UserInformationSnapshot snapshot =
                                projection.GetOrCreateCurrent(current, onPersonaDataChanged.UserID);

                            if (snapshot.persona_state_change != onPersonaDataChanged.StateChange)
                            {
                                snapshot.persona_state_change = onPersonaDataChanged.StateChange;
                                projection.AddIfChanged(snapshot.id.raw, i, snapshot);
                            }

                            break;
                        }

                    case OnRichPresenceUpdated onRichPresenceUpdated when onRichPresenceUpdated.UserID != null:
                        {
                            UserInformationSnapshot snapshot =
                                projection.GetOrCreateCurrent(current, onRichPresenceUpdated.UserID);

                            snapshot.rich_presence_update_count += 1;
                            projection.AddIfChanged(snapshot.id.raw, i, snapshot);
                            break;
                        }

                    case GetPersonaName getPersonaName when currentSelfUser != null:
                        {
                            UserInformationSnapshot snapshot =
                                projection.GetOrCreateCurrent(current, currentSelfUser);

                            if (!StringComparer.Ordinal.Equals(snapshot.persona_name, getPersonaName.Name))
                            {
                                snapshot.persona_name = getPersonaName.Name;
                                projection.AddIfChanged(snapshot.id.raw, i, snapshot);
                            }

                            break;
                        }
                }
            }

            return projection;
        }

        private void AddIfChanged(ulong userId, int timePointIndex, UserInformationSnapshot snapshot)
        {
            TimelineProjection<UserInformationSnapshot> timeline = GetOrCreateTimeline(userId);
            UserInformationSnapshot? previous = timeline[timePointIndex];

            if (previous != null && AreEquivalent(previous, snapshot))
            {
                return;
            }

            timeline.AddSnapshot(timePointIndex, snapshot.DeepClone());
        }

        private TimelineProjection<UserInformationSnapshot> GetOrCreateTimeline(ulong userId)
        {
            if (!ByUserId.TryGetValue(userId, out TimelineProjection<UserInformationSnapshot>? timeline))
            {
                timeline = new TimelineProjection<UserInformationSnapshot>();
                ByUserId.Add(userId, timeline);
            }

            return timeline;
        }

        private UserInformationSnapshot GetOrCreateCurrent(
            Dictionary<ulong, UserInformationSnapshot> current,
            GalaxyID userId)
        {
            if (!current.TryGetValue(userId.raw, out UserInformationSnapshot? snapshot))
            {
                snapshot = new UserInformationSnapshot();
                snapshot.id = userId.DeepClone();
                current.Add(userId.raw, snapshot);
            }

            return snapshot;
        }

        private static bool AreEquivalent(UserInformationSnapshot left, UserInformationSnapshot right)
        {
            return left.id.raw == right.id.raw
                && StringComparer.Ordinal.Equals(left.persona_name, right.persona_name)
                && left.persona_state_change == right.persona_state_change
                && left.avatar_criteria == right.avatar_criteria
                && left.rich_presence_update_count == right.rich_presence_update_count;
        }
    }
}
