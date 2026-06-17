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
}