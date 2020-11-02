using System;
using System.Threading;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.IO;
using Microsoft.VisualBasic;
using Microsoft.Win32.SafeHandles;
using System.Runtime.Remoting.Messaging;

using LibUsbDotNet;
using LibUsbDotNet.Main;

namespace SSComm
{
    public partial class USBHID : IUniComm
    {
        public bool Connected { get; private set; } = false;

        public Int32 lBytesSent;
        public Int32 lBytesReceived;

        public const Int32 RXFIFOSIZE = 32768;
        public const Int32 TXFIFOSIZE = 16384;

        public UInt16 DevVID = UInt16.MaxValue;
        public UInt16 DevPID = UInt16.MaxValue;
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
        private ManualResetEvent bkThInterript = new ManualResetEvent(false);

        private Hid MyHid = new Hid();
        private DeviceManagement MyDeviceManagement = new DeviceManagement();
        private SafeFileHandle hidHandleR;
        private SafeFileHandle hidHandleW;
        private FileStream hidFSR;
        private FileStream hidFSW;
        private string myDevicePathName;

        private byte[] rxBuffer;
        private byte[] txBuffer;

        private object ThisLock = new Object();

        public bool Connect()
        {
            string[] devicePathName = new string[128];
            bool myDeviceDetected = false;

            if (Connected) Disconnect();

            Guid hidGuid = Guid.Empty;
            Hid.HidD_GetHidGuid(ref hidGuid);
            if (MyDeviceManagement.FindDeviceFromGuid(hidGuid, ref devicePathName))
            {
                int memberIndex = 0;
                do
                {
                    hidHandleR = FileIO.CreateFile(devicePathName[memberIndex], 0, FileIO.FILE_SHARE_READ | FileIO.FILE_SHARE_WRITE, IntPtr.Zero, FileIO.OPEN_EXISTING, 0, 0);
                    if (!hidHandleR.IsInvalid)
                    {
                        MyHid.DeviceAttributes.Size = Marshal.SizeOf(MyHid.DeviceAttributes);
                        if (Hid.HidD_GetAttributes(hidHandleR, ref MyHid.DeviceAttributes))
                        {
                            if ((MyHid.DeviceAttributes.VendorID == DevVID) && (MyHid.DeviceAttributes.ProductID == DevPID))
                            {
                                myDeviceDetected = true;
                                myDevicePathName = devicePathName[memberIndex];
                            }
                            else
                            {
                                myDeviceDetected = false;
                                hidHandleR.Close();
                            }
                        }
                        else
                        {
                            myDeviceDetected = false;
                            hidHandleR.Close();
                        }
                    }
                    memberIndex++;
                }
                while (!(myDeviceDetected || memberIndex == devicePathName.Length));
                if (myDeviceDetected)
                {
                    MyHid.Capabilities = MyHid.GetDeviceCapabilities(hidHandleR);
                    MyHid.GetHidUsage(MyHid.Capabilities);
                    hidHandleR.Close();
                    hidHandleR = FileIO.CreateFile(myDevicePathName, FileIO.GENERIC_READ, FileIO.FILE_SHARE_READ | FileIO.FILE_SHARE_WRITE, IntPtr.Zero, FileIO.OPEN_EXISTING, 0, 0);
                    hidHandleW = FileIO.CreateFile(myDevicePathName, FileIO.GENERIC_WRITE, FileIO.FILE_SHARE_READ | FileIO.FILE_SHARE_WRITE, IntPtr.Zero, FileIO.OPEN_EXISTING, 0, 0);
                    if (hidHandleR.IsInvalid || hidHandleW.IsInvalid)
                    {
                        Connected = false;
                        hidFSR.Close();
                        hidFSW.Close();
                        if (!hidHandleR.IsInvalid) hidHandleR.Close();
                        if (!hidHandleW.IsInvalid) hidHandleW.Close();
                    }
                    else
                    {
                        MyHid.FlushQueue(hidHandleR);
                        MyHid.FlushQueue(hidHandleW);
                        hidFSR = new FileStream(hidHandleR, FileAccess.Read, MyHid.Capabilities.OutputReportByteLength, false); //false);
                        hidFSW = new FileStream(hidHandleW, FileAccess.Write, MyHid.Capabilities.OutputReportByteLength, false); //false);
                        rxBuffer = new Byte[MyHid.Capabilities.InputReportByteLength];
                        hidFSR.BeginRead(rxBuffer, 0, rxBuffer.Length, new AsyncCallback(ReadCallback), rxBuffer);
                        bkThread = new System.Threading.Thread(this.Th_DoWork);
                        bkThExit = false;
                        bkThread.Start();
                        Connected = true;
                    }
                }
            }
            return Connected;
        }

