using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UniSolder
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            SSComm.Log.Open(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "UniSolder", "UniSolder.log"));
            SSComm.Log.Info("===== UniSolder " + Application.ProductVersion + " started, log: " + SSComm.Log.FilePath);

            //UI thread exceptions: log and report instead of the default WinForms dialog
            Application.ThreadException += (s, e) =>
            {
                SSComm.Log.Error("Unhandled UI exception", e.Exception);
                MessageBox.Show(e.Exception.Message + "\n\nDetails in log file:\n" + SSComm.Log.FilePath, "UniSolder error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            };
            //other threads: the process terminates, at least keep a trace
            AppDomain.CurrentDomain.UnhandledException += (s, e) => SSComm.Log.Error("Unhandled exception (terminating=" + e.IsTerminating + ")", e.ExceptionObject as Exception);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            SSComm.Log.Info("===== UniSolder closed");
            SSComm.Log.Close();
        }
    }
}
