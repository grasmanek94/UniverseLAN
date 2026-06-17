using UniverseLanLogAnalyzer.Compare;

namespace UniverseLanLogAnalyzer
{
    public partial class Form1 : Form
    {
        private static readonly IReadOnlyList<(ComparisonTargetType Value, string Text)> ProjectionChoices = new[]
        {
            (ComparisonTargetType.Lobby, "Lobby"),
            (ComparisonTargetType.LobbyData, "Lobby Data"),
            (ComparisonTargetType.LobbyMemberData, "Lobby Member Data"),
            (ComparisonTargetType.P2PChannel, "P2P Channel"),
            (ComparisonTargetType.LobbyList, "Lobby List"),
            (ComparisonTargetType.UserInformation, "User Information"),
            (ComparisonTargetType.UserStats, "User Stats"),
            (ComparisonTargetType.UserAchievements, "User Achievements")
        };

        private ParsedLogDocument? _leftDocument;
        private ParsedLogDocument? _rightDocument;
        private ComparisonResult? _lastResult;

        public Form1()
        {
            InitializeComponent();
            InitializeProjectionCombo();
            HookEvents();
        }

        private void HookEvents()
        {
            btnBrowseLeft.Click += (_, _) => BrowseForLog(txtLeftPath);
            btnBrowseRight.Click += (_, _) => BrowseForLog(txtRightPath);
            btnLoadLogs.Click += (_, _) => LoadLogs();
            btnCompare.Click += (_, _) => RunCompare();
            cmbProjection.SelectedIndexChanged += (_, _) => RefreshSelectors();
            cmbLeftLobby.SelectedIndexChanged += (_, _) => OnLobbySelectionChanged(isLeft: true);
            cmbRightLobby.SelectedIndexChanged += (_, _) => OnLobbySelectionChanged(isLeft: false);
            dgvComparison.SelectionChanged += (_, _) => UpdateSelectedChangeDetails();
        }

        private void InitializeProjectionCombo()
        {
            cmbProjection.DisplayMember = nameof(ComboItem<ComparisonTargetType>.Text);
            cmbProjection.ValueMember = nameof(ComboItem<ComparisonTargetType>.Value);
            cmbProjection.Items.Clear();
            foreach (var choice in ProjectionChoices)
            {
                cmbProjection.Items.Add(new ComboItem<ComparisonTargetType>(choice.Value, choice.Text));
            }

            if (cmbProjection.Items.Count > 0)
            {
                cmbProjection.SelectedIndex = 0;
            }

            dgvComparison.AutoGenerateColumns = false;
            dgvComparison.Columns.Clear();
            dgvComparison.Columns.Add(new DataGridViewTextBoxColumn
            {
                Name = "Ordinal",
                HeaderText = "#",
                DataPropertyName = nameof(ComparedChange.Ordinal),
                Width = 48,
                ReadOnly = true
            });
            dgvComparison.Columns.Add(new DataGridViewTextBoxColumn
            {
                Name = "Status",
                HeaderText = "Status",
                DataPropertyName = nameof(ComparedChange.StatusText),
                Width = 96,
                ReadOnly = true
            });
            dgvComparison.Columns.Add(new DataGridViewTextBoxColumn
            {
                Name = "LeftDescription",
                HeaderText = "Left Change",
                DataPropertyName = nameof(ComparedChange.LeftShort),
                AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill,
                FillWeight = 50,
                ReadOnly = true
            });
            dgvComparison.Columns.Add(new DataGridViewTextBoxColumn
            {
                Name = "RightDescription",
                HeaderText = "Right Change",
                DataPropertyName = nameof(ComparedChange.RightShort),
                AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill,
                FillWeight = 50,
                ReadOnly = true
            });
        }

        private void BrowseForLog(TextBox target)
        {
            using OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Log files (*.log)|*.log|All files (*.*)|*.*";
            dialog.CheckFileExists = true;
            dialog.Multiselect = false;
            if (dialog.ShowDialog(this) == DialogResult.OK)
            {
                target.Text = dialog.FileName;
            }
        }

