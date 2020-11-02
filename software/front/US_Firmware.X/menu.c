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
static int TopPar;
static int CPar;
static int ModeTicks;
static int DoExit;
static int DispTemp;
static int CalRes;

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
    CRstTemp=1;
    CPar=0;
    TopPar=0;
    CTicks=0;
    BeepTicks=0;
    InvertTicks=0;
    for(i=0;i<3;i++){
        BTicks[i].o=0;
        BTicks[i].n=0;
        BTicks[i].d=0;
    }
    CTTemp=TTemp;
    mainFlags.HolderPresent=0;
    TempBeep=1;
    DispTemp=0;
    CMode=1;
    ModeTicks=20;
}

void OLEDTasks(){
    int i;
    //UINT8 b;
    t_PIDVars * PV1;
    t_PIDVars * PV2;
    PV1 = (t_PIDVars *)&PIDVars[0];
    PV2 = PV1;
    if(IronPars.Config[1].Type) PV2 = (t_PIDVars *)&PIDVars[1];
    OLEDFlags.DW=0;
    if(mainFlags.PowerLost){
        OLEDFlags.f.Message = 1;
        OLEDMsg1 = "     POWER LOST";
        OLEDMsg2 = "";
    }
    else{
        do{
            DoExit=1;
            switch(CMode){
                case 0: //default mode - display temperature and do nothing
                    if(CTTemp < 75){
                        CMode = 0xFF;
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
                    else if(PV1->NoHeater || PV2->NoHeater){
                        OLEDFlags.f.Message=1;
                        OLEDMsg1="       HEATER";
                        OLEDMsg2="        OPEN";
                    }
                    else if(PV1->NoSensor || PV2->NoSensor){
                        OLEDFlags.f.Message = 1;
                        OLEDMsg1="       SENSOR";
                        OLEDMsg2="        OPEN";
                    }
                    else{
                        OLEDFlags.f.BigTemp = 1;
                        if((LISRTicks & 15) == 1)OLEDTemp = DispTemp >> 3;
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
                        i = TTemp;
                        if(BTicks[0].d)TTemp += (BTicks[0].n>>6) + 1;
                        if(BTicks[2].d)TTemp -= (BTicks[2].n>>6) + 1;
                        if(TTemp < 75)TTemp = 75;
                        if(TTemp > 225)TTemp = 225;
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
                        if(TTemp < 75)TTemp = 75;
                        if(TTemp > 225)TTemp = 225;
                    }
                    OLEDFlags.f.Header = 1;
                    OLEDFlags.f.Footer = 1;
                    OLEDFlags.f.BigTemp = 1;
                    OLEDFlags.f.Set = 1;
                    OLEDTemp = TTemp << 2;
                    break;
                case 3:
                    if(BTicks[0].n | BTicks[1].n | BTicks[2].n){
                        if((BTicks[1].o <= 100) && (BTicks[1].n > 100)){
                            CMode = 0;
                            break;
                        }
                        ModeTicks = 250;
                        if(BTicks[0].n == 1)CPar++;
                        if(BTicks[2].n == 1)CPar--;
                        if(CPar < 0)CPar = 0;
                        if(CPar > ((sizeof(ParDef) / sizeof(ParDef[0])) - 1))CPar = (sizeof(ParDef) / sizeof(ParDef[0])) - 1;
                        if(TopPar > CPar)TopPar = CPar;
                        if((CPar - TopPar) > 3)TopPar = CPar - 3;
                    }
                    if(BTicks[1].o &&(BTicks[1].o < 100) && (BTicks[1].n == 0)){
                        CMode = (CPar == ((sizeof(ParDef) / sizeof(ParDef[0])) - 1)) ? 5 : 4;
                        //CMode=4;
                    }
                    OLEDFlags.f.Pars = 1;
                    //DisplayData(parText[CPar]);
                    break;
                case 4:
                    if(BTicks[0].n | BTicks[1].n | BTicks[2].n) ModeTicks = 250;
                    if(BTicks[1].o && (BTicks[1].n == 0))CMode = 3;
                    OLEDFlags.f.Pars = 1;
                    if(BTicks[0].d && (pars.b[CPar] < ParDef[CPar].Max))pars.b[CPar] += 1;
                    if(BTicks[2].d && (pars.b[CPar] > ParDef[CPar].Min))pars.b[CPar] -= 1;
                    break;
                case 5: //Calibration
                    ModeTicks = 250;
                    if(BTicks[1].o &&(BTicks[1].o<100) && (BTicks[1].n == 0)){
                        mainFlags.Calibration = 0;
                        CMode = 0;
                        break;
                    }
                    mainFlags.Calibration = 1;
                    OLEDFlags.f.Cal = 1;
                    if(BTicks[0].d && (IronPars.Config[0].CurrentA < 256)) IronPars.Config[0].CurrentA++;
                    if(BTicks[2].d && (IronPars.Config[0].CurrentA > 0)) IronPars.Config[0].CurrentA--;
                    break;
                case 0xFF: //stand-by
                    //OLEDFlags.f.Header = 1;
                    //OLEDFlags.f.Footer = 1;
                    //OLEDFlags.f.BigTemp = 1;
                    //if((LISRTicks & 15) == 1)OLEDTemp = DispTemp >> 3;
                    
                    OLEDFlags.f.Message=1;
                    OLEDMsg1="       ZZZ.. .  .";
                    OLEDMsg2="";
                    break;
            }
        }while(!DoExit);
    }
    
    OLEDFill(0, 128,0 ,8 ,0);

    if(OLEDFlags.f.BigTemp){
        OLEDPrintNum3248(12, 1, pars.Deg ? ((OLEDTemp * 461) >> 9) + 32 : OLEDTemp >> 1);
        OLEDPrintCF1648(108, 1, pars.Deg ? 1 : 0);
        //OLEDPrint68(104, 6, "/", 1);
        //OLEDPrintNum68(110, 6, 3, CTTemp);
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
        //OLEDPrintNum68(0,0,8,PIDVars[0].CPolyX * 10.0);
        //OLEDPrintNum68(64,0,8,PIDVars[0].PrbFCTemp1);
        OLEDPrint68(0,0,(const char *)&IronPars.Name, 21);
    }
    if(OLEDFlags.f.Footer){
        UINT8 b;
        int p, 
            df = PIDVars[0].PIDDutyFull, 
            AVG = ADCAVG;
        //OLEDPrintNum88(0, 6, 8, PIDVars[0].Stub);
        //OLEDPrintNum88(0, 7, 5, ((PIDVars[0].HVAvg >> ADCAVG) * 840) >> 10);
        //OLEDPrintNum88(48, 7, 5, ((PIDVars[0].HIAvg >> ADCAVG) * 241) >> 10);
        //OLEDPrintNum88(96, 7, 3, PIDVars[0].HPAvg >> ADCAVG);

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
            if((i & 1)==0)b += 16;
            if((i & 15)==0)b += 40;
            if((i & 31)==0)b += 68;
            if((i & 63)==0)b += 130;
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
        i = 4;
        while(i--){
            OLEDPrint816(0, i * 2, ParDef[TopPar + i].Name, 11);
            if(ParDef[TopPar + i].OLEDDispFunc)(*ParDef[TopPar + i].OLEDDispFunc)(88, i * 2, pars.b[TopPar + i]);
            if((TopPar + i) == CPar){
                if(CMode == 3){
                    OLEDInvert(0, 128 - 44, i * 2, 2);
                }
                if(CMode == 4){
                    OLEDInvert(128 - 44, 44, i * 2, 2);
                }
            }
        }
        
    }
    if(OLEDFlags.f.Cal){
        UINT32 dw = (INT32)IronPars.Config[0].CurrentA * (INT32)IronPars.Config[0].Gain;
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
            OLEDPrintNum68(64,3,1,0);
            OLEDPrintNum68(80,3,3,IronPars.Config[0].CurrentA);
            OLEDPrintNum68(32,4,4,PIDVars[0].ADCTemp[0]);
        }
        else{
            OLEDPrintNum68(64,3,1,1);
            OLEDPrintNum68(80,3,3,IronPars.Config[1].CurrentB);
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
                if(!B1){BTicks[0].n = 0;BTicks[0].d = 0;}
                if(!B2){BTicks[1].n = 0;BTicks[1].d = 0;}
                if(!B3){BTicks[2].n = 0;BTicks[2].d = 0;}

                DispTemp -= DispTemp >> 3;
                i = PIDVars[0].CTemp[0];
                if(IronPars.Config[1].Type) i = (i + PIDVars[1].CTemp[0]) >> 1;
                DispTemp += i;
                //i <<= 3;
                //if(abs(DispTemp-i)>320)DispTemp=i;

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
                    if(B1 || B2 || B3 || (((pars.Holder == 1) || ((pars.Holder == 2) && mainFlags.HolderPresent)) && NAP)){
                        CTicks = 0;
                        CSeconds = 0;
                        CMSeconds = 0;
                        CMinutes = 0;
                    }

                    i = TTemp;
                    if(!NAP){
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
