#define _PARS_C

#include "main.h"
#include "OLED.h"
#include "pars.h"

void ParDispStr(int par, int col, int row, int num);
void ParDispNum(int par, int col, int row, int num);
void ParDispNumOff(int par, int col, int row, int num);
void ParDispTemp(int par, int col, int row, int temp);
void ParDispCF(int par, int col, int row, int num);

const char * StrDispRot[]   = {"0   ", "180 "};
const char * StrResume[]    = {"OFF ", "KEY ", "HOLD", "BOTH"};
const char * StrButtons[]   = {"+/- ", "-/+ "};
const char * StrOffOnAuto[] = {"OFF ", "ON  ", "AUTO"};
const char * StrMenuUp[]    = {"KEY+", "KEY-"};

const t_ParDef ParDef[] = {
//  NAME            DEF  MIN      MAX      IMMEDIATE SUFFIX STRINGS       DISPFUNC    

    {"        T1 ", 125, MINTEMP, MAXTEMP, 0,            0, 0,            &ParDispTemp},
    {"        T2 ", 150, MINTEMP, MAXTEMP, 0,            0, 0,            &ParDispTemp},
    {"        T3 ", 175, MINTEMP, MAXTEMP, 0,            0, 0,            &ParDispTemp},
    {"  HOLDER T ", 150, MINTEMP, MAXTEMP, 0,            0, 0,            &ParDispTemp},
    {"   SLEEP T ", 125, MINTEMP, MAXTEMP, 0,            0, 0,            &ParDispTemp},
    {"     SLEEP ",  20,       0,     255, 0,          "s", 0,            &ParDispNumOff},
    {"  STAND-BY ",  30,       0,     255, 0,          "m", 0,            &ParDispNumOff},
    {"    HOLDER ",   2,       0,       2, 0,            0, StrOffOnAuto, &ParDispStr},
    {"   DEGREES ",   0,       0,       1, 1,            0, 0,            &ParDispCF},
    {"BRIGHTNESS ",  15,       1,      15, 1,            0, 0,            &ParDispNum},
    {"   BUTTONS ",   0,       0,       1, 0,            0, StrButtons,   &ParDispStr},    
    {"   WAKE UP ",   0,       0,       3, 0,            0, StrResume,    &ParDispStr},    
    {"  ROTATION ",   0,       0,       1, 1,            0, StrDispRot,   &ParDispStr},
    {"SENSOR FLT ",   0,       0,     255, 0,            0, 0,            &ParDispNumOff},
    {" MENU DOWN ",   0,       0,       1, 0,            0, StrMenuUp,    &ParDispStr},
    {" CALIBRATE ",   0,       0,       0, 0,            0, 0,            0},
    {" INST.INFO ",   0,       0,       0, 0,            0, 0,            0},
};


void ParDispStr(int par, int col, int row, int num){
    OLEDPrint816(col, row, ParDef[par].Strings[num], 0);
}

void ParDispNum(int par, int col, int row, int num){
    OLEDPrintNum816(col, row, 3, num);
    if(ParDef[par].Suffix) OLEDPrint816(col + 24, row, ParDef[par].Suffix, 0);
}

void ParDispNumOff(int par, int col, int row, int num){
    if(num){
        ParDispNum(par, col, row, num);
    }
    else{
        OLEDPrint816(col, row, StrOffOnAuto[0], 0);
    }
}

void ParDispCF(int par, int col, int row, int num){
    OLEDWrite(col, 4, row, degrees4x16, 8);
    OLEDPrint816(col + 4, row, num ? "F" : "C", 0);
}

void ParDispTemp(int par, int col, int row, int temp){
    if(pars.Deg){
        ParDispNum(par, col, row, ((temp * 461) >> 7) + 32);
    }
    else{
        ParDispNum(par, col, row, temp * 2);
    }
    ParDispCF(par, col + 24, row, pars.Deg);
}
#undef _PARS_C

