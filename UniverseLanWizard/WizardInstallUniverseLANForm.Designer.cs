namespace UniverseLanWizard
{
    partial class WizardInstallUniverseLANForm
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
            this.txtbox_game_directory = new System.Windows.Forms.TextBox();
            this.btn_browse_game_directory = new System.Windows.Forms.Button();
            this.label_game_directory = new System.Windows.Forms.Label();
            this.table_layout_panel_game_directory = new System.Windows.Forms.TableLayoutPanel();
            this.label_progress = new System.Windows.Forms.Label();
            this.label_status = new System.Windows.Forms.Label();
            this.btn_scan = new System.Windows.Forms.Button();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.table_layout_panel_game_directory.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtbox_game_directory
            // 
            this.txtbox_game_directory.AllowDrop = true;
            this.txtbox_game_directory.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
            this.txtbox_game_directory.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
            this.txtbox_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtbox_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtbox_game_directory.Location = new System.Drawing.Point(113, 3);
            this.txtbox_game_directory.Name = "txtbox_game_directory";
            this.txtbox_game_directory.Size = new System.Drawing.Size(423, 22);
            this.txtbox_game_directory.TabIndex = 0;
            this.txtbox_game_directory.WordWrap = false;
            this.txtbox_game_directory.TextChanged += new System.EventHandler(this.txtbox_game_directory_TextChanged);
            // 
            // btn_browse_game_directory
            // 
            this.btn_browse_game_directory.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btn_browse_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btn_browse_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_browse_game_directory.Location = new System.Drawing.Point(542, 3);
            this.btn_browse_game_directory.Name = "btn_browse_game_directory";
            this.btn_browse_game_directory.Size = new System.Drawing.Size(104, 28);
            this.btn_browse_game_directory.TabIndex = 1;
            this.btn_browse_game_directory.Text = "Browse...";
            this.btn_browse_game_directory.UseVisualStyleBackColor = true;
            this.btn_browse_game_directory.Click += new System.EventHandler(this.btn_browse_game_directory_Click);
            // 
            // label_game_directory
            // 
            this.label_game_directory.AutoSize = true;
            this.label_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_game_directory.Location = new System.Drawing.Point(3, 0);
            this.label_game_directory.Name = "label_game_directory";
            this.label_game_directory.Size = new System.Drawing.Size(104, 34);
            this.label_game_directory.TabIndex = 2;
            this.label_game_directory.Text = "Game Directory:";
            this.label_game_directory.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // table_layout_panel_game_directory
            // 
            this.table_layout_panel_game_directory.ColumnCount = 3;
            this.table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.table_layout_panel_game_directory.Controls.Add(this.label_progress, 0, 2);
            this.table_layout_panel_game_directory.Controls.Add(this.label_status, 0, 2);
            this.table_layout_panel_game_directory.Controls.Add(this.btn_browse_game_directory, 2, 0);
            this.table_layout_panel_game_directory.Controls.Add(this.txtbox_game_directory, 1, 0);
            this.table_layout_panel_game_directory.Controls.Add(this.label_game_directory, 0, 0);
            this.table_layout_panel_game_directory.Controls.Add(this.btn_scan, 2, 1);
            this.table_layout_panel_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            this.table_layout_panel_game_directory.Location = new System.Drawing.Point(0, 0);
            this.table_layout_panel_game_directory.MaximumSize = new System.Drawing.Size(0, 105);
            this.table_layout_panel_game_directory.MinimumSize = new System.Drawing.Size(0, 105);
            this.table_layout_panel_game_directory.Name = "table_layout_panel_game_directory";
            this.table_layout_panel_game_directory.RowCount = 3;
            this.table_layout_panel_game_directory.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33F));
            this.table_layout_panel_game_directory.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33F));
            this.table_layout_panel_game_directory.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.34F));
            this.table_layout_panel_game_directory.Size = new System.Drawing.Size(649, 105);
            this.table_layout_panel_game_directory.TabIndex = 3;
            // 
            // label_progress
            // 
            this.label_progress.AutoSize = true;
            this.label_progress.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label_progress.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_progress.Location = new System.Drawing.Point(3, 68);
            this.label_progress.Name = "label_progress";
            this.label_progress.Size = new System.Drawing.Size(104, 37);
            this.label_progress.TabIndex = 7;
            this.label_progress.Text = "0 / 0";
            this.label_progress.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_status
            // 
            this.label_status.AutoSize = true;
            this.label_status.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label_status.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_status.Location = new System.Drawing.Point(113, 68);
            this.label_status.Name = "label_status";
            this.label_status.Size = new System.Drawing.Size(423, 37);
            this.label_status.TabIndex = 6;
            this.label_status.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btn_scan
            // 
            this.btn_scan.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btn_scan.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btn_scan.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_scan.Location = new System.Drawing.Point(542, 37);
            this.btn_scan.Name = "btn_scan";
            this.btn_scan.Size = new System.Drawing.Size(104, 28);
            this.btn_scan.TabIndex = 5;
            this.btn_scan.Text = "Scan";
            this.btn_scan.UseVisualStyleBackColor = true;
            this.btn_scan.Click += new System.EventHandler(this.btn_scan_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.table_layout_panel_game_directory);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.listBox1);
            this.splitContainer1.Size = new System.Drawing.Size(649, 510);
            this.splitContainer1.SplitterDistance = 106;
            this.splitContainer1.TabIndex = 4;
            // 
            // listBox1
            // 
            this.listBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(0, 0);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(649, 400);
            this.listBox1.TabIndex = 0;
            // 
            // WizardInstallUniverseLANForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(649, 510);
            this.Controls.Add(this.splitContainer1);
            this.MinimumSize = new System.Drawing.Size(312, 270);
            this.Name = "WizardInstallUniverseLANForm";
            this.Text = "Install UniverseLAN";
            this.Load += new System.EventHandler(this.WizardInstallUniverseLANForm_Load);
            this.table_layout_panel_game_directory.ResumeLayout(false);
            this.table_layout_panel_game_directory.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox txtbox_game_directory;
        private System.Windows.Forms.Button btn_browse_game_directory;
        private System.Windows.Forms.Label label_game_directory;
        private System.Windows.Forms.TableLayoutPanel table_layout_panel_game_directory;
        private System.Windows.Forms.Button btn_scan;
        private System.Windows.Forms.Label label_status;
        private System.Windows.Forms.Label label_progress;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.ListBox listBox1;
    }
}

