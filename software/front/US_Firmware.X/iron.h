/* 
 * File:   iron.h
 * Author: Sparky
 *
 * Created on ??????????, 2013, ??? 3, 13:34
 */

#ifndef IRON_H
#define	IRON_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <GenericTypeDefs.h>
#include "typedefs.h"

typedef struct __PACKED{
    union __PACKED{
        unsigned int Input:3;
        struct __PACKED{
            unsigned int InputP:1;
            unsigned int InputN:1;
            unsigned int InputInv:1;
        };
    };
    unsigned int CBandA:1;
    unsigned int CurrentA:9;
    unsigned int CBandB:1;
    unsigned int CurrentB:9;
    unsigned int Gain:9;
    unsigned int Offset:10;
}t_MeasurementConfig;    

typedef struct __PACKED{
    UINT8 Type;             //sensor type (1: TC, 2: PTC)
    struct __PACKED{
        unsigned int HChannel :1; //Heater Channel
        union __PACKED{
            unsigned int InputConfig:3;
            struct __PACKED{
                unsigned int InputP :1;    //positive input sensor channel selection (0=GND; 1=sensor channel B)
                unsigned int InputN :1;    //negative input sensor channel selection (0=GND; 1=sensor channel A)
                unsigned int InputInv :1;  //input amplifier invert (0=not inverted (ChP on +, ChN on -), 1=inverted(ChN on +, ChP on -)
            };
        };
        unsigned int CBandA :1; //sensor channel A current source band (0=x16, 1=x1)
        unsigned int CBandB :1; //sensor channel B current source band (0=x16, 1=x1)
        unsigned int stub : 2;
    };
    UINT16  CurrentA;       //current for A sensor channel (0-256) current = CurrentA * (1.225/(1.6*256))mA
    UINT16  CurrentB;       //current for B sensor channel
    INT16   HRCompCurrent;  //heater resistance compensating current (0, currentA, currentB or currentA+currentB)
    UINT16  Gain;           //Amplifier gain for sensor, Gain = x*4, x=8-256
    UINT16  Offset;         //offset to exclude from measurement (0-1024)
    float   TPoly[10];      //Temperature polynomial coefficients
    INT8    WSLen;          //Waveshaping, 0=off, 1-8 = sample waveshaping with length 1-8, -1 = damping waveshaping
    UINT8   PID_DGain;      //PID differential gain (0 - 32)
    UINT16  PID_KP;         //PID proportional coefficient (0.1 - 0.999) * 32768
    UINT16  PID_KI;         //PID integral coefficient (0.1 - 0.999) * 32768
    UINT16  PID_OVSGain;    //Positive overshoot prevention gain (0 - 32)
    UINT16  PID_PMax;       //maximum rated power (watts)
    UINT16  PID_PNom;       //nominal power for which PID coefficients are calculated
} t_IronConfig;

typedef struct __PACKED {
    UINT16 Version;
    UINT16_VAL ID;
    char Name[24];
    t_IronConfig Config[2];
} t_IronPars;

#ifndef _IRON_C
#define IRON_H_EXTERN extern
#else
#define IRON_H_EXTERN
#endif

IRON_H_EXTERN UINT16 IronID;
IRON_H_EXTERN volatile t_IronPars IronPars;
IRON_H_EXTERN void IronInit();
IRON_H_EXTERN void IronTasks();

#undef IRON_H_EXTERN

#ifdef	__cplusplus
}
#endif

#endif	/* IRON_H */

