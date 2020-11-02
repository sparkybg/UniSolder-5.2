using System;
using System.Threading;
using System.Diagnostics;
using LibUsbDotNet;
using LibUsbDotNet.Main;

namespace SSComm
{

    public class USBGen_LibUSB : IUniComm
    {
        public bool Connected { get; private set; } = false;

        public Int32 lBytesSent;
        public Int32 lBytesReceived;

        public const Int32 RXFIFOSIZE = 32768;
        public const Int32 TXFIFOSIZE = 16384;

        public Int32 DevVID = Int32.MaxValue;
        public Int32 DevPID = Int32.MaxValue;
        public Int32 DevRevision = Int32.MaxValue;
        public string DevSerialNumber = string.Empty;

        public Guid DevGUID = Guid.Empty;

        public event EventHandler DataReceived;

        private UsbDevice MyUSBDevice;
        private UsbDeviceFinder MyUSBDeviceFinder;
        private IUsbDevice WholeUSBDevice;
        private UsbEndpointWriter MyUSBWriter;
        private UsbEndpointReader MyUSBReader;
        private UsbSetupPacket MyUSBSetupPacket;
        
        private byte[] RXFIFO = new byte[RXFIFOSIZE];
        private Int32 RXReadPos;
        private Int32 RXWritePos;

        private byte[] TXFIFO = new byte[TXFIFOSIZE];
        private Int32 TXReadPos;
        private Int32 TXWritePos;

        private System.Threading.Thread bkThread;
        private bool bkThExit;
        private ManualResetEvent bkThInterrupt = new ManualResetEvent(false);
        
        public bool Connect()
        {
            bool rv = false;
            rv = false;
            Disconnect();
            MyUSBDeviceFinder = new UsbDeviceFinder(DevVID, DevPID, DevRevision, DevSerialNumber, DevGUID);
            MyUSBDevice = UsbDevice.OpenUsbDevice(MyUSBDeviceFinder);
            if (MyUSBDevice != null)
            {
                WholeUSBDevice = MyUSBDevice as IUsbDevice;
                if (!ReferenceEquals(WholeUSBDevice, null))
                {
                    WholeUSBDevice.SetConfiguration(1);
                    WholeUSBDevice.ClaimInterface(0);
                }
                MyUSBWriter = MyUSBDevice.OpenEndpointWriter(WriteEndpointID.Ep01);
                MyUSBReader = MyUSBDevice.OpenEndpointReader(ReadEndpointID.Ep01, 4096);
                MyUSBReader.DataReceived += MyUSBReader_DataReceived;
                MyUSBReader.DataReceivedEnabled = true;

                MyUSBSetupPacket.RequestType = (byte)(UsbCtrlFlags.RequestType_Vendor | UsbCtrlFlags.Recipient_Interface | UsbCtrlFlags.Direction_In);
                MyUSBSetupPacket.Request = 1;
                MyUSBSetupPacket.Value = 0;
                MyUSBSetupPacket.Length = 4;

                bkThread = new System.Threading.Thread(this.Th_DoWork);
                bkThExit = false;
                bkThread.Start();
                rv = true;
            }
            return rv;
        }

        public void Disconnect()
        {
            if (bkThread != null)
            {
                bkThExit = true;
                bkThInterrupt.Set();
                if (bkThread.ThreadState == System.Threading.ThreadState.Running) bkThread.Join();
            }
            bkThread = null;
            if (MyUSBDevice != null)
            {
                if (MyUSBDevice.IsOpen)
                {
                    WholeUSBDevice = MyUSBDevice as IUsbDevice;
                    if (!ReferenceEquals(WholeUSBDevice, null))
                    {
                        WholeUSBDevice.ReleaseInterface(0);
                    }
                    MyUSBReader.DataReceivedEnabled = false;
                    MyUSBReader.DataReceived -= MyUSBReader_DataReceived;
                    MyUSBDevice.Close();
                }
                MyUSBDevice = null;
                WholeUSBDevice = null;
                MyUSBDeviceFinder = null;
                MyUSBReader = null;
                MyUSBWriter = null;
            }
        }

        public void Init()
        {
            Disconnect();
            lBytesSent = 0;
            lBytesReceived = 0;
            RXReadPos = 0;
            RXWritePos = 0;
            DevVID = Int32.MaxValue;
            DevPID = Int32.MaxValue;
            DevRevision = Int32.MaxValue;
            DevGUID = Guid.Empty;
        }

        public Int32 BytesSent()
        {
            return lBytesSent;
        }

        public Int32 BytesReceived()
        {
            return lBytesReceived;
        }

        public Int32 RXDataCount
        {
            get
            {
                Int32 i;
                i = RXWritePos - RXReadPos;
                if (i < 0) i += RXFIFOSIZE;
                return i;
            }
        }

        public byte ReadByte()
        {
            byte rv;
            if (RXWritePos != RXReadPos)
            {
                rv = RXFIFO[RXReadPos];
                RXReadPos = (RXReadPos + 1) % RXFIFOSIZE;
                return rv;
            }
            else
            {
                throw new Exception("SSComm(USBGen_LibUSB).ReadByte: RX FIFO empty!");
            }
        }

