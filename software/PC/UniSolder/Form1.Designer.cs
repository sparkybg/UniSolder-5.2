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
            this.SsChart2 = new SSControls.SSChart();
            this.Button8 = new System.Windows.Forms.Button();
            this.GLabel = new System.Windows.Forms.Label();
            this.GTrackBar = new System.Windows.Forms.TrackBar();
            this.OVFGLabel = new System.Windows.Forms.Label();
            this.OVFGTrackBar = new System.Windows.Forms.TrackBar();
            this.KpLabel = new System.Windows.Forms.Label();
            this.KpTrackBar = new System.Windows.Forms.TrackBar();
            this.KiLabel = new System.Windows.Forms.Label();
            this.KiTrackBar = new System.Windows.Forms.TrackBar();
            this.DGLabel = new System.Windows.Forms.Label();
            this.DGTrackBar = new System.Windows.Forms.TrackBar();
            this.Button6 = new System.Windows.Forms.Button();
            this.Button3 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.checkBox11 = new System.Windows.Forms.CheckBox();
            this.checkBox10 = new System.Windows.Forms.CheckBox();
            this.checkBox9 = new System.Windows.Forms.CheckBox();
            this.checkBox8 = new System.Windows.Forms.CheckBox();
            this.checkBox7 = new System.Windows.Forms.CheckBox();
            this.checkBox6 = new System.Windows.Forms.CheckBox();
            this.checkBox4 = new System.Windows.Forms.CheckBox();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.GTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.OVFGTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.KpTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.KiTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DGTrackBar)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // SsChart2
            // 
            this.SsChart2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.SsChart2.BackColor = System.Drawing.Color.Black;
            this.SsChart2.DrawingsNum = ((long)(1));
            this.SsChart2.ForeColor = System.Drawing.SystemColors.ControlText;
            this.SsChart2.Location = new System.Drawing.Point(12, 11);
            this.SsChart2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.SsChart2.Name = "SsChart2";
            this.SsChart2.Padding = new System.Windows.Forms.Padding(5);
            this.SsChart2.ScaleNum = ((long)(2));
            this.SsChart2.ScaleOnResize = false;
            this.SsChart2.Size = new System.Drawing.Size(1115, 555);
            this.SsChart2.TabIndex = 16;
            // 
            // Button8
            // 
            this.Button8.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Button8.Location = new System.Drawing.Point(12, 571);
            this.Button8.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Button8.Name = "Button8";
            this.Button8.Size = new System.Drawing.Size(139, 44);
            this.Button8.TabIndex = 48;
            this.Button8.Text = "STOP";
            this.Button8.UseVisualStyleBackColor = true;
            this.Button8.Click += new System.EventHandler(this.Button8_Click);
            // 
            // GLabel
            // 
            this.GLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.GLabel.AutoSize = true;
            this.GLabel.BackColor = System.Drawing.SystemColors.Control;
            this.GLabel.Location = new System.Drawing.Point(383, 607);
            this.GLabel.Name = "GLabel";
            this.GLabel.Size = new System.Drawing.Size(38, 17);
            this.GLabel.TabIndex = 47;
            this.GLabel.Text = "Gain";
            // 
            // GTrackBar
            // 
            this.GTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.GTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.GTrackBar.LargeChange = 8;
            this.GTrackBar.Location = new System.Drawing.Point(329, 571);
            this.GTrackBar.Maximum = 256;
            this.GTrackBar.Name = "GTrackBar";
            this.GTrackBar.Size = new System.Drawing.Size(193, 56);
            this.GTrackBar.TabIndex = 46;
            this.GTrackBar.ValueChanged += new System.EventHandler(this.GTrackBar_ValueChanged);
            // 
            // OVFGLabel
            // 
            this.OVFGLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.OVFGLabel.AutoSize = true;
            this.OVFGLabel.BackColor = System.Drawing.SystemColors.Control;
            this.OVFGLabel.Location = new System.Drawing.Point(582, 607);
            this.OVFGLabel.Name = "OVFGLabel";
            this.OVFGLabel.Size = new System.Drawing.Size(66, 17);
            this.OVFGLabel.TabIndex = 45;
            this.OVFGLabel.Text = "OVFGain";
            // 
            // OVFGTrackBar
            // 
            this.OVFGTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.OVFGTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.OVFGTrackBar.LargeChange = 10;
            this.OVFGTrackBar.Location = new System.Drawing.Point(528, 571);
            this.OVFGTrackBar.Maximum = 100;
            this.OVFGTrackBar.Name = "OVFGTrackBar";
            this.OVFGTrackBar.Size = new System.Drawing.Size(193, 56);
            this.OVFGTrackBar.TabIndex = 44;
            this.OVFGTrackBar.ValueChanged += new System.EventHandler(this.OVFGTrackBar_ValueChanged);
            // 
            // KpLabel
            // 
            this.KpLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.KpLabel.AutoSize = true;
            this.KpLabel.BackColor = System.Drawing.SystemColors.Control;
            this.KpLabel.Location = new System.Drawing.Point(796, 607);
            this.KpLabel.Name = "KpLabel";
            this.KpLabel.Size = new System.Drawing.Size(25, 17);
            this.KpLabel.TabIndex = 43;
            this.KpLabel.Text = "Kp";
            // 
            // KpTrackBar
            // 
            this.KpTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.KpTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.KpTrackBar.LargeChange = 1000;
            this.KpTrackBar.Location = new System.Drawing.Point(727, 571);
            this.KpTrackBar.Maximum = 32767;
            this.KpTrackBar.Name = "KpTrackBar";
            this.KpTrackBar.Size = new System.Drawing.Size(193, 56);
            this.KpTrackBar.SmallChange = 100;
            this.KpTrackBar.TabIndex = 42;
            this.KpTrackBar.ValueChanged += new System.EventHandler(this.KpTrackBar_ValueChanged);
            // 
            // KiLabel
            // 
            this.KiLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.KiLabel.AutoSize = true;
            this.KiLabel.BackColor = System.Drawing.SystemColors.Control;
            this.KiLabel.Location = new System.Drawing.Point(995, 607);
            this.KiLabel.Name = "KiLabel";
            this.KiLabel.Size = new System.Drawing.Size(20, 17);
            this.KiLabel.TabIndex = 41;
            this.KiLabel.Text = "Ki";
            // 
            // KiTrackBar
            // 
            this.KiTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.KiTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.KiTrackBar.LargeChange = 100;
            this.KiTrackBar.Location = new System.Drawing.Point(926, 571);
            this.KiTrackBar.Maximum = 3277;
            this.KiTrackBar.Name = "KiTrackBar";
            this.KiTrackBar.Size = new System.Drawing.Size(193, 56);
            this.KiTrackBar.SmallChange = 10;
            this.KiTrackBar.TabIndex = 40;
            this.KiTrackBar.ValueChanged += new System.EventHandler(this.KiTrackBar_ValueChanged);
            // 
            // DGLabel
            // 
            this.DGLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.DGLabel.AutoSize = true;
            this.DGLabel.BackColor = System.Drawing.SystemColors.Control;
            this.DGLabel.Location = new System.Drawing.Point(1194, 607);
            this.DGLabel.Name = "DGLabel";
            this.DGLabel.Size = new System.Drawing.Size(48, 17);
            this.DGLabel.TabIndex = 39;
            this.DGLabel.Text = "DGain";
            // 
            // DGTrackBar
            // 
            this.DGTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.DGTrackBar.BackColor = System.Drawing.SystemColors.Control;
            this.DGTrackBar.Location = new System.Drawing.Point(1125, 571);
            this.DGTrackBar.Maximum = 32;
            this.DGTrackBar.Name = "DGTrackBar";
            this.DGTrackBar.Size = new System.Drawing.Size(193, 56);
            this.DGTrackBar.TabIndex = 38;
            this.DGTrackBar.ValueChanged += new System.EventHandler(this.DGTrackBar_ValueChanged);
            // 
            // Button6
            // 
            this.Button6.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Button6.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.Button6.Location = new System.Drawing.Point(12, 619);
            this.Button6.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Button6.Name = "Button6";
            this.Button6.Size = new System.Drawing.Size(139, 44);
            this.Button6.TabIndex = 36;
            this.Button6.Text = "Query device";
            this.Button6.UseVisualStyleBackColor = false;
            this.Button6.Click += new System.EventHandler(this.Button6_Click);
            // 
            // Button3
            // 
            this.Button3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Button3.Location = new System.Drawing.Point(12, 667);
            this.Button3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Button3.Name = "Button3";
            this.Button3.Size = new System.Drawing.Size(139, 44);
            this.Button3.TabIndex = 33;
            this.Button3.Text = "Update Firmware";
            this.Button3.UseVisualStyleBackColor = true;
            this.Button3.Click += new System.EventHandler(this.Button3_Click);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.Color.Black;
            this.panel1.Controls.Add(this.checkBox11);
            this.panel1.Controls.Add(this.checkBox10);
            this.panel1.Controls.Add(this.checkBox9);
            this.panel1.Controls.Add(this.checkBox8);
            this.panel1.Controls.Add(this.checkBox7);
            this.panel1.Controls.Add(this.checkBox6);
            this.panel1.Controls.Add(this.checkBox4);
            this.panel1.Controls.Add(this.checkBox3);
            this.panel1.Controls.Add(this.checkBox2);
            this.panel1.Controls.Add(this.checkBox1);
            this.panel1.Font = new System.Drawing.Font("Arial Narrow", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.panel1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.panel1.Location = new System.Drawing.Point(1125, 11);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(193, 555);
            this.panel1.TabIndex = 49;
            // 
            // checkBox11
            // 
            this.checkBox11.AutoSize = true;
            this.checkBox11.Checked = true;
            this.checkBox11.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox11.ForeColor = System.Drawing.Color.White;
            this.checkBox11.Location = new System.Drawing.Point(6, 314);
            this.checkBox11.Name = "checkBox11";
            this.checkBox11.Size = new System.Drawing.Size(174, 26);
            this.checkBox11.TabIndex = 10;
            this.checkBox11.Text = "Waveshaping profile";
            this.checkBox11.UseVisualStyleBackColor = true;
            // 
            // checkBox10
            // 
            this.checkBox10.AutoSize = true;
            this.checkBox10.Checked = true;
            this.checkBox10.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox10.ForeColor = System.Drawing.Color.Blue;
            this.checkBox10.Location = new System.Drawing.Point(6, 282);
            this.checkBox10.Name = "checkBox10";
            this.checkBox10.Size = new System.Drawing.Size(124, 26);
            this.checkBox10.TabIndex = 9;
            this.checkBox10.Text = "Power On/Off";
            this.checkBox10.UseVisualStyleBackColor = true;
            // 
            // checkBox9
            // 
            this.checkBox9.AutoSize = true;
            this.checkBox9.Checked = true;
            this.checkBox9.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox9.ForeColor = System.Drawing.Color.LightGray;
            this.checkBox9.Location = new System.Drawing.Point(6, 250);
            this.checkBox9.Name = "checkBox9";
            this.checkBox9.Size = new System.Drawing.Size(153, 26);
            this.checkBox9.TabIndex = 8;
            this.checkBox9.Text = "Heater resistance";
            this.checkBox9.UseVisualStyleBackColor = true;
            // 
            // checkBox8
            // 
            this.checkBox8.AutoSize = true;
            this.checkBox8.Checked = true;
            this.checkBox8.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox8.ForeColor = System.Drawing.Color.DarkRed;
            this.checkBox8.Location = new System.Drawing.Point(6, 218);
            this.checkBox8.Name = "checkBox8";
            this.checkBox8.Size = new System.Drawing.Size(64, 26);
            this.checkBox8.TabIndex = 7;
            this.checkBox8.Text = "Duty";
            this.checkBox8.UseVisualStyleBackColor = true;
            // 
            // checkBox7
            // 
            this.checkBox7.AutoSize = true;
            this.checkBox7.Checked = true;
            this.checkBox7.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox7.ForeColor = System.Drawing.Color.Green;
            this.checkBox7.Location = new System.Drawing.Point(7, 186);
            this.checkBox7.Name = "checkBox7";
            this.checkBox7.Size = new System.Drawing.Size(171, 26);
            this.checkBox7.TabIndex = 6;
            this.checkBox7.Text = "Destination reached";
            this.checkBox7.UseVisualStyleBackColor = true;
            // 
            // checkBox6
            // 
            this.checkBox6.AutoSize = true;
            this.checkBox6.Checked = true;
            this.checkBox6.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox6.ForeColor = System.Drawing.Color.Orange;
            this.checkBox6.Location = new System.Drawing.Point(7, 154);
            this.checkBox6.Name = "checkBox6";
            this.checkBox6.Size = new System.Drawing.Size(147, 26);
            this.checkBox6.TabIndex = 5;
            this.checkBox6.Text = "PID Temperature";
            this.checkBox6.UseVisualStyleBackColor = true;
            // 
            // checkBox4
            // 
            this.checkBox4.AutoSize = true;
            this.checkBox4.Checked = true;
            this.checkBox4.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox4.ForeColor = System.Drawing.Color.Magenta;
            this.checkBox4.Location = new System.Drawing.Point(7, 122);
            this.checkBox4.Name = "checkBox4";
            this.checkBox4.Size = new System.Drawing.Size(173, 26);
            this.checkBox4.TabIndex = 3;
            this.checkBox4.Text = "Filtered temperature";
            this.checkBox4.UseVisualStyleBackColor = true;
            // 
            // checkBox3
            // 
            this.checkBox3.AutoSize = true;
            this.checkBox3.Checked = true;
            this.checkBox3.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox3.ForeColor = System.Drawing.Color.SkyBlue;
            this.checkBox3.Location = new System.Drawing.Point(7, 90);
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.Size = new System.Drawing.Size(62, 26);
            this.checkBox3.TabIndex = 2;
            this.checkBox3.Text = "ADC";
            this.checkBox3.UseVisualStyleBackColor = true;
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Checked = true;
            this.checkBox2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox2.ForeColor = System.Drawing.Color.LightGreen;
            this.checkBox2.Location = new System.Drawing.Point(7, 58);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(177, 26);
            this.checkBox2.TabIndex = 1;
            this.checkBox2.Text = "Current Temperature";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.ForeColor = System.Drawing.Color.Red;
            this.checkBox1.Location = new System.Drawing.Point(8, 26);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(165, 26);
            this.checkBox1.TabIndex = 0;
            this.checkBox1.Text = "Target temperature";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(1326, 720);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.Button8);
            this.Controls.Add(this.GLabel);
            this.Controls.Add(this.GTrackBar);
            this.Controls.Add(this.OVFGLabel);
            this.Controls.Add(this.OVFGTrackBar);
            this.Controls.Add(this.KpLabel);
            this.Controls.Add(this.KpTrackBar);
            this.Controls.Add(this.KiLabel);
            this.Controls.Add(this.KiTrackBar);
            this.Controls.Add(this.DGLabel);
            this.Controls.Add(this.DGTrackBar);
            this.Controls.Add(this.Button6);
            this.Controls.Add(this.Button3);
            this.Controls.Add(this.SsChart2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.GTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.OVFGTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.KpTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.KiTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DGTrackBar)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        internal SSControls.SSChart SsChart2;
        internal System.Windows.Forms.Button Button8;
        internal System.Windows.Forms.Label GLabel;
        internal System.Windows.Forms.TrackBar GTrackBar;
        internal System.Windows.Forms.Label OVFGLabel;
        internal System.Windows.Forms.TrackBar OVFGTrackBar;
        internal System.Windows.Forms.Label KpLabel;
        internal System.Windows.Forms.TrackBar KpTrackBar;
        internal System.Windows.Forms.Label KiLabel;
        internal System.Windows.Forms.TrackBar KiTrackBar;
        internal System.Windows.Forms.Label DGLabel;
        internal System.Windows.Forms.TrackBar DGTrackBar;
        internal System.Windows.Forms.Button Button6;
        internal System.Windows.Forms.Button Button3;
        private Panel panel1;
        private CheckBox checkBox1;
        private CheckBox checkBox2;
        private CheckBox checkBox3;
        private CheckBox checkBox4;
        private CheckBox checkBox7;
        private CheckBox checkBox6;
        private CheckBox checkBox11;
        private CheckBox checkBox10;
        private CheckBox checkBox9;
        private CheckBox checkBox8;
    }
}

