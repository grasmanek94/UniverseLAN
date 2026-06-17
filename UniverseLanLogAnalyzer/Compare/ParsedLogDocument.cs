using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;
using UniverseLanLogAnalyzer.Projections;

namespace UniverseLanLogAnalyzer.Compare
{
    public sealed class ParsedLogDocument
    {
        public string FilePath { get; }
        public LoggerStateMachine StateMachine { get; }
        public ProjectionSuite Projections { get; }

        private ParsedLogDocument(string filePath, LoggerStateMachine stateMachine, ProjectionSuite projections)
        {
            FilePath = filePath;
            StateMachine = stateMachine;
            Projections = projections;
        }

        public static ParsedLogDocument Load(string filePath)
        {
            LoggerStateMachine stateMachine = new LoggerStateMachine();
            LogParser parser = new LogParser(filePath, stateMachine);
            parser.Parse();
            LoggerStateMachineCleanup cleanup = new LoggerStateMachineCleanup(stateMachine);
            cleanup.FoldRecurring();
            stateMachine.PopulateStateMachine();
            ProjectionSuite projections = ProjectionSuite.Build(stateMachine);
            return new ParsedLogDocument(filePath, stateMachine, projections);
        }
    }
}
