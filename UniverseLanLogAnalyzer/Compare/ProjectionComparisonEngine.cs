using System.ComponentModel;
using System.Globalization;
using System.Text;
using System.Text.Json;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Projections;

namespace UniverseLanLogAnalyzer.Compare
{
    public static class ProjectionComparisonEngine
    {
        private static readonly JsonSerializerOptions JsonOptions = new()
        {
            WriteIndented = true
        };

        public static ComparisonResult Compare(
            ParsedLogDocument leftDocument,
            ProjectionSelection leftSelection,
            ParsedLogDocument rightDocument,
            ProjectionSelection rightSelection)
        {
            List<NormalizedTransition> leftTransitions = ExtractTransitions(leftDocument, leftSelection);
            List<NormalizedTransition> rightTransitions = ExtractTransitions(rightDocument, rightSelection);

            int max = Math.Max(leftTransitions.Count, rightTransitions.Count);
            BindingList<ComparedChange> rows = new BindingList<ComparedChange>();
            int sameCount = 0;
            int differentCount = 0;
            int missingLeftCount = 0;
            int missingRightCount = 0;

            for (int i = 0; i < max; ++i)
            {
                NormalizedTransition? left = i < leftTransitions.Count ? leftTransitions[i] : null;
                NormalizedTransition? right = i < rightTransitions.Count ? rightTransitions[i] : null;

                ComparedChangeStatus status;
                if (left == null)
                {
                    status = ComparedChangeStatus.MissingOnLeft;
                    missingLeftCount++;
                }
                else if (right == null)
                {
                    status = ComparedChangeStatus.MissingOnRight;
                    missingRightCount++;
                }
                else if (left.Canonical == right.Canonical)
                {
                    status = ComparedChangeStatus.Same;
                    sameCount++;
                }
                else
                {
                    status = ComparedChangeStatus.Different;
                    differentCount++;
                }

                rows.Add(new ComparedChange
                {
                    Ordinal = i + 1,
                    Status = status,
                    LeftTimePointIndex = left?.TimePointIndex,
                    RightTimePointIndex = right?.TimePointIndex,
                    LeftShort = left?.ShortDescription ?? "<missing>",
                    RightShort = right?.ShortDescription ?? "<missing>",
                    LeftDetails = left?.DetailedDescription ?? "<missing>",
                    RightDetails = right?.DetailedDescription ?? "<missing>"
                });
            }

            StringBuilder summary = new StringBuilder();
            summary.AppendLine($"Projection: {leftSelection.TargetType}");
            summary.AppendLine($"Left target:  {leftSelection.Describe()}");
            summary.AppendLine($"Right target: {rightSelection.Describe()}");
            summary.AppendLine();
            summary.AppendLine($"Left change count:  {leftTransitions.Count}");
            summary.AppendLine($"Right change count: {rightTransitions.Count}");
            summary.AppendLine($"Exact matches by ordinal: {sameCount}");
            summary.AppendLine($"Different transitions: {differentCount}");
            summary.AppendLine($"Missing on left: {missingLeftCount}");
            summary.AppendLine($"Missing on right: {missingRightCount}");
            summary.AppendLine();
            summary.AppendLine("Notes:");
            summary.AppendLine("- Comparison ignores absolute timepoint numbers and compares the ordered state-change sequence instead.");
            summary.AppendLine("- Selected lobby/user ids are normalized, so lobby 567 vs lobby 444 (or user 123 vs 888) can be compared directly.");
            summary.AppendLine("- For lobby-data projections, each change represents the full aggregated state after a key update.");

            return new ComparisonResult
            {
                Summary = summary.ToString(),
                Changes = rows
            };
        }

        private static List<NormalizedTransition> ExtractTransitions(ParsedLogDocument document, ProjectionSelection selection)
        {
            var context = new NormalizationContext(selection);
            List<StatePoint> states = ExtractStates(document, selection, context);
            List<NormalizedTransition> result = new List<NormalizedTransition>();
            object? previous = null;
            string previousCanonical = SerializeNormalized(previous);

            foreach (StatePoint state in states)
            {
                string currentCanonical = SerializeNormalized(state.NormalizedState);
                string shortDescription = BuildShortDescription(previous, state.NormalizedState);
                string details = BuildDetailedDescription(previous, state.NormalizedState, state.TimePointIndex);

                result.Add(new NormalizedTransition
                {
                    TimePointIndex = state.TimePointIndex,
                    Canonical = previousCanonical + " -> " + currentCanonical,
                    ShortDescription = shortDescription,
                    DetailedDescription = details
                });

                previous = state.NormalizedState;
                previousCanonical = currentCanonical;
            }

            return result;
        }

