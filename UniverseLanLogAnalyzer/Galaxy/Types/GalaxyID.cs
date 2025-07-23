namespace UniverseLanLogAnalyzer.Galaxy.Types
{
    public class GalaxyID
    {
        public enum Type
        {
            ID_TYPE_UNASSIGNED,
            ID_TYPE_LOBBY,
            ID_TYPE_USER
        }

        public ulong raw; // 0 as an argument to a function means usually SELF (logged in user), otherwise invalid
        public static readonly ulong mask_id = 0x00FFFFFFFFFFFFFFUL;
        public static readonly ulong mask_type = ~mask_id;
        public static readonly int shift_type = 56;

        public GalaxyID(ulong id)
        {
            raw = id;
        }

        public GalaxyID(ulong id, Type type)
        {
            raw = (ulong)type << shift_type & mask_type | id & mask_id;
        }

        public Type GetIDType()
        {
            return (Type)(raw >> 56);
        }

        public ulong GetID()
        {
            return raw & mask_id;
        }

        public void SetType(Type type)
        {
            raw = raw & mask_id | (ulong)type << shift_type & mask_type;
        }

        public void SetID(ulong id)
        {
            raw = raw & mask_id | (ulong)GetIDType() << shift_type & mask_type;
        }

        public void SetRaw(ulong num)
        {
            raw = num;
        }
    }
}
