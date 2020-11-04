/* 
 * File:   main.h
 * Author: Sparky
 *
 * Created on ???????, 2013, ??? 21, 3:06
 */

#ifndef MAIN_H
#define	MAIN_H

#include "typedefs.h"
#include "pars.h"

#define MINTEMP 50
#define MAXTEMP 225

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct __PACKED{
        int HolderPresent:1;
        int PowerLost:1;
        int ACPower:1;
        int Calibration:1;
    }mainflags_t;

#ifndef _MAIN_C
    extern volatile unsigned int BeepTicks;
    extern volatile unsigned int InvertTicks;
    extern volatile unsigned int MAINS_PER;
    extern volatile unsigned int MAINS_PER_US;
    extern volatile unsigned int MAINS_PER_H_US;
    extern volatile unsigned int MAINS_PER_Q_US;
    extern volatile unsigned int T_PER;
    extern volatile unsigned int C_PER;
    
    extern volatile unsigned int TTemp;
    extern volatile mainflags_t mainFlags;
    extern volatile pars_t pars;
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

