#define _MENU_C

#include <GenericTypeDefs.h>
#include <stdlib.h>
#include "typedefs.h"
#include "mcu.h"
#include "pars.h"
#include "main.h"
#include "isr.h"
#include "pid.h"
#include "OLED.h"
#include "pars.h"
#include "iron.h"
#include "EEP.h"
#include "usb/usb.h"
#include "usb/usb_driver.h"
#include "usb/usb_function_hid.h"

#define intshr(a,b) ((a < 0) ? (-((-a) >> b)) : (a >> b))

static int TempBeep;
static int LISRTicks;
static int CTicks;
static int CSeconds=0;
static int CMSeconds=0;
static int CMinutes=0;
static int CMode;
static int OldMode;
static int CRstTemp;
static int CPar;
static int CRow;
static int CParVal;
static int ModeTicks;
static int DoExit;
static int DispTemp;
static int CalRes;
static UINT8 OldNAP;
static int NapTicks;
static UINT8 FNAP;

static union {
    UINT32 DW;
    struct { __PACKED
        int Header :1;
        int Footer :1;
        int BigTemp :1;
        int Message :1;
        int Set:1;
        int Pars:1;
        int SetPars:1;
        int StandBy:1;
        int Cal:1;
    }f;
}OLEDFlags;

int OLEDTemp;
int OLEDPower;
const char * OLEDMsg1;
const char * OLEDMsg2;


//static SUINT16 LDispTime;
static struct{
    int o;
    int n;
    int d;
}BTicks[3];

void MenuInit(){
    int i,p;
    CRstTemp = 1;
    CPar = 0;
    CRow = 0;
    CTicks = 0;
    BeepTicks = 0;
    InvertTicks = 0;
    for(i=0;i<3;i++){
        BTicks[i].o = 0;
        BTicks[i].n = 0;
        BTicks[i].d = 0;
    }
    CTTemp = TTemp;
    mainFlags.HolderPresent=0;
    TempBeep = 1;
    DispTemp = 0;
    CMode = 1;
    ModeTicks = 20;
    FNAP = 1;
    OldNAP = 1;
    NapTicks = pars.NapFilterTicks + 1;
    CalCh = 0;
}

