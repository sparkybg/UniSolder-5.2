using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;

namespace SSComm
{
    /// <summary>
    /// Thread-safe log file shared by the transport and the application.
    /// Lines are also echoed to the debugger output. Works in Release builds (unlike Debug.Print).
    /// </summary>
    public static class Log
    {
        private const long MaxSize = 5 * 1024 * 1024; //rotate to .old.log above this size at startup
        private static readonly object Sync = new object();
        private static StreamWriter writer;

        public static string FilePath { get; private set; }

        /// <summary>Raised after each message (level, message), on the logging thread.</summary>
        public static event Action<string, string> MessageLogged;

        public static void Open(string path)
        {
            lock (Sync)
            {
                Close();
                try
                {
                    Directory.CreateDirectory(Path.GetDirectoryName(path));
                    if (File.Exists(path) && new FileInfo(path).Length > MaxSize)
                    {
                        var old = Path.ChangeExtension(path, ".old.log");
                        if (File.Exists(old)) File.Delete(old);
                        File.Move(path, old);
                    }
                    writer = new StreamWriter(new FileStream(path, FileMode.Append, FileAccess.Write, FileShare.ReadWrite), new UTF8Encoding(false)) { AutoFlush = true };
                    FilePath = path;
                }
                catch (Exception ex)
                {
                    writer = null;
                    Debug.WriteLine("Log: cannot open " + path + ": " + ex.Message);
                }
            }
        }

        public static void Close()
        {
            lock (Sync)
            {
                writer?.Dispose();
                writer = null;
            }
        }

        public static void Info(string msg) { Write("INFO ", msg); }
        public static void Warn(string msg) { Write("WARN ", msg); }
        public static void Error(string msg, Exception ex = null) { Write("ERROR", ex == null ? msg : msg + ": " + ex); }

        /// <summary>Hex dump of a buffer slice, e.g. "E2 34 12 21 43".</summary>
        public static string Hex(byte[] b, int offset, int count)
        {
            if (b == null) return "";
            count = Math.Max(0, Math.Min(count, b.Length - offset));
            var sb = new StringBuilder(count * 3);
            for (int i = 0; i < count; i++)
            {
                if (i > 0) sb.Append(' ');
                sb.Append(b[offset + i].ToString("X2"));
            }
            return sb.ToString();
        }

        private static void Write(string level, string msg)
        {
            var line = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff") + " [" + Thread.CurrentThread.ManagedThreadId.ToString("D2") + "] " + level + " " + msg;
            Debug.WriteLine(line);
            lock (Sync)
            {
                try { writer?.WriteLine(line); }
                catch (IOException) { }
            }
            //outside the lock; a failing subscriber must not break logging
            try { MessageLogged?.Invoke(level.Trim(), msg); }
            catch (Exception ex) { Debug.WriteLine("Log: MessageLogged handler failed: " + ex.Message); }
        }
    }
}
