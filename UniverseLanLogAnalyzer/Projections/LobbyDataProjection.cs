using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.LogEntries;

namespace UniverseLanLogAnalyzer.Projections
{
    public sealed class LobbyDataProjection
    {
        public Dictionary<ulong, Dictionary<string, TimelineProjection<string?>>> ByLobbyId { get; } = new();

        public TimelineProjection<string?> this[ulong lobbyId, string key] => ByLobbyId[lobbyId][key];

        public static LobbyDataProjection Build(LoggerStateMachine stateMachine)
        {
            LobbyDataProjection projection = new LobbyDataProjection();
            Dictionary<ulong, Dictionary<string, string?>> current = new();

            for (int i = 0; i < stateMachine.Entries.Count; ++i)
            {
                Base entry = stateMachine.Entries[i];

                switch (entry)
                {
                    case GetLobbyData getLobbyData when getLobbyData.LobbyID != null:
                        {
                            ulong lobbyId = getLobbyData.LobbyID.raw;
                            projection.ApplyValue(current, lobbyId, getLobbyData.Key, getLobbyData.Value, i);
                            break;
                        }

                    case SetLobbyData setLobbyData when setLobbyData.LobbyID != null && setLobbyData.Result:
                        {
                            ulong lobbyId = setLobbyData.LobbyID.raw;
                            projection.ApplyValue(current, lobbyId, setLobbyData.Key, setLobbyData.Value, i);
                            break;
                        }

                    case DeleteLobbyData deleteLobbyData when deleteLobbyData.LobbyID != null && deleteLobbyData.Result:
                        {
                            ulong lobbyId = deleteLobbyData.LobbyID.raw;
                            projection.ApplyValue(current, lobbyId, deleteLobbyData.Key, null, i);
                            break;
                        }
                }
            }

            return projection;
        }

        private void ApplyValue(
            Dictionary<ulong, Dictionary<string, string?>> current,
            ulong lobbyId,
            string key,
            string? value,
            int timePoint)
        {
            if (!current.TryGetValue(lobbyId, out Dictionary<string, string?>? kv))
            {
                // Ignore no-op deletions for lobbies we have never observed state for.
                if (value == null)
                {
                    return;
                }

                kv = new Dictionary<string, string?>(StringComparer.Ordinal);
                current.Add(lobbyId, kv);
            }

            if (!kv.TryGetValue(key, out string? existing))
            {
                // Ignore deleting a value that does not exist; it is not a state change.
                if (value == null)
                {
                    return;
                }

                kv[key] = value;
                GetOrCreateTimeline(lobbyId, key).AddSnapshot(timePoint, value);
                return;
            }

            if (StringComparer.Ordinal.Equals(existing, value))
            {
                return;
            }

            if (value == null)
            {
                kv.Remove(key);
            }
            else
            {
                kv[key] = value;
            }

            GetOrCreateTimeline(lobbyId, key).AddSnapshot(timePoint, value);
        }

        private TimelineProjection<string?> GetOrCreateTimeline(ulong lobbyId, string key)
        {
            if (!ByLobbyId.TryGetValue(lobbyId, out Dictionary<string, TimelineProjection<string?>>? keys))
            {
                keys = new Dictionary<string, TimelineProjection<string?>>(StringComparer.Ordinal);
                ByLobbyId.Add(lobbyId, keys);
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
