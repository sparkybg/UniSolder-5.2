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
#include <GenericTypeDefs.h>
#include "typedefs.h"

typedef union {
    UINT8 RawData[68];
    struct {
        UINT8 Command;
        UINT8 stub[3];
        union {
            UINT8 Data[64];
            UINT16 Data16[32];
            UINT32 Data32[16];
            struct {
                UINT32 DevID;
                UINT8 VerMin;
                UINT8 VerMaj;
            }DevInfo;
            struct {
                UINT32 Addr;
                UINT32 Len;
                UINT32 CRC;
            }ProgCRC;
            struct {
                UINT32 Key;
                UINT8 Data[60];
            }Secure;
        };
    };
}USBPacket;


#ifndef _IO_C
#define IOC_EXTERN extern
extern volatile USBPacket RXP;
extern volatile USBPacket TXP;

#else
#define IOC_EXTERN
#endif

IOC_EXTERN void IOInit();
IOC_EXTERN void IOTasks();


#undef IOC_EXTERN


#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */

