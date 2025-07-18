using UniverseLanLogAnalyzer.Galaxy;
using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            {
                LoggerStateMachine state_machine = new LoggerStateMachine();
                LogParser parser = new LogParser(@"C:\Users\Rafal\Desktop\SSBD-real-gog-log\Working-A.log", state_machine);
                parser.Parse();
            }
            {
                LoggerStateMachine state_machine = new LoggerStateMachine();
                LogParser parser = new LogParser(@"C:\Users\Rafal\Desktop\SSBD-real-gog-log\Working-B.log", state_machine);
                parser.Parse();
            }
            {
                LoggerStateMachine state_machine = new LoggerStateMachine();
                LogParser parser = new LogParser(@"C:\Users\Rafal\Desktop\SSBD-real-gog-log\NotWorking-C.log", state_machine);
                parser.Parse();
            }
            {
                LoggerStateMachine state_machine = new LoggerStateMachine();
                LogParser parser = new LogParser(@"C:\Users\Rafal\Desktop\SSBD-real-gog-log\NotWorking-D.log", state_machine);
                parser.Parse();
            }
        }
    }
}
