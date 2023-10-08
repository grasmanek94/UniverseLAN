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
            txtbox_game_directory = new System.Windows.Forms.TextBox();
            btn_browse_game_directory = new System.Windows.Forms.Button();
            label_game_directory = new System.Windows.Forms.Label();
            table_layout_panel_game_directory = new System.Windows.Forms.TableLayoutPanel();
            label_progress = new System.Windows.Forms.Label();
            label_status = new System.Windows.Forms.Label();
            btn_scan = new System.Windows.Forms.Button();
            splitContainer1 = new System.Windows.Forms.SplitContainer();
            listBox1 = new System.Windows.Forms.ListBox();
            table_layout_panel_game_directory.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer1).BeginInit();
            splitContainer1.Panel1.SuspendLayout();
            splitContainer1.Panel2.SuspendLayout();
            splitContainer1.SuspendLayout();
            SuspendLayout();
            // 
            // txtbox_game_directory
            // 
            txtbox_game_directory.AllowDrop = true;
            txtbox_game_directory.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
            txtbox_game_directory.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
            txtbox_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            txtbox_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            txtbox_game_directory.Location = new System.Drawing.Point(116, 3);
            txtbox_game_directory.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            txtbox_game_directory.Name = "txtbox_game_directory";
            txtbox_game_directory.Size = new System.Drawing.Size(508, 22);
            txtbox_game_directory.TabIndex = 0;
            txtbox_game_directory.WordWrap = false;
            txtbox_game_directory.TextChanged += txtbox_game_directory_TextChanged;
            // 
            // btn_browse_game_directory
            // 
            btn_browse_game_directory.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            btn_browse_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            btn_browse_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            btn_browse_game_directory.Location = new System.Drawing.Point(632, 3);
            btn_browse_game_directory.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            btn_browse_game_directory.Name = "btn_browse_game_directory";
            btn_browse_game_directory.Size = new System.Drawing.Size(121, 34);
            btn_browse_game_directory.TabIndex = 1;
            btn_browse_game_directory.Text = "Browse...";
            btn_browse_game_directory.UseVisualStyleBackColor = true;
            btn_browse_game_directory.Click += btn_browse_game_directory_Click;
            // 
            // label_game_directory
            // 
            label_game_directory.AutoSize = true;
            label_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            label_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            label_game_directory.Location = new System.Drawing.Point(4, 0);
            label_game_directory.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            label_game_directory.Name = "label_game_directory";
            label_game_directory.Size = new System.Drawing.Size(104, 40);
            label_game_directory.TabIndex = 2;
            label_game_directory.Text = "Game Directory:";
            label_game_directory.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // table_layout_panel_game_directory
            // 
            table_layout_panel_game_directory.ColumnCount = 3;
            table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            table_layout_panel_game_directory.Controls.Add(label_progress, 0, 2);
            table_layout_panel_game_directory.Controls.Add(label_status, 0, 2);
            table_layout_panel_game_directory.Controls.Add(btn_browse_game_directory, 2, 0);
            table_layout_panel_game_directory.Controls.Add(txtbox_game_directory, 1, 0);
            table_layout_panel_game_directory.Controls.Add(label_game_directory, 0, 0);
            table_layout_panel_game_directory.Controls.Add(btn_scan, 2, 1);
            table_layout_panel_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            table_layout_panel_game_directory.Location = new System.Drawing.Point(0, 0);
            table_layout_panel_game_directory.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            table_layout_panel_game_directory.MaximumSize = new System.Drawing.Size(0, 121);
            table_layout_panel_game_directory.MinimumSize = new System.Drawing.Size(0, 121);
            table_layout_panel_game_directory.Name = "table_layout_panel_game_directory";
            table_layout_panel_game_directory.RowCount = 3;
            table_layout_panel_game_directory.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33F));
            table_layout_panel_game_directory.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33F));
            table_layout_panel_game_directory.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.34F));
            table_layout_panel_game_directory.Size = new System.Drawing.Size(757, 121);
            table_layout_panel_game_directory.TabIndex = 3;
            // 
            // label_progress
            // 
            label_progress.AutoSize = true;
            label_progress.Dock = System.Windows.Forms.DockStyle.Fill;
            label_progress.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            label_progress.Location = new System.Drawing.Point(4, 80);
            label_progress.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            label_progress.Name = "label_progress";
            label_progress.Size = new System.Drawing.Size(104, 41);
            label_progress.TabIndex = 7;
            label_progress.Text = "0 / 0";
            label_progress.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_status
            // 
            label_status.AutoSize = true;
            label_status.Dock = System.Windows.Forms.DockStyle.Fill;
            label_status.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            label_status.Location = new System.Drawing.Point(116, 80);
            label_status.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            label_status.Name = "label_status";
            label_status.Size = new System.Drawing.Size(508, 41);
            label_status.TabIndex = 6;
            label_status.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btn_scan
            // 
            btn_scan.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            btn_scan.Dock = System.Windows.Forms.DockStyle.Fill;
            btn_scan.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            btn_scan.Location = new System.Drawing.Point(632, 43);
            btn_scan.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            btn_scan.Name = "btn_scan";
            btn_scan.Size = new System.Drawing.Size(121, 34);
            btn_scan.TabIndex = 5;
            btn_scan.Text = "Scan";
            btn_scan.UseVisualStyleBackColor = true;
            btn_scan.Click += btn_scan_Click;
            // 
            // splitContainer1
            // 
            splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            splitContainer1.IsSplitterFixed = true;
            splitContainer1.Location = new System.Drawing.Point(0, 0);
            splitContainer1.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            splitContainer1.Name = "splitContainer1";
            splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            splitContainer1.Panel1.Controls.Add(table_layout_panel_game_directory);
            // 
            // splitContainer1.Panel2
            // 
            splitContainer1.Panel2.Controls.Add(listBox1);
            splitContainer1.Size = new System.Drawing.Size(757, 588);
            splitContainer1.SplitterDistance = 125;
            splitContainer1.SplitterWidth = 5;
            splitContainer1.TabIndex = 4;
            // 
            // listBox1
            // 
            listBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            listBox1.FormattingEnabled = true;
            listBox1.ItemHeight = 15;
            listBox1.Location = new System.Drawing.Point(0, 0);
            listBox1.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            listBox1.Name = "listBox1";
            listBox1.Size = new System.Drawing.Size(757, 458);
            listBox1.TabIndex = 0;
            // 
            // WizardInstallUniverseLANForm
            // 
            AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            ClientSize = new System.Drawing.Size(757, 588);
            Controls.Add(splitContainer1);
            Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            MinimumSize = new System.Drawing.Size(361, 306);
            Name = "WizardInstallUniverseLANForm";
            Text = "Install UniverseLAN";
            Load += WizardInstallUniverseLANForm_Load;
            table_layout_panel_game_directory.ResumeLayout(false);
            table_layout_panel_game_directory.PerformLayout();
            splitContainer1.Panel1.ResumeLayout(false);
            splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)splitContainer1).EndInit();
            splitContainer1.ResumeLayout(false);
            ResumeLayout(false);
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

