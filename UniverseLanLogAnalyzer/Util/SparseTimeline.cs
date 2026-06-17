using System.Collections;
using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Projections
{
    /// <summary>
    /// Stores snapshots only when value changed.
    /// Random access by parser entry index returns the nearest previous snapshot.
    /// </summary>
    public class SparseTimeline<T> : IEnumerable<KeyValuePair<int, T>>
        where T : class
    {
        private readonly SortedDictionary<int, T> _points = new();

        public IEnumerable<int> TimePoints => _points.Keys;

        public int Count => _points.Count;

        public bool HasAny => _points.Count > 0;

        public T? Latest => _points.Count == 0 ? null : _points.Last().Value;

        public T? this[int parserEntryIndex]
        {
            get
            {
                if (_points.Count == 0)
                {
                    return null;
                }

                T? best = null;

                foreach (var kv in _points)
                {
                    if (kv.Key > parserEntryIndex)
                    {
                        break;
                    }

                    best = kv.Value;
                }

                return best;
            }
        }

        public void SetIfChanged(int parserEntryIndex, T snapshot, Func<T, T, bool> areEqual)
        {
            if (_points.TryGetValue(parserEntryIndex, out var existingAtSamePoint))
            {
                if (!areEqual(existingAtSamePoint, snapshot))
                {
                    _points[parserEntryIndex] = CloneUtils.DeepClone(snapshot);
                }

                return;
            }

            var previous = this[parserEntryIndex];
            if (previous != null && areEqual(previous, snapshot))
            {
                return;
            }

            _points[parserEntryIndex] = CloneUtils.DeepClone(snapshot);
        }

        public bool ContainsTimePoint(int parserEntryIndex)
        {
            return _points.ContainsKey(parserEntryIndex);
        }

        public IEnumerator<KeyValuePair<int, T>> GetEnumerator()
        {
            return _points.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}