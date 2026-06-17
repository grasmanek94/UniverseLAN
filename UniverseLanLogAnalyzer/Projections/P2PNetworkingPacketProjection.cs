using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.LogEntries;

namespace UniverseLanLogAnalyzer.Projections
{
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
}