void OLEDTasks(){
    OLEDFlags.DW=0;
    if(mainFlags.PowerLost){
        OLEDFlags.f.Message = 1;
        OLEDMsg1 = "     POWER LOST";
        OLEDMsg2 = "";
    }
    else{
        t_PIDVars * PV1 = (t_PIDVars *)&PIDVars[0];
        t_PIDVars * PV2 = PV1;IronPars.Config[1].Type? (t_PIDVars *)&PIDVars[1]: PV1;
        do{
            DoExit=1;
            switch(CMode){
                case 0: //default mode - display temperature and do nothing
                    if(CTTemp < MINTEMP){                        
                        CMode = 0xFF;
                        OldNAP = FNAP;
                        ModeTicks = 255;
                        DoExit = 0;
                        break;
                    }
                    if(BTicks[0].n | BTicks[2].n)CMode=1;
                    if(BTicks[1].o && (BTicks[1].o<100) && (BTicks[1].n==0))CMode=2;
                    if(CMode != 0){
                        DoExit = 0;
                        break;
                    }
                    if((BTicks[1].o <= 100) && (BTicks[1].n > 100)){ //goto set parameters menu
                        CMode=3;
                        ModeTicks=250;
                        BeepTicks=2;
                    }
                    OLEDFlags.f.Header = 1;
                    OLEDFlags.f.Footer = 1;
                    

                    if(IronPars.Config[0].Type == 255){
                    }
                    else if(PV1->ShortCircuit || PV2->ShortCircuit){
                        OLEDFlags.f.Message=1;
                        OLEDMsg1="       HEATER";
                        OLEDMsg2="    SHORTCIRCUIT";
                    }
                    else if(PV1->NoSensor || PV2->NoSensor){
                        OLEDFlags.f.Message = 1;
                        OLEDMsg1="       SENSOR";
                        OLEDMsg2="        OPEN";
                    }
                    else if(PV1->NoHeater || PV2->NoHeater){
                        OLEDFlags.f.Message=1;
                        OLEDMsg1="       HEATER";
                        OLEDMsg2="        OPEN";
                    }
                    else{
                        OLEDFlags.f.BigTemp = 1;
                        if((LISRTicks & 15) == 1){
                            OLEDTemp = DispTemp >> 3;
                        }
                    }                    
                    break;
                case 1: //set temperature mode
                    if(BTicks[1].n > 100)CMode = 0;
                    if(BTicks[1].o && (BTicks[1].n == 0))CMode = 2; //goto reset temperature mode
                    if(CMode != 1){
                        DoExit = 0;
                        break;
                    }
                    if(BTicks[0].n | BTicks[2].n){ //Temp inc/dec
                        ModeTicks = 100;
                        int i = TTemp;
                        if(BTicks[0].d)TTemp += (BTicks[0].n>>6) + 1;
                        if(BTicks[2].d)TTemp -= (BTicks[2].n>>6) + 1;
                        if(TTemp < MINTEMP)TTemp = MINTEMP;
                        if(TTemp > MAXTEMP)TTemp = MAXTEMP;
                        if(i != TTemp)TempBeep = 1;
                    }
                    OLEDFlags.f.Header = 1;
                    OLEDFlags.f.Footer = 1;
                    OLEDFlags.f.BigTemp = 1;
                    OLEDFlags.f.Set = 1;
                    OLEDTemp = TTemp << 2;
                    break;
                case 2: //reset temperature mode
                    if(BTicks[1].n > 100)CMode = 0;
                    if(BTicks[0].n | BTicks[2].n)CMode = 1;
                    if(CMode != 2){
                        DoExit = 0;
                        break;
                    }
                    if(BTicks[1].o && (BTicks[1].n == 0)){
                        int i;
                        ModeTicks = 75;
                        if(OldMode == CMode){
                            CRstTemp++;
                            if(CRstTemp > 2)CRstTemp = 0;
                        }
                        for(i = 0; i < 3; i++){
                            if(pars.RTemp[CRstTemp]){
                                if(TTemp != pars.RTemp[CRstTemp]){
                                    TTemp = pars.RTemp[CRstTemp];
                                    TempBeep = 1;
                                }
                                break;
                            }
                            CRstTemp++;
                            if(CRstTemp > 2)CRstTemp=0;
                        }
                        if(TTemp < MINTEMP)TTemp = MINTEMP;
                        if(TTemp > MAXTEMP)TTemp = MAXTEMP;
                    }
                    OLEDFlags.f.Header = 1;
                    OLEDFlags.f.Footer = 1;
                    OLEDFlags.f.BigTemp = 1;
                    OLEDFlags.f.Set = 1;
                    OLEDTemp = TTemp << 2;
                    break;
                case 3: //menu mode
                    if(BTicks[0].n | BTicks[1].n | BTicks[2].n){
                        if((BTicks[1].o <= 100) && (BTicks[1].n > 100)){
                            CMode = 0;
                            break;
                        }
                        ModeTicks = 250;
                        if(BTicks[(pars.MenuDown ? 2 : 0)].n == 1){CPar++; CRow++;}
                        if(BTicks[(pars.MenuDown ? 0 : 2)].n == 1){CPar--; CRow--;}
                        if(CRow < 0)CRow = 0;
                        if(CRow > 3)CRow = 3;
                        if(CPar < 0)CPar = (sizeof(ParDef) / sizeof(ParDef[0])) - 1;
                        if(CPar > ((sizeof(ParDef) / sizeof(ParDef[0])) - 1))CPar = 0;
                    }
                    if(BTicks[1].o &&(BTicks[1].o < 100) && (BTicks[1].n == 0)){
                        CMode = (CPar == ((sizeof(ParDef) / sizeof(ParDef[0])) - 1)) ? 5 : 4;
                        if(CMode == 4) CParVal = pars.b[CPar];
                    }
                    OLEDFlags.f.Pars = 1;
                    break;
                case 4: //menu set parameter mode
                    if(BTicks[0].n | BTicks[1].n | BTicks[2].n) ModeTicks = 250;
                    if(BTicks[1].o && (BTicks[1].n == 0)){
                        pars.b[CPar] = CParVal;
                        CMode = 3;
                    }
                    else {
                        if(BTicks[0].d)CParVal++;
                        if(BTicks[2].d)CParVal--;
                        if((CParVal < ParDef[CPar].Min))CParVal = ParDef[CPar].Max;
                        if((CParVal > ParDef[CPar].Max))CParVal = ParDef[CPar].Min;
                        if(ParDef[CPar].Immediate)pars.b[CPar] = CParVal;
                    }
                    OLEDFlags.f.Pars = 1;
                    break;
                case 5: //Calibration
                    ModeTicks = 250;
                    if(BTicks[1].o && !BTicks[1].n){
                        if((BTicks[1].o<100)){
                            mainFlags.Calibration = 0;
                            CMode = 0;
                            break;
                        }
                        else{
                            CalCh=CalCh?0:1;
                        }
                    }
                    else{
                        UINT16 Current = CalCh ? IronPars.Config[0].CurrentB : IronPars.Config[0].CurrentB;
                        if(BTicks[0].d && Current < 256) Current++;
                        if(BTicks[2].d && Current > 0) Current--;
                        if(CalCh){
                            IronPars.Config[0].CurrentB = Current;
                        }
                        else{
                            IronPars.Config[0].CurrentA = Current;                            
                        }
                    }
                    OLEDFlags.f.Cal = 1;
                    mainFlags.Calibration = 1;
                    break;
                case 0xFF: //stand-by
                    if(((pars.WakeUp & 1)!=0 && BTicks[1].o <= 50 && BTicks[1].n > 50) ||
                       (pars.WakeUp & 2 && mainFlags.HolderPresent && FNAP && OldNAP != FNAP)){ //exit from stand-by
                        CTTemp = TTemp;
                        CTicks = 0;
                        CSeconds = 0;
                        CMSeconds = 0;
                        CMinutes = 0;
                        CMode = 0;
                        BeepTicks = 2;
                    }
                    OldNAP = FNAP;
                    OLEDFlags.f.StandBy = 1;
                    break;
            }
        }while(!DoExit);
    }
    
    OLEDFill(0, 128,0 ,8 ,0);

    if(OLEDFlags.f.BigTemp){
        OLEDPrintNum3248(12, 1, pars.Deg ? ((OLEDTemp * 461) >> 9) + 32 : OLEDTemp >> 1);
        OLEDPrintCF1648(108, 1, pars.Deg ? 1 : 0);
    }

    if(OLEDFlags.f.Set){
        OLEDPrint68(3, 3, "S", 1);
        OLEDPrint68(3, 4, "E", 1);
        OLEDPrint68(3, 5, "T", 1);
    }
    
    if(OLEDFlags.f.Message){
        OLEDPrint68(0, 3, OLEDMsg1, 21);
        OLEDPrint68(0, 4, OLEDMsg2, 21);
    }

    if(OLEDFlags.f.Header){
        OLEDPrint68(0,0,(const char *)&IronPars.Name, 21);
    }
    if(OLEDFlags.f.Footer){
        UINT8 b;
        int i, p, 
            df = PIDVars[0].PIDDutyFull, 
            AVG = ADCAVG;

        OLEDPrint68(0, 7, mainFlags.ACPower ? "AC" : "DC", 2);
        OLEDPrint68(12, 7, PIDVars[0].Power ? (PIDVars[0].Power == 1 ? "H": "Q"): "F", 1);

        if(IronPars.Config[1].Type) AVG--;
        p = ((PIDVars[0].PIDDuty + 0x7FL) >> 8) * (PIDVars[0].HPAvg >> AVG);
        if(IronPars.Config[1].Type){
            df += PIDVars[1].PIDDutyFull;
            p += ((PIDVars[1].PIDDuty + 0x7FL) >> 8) * (PIDVars[1].HPAvg >> AVG);
        }
        else{
            df += df;
        }
        df >>= 19;
        p += 0x7FFFL;
        p >>= 16;
        for(i = 0; i <= 64; i++){
            b = 0;
            if(!(i & 1))b += 16;
            if(!(i & 15))b += 40;
            if(!(i & 31))b += 68;
            if(!(i & 63))b += 130;
            if(i && df){
                df--;
                b =~ b;
            }
            b &= 254;
            OLEDBUFF.B[7][i + 31] = b;
        }
        if((LISRTicks & 15) == 1)OLEDPower = p;
        OLEDPrintNum68(100, 7, 3, OLEDPower);
        OLEDPrint68(118, 7, "W", 1);
        if(HEATER)OLEDWrite(21, 8, 7, font8x8[4], 8);
    }
    
    if(OLEDFlags.f.Pars){
        int i, par = CPar - CRow;
        if(par < 0) par += sizeof(ParDef) / sizeof(ParDef[0]);
        for(i=0; i < 4; i++){
            OLEDPrint816(0, i * 2, ParDef[par].Name, 11);
            if(ParDef[par].OLEDDispFunc)(*ParDef[par].OLEDDispFunc)(par, 88, i * 2,  pars.b[par]);
            if(par == CPar){
                if(CMode == 3){
                    OLEDInvert(0, 128 - 44, i * 2, 2);
                }
                if(CMode == 4){
                    if(ParDef[par].OLEDDispFunc)(*ParDef[par].OLEDDispFunc)(par, 88, i * 2,  CParVal);
                    OLEDInvert(128 - 44, 44, i * 2, 2);
                }
            }
            par++;
            if(par >= sizeof(ParDef) / sizeof(ParDef[0])) par -= sizeof(ParDef) / sizeof(ParDef[0]);
        }        
    }
    
    if(OLEDFlags.f.StandBy){
        static int X, Y, DX, DY;
        if(X <= 0) DX = 1;
        if(Y <= 0) DY = 1;
        if(X >= ((128 - 18) * 2)) DX = -1;
        if(Y >= ((64 - 8) * 2)) DY =- 1;                                    
        X += DX;
        Y += DY;        
        OLEDPrintGr68(X >> 1, Y >> 1, "ZZZ", 3);
    }
    
    if(OLEDFlags.f.Cal){
        UINT32 dw = (INT32)(CalCh?IronPars.Config[0].CurrentA : IronPars.Config[0].CurrentB) * (INT32)IronPars.Config[0].Gain;
        if(dw){                    
            CalRes -= CalRes >> 3;                        
            CalRes += ((INT32)PIDVars[0].ADCTemp[0] * (INT32)33437L) / dw;
        }
        else{
            CalRes = 0;
        }
        
        OLEDPrint68(0,0,"CALIBRATION",0);
        OLEDPrint68(0,2,"IRON ID:",0);
        OLEDPrint68(0,3,"CURRENT:",0);
        OLEDPrint68(0,4,"ADC:",0);
        OLEDPrint68(0,5,"R:",0);
        OLEDPrint68(0,6,"ROOM:",0);
        OLEDPrint68(0,7,"PERIOD:",0);
        OLEDPrintNum68(64,2,2,IronID >> 8);
        OLEDPrintNum68(80,2,2,IronID & 255);
        if(IronPars.Config[1].Type==0 || (LISRTicks % 200) <100){
            OLEDPrintNum68(64,3,1,CalCh);
            OLEDPrintNum68(80,3,3,CalCh ? IronPars.Config[0].CurrentB : IronPars.Config[0].CurrentA);
            OLEDPrintNum68(32,4,4,PIDVars[0].ADCTemp[0]);
        }
        else{
            OLEDPrintNum68(64,3,1,1-CalCh);
            OLEDPrintNum68(80,3,3,CalCh ? IronPars.Config[1].CurrentA : IronPars.Config[1].CurrentB);
            OLEDPrintNum68(32,4,4,PIDVars[1].ADCTemp[0]);            
        }
        OLEDPrintNum68(16,5,4,CalRes >> 3);
        OLEDPrintNum68(40,6,3,CRTemp >> 1);
        OLEDPrintNum68(56,7,9,MAINS_PER_US);
    }
    if(InvertTicks) OLEDInvert(0, 128, 0, 8);
    
    OLEDUpdate();
}

