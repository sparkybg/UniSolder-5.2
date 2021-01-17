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

#ifndef _IO_C
#define IOC_EXTERN extern
#else
#define IOC_EXTERN
#endif

typedef enum {
    DEV_GET_INFO                = 0x60,
    DEV_GET_OPERATING_MODE      = 0x61,
    DEV_RESET                   = 0x62,

    BL_GET_INFO                 = 0xE0,
    BL_ERASE_FLASH              = 0xE1,
    BL_PROGRAM_FLASH            = 0xE2,
    BL_READ_CRC                 = 0xE3,
    BL_JUMP_TO_APP              = 0xE4,
    BL_PROGRAM_COMPLETE         = 0xE5
}T_COMMANDS;

typedef union {
    UINT8 RawData[68];
    struct {
        UINT8 Command;  // T_COMMANDS
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

/*Buffers used for USB communication*/
IOC_EXTERN USBPacket RXP;
IOC_EXTERN USBPacket TXP;

IOC_EXTERN void IOInit();
IOC_EXTERN void IOTasks();

#undef IOC_EXTERN

#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */

