
using Microsoft.VisualBasic;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;
using System.Windows.Forms;
using System.IO;

public class UniSolderComm
{

    #region "Enums"
    public enum Commands : byte
    {
        DEV_QUERY = 0x02,
        DEV_GET_INFO = 0x60,
        DEV_GET_OPERATING_MODE = 0x61,
        DEV_RESET = 0x62,

        APP_GET_INFO = 0x80,
        APP_JUMP_TO_BOOTLOADER = 0x81,
        APP_RESTART = 0x82,

        APP_SET_PID = 3,
        APP_GET_PID = 4,

        BL_GET_INFO = 0xE0,
        BL_ERASE_FLASH = 0xE1,
        BL_PROGRAM_FLASH = 0xE2,
        BL_READ_CRC = 0xE3,
        BL_JUMP_TO_APP = 0xE4,
        BL_PROGRAM_COMPLETE = 0xE5
    }

    #endregion

    #region "Public subclasses"

    public class T_CommandFeedback
    {
        public bool IsEmpty;
        public byte Command;
        public byte Status;
        public byte[] Data = new byte[1024];

        public UInt32 DataLength;
        public void Clear()
        {
            IsEmpty = true;
            Command = 0;
            Status = 0;
            DataLength = 0;
        }

        public bool ReadFromBuffer(ref byte[] bb, UInt32 Offset, UInt32 DLen)
        {
            UInt32 i = default(UInt32);
            Command = bb[Offset];
            //Status = bb(Offset + 1)
            DataLength = DLen - 1;
            for (i = 0; i <= DLen - 2; i++)
            {
                Data[i] = bb[Offset + 1 + i];
            }
            IsEmpty = false;
            return true;
        }

        public T_CommandFeedback()
        {
            Clear();
        }
    }

    public class PID
    {
        public UInt16 Gain;
        public UInt16 Offset;
        public UInt16 KP;
        public UInt16 KI;
        public byte DGain;
        public byte OVSGain;
    }
    #endregion

    private SSComm.IUniComm lTransport;
    public SSComm.IUniComm Transport
    {
        get
        {
            return lTransport;
        }
        set
        {
            if (lTransport != null && lTransport != value)
            {
                lTransport.DataReceived -= Transport_DataReceived;
            }
            if ((lTransport = value) != null)
            {
                lTransport.DataReceived += Transport_DataReceived;
            }
        }
    }


    public T_CommandFeedback CommandFeedBack = new T_CommandFeedback();

    public class LiveDataReceivedEventData : EventArgs
    {
        public byte[] Data;
    }

    public event EventHandler<LiveDataReceivedEventData> LiveDataReceived;
    public event EventHandler InstrumentChange;


    private Stopwatch TOTimer = new Stopwatch();
    public void Init()
    {
        CommandFeedBack.Clear();
    }

    public int DevQuery()
    {
        byte[] bb = { (byte)Commands.DEV_QUERY };
        var result = SendBINCommand(bb, 0, 1, bb, 1000);
        return result;
    }

    public int DevGetInfo(ref UInt32 dDevID, ref byte dVerMaj, ref byte dVerMin)
    {
        byte[] bb = {
            (byte)Commands.DEV_GET_INFO,
            0,
            0,
            0,
            0,
            0,
            0
        };
        var Result = SendBINCommand(bb, 0, 1, bb, 1000);
        if (Result == 0)
        {
            dDevID = bb[3];
            dDevID <<= 8;
            dDevID += bb[2];
            dDevID <<= 8;
            dDevID += bb[1];
            dDevID <<= 8;
            dDevID += bb[0];
            dVerMin = bb[4];
            dVerMaj = bb[5];
            Debug.Print("Device info: ID=" + String.Format("X8", dDevID) + " Version: " + dVerMaj + "." + dVerMin);
        }
        return Result;
    }

    public int DevGetOpMode(ref byte dOpM)
    {
        byte[] bb = { (byte)Commands.DEV_GET_OPERATING_MODE };
        var Result = SendBINCommand(bb, 0, 1, bb, 1000);
        if (Result == 0)
        {
            dOpM = bb[0];
            Debug.Print("Device operating mode: " + bb[0]);
        }
        return Result;
    }

    public void DevReset()
    {
        byte[] bb = { (byte)Commands.DEV_RESET };
        SendBINCommand(bb, 0, 1, null, 0);
        Debug.Print("Device reset.");
    }

