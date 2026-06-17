using System.Diagnostics;
using System.Text;
using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Parser;
using UniverseLanLogAnalyzer.Projections;

namespace UniverseLanLogAnalyzer
{
    public partial class Form1 : Form
    {
        public static readonly string[] test_files = new string[]
        {
            @"D:\Backup\Desktop202603\SSBD-real-gog-log\Working-A.log",
            @"D:\Backup\Desktop202603\SSBD-real-gog-log\Working-B.log",
            @"D:\Backup\Desktop202603\SSBD-real-gog-log\NotWorking-A.log",
            @"D:\Backup\Desktop202603\SSBD-real-gog-log\NotWorking-B.log"
        };

        public Form1()
        {
            InitializeComponent();

            foreach (var file in test_files)
            {
                Debug.WriteLine("============================================================");
                Debug.WriteLine($"FILE: {file}");
                Debug.WriteLine("============================================================");

                LoggerStateMachine state_machine = new LoggerStateMachine();
                LogParser parser = new LogParser(file, state_machine);
                parser.Parse();

                LoggerStateMachineCleanup cleanup = new LoggerStateMachineCleanup(state_machine);
                cleanup.FoldRecurring();

                state_machine.PopulateStateMachine();

                ProjectionSuite projections = ProjectionSuite.Build(state_machine);

                Debug.WriteLine($"Entries after cleanup: {state_machine.Entries.Count}");
                Debug.WriteLine($"States captured: {state_machine.States.Count}");
                Debug.WriteLine("");

                DumpLobbyProjection(projections.Lobby);
                DumpLobbyDataProjection(projections.LobbyData);
                DumpLobbyMemberDataProjection(projections.LobbyMemberData);
                DumpP2PProjection(projections.P2PNetworkingPacket);
                DumpLobbyListProjection(projections.LobbyList);
                DumpUserInformationProjection(projections.UserInformation);
                DumpUserStatsProjection(projections.UserStats);
                DumpUserAchievementsProjection(projections.UserAchievements);

                Debug.WriteLine("");
                Debug.WriteLine("END OF FILE");
                Debug.WriteLine("");
            }
        }

        private static void DumpLobbyProjection(LobbyProjection projection)
        {
            Debug.WriteLine("---- LobbyProjection ----");

            foreach (var lobbyPair in projection.ByLobbyId.OrderBy(x => x.Key))
            {
                ulong lobbyId = lobbyPair.Key;
                TimelineProjection<Lobby> timeline = lobbyPair.Value;

                Debug.WriteLine($"Lobby {lobbyId}");

                foreach (var snapshotPair in timeline.Changes.OrderBy(x => x.Key))
                {
                    int time = snapshotPair.Key;
                    Lobby lobby = snapshotPair.Value;

                    Debug.WriteLine($"  [t={time}] Lobby snapshot");
                    DumpLobby(lobby, "    ");
                }

                Debug.WriteLine("");
            }
        }

        private static void DumpLobbyDataProjection(LobbyDataProjection projection)
        {
            Debug.WriteLine("---- LobbyDataProjection ----");

            foreach (var lobbyPair in projection.ByLobbyId.OrderBy(x => x.Key))
            {
                ulong lobbyId = lobbyPair.Key;
                Debug.WriteLine($"Lobby {lobbyId}");

                foreach (var keyPair in lobbyPair.Value.OrderBy(x => x.Key))
                {
                    string key = keyPair.Key;
                    TimelineProjection<string?> timeline = keyPair.Value;

                    Debug.WriteLine($"  Key '{key}'");

                    foreach (var snapshotPair in timeline.Changes.OrderBy(x => x.Key))
                    {
                        int time = snapshotPair.Key;
                        string? value = snapshotPair.Value;

                        Debug.WriteLine($"    [t={time}] value={(value ?? "<null>")}");
                    }
                }

                Debug.WriteLine("");
            }
        }

