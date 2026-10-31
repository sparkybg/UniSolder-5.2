using System.Windows.Forms;

namespace UniSolder
{
    partial class Form1:Form
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
            this.mainLayout = new System.Windows.Forms.TableLayoutPanel();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.connStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.logStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.SsChart2 = new SSControls.SSChart();
            this.panel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.checkBox4 = new System.Windows.Forms.CheckBox();
            this.checkBox6 = new System.Windows.Forms.CheckBox();
            this.checkBox7 = new System.Windows.Forms.CheckBox();
            this.checkBox8 = new System.Windows.Forms.CheckBox();
            this.checkBox9 = new System.Windows.Forms.CheckBox();
            this.checkBox10 = new System.Windows.Forms.CheckBox();
            this.checkBox11 = new System.Windows.Forms.CheckBox();
            this.bottomPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.buttonsPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.Button8 = new System.Windows.Forms.Button();
            this.Button6 = new System.Windows.Forms.Button();
            this.Button3 = new System.Windows.Forms.Button();
            this.GPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.GTrackBar = new System.Windows.Forms.TrackBar();
            this.GLabel = new System.Windows.Forms.Label();
            this.OVFGPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.OVFGTrackBar = new System.Windows.Forms.TrackBar();
            this.OVFGLabel = new System.Windows.Forms.Label();
            this.KpPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.KpTrackBar = new System.Windows.Forms.TrackBar();
            this.KpLabel = new System.Windows.Forms.Label();
            this.KiPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.KiTrackBar = new System.Windows.Forms.TrackBar();
            this.KiLabel = new System.Windows.Forms.Label();
            this.DGPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.DGTrackBar = new System.Windows.Forms.TrackBar();
            this.DGLabel = new System.Windows.Forms.Label();
            this.mainLayout.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.bottomPanel.SuspendLayout();
            this.buttonsPanel.SuspendLayout();
            this.GPanel.SuspendLayout();
            this.OVFGPanel.SuspendLayout();
            this.KpPanel.SuspendLayout();
            this.KiPanel.SuspendLayout();
            this.DGPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.GTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.OVFGTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.KpTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.KiTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DGTrackBar)).BeginInit();
            this.SuspendLayout();
            //
            // mainLayout
            //
            this.mainLayout.ColumnCount = 2;
            this.mainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.mainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.mainLayout.Controls.Add(this.SsChart2, 0, 0);
            this.mainLayout.Controls.Add(this.panel1, 1, 0);
            this.mainLayout.Controls.Add(this.bottomPanel, 0, 1);
            this.mainLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainLayout.Location = new System.Drawing.Point(0, 0);
            this.mainLayout.Name = "mainLayout";
            this.mainLayout.Padding = new System.Windows.Forms.Padding(9);
            this.mainLayout.RowCount = 2;
            this.mainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.mainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.mainLayout.SetColumnSpan(this.bottomPanel, 2);
            this.mainLayout.Size = new System.Drawing.Size(1326, 720);
            this.mainLayout.TabIndex = 0;
            //
            // SsChart2
            //
            this.SsChart2.BackColor = System.Drawing.Color.Black;
            this.SsChart2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SsChart2.DrawingsNum = ((long)(1));
            this.SsChart2.ForeColor = System.Drawing.SystemColors.ControlText;
            this.SsChart2.Location = new System.Drawing.Point(9, 9);
            this.SsChart2.Margin = new System.Windows.Forms.Padding(0);
            this.SsChart2.Name = "SsChart2";
            this.SsChart2.Padding = new System.Windows.Forms.Padding(5);
            this.SsChart2.ScaleNum = ((long)(2));
            this.SsChart2.ScaleOnResize = false;
            this.SsChart2.Size = new System.Drawing.Size(1115, 560);
            this.SsChart2.TabIndex = 0;
            //
            // panel1
            //
            this.panel1.AutoSize = true;
            this.panel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel1.BackColor = System.Drawing.Color.Black;
            this.panel1.Controls.Add(this.checkBox1);
            this.panel1.Controls.Add(this.checkBox2);
            this.panel1.Controls.Add(this.checkBox3);
            this.panel1.Controls.Add(this.checkBox4);
            this.panel1.Controls.Add(this.checkBox6);
            this.panel1.Controls.Add(this.checkBox7);
            this.panel1.Controls.Add(this.checkBox8);
            this.panel1.Controls.Add(this.checkBox9);
            this.panel1.Controls.Add(this.checkBox10);
            this.panel1.Controls.Add(this.checkBox11);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.panel1.Font = new System.Drawing.Font("Arial Narrow", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.panel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.panel1.Location = new System.Drawing.Point(1124, 9);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Padding = new System.Windows.Forms.Padding(6, 20, 9, 6);
            this.panel1.Size = new System.Drawing.Size(193, 560);
            this.panel1.TabIndex = 1;
            this.panel1.WrapContents = false;
            //
            // checkBox1
            //
            this.checkBox1.AutoSize = true;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.ForeColor = System.Drawing.Color.Red;
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.TabIndex = 0;
            this.checkBox1.Text = "Target temperature";
            this.checkBox1.UseVisualStyleBackColor = true;
            //
            // checkBox2
            //
            this.checkBox2.AutoSize = true;
            this.checkBox2.Checked = true;
            this.checkBox2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox2.ForeColor = System.Drawing.Color.LightGreen;
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.TabIndex = 1;
            this.checkBox2.Text = "Current Temperature";
            this.checkBox2.UseVisualStyleBackColor = true;
            //
            // checkBox3
            //
            this.checkBox3.AutoSize = true;
            this.checkBox3.Checked = true;
            this.checkBox3.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox3.ForeColor = System.Drawing.Color.SkyBlue;
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.TabIndex = 2;
            this.checkBox3.Text = "ADC";
            this.checkBox3.UseVisualStyleBackColor = true;
            //
            // checkBox4
            //
            this.checkBox4.AutoSize = true;
            this.checkBox4.Checked = true;
            this.checkBox4.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox4.ForeColor = System.Drawing.Color.Magenta;
            this.checkBox4.Name = "checkBox4";
            this.checkBox4.TabIndex = 3;
            this.checkBox4.Text = "Filtered temperature";
            this.checkBox4.UseVisualStyleBackColor = true;
            //
            // checkBox6
            //
            this.checkBox6.AutoSize = true;
            this.checkBox6.Checked = true;
            this.checkBox6.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox6.ForeColor = System.Drawing.Color.Orange;
            this.checkBox6.Name = "checkBox6";
            this.checkBox6.TabIndex = 4;
            this.checkBox6.Text = "PID Temperature";
            this.checkBox6.UseVisualStyleBackColor = true;
            //
            // checkBox7
            //
            this.checkBox7.AutoSize = true;
            this.checkBox7.Checked = true;
            this.checkBox7.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox7.ForeColor = System.Drawing.Color.Green;
            this.checkBox7.Name = "checkBox7";
            this.checkBox7.TabIndex = 5;
            this.checkBox7.Text = "Destination reached";
            this.checkBox7.UseVisualStyleBackColor = true;
            //
            // checkBox8
            //
            this.checkBox8.AutoSize = true;
            this.checkBox8.Checked = true;
            this.checkBox8.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox8.ForeColor = System.Drawing.Color.DarkRed;
            this.checkBox8.Name = "checkBox8";
            this.checkBox8.TabIndex = 6;
            this.checkBox8.Text = "Duty";
            this.checkBox8.UseVisualStyleBackColor = true;
            //
            // checkBox9
            //
            this.checkBox9.AutoSize = true;
            this.checkBox9.Checked = true;
            this.checkBox9.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox9.ForeColor = System.Drawing.Color.LightGray;
            this.checkBox9.Name = "checkBox9";
            this.checkBox9.TabIndex = 7;
            this.checkBox9.Text = "Heater resistance";
            this.checkBox9.UseVisualStyleBackColor = true;
            //
            // checkBox10
            //
            this.checkBox10.AutoSize = true;
            this.checkBox10.Checked = true;
            this.checkBox10.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox10.ForeColor = System.Drawing.Color.Blue;
            this.checkBox10.Name = "checkBox10";
            this.checkBox10.TabIndex = 8;
            this.checkBox10.Text = "Power On/Off";
            this.checkBox10.UseVisualStyleBackColor = true;
            //
            // checkBox11
            //
            this.checkBox11.AutoSize = true;
            this.checkBox11.Checked = true;
            this.checkBox11.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox11.ForeColor = System.Drawing.Color.White;
            this.checkBox11.Name = "checkBox11";
            this.checkBox11.TabIndex = 9;
            this.checkBox11.Text = "Waveshaping profile";
            this.checkBox11.UseVisualStyleBackColor = true;
            //
            // bottomPanel
            //
            this.bottomPanel.AutoSize = true;
            this.bottomPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.bottomPanel.Controls.Add(this.buttonsPanel);
            this.bottomPanel.Controls.Add(this.GPanel);
            this.bottomPanel.Controls.Add(this.OVFGPanel);
            this.bottomPanel.Controls.Add(this.KpPanel);
            this.bottomPanel.Controls.Add(this.KiPanel);
            this.bottomPanel.Controls.Add(this.DGPanel);
            this.bottomPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bottomPanel.Location = new System.Drawing.Point(9, 569);
            this.bottomPanel.Margin = new System.Windows.Forms.Padding(0, 6, 0, 0);
            this.bottomPanel.Name = "bottomPanel";
            this.bottomPanel.Size = new System.Drawing.Size(1308, 142);
            this.bottomPanel.TabIndex = 2;
            //
            // buttonsPanel
            //
            this.buttonsPanel.AutoSize = true;
            this.buttonsPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.buttonsPanel.Controls.Add(this.Button8);
            this.buttonsPanel.Controls.Add(this.Button6);
            this.buttonsPanel.Controls.Add(this.Button3);
            this.buttonsPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.buttonsPanel.Margin = new System.Windows.Forms.Padding(0, 0, 12, 0);
            this.buttonsPanel.Name = "buttonsPanel";
            this.buttonsPanel.TabIndex = 0;
            this.buttonsPanel.WrapContents = false;
            //
            // Button8
            //
            this.Button8.AutoSize = true;
            this.Button8.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.Button8.MinimumSize = new System.Drawing.Size(139, 40);
            this.Button8.Name = "Button8";
            this.Button8.Padding = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.Button8.Size = new System.Drawing.Size(139, 40);
            this.Button8.TabIndex = 0;
            this.Button8.Text = "STOP";
            this.Button8.UseVisualStyleBackColor = true;
            this.Button8.Click += new System.EventHandler(this.Button8_Click);
            //
            // Button6
            //
            this.Button6.AutoSize = true;
            this.Button6.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.Button6.MinimumSize = new System.Drawing.Size(139, 40);
            this.Button6.Name = "Button6";
            this.Button6.Padding = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.Button6.Size = new System.Drawing.Size(139, 40);
            this.Button6.TabIndex = 1;
            this.Button6.Text = "Query device";
            this.Button6.UseVisualStyleBackColor = true;
            this.Button6.Click += new System.EventHandler(this.Button6_Click);
            //
            // Button3
            //
            this.Button3.AutoSize = true;
            this.Button3.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.Button3.MinimumSize = new System.Drawing.Size(139, 40);
            this.Button3.Name = "Button3";
            this.Button3.Padding = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.Button3.Size = new System.Drawing.Size(139, 40);
            this.Button3.TabIndex = 2;
            this.Button3.Text = "Update Firmware";
            this.Button3.UseVisualStyleBackColor = true;
            this.Button3.Click += new System.EventHandler(this.Button3_Click);
            //
            // GPanel
            //
            this.GPanel.AutoSize = true;
            this.GPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.GPanel.BackColor = System.Drawing.SystemColors.Control;
            this.GPanel.Controls.Add(this.GTrackBar);
            this.GPanel.Controls.Add(this.GLabel);
            this.GPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.GPanel.Margin = new System.Windows.Forms.Padding(0, 0, 6, 0);
            this.GPanel.Name = "GPanel";
            this.GPanel.Padding = new System.Windows.Forms.Padding(3);
            this.GPanel.TabIndex = 1;
            this.GPanel.WrapContents = false;
            //
            // GTrackBar
            //
            this.GTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.GTrackBar.LargeChange = 8;
            this.GTrackBar.Margin = new System.Windows.Forms.Padding(0);
            this.GTrackBar.Maximum = 256;
            this.GTrackBar.Name = "GTrackBar";
            this.GTrackBar.Size = new System.Drawing.Size(193, 56);
            this.GTrackBar.TabIndex = 0;
            this.GTrackBar.ValueChanged += new System.EventHandler(this.GTrackBar_ValueChanged);
            //
            // GLabel
            //
            this.GLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.GLabel.Margin = new System.Windows.Forms.Padding(0);
            this.GLabel.Name = "GLabel";
            this.GLabel.Size = new System.Drawing.Size(193, 22);
            this.GLabel.TabIndex = 1;
            this.GLabel.Text = "Gain";
            this.GLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            //
            // OVFGPanel
            //
            this.OVFGPanel.AutoSize = true;
            this.OVFGPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.OVFGPanel.BackColor = System.Drawing.SystemColors.Control;
            this.OVFGPanel.Controls.Add(this.OVFGTrackBar);
            this.OVFGPanel.Controls.Add(this.OVFGLabel);
            this.OVFGPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.OVFGPanel.Margin = new System.Windows.Forms.Padding(0, 0, 6, 0);
            this.OVFGPanel.Name = "OVFGPanel";
            this.OVFGPanel.Padding = new System.Windows.Forms.Padding(3);
            this.OVFGPanel.TabIndex = 2;
            this.OVFGPanel.WrapContents = false;
            //
            // OVFGTrackBar
            //
            this.OVFGTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.OVFGTrackBar.LargeChange = 10;
            this.OVFGTrackBar.Margin = new System.Windows.Forms.Padding(0);
            this.OVFGTrackBar.Maximum = 100;
            this.OVFGTrackBar.Name = "OVFGTrackBar";
            this.OVFGTrackBar.Size = new System.Drawing.Size(193, 56);
            this.OVFGTrackBar.TabIndex = 0;
            this.OVFGTrackBar.ValueChanged += new System.EventHandler(this.OVFGTrackBar_ValueChanged);
            //
            // OVFGLabel
            //
            this.OVFGLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.OVFGLabel.Margin = new System.Windows.Forms.Padding(0);
            this.OVFGLabel.Name = "OVFGLabel";
            this.OVFGLabel.Size = new System.Drawing.Size(193, 22);
            this.OVFGLabel.TabIndex = 1;
            this.OVFGLabel.Text = "OVFGain";
            this.OVFGLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            //
            // KpPanel
            //
            this.KpPanel.AutoSize = true;
            this.KpPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.KpPanel.BackColor = System.Drawing.SystemColors.Control;
            this.KpPanel.Controls.Add(this.KpTrackBar);
            this.KpPanel.Controls.Add(this.KpLabel);
            this.KpPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.KpPanel.Margin = new System.Windows.Forms.Padding(0, 0, 6, 0);
            this.KpPanel.Name = "KpPanel";
            this.KpPanel.Padding = new System.Windows.Forms.Padding(3);
            this.KpPanel.TabIndex = 3;
            this.KpPanel.WrapContents = false;
            //
            // KpTrackBar
            //
            this.KpTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.KpTrackBar.LargeChange = 1000;
            this.KpTrackBar.Margin = new System.Windows.Forms.Padding(0);
            this.KpTrackBar.Maximum = 32767;
            this.KpTrackBar.Name = "KpTrackBar";
            this.KpTrackBar.Size = new System.Drawing.Size(193, 56);
            this.KpTrackBar.SmallChange = 100;
            this.KpTrackBar.TabIndex = 0;
            this.KpTrackBar.ValueChanged += new System.EventHandler(this.KpTrackBar_ValueChanged);
            //
            // KpLabel
            //
            this.KpLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.KpLabel.Margin = new System.Windows.Forms.Padding(0);
            this.KpLabel.Name = "KpLabel";
            this.KpLabel.Size = new System.Drawing.Size(193, 22);
            this.KpLabel.TabIndex = 1;
            this.KpLabel.Text = "Kp";
            this.KpLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            //
            // KiPanel
            //
            this.KiPanel.AutoSize = true;
            this.KiPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.KiPanel.BackColor = System.Drawing.SystemColors.Control;
            this.KiPanel.Controls.Add(this.KiTrackBar);
            this.KiPanel.Controls.Add(this.KiLabel);
            this.KiPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.KiPanel.Margin = new System.Windows.Forms.Padding(0, 0, 6, 0);
            this.KiPanel.Name = "KiPanel";
            this.KiPanel.Padding = new System.Windows.Forms.Padding(3);
            this.KiPanel.TabIndex = 4;
            this.KiPanel.WrapContents = false;
            //
            // KiTrackBar
            //
            this.KiTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.KiTrackBar.LargeChange = 100;
            this.KiTrackBar.Margin = new System.Windows.Forms.Padding(0);
            this.KiTrackBar.Maximum = 3277;
            this.KiTrackBar.Name = "KiTrackBar";
            this.KiTrackBar.Size = new System.Drawing.Size(193, 56);
            this.KiTrackBar.SmallChange = 10;
            this.KiTrackBar.TabIndex = 0;
            this.KiTrackBar.ValueChanged += new System.EventHandler(this.KiTrackBar_ValueChanged);
            //
            // KiLabel
            //
            this.KiLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.KiLabel.Margin = new System.Windows.Forms.Padding(0);
            this.KiLabel.Name = "KiLabel";
            this.KiLabel.Size = new System.Drawing.Size(193, 22);
            this.KiLabel.TabIndex = 1;
            this.KiLabel.Text = "Ki";
            this.KiLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            //
            // DGPanel
            //
            this.DGPanel.AutoSize = true;
            this.DGPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.DGPanel.BackColor = System.Drawing.SystemColors.Control;
            this.DGPanel.Controls.Add(this.DGTrackBar);
            this.DGPanel.Controls.Add(this.DGLabel);
            this.DGPanel.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.DGPanel.Margin = new System.Windows.Forms.Padding(0, 0, 6, 0);
            this.DGPanel.Name = "DGPanel";
            this.DGPanel.Padding = new System.Windows.Forms.Padding(3);
            this.DGPanel.TabIndex = 5;
            this.DGPanel.WrapContents = false;
            //
            // DGTrackBar
            //
            this.DGTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.DGTrackBar.Margin = new System.Windows.Forms.Padding(0);
            this.DGTrackBar.Maximum = 32;
            this.DGTrackBar.Name = "DGTrackBar";
            this.DGTrackBar.Size = new System.Drawing.Size(193, 56);
            this.DGTrackBar.TabIndex = 0;
            this.DGTrackBar.ValueChanged += new System.EventHandler(this.DGTrackBar_ValueChanged);
            //
            // DGLabel
            //
            this.DGLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.DGLabel.Margin = new System.Windows.Forms.Padding(0);
            this.DGLabel.Name = "DGLabel";
            this.DGLabel.Size = new System.Drawing.Size(193, 22);
            this.DGLabel.TabIndex = 1;
            this.DGLabel.Text = "DGain";
            this.DGLabel.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            //
            // statusStrip1
            //
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.connStatusLabel,
            this.logStatusLabel});
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.ShowItemToolTips = true;
            //the sizing grip made the Spring label 1 column too wide at non-100% scaling, so it was not placed at all
            this.statusStrip1.SizingGrip = false;
            this.statusStrip1.Size = new System.Drawing.Size(1326, 26);
            this.statusStrip1.TabIndex = 1;
            //
            // connStatusLabel
            //
            this.connStatusLabel.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Right;
            this.connStatusLabel.DoubleClickEnabled = true;
            this.connStatusLabel.Name = "connStatusLabel";
            this.connStatusLabel.Size = new System.Drawing.Size(120, 20);
            this.connStatusLabel.Text = "Not connected";
            this.connStatusLabel.ToolTipText = "Double-click to open the log file";
            this.connStatusLabel.DoubleClick += new System.EventHandler(this.StatusBar_DoubleClick);
            //
            // logStatusLabel
            //
            this.logStatusLabel.AutoSize = false;
            this.logStatusLabel.AutoToolTip = false;
            this.logStatusLabel.DoubleClickEnabled = true;
            this.logStatusLabel.Name = "logStatusLabel";
            //small preferred width: Spring gives it the remaining space
            this.logStatusLabel.Size = new System.Drawing.Size(100, 20);
            this.logStatusLabel.Spring = true;
            this.logStatusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.logStatusLabel.ToolTipText = "Double-click to open the log file";
            this.logStatusLabel.DoubleClick += new System.EventHandler(this.StatusBar_DoubleClick);
            //
            // Form1
            //
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1326, 720);
            this.Controls.Add(this.mainLayout);
            this.Controls.Add(this.statusStrip1);
            this.MinimumSize = new System.Drawing.Size(900, 600);
            this.Name = "Form1";
            this.Text = "UniSolder";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.GTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.OVFGTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.KpTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.KiTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DGTrackBar)).EndInit();
            this.DGPanel.ResumeLayout(false);
            this.DGPanel.PerformLayout();
            this.KiPanel.ResumeLayout(false);
            this.KiPanel.PerformLayout();
            this.KpPanel.ResumeLayout(false);
            this.KpPanel.PerformLayout();
            this.OVFGPanel.ResumeLayout(false);
            this.OVFGPanel.PerformLayout();
            this.GPanel.ResumeLayout(false);
            this.GPanel.PerformLayout();
            this.buttonsPanel.ResumeLayout(false);
            this.buttonsPanel.PerformLayout();
            this.bottomPanel.ResumeLayout(false);
            this.bottomPanel.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.mainLayout.ResumeLayout(false);
            this.mainLayout.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel mainLayout;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel connStatusLabel;
        private System.Windows.Forms.ToolStripStatusLabel logStatusLabel;
        internal SSControls.SSChart SsChart2;
        private System.Windows.Forms.FlowLayoutPanel panel1;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.CheckBox checkBox3;
        private System.Windows.Forms.CheckBox checkBox4;
        private System.Windows.Forms.CheckBox checkBox6;
        private System.Windows.Forms.CheckBox checkBox7;
        private System.Windows.Forms.CheckBox checkBox8;
        private System.Windows.Forms.CheckBox checkBox9;
        private System.Windows.Forms.CheckBox checkBox10;
        private System.Windows.Forms.CheckBox checkBox11;
        private System.Windows.Forms.FlowLayoutPanel bottomPanel;
        private System.Windows.Forms.FlowLayoutPanel buttonsPanel;
        internal System.Windows.Forms.Button Button8;
        internal System.Windows.Forms.Button Button6;
        internal System.Windows.Forms.Button Button3;
        private System.Windows.Forms.FlowLayoutPanel GPanel;
        internal System.Windows.Forms.TrackBar GTrackBar;
        internal System.Windows.Forms.Label GLabel;
        private System.Windows.Forms.FlowLayoutPanel OVFGPanel;
        internal System.Windows.Forms.TrackBar OVFGTrackBar;
        internal System.Windows.Forms.Label OVFGLabel;
        private System.Windows.Forms.FlowLayoutPanel KpPanel;
        internal System.Windows.Forms.TrackBar KpTrackBar;
        internal System.Windows.Forms.Label KpLabel;
        private System.Windows.Forms.FlowLayoutPanel KiPanel;
        internal System.Windows.Forms.TrackBar KiTrackBar;
        internal System.Windows.Forms.Label KiLabel;
        private System.Windows.Forms.FlowLayoutPanel DGPanel;
        internal System.Windows.Forms.TrackBar DGTrackBar;
        internal System.Windows.Forms.Label DGLabel;
    }
}
