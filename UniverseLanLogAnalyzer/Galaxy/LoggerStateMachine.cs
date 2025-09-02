namespace UniverseLanLogAnalyzer.Galaxy
{
    public class LoggerStateMachine
    {
        public List<LogEntries.Base> Entries { get; set; } = new();

        public List<State> States {  get; set; } = new();

        public void PopulateStateMachine()
        {
            States.Clear();

            State state = new State();

            foreach (var entry in Entries)
            {
                entry.ProcessState(state);

                States.Add(state);
                state = state.DeepClone();
            }
        }
    }
}
