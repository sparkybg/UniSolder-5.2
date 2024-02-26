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

#ifdef	__cplusplus
extern "C" {
#endif

#define MINTEMP 50
#define MAXTEMP 225

/*This will be visible in version menu*/
#define VERSION_MAJOR   1
#define VERSION_MINOR   1

typedef struct __PACKED{
    int HolderPresent:1;
    int PowerLost:1;
    int ACPower:1;
    int Calibration:1;
    int TipChange:1;
}mainflags_t;

/* Front PCB version 0=first version, 1=rev B/C with tip change support */
typedef enum{
    BOARD_HW_5_2 = 0,   /* first hw version */
    BOARD_HW_5_2C = 1   /* rev B/C with tip change support */
}T_BOARD_VERSION;

#ifndef _MAIN_C
    extern volatile T_BOARD_VERSION BoardVersion;
    extern volatile unsigned int BeepTicks;
    extern volatile unsigned int InvertTicks;
    extern volatile unsigned int POWER_DUTY;
    extern volatile unsigned int MAINS_PER;
    extern volatile unsigned int MAINS_PER_US;
    extern volatile unsigned int MAINS_PER_H_US;
    extern volatile unsigned int MAINS_PER_Q_US;
    extern volatile unsigned int MAINS_PER_E_US;
    extern volatile unsigned int T_PER;    
    extern volatile unsigned int TTemp;
    extern volatile mainflags_t mainFlags;
    extern volatile pars_t pars;
    
    extern volatile int Enc;
    
    extern volatile int CalCh;
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