        private void ReadCallback(IAsyncResult ar)
        {
            if (hidFSR != null)
            {
                try
                {
                    hidFSR.EndRead(ar);
                    if (ar.IsCompleted)
                    {
                        lBytesReceived += rxBuffer.Length;
                        if (RXDataCount + rxBuffer.Length < RXFIFOSIZE)
                        {
                            for (int i = 1; i < rxBuffer.Length; i++)
                            {
                                RXFIFO[RXWritePos] = rxBuffer[i];
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
                    hidFSR.BeginRead(rxBuffer, 0, rxBuffer.Length, new AsyncCallback(ReadCallback), rxBuffer);
                }
                catch
                {
                    Disconnect();
                }
            }
        }


        public void Disconnect()
        {
            if (bkThread != null)
            {
                bkThExit = true;
                bkThInterript.Set();
                if (bkThread.ThreadState == System.Threading.ThreadState.Running) bkThread.Join();
            }
            bkThread = null;
            lock (ThisLock)
            {
                if (hidFSR != null)
                {
                    hidFSR.Close();
                    hidFSR = null;
                }
                if (hidFSW != null)
                {
                    hidFSW.Close();
                    hidFSW = null;
                }
                if ((hidHandleR != null) && (!(hidHandleR.IsInvalid)))
                {
                    hidHandleR.Close();
                }
                if ((hidHandleW != null) && (!(hidHandleW.IsInvalid)))
                {
                    hidHandleW.Close();
                }
                hidHandleR = null;
                hidHandleW = null;
                myDevicePathName = "";
            }
            Connected = false;
        }

        public void Init()
        {
            Disconnect();
            lBytesSent = 0;
            lBytesReceived = 0;
            RXReadPos = 0;
            RXWritePos = 0;
            DevVID = UInt16.MaxValue;
            DevPID = UInt16.MaxValue;
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
                if (dow && (bkThread != null)) bkThInterript.Set();
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
            if (bkThread != null) bkThInterript.Set();
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
            Int32 lTXSize;
            Int32 i;
            byte[] b = new byte[MyHid.Capabilities.OutputReportByteLength];
            try
            {
                while (true)
                {
                    if (hidFSW != null && hidFSW.CanWrite)
                    {
                        lTXSize = TXWritePos - TXReadPos;
                        if (lTXSize < 0) lTXSize += TXFIFOSIZE;
                        if (lTXSize >= (b.Length - 1))
                        {
                            b[0] = 0;
                            for (i = 0; i < (b.Length - 1); i++)
                            {
                                b[i + 1] = TXFIFO[(TXReadPos + i) % TXFIFOSIZE];
                            }
                            hidFSW.Write(b, 0, b.Length);
                            hidFSW.Flush();
                            TXReadPos += b.Length - 1;
                            TXReadPos %= TXFIFOSIZE;
                            lBytesSent += b.Length - 1;
                        }
                        else
                        {
                            bkThInterript.WaitOne(Timeout.Infinite);
                            bkThInterript.Reset();
                        }
                    }
                    else
                    {
                        bkThInterript.WaitOne(Timeout.Infinite);
                        bkThInterript.Reset();
                    }
                    if (bkThExit) break;
                }
            }
            catch (ThreadAbortException) { }
        }
    }
}
