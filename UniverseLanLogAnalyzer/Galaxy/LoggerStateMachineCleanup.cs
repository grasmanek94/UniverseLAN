namespace UniverseLanLogAnalyzer.Galaxy
{
    public class LoggerStateMachineCleanup
    {
        public List<LogEntries.Base>? CleanedUpEntries;
        public LoggerStateMachine StateMachine;

        public LoggerStateMachineCleanup(LoggerStateMachine state_machine)
        {
            StateMachine = state_machine;
        }

        public void Fold(LogEntries.Base entry)
        {
            LogEntries.Base? next = entry.Next;
            if(next == null)
            {
                return;
            }

            /* Basically removes the entry from in between two entries from the linked list */
            entry.Next = next.Next;
            if (entry.Next != null)
            {
                entry.Next.Previous = entry;
            }
        }

        public void FoldRecurring()
        {
            CleanedUpEntries = new();

            for (int i = 0; i < StateMachine.Entries.Count; ++i)
            {
                LogEntries.Base entry = StateMachine.Entries[i];
                CleanedUpEntries.Add(entry);
                while (entry.CollapseRepeat && entry.IsRepeatEntry(entry.Next))
                {
                    ++i;
                    Fold(entry);
                }
            }
        }
    }
}
