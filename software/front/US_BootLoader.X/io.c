#define _IO_C

#include <xc.h>
#include "typedefs.h"
#include "mcu.h"
#include "io.h"
#include "crc.h"
#include "usb/usb.h"
#include "usb/usb_driver.h"
#include "usb/usb_function_hid.h"

#define IO_IDLE 0
#define IO_BUSY 1

static UINT8 IO_STATUS;

void ProcessIO();

void IOInit(){
    USBDriverInit();
    IO_STATUS=IO_IDLE;
    RXP.Command=0;
    USBOutHandle = HIDRxPacket(HID_EP, (BYTE *)&RXP, 64);
}

void IOTasks(){
    USBDeviceTasks();
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
    ProcessIO();   // This is where all the actual bootloader related data transfer/self programming takes place
}

void ProcessIO(){
    if(IO_STATUS == IO_IDLE){
        if(!HIDRxHandleBusy(USBOutHandle)){
            IO_STATUS = IO_BUSY;
        }
    }
    if(IO_STATUS == IO_BUSY){
        if(!HIDTxHandleBusy(USBInHandle)){
            UINT8 Secured;
            /*memory move necessary because the command is on 1 byte, could be avoided by using 4 bytes*/
            memmove((void*)(&RXP.RawData[4]), (void*)(&RXP.RawData[1]), 63);
            Secured = (RXP.Secure.Key == 0x43211234);
            TXP.Command = RXP.Command;
            TXP.Data[0] = 0xFF;
            switch(RXP.Command){
                case DEV_GET_INFO:
                    TXP.DevInfo.DevID = DEVICE_ID;
                    TXP.DevInfo.VerMin = DEVICE_MINOR_VERSION;
                    TXP.DevInfo.VerMaj = DEVICE_MAJOR_VERSION;
                    break;
                case DEV_GET_OPERATING_MODE:
                    TXP.Data[0] = 0x10;
                    break;
                case BL_GET_INFO:
                    TXP.Data[0] = BOOTLOADER_MINOR_VERSION;
                    TXP.Data[1] = BOOTLOADER_MAJOR_VERSION;
                    break;
                case BL_ERASE_FLASH:
                    if(Secured) TXP.Data[0] = mcuEraseFlash();
                    break;
                case BL_PROGRAM_FLASH:
                    if(Secured) TXP.Data[0] = mcuWriteFlashRecord((void*)RXP.Secure.Data);
                    break;
                case BL_PROGRAM_COMPLETE:
                    if(Secured) TXP.Data32[0] = mcuProgramComplete();
                    break;
                case BL_READ_CRC:
                    TXP.ProgCRC.CRC = CalculateCRC(0, (void *)RXP.ProgCRC.Addr, RXP.ProgCRC.Len);
                    break;
                case DEV_RESET:
                case BL_JUMP_TO_APP:
                    TXP.Command = 0;
                    mcuDisableInterrupts();
                    mcuDisableUSB();
                    if(RXP.Command == DEV_RESET){
                        mcuReset();
                    }
                    else{
                        mcuReset();
                        //mcuJumpToApp();
                    }
                    break;
                default:
                    TXP.Command = 0;
                    break;
            }
            RXP.Command = 0;
            if(TXP.Command != 0){
                memmove((void*)&TXP.RawData[1], (void*)&TXP.RawData[4], 63);
                USBInHandle = HIDTxPacket(HID_EP, (BYTE *)&TXP, 64);
            }
            IO_STATUS=IO_IDLE;
            USBOutHandle = HIDRxPacket(HID_EP, (BYTE *)&RXP, 64);
        }
    }
}

#undef _IO_C
