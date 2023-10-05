using System;
using System.Windows.Forms;

namespace UniverseLanWizard
{
    public partial class WizardChoiceForm : Form
    {
        public WizardChoiceForm()
        {
            InitializeComponent();
        }

        private void btn_install_uvl_Click(object sender, EventArgs e)
        {
            var frm = new WizardInstallUniverseLANForm();
            frm.Location = this.Location;
            frm.StartPosition = FormStartPosition.Manual;
            //frm.FormClosing += delegate { this.Show(); };
            //frm.Show();
            
            this.Hide();
            frm.ShowDialog();
            this.Close();
        }

        private void btn_launch_game_server_Click(object sender, EventArgs e)
        {

        }

        private void btn_launch_game_client_Click(object sender, EventArgs e)
        {

        }
    }
}
