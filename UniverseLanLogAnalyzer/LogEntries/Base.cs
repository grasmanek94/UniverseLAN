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

        public ulong Address { get; set; } = 0;
        public int NestingLevel { get; set; } = 0;
        public string Function { get; set; } = String.Empty;
        public string FunctionExtra { get; set; } = String.Empty;

        public List<string> Properties { get; set; } = new List<string>();

        public LoggerStateMachine StateMachine { get; set; }

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
        }

        public virtual void PostInit() { }

        public override string ToString()
        {
            return $"{Function}@{Address:X}[{NestingLevel}]";
        }
    }
}