    public int AppGetInfo(ref byte aVerMin, ref byte aVerMaj)
    {
        byte[] bb = {
            (byte)Commands.APP_GET_INFO,
            0
        };
        var Result = SendBINCommand(bb, 0, 1, bb, 1000);
        if (Result == 0)
        {
            aVerMin = bb[0];
            aVerMaj = bb[1];
            Debug.Print("Device application info: Version: " + aVerMaj + "." + aVerMin);
        }
        return Result;
    }

    public void AppJumpToBootloader()
    {
        byte[] bb = { (byte)Commands.APP_JUMP_TO_BOOTLOADER };
        SendBINCommand(bb, 0, 1, null, 0);
        Debug.Print("Jump to bootloader.");
    }

    public void AppRestart()
    {
        byte[] bb = { (byte)Commands.APP_RESTART };
        SendBINCommand(bb, 0, 1, null, 0);
        Debug.Print("Application restart.");
    }

    public PID AppGetPIDParameters()
    {
        byte[] bb = {
            (byte)Commands.APP_GET_PID,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        };
        Debug.Print("Get PID paramaters");
        SendBINCommand(bb, 0, 1, bb, 1000);
        return new PID
        {
            Gain = (UInt16)((UInt16)bb[0] + (UInt16)bb[1] * (UInt16)256),
            Offset = (UInt16)((UInt16)bb[2] + (UInt16)bb[3] * (UInt16)256),
            KP = (UInt16)((UInt16)bb[4] + (UInt16)bb[5] * (UInt16)256),
            KI = (UInt16)((UInt16)bb[6] + (UInt16)bb[7] * (UInt16)256),
            DGain = bb[8],
            OVSGain = bb[10]
        };
    }

    public void AppSetPIDParameters(ref PID PID)
    {
        byte[] BB = {
            (byte)Commands.APP_SET_PID,
            (byte)(PID.Gain & 255),
            (byte)(PID.Gain / 256),
            0,
            0,
            (byte)(PID.KP & 255),
            (byte)(PID.KP / 256),
            (byte)(PID.KI & 255),
            (byte)(PID.KI / 256),
            PID.DGain,
            0,
            PID.OVSGain,
            0
        };
        SendBINCommand(BB, 0, BB.Length, null, 0);
    }

    public Int32 BlGetInfo(ref byte blVerMaj, ref byte blVerMin)
    {
        byte[] bb = {
            (byte)Commands.BL_GET_INFO,
            0
        };
        var Result = SendBINCommand(bb, 0, 1, bb, 1000);
        if (Result == 0)
        {
            blVerMin = bb[0];
            blVerMaj = bb[1];
            Debug.Print("Bootloader information: Version=" + blVerMaj + "." + blVerMin);
        }
        return Result;
    }

    public Int32 BlEraseFlash()
    {
        byte[] bb = {
            (byte)Commands.BL_ERASE_FLASH,
            0x34,
            0x12,
            0x21,
            0x43
        };
        Debug.Print("BlEraseFlash");
        return SendBINCommand(bb, 0, 5, null, 6000);
    }

    public Int32 BlProgramFlash(UInt32 pfAddr, ref byte[] byteBuff, int bbOffset, int bbCount)
    {
        byte[] bb = new byte[65];
        if (bbCount > 0)
        {
            bb[0] = (byte)Commands.BL_PROGRAM_FLASH;
            bb[1] = 0x34;
            bb[2] = 0x12;
            bb[3] = 0x21;
            bb[4] = 0x43;
            bb[5] = (byte)(pfAddr & 0xffL);
            bb[6] = (byte)((pfAddr >> 8) & 0xffL);
            bb[7] = (byte)((pfAddr >> 16) & 0xffL);
            bb[8] = (byte)((pfAddr >> 24) & 0xffL);
            bb[9] = (byte)(bbCount & 0xffL);
            bb[10] = (byte)((bbCount >> 8) & 0xffL);
            bb[11] = (byte)((bbCount >> 16) & 0xffL);
            bb[12] = (byte)((bbCount >> 24) & 0xffL);
            for (int i = 0; i <= bbCount - 1; i++)
            {
                bb[13 + i] = byteBuff[bbOffset + i];
            }
            return SendBINCommand(bb, 0, 13 + bbCount, null, 1000);
        }
        else
        {
            return 0;
        }
    }

    public Int32 BlProgramComplete()
    {
        byte[] bb = {
            (byte)Commands.BL_PROGRAM_COMPLETE,
            0x34,
            0x12,
            0x21,
            0x43
        };
        Debug.Print("BlProgramComplete");
        return SendBINCommand(bb, 0, 5, null, 1000);
    }

