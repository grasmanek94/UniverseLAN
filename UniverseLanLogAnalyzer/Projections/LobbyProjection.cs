using System.Text;
using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.LogEntries;

namespace UniverseLanLogAnalyzer.Projections
{
    public sealed class LobbyProjection
    {
        public Dictionary<ulong, TimelineProjection<Lobby>> ByLobbyId { get; } = new();

        public TimelineProjection<Lobby> this[ulong lobbyId] => ByLobbyId[lobbyId];

        public static LobbyProjection Build(LoggerStateMachine stateMachine)
        {
            LobbyProjection projection = new LobbyProjection();
            Dictionary<ulong, Lobby> current = new();

            for (int i = 0; i < stateMachine.Entries.Count; ++i)
            {
                Base entry = stateMachine.Entries[i];

                switch (entry)
                {
                    case OnLobbyCreated onLobbyCreated
                        when onLobbyCreated.Result == LobbyCreateResult.LOBBY_CREATE_RESULT_SUCCESS
                        && onLobbyCreated.LobbyID != null:
                        {
                            ulong lobbyId = onLobbyCreated.LobbyID.raw;

                            if (!current.ContainsKey(lobbyId))
                            {
                                Lobby lobby = new Lobby();
                                lobby.id = onLobbyCreated.LobbyID.DeepClone();
                                current[lobbyId] = lobby;
                                projection.GetOrCreateTimeline(lobbyId).AddSnapshot(i, lobby.DeepClone());
                            }

                            break;
                        }

                    case GetLobbyData getLobbyData when getLobbyData.LobbyID != null:
                        {
                            Lobby lobby = projection.GetOrCreateLobby(current, getLobbyData.LobbyID);
                            if (SetLobbyKeyValue(lobby.kv_store, getLobbyData.Key, getLobbyData.Value))
                            {
                                projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                            }
                            break;
                        }

                    case SetLobbyData setLobbyData when setLobbyData.LobbyID != null && setLobbyData.Result:
                        {
                            Lobby lobby = projection.GetOrCreateLobby(current, setLobbyData.LobbyID);
                            if (SetLobbyKeyValue(lobby.kv_store, setLobbyData.Key, setLobbyData.Value))
                            {
                                projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                            }
                            break;
                        }

                    case DeleteLobbyData deleteLobbyData when deleteLobbyData.LobbyID != null && deleteLobbyData.Result:
                        {
                            Lobby lobby = projection.GetOrCreateLobby(current, deleteLobbyData.LobbyID);
                            if (lobby.kv_store.Remove(deleteLobbyData.Key))
                            {
                                projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                            }
                            break;
                        }

                    case GetLobbyOwner getLobbyOwner when getLobbyOwner.LobbyID != null && getLobbyOwner.OwnerID != null:
                        {
                            Lobby lobby = projection.GetOrCreateLobby(current, getLobbyOwner.LobbyID);
                            if (lobby.owner_id == null || lobby.owner_id.raw != getLobbyOwner.OwnerID.raw)
                            {
                                lobby.owner_id = getLobbyOwner.OwnerID.DeepClone();
                                projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                            }
                            break;
                        }

                    case SetLobbyJoinable setLobbyJoinable when setLobbyJoinable.LobbyID != null && setLobbyJoinable.Result:
                        {
                            Lobby lobby = projection.GetOrCreateLobby(current, setLobbyJoinable.LobbyID);
                            if (lobby.joinable != setLobbyJoinable.Joinable)
                            {
                                lobby.joinable = setLobbyJoinable.Joinable;
                                projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                            }
                            break;
                        }

                    case GetMaxNumLobbyMembers getMaxNumLobbyMembers when getMaxNumLobbyMembers.LobbyID != null:
                        {
                            Lobby lobby = projection.GetOrCreateLobby(current, getMaxNumLobbyMembers.LobbyID);
                            if (lobby.max_members != (uint)getMaxNumLobbyMembers.MaxNumLobbyMembers)
                            {
                                lobby.max_members = (uint)getMaxNumLobbyMembers.MaxNumLobbyMembers;
                                projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                            }
                            break;
                        }

                    case SetMaxNumLobbyMembers setMaxNumLobbyMembers when setMaxNumLobbyMembers.LobbyID != null && setMaxNumLobbyMembers.Result:
                        {
                            Lobby lobby = projection.GetOrCreateLobby(current, setMaxNumLobbyMembers.LobbyID);
                            if (lobby.max_members != (uint)setMaxNumLobbyMembers.MaxNumLobbyMembers)
                            {
                                lobby.max_members = (uint)setMaxNumLobbyMembers.MaxNumLobbyMembers;
                                projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                            }
                            break;
                        }

                    case GetLobbyMemberData getLobbyMemberData when getLobbyMemberData.LobbyID != null && getLobbyMemberData.MemberID != null:
                        {
                            Lobby lobby = projection.GetOrCreateLobby(current, getLobbyMemberData.LobbyID);
                            if (SetLobbyMemberKeyValue(lobby.user_kv_store, getLobbyMemberData.MemberID, getLobbyMemberData.Key, getLobbyMemberData.Value))
                            {
                                projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                            }
                            break;
                        }

                    case SetLobbyMemberData setLobbyMemberData when setLobbyMemberData.LobbyID != null:
                        {
                            // handled below via latest self user inference
                            break;
                        }
                }
            }

            // second pass only for SetLobbyMemberData self-user inference
            GalaxyID? currentSelfUser = null;
            for (int i = 0; i < stateMachine.Entries.Count; ++i)
            {
                Base entry = stateMachine.Entries[i];

                if (entry is GetGalaxyID getGalaxyID && getGalaxyID.Result != null)
                {
                    currentSelfUser = getGalaxyID.Result;
                    continue;
                }

                if (entry is SetLobbyMemberData setLobbyMemberData && setLobbyMemberData.LobbyID != null && currentSelfUser != null)
                {
                    Lobby lobby = projection.GetOrCreateLobby(current, setLobbyMemberData.LobbyID);
                    if (SetLobbyMemberKeyValue(lobby.user_kv_store, currentSelfUser, setLobbyMemberData.Key, setLobbyMemberData.Value))
                    {
                        projection.GetOrCreateTimeline(lobby.id.raw).AddSnapshot(i, lobby.DeepClone());
                    }
                }
            }

            return projection;
        }

