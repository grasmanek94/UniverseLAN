namespace UniverseLanWizard
{
    partial class WizardChoiceForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_install_uvl = new System.Windows.Forms.Button();
            this.btn_launch_game_server = new System.Windows.Forms.Button();
            this.btn_launch_game_client = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_install_uvl
            // 
            this.btn_install_uvl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_install_uvl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_install_uvl.Location = new System.Drawing.Point(3, 3);
            this.btn_install_uvl.Name = "btn_install_uvl";
            this.btn_install_uvl.Size = new System.Drawing.Size(290, 24);
            this.btn_install_uvl.TabIndex = 0;
            this.btn_install_uvl.Text = "Install UniverseLAN (into game directory)";
            this.btn_install_uvl.UseVisualStyleBackColor = true;
            this.btn_install_uvl.Click += new System.EventHandler(this.btn_install_uvl_Click);
            // 
            // btn_launch_game_server
            // 
            this.btn_launch_game_server.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_launch_game_server.Enabled = false;
            this.btn_launch_game_server.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_launch_game_server.Location = new System.Drawing.Point(3, 33);
            this.btn_launch_game_server.Name = "btn_launch_game_server";
            this.btn_launch_game_server.Size = new System.Drawing.Size(290, 25);
            this.btn_launch_game_server.TabIndex = 1;
            this.btn_launch_game_server.Text = "Launch Game + UniverseLAN Server";
            this.btn_launch_game_server.UseVisualStyleBackColor = true;
            this.btn_launch_game_server.Click += new System.EventHandler(this.btn_launch_game_server_Click);
            // 
            // btn_launch_game_client
            // 
            this.btn_launch_game_client.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_launch_game_client.Enabled = false;
            this.btn_launch_game_client.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_launch_game_client.Location = new System.Drawing.Point(3, 64);
            this.btn_launch_game_client.Name = "btn_launch_game_client";
            this.btn_launch_game_client.Size = new System.Drawing.Size(290, 26);
            this.btn_launch_game_client.TabIndex = 2;
            this.btn_launch_game_client.Text = "Launch Game + UniverseLAN Client";
            this.btn_launch_game_client.UseVisualStyleBackColor = true;
            this.btn_launch_game_client.Click += new System.EventHandler(this.btn_launch_game_client_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.btn_install_uvl, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.btn_launch_game_client, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.btn_launch_game_server, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.GrowStyle = System.Windows.Forms.TableLayoutPanelGrowStyle.FixedSize;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33109F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33779F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33112F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(296, 93);
            this.tableLayoutPanel1.TabIndex = 3;
            // 
            // WizardChoiceForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(296, 93);
            this.Controls.Add(this.tableLayoutPanel1);
            this.MinimumSize = new System.Drawing.Size(312, 132);
            this.Name = "WizardChoiceForm";
            this.Text = "UniverseLAN Wizard Choice...";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_install_uvl;
        private System.Windows.Forms.Button btn_launch_game_server;
        private System.Windows.Forms.Button btn_launch_game_client;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
    }
}

