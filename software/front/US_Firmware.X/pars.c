#define _PARS_C

#include "main.h"
#include "OLED.h"
#include "pars.h"

void ParDispNum(int col, int row, int num);
void ParDispNumOff(int col, int row, int num);
void ParDispOnOffAuto(int col, int row, int temp);
void ParDispTemp(int col, int row, int temp);
void ParDispCF(int col, int row, int num);
void Temp(int T, int C_F);

const t_ParDef ParDef[11] = {
    {"        T1 ", {78  , 160,   0}, 125, 75, 225, &ParDispTemp},
    {"        T2 ", {78  ,  62,   0}, 150, 75, 225, &ParDispTemp},
    {"        T3 ", {78  , 186,   0}, 175, 75, 225, &ParDispTemp},
    {" HOL. TEMP ", {230 ,  78,   0}, 150, 75, 225, &ParDispTemp},
    {"SLEEP TEMP ", {218 ,  78,   0}, 125, 75, 225, &ParDispTemp},
    {"SLEEP TIME ", {218 ,  78, 128},  20,  0, 255, &ParDispNumOff},
    {"  STAND-BY ", {218 , 206,  78},  30,  0, 255, &ParDispNumOff},
    {"    HOLDER ", {230 , 252,  76},   2,  0,   2, &ParDispOnOffAuto},
    {"   DEGREES ", {230 , 252,  76},   0,  0,   1, &ParDispCF},
    {"BRIGHTNESS ", {206 ,   6, 128},  15,  1,  15, &ParDispNum},
    {"CALIBRATION", { 92 , 246,  76},  15,  1,  15, 0}
};

void ParDispCF(int col, int row, int num){
    OLEDWrite(col,4,row,degrees4x16,8);
    OLEDPrint816(col+4,row,num?"F":"C",0);
}

void ParDispNum(int col, int row, int num){
    OLEDPrintNum816(col,row,3,num);
}

void ParDispNumOff(int col, int row, int num){
    if(num){
        ParDispNum(col,row,num);
    }
    else{
        OLEDPrint816(col,row,"OFF",0);
    }
}

void ParDispOnOffAuto(int col, int row, int num){
    const char* s;
    switch(num){
        case 0:
            s="OFF";
            break;
        case 1:
            s="ON";
            break;
        default:
            s="AUTO";
            break;
    }
    OLEDPrint816(col,row,s,0);
}

void ParDispTemp(int col, int row, int temp){
    if(pars.Deg){
        ParDispNum(col, row, ((temp * 461) >> 7) + 32);
    }
    else{
        ParDispNum(col, row, temp * 2);
    }
    ParDispCF(col + 24, row, pars.Deg);
}
#undef _PARS_C

