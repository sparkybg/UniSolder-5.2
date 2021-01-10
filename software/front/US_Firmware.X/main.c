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

#include "main.h"

#include "isr.h"
#include "iron.h"
#include "PID.h"
#include "menu.h"
#include "io.h"
#include "EEP.h"
#include "OLED.h"
#include "pars.h"

volatile T_BOARD_VERSION BoardVersion;

volatile unsigned int   BeepTicks;
volatile unsigned int   InvertTicks;

volatile unsigned int   POWER_DUTY;                 //max duty for compensation of heater off time
volatile unsigned int   MAINS_PER;                  //mains voltage period
volatile unsigned int   MAINS_PER_US;               //mains voltage period in microseconds
volatile unsigned int   MAINS_PER_H_US;             //mains voltage period for half power
volatile unsigned int   MAINS_PER_Q_US;             //mains voltage period for 1/4 power
volatile unsigned int   MAINS_PER_E_US;             //mains voltage period for 1/8 power

volatile unsigned int   T_PER;                      //ISR Timer period for mains frequency/1.2
volatile unsigned int   C_PER;                      //Character display period

volatile mainflags_t mainFlags = {1, 1, 1, 0};

volatile int CalCh;

/****** PARAMETERS SAVED IN EEPROM WHEN POWER IS LOST**************************/
volatile unsigned int   TTemp;                      //target temperature/2
volatile pars_t         pars;
/******************************************************************************/

volatile int Enc; //Rotary encoder position

int main(void){
    int i;
    mcuInit1();
    SPKOFF;

    OLEDInit();        
    OLEDPrintNum816(0, 0, 2, 0);
    OLEDUpdate();

    mcuInit2();
        
    CalCh = 0;
    mainFlags.ACPower = 0;
    MAINS_PER = 0;
    
    mcuDCTimerReset();
    while(MAINS && !mcuDCTimerInterrupt);

    if(!mcuDCTimerInterrupt){
        _delay_us(100);
        while(!MAINS && !mcuDCTimerInterrupt);

        mcuDCTimerReset();
        for(i = 0; (i < 8) && !mcuDCTimerInterrupt; i++){
            _delay_us(100);
            while(MAINS && !mcuDCTimerInterrupt){};
            _delay_us(100);
            while(!MAINS && !mcuDCTimerInterrupt){};
            MAINS_PER = mcuReadDCTimer();
        }
    }
    
    if(mcuDCTimerInterrupt){ //DC Power
        MAINS_PER_US = 9091; //110Hz
        POWER_DUTY = (1060*(9091-810))/9091; //max duty for power-off time (810us on DC)
        MAINS_PER_H_US = (MAINS_PER_US - 810) >> 1;
        MAINS_PER_Q_US = (MAINS_PER_US - 810) >> 2;
        MAINS_PER_E_US = (MAINS_PER_US - 810) >> 3;
        MAINS_PER = (PER_FREQ / 256) / 110;        //55Hz
        T_PER = MAINS_PER;
    }
    else{ //AC Power
        MAINS_PER_US = MAINS_PER * 256 /(PER_FREQ * 8 / 1000000);
        POWER_DUTY = (1060*(MAINS_PER_US-510))/MAINS_PER_US; //max duty for power-off time (510us on AC)
        MAINS_PER_H_US = MAINS_PER_US >> 1;
        MAINS_PER_Q_US = (MAINS_PER_US * 368)/1001;
        MAINS_PER_E_US = (MAINS_PER_US * 271)/964;
        MAINS_PER >>= 3;
        T_PER = MAINS_PER + ((PER_FREQ / 256) / 1000);
        mainFlags.ACPower = 1;
    }
    MAINS_PER_E_US = MAINS_PER_H_US - MAINS_PER_E_US;
    MAINS_PER_Q_US = MAINS_PER_H_US - MAINS_PER_Q_US;
    MAINS_PER_E_US -= MAINS_PER_Q_US;

    //Init timer1 with T_PER
    mcuInit3();

    IronInit();
    OLEDPrintNum816(0, 0, 2, 31);
    OLEDUpdate();
    ISRInit();
    OLEDPrintNum816(0, 0, 2, 32);
    OLEDUpdate();
    PIDInit();
    OLEDPrintNum816(0, 0, 2, 33);
    OLEDUpdate();
    IOInit();
    OLEDPrintNum816(0, 0, 2, 34);
    OLEDUpdate();
    MenuInit();
    OLEDPrintNum816(0, 0, 2, 35);
    OLEDUpdate();

    if(mainFlags.ACPower){
        while(MAINS);
        while(!MAINS);
    }
    OLEDPrintNum816(0, 0, 2, 36);
    OLEDUpdate();
    
    mcuDCTimerReset();
    
    mcuInit4();

    CBANDA=1;
    CBANDB=1;
    CHSEL1=0;
    CHSEL2=1;
    CHPOL=0;
    I2CData.CurrentA.ui16=128;
    I2CData.CurrentB.ui16=128;
    I2CData.Gain.ui16=128;
    I2CData.Offset.ui16=128;
    I2CAddCommands(I2C_SET_CPOT | I2C_SET_GAINPOT | I2C_SET_OFFSET);
    OLEDPrintNum816(0, 0, 2, 45);
    OLEDUpdate();

    LoadPars();
    OLEDPrintNum816(0, 0, 2, 46);
    OLEDUpdate();

    ISRStop();
    OLEDPrintNum816(0, 0, 2, 47);    
    OLEDUpdate();

    mainFlags.PowerLost = 0;
    
    ISRStart();
    OLEDPrintNum816(0, 0, 2, 48);
    OLEDUpdate();
    
    BeepTicks = 2;

    while(1){
        if(mainFlags.PowerLost){
            SavePars();
            MenuTasks();
            _delay_ms(1000);
            mcuReset();
            while(1);
        }
        MenuTasks();
        IOTasks();
        IronTasks();
        PIDTasks();
    }
}

#undef _MAIN_C
