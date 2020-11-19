#define _IO_C

#include <xc.h>
#include "typedefs.h"
#include "mcu.h"
#include "io.h"
#include "pars.h"
#include "main.h"
#include "PID.h"
#include "isr.h"
#include "iron.h"
#include "usb/usb.h"
#include "usb/usb_driver.h"
#include "usb/usb_function_hid.h"

#define TXP (*((USBPacket *)USBTxBuffer))
#define RXP (*((USBPacket *)USBRxBuffer))

//#define IO_IDLE 0
//#define IO_BUSY 1

static unsigned int IO_TICKS;
static unsigned int IO_BUSY;

static unsigned int BuffPos;

void ProcessIO();

void IOInit(){
    IO_TICKS = ISRTicks;
    IO_BUSY = 1;
    USBDriverInit();
    RXP.Command = 0;
}

void IOTasks(){
    USBDeviceTasks();
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
    ProcessIO();   // This is where all the actual bootloader related data transfer/self programming takes place
}

void ProcessIO(){
    static UINT16 _IronID=0; 
    UINT8 i;
    if(!IO_BUSY && !HIDTxHandleBusy(USBInHandle)){
        if(_IronID != IronID){
            _IronID = IronID;
            TXP.Command = 1;
            TXP.Data16[0] = IronID;
            USBInHandle = HIDTxPacket(HID_EP, (char *)&TXP, 64);
        }
        else if(IO_TICKS != ADCStep && !HIDTxHandleBusy(USBInHandle)){
            IO_TICKS = ADCStep;
            if(IO_TICKS & 1){
                BuffPos++;
                if(BuffPos>127){
                    BuffPos &= 127;
                }
                TXP.Command=3;
                TXP.LiveData.Ticks=IO_TICKS;
                TXP.LiveData.CTTemp=CTTemp;                                 //
                TXP.LiveData.CTemp=PIDVars[0].CTemp[0];                                //
                TXP.LiveData.ADCTemp=PIDVars[0].ADCTemp[0];                            //
                TXP.LiveData.TAvgF=PIDVars[0].TAvgF[0] >> ADCAVG;                        //
                TXP.LiveData.CHRes=PIDVars[0].HRAvg >> ADCAVG;// (PIDVars[0].Delta[0]>>4)+250;//HRAvg>>ADCAVG;
                TXP.LiveData.TAvgP=PIDVars[0].TAvgP[0];
                TXP.LiveData.Heater=PHEATER;
                TXP.LiveData.WSDelta[0] = PIDVars[0].WSDelta[0].val + 2048;                //
                TXP.LiveData.WSDelta[1] = PIDVars[0].WSDelta[1].val + 2048;   //
                TXP.LiveData.WSDelta[2] = PIDVars[0].WSDelta[2].val + 2048;   //
                TXP.LiveData.WSDelta[3] = PIDVars[0].WSDelta[3].val + 2048;   //
                TXP.LiveData.WSDelta[4] = PIDVars[0].WSDelta[4].val + 2048;   //
                TXP.LiveData.WSDelta[5] = PIDVars[0].WSDelta[5].val + 2048;   //
                TXP.LiveData.WSDelta[6] = PIDVars[0].WSDelta[6].val + 2048;   //
                TXP.LiveData.WSDelta[7] = PIDVars[0].WSDelta[7].val + 2048;   //
                TXP.LiveData.DestinationReached=PIDVars[0].DestinationReached;         //
                TXP.LiveData.Duty = (UINT16)(PIDVars[0].PIDDutyFull>>8);                       //
                USBInHandle = HIDTxPacket(HID_EP, (char *)&TXP, 64);
            }
        }        
    }
    else {
        if(!HIDRxHandleBusy(USBOutHandle)){
            IO_BUSY = 1;
            switch(RXP.Command){
                case 0x81: //jump to bootloader                    
                    mcuJumpToBootLoader();
                    break;
                case 0x61: //get operating mode
                    if(!HIDTxHandleBusy(USBInHandle)){
                        TXP.Command=0x61;
                        TXP.OpMode=1;
                        USBInHandle = HIDTxPacket(HID_EP, (char *)&TXP, 64);
                        IO_BUSY=0;
                    }
                    break;
                case 2: //Query device
                    BeepTicks=5;
                    if(!HIDTxHandleBusy(USBInHandle)){
                        TXP.Command=2;
                        TXP.QueryDev.PacketDataFieldSize = 64;
                        USBInHandle = HIDTxPacket(HID_EP, (char *)&TXP, 64);
                        BeepTicks=20;
                        InvertTicks=20;
                        IO_BUSY=0;
                    }
                    break;
                case 3: //Set current iron PID parameters
                    IronPars.Config[0].SensorConfig.Gain = RXP.IronPars.Gain;
                    IronPars.Config[0].PID_KP = RXP.IronPars.PID_KP;
                    IronPars.Config[0].PID_KI = RXP.IronPars.PID_KI;
                    IronPars.Config[0].PID_DGain = RXP.IronPars.PID_DGain;
                    IronPars.Config[0].PID_OVSGain = RXP.IronPars.PID_OVSGain;
                    IO_BUSY = 0;
                    break;
                case 4: //Get current iron PID parameters
                    if(!HIDTxHandleBusy(USBInHandle)){
                        BeepTicks=20;
                        TXP.Command=4;
                        TXP.IronPars.Gain = IronPars.Config[0].SensorConfig.Gain;
                        TXP.IronPars.Offset = IronPars.Config[0].SensorConfig.Offset;
                        TXP.IronPars.PID_KP = IronPars.Config[0].PID_KP;
                        TXP.IronPars.PID_KI = IronPars.Config[0].PID_KI;
                        TXP.IronPars.PID_DGain = IronPars.Config[0].PID_DGain;
                        TXP.IronPars.PID_OVSGain = IronPars.Config[0].PID_OVSGain;
                        USBInHandle = HIDTxPacket(HID_EP, (char *)&TXP, 64);
                        IO_BUSY = 0;
                    }
                    break;
                default:
                    IO_BUSY = 0;
                    break;
            }
            if(!IO_BUSY) USBOutHandle = HIDRxPacket(HID_EP, (char *)&RXP, 64);
        }
    }
}

#undef _IO_C
