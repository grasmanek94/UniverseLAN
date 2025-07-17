using System.Globalization;
using System.Runtime.CompilerServices;
using UniverseLanLogAnalyzer.Galaxy;

namespace UniverseLanLogAnalyzer.Parser
{
    public class LogParser
    {
        public string FileName { get; private set; }
        public int NestingLevel { get; private set; }
        public int CurrentLineNumber { get; private set; }
        public List<LogEntries.Base> Entries { get; private set; }
        private LogEntries.Base? PreviousEntry { get; set; }
        private LoggerStateMachine StateMachine { get; set; }

        public LogParser(string filename, LoggerStateMachine state_machine)
        {
            FileName = filename;
            NestingLevel = 0;
            CurrentLineNumber = 0;
            Entries = new();
            PreviousEntry = null;
            StateMachine = state_machine;
        }

        public void Parse()
        {
            using (StreamReader reader = new StreamReader(FileName))
            {
                string? line = reader.ReadLine();

                while (line != null)
                {
                    ++CurrentLineNumber;

                    ParseLine(line);

                    line = reader.ReadLine();
                }
            }
        }

        private LogEntries.Base? GetLastRelativeEntryAtNestingLevel(LogEntries.Base current)
        {
            int nesting_level = current.NestingLevel;
            LogEntries.Base? prev = current.Previous;

            if(prev == null || prev.NestingLevel < nesting_level)
            {
                return null;
            }

            while (prev != null)
            {
                if(prev.NestingLevel == nesting_level)
                {
                    return prev;
                }

                prev = prev.Previous;
            }

            return null;
        }

        private LogEntries.Base? GetLastUpEntry()
        {
            LogEntries.Base? prev = Entries.Last();

            if (prev == null)
            {
                return null;
            }

            while (prev != null)
            {
                if (prev.NestingLevel == (NestingLevel - 1))
                {
                    return prev;
                }

                prev = prev.Previous;
            }

            return null;
        }

        private LogEntries.Base? CalculateEntryParent(LogEntries.Base current)
        {
            int nesting_level = current.NestingLevel;
            LogEntries.Base? prev = current.Previous;

            while (prev != null)
            {
                if (prev.NestingLevel < nesting_level)
                {
                    return prev;
                }

                prev = prev.Previous;
            }

            return null;
        }

        private void AddNewEntry(string line)
        {
            string trimmed = line.Substring(NestingLevel);

            string after_plus = trimmed.Substring(1);
            if (after_plus.Length < 1)
            {
                throw new InterceptorLogParsingException(FileName, CurrentLineNumber, line);
            }

            int at_sign = after_plus.LastIndexOf('@');
            if (at_sign == -1)
            {
                throw new InterceptorLogParsingException(FileName, CurrentLineNumber, line);
            }

            string address_str = after_plus.Substring(at_sign + 1);
            string function_str = after_plus.Substring(0, at_sign);
            string function_str_extra = String.Empty;

            int function_str_space = function_str.IndexOf(" ");
            if (function_str_space != -1)
            {
                function_str_extra = function_str.Substring(function_str_space + 1);
                function_str = function_str.Substring(0, function_str_space);
            }

            ulong address = 0;
            if (!ulong.TryParse(address_str, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out address))
            {
                throw new InterceptorLogParsingException(FileName, CurrentLineNumber, line);
            }

            LogEntries.Base entry = new();

            entry.NestingLevel = NestingLevel;
            entry.Address = address;
            entry.Function = function_str;
            entry.FunctionExtra = function_str_extra;
            entry.Previous = PreviousEntry;

            if (PreviousEntry != null)
            {
                PreviousEntry.Next = entry;
            }

            LogEntries.Base? nesting_level_tracker = GetLastRelativeEntryAtNestingLevel(entry);
            if (nesting_level_tracker != null)
            {
                entry.PrevAtNestingLevel = nesting_level_tracker;
                nesting_level_tracker.NextAtNestingLevel = entry;
            }

            LogEntries.Base? parent = CalculateEntryParent(entry);
            if (parent != null && parent.Child == null)
            {
                /* Sets the first child of the chain as child */
                entry.Parent = parent;
                parent.Child = entry;
            }

            Entries.Add(LogEntries.Reallocator.ReMap(entry));

            PreviousEntry = entry;
        }

        private void CheckIndentation(string line)
        {
            for (int i = 0; i < NestingLevel; ++i)
            {
                if (line[i] != ' ')
                {
                    throw new InterceptorLogParsingException(FileName, CurrentLineNumber, line);
                }
            }
        }

        private void ParseLine(string line)
        {
            if (line.Length < 2)
            {
                return;
            }

            if (line.Length <= NestingLevel)
            {
                throw new InterceptorLogParsingException(FileName, CurrentLineNumber, line);
            }

            if (NestingLevel > 0 && line[NestingLevel - 1] == '-')
            {
                --NestingLevel;

                if (PreviousEntry == null)
                {
                    throw new InterceptorLogParsingException(FileName, CurrentLineNumber, line);
                }
            }

            CheckIndentation(line);

            switch (line[NestingLevel])
            {
                case '+':

                    AddNewEntry(line);

                    ++NestingLevel;

                    break;

                case '-':
                    /* Already processed */
                    break;

                default:
                    if (PreviousEntry == null)
                    {
                        throw new InterceptorLogParsingException(FileName, CurrentLineNumber, line);
                    }

                    LogEntries.Base? entry = GetLastUpEntry();
                    if(entry == null)
                    {
                        throw new InterceptorLogParsingException(FileName, CurrentLineNumber, line);
                    }

                    entry.Properties.Add(line.Trim());

                    break;
            }
        }
    }
}