    public Int32 BlReadCRC(UInt32 pfAddr, UInt32 pfCount, ref UInt16 pfCRC)
    {
        if (pfCount > 0)
        {
            byte[] bb = {
                (byte)Commands.BL_READ_CRC,
                (byte)(pfAddr & 0xffL),
                (byte)((pfAddr >> 8) & 0xffL),
                (byte)((pfAddr >> 16) & 0xffL),
                (byte)((pfAddr >> 24) & 0xffL),
                (byte)(pfCount & 0xffL),
                (byte)((pfCount >> 8) & 0xffL),
                (byte)((pfCount >> 16) & 0xffL),
                (byte)((pfCount >> 24) & 0xffL)
            };
            var Result = SendBINCommand(bb, 0, 9, bb, 5000);
            if (Result == 0)
            {
                pfCRC = bb[1];
                pfCRC <<= 8;
                pfCRC += bb[0];
            }
            return Result;
        }
        return 0;
    }

    public void BlJumpToApplication()
    {
        byte[] bb = { (byte)Commands.BL_JUMP_TO_APP };
        SendBINCommand(bb, 0, 1, null, 0);
    }

    private int SendBINCommand(byte[] OutBuffer, int OutOffset, int OutCount, byte[] RespBuffer = null, int TimeOut = 5000)
    {
        int rv = 0;
        byte[] OB = new byte[64];
        if (OutCount > 0)
        {
            lock (TOTimer)
            {
                Array.Copy(OutBuffer, OB, OutCount);
                //while (OutCount-->0) OB[OutCount] = OutBuffer[OutCount];
                //for (int i = 0; i <= OutCount - 1; i++)
                //{
                //OB[i] = OutBuffer[i];
                //}
                Transport.Write(ref OB, 0, 64);
                //wait for feedback
                if (TimeOut > 0)
                {
                    CommandFeedBack.IsEmpty = true;
                    rv = -1;
                    TOTimer.Restart();
                    while (TOTimer.ElapsedMilliseconds < TimeOut)
                    {
                        if (!CommandFeedBack.IsEmpty)
                        {
                            if (OutBuffer[0] == CommandFeedBack.Command)
                            {
                                rv = CommandFeedBack.Status;
                                if (RespBuffer != null)
                                {
                                    Array.Copy(CommandFeedBack.Data, RespBuffer, Math.Min(RespBuffer.Length, (int)CommandFeedBack.DataLength));
                                }
                                break;
                            }
                            else
                            {
                                CommandFeedBack.IsEmpty = true;
                            }
                        }
                    }
                    TOTimer.Stop();
                }
            }
        }
        return rv;
    }


    private byte[] RXFBuff = new byte[65];
    private void Transport_DataReceived(object sender, EventArgs e)
    {
        int rlen;
        byte[] RXB = new byte[65];
        while (Transport.RXDataCount >= 64)
        {
            rlen = Transport.Read(ref RXB, 0, 64);
            ProcessRXMessage(ref RXB);
        }
    }

    private bool ProcessRXMessage(ref byte[] RXB)
    {
        switch (RXB[0])
        {
            case 1:
                InstrumentChange(this, new EventArgs());
                break;
            case 3:
                LiveDataReceived(this, new LiveDataReceivedEventData() { Data = RXB });
                break;
            default:
                CommandFeedBack.ReadFromBuffer(ref RXB, 0, 64);
                break;
        }
        return true;
    }

    private UInt16 CalculateCRC(ref byte[] data, int boff, int blen)
    {
        UInt16[] crc_table = {
            0x0,
            0x1021,
            0x2042,
            0x3063,
            0x4084,
            0x50a5,
            0x60c6,
            0x70e7,
            0x8108,
            0x9129,
            0xa14a,
            0xb16b,
            0xc18c,
            0xd1ad,
            0xe1ce,
            0xf1ef
        };
        UInt32 i;
        UInt16 crc = 0;

        while (blen > 0)
        {
            i = (UInt32)((crc >> 12) ^ (data[boff] >> 4));
            crc = (UInt16)(crc_table[i & 15] ^ (crc << 4));
            i = (UInt32)((crc >> 12) ^ (UInt32)data[boff]);
            crc = (UInt16)(crc_table[i & 15] ^ (crc << 4));
            boff++;
            blen--;
        }
        return crc;
    }
}

