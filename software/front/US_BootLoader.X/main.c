/* 
 * File:   main.c
 * Author: Sparky
 * Compiler: Microchip XC8 1.12
 *
 * Created on ??????, 2013, ?????? 5, 3:15
 */
#define _MAIN_C

#include "mcu.h"
#include "usb/usb.h"
#include "usb/usb_function_hid.h"
#include "io.h"
#include "OLED.h"

void displayTasts(void);

void main(void){
    int i;
    mcuInit();

    if(((B1 == 0) || (B3 == 0)) && (NVMDATA != 0x6193471A)){
        if(mcuValidAppPresent() == 1)mcuJumpToApp();
    }
    NVMDATA = 0xFFFFFFFF;

    SDI_OUT=0;
    SDO_OUT=0;
    SDISDO_OO;

    mcuSPIOpen();
    OLEDInit();
    
    IOInit();
    while(1){
        displayTasts();
        IOTasks();
    }
}

void displayTasts(void){
    volatile static int CT;
    volatile static int CTT;
    int i;
    CT++;
    if((CT & 4095) == 4095){
        CTT++;
        i=128;
        while(i--){
            OLEDBUFF.B[3][i]=((CTT+i) & 8)?0xFF:0;
            OLEDBUFF.B[4][i]=~OLEDBUFF.B[3][i];
        }
        OLEDUpdate();
    }
}

#undef _MAIN_C