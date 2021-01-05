/* 
 * File:   io.h
 * Author: Sparky
 *
 * Created on ?????, 2013, ??? 28, 23:18
 */

#ifndef IO_H
#define	IO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "iron.h"

#ifndef _IO_C
#define IOC_EXTERN extern
#else
#define IOC_EXTERN
#endif

typedef union {
    UINT8 RAWData[64];
    struct  __PACKED {
        UINT8 Command;
        union{
            UINT8 OpMode;
            UINT8 Data[63];
            UINT16 Data16[31];
            struct __PACKED {
                unsigned char PacketDataFieldSize;
                unsigned char BytesPerAddress;
            }QueryDev;
            struct __PACKED {
                UINT16 Gain;
                UINT16 Offset;
                UINT16 PID_KP;
                UINT16 PID_KI;
                UINT16 PID_DGain;
                UINT16 PID_OVSGain;
            }IronPars;
            struct __PACKED {
                UINT16 Ticks;
                UINT8 CTTemp;
                UINT16 CTemp;
                UINT16 ADCTemp;
                UINT16 TAvgF;
                INT16 CHRes;
                UINT16 TAvgP;
                UINT8 Heater;
                INT16 WSDelta[8] __PACKED;
                UINT8 DestinationReached;
                UINT16 Duty;
            }LiveData;
        };
    };
}USBPacket;




IOC_EXTERN volatile USBPacket RXP;
IOC_EXTERN volatile USBPacket TXP;

IOC_EXTERN void IOInit();
IOC_EXTERN void IOTasks();

IOC_EXTERN int BuffEmpty;


#undef IOC_EXTERN


#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */

