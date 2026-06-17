using MessagePack;
using System.Text;
using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.LogEntries;
using UniverseLanLogAnalyzer.Projections;
using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Projections
{
    public sealed class TimelineProjection<T> where T : class
    {
        private readonly SortedDictionary<int, T> _changes = new();

        public IReadOnlyDictionary<int, T> Changes => _changes;

        public bool HasSnapshots => _changes.Count > 0;

        public T? this[int timePointIndex] => GetAtOrBefore(timePointIndex);

        public T? GetAtOrBefore(int timePointIndex)
        {
            T? latest = null;

            foreach (var pair in _changes)
            {
                if (pair.Key > timePointIndex)
                {
                    break;
                }

                latest = pair.Value;
            }

            return latest;
        }

        public void AddSnapshot(int timePointIndex, T snapshot)
        {
            _changes[timePointIndex] = snapshot;
        }
    }

    public static class ProjectionClone
    {
        public static T Clone<T>(T value)
        {
            return CloneUtils.DeepClone(value);
        }
    }

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
                kv = new Dictionary<string, string?>(StringComparer.Ordinal);
                current.Add(lobbyId, kv);
            }

            if (kv.TryGetValue(key, out string? existing) && StringComparer.Ordinal.Equals(existing, value))
            {
                return;
            }

            kv[key] = value;
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

    public sealed class P2PNetworkingPacketProjection
    {
        public Dictionary<int, TimelineProjection<P2PPacketSnapshot>> ByChannel { get; } = new();

        public TimelineProjection<P2PPacketSnapshot> this[int channel] => ByChannel[channel];

        public static P2PNetworkingPacketProjection Build(LoggerStateMachine stateMachine)
        {
            P2PNetworkingPacketProjection projection = new P2PNetworkingPacketProjection();
            Dictionary<int, P2PPacketSnapshot> current = new();

            for (int i = 0; i < stateMachine.Entries.Count; ++i)
            {
                if (stateMachine.Entries[i] is not ReadP2PPacket_C readP2PPacket)
                {
                    continue;
                }

                if (!readP2PPacket.Result)
                {
                    continue;
                }

                if (!readP2PPacket.DataSize.Available || readP2PPacket.DataSize.Value <= 0)
                {
                    continue;
                }

                if (!readP2PPacket.From.Available || !readP2PPacket.DataHex.Available)
                {
                    continue;
                }

                P2PPacketSnapshot next = new P2PPacketSnapshot
                {
                    from = readP2PPacket.From.Value.DeepClone(),
                    data_hex = readP2PPacket.DataHex.Value ?? string.Empty
                };

                if (!current.TryGetValue(readP2PPacket.Channel, out P2PPacketSnapshot? previous)
                    || !AreEquivalent(previous, next))
                {
                    current[readP2PPacket.Channel] = next;
                    projection.GetOrCreateTimeline(readP2PPacket.Channel).AddSnapshot(i, next.DeepClone());
                }
            }

            return projection;
        }

        private TimelineProjection<P2PPacketSnapshot> GetOrCreateTimeline(int channel)
        {
            if (!ByChannel.TryGetValue(channel, out TimelineProjection<P2PPacketSnapshot>? timeline))
            {
                timeline = new TimelineProjection<P2PPacketSnapshot>();
                ByChannel.Add(channel, timeline);
            }

            return timeline;
        }

        private static bool AreEquivalent(P2PPacketSnapshot left, P2PPacketSnapshot right)
        {
            return left.from.raw == right.from.raw
                && StringComparer.Ordinal.Equals(left.data_hex, right.data_hex);
        }
    }


    public sealed class LobbyListProjection
    {
        public TimelineProjection<List<GalaxyID>> Timeline { get; } = new();

        public List<GalaxyID>? this[int timePointIndex] => Timeline[timePointIndex];

        public static LobbyListProjection Build(LoggerStateMachine stateMachine)
        {
            LobbyListProjection projection = new LobbyListProjection();
            List<GalaxyID> current = new();

            for (int i = 0; i < stateMachine.Entries.Count; ++i)
            {
                Base entry = stateMachine.Entries[i];

                switch (entry)
                {
                    case RequestLobbyList:
                        {
                            if (current.Count > 0 || !projection.Timeline.HasSnapshots)
                            {
                                current = new List<GalaxyID>();
                                projection.Timeline.AddSnapshot(i, ProjectionClone.Clone(current));
                            }

                            break;
                        }

                    case OnLobbyList onLobbyList when onLobbyList.LobbyCount == 0:
                        {
                            if (current.Count != 0 || !projection.Timeline.HasSnapshots)
                            {
                                current = new List<GalaxyID>();
                                projection.Timeline.AddSnapshot(i, ProjectionClone.Clone(current));
                            }

                            break;
                        }

                    case GetLobbyByIndex getLobbyByIndex when getLobbyByIndex.LobbyID != null:
                        {
                            bool changed = false;

                            while (current.Count <= getLobbyByIndex.Index)
                            {
                                current.Add(new GalaxyID(0));
                                changed = true;
                            }

                            if (current[getLobbyByIndex.Index].raw != getLobbyByIndex.LobbyID.raw)
                            {
                                current[getLobbyByIndex.Index] = getLobbyByIndex.LobbyID.DeepClone();
                                changed = true;
                            }

                            if (changed)
                            {
                                projection.Timeline.AddSnapshot(i, ProjectionClone.Clone(current));
                            }

                            break;
                        }
                }
            }

            return projection;
        }
    }

    [MessagePackObject]
    public class UserInformationSnapshot
    {
        [Key(0)]
        public GalaxyID id = new GalaxyID(0);

        [Key(1)]
        public string persona_name = string.Empty;

        [Key(2)]
        public PersonaStateChange persona_state_change = PersonaStateChange.PERSONA_CHANGE_NONE;

        [Key(3)]
        public AvatarType avatar_criteria = AvatarType.AVATAR_TYPE_NONE;

        [Key(4)]
        public int rich_presence_update_count = 0;

        public UserInformationSnapshot DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }

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

    [MessagePackObject]
    public class UserStatsSnapshot
    {
        [Key(0)]
        public GalaxyID id = new GalaxyID(0);

        [Key(1)]
        public Dictionary<string, int> values = new();

        public UserStatsSnapshot DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }

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

    [MessagePackObject]
    public class AchievementState
    {
        [Key(0)]
        public bool unlocked;

        [Key(1)]
        public uint unlock_time;
    }

    [MessagePackObject]
    public class UserAchievementsSnapshot
    {
        [Key(0)]
        public GalaxyID id = new GalaxyID(0);

        [Key(1)]
        public Dictionary<string, AchievementState> values = new();

        public UserAchievementsSnapshot DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }

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