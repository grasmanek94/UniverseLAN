using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.LogEntries
{
    public class Base
    {
        public Base? Next { get; set; }
        public Base? Previous { get; set; }

        public Base? Parent { get; set; }
        public Base? Child { get; set; }

        public Base? NextAtNestingLevel { get; set; }
        public Base? PrevAtNestingLevel { get; set; }

        public ulong Address = 0;
        public int NestingLevel = 0;
        public string Function = String.Empty;
        public string FunctionExtra = String.Empty;

        /* Entries such as ReadP2PPacket and Send aren't considered 'Key' frames for log comparison.
         * Entries like 'CreateLobby' 'JoinLobby' 'Set*Data' etc should be considered key elements for comparison.
         * */
        public bool IsKeyFrame = false;

        /* Entries which can be squashed into a single entry like IsP2PPacketAvailable or GetGalaxyID loops, etc..
         * */
        public bool CollapseRepeat = false;

        public List<string> Properties = new List<string>();

        public LoggerStateMachine StateMachine;

        public Base(LoggerStateMachine state_machine) {
            StateMachine = state_machine;
        }

        public Base(Base original)
        {
            this.Next = original.Next;
            this.Previous = original.Previous;
            this.Parent = original.Parent;
            this.Child = original.Child;
            this.NextAtNestingLevel = original.NextAtNestingLevel;
            this.PrevAtNestingLevel = original.PrevAtNestingLevel;
            this.Address = original.Address;
            this.NestingLevel = original.NestingLevel;
            this.Function = original.Function;
            this.FunctionExtra = original.FunctionExtra;
            this.Properties = new List<string>(original.Properties);
            this.StateMachine = original.StateMachine;
            this.IsKeyFrame = original.IsKeyFrame;
            this.CollapseRepeat = original.CollapseRepeat;
        }

        public virtual void PostInit() { }

        public override string ToString()
        {
            return $"{Function}@{Address:X}[{NestingLevel}]";
        }
    }
}
