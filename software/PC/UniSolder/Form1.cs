
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using SSControls;

namespace UniSolder
{

    partial class Form1
    {
        int CPoint = 0;

        private UniSolderComm lUniSolder = null;
        private UniSolderComm.PID PID = null;

        private System.Windows.Forms.Timer ConnectionTimer;

        public Form1()
        {
            Disposed += Form1_Disposed;
            InitializeComponent();

            lUniSolder = new UniSolderComm();
            lUniSolder.InstrumentChange += InstrumentChange;
            lUniSolder.LiveDataReceived += LiveDataReceived;
            lUniSolder.Transport = new SSComm.USBHID { DevVID = 0x4d8, DevPID = 0x3c };

            ConnectionTimer = new System.Windows.Forms.Timer() { Interval = 1000, Enabled = true };
            ConnectionTimer.Tick += ConnectionTimer_Tick;
        }

        private void ConnectionTimer_Tick(object sender, EventArgs e)
        {
            if (!lUniSolder.Transport.Connected)
            {
                if (lUniSolder.Transport.Connect())
                {
                    InstrumentChange(null, null);
                }
            }
        }

        private void Form1_Disposed(object sender, EventArgs e)
        {
            lUniSolder?.Transport?.Dispose();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            SsChart2.DrawingsNum = 13;
            var _with1 = SsChart2.Scales(0);
            _with1.ValFrom = 0;
            _with1.ValTo = 5.11F;
            _with1.ValMinStep = 1F / 50F;
            _with1.ValMajStep = 1F;
            _with1.ValFormat = "0";

            var _with2 = SsChart2.Scales(1);
            _with2.ValFrom = 0;
            _with2.ValTo = 500;
            _with2.ValMinStep = 10;
            _with2.ValMajStep = 50;
            _with2.ValFormat = "0";

            var _with3 = SsChart2.Drawings(0);
            _with3.XScale = SsChart2.Scales(0);
            _with3.Yscale = SsChart2.Scales(1);
            _with3.Pen.Color = Color.Yellow;
            _with3.Pen.Width = 1;
            _with3.PointsNum = 2;
            _with3.Points[0].X = _with3.XScale.ValFrom;
            _with3.Points[0].Y = _with3.Yscale.ValFrom;
            _with3.Points[1].X = _with3.XScale.ValFrom;
            _with3.Points[1].Y = _with3.Yscale.ValTo;

            foreach (var d in SsChart2.Drawings1)
            {
                if (d != SsChart2.Drawings1[0])
                {
                    d.XScale = SsChart2.Scales(0);
                    d.Yscale = SsChart2.Scales(1);
                    d.Pen.Width = 2;
                    d.PointsNum = 256;
                    for (var i = 0; i <= 255; i++)
                    {
                        d.Points[i].X = i / 50F;
                        d.Points[i].Y = 10;
                    }
                }
            }

            SsChart2.Drawings(1).Pen.Color = Color.DarkRed;
            SsChart2.Drawings(2).Pen.Color = Color.Red;
            SsChart2.Drawings(3).Pen.Color = Color.LightGreen;
            SsChart2.Drawings(4).Pen.Color = Color.SkyBlue;
            SsChart2.Drawings(5).Pen.Color = Color.Magenta;
            SsChart2.Drawings(6).Pen.Color = Color.Yellow;
            SsChart2.Drawings(7).Pen.Color = Color.Blue;
            SsChart2.Drawings(8).Pen.Color = Color.LightGray;
            SsChart2.Drawings(9).Pen.Color = Color.Orange;
            SsChart2.Drawings(10).Pen.Color = Color.White;
            SsChart2.Drawings(11).Pen.Color = Color.Green;
            SsChart2.Drawings(12).Pen.Color = Color.DarkSlateBlue;


            //Debug.Print("Connecting.....");
            //Debug.Print(lUniSolder.Transport.Connect().ToString());
            //Dim aa(64) As Byte
            //aa(0) = 0
            //lUniSolder.TransLayer.Write(aa, 0, 64)
            //lUniSolder.TransLayer.Write(aa, 0, 64)

            System.Threading.Thread.Sleep(500);
            InstrumentChange(null, null);
            //PID = lUniSolder.AppGetPIDParameters()
            //KpTrackBar.Value = PID.KP
            //KiTrackBar.Value = PID.KI
            //DGTrackBar.Value = PID.DGain
            //OVFGTrackBar.Value = PID.OVSGain
            //GTrackBar.Value = PID.Gain
            //Dim b(64) As Byte
            //b(0) = 4
            //ud.Write(b, 0, 64)
            //Timer1.Enabled = True
        }

