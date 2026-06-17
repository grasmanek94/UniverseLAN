using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Projections
{
    public static class ProjectionClone
    {
        public static T Clone<T>(T value)
        {
            return CloneUtils.DeepClone(value);
        }
    }
}