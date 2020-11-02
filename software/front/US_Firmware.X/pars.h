/* 
 * File:   pars.h
 * Author: Sparky
 *
 * Created on ??????????, 2014, ?????? 25, 20:49
 */

#ifndef PARS_H
#define	PARS_H

#include <GenericTypeDefs.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef union {
    struct __PACKED {
        UINT8 RTemp[3];                             //Reset temperatures
        UINT8 HTemp;                                //Holder temperature
        UINT8 SlTemp;                               //Sleep temperature
        UINT8 SlTime;                               //Sleep Time (0(off) - 240 seconds(holder with sensor)/minutes(holder without sensor))
        UINT8 STBTime;                              //StandBy Time (0(off) - 240 minutes)
        UINT8 Holder;                               //Holder sensor (0(off), 1(on), 2(auto)
        UINT8 Deg;                                  //Celsius/Farenheit (0-Celsous), 1-Farenheit))
        UINT8 Bri;                                  //display brightness (1-16)
        UINT8 Cal;
    };
    UINT8 b[11];
}pars_t;

typedef struct {
    const char * Name;
    const char ShortName[3];
    UINT8 Default;
    UINT8 Min;
    UINT8 Max;
    void (*OLEDDispFunc)(int,int,int);
}t_ParDef;

#ifndef _PARS_C
extern const t_ParDef ParDef[11];
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* PARS_H */

