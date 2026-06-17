using MessagePack;
using UniverseLanLogAnalyzer.Galaxy.Types;
using UniverseLanLogAnalyzer.Util;

namespace UniverseLanLogAnalyzer.Projections
{
    [MessagePackObject]
    public class UserInformationSnapshot
    {
        [Key(0)]
        public GalaxyID id = new GalaxyID(0);

        [Key(1)]
        public string persona_name = string.Empty;

        [Key(2)]
        public PersonaStateChange persona_state_change = PersonaStateChange.PERSONA_CHANGE_NONE;

        [Key(3)]
        public AvatarType avatar_criteria = AvatarType.AVATAR_TYPE_NONE;

        [Key(4)]
        public int rich_presence_update_count = 0;

        public UserInformationSnapshot DeepClone()
        {
            return CloneUtils.DeepClone(this);
        }
    }
}