        private static List<StatePoint> ExtractStates(ParsedLogDocument document, ProjectionSelection selection, NormalizationContext context)
        {
            return selection.TargetType switch
            {
                ComparisonTargetType.Lobby => ExtractSimpleTimeline(
                    GetRequiredTimeline(document.Projections.Lobby.ByLobbyId, selection.LobbyId, "lobby"),
                    context),
                ComparisonTargetType.LobbyData => ExtractLobbyDataStates(document, selection, context),
                ComparisonTargetType.LobbyMemberData => ExtractLobbyMemberDataStates(document, selection, context),
                ComparisonTargetType.P2PChannel => ExtractSimpleTimeline(
                    GetRequiredTimeline(document.Projections.P2PNetworkingPacket.ByChannel, selection.Channel, "channel"),
                    context),
                ComparisonTargetType.LobbyList => ExtractSimpleTimeline(document.Projections.LobbyList.Timeline, context),
                ComparisonTargetType.UserInformation => ExtractSimpleTimeline(
                    GetRequiredTimeline(document.Projections.UserInformation.ByUserId, selection.UserId, "user"),
                    context),
                ComparisonTargetType.UserStats => ExtractSimpleTimeline(
                    GetRequiredTimeline(document.Projections.UserStats.ByUserId, selection.UserId, "user"),
                    context),
                ComparisonTargetType.UserAchievements => ExtractSimpleTimeline(
                    GetRequiredTimeline(document.Projections.UserAchievements.ByUserId, selection.UserId, "user"),
                    context),
                _ => throw new InvalidOperationException($"Unsupported comparison target: {selection.TargetType}")
            };
        }

        private static TimelineProjection<T> GetRequiredTimeline<TKey, T>(IReadOnlyDictionary<TKey, TimelineProjection<T>> map, TKey? key, string description)
            where TKey : struct
            where T : class
        {
            if (!key.HasValue || !map.TryGetValue(key.Value, out TimelineProjection<T>? timeline))
            {
                throw new InvalidOperationException($"No {description} with key '{key}' was found in the loaded log.");
            }
            return timeline;
        }

        private static List<StatePoint> ExtractSimpleTimeline<T>(TimelineProjection<T> timeline, NormalizationContext context) where T : class
        {
            List<StatePoint> states = new List<StatePoint>();
            string? previousCanonical = null;

            foreach (KeyValuePair<int, T> pair in timeline.Changes.OrderBy(x => x.Key))
            {
                object? normalized = NormalizeValue(pair.Value, context);
                string canonical = SerializeNormalized(normalized);
                if (previousCanonical == canonical)
                {
                    continue;
                }

                states.Add(new StatePoint(pair.Key, normalized));
                previousCanonical = canonical;
            }

            return states;
        }

        private static List<StatePoint> ExtractLobbyDataStates(ParsedLogDocument document, ProjectionSelection selection, NormalizationContext context)
        {
            if (!selection.LobbyId.HasValue || !document.Projections.LobbyData.ByLobbyId.TryGetValue(selection.LobbyId.Value, out var keyMap))
            {
                throw new InvalidOperationException($"No lobby-data stream exists for lobby {selection.LobbyId}.");
            }

            var events = new List<KeyedStringEvent>();
            foreach (KeyValuePair<string, TimelineProjection<string?>> keyPair in keyMap)
            {
                foreach (KeyValuePair<int, string?> timePair in keyPair.Value.Changes)
                {
                    events.Add(new KeyedStringEvent(timePair.Key, keyPair.Key, timePair.Value));
                }
            }

            return AggregateKeyValueEvents(events, context);
        }

        private static List<StatePoint> ExtractLobbyMemberDataStates(ParsedLogDocument document, ProjectionSelection selection, NormalizationContext context)
        {
            if (!selection.LobbyId.HasValue || !selection.UserId.HasValue)
            {
                throw new InvalidOperationException("Lobby member data comparison requires both lobby and user selection.");
            }

            if (!document.Projections.LobbyMemberData.ByLobbyId.TryGetValue(selection.LobbyId.Value, out var users))
            {
                throw new InvalidOperationException($"No lobby-member-data stream exists for lobby {selection.LobbyId}.");
            }

            if (!users.TryGetValue(selection.UserId.Value, out var keys))
            {
                throw new InvalidOperationException($"No lobby-member-data stream exists for user {selection.UserId} in lobby {selection.LobbyId}.");
            }

            var events = new List<KeyedStringEvent>();
            foreach (KeyValuePair<string, TimelineProjection<string?>> keyPair in keys)
            {
                foreach (KeyValuePair<int, string?> timePair in keyPair.Value.Changes)
                {
                    events.Add(new KeyedStringEvent(timePair.Key, keyPair.Key, timePair.Value));
                }
            }

            return AggregateKeyValueEvents(events, context);
        }

        private static List<StatePoint> AggregateKeyValueEvents(List<KeyedStringEvent> events, NormalizationContext context)
        {
            List<StatePoint> states = new List<StatePoint>();
            SortedDictionary<string, string?> current = new SortedDictionary<string, string?>(StringComparer.Ordinal);
            string? previousCanonical = null;

            foreach (KeyedStringEvent item in events.OrderBy(x => x.TimePointIndex).ThenBy(x => x.Key, StringComparer.Ordinal))
            {
                current[item.Key] = item.Value;
                object? normalized = NormalizeValue(current, context);
                string canonical = SerializeNormalized(normalized);
                if (canonical == previousCanonical)
                {
                    continue;
                }

                states.Add(new StatePoint(item.TimePointIndex, normalized));
                previousCanonical = canonical;
            }

            return states;
        }

