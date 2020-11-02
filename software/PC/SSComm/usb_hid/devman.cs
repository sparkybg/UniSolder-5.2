///  <summary>
///  Routines for detecting devices and receiving device notifications.
///  </summary>

using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SSComm
{
    internal sealed partial class DeviceManagement
    {
        ///  <summary>
        ///  Compares two device path names. Used to find out if the device name 
        ///  of a recently attached or removed device matches the name of a 
        ///  device the application is communicating with.
        ///  </summary>
        ///  
        ///  <param name="m"> a WM_DEVICECHANGE message. A call to RegisterDeviceNotification
        ///  causes WM_DEVICECHANGE messages to be passed to an OnDeviceChange routine.. </param>
        ///  <param name="mydevicePathName"> a device pathname returned by 
        ///  SetupDiGetDeviceInterfaceDetail in an SP_DEVICE_INTERFACE_DETAIL_DATA structure. </param>
        ///  
        ///  <returns>
        ///  True if the names match, False if not.
        ///  </returns>
        ///  
        internal Boolean DeviceNameMatch(Message m, String mydevicePathName)
        {
            Int32 stringSize;

            try
            {
                DEV_BROADCAST_DEVICEINTERFACE_1 devBroadcastDeviceInterface = new DEV_BROADCAST_DEVICEINTERFACE_1();
                DEV_BROADCAST_HDR devBroadcastHeader = new DEV_BROADCAST_HDR();

                // The LParam parameter of Message is a pointer to a DEV_BROADCAST_HDR structure.

                Marshal.PtrToStructure(m.LParam, devBroadcastHeader);

                if ((devBroadcastHeader.dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE))
                {
                    // The dbch_devicetype parameter indicates that the event applies to a device interface.
                    // So the structure in LParam is actually a DEV_BROADCAST_INTERFACE structure, 
                    // which begins with a DEV_BROADCAST_HDR.

                    // Obtain the number of characters in dbch_name by subtracting the 32 bytes
                    // in the strucutre that are not part of dbch_name and dividing by 2 because there are 
                    // 2 bytes per character.

                    stringSize = System.Convert.ToInt32((devBroadcastHeader.dbch_size - 32) / 2);

                    // The dbcc_name parameter of devBroadcastDeviceInterface contains the device name. 
                    // Trim dbcc_name to match the size of the String.         

                    devBroadcastDeviceInterface.dbcc_name = new Char[stringSize + 1];

                    // Marshal data from the unmanaged block pointed to by m.LParam 
                    // to the managed object devBroadcastDeviceInterface.

                    Marshal.PtrToStructure(m.LParam, devBroadcastDeviceInterface);

                    // Store the device name in a String.

                    String DeviceNameString = new String(devBroadcastDeviceInterface.dbcc_name, 0, stringSize);

                    // Compare the name of the newly attached device with the name of the device 
                    // the application is accessing (mydevicePathName).
                    // Set ignorecase True.

                    if ((String.Compare(DeviceNameString, mydevicePathName, true) == 0))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            catch (Exception ex)
            {
                throw;
            }

            return false;
        }

        ///  <summary>
        ///  Use SetupDi API functions to retrieve the device path name of an
        ///  attached device that belongs to a device interface class.
        ///  </summary>
        ///  
        ///  <param name="myGuid"> an interface class GUID. </param>
        ///  <param name="devicePathName"> a pointer to the device path name 
        ///  of an attached device. </param>
        ///  
        ///  <returns>
        ///   True if a device is found, False if not. 
        ///  </returns>

        internal Boolean FindDeviceFromGuid(System.Guid myGuid, ref String[] devicePathName)
        {
            Int32 bufferSize = 0;
            IntPtr detailDataBuffer = IntPtr.Zero;
            Boolean deviceFound;
            IntPtr deviceInfoSet = new System.IntPtr();
            Boolean lastDevice = false;
            Int32 memberIndex = 0;
            SP_DEVICE_INTERFACE_DATA MyDeviceInterfaceData = new SP_DEVICE_INTERFACE_DATA();
            Boolean success;

            try
            {
                // ***
                //  API function

                //  summary 
                //  Retrieves a device information set for a specified group of devices.
                //  SetupDiEnumDeviceInterfaces uses the device information set.

                //  parameters 
                //  Interface class GUID.
                //  Null to retrieve information for all device instances.
                //  Optional handle to a top-level window (unused here).
                //  Flags to limit the returned information to currently present devices 
                //  and devices that expose interfaces in the class specified by the GUID.

                //  Returns
                //  Handle to a device information set for the devices.
                // ***

                deviceInfoSet = SetupDiGetClassDevs(ref myGuid, IntPtr.Zero, IntPtr.Zero, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

                deviceFound = false;
                memberIndex = 0;

                // The cbSize element of the MyDeviceInterfaceData structure must be set to
                // the structure's size in bytes. 
                // The size is 28 bytes for 32-bit code and 32 bits for 64-bit code.

                MyDeviceInterfaceData.cbSize = Marshal.SizeOf(MyDeviceInterfaceData);

                do
                {
                    // Begin with 0 and increment through the device information set until
                    // no more devices are available.

                    // ***
                    //  API function

                    //  summary
                    //  Retrieves a handle to a SP_DEVICE_INTERFACE_DATA structure for a device.
                    //  On return, MyDeviceInterfaceData contains the handle to a
                    //  SP_DEVICE_INTERFACE_DATA structure for a detected device.

                    //  parameters
                    //  DeviceInfoSet returned by SetupDiGetClassDevs.
                    //  Optional SP_DEVINFO_DATA structure that defines a device instance 
                    //  that is a member of a device information set.
                    //  Device interface GUID.
                    //  Index to specify a device in a device information set.
                    //  Pointer to a handle to a SP_DEVICE_INTERFACE_DATA structure for a device.

                    //  Returns
                    //  True on success.
                    // ***

                    success = SetupDiEnumDeviceInterfaces
                        (deviceInfoSet,
                        IntPtr.Zero,
                        ref myGuid,
                        memberIndex,
                        ref MyDeviceInterfaceData);

                    // Find out if a device information set was retrieved.

                    if (!success)
                    {
                        lastDevice = true;

                    }
                    else
                    {
                        // A device is present.

                        // ***
                        //  API function: 

                        //  summary:
                        //  Retrieves an SP_DEVICE_INTERFACE_DETAIL_DATA structure
                        //  containing information about a device.
                        //  To retrieve the information, call this function twice.
                        //  The first time returns the size of the structure.
                        //  The second time returns a pointer to the data.

                        //  parameters
                        //  DeviceInfoSet returned by SetupDiGetClassDevs
                        //  SP_DEVICE_INTERFACE_DATA structure returned by SetupDiEnumDeviceInterfaces
                        //  A returned pointer to an SP_DEVICE_INTERFACE_DETAIL_DATA 
                        //  Structure to receive information about the specified interface.
                        //  The size of the SP_DEVICE_INTERFACE_DETAIL_DATA structure.
                        //  Pointer to a variable that will receive the returned required size of the 
                        //  SP_DEVICE_INTERFACE_DETAIL_DATA structure.
                        //  Returned pointer to an SP_DEVINFO_DATA structure to receive information about the device.

                        //  Returns
                        //  True on success.
                        // ***                     

                        success = SetupDiGetDeviceInterfaceDetail
                            (deviceInfoSet,
                            ref MyDeviceInterfaceData,
                            IntPtr.Zero,
                            0,
                            ref bufferSize,
                            IntPtr.Zero);

                        // Allocate memory for the SP_DEVICE_INTERFACE_DETAIL_DATA structure using the returned buffer size.

                        detailDataBuffer = Marshal.AllocHGlobal(bufferSize);

                        // Store cbSize in the first bytes of the array. The number of bytes varies with 32- and 64-bit systems.

                        Marshal.WriteInt32(detailDataBuffer, (IntPtr.Size == 4) ? (4 + Marshal.SystemDefaultCharSize) : 8);

                        // Call SetupDiGetDeviceInterfaceDetail again.
                        // This time, pass a pointer to DetailDataBuffer
                        // and the returned required buffer size.

                        success = SetupDiGetDeviceInterfaceDetail
                            (deviceInfoSet,
                            ref MyDeviceInterfaceData,
                            detailDataBuffer,
                            bufferSize,
                            ref bufferSize,
                            IntPtr.Zero);

                        // Skip over cbsize (4 bytes) to get the address of the devicePathName.

                        IntPtr pDevicePathName = new IntPtr(detailDataBuffer.ToInt32() + 4);

                        // Get the String containing the devicePathName.

                        devicePathName[memberIndex] = Marshal.PtrToStringAuto(pDevicePathName);

                        if (detailDataBuffer != IntPtr.Zero)
                        {
                            // Free the memory allocated previously by AllocHGlobal.

                            Marshal.FreeHGlobal(detailDataBuffer);
                        }
                        deviceFound = true;
                    }
                    memberIndex = memberIndex + 1;
                }
                while (!((lastDevice == true)));



                return deviceFound;
            }
            catch (Exception ex)
            {
                throw;
            }
            finally
            {

                // ***
                //  API function

                //  summary
                //  Frees the memory reserved for the DeviceInfoSet returned by SetupDiGetClassDevs.

                //  parameters
                //  DeviceInfoSet returned by SetupDiGetClassDevs.

                //  returns
                //  True on success.
                // ***

                if (deviceInfoSet != IntPtr.Zero)
                {
                    SetupDiDestroyDeviceInfoList(deviceInfoSet);
                }
            }
        }


        ///  <summary>
        ///  Requests to receive a notification when a device is attached or removed.
        ///  </summary>
        ///  
        ///  <param name="devicePathName"> handle to a device. </param>
        ///  <param name="formHandle"> handle to the window that will receive device events. </param>
        ///  <param name="classGuid"> device interface GUID. </param>
        ///  <param name="deviceNotificationHandle"> returned device notification handle. </param>
        ///  
        ///  <returns>
        ///  True on success.
        ///  </returns>
        ///  
        internal Boolean RegisterForDeviceNotifications(String devicePathName, IntPtr formHandle, Guid classGuid, ref IntPtr deviceNotificationHandle)
        {
            // A DEV_BROADCAST_DEVICEINTERFACE header holds information about the request.

            DEV_BROADCAST_DEVICEINTERFACE devBroadcastDeviceInterface = new DEV_BROADCAST_DEVICEINTERFACE();
            IntPtr devBroadcastDeviceInterfaceBuffer = IntPtr.Zero;
            Int32 size = 0;

            try
            {
                // Set the parameters in the DEV_BROADCAST_DEVICEINTERFACE structure.

                // Set the size.

                size = Marshal.SizeOf(devBroadcastDeviceInterface);
                devBroadcastDeviceInterface.dbcc_size = size;

                // Request to receive notifications about a class of devices.

                devBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

                devBroadcastDeviceInterface.dbcc_reserved = 0;

                // Specify the interface class to receive notifications about.

                devBroadcastDeviceInterface.dbcc_classguid = classGuid;

                // Allocate memory for the buffer that holds the DEV_BROADCAST_DEVICEINTERFACE structure.

                devBroadcastDeviceInterfaceBuffer = Marshal.AllocHGlobal(size);

                // Copy the DEV_BROADCAST_DEVICEINTERFACE structure to the buffer.
                // Set fDeleteOld True to prevent memory leaks.

                Marshal.StructureToPtr(devBroadcastDeviceInterface, devBroadcastDeviceInterfaceBuffer, true);

                // ***
                //  API function

                //  summary
                //  Request to receive notification messages when a device in an interface class
                //  is attached or removed.

                //  parameters 
                //  Handle to the window that will receive device events.
                //  Pointer to a DEV_BROADCAST_DEVICEINTERFACE to specify the type of 
                //  device to send notifications for.
                //  DEVICE_NOTIFY_WINDOW_HANDLE indicates the handle is a window handle.

                //  Returns
                //  Device notification handle or NULL on failure.
                // ***

                deviceNotificationHandle = RegisterDeviceNotification(formHandle, devBroadcastDeviceInterfaceBuffer, DEVICE_NOTIFY_WINDOW_HANDLE);

                // Marshal data from the unmanaged block devBroadcastDeviceInterfaceBuffer to
                // the managed object devBroadcastDeviceInterface

                Marshal.PtrToStructure(devBroadcastDeviceInterfaceBuffer, devBroadcastDeviceInterface);



                if ((deviceNotificationHandle.ToInt32() == IntPtr.Zero.ToInt32()))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
            catch (Exception ex)
            {
                throw;
            }
            finally
            {
                if (devBroadcastDeviceInterfaceBuffer != IntPtr.Zero)
                {
                    // Free the memory allocated previously by AllocHGlobal.

                    Marshal.FreeHGlobal(devBroadcastDeviceInterfaceBuffer);
                }
            }
        }

        ///  <summary>
        ///  Requests to stop receiving notification messages when a device in an
        ///  interface class is attached or removed.
        ///  </summary>
        ///  
        ///  <param name="deviceNotificationHandle"> handle returned previously by
        ///  RegisterDeviceNotification. </param>

        internal void StopReceivingDeviceNotifications(IntPtr deviceNotificationHandle)
        {
            try
            {
                // ***
                //  API function

                //  summary
                //  Stop receiving notification messages.

                //  parameters
                //  Handle returned previously by RegisterDeviceNotification.  

                //  returns
                //  True on success.
                // ***

                //  Ignore failures.

                DeviceManagement.UnregisterDeviceNotification(deviceNotificationHandle);
            }
            catch (Exception ex)
            {
                throw;
            }
        }
    }
}




