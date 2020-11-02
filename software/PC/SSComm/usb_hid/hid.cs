using Microsoft.VisualBasic;
using Microsoft.Win32.SafeHandles;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;

///  <summary>
///  For communicating with HID-class USB devices.
///  Includes routines for sending and receiving reports via control transfers and to 
///  retrieve information about and configure a HID.
///  </summary>
///  

namespace SSComm
{
    internal sealed partial class Hid
    {
        //  Used in error messages.

        private const String MODULE_NAME = "Hid";

        internal HIDP_CAPS Capabilities;
        internal HIDD_ATTRIBUTES DeviceAttributes;

        //  For viewing results of API calls in debug.write statements:

        //internal static Debugging MyDebugging = new Debugging();

        ///  <summary>
        ///  Remove any Input reports waiting in the buffer.
        ///  </summary>
        ///  
        ///  <param name="hidHandle"> a handle to a device.   </param>
        ///  
        ///  <returns>
        ///  True on success, False on failure.
        ///  </returns>

        internal Boolean FlushQueue(SafeFileHandle hidHandle)
        {
            Boolean success = false;

            try
            {
                //  ***
                //  API function: HidD_FlushQueue

                //  Purpose: Removes any Input reports waiting in the buffer.

                //  Accepts: a handle to the device.

                //  Returns: True on success, False on failure.
                //  ***

                success = HidD_FlushQueue(hidHandle);

                return success;
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }

        ///  <summary>
        ///  Retrieves a structure with information about a device's capabilities. 
        ///  </summary>
        ///  
        ///  <param name="hidHandle"> a handle to a device. </param>
        ///  
        ///  <returns>
        ///  An HIDP_CAPS structure.
        ///  </returns>

        internal HIDP_CAPS GetDeviceCapabilities(SafeFileHandle hidHandle)
        {
            IntPtr preparsedData = new System.IntPtr();
            Int32 result = 0;
            Boolean success = false;

            try
            {
                //  ***
                //  API function: HidD_GetPreparsedData

                //  Purpose: retrieves a pointer to a buffer containing information about the device's capabilities.
                //  HidP_GetCaps and other API functions require a pointer to the buffer.

                //  Requires: 
                //  A handle returned by CreateFile.
                //  A pointer to a buffer.

                //  Returns:
                //  True on success, False on failure.
                //  ***

                success = HidD_GetPreparsedData(hidHandle, ref preparsedData);

                //  ***
                //  API function: HidP_GetCaps

                //  Purpose: find out a device's capabilities.
                //  For standard devices such as joysticks, you can find out the specific
                //  capabilities of the device.
                //  For a custom device where the software knows what the device is capable of,
                //  this call may be unneeded.

                //  Accepts:
                //  A pointer returned by HidD_GetPreparsedData
                //  A pointer to a HIDP_CAPS structure.

                //  Returns: True on success, False on failure.
                //  ***

                result = HidP_GetCaps(preparsedData, ref Capabilities);
                if ((result != 0))
                {
                    Debug.WriteLine("");
                    Debug.WriteLine("  Usage: " + Convert.ToString(Capabilities.Usage, 16));
                    Debug.WriteLine("  Usage Page: " + Convert.ToString(Capabilities.UsagePage, 16));
                    Debug.WriteLine("  Input Report Byte Length: " + Capabilities.InputReportByteLength);
                    Debug.WriteLine("  Output Report Byte Length: " + Capabilities.OutputReportByteLength);
                    Debug.WriteLine("  Feature Report Byte Length: " + Capabilities.FeatureReportByteLength);
                    Debug.WriteLine("  Number of Link Collection Nodes: " + Capabilities.NumberLinkCollectionNodes);
                    Debug.WriteLine("  Number of Input Button Caps: " + Capabilities.NumberInputButtonCaps);
                    Debug.WriteLine("  Number of Input Value Caps: " + Capabilities.NumberInputValueCaps);
                    Debug.WriteLine("  Number of Input Data Indices: " + Capabilities.NumberInputDataIndices);
                    Debug.WriteLine("  Number of Output Button Caps: " + Capabilities.NumberOutputButtonCaps);
                    Debug.WriteLine("  Number of Output Value Caps: " + Capabilities.NumberOutputValueCaps);
                    Debug.WriteLine("  Number of Output Data Indices: " + Capabilities.NumberOutputDataIndices);
                    Debug.WriteLine("  Number of Feature Button Caps: " + Capabilities.NumberFeatureButtonCaps);
                    Debug.WriteLine("  Number of Feature Value Caps: " + Capabilities.NumberFeatureValueCaps);
                    Debug.WriteLine("  Number of Feature Data Indices: " + Capabilities.NumberFeatureDataIndices);

                    //  ***
                    //  API function: HidP_GetValueCaps

                    //  Purpose: retrieves a buffer containing an array of HidP_ValueCaps structures.
                    //  Each structure defines the capabilities of one value.
                    //  This application doesn't use this data.

                    //  Accepts:
                    //  A report type enumerator from hidpi.h,
                    //  A pointer to a buffer for the returned array,
                    //  The NumberInputValueCaps member of the device's HidP_Caps structure,
                    //  A pointer to the PreparsedData structure returned by HidD_GetPreparsedData.

                    //  Returns: True on success, False on failure.
                    //  ***                    

                    Int32 vcSize = Capabilities.NumberInputValueCaps;
                    Byte[] valueCaps = new Byte[vcSize];

                    result = HidP_GetValueCaps(HidP_Input, valueCaps, ref vcSize, preparsedData);

                    // (To use this data, copy the ValueCaps byte array into an array of structures.)                   

                }
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
            finally
            {
                //  ***
                //  API function: HidD_FreePreparsedData

                //  Purpose: frees the buffer reserved by HidD_GetPreparsedData.

                //  Accepts: A pointer to the PreparsedData structure returned by HidD_GetPreparsedData.

                //  Returns: True on success, False on failure.
                //  ***

                if (preparsedData != IntPtr.Zero)
                {
                    success = HidD_FreePreparsedData(preparsedData);
                }
            }

            return Capabilities;
        }

        ///  <summary>
        ///  reads a Feature report from the device.
        ///  </summary>
        ///  
        ///  <param name="hidHandle"> the handle for learning about the device and exchanging Feature reports. </param>	
        ///  <param name="myDeviceDetected"> tells whether the device is currently attached.</param>
        ///  <param name="inFeatureReportBuffer"> contains the requested report.</param>
        ///  <param name="success"> read success</param>

        internal Boolean GetFeatureReport(SafeFileHandle hidHandle, ref Byte[] inFeatureReportBuffer)
        {
            Boolean success;

            try
            {
                //  ***
                //  API function: HidD_GetFeature
                //  Attempts to read a Feature report from the device.

                //  Requires:
                //  A handle to a HID
                //  A pointer to a buffer containing the report ID and report
                //  The size of the buffer. 

                //  Returns: true on success, false on failure.
                //  ***                    

                success = HidD_GetFeature(hidHandle, inFeatureReportBuffer, inFeatureReportBuffer.Length);

                Debug.Print("HidD_GetFeature success = " + success);
                return success;
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }


        ///  <summary>
        ///  Creates a 32-bit Usage from the Usage Page and Usage ID. 
        ///  Determines whether the Usage is a system mouse or keyboard.
        ///  Can be modified to detect other Usages.
        ///  </summary>
        ///  
        ///  <param name="MyCapabilities"> a HIDP_CAPS structure retrieved with HidP_GetCaps. </param>
        ///  
        ///  <returns>
        ///  A String describing the Usage.
        ///  </returns>

        internal String GetHidUsage(HIDP_CAPS MyCapabilities)
        {
            Int32 usage = 0;
            String usageDescription = "";

            try
            {
                //  Create32-bit Usage from Usage Page and Usage ID.

                usage = MyCapabilities.UsagePage * 256 + MyCapabilities.Usage;

                if (usage == Convert.ToInt32(0X102))
                {
                    usageDescription = "mouse";
                }

                if (usage == Convert.ToInt32(0X106))
                {
                    usageDescription = "keyboard";
                }
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }

            return usageDescription;
        }


        ///  <summary>
        ///  reads an Input report from the device using a control transfer.
        ///  </summary>
        ///  
        ///  <param name="hidHandle"> the handle for learning about the device and exchanging Feature reports. </param>
        ///  <param name="myDeviceDetected"> tells whether the device is currently attached. </param>
        ///  <param name="inputReportBuffer"> contains the requested report. </param>
        ///  <param name="success"> read success </param>

        internal Boolean GetInputReportViaControlTransfer(SafeFileHandle hidHandle, ref Byte[] inputReportBuffer)
        {
            Boolean success;

            try
            {
                //  ***
                //  API function: HidD_GetInputReport

                //  Purpose: Attempts to read an Input report from the device using a control transfer.
                //  Supported under Windows XP and later only.

                //  Requires:
                //  A handle to a HID
                //  A pointer to a buffer containing the report ID and report
                //  The size of the buffer. 

                //  Returns: true on success, false on failure.
                //  ***

                success = HidD_GetInputReport(hidHandle, inputReportBuffer, inputReportBuffer.Length + 1);

                Debug.Print("HidD_GetInputReport success = " + success);
                return success;
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }

        ///  <summary>
        ///  Retrieves the number of Input reports the host can store.
        ///  </summary>
        ///  
        ///  <param name="hidDeviceObject"> a handle to a device  </param>
        ///  <param name="numberOfInputBuffers"> an integer to hold the returned value. </param>
        ///  
        ///  <returns>
        ///  True on success, False on failure.
        ///  </returns>

        internal Boolean GetNumberOfInputBuffers(SafeFileHandle hidDeviceObject, ref Int32 numberOfInputBuffers)
        {
            Boolean success = false;

            try
            {
                if (!((IsWindows98Gold())))
                {
                    //  ***
                    //  API function: HidD_GetNumInputBuffers

                    //  Purpose: retrieves the number of Input reports the host can store.
                    //  Not supported by Windows 98 Gold.
                    //  If the buffer is full and another report arrives, the host drops the 
                    //  ldest report.

                    //  Accepts: a handle to a device and an integer to hold the number of buffers. 

                    //  Returns: True on success, False on failure.
                    //  ***

                    success = HidD_GetNumInputBuffers(hidDeviceObject, ref numberOfInputBuffers);
                }
                else
                {
                    //  Under Windows 98 Gold, the number of buffers is fixed at 2.

                    numberOfInputBuffers = 2;
                    success = true;
                }

                return success;
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }
        ///  <summary>
        ///  writes a Feature report to the device.
        ///  </summary>
        ///  
        ///  <param name="outFeatureReportBuffer"> contains the report ID and report data. </param>
        ///  <param name="hidHandle"> handle to the device.  </param>
        ///  
        ///  <returns>
        ///   True on success. False on failure.
        ///  </returns>            

        internal Boolean SendFeatureReport(SafeFileHandle hidHandle, Byte[] outFeatureReportBuffer)
        {
            Boolean success = false;

            try
            {
                //  ***
                //  API function: HidD_SetFeature

                //  Purpose: Attempts to send a Feature report to the device.

                //  Accepts:
                //  A handle to a HID
                //  A pointer to a buffer containing the report ID and report
                //  The size of the buffer. 

                //  Returns: true on success, false on failure.
                //  ***

                success = HidD_SetFeature(hidHandle, outFeatureReportBuffer, outFeatureReportBuffer.Length);

                Debug.Print("HidD_SetFeature success = " + success);

                return success;
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }
        ///  <summary>
        ///  Writes an Output report to the device using a control transfer.
        ///  </summary>
        ///  
        ///  <param name="outputReportBuffer"> contains the report ID and report data. </param>
        ///  <param name="hidHandle"> handle to the device.  </param>
        ///  
        ///  <returns>
        ///   True on success. False on failure.
        ///  </returns>            

        internal Boolean SendOutputReportViaControlTransfer(SafeFileHandle hidHandle, Byte[] outputReportBuffer)
        {
            Boolean success = false;

            try
            {
                //  ***
                //  API function: HidD_SetOutputReport

                //  Purpose: 
                //  Attempts to send an Output report to the device using a control transfer.
                //  Requires Windows XP or later.

                //  Accepts:
                //  A handle to a HID
                //  A pointer to a buffer containing the report ID and report
                //  The size of the buffer. 

                //  Returns: true on success, false on failure.
                //  ***                    

                success = HidD_SetOutputReport(hidHandle, outputReportBuffer, outputReportBuffer.Length + 1);

                Debug.Print("HidD_SetOutputReport success = " + success);

                return success;
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }

        ///  <summary>
        ///  sets the number of input reports the host will store.
        ///  Requires Windows XP or later.
        ///  </summary>
        ///  
        ///  <param name="hidDeviceObject"> a handle to the device.</param>
        ///  <param name="numberBuffers"> the requested number of input reports.  </param>
        ///  
        ///  <returns>
        ///  True on success. False on failure.
        ///  </returns>

        internal Boolean SetNumberOfInputBuffers(SafeFileHandle hidDeviceObject, Int32 numberBuffers)
        {
            try
            {
                if (!IsWindows98Gold())
                {
                    //  ***
                    //  API function: HidD_SetNumInputBuffers

                    //  Purpose: Sets the number of Input reports the host can store.
                    //  If the buffer is full and another report arrives, the host drops the 
                    //  oldest report.

                    //  Requires:
                    //  A handle to a HID
                    //  An integer to hold the number of buffers. 

                    //  Returns: true on success, false on failure.
                    //  ***

                    HidD_SetNumInputBuffers(hidDeviceObject, numberBuffers);
                    return true;
                }
                else
                {
                    //  Not supported under Windows 98 Gold.

                    return false;
                }
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }

        ///  <summary>
        ///  Find out if the current operating system is Windows XP or later.
        ///  (Windows XP or later is required for HidD_GetInputReport and HidD_SetInputReport.)
        ///  </summary>

        internal Boolean IsWindowsXpOrLater()
        {
            try
            {
                OperatingSystem myEnvironment = Environment.OSVersion;

                //  Windows XP is version 5.1.

                System.Version versionXP = new System.Version(5, 1);

                if (myEnvironment.Version >= versionXP)
                {
                    Debug.Write("The OS is Windows XP or later.");
                    return true;
                }
                else
                {
                    Debug.Write("The OS is earlier than Windows XP.");
                    return false;
                }
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }

        ///  <summary>
        ///  Find out if the current operating system is Windows 98 Gold (original version).
        ///  Windows 98 Gold does not support the following:
        ///  Interrupt OUT transfers (WriteFile uses control transfers and Set_Report).
        ///  HidD_GetNumInputBuffers and HidD_SetNumInputBuffers
        ///  (Not yet tested on a Windows 98 Gold system.)
        ///  </summary>

        internal Boolean IsWindows98Gold()
        {
            Boolean result = false;
            try
            {
                OperatingSystem myEnvironment = Environment.OSVersion;

                //  Windows 98 Gold is version 4.10 with a build number less than 2183.

                System.Version version98SE = new System.Version(4, 10, 2183);

                if (myEnvironment.Version < version98SE)
                {
                    Debug.Write("The OS is Windows 98 Gold.");
                    result = true;
                }
                else
                {
                    Debug.Write("The OS is more recent than Windows 98 Gold.");
                    result = false;
                }
                return result;
            }
            catch (Exception ex)
            {
                DisplayException(MODULE_NAME, ex);
                throw;
            }
        }

        ///  <summary>
        ///  Provides a central mechanism for exception handling.
        ///  Displays a message box that describes the exception.
        ///  </summary>
        ///  
        ///  <param name="moduleName">  the module where the exception occurred. </param>
        ///  <param name="e"> the exception </param>

        internal static void DisplayException(String moduleName, Exception e)
        {
            String message = null;
            String caption = null;

            //  Create an error message.

            //message = "Exception: " + e.Message + ControlChars.CrLf + "Module: " + moduleName + ControlChars.CrLf + "Method: " + e.TargetSite.Name;

            caption = "Unexpected Exception";

            MessageBox.Show(message, caption, MessageBoxButtons.OK);
            Debug.Write(message);
        }
    }
}
