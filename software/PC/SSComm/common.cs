using System;

namespace SSComm
{

    public interface IUniComm : IDisposable
    {
        bool Connected { get; }
        Int32 BytesSent();
        Int32 BytesReceived();
        void Init();
        bool Connect();
        void Disconnect();
        byte ReadByte();
        Int32 Read(ref byte[] DBuffer, Int32 DOffset, Int32 MaxBytes);
        void WriteByte(ref byte wb, bool DoWake = true);
        bool Write(ref byte[] DBuffer, Int32 DOffset, Int32 NumBytes);
        Int32 RXDataCount { get; }
        Int32 TXFreeSpace { get; }
        event EventHandler DataReceived;
    }
}

