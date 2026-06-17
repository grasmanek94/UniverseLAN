using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.LogEntries;

namespace UniverseLanLogAnalyzer.Projections
{
    public sealed class LobbyMemberDataProjection
    {
        public Dictionary<ulong, Dictionary<ulong, Dictionary<string, TimelineProjection<string?>>>> ByLobbyId { get; } = new();

        public TimelineProjection<string?> this[ulong lobbyId, ulong userId, string key] => ByLobbyId[lobbyId][userId][key];

        public static LobbyMemberDataProjection Build(LoggerStateMachine stateMachine)
        {
            LobbyMemberDataProjection projection = new LobbyMemberDataProjection();
            Dictionary<ulong, Dictionary<ulong, Dictionary<string, string?>>> current = new();
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
                    case GetLobbyMemberData getLobbyMemberData
                        when getLobbyMemberData.LobbyID != null && getLobbyMemberData.MemberID != null:
                        {
                            projection.ApplyValue(
                                current,
                                getLobbyMemberData.LobbyID.raw,
                                getLobbyMemberData.MemberID.raw,
                                getLobbyMemberData.Key,
                                getLobbyMemberData.Value,
                                i);
                            break;
                        }

                    case SetLobbyMemberData setLobbyMemberData
                        when setLobbyMemberData.LobbyID != null && currentSelfUser != null:
                        {
                            projection.ApplyValue(
                                current,
                                setLobbyMemberData.LobbyID.raw,
                                currentSelfUser.raw,
                                setLobbyMemberData.Key,
                                setLobbyMemberData.Value,
                                i);
                            break;
                        }
                }
            }

            return projection;
        }

        private void ApplyValue(
            Dictionary<ulong, Dictionary<ulong, Dictionary<string, string?>>> current,
            ulong lobbyId,
            ulong userId,
            string key,
            string? value,
            int timePoint)
        {
            if (!current.TryGetValue(lobbyId, out Dictionary<ulong, Dictionary<string, string?>>? users))
            {
                users = new Dictionary<ulong, Dictionary<string, string?>>();
                current.Add(lobbyId, users);
            }

            if (!users.TryGetValue(userId, out Dictionary<string, string?>? kv))
            {
                kv = new Dictionary<string, string?>(StringComparer.Ordinal);
                users.Add(userId, kv);
            }

            if (kv.TryGetValue(key, out string? existing) && StringComparer.Ordinal.Equals(existing, value))
            {
                return;
            }

            kv[key] = value;
            GetOrCreateTimeline(lobbyId, userId, key).AddSnapshot(timePoint, value);
        }

        private TimelineProjection<string?> GetOrCreateTimeline(ulong lobbyId, ulong userId, string key)
        {
            if (!ByLobbyId.TryGetValue(lobbyId, out Dictionary<ulong, Dictionary<string, TimelineProjection<string?>>>? users))
            {
                users = new Dictionary<ulong, Dictionary<string, TimelineProjection<string?>>>();
                ByLobbyId.Add(lobbyId, users);
            }

            if (!users.TryGetValue(userId, out Dictionary<string, TimelineProjection<string?>>? keys))
            {
                keys = new Dictionary<string, TimelineProjection<string?>>(StringComparer.Ordinal);
                users.Add(userId, keys);
            }

            if (!keys.TryGetValue(key, out TimelineProjection<string?>? timeline))
            {
                timeline = new TimelineProjection<string?>();
                keys.Add(key, timeline);
            }

            return timeline;
        }
    }
}
