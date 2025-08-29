namespace UniverseLanLogAnalyzer.Galaxy
{
    public class User
    {
        public GalaxyID id;

        public User(GalaxyID id)
        {
            this.id = id;
        }

        public User(ulong id)
        {
            this.id = new GalaxyID(id, GalaxyID.Type.ID_TYPE_USER);
        }
    }
}