        private static void DumpLobbyMemberDataProjection(LobbyMemberDataProjection projection)
        {
            Debug.WriteLine("---- LobbyMemberDataProjection ----");

            foreach (var lobbyPair in projection.ByLobbyId.OrderBy(x => x.Key))
            {
                ulong lobbyId = lobbyPair.Key;
                Debug.WriteLine($"Lobby {lobbyId}");

                foreach (var userPair in lobbyPair.Value.OrderBy(x => x.Key))
                {
                    ulong userId = userPair.Key;
                    Debug.WriteLine($"  User {userId}");

                    foreach (var keyPair in userPair.Value.OrderBy(x => x.Key))
                    {
                        string key = keyPair.Key;
                        TimelineProjection<string?> timeline = keyPair.Value;

                        Debug.WriteLine($"    Key '{key}'");

                        foreach (var snapshotPair in timeline.Changes.OrderBy(x => x.Key))
                        {
                            int time = snapshotPair.Key;
                            string? value = snapshotPair.Value;

                            Debug.WriteLine($"      [t={time}] value={(value ?? "<null>")}");
                        }
                    }
                }

                Debug.WriteLine("");
            }
        }

        private static void DumpP2PProjection(P2PNetworkingPacketProjection projection)
        {
            Debug.WriteLine("---- P2PNetworkingPacketProjection ----");

            foreach (var pair in projection.ByChannel.OrderBy(x => x.Key))
            {
                int channel = pair.Key;
                TimelineProjection<P2PPacketSnapshot> timeline = pair.Value;

                Debug.WriteLine($"Channel {channel}");

                foreach (var snapshotPair in timeline.Changes.OrderBy(x => x.Key))
                {
                    int time = snapshotPair.Key;
                    P2PPacketSnapshot snapshot = snapshotPair.Value;

                    Debug.WriteLine(
                        $"  [t={time}] from={FormatGalaxyID(snapshot.from)}, data_hex={snapshot.data_hex}");
                }

                Debug.WriteLine("");
            }
        }

        private static void DumpLobbyListProjection(LobbyListProjection projection)
        {
            Debug.WriteLine("---- LobbyListProjection ----");

            foreach (var snapshotPair in projection.Timeline.Changes.OrderBy(x => x.Key))
            {
                int time = snapshotPair.Key;
                List<GalaxyID> lobbies = snapshotPair.Value;

                Debug.WriteLine($"  [t={time}] Lobby list snapshot");

                if (lobbies.Count == 0)
                {
                    Debug.WriteLine("    <empty>");
                    continue;
                }

                for (int i = 0; i < lobbies.Count; ++i)
                {
                    Debug.WriteLine($"    [{i}] {FormatGalaxyID(lobbies[i])}");
                }
            }

            Debug.WriteLine("");
        }

        private static void DumpUserInformationProjection(UserInformationProjection projection)
        {
            Debug.WriteLine("---- UserInformationProjection ----");

            foreach (var pair in projection.ByUserId.OrderBy(x => x.Key))
            {
                ulong userId = pair.Key;
                TimelineProjection<UserInformationSnapshot> timeline = pair.Value;

                Debug.WriteLine($"User {userId}");

                foreach (var snapshotPair in timeline.Changes.OrderBy(x => x.Key))
                {
                    int time = snapshotPair.Key;
                    UserInformationSnapshot snapshot = snapshotPair.Value;

                    Debug.WriteLine(
                        $"  [t={time}] id={FormatGalaxyID(snapshot.id)}, " +
                        $"persona_name={snapshot.persona_name}, " +
                        $"persona_state_change={snapshot.persona_state_change}, " +
                        $"avatar_criteria={snapshot.avatar_criteria}, " +
                        $"rich_presence_update_count={snapshot.rich_presence_update_count}");
                }

                Debug.WriteLine("");
            }
        }

        private static void DumpUserStatsProjection(UserStatsProjection projection)
        {
            Debug.WriteLine("---- UserStatsProjection ----");

            foreach (var pair in projection.ByUserId.OrderBy(x => x.Key))
            {
                ulong userId = pair.Key;
                TimelineProjection<UserStatsSnapshot> timeline = pair.Value;

                Debug.WriteLine($"User {userId}");

                foreach (var snapshotPair in timeline.Changes.OrderBy(x => x.Key))
                {
                    int time = snapshotPair.Key;
                    UserStatsSnapshot snapshot = snapshotPair.Value;

                    Debug.WriteLine($"  [t={time}] Stats snapshot for {FormatGalaxyID(snapshot.id)}");

                    if (snapshot.values.Count == 0)
                    {
                        Debug.WriteLine("    <empty>");
                        continue;
                    }

                    foreach (var stat in snapshot.values.OrderBy(x => x.Key))
                    {
                        Debug.WriteLine($"    {stat.Key} = {stat.Value}");
                    }
                }

                Debug.WriteLine("");
            }
        }