        public delegate void InstrumentChangeDelegate(object sender, EventArgs e);
        private void InstrumentChange(object sender, EventArgs e)
        {
            if ((KpTrackBar.InvokeRequired))
            {
                KpTrackBar.BeginInvoke(new InstrumentChangeDelegate(InstrumentChange), sender, e);
            }
            else
            {
                PID = lUniSolder.AppGetPIDParameters();
                KpTrackBar.Value = PID.KP;
                KiTrackBar.Value = PID.KI;
                DGTrackBar.Value = PID.DGain;
                OVFGTrackBar.Value = PID.OVSGain;
                GTrackBar.Value = PID.Gain;
            }
        }

        public delegate void LiveDataReceivedDelegate(object sender, UniSolderComm.LiveDataReceivedEventData e);
        private void LiveDataReceived(object sender, UniSolderComm.LiveDataReceivedEventData e)
        {
            if (SsChart2.InvokeRequired)
            {
                SsChart2.BeginInvoke(new LiveDataReceivedDelegate(LiveDataReceived), sender, e);
            }
            else
            {
                var b = e.Data;
                switch (b[0])
                {
                    case 3:
                        if (Button8.Text != "START")
                        {
                            SsChart2.Drawings(0).Points[0].X = SsChart2.Drawings(1).Points[CPoint].X;
                            SsChart2.Drawings(0).Points[1].X = SsChart2.Drawings(1).Points[CPoint].X;

                            //CTTemp
                            SsChart2.Drawings(2).Points[CPoint].Y = b[3] * 2.0F;

                            //CTemp
                            SsChart2.Drawings(3).Points[CPoint].Y = b[4] * 0.5F + b[5] * 128.0F;

                            //ADCTemp
                            SsChart2.Drawings(4).Points[CPoint].Y = b[6] * 0.5F + b[7] * 128.0F;

                            //TAvgF
                            SsChart2.Drawings(5).Points[CPoint].Y = b[8] * 0.5F + b[9] * 128.0F;

                            //CHRes - Heater resistance x10
                            SsChart2.Drawings(8).Points[CPoint].Y = b[10] * 1.0F + b[11] * 256.0F;

                            //TAvgP
                            SsChart2.Drawings(9).Points[CPoint].Y = b[12] * 0.5F + b[13] * 128.0F;

                            //Power On/Off
                            SsChart2.Drawings(7).Points[CPoint].Y = b[14] != 0 ? 100.0F : 0.0F;

                            //WSDelta
                            SsChart2.Drawings(10).Points[0].Y = (b[15] * 1.0F + b[16] * 256.0F - 2048.0F) / 4.0F + 200.0F;
                            SsChart2.Drawings(10).Points[1].Y = (b[17] * 1.0F + b[18] * 256.0F - 2048.0F) / 4.0F + 200.0F;
                            SsChart2.Drawings(10).Points[2].Y = (b[19] * 1.0F + b[20] * 256.0F - 2048.0F) / 4.0F + 200.0F;
                            SsChart2.Drawings(10).Points[3].Y = (b[21] * 1.0F + b[22] * 256.0F - 2048.0F) / 4.0F + 200.0F;
                            SsChart2.Drawings(10).Points[4].Y = (b[23] * 1.0F + b[24] * 256.0F - 2048.0F) / 4.0F + 200.0F;
                            SsChart2.Drawings(10).Points[5].Y = (b[25] * 1.0F + b[26] * 256.0F - 2048.0F) / 4.0F + 200.0F;
                            SsChart2.Drawings(10).Points[6].Y = (b[27] * 1.0F + b[28] * 256.0F - 2048.0F) / 4.0F + 200.0F;

                            //DestinationReached
                            SsChart2.Drawings(11).Points[CPoint].Y = b[31] * 100.0F;

                            //Duty
                            SsChart2.Drawings(1).Points[CPoint].Y = (b[32] * 1.0F + b[33] * 256.0F) / 128.0F;

                            ////SsChart2.Drawings(12).Points(CPoint).Y = (b(34) * 1.0 + b(35) * 256.0);
                            //TAvgF
                            //SsChart2.Drawings(6).Points(CPoint).Y = (b(10) * 1.0 + b(11) * 256.0 - 2048.0) / 4.0 + 200.0

                            CPoint = (CPoint + 1) % 256;
                        }
                        break;
                }
                if (!SsChart2.redrawactive)
                {
                    SsChart2.Drawings(2).Visible = checkBox1.Checked; //CTTemp
                    SsChart2.Drawings(3).Visible = checkBox2.Checked; //CTemp
                    SsChart2.Drawings(4).Visible = checkBox3.Checked; //ADCTemp
                    SsChart2.Drawings(5).Visible = checkBox4.Checked; //TAvgF
                    SsChart2.Drawings(9).Visible = checkBox6.Checked; //TavgP
                    SsChart2.Drawings(11).Visible = checkBox7.Checked; //DestinationReached
                    SsChart2.Drawings(1).Visible = checkBox8.Checked; //Duty
                    SsChart2.Drawings(8).Visible = checkBox9.Checked; //CHRes
                    SsChart2.Drawings(7).Visible = checkBox10.Checked; //Power On/Off
                    SsChart2.Drawings(10).Visible = checkBox11.Checked; //WsDelta

                    SsChart2._Redraw();
                }
            }
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            var fd = new OpenFileDialog()
            {
                CheckFileExists = true,
                CheckPathExists = true,
                Multiselect = false,
                Filter = "HEX Files|*.hex",
                Title = "Select HEX file to upload.",
                FilterIndex = 0
            };
            if (fd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                Stopwatch sst = new Stopwatch();
                HexFileManager ss = new HexFileManager();
                if (ss.LoadHexFile(fd.FileName))// "C:\\Users\\Sparky\\Desktop\\MyProjects\\Electronics\\UniSolder\\software\\front\\US_Firmware.X\\dist\\PIC32_with_bootloader\\production\\US_Firmware.X.production.hex"))
                {
                    if (lUniSolder.Transport.Connected)
                    {
                        Debug.Print("Hex File loaded successfully");
                        sst.Restart();
                        byte b = 0;
                        lUniSolder.DevGetOpMode(ref b);
                        if (b != 16)
                        {
                            lUniSolder.AppJumpToBootloader();
                            Thread.Sleep(500);
                            lUniSolder.Transport.Disconnect();
                            for (int i = 0; i < 20; i++)
                            {
                                if (lUniSolder.Transport.Connect()) break;
                                Thread.Sleep(500);
                            }
                            if (!lUniSolder.Transport.Connected) throw new Exception("Could not connect to UniSolder device.");
                            for (int i = 0; i < 20 && b != 16; i++)
                            {
                                lUniSolder.DevGetOpMode(ref b);
                            }
                            if (b != 16) throw new Exception("Could not go into bootloader mode.");
                        }
                        Debug.Print("Erasing Flash...");
                        lUniSolder.BlEraseFlash();
                        sst.Stop();
                        Debug.Print("Erasing completed in " + sst.Elapsed.ToString());
                        Debug.Print("Programming started...");
                        sst.Restart();
                        foreach (var r in ss.Records)
                        {
                            var cResult = lUniSolder.BlProgramFlash(r.Address, ref r.Data, 0, (int)r.RecDataLen);
                            switch (cResult)
                            {
                                case 0:
                                    //Debug.Print(i & "(" & Format(.Address, "X8") & "," & .RecDataLen & ")")
                                    break;
                                case -1:
                                    Debug.Print("Time Out");
                                    break;
                                default:
                                    Debug.Print("Error(" + cResult + ")");
                                    break;
                            }
                            if (cResult != 0) break;
                        }
                        lUniSolder.BlProgramComplete();
                        sst.Stop();
                        Debug.Print("Programming completed in " + sst.Elapsed.ToString());
                        lUniSolder.BlJumpToApplication();
                    }
                }
            }
        }


