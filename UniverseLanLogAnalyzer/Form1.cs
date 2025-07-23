using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer
{
    public partial class Form1 : Form
    {
        public static readonly string[] test_files = new string[]
        {
            @"C:\Users\Rafal\Desktop\SSBD-real-gog-log\Working-A.log",
            @"C:\Users\Rafal\Desktop\SSBD-real-gog-log\Working-B.log",
            @"C:\Users\Rafal\Desktop\SSBD-real-gog-log\NotWorking-A.log",
            @"C:\Users\Rafal\Desktop\SSBD-real-gog-log\NotWorking-B.log"
        };

        public Form1()
        {
            InitializeComponent();

            foreach(var file in test_files)
            {
                LoggerStateMachine state_machine = new LoggerStateMachine();
                LogParser parser = new LogParser(file, state_machine);
                parser.Parse();
                LoggerStateMachineCleanup cleanup = new LoggerStateMachineCleanup(state_machine);
                cleanup.FoldRecurring();
            }
        }
    }
}
