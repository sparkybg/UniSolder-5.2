/********************************************************************
  File Information:
    FileName:     	usb_function_hid.c
    Dependencies:   See INCLUDES section
    Processor:      PIC18 or PIC24 USB Microcontrollers
    Hardware:       The code is natively intended to be used on the following
    				hardware platforms: PICDEM� FS USB Demo Board, 
    				PIC18F87J50 FS USB Plug-In Module, or
    				Explorer 16 + PIC24 USB PIM.  The firmware may be
    				modified for use on other USB platforms by editing the
    				HardwareProfile.h file.
    Complier:  	    Microchip C18 (for PIC18) or C30 (for PIC24)
    Company:        Microchip Technology, Inc.
    
    Software License Agreement:
    
    The software supplied herewith by Microchip Technology Incorporated
    (the �Company�) for its PIC� Microcontroller is intended and
    supplied to you, the Company�s customer, for use solely and
    exclusively on Microchip PIC Microcontroller products. The
    software is owned by the Company and/or its supplier, and is
    protected under applicable copyright laws. All rights are reserved.
    Any use in violation of the foregoing restrictions may subject the
    user to criminal sanctions under applicable laws, as well as to
    civil liability for the breach of the terms and conditions of this
    license.
    
    THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
    WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
    TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
    IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

  File Description:
    
    Change History:
     Rev   Date         Description
     1.0   11/19/2004   Initial release
     2.1   02/26/2007   Updated for simplicity and to use common
                        coding style

  Summary:
    This file contains all of functions, macros, definitions, variables,
    datatypes, etc. that are required for usage with the HID function
    driver. This file should be included in projects that use the HID
    \function driver.
    
    
    
    This file is located in the "\<Install Directory\>\\Microchip\\USB\\HID
    Device Driver" directory.
  Description:
    USB HID Function Driver File
    
    This file contains all of functions, macros, definitions, variables,
    datatypes, etc. that are required for usage with the HID function
    driver. This file should be included in projects that use the HID
    \function driver.
    
    This file is located in the "\<Install Directory\>\\Microchip\\USB\\HID
    Device Driver" directory.
    
    When including this file in a new project, this file can either be
    referenced from the directory in which it was installed or copied
    directly into the user application folder. If the first method is
    chosen to keep the file located in the folder in which it is installed
    then include paths need to be added so that the library and the
    application both know where to reference each others files. If the
    application folder is located in the same folder as the Microchip
    folder (like the current demo folders), then the following include
    paths need to be added to the application's project:
    
    ..\\Include
    
    ..\\..\\Include
    
    ..\\..\\Microchip\\Include
    
    ..\\..\\\<Application Folder\>
    
    ..\\..\\..\\\<Application Folder\>
    
    If a different directory structure is used, modify the paths as
    required. An example using absolute paths instead of relative paths
    would be the following:
    
    C:\\Microchip Solutions\\Microchip\\Include
    
    C:\\Microchip Solutions\\My Demo Application 


 Change History:
   Rev    Description
   ----   ------------------------------------------
   1.0    Initial release
   2.1    Updated for simplicity and to use common
          coding style
   2.6    Minor changes in defintions

*******************************************************************/

#ifndef USB_FUNCTION_HID_C
#define USB_FUNCTION_HID_C

/** INCLUDES *******************************************************/
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb.h"
#include "usb_function_hid.h"


/** VARIABLES ******************************************************/
#if defined(COMPILER_MPLAB_C18)
	#pragma udata
#endif

BYTE idle_rate;
BYTE active_protocol;   // [0] Boot Protocol [1] Report Protocol

/** EXTERNAL PROTOTYPES ********************************************/
#if defined USER_GET_REPORT_HANDLER
    void USER_GET_REPORT_HANDLER(void);
#endif

#if defined USER_SET_REPORT_HANDLER
    void USER_SET_REPORT_HANDLER(void);
#endif     

/** Section: DECLARATIONS ***************************************************/
#if defined(__18CXX)
    #pragma code
#endif

/** Section: CLASS SPECIFIC REQUESTS ****************************************/

/********************************************************************
	Function:
		void USBCheckHIDRequest(void)

 	Summary:
 		This routine handles HID specific request that happen on EP0.
        This function should be called from the USBCBCheckOtherReq() call back
        function whenever implementing a HID device.

 	Description:
 		This routine handles HID specific request that happen on EP0.  These
        include, but are not limited to, requests for the HID report
        descriptors.  This function should be called from the
        USBCBCheckOtherReq() call back function whenever using an HID device.

        Typical Usage:
        <code>
        void USBCBCheckOtherReq(void)
        {
            //Since the stack didn't handle the request I need to check
            //  my class drivers to see if it is for them
            USBCheckHIDRequest();
        }
        </code>

	PreCondition:
		None

	Parameters:
		None

	Return Values:
		None

	Remarks:
		None
 
 *******************************************************************/