        private static void DumpUserAchievementsProjection(UserAchievementsProjection projection)
        {
            Debug.WriteLine("---- UserAchievementsProjection ----");

            foreach (var pair in projection.ByUserId.OrderBy(x => x.Key))
            {
                ulong userId = pair.Key;
                TimelineProjection<UserAchievementsSnapshot> timeline = pair.Value;

                Debug.WriteLine($"User {userId}");

                foreach (var snapshotPair in timeline.Changes.OrderBy(x => x.Key))
                {
                    int time = snapshotPair.Key;
                    UserAchievementsSnapshot snapshot = snapshotPair.Value;

                    Debug.WriteLine($"  [t={time}] Achievements snapshot for {FormatGalaxyID(snapshot.id)}");

                    if (snapshot.values.Count == 0)
                    {
                        Debug.WriteLine("    <empty>");
                        continue;
                    }

                    foreach (var achievement in snapshot.values.OrderBy(x => x.Key))
                    {
                        Debug.WriteLine(
                            $"    {achievement.Key} => unlocked={achievement.Value.unlocked}, unlock_time={achievement.Value.unlock_time}");
                    }
                }

                Debug.WriteLine("");
            }
        }

        private static void DumpLobby(Lobby lobby, string indent)
        {
            Debug.WriteLine($"{indent}id={FormatGalaxyID(lobby.id)}");
            Debug.WriteLine($"{indent}owner_id={FormatGalaxyID(lobby.owner_id)}");
            Debug.WriteLine($"{indent}joinable={lobby.joinable}");
            Debug.WriteLine($"{indent}max_members={lobby.max_members}");
            Debug.WriteLine($"{indent}topology_type={lobby.topology_type}");
            Debug.WriteLine($"{indent}type={lobby.type}");
            Debug.WriteLine($"{indent}created_listener=0x{lobby.created_listener:X}");
            Debug.WriteLine($"{indent}entered_listener=0x{lobby.entered_listener:X}");

            Debug.WriteLine($"{indent}kv_store:");
            if (lobby.kv_store.Count == 0)
            {
                Debug.WriteLine($"{indent}  <empty>");
            }
            else
            {
                foreach (var kv in lobby.kv_store.OrderBy(x => x.Key))
                {
                    Debug.WriteLine($"{indent}  {kv.Key} = {DecodeBytes(kv.Value)}");
                }
            }

            Debug.WriteLine($"{indent}user_kv_store:");
            if (lobby.user_kv_store.Count == 0)
            {
                Debug.WriteLine($"{indent}  <empty>");
            }
            else
            {
                foreach (var userKv in lobby.user_kv_store.OrderBy(x => x.Key.raw))
                {
                    Debug.WriteLine($"{indent}  user {FormatGalaxyID(userKv.Key)}");

                    if (userKv.Value.Count == 0)
                    {
                        Debug.WriteLine($"{indent}    <empty>");
                        continue;
                    }

                    foreach (var kv in userKv.Value.OrderBy(x => x.Key))
                    {
                        Debug.WriteLine($"{indent}    {kv.Key} = {DecodeBytes(kv.Value)}");
                    }
                }
            }

            Debug.WriteLine($"{indent}messages:");
            if (lobby.messages.Count == 0)
            {
                Debug.WriteLine($"{indent}  <empty>");
            }
            else
            {
                foreach (var msg in lobby.messages.OrderBy(x => x.Key))
                {
                    Debug.WriteLine($"{indent}  [{msg.Key}] = {DecodeBytes(msg.Value)}");
                }
            }
        }

        private static string DecodeBytes(byte[] data)
        {
            try
            {
                return Encoding.UTF8.GetString(data);
            }
            catch
            {
                return BitConverter.ToString(data);
            }
        }

        private static string FormatGalaxyID(GalaxyID? id)
        {
            if (id == null)
            {
                return "<null>";
            }

            return $"{id.GetID()}({id.GetIDType()})";
        }
    }
}