        public Int32 Read(ref byte[] DBuffer, Int32 DOffset, Int32 MaxBytes)
        {
            Int32 i;
            if (MaxBytes < 0) MaxBytes = 0;
            if (MaxBytes > 0)
            {
                i = RXDataCount;
                if (MaxBytes > i) MaxBytes = i;
                if (MaxBytes < i) i = MaxBytes;
                while (i > 0)
                {
                    DBuffer[DOffset] = RXFIFO[RXReadPos];
                    DOffset += 1;
                    RXReadPos = (RXReadPos + 1) % RXFIFOSIZE;
                    i -= 1;
                }
            }
            return MaxBytes;
        }

        public Int32 TXFreeSpace
        {
            get
            {
                Int32 i;
                i = TXWritePos - TXReadPos;
                if (i < 0) i += TXFIFOSIZE;
                i = TXFIFOSIZE - i;
                return i;
            }
        }

        public void WriteByte(ref byte wb, bool dow = true)
        {
            if (TXFreeSpace > 0)
            {
                TXFIFO[TXWritePos] = wb;
                TXWritePos = (TXWritePos + 1) % TXFIFOSIZE;
                if (dow && (bkThread != null)) bkThInterrupt.Set();
            }
            else
            {
                throw new Exception("SSComm(USBGen_LibUSB).WriteByte: TX FIFO Full!");
            }
        }

        public bool Write(ref byte[] DBuffer, int DOffset, int NumBytes)
        {
            Int32 i;
            if (NumBytes > TXFreeSpace) throw new Exception("Not enough space in TX buffer.");
            for (i = 0; i < NumBytes; i++)
            {
                TXFIFO[TXWritePos] = DBuffer[DOffset + i];
                TXWritePos = (TXWritePos + 1) % TXFIFOSIZE;
            }
            if (bkThread != null)bkThInterrupt.Set();
            return true;
        }

        public void Dispose()
        {
            Disconnect();
        }

        private void MyUSBReader_DataReceived(object sender, LibUsbDotNet.Main.EndpointDataEventArgs e)
        {
            Int32 i;
            if (e.Count > 0)
            {
                lBytesReceived += e.Count;
                if (RXDataCount + e.Count < RXFIFOSIZE)
                {
                    for (i = 0; i < e.Count; i++)
                    {
                        RXFIFO[RXWritePos] = e.Buffer[i];
                        RXWritePos = (RXWritePos + 1) % RXFIFOSIZE;
                    }
                }
                else
                {
                    throw new Exception("RX FIFO overflow");
                }
                if (DataReceived != null)
                {
                    DataReceived(this, new EventArgs());
                }
            }
        }

        private void Th_DoWork()
        {
            Int32 lDevMaxDataSize;
            Int32 lDevWait;
            Int32 lTXSize;
            Int32[] i = new Int32[1];
            bool TXSuccess;
            lDevWait = 0;
            try
            {
                while (true)
                {
                    if (TXReadPos != TXWritePos)
                    {
                        lDevWait += 1;
                        if (lDevWait > 1000) lDevWait = 1000;
                        if (MyUSBDevice != null)
                        {
                            if (MyUSBDevice.IsOpen)
                            {
                                if (MyUSBWriter != null)
                                {
                                    //query how much data device can accept
                                    if (MyUSBDevice.ControlTransfer(ref MyUSBSetupPacket, i, 4, out lTXSize))
                                    {
                                        if (lTXSize == 4)
                                        {
                                            lDevMaxDataSize = i[0];
                                            //Debug.Print("Device can accept maximum " & lDevMaxDataSize & " byte(s)")
                                            if (lDevMaxDataSize > 0)
                                            {
                                                lDevWait = 0;
                                                lTXSize = TXWritePos - TXReadPos;
                                                if (lTXSize < 0)
                                                    lTXSize += TXFIFOSIZE;
                                                if (lTXSize > 0)
                                                {
                                                    if (lTXSize > lDevMaxDataSize) lTXSize = lDevMaxDataSize;
                                                    if ((TXReadPos + lTXSize) >= TXFIFOSIZE) lTXSize = TXFIFOSIZE - TXReadPos;
                                                    TXSuccess = (MyUSBWriter.Write(TXFIFO, TXReadPos, lTXSize, 2000, out lTXSize) == ErrorCode.Success);
                                                    if (TXSuccess)
                                                    {
                                                        TXReadPos = (TXReadPos + lTXSize) % TXFIFOSIZE;
                                                        lBytesSent += lTXSize;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        bkThInterrupt.WaitOne(lDevWait);
                        bkThInterrupt.Reset();
                    }
                    else
                    {
                        bkThInterrupt.WaitOne(Timeout.Infinite);
                        bkThInterrupt.Reset();
                    }
                    if (bkThExit) break; 
                }
            }
            catch (ThreadAbortException) { }
        }
    }
}
