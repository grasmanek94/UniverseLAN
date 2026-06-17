namespace UniverseLanLogAnalyzer.Projections
{
    /// <summary>
    /// Key -> sparse timeline.
    /// Usage:
    ///   projection[key][entryIndex]
    /// </summary>
    public class ProjectionMap<TKey, TValue>
        where TKey : notnull
        where TValue : class
    {
        private readonly Dictionary<TKey, SparseTimeline<TValue>> _map = new();

        public IReadOnlyDictionary<TKey, SparseTimeline<TValue>> Items => _map;

        public SparseTimeline<TValue> this[TKey key]
        {
            get
            {
                if (!_map.TryGetValue(key, out var timeline))
                {
                    timeline = new SparseTimeline<TValue>();
                    _map[key] = timeline;
                }

                return timeline;
            }
        }

        public bool TryGetValue(TKey key, out SparseTimeline<TValue> timeline)
        {
            return _map.TryGetValue(key, out timeline!);
        }

        public IEnumerable<TKey> Keys => _map.Keys;
    }
}