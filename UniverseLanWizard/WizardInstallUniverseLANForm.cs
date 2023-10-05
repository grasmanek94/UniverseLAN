using Microsoft.WindowsAPICodePack.Dialogs;
using System;
using System.IO;
using System.Windows.Forms;

namespace UniverseLanWizard
{
    public partial class WizardInstallUniverseLANForm : Form
    {
        public WizardInstallUniverseLANForm()
        {
            InitializeComponent();
        }

        private void WizardInstallUniverseLANForm_Load(object sender, EventArgs e)
        {
            btn_scan.Enabled = false;
            txtbox_game_directory.Text = Directory.GetCurrentDirectory() + "\\";
        }

        private void btn_browse_game_directory_Click(object sender, EventArgs e)
        {
            CommonOpenFileDialog dialog = new CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            if (dialog.ShowDialog() == CommonFileDialogResult.Ok)
            {
                txtbox_game_directory.Text = dialog.FileName + "\\";
            }
        }

        private void txtbox_game_directory_TextChanged(object sender, EventArgs e)
        {
            if(txtbox_game_directory.Text == null || txtbox_game_directory.Text.Trim() == "")
            {
                return;
            }

            string dir = txtbox_game_directory.Text.Trim();

            DirectoryInfo dirInfo = new DirectoryInfo(dir);
            btn_scan.Enabled = dirInfo.Exists;
        }
    }
}
