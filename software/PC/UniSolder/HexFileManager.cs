using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UniSolder
{
    public class HexFileManager
    {
        private byte[] VirtualFlash = new byte[5 * 1024 * 1024 + 1];
        private const UInt32 BOOT_SECTOR_BEGIN = 0x9fc00000;

        private const UInt32 APPLICATION_START = 0x9d000000;
        private const byte DATA_RECORD = 0;
        private const byte END_OF_FILE_RECORD = 1;
        private const byte EXT_SEG_ADRS_RECORD = 2;

        private const byte EXT_LIN_ADRS_RECORD = 4;

        public class HexDataRecord
        {
            public UInt32 Address;
            public UInt32 RecDataLen;
            public byte[] Data = new byte[1024];
            public byte CheckSum;
        }

        public List<HexDataRecord> Records = new List<HexDataRecord>();

        private UInt32 PA_TO_VFA(UInt32 x)
        {
            return (x - APPLICATION_START);
        }

        private UInt32 PA_TO_KVA0(UInt32 x)
        {
            return (x | 0x80000000);
        }

        public bool LoadHexFile(string filepath)
        {
            UInt32 cExtSegAddress = 0;
            UInt32 cExtLinAddress = 0;
            var FileReader = new StreamReader(filepath);

            while (!FileReader.EndOfStream)
            {
                var s = FileReader.ReadLine().Trim();
                if (s.Length >= 11)
                {
                    if (s[0] == ':')
                    {
                        UInt32 ccs = 0;
                        for (int i = 0; i <= ((s.Length - 1) / 2) - 2; i++)
                        {
                            ccs = ccs + Convert.ToUInt32(s.Substring(1 + ((int)i * 2), 2), 16);
                            ccs = ccs & 0xff;
                        }
                        ccs = (0x100 - ccs) & 0xff;
                        if (ccs == Convert.ToUInt32(s.Substring(s.Length - 2), 16))// Strings.Right(s, 2)))
                        {
                            var rectype = Convert.ToByte(s.Substring(7, 2), 16); // Strings.Mid(s, 8, 2));
                            switch (rectype)
                            {
                                case DATA_RECORD:
                                    var previous = Records.Count > 0 ? Records.Last() : null;
                                    var current = new HexDataRecord()
                                    {
                                        Address = Convert.ToUInt32(s.Substring(3, 4), 16) + cExtSegAddress + cExtLinAddress,
                                        RecDataLen = Convert.ToUInt32(s.Substring(1, 2), 16)
                                    };
                                    for (int i = 0; i < current.RecDataLen; i++) current.Data[i] = Convert.ToByte(s.Substring(9 + i * 2, 2), 16);
                                    if (previous != null)
                                    {
                                        if (current.Address == (previous.Address + previous.RecDataLen))
                                        {
                                            while (current.RecDataLen > 0)
                                            {
                                                if (previous.RecDataLen < 48)
                                                {
                                                    previous.RecDataLen++;
                                                    previous.Data[previous.RecDataLen-1] = current.Data[0];
                                                    for (int i = 1; i < current.RecDataLen; i++) current.Data[i - 1] = current.Data[i];
                                                    current.Address++;
                                                    current.RecDataLen--;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    if (current.RecDataLen > 0) Records.Add(current);
                                    break;
                                case EXT_SEG_ADRS_RECORD:
                                    cExtSegAddress = Convert.ToUInt32(s.Substring(9, 4), 16) << 8;
                                    cExtLinAddress = 0;
                                    break;
                                case EXT_LIN_ADRS_RECORD:
                                    cExtLinAddress = Convert.ToUInt32(s.Substring(9, 4), 16) << 16;
                                    cExtSegAddress = 0;
                                    break;
                                case END_OF_FILE_RECORD:
                                    break;
                                default:
                                    cExtLinAddress = 0;
                                    cExtSegAddress = 0;
                                    break;
                            }
                        }
                        else
                        {
                            FileReader.Close();
                            return false;
                        }
                    }
                    else
                    {
                        FileReader.Close();
                        return false;
                    }
                }
            }
            foreach (var r in Records)
            {
                var s = "";
                for (int i = 0; i < r.RecDataLen; i++) s += r.Data[i].ToString("X2");
                //Debug.Print(Format(PA_TO_KVA0(.Address), "X8") & "(" & Format(.RecDataLen, "X2") & "): " & s)
            }
            FileReader.Close();
            FileReader = null;
            return true;
        }
    }
}
