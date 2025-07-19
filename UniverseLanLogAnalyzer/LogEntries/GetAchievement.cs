using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class GetAchievement : Base
    {
        public static readonly string MATCH = "universelan::client::StatsImpl::GetAchievement";

        public string Name = "";
        public GalaxyID? UserID;
        public bool Unlocked;
        public uint UnlockTime;

        public GetAchievement(Base original) : base(original) { }

        /* Example contents:
            name: all_weapons
            userID: 0(ID_TYPE_UNASSIGNED)
            unlocked: false
            unlockTime: 0
        */
        public override void PostInit()
        {
            if (!PropertyParser.Parse(ref Properties,
                "name: {s}\nuserID: {gid}\nunlocked: {b}\nunlockTime: {d}",
                out Name, out UserID, out Unlocked, out UnlockTime))
            {
                throw new InterceptorPropertyParsingException(this);
            }
        }
    }
}