        private static object? NormalizeValue(object? value, NormalizationContext context)
        {
            if (value == null)
            {
                return null;
            }

            Type type = value.GetType();

            if (value is string || type.IsPrimitive || value is decimal)
            {
                return value;
            }

            if (value is Enum enumValue)
            {
                return enumValue.ToString();
            }

            if (value is GalaxyID galaxyId)
            {
                return NormalizeGalaxyId(galaxyId, context);
            }

            if (value is byte[] bytes)
            {
                return Convert.ToHexString(bytes);
            }

            if (value is System.Collections.IDictionary dict)
            {
                SortedDictionary<string, object?> normalized = new SortedDictionary<string, object?>(StringComparer.Ordinal);
                foreach (object key in dict.Keys)
                {
                    object? dictValue = dict[key];
                    string normalizedKey = SerializeDictionaryKey(key, context);
                    normalized[normalizedKey] = NormalizeValue(dictValue, context);
                }
                return normalized;
            }

            if (value is System.Collections.IEnumerable sequence)
            {
                List<object?> list = new List<object?>();
                foreach (object? item in sequence)
                {
                    list.Add(NormalizeValue(item, context));
                }
                return list;
            }

            SortedDictionary<string, object?> bag = new SortedDictionary<string, object?>(StringComparer.Ordinal);

            foreach (var field in type.GetFields(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.Public))
            {
                bag[field.Name] = NormalizeValue(field.GetValue(value), context);
            }

            foreach (var property in type.GetProperties(System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.Public)
                         .Where(x => x.CanRead && x.GetIndexParameters().Length == 0))
            {
                if (bag.ContainsKey(property.Name))
                {
                    continue;
                }

                try
                {
                    bag[property.Name] = NormalizeValue(property.GetValue(value), context);
                }
                catch
                {
                    // Ignore properties that throw during UI comparison flattening.
                }
            }

            return bag;
        }

        private static string SerializeDictionaryKey(object key, NormalizationContext context)
        {
            return key switch
            {
                GalaxyID gid => NormalizeGalaxyId(gid, context),
                null => "<null>",
                _ => Convert.ToString(key, CultureInfo.InvariantCulture) ?? key.ToString() ?? string.Empty
            };
        }

        private static string NormalizeGalaxyId(GalaxyID id, NormalizationContext context)
        {
            if (id.GetIDType() == GalaxyID.Type.ID_TYPE_LOBBY && context.SelectedLobbyId.HasValue && id.GetID() == context.SelectedLobbyId.Value)
            {
                return "$selectedLobby";
            }

            if (id.GetIDType() == GalaxyID.Type.ID_TYPE_USER && context.SelectedUserId.HasValue && id.GetID() == context.SelectedUserId.Value)
            {
                return "$selectedUser";
            }

            return $"{id.GetIDType()}:{id.GetID()}";
        }

        private static string SerializeNormalized(object? normalized)
        {
            return JsonSerializer.Serialize(normalized, JsonOptions);
        }

        private static string BuildShortDescription(object? before, object? after)
        {
            string Compact(object? value)
            {
                string json = SerializeNormalized(value).Replace(Environment.NewLine, " ");
                json = json.Replace("\r", " ").Replace("\n", " ").Trim();
                return json.Length <= 150 ? json : json.Substring(0, 147) + "...";
            }

            return $"{Compact(before)} -> {Compact(after)}";
        }

        private static string BuildDetailedDescription(object? before, object? after, int timePointIndex)
        {
            StringBuilder builder = new StringBuilder();
            builder.AppendLine($"Source timepoint index: {timePointIndex}");
            builder.AppendLine();
            builder.AppendLine("FROM");
            builder.AppendLine(SerializeNormalized(before));
            builder.AppendLine();
            builder.AppendLine("TO");
            builder.AppendLine(SerializeNormalized(after));
            return builder.ToString();
        }

        private sealed record KeyedStringEvent(int TimePointIndex, string Key, string? Value);
        private sealed record StatePoint(int TimePointIndex, object? NormalizedState);

        private sealed class NormalizedTransition
        {
            public int TimePointIndex { get; init; }
            public string Canonical { get; init; } = string.Empty;
            public string ShortDescription { get; init; } = string.Empty;
            public string DetailedDescription { get; init; } = string.Empty;
        }

        private sealed class NormalizationContext
        {
            public NormalizationContext(ProjectionSelection selection)
            {
                SelectedLobbyId = selection.LobbyId;
                SelectedUserId = selection.UserId;
            }

            public ulong? SelectedLobbyId { get; }
            public ulong? SelectedUserId { get; }
        }
    }
}