        private void LoadLogs()
        {
            string leftPath = txtLeftPath.Text.Trim();
            string rightPath = txtRightPath.Text.Trim();

            if (!File.Exists(leftPath))
            {
                MessageBox.Show(this, "Select a valid left log file.", "Missing file", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (!File.Exists(rightPath))
            {
                MessageBox.Show(this, "Select a valid right log file.", "Missing file", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            try
            {
                UseWaitCursor = true;
                Enabled = false;
                _leftDocument = ParsedLogDocument.Load(leftPath);
                _rightDocument = ParsedLogDocument.Load(rightPath);
                lblLoadState.Text = $"Loaded {Path.GetFileName(leftPath)} and {Path.GetFileName(rightPath)}";
                RefreshSelectors();
                RunCompare();
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.ToString(), "Failed to load log(s)", MessageBoxButtons.OK, MessageBoxIcon.Error);
                lblLoadState.Text = "Load failed.";
            }
            finally
            {
                Enabled = true;
                UseWaitCursor = false;
            }
        }

        private void RefreshSelectors()
        {
            ComparisonTargetType projection = GetSelectedProjection();
            PopulateSideSelectors(_leftDocument, true, projection);
            PopulateSideSelectors(_rightDocument, false, projection);
            ApplySelectorVisibility(projection);
            btnCompare.Enabled = _leftDocument != null && _rightDocument != null;
        }

        private void OnLobbySelectionChanged(bool isLeft)
        {
            if (GetSelectedProjection() != ComparisonTargetType.LobbyMemberData)
            {
                return;
            }

            ParsedLogDocument? document = isLeft ? _leftDocument : _rightDocument;
            ComboBox lobbyCombo = isLeft ? cmbLeftLobby : cmbRightLobby;
            ComboBox userCombo = isLeft ? cmbLeftUser : cmbRightUser;

            var selectedLobby = GetSelectedComboValue<ulong>(lobbyCombo);
            PopulateLobbyMemberUsers(document, userCombo, selectedLobby);
        }

        private void PopulateSideSelectors(ParsedLogDocument? doc, bool isLeft, ComparisonTargetType target)
        {
            ComboBox lobbyCombo = isLeft ? cmbLeftLobby : cmbRightLobby;
            ComboBox userCombo = isLeft ? cmbLeftUser : cmbRightUser;
            ComboBox channelCombo = isLeft ? cmbLeftChannel : cmbRightChannel;

            PopulateLobbyChoices(doc, lobbyCombo, target);
            PopulateUserChoices(doc, userCombo, target);
            PopulateChannelChoices(doc, channelCombo, target);

            if (target == ComparisonTargetType.LobbyMemberData)
            {
                var selectedLobby = GetSelectedComboValue<ulong>(lobbyCombo);
                PopulateLobbyMemberUsers(doc, userCombo, selectedLobby);
            }
        }

        private void PopulateLobbyChoices(ParsedLogDocument? doc, ComboBox combo, ComparisonTargetType target)
        {
            combo.BeginUpdate();
            try
            {
                object? previous = combo.SelectedItem;
                combo.DisplayMember = nameof(ComboItem<ulong>.Text);
                combo.ValueMember = nameof(ComboItem<ulong>.Value);
                combo.Items.Clear();

                if (doc == null)
                {
                    return;
                }

                IEnumerable<ulong> source = target switch
                {
                    ComparisonTargetType.Lobby => doc.Projections.Lobby.ByLobbyId.Keys,
                    ComparisonTargetType.LobbyData => doc.Projections.LobbyData.ByLobbyId.Keys,
                    ComparisonTargetType.LobbyMemberData => doc.Projections.LobbyMemberData.ByLobbyId.Keys,
                    _ => Array.Empty<ulong>()
                };

                foreach (ulong lobbyId in source.OrderBy(x => x))
                {
                    combo.Items.Add(new ComboItem<ulong>(lobbyId, $"{lobbyId}"));
                }

                if (combo.Items.Count > 0)
                {
                    combo.SelectedIndex = 0;
                }
            }
            finally
            {
                combo.EndUpdate();
            }
        }

        private void PopulateUserChoices(ParsedLogDocument? doc, ComboBox combo, ComparisonTargetType target)
        {
            combo.BeginUpdate();
            try
            {
                combo.DisplayMember = nameof(ComboItem<ulong>.Text);
                combo.ValueMember = nameof(ComboItem<ulong>.Value);
                combo.Items.Clear();

                if (doc == null)
                {
                    return;
                }

                IEnumerable<ulong> ids = target switch
                {
                    ComparisonTargetType.UserInformation => doc.Projections.UserInformation.ByUserId.Keys,
                    ComparisonTargetType.UserStats => doc.Projections.UserStats.ByUserId.Keys,
                    ComparisonTargetType.UserAchievements => doc.Projections.UserAchievements.ByUserId.Keys,
                    _ => Array.Empty<ulong>()
                };

                foreach (ulong userId in ids.OrderBy(x => x))
                {
                    combo.Items.Add(new ComboItem<ulong>(userId, $"{userId}"));
                }

                if (combo.Items.Count > 0)
                {
                    combo.SelectedIndex = 0;
                }
            }
            finally
            {
                combo.EndUpdate();
            }
        }

        private void PopulateLobbyMemberUsers(ParsedLogDocument? doc, ComboBox combo, ulong? lobbyId)
        {
            combo.BeginUpdate();
            try
            {
                combo.DisplayMember = nameof(ComboItem<ulong>.Text);
                combo.ValueMember = nameof(ComboItem<ulong>.Value);
                combo.Items.Clear();

                if (doc == null || !lobbyId.HasValue)
                {
                    return;
                }

                if (!doc.Projections.LobbyMemberData.ByLobbyId.TryGetValue(lobbyId.Value, out var members))
                {
                    return;
                }

                foreach (ulong userId in members.Keys.OrderBy(x => x))
                {
                    combo.Items.Add(new ComboItem<ulong>(userId, $"{userId}"));
                }

                if (combo.Items.Count > 0)
                {
                    combo.SelectedIndex = 0;
                }
            }
            finally
            {
                combo.EndUpdate();
            }
        }

        private void PopulateChannelChoices(ParsedLogDocument? doc, ComboBox combo, ComparisonTargetType target)
        {
            combo.BeginUpdate();
            try
            {
                combo.DisplayMember = nameof(ComboItem<int>.Text);
                combo.ValueMember = nameof(ComboItem<int>.Value);
                combo.Items.Clear();

                if (doc == null || target != ComparisonTargetType.P2PChannel)
                {
                    return;
                }

                foreach (int channel in doc.Projections.P2PNetworkingPacket.ByChannel.Keys.OrderBy(x => x))
                {
                    combo.Items.Add(new ComboItem<int>(channel, channel.ToString()));
                }

                if (combo.Items.Count > 0)
                {
                    combo.SelectedIndex = 0;
                }
            }
            finally
            {
                combo.EndUpdate();
            }
        }

        private void ApplySelectorVisibility(ComparisonTargetType target)
        {
            bool needsLobby = target is ComparisonTargetType.Lobby or ComparisonTargetType.LobbyData or ComparisonTargetType.LobbyMemberData;
            bool needsUser = target is ComparisonTargetType.UserInformation or ComparisonTargetType.UserStats or ComparisonTargetType.UserAchievements or ComparisonTargetType.LobbyMemberData;
            bool needsChannel = target == ComparisonTargetType.P2PChannel;

            lblLeftLobby.Visible = cmbLeftLobby.Visible = needsLobby;
            lblRightLobby.Visible = cmbRightLobby.Visible = needsLobby;
            lblLeftUser.Visible = cmbLeftUser.Visible = needsUser;
            lblRightUser.Visible = cmbRightUser.Visible = needsUser;
            lblLeftChannel.Visible = cmbLeftChannel.Visible = needsChannel;
            lblRightChannel.Visible = cmbRightChannel.Visible = needsChannel;
        }

        private void RunCompare()
        {
            if (_leftDocument == null || _rightDocument == null)
            {
                return;
            }

            try
            {
                ProjectionSelection leftSelection = BuildSelection(isLeft: true);
                ProjectionSelection rightSelection = BuildSelection(isLeft: false);

                _lastResult = ProjectionComparisonEngine.Compare(_leftDocument, leftSelection, _rightDocument, rightSelection);
                dgvComparison.DataSource = _lastResult.Changes;
                txtSummary.Text = _lastResult.Summary;
                if (dgvComparison.Rows.Count > 0)
                {
                    dgvComparison.Rows[0].Selected = true;
                }
                else
                {
                    txtDetails.Text = "No state changes were captured for the selected targets.";
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.Message, "Comparison failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private ProjectionSelection BuildSelection(bool isLeft)
        {
            ComparisonTargetType target = GetSelectedProjection();
            var selection = new ProjectionSelection { TargetType = target };

            ComboBox lobbyCombo = isLeft ? cmbLeftLobby : cmbRightLobby;
            ComboBox userCombo = isLeft ? cmbLeftUser : cmbRightUser;
            ComboBox channelCombo = isLeft ? cmbLeftChannel : cmbRightChannel;

            if (target is ComparisonTargetType.Lobby or ComparisonTargetType.LobbyData or ComparisonTargetType.LobbyMemberData)
            {
                selection.LobbyId = GetRequiredUInt64(lobbyCombo, isLeft ? "left lobby" : "right lobby");
            }

            if (target is ComparisonTargetType.UserInformation or ComparisonTargetType.UserStats or ComparisonTargetType.UserAchievements or ComparisonTargetType.LobbyMemberData)
            {
                selection.UserId = GetRequiredUInt64(userCombo, isLeft ? "left user" : "right user");
            }

            if (target == ComparisonTargetType.P2PChannel)
            {
                selection.Channel = GetRequiredInt32(channelCombo, isLeft ? "left channel" : "right channel");
            }

            return selection;
        }

        private static ulong GetRequiredUInt64(ComboBox combo, string description)
        {
            if (combo.SelectedItem is ComboItem<ulong> item)
            {
                return item.Value;
            }

            throw new InvalidOperationException($"Select a {description} before comparing.");
        }

        private static int GetRequiredInt32(ComboBox combo, string description)
        {
            if (combo.SelectedItem is ComboItem<int> item)
            {
                return item.Value;
            }

            throw new InvalidOperationException($"Select a {description} before comparing.");
        }

        private static ulong? GetSelectedComboValue<T>(ComboBox combo)
        {
            if (typeof(T) == typeof(ulong) && combo.SelectedItem is ComboItem<ulong> ulongItem)
            {
                return ulongItem.Value;
            }

            return null;
        }

        private ComparisonTargetType GetSelectedProjection()
        {
            if (cmbProjection.SelectedItem is ComboItem<ComparisonTargetType> item)
            {
                return item.Value;
            }

            return ComparisonTargetType.Lobby;
        }

        private void UpdateSelectedChangeDetails()
        {
            if (_lastResult == null)
            {
                txtDetails.Text = string.Empty;
                return;
            }

            if (dgvComparison.CurrentRow?.DataBoundItem is not ComparedChange change)
            {
                txtDetails.Text = string.Empty;
                return;
            }

            txtDetails.Text = change.BuildDetailedText();
        }

        private sealed class ComboItem<T>
        {
            public ComboItem(T value, string text)
            {
                Value = value;
                Text = text;
            }

            public T Value { get; }
            public string Text { get; }
            public override string ToString() => Text;
        }
    }
}
