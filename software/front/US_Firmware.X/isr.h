/* 
 * File:   isr.h
 * Author: Sparky
 *
 * Created on ??????????, 2013, ??? 20, 2:17
 */

#ifndef ISR_H
#define	ISR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <GenericTypeDefs.h>
#include "typedefs.h"
#include "mcu.h"
    
#define CJ_PERIOD 500;  //Period in ticks of measurement of cold junction sensor temperature, if present.    


typedef struct {
    int HeaterOn;
    unsigned int VRT;
    unsigned int VCJ;
    unsigned int VID;
    unsigned int VTEMP[4];
    unsigned int VIN;
}ADCDataS;

typedef struct {
    SUINT16 CurrentA;
    SUINT16 CurrentB;
    SUINT16 Gain;
    SUINT16 Offset;
}I2CDataS;

#ifndef _ISR_C
#define ISRC_EXTERN extern
#else
#define ISRC_EXTERN
#endif

ISRC_EXTERN void IsrHigh(int src);

ISRC_EXTERN volatile int ISRStep;
ISRC_EXTERN volatile int ISRTicks;
ISRC_EXTERN volatile unsigned int CJTicks;

ISRC_EXTERN volatile int ISRStopped;

ISRC_EXTERN volatile ADCDataS ADCData;
ISRC_EXTERN volatile UINT32 VBuff[256];
ISRC_EXTERN volatile UINT32 TIBuff[256];
ISRC_EXTERN volatile unsigned int VTIBuffCnt;

ISRC_EXTERN UINT32 OffDelayOff;

ISRC_EXTERN volatile UINT32 CompLowTime;
ISRC_EXTERN volatile UINT32 CompLowTimeOn;
ISRC_EXTERN volatile UINT32 CompLowTimeOff;

ISRC_EXTERN volatile I2CDataS I2CData;

ISRC_EXTERN volatile UINT8 PHEATER;

ISRC_EXTERN volatile int ADCStep;

ISRC_EXTERN volatile int KeepOff;

ISRC_EXTERN volatile unsigned char NoHeater;
ISRC_EXTERN volatile unsigned char NoSensor;
ISRC_EXTERN volatile unsigned char ShortCircuit;

ISRC_EXTERN volatile UINT16 EEPAddrR;
ISRC_EXTERN volatile UINT16 EEPAddrW;
ISRC_EXTERN volatile void * EEPDataR;
ISRC_EXTERN volatile void * EEPDataW;
ISRC_EXTERN volatile UINT16 EEPCntR;
ISRC_EXTERN volatile UINT16 EEPCntW;

ISRC_EXTERN volatile int Buff1[128];
ISRC_EXTERN volatile int Buff2[128];

enum I2C_FLAGS{
    I2C_SET_CPOT=1,
    I2C_SET_GAINPOT=2,
    I2C_SET_OFFSET=4,
    I2C_EEPWRITE = 8,
    I2C_EEPREAD = 16
};

enum IntSrc{
    CompH2L=1,
    CompL2H=2,
    DCTimer=3
};


ISRC_EXTERN volatile int I2CStep;
ISRC_EXTERN volatile unsigned char I2CIdle;


#undef ISRC_EXTERN

//#define _I2CStart {I2CStep=0;PIR1bits.SSPIF=1;}
    
#ifdef	__cplusplus
}
#endif

#endif	/* ISR_H */

