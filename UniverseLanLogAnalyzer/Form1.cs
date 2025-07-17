using UniverseLanLogAnalyzer.Parser;

namespace UniverseLanLogAnalyzer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            LogParser parser = new LogParser(@"C:\Users\Rafal\Desktop\SSBD-real-gog-log\Working-A.log");
            parser.Parse();
        }
    }
}