void MenuTasks(){
    int i;
    if(mainFlags.PowerLost){ 
        OLEDTasks(); 
    }else{
        if(LISRTicks != ISRTicks){
            LISRTicks = ISRTicks;
            if((LISRTicks & 1) || mainFlags.PowerLost){
                for(i = 0; i < 3; i++){
                    BTicks[i].o = BTicks[i].n;
                    if(BTicks[i].n < 240)BTicks[i].n++;
                    BTicks[i].d = (BTicks[i].n == 1) || ((BTicks[i].n > 25) && ((LISRTicks & 3) == 1));
                }
                if(!(pars.Buttons?B3:B1)){BTicks[0].n = 0;BTicks[0].d = 0;}
                if(!B2){BTicks[1].n = 0;BTicks[1].d = 0;}
                if(!(pars.Buttons?B1:B3)){BTicks[2].n = 0;BTicks[2].d = 0;}

                DispTemp -= DispTemp >> 3;
                i = PIDVars[0].CTemp[0];
                if(IronPars.Config[1].Type) i = (i + PIDVars[1].CTemp[0]) >> 1;
                DispTemp += i;

                OldMode = CMode;
                
                OLEDTasks();

                if(BeepTicks){
                    BeepTicks--;
                    SPKON;
                }
                else
                {
                    SPKOFF;
                }
                
                if(InvertTicks)InvertTicks--;                
                
                if(ModeTicks){
                    ModeTicks--;
                }
                else{
                    CMode = 0;
                }
                
                if (!NAP){
                    NapTicks = 0;
                    FNAP = 0;
                }
                else{
                    if (NapTicks <= pars.NapFilterTicks){
                        NapTicks++;
                    }
                    else{
                        FNAP = 1;
                    }
                }

                if(CMode == 0xFF){
                    ModeTicks = 255;
                    CTTemp = 0;
                }
                else{
                    if((CTicks++) >= 50){
                        CTicks -= 50;
                        if(CSeconds < 255)CSeconds++;
                        if((CMSeconds++) >= 60){
                            CMSeconds -= 60;
                            if(CMinutes < 255)CMinutes++;
                        }
                    }
                    if(B1 || B2 || B3 || (((pars.Holder == 1) || ((pars.Holder == 2) && mainFlags.HolderPresent)) && FNAP)){
                        CTicks = 0;
                        CSeconds = 0;
                        CMSeconds = 0;
                        CMinutes = 0;
                    }

                    i = TTemp;
                    if(!FNAP){
                        mainFlags.HolderPresent = 1;
                        if(i > pars.HTemp) i = pars.HTemp;
                    }
                    if(pars.SlTime && (i > pars.SlTemp)){
                        if((pars.Holder == 1) || ((pars.Holder == 2) && mainFlags.HolderPresent)){
                            if(CSeconds >= pars.SlTime) i = pars.SlTemp;
                        }
                        else{
                            if(CMinutes >= pars.SlTime) i = pars.SlTemp;                            
                        }
                    }
                    if(pars.STBTime && (CMinutes >= pars.STBTime)) i = 0;
                    CTTemp = i;

                    if(TempBeep && (CTTemp == TTemp) && (CTTemp == (DispTemp >> 5))){
                        BeepTicks = 2;
                        TempBeep = 0;
                    }
                }
            }
        }
    }
}

#undef _MENU_C
