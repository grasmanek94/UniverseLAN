using Microsoft.WindowsAPICodePack.Dialogs;
using Newtonsoft.Json.Linq;
using System;
using System.Drawing;
using System.IO;
using System.Runtime.Versioning;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UniverseLanWizard
{
    public partial class WizardInstallUniverseLANForm : Form
    {
        private static string ReleasesURL = "https://api.github.com/repos/grasmanek94/UniverseLAN/releases?per_page=1";

        private string AppBaseDirectory;

        private string SHA1HashesTxtFile;
        private string ReleasesJsonFile;
        private string CurrentSelectedDir;

        private DLLHashDatabase DLLHashDb;
        private GalaxyGameScanner Scanner;
        private GalaxyBinaryCompatibilityMatrix CompatibilityMatrix;
        private InstallWizardLogic InstallActions;

        public WizardInstallUniverseLANForm()
        {
            AppBaseDirectory = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);

            SHA1HashesTxtFile = Path.Combine(AppBaseDirectory, "sha1_hashes.txt");
            ReleasesJsonFile = Path.Combine(AppBaseDirectory, "releases.json");

            DLLHashDb = new DLLHashDatabase();
            if (File.Exists(SHA1HashesTxtFile))
            {
                DLLHashDb.LoadFile(SHA1HashesTxtFile);
            }
            else
            {
                DLLHashDb.LoadString(Resources.sha1_hashes);
            }

            Scanner = new GalaxyGameScanner(DLLHashDb);
            Scanner.OnScanStarted += Scanner_OnScanStarted;
            Scanner.OnScanFinished += Scanner_OnScanFinished;
            Scanner.OnScanUpdate += Scanner_OnScanUpdate;
            Scanner.OnScanDLLFound += Scanner_OnScanDLLFound;

            CompatibilityMatrix = new GalaxyBinaryCompatibilityMatrix();

            InitializeComponent();

            var fi = new FileInfo(ReleasesJsonFile);
            bool check_for_update = true;
            if (fi.Exists)
            {
                var releases_age = fi.LastWriteTime - DateTime.Now;
                check_for_update = (releases_age.TotalDays >= 1.0);
            }

            if (check_for_update)
            {
                DialogResult dialogResult = MessageBox.Show(string.Format("Will you allow this program to contact\n\n    {0}\n\nto update the latest release information?", ReleasesURL), "Release info update allowed?", MessageBoxButtons.YesNo);
                if (dialogResult == DialogResult.Yes)
                {
                    SimpleFileDownloader.DownloadFile(ReleasesURL, ReleasesJsonFile);
                }
                else if (dialogResult == DialogResult.No)
                {
                    if (!File.Exists(ReleasesJsonFile))
                    {
                        MessageBox.Show(string.Format("This program cannot work without any releases information.\nPlease go to\n\n    {1}\n\n and put the contents into a file called \n\n    {0}\\releases.json\n\n(You can click this message and CTRL+C to copy the URL and file name)", AppBaseDirectory, ReleasesURL), "No release data available", MessageBoxButtons.OK);
                        Application.Exit();
                    }
                }
            }

            string latest_release_info_data = File.ReadAllText(ReleasesJsonFile);
            JArray releases_info = JArray.Parse(latest_release_info_data);

            if (releases_info.Count < 1)
            {
                MessageBox.Show(string.Format("{0}\\releases.json\n\nDoes not have any releases.", AppBaseDirectory, ReleasesURL), "No release data available", MessageBoxButtons.OK);
                Application.Exit();
            }

            var latest_release_info = releases_info.First["assets"];

            foreach (var entry in latest_release_info)
            {
                var name = entry["name"];
                var browser_download_url = entry["browser_download_url"];

                CompatibilityMatrix.AddVersionAsset(name.Value<string>(), browser_download_url.Value<string>());
            }

            CurrentSelectedDir = "";
            InstallActions = new InstallWizardLogic(CompatibilityMatrix);
        }

        private void Scanner_OnScanStarted(GalaxyGameScanner sender)
        {
            btn_scan.Invoke(new Action(() =>
            {
                btn_scan.Enabled = false;
                txtbox_game_directory.Enabled = false;
                btn_browse_game_directory.Enabled = false;
                label_status.Text = "";
            }));
        }

        private void Scanner_OnScanUpdate(GalaxyGameScanner sender, int files_processed)
        {
            btn_scan.Invoke(new Action(() =>
            {
                label_progress.Text = String.Format("{0} / {1}", sender.GetFoundGalaxyDLLsCount(), sender.CurrentFilesProcessedCount);
            }));
        }

        private void Scanner_OnScanDLLFound(GalaxyGameScanner sender, string file, DLLHashEntry version_info)
        {

        }

        private void Scanner_OnScanFinished(GalaxyGameScanner sender)
        {
            btn_scan.Invoke(new Action(() =>
            {
                btn_browse_game_directory.Enabled = true;
                txtbox_game_directory.Enabled = true;
                txtbox_game_directory_TextChanged(null, null);

                WizardPerformInstallCheck();
            }));
        }

        private void WizardPerformInstallCheck()
        {
            if (Scanner.GetFoundGalaxyDLLsCount() > 0)
            {
                listBox1.DataSource = null;
                try
                {
                    InstallActions.ParseInfo(Scanner);
                    listBox1.DataSource = InstallActions.Actions;

                    string versions = "";
                    foreach (var dll_version in Scanner.GetFoundGalaxyDLLs().Values)
                    {
                        versions += " " + dll_version.version + "-" + dll_version.bits.ToString();
                    }

                    label_status.Text = "Found Galaxy DLLs:\n" + versions;
                    label_status.ForeColor = Color.Green;
                }
                catch (UnsupportedGalaxyVersionException ex)
                {
                    label_status.Text = "Unsupported Galaxy Version:\n" + ex.Message;
                    label_status.ForeColor = Color.OrangeRed;
                }
            }
            else
            {
                label_status.Text = "No Galaxy DLLs found.";
                label_status.ForeColor = Color.Red;
            }
        }

        private void WizardInstallUniverseLANForm_Load(object sender, EventArgs e)
        {
            btn_scan.Enabled = false;
            txtbox_game_directory.Text = Directory.GetCurrentDirectory() + "\\";
        }

        [SupportedOSPlatform("windows")]
        private void btn_browse_game_directory_Click(object sender, EventArgs e)
        {
            CommonOpenFileDialog dialog = new()
            {
                IsFolderPicker = true
            };

            if (dialog.ShowDialog() == CommonFileDialogResult.Ok)
            {
                txtbox_game_directory.Text = Path.GetFullPath(dialog.FileName + "\\");
            }
        }

        private void txtbox_game_directory_TextChanged(object sender, EventArgs e)
        {
            if (txtbox_game_directory.Text == null || txtbox_game_directory.Text.Trim() == "")
            {
                return;
            }

            CurrentSelectedDir = txtbox_game_directory.Text.Trim();

            DirectoryInfo dirInfo = new DirectoryInfo(CurrentSelectedDir);
            btn_scan.Enabled = dirInfo.Exists;
        }

        private void btn_scan_Click(object sender, EventArgs e)
        {
            DirectoryInfo dirInfo = new DirectoryInfo(CurrentSelectedDir);
            if (!dirInfo.Exists)
            {
                return;
            }

            Task.Run(() => Scanner.Scan(CurrentSelectedDir));
        }
    }
}
