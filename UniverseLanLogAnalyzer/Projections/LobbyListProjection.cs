using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.LogEntries;

namespace UniverseLanLogAnalyzer.Projections
{
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
}
