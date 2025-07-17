namespace UniverseLanLogAnalyzer.Galaxy
{
    public class GalaxyID
    {
        public enum Type
        {
            ID_TYPE_UNASSIGNED,
            ID_TYPE_LOBBY,
            ID_TYPE_USER
        }

        public ulong id; // 0 as an argument to a function means usually SELF (logged in user), otherwise invalid

        public GalaxyID(ulong id)
        {
            this.id = id;
        }

        public GalaxyID(ulong id, Type type)
        {
            this.id = (id & 0x0FFFFFFFFFFFFFFF) | (((ulong)type << 56) & 0xF000000000000000);
        }

        public Type GetIDType()
        {
            return (Type)(id >> 56);
        }

        public void SetType(Type type)
        {
            this.id = (id & 0x0FFFFFFFFFFFFFFF) | (((ulong)type << 56) & 0xF000000000000000);
        }

        public void SetID(ulong id)
        {
            this.id = (id & 0x0FFFFFFFFFFFFFFF) | (((ulong)GetIDType() << 56) & 0xF000000000000000);
        }

        public void SetRaw(ulong num)
        {
            this.id = num;
        }
    }
}