        private void Button6_Click(object sender, EventArgs e)
        {
            lUniSolder.DevQuery();
        }

        private void KpTrackBar_ValueChanged(object sender, EventArgs e)
        {
            KpLabel.Text = "Kp = " + (KpTrackBar.Value / 32767.0).ToString("0.00");
            if ((PID.KP != KpTrackBar.Value))
            {
                PID.KP = (UInt16)KpTrackBar.Value;
                lUniSolder.AppSetPIDParameters(ref PID);
            }
        }

        private void KiTrackBar_ValueChanged(object sender, EventArgs e)
        {
            KiLabel.Text = "Ki = " + (KiTrackBar.Value / 32767.0).ToString("0.000");
            if ((PID.KI != KiTrackBar.Value))
            {
                PID.KI = (UInt16)KiTrackBar.Value;
                lUniSolder.AppSetPIDParameters(ref PID);
            }
        }

        private void DGTrackBar_ValueChanged(object sender, EventArgs e)
        {
            DGLabel.Text = "DGain = " + DGTrackBar.Value.ToString();
            if ((PID.DGain != DGTrackBar.Value))
            {
                PID.DGain = (byte)DGTrackBar.Value;
                lUniSolder.AppSetPIDParameters(ref PID);
            }
        }

        private void OVFGTrackBar_ValueChanged(object sender, EventArgs e)
        {
            OVFGLabel.Text = "OVFGain = " + OVFGTrackBar.Value.ToString();
            if ((PID.OVSGain != OVFGTrackBar.Value))
            {
                PID.OVSGain = (byte)OVFGTrackBar.Value;
                lUniSolder.AppSetPIDParameters(ref PID);
            }
        }

        private void GTrackBar_ValueChanged(object sender, EventArgs e)
        {
            GLabel.Text = "Gain = " + GTrackBar.Value.ToString();
            if ((PID.Gain != GTrackBar.Value))
            {
                PID.Gain = (UInt16)GTrackBar.Value;
                lUniSolder.AppSetPIDParameters(ref PID);
            }
        }

        private void Button8_Click(object sender, EventArgs e)
        {
            if (Button8.Text == "STOP")
            {
                Button8.Text = "START";
            }
            else
            {
                Button8.Text = "STOP";
            }
        }
    }
}