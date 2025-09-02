using MessagePack;

namespace UniverseLanLogAnalyzer.Util
{
    public static class CloneUtils
    {
        public static T DeepClone<T>(T value)
        {
            return MessagePackSerializer.Deserialize<T>(MessagePackSerializer.Serialize(value));
        }
    }
}
