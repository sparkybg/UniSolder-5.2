/* 
 * File:   menu.h
 * Author: Sparky
 *
 * Created on ???????, 2013, ??? 2, 23:27
 */

#ifndef MENU_H
#define	MENU_H

#ifdef	__cplusplus
extern "C" {
#endif

/*State machine modes for menu*/
typedef enum{
    DEFAULT_MENU,         /*display temperature and do nothing*/
    SET_TEMPERATURE,      /*set temperature*/
    RESET_TEMPERATURE,    /*reset temperature*/
    MENU,                 /*in menu mode*/
    SET_PARAMS,           /*set parameters*/
    CALIBRATION,          /*calibration*/
    INSTRUMENT_INFO,      /*instrument info (debug)*/
    SET_INPUT_TYPE,       /*input selection*/
    TIP_CHANGE,           /*tip change*/
    VERSION_INFO,         /*version information*/
    STANDBY = 0xFF        /*standby*/
}T_MENU_MODE;

extern void MenuInit();
extern void MenuTasks();

#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