void USBCheckHIDRequest(void)
{
    if(SetupPkt.Recipient != USB_SETUP_RECIPIENT_INTERFACE_BITFIELD) return;
    if(SetupPkt.bIntfID != HID_INTF_ID) return;
    
    /*
     * There are two standard requests that hid.c may support.
     * 1. GET_DSC(DSC_HID,DSC_RPT,DSC_PHY);
     * 2. SET_DSC(DSC_HID,DSC_RPT,DSC_PHY);
     */
    if(SetupPkt.bRequest == USB_REQUEST_GET_DESCRIPTOR)
    {
        switch(SetupPkt.bDescriptorType)
        {
            case DSC_HID: //HID Descriptor          
                if(USBActiveConfiguration == 1)
                {
                    USBEP0SendROMPtr(
                        (ROM BYTE*)&configDescriptor1 + 18,		//18 is a magic number.  It is the offset from start of the configuration descriptor to the start of the HID descriptor.
                        sizeof(USB_HID_DSC)+3,
                        USB_EP0_INCLUDE_ZERO);
                }
                break;
            case DSC_RPT:  //Report Descriptor           
                //if(USBActiveConfiguration == 1)
                {
                    USBEP0SendROMPtr(
                        (ROM BYTE*)&hid_rpt01,
                        HID_RPT01_SIZE,     //See usbcfg.h
                        USB_EP0_INCLUDE_ZERO);
                }
                break;
            case DSC_PHY:  //Physical Descriptor
				//Note: The below placeholder code is commented out.  HID Physical Descriptors are optional and are not used
				//in many types of HID applications.  If an application does not have a physical descriptor,
				//then the device should return STALL in response to this request (stack will do this automatically
				//if no-one claims ownership of the control transfer).
				//If an application does implement a physical descriptor, then make sure to declare
				//hid_phy01 (rom structure containing the descriptor data), and hid_phy01 (the size of the descriptors in bytes),
				//and then uncomment the below code.
                //if(USBActiveConfiguration == 1)
                //{
                //    USBEP0SendROMPtr((ROM BYTE*)&hid_phy01, sizeof(hid_phy01), USB_EP0_INCLUDE_ZERO);
                //}
                break;
        }//end switch(SetupPkt.bDescriptorType)
    }//end if(SetupPkt.bRequest == GET_DSC)
    
    if(SetupPkt.RequestType != USB_SETUP_TYPE_CLASS_BITFIELD)
    {
        return;
    }

    switch(SetupPkt.bRequest)
    {
        case GET_REPORT:
            #if defined USER_GET_REPORT_HANDLER
                USER_GET_REPORT_HANDLER();
            #endif
            break;
        case SET_REPORT:
            #if defined USER_SET_REPORT_HANDLER
                USER_SET_REPORT_HANDLER();
            #endif       
            break;
        case GET_IDLE:
            USBEP0SendRAMPtr(
                (BYTE*)&idle_rate,
                1,
                USB_EP0_INCLUDE_ZERO);
            break;
        case SET_IDLE:
            USBEP0Transmit(USB_EP0_NO_DATA);
            idle_rate = SetupPkt.W_Value.byte.HB;
            break;
        case GET_PROTOCOL:
            USBEP0SendRAMPtr(
                (BYTE*)&active_protocol,
                1,
                USB_EP0_NO_OPTIONS);
            break;
        case SET_PROTOCOL:
            USBEP0Transmit(USB_EP0_NO_DATA);
            active_protocol = SetupPkt.W_Value.byte.LB;
            break;
    }//end switch(SetupPkt.bRequest)

}//end USBCheckHIDRequest

/********************************************************************
    Function:
        USB_HANDLE HIDTxPacket(BYTE ep, BYTE* data, WORD len)
        
    Summary:
        Sends the specified data out the specified endpoint

    Description:
        This function sends the specified data out the specified 
        endpoint and returns a handle to the transfer information.

        Typical Usage:
        <code>
        //make sure that the last transfer isn't busy by checking the handle
        if(!HIDTxHandleBusy(USBInHandle))
        {
            //Send the data contained in the ToSendDataBuffer[] array out on
            //  endpoint HID_EP
            USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&ToSendDataBuffer[0],sizeof(ToSendDataBuffer));
        }
        </code>
        
    PreCondition:
        None
        
    Parameters:
        BYTE ep    - the endpoint you want to send the data out of
        BYTE* data - pointer to the data that you wish to send
        WORD len   - the length of the data that you wish to send
        
    Return Values:
        USB_HANDLE - a handle for the transfer.  This information
        should be kept to track the status of the transfer
        
    Remarks:
        None
  
 *******************************************************************/
 // Implemented as a macro. See usb_function_hid.h

/********************************************************************
    Function:
        USB_HANDLE HIDRxPacket(BYTE ep, BYTE* data, WORD len)
        
    Summary:
        Receives the specified data out the specified endpoint
        
    Description:
        Receives the specified data out the specified endpoint.

        Typical Usage:
        <code>
        //Read 64-bytes from endpoint HID_EP, into the ReceivedDataBuffer array.
        //  Make sure to save the return handle so that we can check it later
        //  to determine when the transfer is complete.
        USBOutHandle = HIDRxPacket(HID_EP,(BYTE*)&ReceivedDataBuffer,64);
        </code>

    PreCondition:
        None
        
    Parameters:
        BYTE ep    - the endpoint you want to receive the data into
        BYTE* data - pointer to where the data will go when it arrives
        WORD len   - the length of the data that you wish to receive
        
    Return Values:
        USB_HANDLE - a handle for the transfer.  This information
        should be kept to track the status of the transfer
        
    Remarks:
        None
  
 *******************************************************************/
  // Implemented as a macro. See usb_function_hid.h
  
/** USER API *******************************************************/

#endif
/** EOF usb_function_hid.c ******************************************************/