        private TimelineProjection<Lobby> GetOrCreateTimeline(ulong lobbyId)
        {
            if (!ByLobbyId.TryGetValue(lobbyId, out TimelineProjection<Lobby>? timeline))
            {
                timeline = new TimelineProjection<Lobby>();
                ByLobbyId.Add(lobbyId, timeline);
            }

            return timeline;
        }

        private Lobby GetOrCreateLobby(Dictionary<ulong, Lobby> current, GalaxyID lobbyId)
        {
            if (!current.TryGetValue(lobbyId.raw, out Lobby? lobby))
            {
                lobby = new Lobby();
                lobby.id = lobbyId.DeepClone();
                current.Add(lobbyId.raw, lobby);
            }

            return lobby;
        }

        private static bool SetLobbyKeyValue(Dictionary<string, byte[]> store, string key, string value)
        {
            byte[] bytes = Encoding.UTF8.GetBytes(value ?? string.Empty);
            if (store.TryGetValue(key, out byte[]? existing) && existing.SequenceEqual(bytes))
            {
                return false;
            }

            store[key] = bytes;
            return true;
        }

        private static bool SetLobbyMemberKeyValue(
            Dictionary<GalaxyID, Dictionary<string, byte[]>> userStore,
            GalaxyID userId,
            string key,
            string value)
        {
            GalaxyID? existingUserId = userStore.Keys.FirstOrDefault(x => x.raw == userId.raw);
            if (existingUserId == null)
            {
                existingUserId = userId.DeepClone();
                userStore[existingUserId] = new Dictionary<string, byte[]>();
            }

            Dictionary<string, byte[]> kvStore = userStore[existingUserId];
            byte[] bytes = Encoding.UTF8.GetBytes(value ?? string.Empty);

            if (kvStore.TryGetValue(key, out byte[]? existing) && existing.SequenceEqual(bytes))
            {
                return false;
            }

            kvStore[key] = bytes;
            return true;
        }
    }
}
