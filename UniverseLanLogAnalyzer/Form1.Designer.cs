namespace UniverseLanLogAnalyzer
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            mainLayout = new TableLayoutPanel();
            groupBoxFiles = new GroupBox();
            filesLayout = new TableLayoutPanel();
            lblLeftFile = new Label();
            txtLeftPath = new TextBox();
            btnBrowseLeft = new Button();
            lblRightFile = new Label();
            txtRightPath = new TextBox();
            btnBrowseRight = new Button();
            btnLoadLogs = new Button();
            lblLoadState = new Label();
            groupBoxSelection = new GroupBox();
            selectionLayout = new TableLayoutPanel();
            lblProjection = new Label();
            cmbProjection = new ComboBox();
            leftSelectionGroup = new GroupBox();
            leftSelectionLayout = new TableLayoutPanel();
            lblLeftLobby = new Label();
            cmbLeftLobby = new ComboBox();
            lblLeftUser = new Label();
            cmbLeftUser = new ComboBox();
            lblLeftChannel = new Label();
            cmbLeftChannel = new ComboBox();
            rightSelectionGroup = new GroupBox();
            rightSelectionLayout = new TableLayoutPanel();
            lblRightLobby = new Label();
            cmbRightLobby = new ComboBox();
            lblRightUser = new Label();
            cmbRightUser = new ComboBox();
            lblRightChannel = new Label();
            cmbRightChannel = new ComboBox();
            btnCompare = new Button();
            resultsSplit = new SplitContainer();
            topResultsLayout = new TableLayoutPanel();
            summaryGroup = new GroupBox();
            txtSummary = new TextBox();
            changesGroup = new GroupBox();
            dgvComparison = new DataGridView();
            detailsGroup = new GroupBox();
            txtDetails = new TextBox();
            mainLayout.SuspendLayout();
            groupBoxFiles.SuspendLayout();
            filesLayout.SuspendLayout();
            groupBoxSelection.SuspendLayout();
            selectionLayout.SuspendLayout();
            leftSelectionGroup.SuspendLayout();
            leftSelectionLayout.SuspendLayout();
            rightSelectionGroup.SuspendLayout();
            rightSelectionLayout.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)resultsSplit).BeginInit();
            resultsSplit.Panel1.SuspendLayout();
            resultsSplit.Panel2.SuspendLayout();
            resultsSplit.SuspendLayout();
            topResultsLayout.SuspendLayout();
            summaryGroup.SuspendLayout();
            changesGroup.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dgvComparison).BeginInit();
            detailsGroup.SuspendLayout();
            SuspendLayout();
            // 
            // mainLayout
            // 
            mainLayout.ColumnCount = 1;
            mainLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            mainLayout.Controls.Add(groupBoxFiles, 0, 0);
            mainLayout.Controls.Add(groupBoxSelection, 0, 1);
            mainLayout.Controls.Add(resultsSplit, 0, 2);
            mainLayout.Dock = DockStyle.Fill;
            mainLayout.Location = new Point(0, 0);
            mainLayout.Margin = new Padding(2);
            mainLayout.Name = "mainLayout";
            mainLayout.RowCount = 3;
            mainLayout.RowStyles.Add(new RowStyle(SizeType.Absolute, 100F));
            mainLayout.RowStyles.Add(new RowStyle(SizeType.Absolute, 156F));
            mainLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            mainLayout.Size = new Size(1284, 782);
            mainLayout.TabIndex = 0;
            // 
            // groupBoxFiles
            // 
            groupBoxFiles.Controls.Add(filesLayout);
            groupBoxFiles.Dock = DockStyle.Fill;
            groupBoxFiles.Location = new Point(6, 5);
            groupBoxFiles.Margin = new Padding(6, 5, 6, 5);
            groupBoxFiles.Name = "groupBoxFiles";
            groupBoxFiles.Padding = new Padding(8, 7, 8, 7);
            groupBoxFiles.Size = new Size(1272, 90);
            groupBoxFiles.TabIndex = 0;
            groupBoxFiles.TabStop = false;
            groupBoxFiles.Text = "Logs";
            // 
            // filesLayout
            // 
            filesLayout.ColumnCount = 4;
            filesLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 50F));
            filesLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            filesLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 73F));
            filesLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 126F));
            filesLayout.Controls.Add(lblLeftFile, 0, 0);
            filesLayout.Controls.Add(txtLeftPath, 1, 0);
            filesLayout.Controls.Add(btnBrowseLeft, 2, 0);
            filesLayout.Controls.Add(lblRightFile, 0, 1);
            filesLayout.Controls.Add(txtRightPath, 1, 1);
            filesLayout.Controls.Add(btnBrowseRight, 2, 1);
            filesLayout.Controls.Add(btnLoadLogs, 3, 0);
            filesLayout.Controls.Add(lblLoadState, 3, 1);
            filesLayout.Dock = DockStyle.Fill;
            filesLayout.Location = new Point(8, 23);
            filesLayout.Margin = new Padding(2);
            filesLayout.Name = "filesLayout";
            filesLayout.RowCount = 2;
            filesLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            filesLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            filesLayout.Size = new Size(1256, 60);
            filesLayout.TabIndex = 0;
            // 
            // lblLeftFile
            // 
            lblLeftFile.Anchor = AnchorStyles.Left;
            lblLeftFile.AutoSize = true;
            lblLeftFile.Location = new Point(2, 7);
            lblLeftFile.Margin = new Padding(2, 0, 2, 0);
            lblLeftFile.Name = "lblLeftFile";
            lblLeftFile.Size = new Size(30, 15);
            lblLeftFile.TabIndex = 0;
            lblLeftFile.Text = "Left:";
            // 
            // txtLeftPath
            // 
            txtLeftPath.Dock = DockStyle.Fill;
            txtLeftPath.Location = new Point(52, 2);
            txtLeftPath.Margin = new Padding(2);
            txtLeftPath.Name = "txtLeftPath";
            txtLeftPath.Size = new Size(1003, 23);
            txtLeftPath.TabIndex = 1;
            // 
            // btnBrowseLeft
            // 
            btnBrowseLeft.Dock = DockStyle.Fill;
            btnBrowseLeft.Location = new Point(1059, 2);
            btnBrowseLeft.Margin = new Padding(2);
            btnBrowseLeft.Name = "btnBrowseLeft";
            btnBrowseLeft.Size = new Size(69, 26);
            btnBrowseLeft.TabIndex = 2;
            btnBrowseLeft.Text = "Browse...";
            btnBrowseLeft.UseVisualStyleBackColor = true;
            // 
            // lblRightFile
            // 
            lblRightFile.Anchor = AnchorStyles.Left;
            lblRightFile.AutoSize = true;
            lblRightFile.Location = new Point(2, 37);
            lblRightFile.Margin = new Padding(2, 0, 2, 0);
            lblRightFile.Name = "lblRightFile";
            lblRightFile.Size = new Size(38, 15);
            lblRightFile.TabIndex = 3;
            lblRightFile.Text = "Right:";
            // 
            // txtRightPath
            // 
            txtRightPath.Dock = DockStyle.Fill;
            txtRightPath.Location = new Point(52, 32);
            txtRightPath.Margin = new Padding(2);
            txtRightPath.Name = "txtRightPath";
            txtRightPath.Size = new Size(1003, 23);
            txtRightPath.TabIndex = 4;
            // 
            // btnBrowseRight
            // 
            btnBrowseRight.Dock = DockStyle.Fill;
            btnBrowseRight.Location = new Point(1059, 32);
            btnBrowseRight.Margin = new Padding(2);
            btnBrowseRight.Name = "btnBrowseRight";
            btnBrowseRight.Size = new Size(69, 26);
            btnBrowseRight.TabIndex = 5;
            btnBrowseRight.Text = "Browse...";
            btnBrowseRight.UseVisualStyleBackColor = true;
            // 
            // btnLoadLogs
            // 
            btnLoadLogs.Dock = DockStyle.Fill;
            btnLoadLogs.Location = new Point(1132, 2);
            btnLoadLogs.Margin = new Padding(2);
            btnLoadLogs.Name = "btnLoadLogs";
            btnLoadLogs.Size = new Size(122, 26);
            btnLoadLogs.TabIndex = 6;
            btnLoadLogs.Text = "Load / Rebuild";
            btnLoadLogs.UseVisualStyleBackColor = true;
            // 
            // lblLoadState
            // 
            lblLoadState.Anchor = AnchorStyles.Left;
            lblLoadState.AutoSize = true;
            lblLoadState.Location = new Point(1132, 37);
            lblLoadState.Margin = new Padding(2, 0, 2, 0);
            lblLoadState.Name = "lblLoadState";
            lblLoadState.Size = new Size(90, 15);
            lblLoadState.TabIndex = 7;
            lblLoadState.Text = "No logs loaded.";
            // 
            // groupBoxSelection
            // 
            groupBoxSelection.Controls.Add(selectionLayout);
            groupBoxSelection.Dock = DockStyle.Fill;
            groupBoxSelection.Location = new Point(6, 105);
            groupBoxSelection.Margin = new Padding(6, 5, 6, 5);
            groupBoxSelection.Name = "groupBoxSelection";
            groupBoxSelection.Padding = new Padding(8, 7, 8, 7);
            groupBoxSelection.Size = new Size(1272, 146);
            groupBoxSelection.TabIndex = 1;
            groupBoxSelection.TabStop = false;
            groupBoxSelection.Text = "Comparison target";
            // 
            // selectionLayout
            // 
            selectionLayout.ColumnCount = 3;
            selectionLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 168F));
            selectionLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            selectionLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            selectionLayout.Controls.Add(lblProjection, 0, 0);
            selectionLayout.Controls.Add(cmbProjection, 0, 1);
            selectionLayout.Controls.Add(leftSelectionGroup, 1, 0);
            selectionLayout.Controls.Add(rightSelectionGroup, 2, 0);
            selectionLayout.Controls.Add(btnCompare, 0, 2);
            selectionLayout.Dock = DockStyle.Fill;
            selectionLayout.Location = new Point(8, 23);
            selectionLayout.Margin = new Padding(2);
            selectionLayout.Name = "selectionLayout";
            selectionLayout.RowCount = 3;
            selectionLayout.RowStyles.Add(new RowStyle(SizeType.Absolute, 17F));
            selectionLayout.RowStyles.Add(new RowStyle(SizeType.Absolute, 25F));
            selectionLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            selectionLayout.Size = new Size(1256, 116);
            selectionLayout.TabIndex = 0;
            // 
            // lblProjection
            // 
            lblProjection.Anchor = AnchorStyles.Left;
            lblProjection.AutoSize = true;
            lblProjection.Location = new Point(2, 1);
            lblProjection.Margin = new Padding(2, 0, 2, 0);
            lblProjection.Name = "lblProjection";
            lblProjection.Size = new Size(108, 15);
            lblProjection.TabIndex = 0;
            lblProjection.Text = "Projection / stream";
            // 
            // cmbProjection
            // 
            cmbProjection.Dock = DockStyle.Top;
            cmbProjection.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbProjection.FormattingEnabled = true;
            cmbProjection.Location = new Point(2, 19);
            cmbProjection.Margin = new Padding(2);
            cmbProjection.Name = "cmbProjection";
            cmbProjection.Size = new Size(164, 23);
            cmbProjection.TabIndex = 1;
            // 
            // leftSelectionGroup
            // 
            leftSelectionGroup.Controls.Add(leftSelectionLayout);
            leftSelectionGroup.Dock = DockStyle.Fill;
            leftSelectionGroup.Location = new Point(170, 2);
            leftSelectionGroup.Margin = new Padding(2);
            leftSelectionGroup.Name = "leftSelectionGroup";
            leftSelectionGroup.Padding = new Padding(2);
            selectionLayout.SetRowSpan(leftSelectionGroup, 3);
            leftSelectionGroup.Size = new Size(540, 112);
            leftSelectionGroup.TabIndex = 2;
            leftSelectionGroup.TabStop = false;
            leftSelectionGroup.Text = "Left target";
            // 
            // leftSelectionLayout
            // 
            leftSelectionLayout.ColumnCount = 2;
            leftSelectionLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 56F));
            leftSelectionLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            leftSelectionLayout.Controls.Add(lblLeftLobby, 0, 0);
            leftSelectionLayout.Controls.Add(cmbLeftLobby, 1, 0);
            leftSelectionLayout.Controls.Add(lblLeftUser, 0, 1);
            leftSelectionLayout.Controls.Add(cmbLeftUser, 1, 1);
            leftSelectionLayout.Controls.Add(lblLeftChannel, 0, 2);
            leftSelectionLayout.Controls.Add(cmbLeftChannel, 1, 2);
            leftSelectionLayout.Dock = DockStyle.Fill;
            leftSelectionLayout.Location = new Point(2, 18);
            leftSelectionLayout.Margin = new Padding(2);
            leftSelectionLayout.Name = "leftSelectionLayout";
            leftSelectionLayout.RowCount = 3;
            leftSelectionLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
            leftSelectionLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
            leftSelectionLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
            leftSelectionLayout.Size = new Size(536, 92);
            leftSelectionLayout.TabIndex = 0;
            // 
            // lblLeftLobby
            // 
            lblLeftLobby.Anchor = AnchorStyles.Left;
            lblLeftLobby.AutoSize = true;
            lblLeftLobby.Location = new Point(2, 7);
            lblLeftLobby.Margin = new Padding(2, 0, 2, 0);
            lblLeftLobby.Name = "lblLeftLobby";
            lblLeftLobby.Size = new Size(40, 15);
            lblLeftLobby.TabIndex = 0;
            lblLeftLobby.Text = "Lobby";
            // 
            // cmbLeftLobby
            // 
            cmbLeftLobby.Dock = DockStyle.Top;
            cmbLeftLobby.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbLeftLobby.FormattingEnabled = true;
            cmbLeftLobby.Location = new Point(58, 2);
            cmbLeftLobby.Margin = new Padding(2);
            cmbLeftLobby.Name = "cmbLeftLobby";
            cmbLeftLobby.Size = new Size(476, 23);
            cmbLeftLobby.TabIndex = 1;
            // 
            // lblLeftUser
            // 
            lblLeftUser.Anchor = AnchorStyles.Left;
            lblLeftUser.AutoSize = true;
            lblLeftUser.Location = new Point(2, 37);
            lblLeftUser.Margin = new Padding(2, 0, 2, 0);
            lblLeftUser.Name = "lblLeftUser";
            lblLeftUser.Size = new Size(30, 15);
            lblLeftUser.TabIndex = 2;
            lblLeftUser.Text = "User";
            // 
            // cmbLeftUser
            // 
            cmbLeftUser.Dock = DockStyle.Top;
            cmbLeftUser.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbLeftUser.FormattingEnabled = true;
            cmbLeftUser.Location = new Point(58, 32);
            cmbLeftUser.Margin = new Padding(2);
            cmbLeftUser.Name = "cmbLeftUser";
            cmbLeftUser.Size = new Size(476, 23);
            cmbLeftUser.TabIndex = 3;
            // 
            // lblLeftChannel
            // 
            lblLeftChannel.Anchor = AnchorStyles.Left;
            lblLeftChannel.AutoSize = true;
            lblLeftChannel.Location = new Point(2, 68);
            lblLeftChannel.Margin = new Padding(2, 0, 2, 0);
            lblLeftChannel.Name = "lblLeftChannel";
            lblLeftChannel.Size = new Size(51, 15);
            lblLeftChannel.TabIndex = 4;
            lblLeftChannel.Text = "Channel";
            // 
            // cmbLeftChannel
            // 
            cmbLeftChannel.Dock = DockStyle.Top;
            cmbLeftChannel.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbLeftChannel.FormattingEnabled = true;
            cmbLeftChannel.Location = new Point(58, 62);
            cmbLeftChannel.Margin = new Padding(2);
            cmbLeftChannel.Name = "cmbLeftChannel";
            cmbLeftChannel.Size = new Size(476, 23);
            cmbLeftChannel.TabIndex = 5;
            // 
            // rightSelectionGroup
            // 
            rightSelectionGroup.Controls.Add(rightSelectionLayout);
            rightSelectionGroup.Dock = DockStyle.Fill;
            rightSelectionGroup.Location = new Point(714, 2);
            rightSelectionGroup.Margin = new Padding(2);
            rightSelectionGroup.Name = "rightSelectionGroup";
            rightSelectionGroup.Padding = new Padding(2);
            selectionLayout.SetRowSpan(rightSelectionGroup, 3);
            rightSelectionGroup.Size = new Size(540, 112);
            rightSelectionGroup.TabIndex = 3;
            rightSelectionGroup.TabStop = false;
            rightSelectionGroup.Text = "Right target";
            // 
            // rightSelectionLayout
            // 
            rightSelectionLayout.ColumnCount = 2;
            rightSelectionLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 56F));
            rightSelectionLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            rightSelectionLayout.Controls.Add(lblRightLobby, 0, 0);
            rightSelectionLayout.Controls.Add(cmbRightLobby, 1, 0);
            rightSelectionLayout.Controls.Add(lblRightUser, 0, 1);
            rightSelectionLayout.Controls.Add(cmbRightUser, 1, 1);
            rightSelectionLayout.Controls.Add(lblRightChannel, 0, 2);
            rightSelectionLayout.Controls.Add(cmbRightChannel, 1, 2);
            rightSelectionLayout.Dock = DockStyle.Fill;
            rightSelectionLayout.Location = new Point(2, 18);
            rightSelectionLayout.Margin = new Padding(2);
            rightSelectionLayout.Name = "rightSelectionLayout";
            rightSelectionLayout.RowCount = 3;
            rightSelectionLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
            rightSelectionLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
            rightSelectionLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
            rightSelectionLayout.Size = new Size(536, 92);
            rightSelectionLayout.TabIndex = 0;
            // 
            // lblRightLobby
            // 
            lblRightLobby.Anchor = AnchorStyles.Left;
            lblRightLobby.AutoSize = true;
            lblRightLobby.Location = new Point(2, 7);
            lblRightLobby.Margin = new Padding(2, 0, 2, 0);
            lblRightLobby.Name = "lblRightLobby";
            lblRightLobby.Size = new Size(40, 15);
            lblRightLobby.TabIndex = 0;
            lblRightLobby.Text = "Lobby";
            // 
            // cmbRightLobby
            // 
            cmbRightLobby.Dock = DockStyle.Top;
            cmbRightLobby.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbRightLobby.FormattingEnabled = true;
            cmbRightLobby.Location = new Point(58, 2);
            cmbRightLobby.Margin = new Padding(2);
            cmbRightLobby.Name = "cmbRightLobby";
            cmbRightLobby.Size = new Size(476, 23);
            cmbRightLobby.TabIndex = 1;
            // 
            // lblRightUser
            // 
            lblRightUser.Anchor = AnchorStyles.Left;
            lblRightUser.AutoSize = true;
            lblRightUser.Location = new Point(2, 37);
            lblRightUser.Margin = new Padding(2, 0, 2, 0);
            lblRightUser.Name = "lblRightUser";
            lblRightUser.Size = new Size(30, 15);
            lblRightUser.TabIndex = 2;
            lblRightUser.Text = "User";
            // 
            // cmbRightUser
            // 
            cmbRightUser.Dock = DockStyle.Top;
            cmbRightUser.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbRightUser.FormattingEnabled = true;
            cmbRightUser.Location = new Point(58, 32);
            cmbRightUser.Margin = new Padding(2);
            cmbRightUser.Name = "cmbRightUser";
            cmbRightUser.Size = new Size(476, 23);
            cmbRightUser.TabIndex = 3;
            // 
            // lblRightChannel
            // 
            lblRightChannel.Anchor = AnchorStyles.Left;
            lblRightChannel.AutoSize = true;
            lblRightChannel.Location = new Point(2, 68);
            lblRightChannel.Margin = new Padding(2, 0, 2, 0);
            lblRightChannel.Name = "lblRightChannel";
            lblRightChannel.Size = new Size(51, 15);
            lblRightChannel.TabIndex = 4;
            lblRightChannel.Text = "Channel";
            // 
            // cmbRightChannel
            // 
            cmbRightChannel.Dock = DockStyle.Top;
            cmbRightChannel.DropDownStyle = ComboBoxStyle.DropDownList;
            cmbRightChannel.FormattingEnabled = true;
            cmbRightChannel.Location = new Point(58, 62);
            cmbRightChannel.Margin = new Padding(2);
            cmbRightChannel.Name = "cmbRightChannel";
            cmbRightChannel.Size = new Size(476, 23);
            cmbRightChannel.TabIndex = 5;
            // 
            // btnCompare
            // 
            btnCompare.Dock = DockStyle.Top;
            btnCompare.Location = new Point(2, 44);
            btnCompare.Margin = new Padding(2);
            btnCompare.Name = "btnCompare";
            btnCompare.Size = new Size(164, 20);
            btnCompare.TabIndex = 4;
            btnCompare.Text = "Compare selected targets";
            btnCompare.UseVisualStyleBackColor = true;
            // 
            // resultsSplit
            // 
            resultsSplit.Dock = DockStyle.Fill;
            resultsSplit.Location = new Point(6, 261);
            resultsSplit.Margin = new Padding(6, 5, 6, 5);
            resultsSplit.Name = "resultsSplit";
            resultsSplit.Orientation = Orientation.Horizontal;
            // 
            // resultsSplit.Panel1
            // 
            resultsSplit.Panel1.Controls.Add(topResultsLayout);
            // 
            // resultsSplit.Panel2
            // 
            resultsSplit.Panel2.Controls.Add(detailsGroup);
            resultsSplit.Size = new Size(1272, 516);
            resultsSplit.SplitterDistance = 330;
            resultsSplit.SplitterWidth = 2;
            resultsSplit.TabIndex = 2;
            // 
            // topResultsLayout
            // 
            topResultsLayout.ColumnCount = 2;
            topResultsLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 252F));
            topResultsLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            topResultsLayout.Controls.Add(summaryGroup, 0, 0);
            topResultsLayout.Controls.Add(changesGroup, 1, 0);
            topResultsLayout.Dock = DockStyle.Fill;
            topResultsLayout.Location = new Point(0, 0);
            topResultsLayout.Margin = new Padding(2);
            topResultsLayout.Name = "topResultsLayout";
            topResultsLayout.RowCount = 1;
            topResultsLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            topResultsLayout.Size = new Size(1272, 330);
            topResultsLayout.TabIndex = 0;
            // 
            // summaryGroup
            // 
            summaryGroup.Controls.Add(txtSummary);
            summaryGroup.Dock = DockStyle.Fill;
            summaryGroup.Location = new Point(2, 2);
            summaryGroup.Margin = new Padding(2);
            summaryGroup.Name = "summaryGroup";
            summaryGroup.Padding = new Padding(2);
            summaryGroup.Size = new Size(248, 326);
            summaryGroup.TabIndex = 0;
            summaryGroup.TabStop = false;
            summaryGroup.Text = "Summary";
            // 
            // txtSummary
            // 
            txtSummary.Dock = DockStyle.Fill;
            txtSummary.Location = new Point(2, 18);
            txtSummary.Margin = new Padding(2);
            txtSummary.Multiline = true;
            txtSummary.Name = "txtSummary";
            txtSummary.ReadOnly = true;
            txtSummary.ScrollBars = ScrollBars.Vertical;
            txtSummary.Size = new Size(244, 306);
            txtSummary.TabIndex = 0;
            // 
            // changesGroup
            // 
            changesGroup.Controls.Add(dgvComparison);
            changesGroup.Dock = DockStyle.Fill;
            changesGroup.Location = new Point(254, 2);
            changesGroup.Margin = new Padding(2);
            changesGroup.Name = "changesGroup";
            changesGroup.Padding = new Padding(2);
            changesGroup.Size = new Size(1016, 326);
            changesGroup.TabIndex = 1;
            changesGroup.TabStop = false;
            changesGroup.Text = "Change by change comparison";
            // 
            // dgvComparison
            // 
            dgvComparison.AllowUserToAddRows = false;
            dgvComparison.AllowUserToDeleteRows = false;
            dgvComparison.AllowUserToResizeRows = false;
            dgvComparison.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvComparison.Dock = DockStyle.Fill;
            dgvComparison.Location = new Point(2, 18);
            dgvComparison.Margin = new Padding(2);
            dgvComparison.MultiSelect = false;
            dgvComparison.Name = "dgvComparison";
            dgvComparison.ReadOnly = true;
            dgvComparison.RowHeadersVisible = false;
            dgvComparison.RowTemplate.Height = 33;
            dgvComparison.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvComparison.Size = new Size(1012, 306);
            dgvComparison.TabIndex = 0;
            // 
            // detailsGroup
            // 
            detailsGroup.Controls.Add(txtDetails);
            detailsGroup.Dock = DockStyle.Fill;
            detailsGroup.Location = new Point(0, 0);
            detailsGroup.Margin = new Padding(2);
            detailsGroup.Name = "detailsGroup";
            detailsGroup.Padding = new Padding(2);
            detailsGroup.Size = new Size(1272, 184);
            detailsGroup.TabIndex = 0;
            detailsGroup.TabStop = false;
            detailsGroup.Text = "Selected change details";
            // 
            // txtDetails
            // 
            txtDetails.Dock = DockStyle.Fill;
            txtDetails.Font = new Font("Consolas", 10F);
            txtDetails.Location = new Point(2, 18);
            txtDetails.Margin = new Padding(2);
            txtDetails.Multiline = true;
            txtDetails.Name = "txtDetails";
            txtDetails.ReadOnly = true;
            txtDetails.ScrollBars = ScrollBars.Both;
            txtDetails.Size = new Size(1268, 164);
            txtDetails.TabIndex = 0;
            txtDetails.WordWrap = false;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1284, 782);
            Controls.Add(mainLayout);
            Margin = new Padding(2);
            MinimumSize = new Size(845, 472);
            Name = "Form1";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "UniverseLan Log Analyzer - Comparer";
            mainLayout.ResumeLayout(false);
            groupBoxFiles.ResumeLayout(false);
            filesLayout.ResumeLayout(false);
            filesLayout.PerformLayout();
            groupBoxSelection.ResumeLayout(false);
            selectionLayout.ResumeLayout(false);
            selectionLayout.PerformLayout();
            leftSelectionGroup.ResumeLayout(false);
            leftSelectionLayout.ResumeLayout(false);
            leftSelectionLayout.PerformLayout();
            rightSelectionGroup.ResumeLayout(false);
            rightSelectionLayout.ResumeLayout(false);
            rightSelectionLayout.PerformLayout();
            resultsSplit.Panel1.ResumeLayout(false);
            resultsSplit.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)resultsSplit).EndInit();
            resultsSplit.ResumeLayout(false);
            topResultsLayout.ResumeLayout(false);
            summaryGroup.ResumeLayout(false);
            summaryGroup.PerformLayout();
            changesGroup.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)dgvComparison).EndInit();
            detailsGroup.ResumeLayout(false);
            detailsGroup.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel mainLayout;
        private GroupBox groupBoxFiles;
        private TableLayoutPanel filesLayout;
        private Label lblLeftFile;
        private TextBox txtLeftPath;
        private Button btnBrowseLeft;
        private Label lblRightFile;
        private TextBox txtRightPath;
        private Button btnBrowseRight;
        private Button btnLoadLogs;
        private Label lblLoadState;
        private GroupBox groupBoxSelection;
        private TableLayoutPanel selectionLayout;
        private Label lblProjection;
        private ComboBox cmbProjection;
        private GroupBox leftSelectionGroup;
        private TableLayoutPanel leftSelectionLayout;
        private Label lblLeftLobby;
        private ComboBox cmbLeftLobby;
        private Label lblLeftUser;
        private ComboBox cmbLeftUser;
        private Label lblLeftChannel;
        private ComboBox cmbLeftChannel;
        private GroupBox rightSelectionGroup;
        private TableLayoutPanel rightSelectionLayout;
        private Label lblRightLobby;
        private ComboBox cmbRightLobby;
        private Label lblRightUser;
        private ComboBox cmbRightUser;
        private Label lblRightChannel;
        private ComboBox cmbRightChannel;
        private Button btnCompare;
        private SplitContainer resultsSplit;
        private TableLayoutPanel topResultsLayout;
        private GroupBox summaryGroup;
        private TextBox txtSummary;
        private GroupBox changesGroup;
        private DataGridView dgvComparison;
        private GroupBox detailsGroup;
        private TextBox txtDetails;
    }
}
