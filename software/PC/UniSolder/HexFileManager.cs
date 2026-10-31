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

        /// <summary>Reason of the last LoadHexFile failure.</summary>
        public string LastError { get; private set; }

        //physical addresses as found in the HEX file (see bootloader.ld / firmware.ld)
        public const UInt32 BOOTLOADER_FLASH_START = 0x1D000000;
        public const UInt32 APP_FLASH_START = 0x1D003000;
        //64-byte USB packet minus 13 header bytes (command, key, address, length)
        public const int MAX_RECORD_DATA = 51;

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
            try
            {
                return LoadHexFileLines(filepath);
            }
            catch (Exception ex) when (ex is FormatException || ex is ArgumentOutOfRangeException || ex is IOException)
            {
                LastError = "cannot read the file: " + ex.Message;
                return false;
            }
        }

        private bool LoadHexFileLines(string filepath)
        {
            UInt32 cExtSegAddress = 0;
            UInt32 cExtLinAddress = 0;
            int lineNumber = 0;
            LastError = null;
            Records.Clear();
            using (var FileReader = new StreamReader(filepath))
            while (!FileReader.EndOfStream)
            {
                var s = FileReader.ReadLine().Trim();
                lineNumber++;
                if (s.Length >= 11)
                {
                    if (s[0] == ':')
                    {
                        //declared data length must match the line length (":" + count, address, type, data, checksum)
                        if (s.Length != 11 + 2 * Convert.ToInt32(s.Substring(1, 2), 16))
                        {
                            LastError = "line " + lineNumber + ": length does not match its byte count";
                            return false;
                        }
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
                            LastError = "line " + lineNumber + ": bad checksum";
                            return false;
                        }
                    }
                    else
                    {
                        LastError = "line " + lineNumber + ": does not start with ':'";
                        return false;
                    }
                }
            }
            return true;
        }

        /// <summary>
        /// Checks that the loaded file is a firmware built for the UniSolder bootloader (PIC32_with_bootloader),
        /// before anything is sent to the device. Returns null if the file can be used, otherwise the reason.
        /// </summary>
        public string Validate()
        {
            if (Records.Count == 0) return "the file contains no data.";
            bool hasAppStart = false;
            foreach (var r in Records)
            {
                UInt32 end = r.Address + r.RecDataLen; //exclusive
                //the bootloader skips its address check for records of 512 bytes or more: never send big records
                if (r.RecDataLen > MAX_RECORD_DATA)
                    return "record at 0x" + r.Address.ToString("X8") + " has " + r.RecDataLen + " bytes, more than the " + MAX_RECORD_DATA + " bytes a USB packet can carry.";
                if (r.Address < APP_FLASH_START && end > BOOTLOADER_FLASH_START)
                    return "the file contains code in the bootloader area (0x1D000000-0x1D002FFF). It is probably a firmware built without bootloader (PIC32_Standalone): use the PIC32_with_bootloader HEX file.";
                if (r.Address <= APP_FLASH_START && end > APP_FLASH_START) hasAppStart = true;
            }
            if (!hasAppStart)
                return "the file contains no code at the application start address 0x1D003000: it is not a firmware built for the UniSolder bootloader (PIC32_with_bootloader).";
            return null;
        }
    }
}
