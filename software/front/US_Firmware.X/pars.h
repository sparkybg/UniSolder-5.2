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
        UINT8 Buttons;                              //Buttons swap (0 - +/-, 1 - -/+)
        UINT8 WakeUp;                               //Wake up from standby (0-off, 1-long key press, 2-holder sensor, 3-key or sensor)
        UINT8 DispRot;                              //Display rotation (0 - 0deg, 1 - 180deg)
        UINT8 NapFilterTicks;                       //Holder/stand sensor filter ticks
        UINT8 MenuScroll;                           //Menu scroll direction (0 - +=down, 1 - +=up)
        UINT8 DispCol;                              //Display staring coluimn (0 - 15))
        UINT8 Cal;
    };
    UINT8 b[17];
}pars_t;

typedef struct {
    const char * Name;
    UINT8 Default;
    UINT8 Min;
    UINT8 Max;
    UINT8 Immediate;
    const char ** Strings;
    void (*OLEDDispFunc)(int, int, int, int);
}t_ParDef;

#ifndef _PARS_C
extern const t_ParDef ParDef[17];
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* PARS_H */

