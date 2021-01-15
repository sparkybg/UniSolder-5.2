#define _MENU_C

#include <GenericTypeDefs.h>
#include <stdlib.h>
#include "typedefs.h"
#include "mcu.h"
#include "pars.h"
#include "main.h"
#include "menu.h"
#include "isr.h"
#include "PID.h"
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
static T_MENU_MODE CMode;
static T_MENU_MODE OldMode;
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
static int TipChangeTicks;
static UINT8 FNAP;

static union {
    UINT32 DW;
    struct { __PACKED
        int Header :1;
        int Footer :1;
        int BigTemp :1;
        int Message :1;
        int Set:1;
        int TReset:1;
        int Pars:1;
        int SetPars:1;
        int StandBy:1;
        int Cal:1;
        int Debug:1;
        int Input:1;
        int Version:1;
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

static int LastEnc;
static int EncDiff;

void MenuInit(){
    int i;
    
    CRstTemp = 1;
    CPar = 0;
    CRow = 0;
    CTicks = 0;
    BeepTicks = 0;
    InvertTicks = 0;
    for(i = 0; i < 2; i++){
        BTicks[i].o = 0;
        BTicks[i].n = 0;
        BTicks[i].d = 0;
    }
    CTTemp = TTemp;
    mainFlags.HolderPresent = 0;
    mainFlags.TipChange = 0;
    TempBeep = 1;
    DispTemp = 0;
    CMode = SET_TEMPERATURE;
    ModeTicks = 20;
    FNAP = 1;
    OldNAP = 1;
    NapTicks = pars.NapFilterTicks + 1;
    TipChangeTicks = 0;
    CalCh = 0;
    Enc = LastEnc = 0;
}

void OLEDTasks(){
    int dual = IronPars.Config[1].SensorConfig.Type;
    t_PIDVars * PV1 = (t_PIDVars *)&PIDVars[0];
    t_PIDVars * PV2 = (t_PIDVars *)&PIDVars[1];
    if(!dual) PV2 = PV1;
    OLEDFlags.DW = 0;
    if(mainFlags.PowerLost){
        OLEDFlags.f.Message = 1;
        OLEDMsg1 = "     POWER LOST";
        OLEDMsg2 = "";
    }
    else{
        do{
            DoExit = 1;
            switch(CMode){
                case DEFAULT_MENU: //default mode - display temperature and do nothing
                    if(CTTemp < MINTEMP){                        
                        CMode = STANDBY;
                        OldNAP = FNAP;
                        ModeTicks = 255;
                        DoExit = 0;
                        break;
                    }
                    if(EncDiff) CMode = SET_TEMPERATURE;
                    if(BTicks[1].o && BTicks[1].o < 100 && BTicks[1].n == 0) CMode = RESET_TEMPERATURE;
                    if(CMode != DEFAULT_MENU){
                        DoExit = 0;
                        break;
                    }
                    if(BTicks[1].o <= 100 && BTicks[1].n > 100){ //goto set parameters menu
                        CMode=MENU;
                        ModeTicks=250;
                        BeepTicks=2;
                    }
                    OLEDFlags.f.Header = 1;
                    OLEDFlags.f.Footer = 1;
                    

                    if(IronPars.Config[0].SensorConfig.Type == SENSOR_NONE){
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
                case SET_TEMPERATURE: //set temperature mode
                    if(BTicks[1].n > 100)CMode = DEFAULT_MENU;
                    if(BTicks[1].o && (BTicks[1].n == 0))CMode = RESET_TEMPERATURE; //goto reset temperature mode
                    if(CMode != SET_TEMPERATURE){
                        DoExit = 0;
                        break;
                    }
                    if(EncDiff){ //Temp inc/dec
                        int i = TTemp;
                        ModeTicks = 100;
                        if(EncDiff){
                            int ctt = TTemp;
                            ctt += EncDiff * pars.TempStep;;
                            EncDiff = 0;
                            if(ctt < MINTEMP) ctt = MINTEMP;
                            if(ctt > MAXTEMP) ctt = MAXTEMP;
                            TTemp = ctt;
                        }
                        if(i != TTemp)TempBeep = 1;
                    }
                    OLEDFlags.f.Header = 1;
                    OLEDFlags.f.Footer = 1;
                    OLEDFlags.f.BigTemp = 1;
                    OLEDFlags.f.Set = 1;
                    OLEDTemp = TTemp << 2;
                    break;
                case RESET_TEMPERATURE: //reset temperature mode
                    if(BTicks[1].n > 100)CMode = DEFAULT_MENU;
                    if(EncDiff) CMode = SET_TEMPERATURE;
                    if(CMode != RESET_TEMPERATURE){
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
                    OLEDFlags.f.TReset = 1;
                    OLEDTemp = TTemp << 2;
                    break;
                case MENU: //menu mode
                    if((BTicks[1].o <= 250) && (BTicks[1].n > 250)){
                        CMode = SET_INPUT_TYPE;
                        break;
                    }
                    else{
                        if(BTicks[1].n || EncDiff){
                            ModeTicks = 250;

                            if((EncDiff > 0 && !pars.MenuDown) || (EncDiff < 0 && pars.MenuDown)){CPar++; CRow++;}
                            if((EncDiff < 0 && !pars.MenuDown) || (EncDiff > 0 && pars.MenuDown)){CPar--; CRow--;}
                            EncDiff = 0;
                            if(CRow < 0)CRow = 0;
                            if(CRow > 3)CRow = 3;
                            if(CPar < 0)CPar = (sizeof(MenuOrder) / sizeof(MenuOrder[0])) - 1;
                            if(CPar >= (sizeof(MenuOrder) / sizeof(MenuOrder[0]))) CPar = 0;
                        }
                        if(BTicks[1].o &&(BTicks[1].o < 100) && (BTicks[1].n == 0)){
                            int p = MenuOrder[CPar];
                            switch(p) {
                                case 16: //calibrate
                                    CMode=CALIBRATION;
                                    break;
                                case 17: //Instrument info
                                    CMode=INSTRUMENT_INFO;
                                    break;
                                case 19: //Version info
                                    CMode=VERSION_INFO;
                                    break;
                                default:
                                    CMode=SET_PARAMS;
                                    break;
                            }
                            if(CMode == SET_PARAMS) CParVal = pars.b[(UINT8)MenuOrder[(UINT8)CPar]];
                        }
                        OLEDFlags.f.Pars = 1;
                    }
                    break;
                case SET_PARAMS: //menu set parameter mode
                    {
                        int p = MenuOrder[CPar];
                        if(BTicks[1].n || EncDiff) ModeTicks = 250;
                        if(BTicks[1].o && (BTicks[1].n == 0)){
                            pars.b[p] = CParVal;
                            CMode = MENU;
                        }
                        else {
                            if(EncDiff > 0)CParVal++;
                            if(EncDiff < 0)CParVal--;
                            EncDiff=0;
                            if((CParVal < ParDef[p].Min))CParVal = ParDef[p].Max;
                            if((CParVal > ParDef[p].Max))CParVal = ParDef[p].Min;
                            if(ParDef[p].Immediate)pars.b[p] = CParVal;
                        }
                        OLEDFlags.f.Pars = 1;
                    }
                    break;
                case CALIBRATION: //Calibration
                    ModeTicks = 250;
                    if(BTicks[1].o && !BTicks[1].n){
                        if((BTicks[1].o<100)){
                            mainFlags.Calibration = 0;
                            CMode = DEFAULT_MENU;
                            break;
                        }
                        else{
                            CalCh = CalCh ? 0 : 1;
                        }
                    }
                    UINT16 Current = CalCh ? IronPars.Config[0].SensorConfig.CurrentB : IronPars.Config[0].SensorConfig.CurrentA;                                        
                    if(EncDiff > 0 && Current < 256) Current++;
                    if(EncDiff < 0 && Current > 0) Current--;
                    EncDiff = 0;                    
                    if(CalCh){
                        IronPars.Config[0].SensorConfig.CurrentB = Current;
                    }
                    else{
                        IronPars.Config[0].SensorConfig.CurrentA = Current;                            
                    }
                    OLEDFlags.f.Cal = 1;
                    mainFlags.Calibration = 1;
                    break;
                case INSTRUMENT_INFO: //Instrument information
                    ModeTicks = 250;
                    if(BTicks[1].o && !BTicks[1].n){
                        CMode = DEFAULT_MENU;
                        break;
                    }
                    OLEDFlags.f.Debug = 1;
                    break;
                case SET_INPUT_TYPE: //Set input type mode (keys or encoder type)
                    if(!BTicks[1].o && BTicks[1].n){
                        ModeTicks = 250;
                        EncDiff = 0;
                        pars.Input++;
                        if(pars.Input>ParDef[15].Max) pars.Input = 0;
                    }
                    OLEDFlags.f.Input = 1;
                    break;
                case TIP_CHANGE: //tip change mode
                    if(IronPars.Config[0].SensorConfig.Type == SENSOR_NONE){
                        CMode = DEFAULT_MENU;
                        DoExit = 0;
                        break;
                    }
                    if(mainFlags.TipChange || PV1->NoHeater || PV1->NoSensor || PV2->NoHeater || PV2->NoSensor){
                        ModeTicks = 2;
                    }
                    mainFlags.Calibration = 0;
                    OLEDFlags.f.Header = 1;
                    OLEDFlags.f.Footer = 1;
                    OLEDFlags.f.Message = 1;
                    OLEDMsg1 = "        TIP";
                    OLEDMsg2 = "       CHANGE";
                    break;
                case VERSION_INFO: //Version information
                    ModeTicks = 250;
                    if(BTicks[1].o && !BTicks[1].n){
                        CMode = DEFAULT_MENU;
                        break;
                    }
                    OLEDFlags.f.Version = 1;
                    break;
                case STANDBY: //stand-by
                    if(((pars.WakeUp & 1) && BTicks[1].o <= 50 && BTicks[1].n > 50) ||
                       ((pars.WakeUp & 2) && mainFlags.HolderPresent && FNAP && OldNAP != FNAP)){ //exit from stand-by
                        CTTemp = TTemp;
                        CTicks = 0;
                        CSeconds = 0;
                        CMSeconds = 0;
                        CMinutes = 0;
                        CMode = DEFAULT_MENU;
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
        OLEDPrintXY88(1, 21, "S", 1);
        OLEDPrintXY88(1, 29, "E", 1);
        OLEDPrintXY88(1, 37, "T", 1);    }

    if(OLEDFlags.f.TReset){
        OLEDPrintXY88(1, 26, "T", 1);
        OLEDPrintNumXY88(1, 34, 1, CRstTemp + 1);
    }
    
    if(OLEDFlags.f.Message){
        OLEDPrint68(0, 3, OLEDMsg1, 21);
        OLEDPrint68(0, 4, OLEDMsg2, 21);
    }

    if(OLEDFlags.f.Header){
        OLEDPrint68(0, 0, (const char *)&IronPars.Name, 21);
    }
    if(OLEDFlags.f.Footer){
        UINT8 b;
        int i, p, df, 
            AVG = ADCAVG;

        OLEDPrint68(0, 7, mainFlags.ACPower ? "AC" : "DC", 2);
        OLEDPrint68(12, 7, &("FHQE")[PIDVars[0].Power], 1);// PIDVars[0].Power ? (PIDVars[0].Power == 1 ? "H": "Q"): "F", 1);

        if(PV1->NoHeater || PV1->NoSensor || PV1->ShortCircuit || PV2->NoHeater || PV2->NoSensor || PV2->ShortCircuit){
            df = 0;
            p = 0;
        }
        else{
            if(dual) AVG--;
            df = PV1->PIDDutyFull; 
            p = ((PV1->PIDDuty + 0x7FL) >> 8) * (PV1->HPAvg >> AVG);
            if(dual){
                df += PV2->PIDDutyFull;
                p += ((PV2->PIDDuty + 0x7FL) >> 8) * (PV2->HPAvg >> AVG);
            }
            else{
                df += df;
            }
            df >>= 19;
        }
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
        if(HEATER)OLEDWrite(21, 8, 7, (char*)font8x8[4], 8);
    }
    
    if(OLEDFlags.f.Pars){
        int i, par = CPar - CRow;
        if(par < 0) par += NB_OF_MENU_PARAMS);
        for(i=0; i < 4; i++){
            int p = MenuOrder[par];
            OLEDPrint816(0, i * 2, ParDef[(UINT8)MenuOrder[(UINT8)par]].Name, 11);
            if(ParDef[p].OLEDDispFunc)(*ParDef[p].OLEDDispFunc)(p, 88, i * 2,  pars.b[p]);
            if(par == CPar){
                if(CMode == MENU){
                    OLEDInvert(0, 128 - 44, i * 2, 2);
                }
                if(CMode == SET_PARAMS){
                    if(ParDef[p].OLEDDispFunc)(*ParDef[p].OLEDDispFunc)(p, 88, i * 2,  CParVal);
                    OLEDInvert(128 - 44, 44, i * 2, 2);
                }
            }
            par++;
            if(par >= NB_OF_MENU_PARAMS)) par -= NB_OF_MENU_PARAMS);
        }        
    }
    
    if(OLEDFlags.f.StandBy){
        static int X, Y, DX, DY;
        if(X <= 0) DX = 1;
        if(Y <= 0) DY = 1;
        if((DispTemp >> 4) > 60 && !PV1->NoHeater && !PV1->NoSensor && !PV1->ShortCircuit && !PV2->NoHeater && !PV2->NoSensor && !PV2->ShortCircuit){
            if(X >= ((127 - 24) * 2)){
                X = (127 - 24 )* 2;
                DX = -1;
            }
            if(Y >= ((63 - 16) * 2)){
                Y = (63 - 16) * 2;
                DY =- 1;                                    
            }            
            OLEDPrintXY816(X >> 1, Y >> 1, "HOT", 3);
        }
        else{
            if(X >= ((127 - 18) * 2)) DX = -1;
            if(Y >= ((63 - 8) * 2)) DY =- 1;                                    
            OLEDPrintXY68(X >> 1, Y >> 1, "ZZZ", 3);
        }
        X += DX;
        Y += DY;        
    }
    
    if(OLEDFlags.f.Input){
        const char * StrEncoder[]   = {
            "KEYS", 
            "ENC-A-1PPD", 
            "ENC-AB-2PPD", 
            "ENC-A-2PPD", 
            "ENC-AB-4PPD"
        };

        OLEDPrint68(13, 0, "CONTROL SELECTION", 0);
        int i;
        for(i = 0; i <= 4; i++){
            OLEDPrintXY88(2, i * 10 + 14, StrEncoder[i], 0);
            if(i == pars.Input) OLEDInvertXY(0, 124, i * 10 + 12, 11);
        }
    }
    
    if(OLEDFlags.f.Cal){
        UINT32 dw = (INT32)(CalCh ? IronPars.Config[0].SensorConfig.CurrentB : IronPars.Config[0].SensorConfig.CurrentA) * (INT32)IronPars.Config[0].SensorConfig.Gain;
        if(dw){                    
            CalRes -= CalRes >> 3;                        
            CalRes += ((INT32)PIDVars[0].ADCTemp[0] * (INT32)33437L) / dw;  //CalRes = R*800
        }
        else{
            CalRes = 0;
        }
        
        OLEDPrint68(0, 0, "CALIBRATION        V", 0);
        OLEDPrintNum68(122, 0, 1, BoardVersion);
        OLEDPrint68(0, 1, "ENC:", 0);
        OLEDPrint68(60,1, "HLD:", 0);
        OLEDPrint68(0, 2, "IRON ID:", 0);
        OLEDPrint68(0, 3, "CURRENT:", 0);
        OLEDPrint68(0, 4, "ADC:", 0);
        OLEDPrint68(0, 5, "R:", 0);
        OLEDPrint68(0, 6, "ROOM:", 0);
        OLEDPrint68(0, 7, "PERIOD:", 0);
        OLEDPrintNum68(24, 1, 5, Enc);
        OLEDPrintNum68(84, 1, 4, Holder);
        OLEDPrintHex68(64, 2, 4, IronID);
        if(IronPars.Config[1].SensorConfig.Type == SENSOR_UNDEFINED || (LISRTicks % 200) < 100){
            OLEDPrintNum68(64, 3, 1, CalCh);
            OLEDPrintNum68(80, 3, 3, CalCh ? IronPars.Config[0].SensorConfig.CurrentB : IronPars.Config[0].SensorConfig.CurrentA);
            OLEDPrintNum68(32, 4, 4, PIDVars[0].ADCTemp[0]);
        }
        else{
            OLEDPrintNum68(64, 3, 1, 1 - CalCh);
            OLEDPrintNum68(80, 3, 3, CalCh ? IronPars.Config[1].SensorConfig.CurrentA : IronPars.Config[1].SensorConfig.CurrentB);
            OLEDPrintNum68(32, 4, 4, PIDVars[1].ADCTemp[0]);            
        }
        OLEDPrintNum68(16, 5, 5, CalRes >> 3);
        OLEDPrintNum68(40, 6, 3, CRTemp >> 1);
        OLEDPrintNum68(56, 7, 9, MAINS_PER_US);
    }
    
    if(OLEDFlags.f.Debug){        
        int AVG = ADCAVG;
        if(IronPars.Config[1].SensorConfig.Type) AVG--;

        OLEDPrint68(0,0,"INSTRUMENT INFO", 0);
        
        OLEDPrint68(0, 2, "    ID:", 0);
        OLEDPrint68(0, 3, "  Pmax:", 0);
        OLEDPrint68(0, 4, " Power:", 0);
        OLEDPrint68(0, 5, " HPmax:", 0);
        OLEDPrint68(0, 6, "CJTemp:", 0);
        OLEDPrint68(0, 7, "  Room:", 0);
        
        OLEDPrintHex68(54, 2, 4, IronID);
        
        int ch;        
        if(IronPars.Config[1].SensorConfig.Type == SENSOR_UNDEFINED || (LISRTicks % 200) <100){
            ch = 0;
        }
        else{
            ch = 1;
        }        
        OLEDPrintNum68(54, 4, 2, ch);
        switch (PIDVars[ch].Power){
            case 0: 
                OLEDPrint68(70, 4, "FULL", 0);
                break;
            case 1: 
                OLEDPrint68(70, 4, "1/2", 0);
                break;
            case 2: 
                OLEDPrint68(70, 4, "1/4", 0);
                break;                    
            case 3: 
                OLEDPrint68(70, 4, "1/8", 0);
                break;                    
        }
        OLEDPrintNum68(54, 3, 3, IronPars.Config[ch].PID_PMax);
        OLEDPrintNum68(54, 5, 3, PIDVars[ch].HPMax);
        OLEDPrintNum68(54, 5, 3, PIDVars[ch].HPMax);
        OLEDPrintNum68(54, 6, 5, CJTemp >> 1);
        OLEDPrintNum68(54 ,7, 5, CRTemp >> 1);

    }
    
    if(OLEDFlags.f.Version){
        OLEDPrint68(0,0,"VERSION INFO", 0);
        OLEDPrint68(0,2,"HW VER:", 0);
        OLEDPrintNum68(50, 2, 1, BoardVersion);
        OLEDPrint68(0,3,"FW VER:  .", 0);
        OLEDPrintNum68(50, 3, 1, VERSION_MAJOR);
        OLEDPrintHex68(60, 3, 2, VERSION_MINOR);/*as hex to display 2 digits*/
        OLEDPrint68(0,4,"FW CRC:", 0);
        OLEDPrintHex68(54, 4, 4, APP_CRC_VALUE);
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
                int userInput=0;
                for(i = 0; i < 3; i++){
                    BTicks[i].o = BTicks[i].n;
                    if(BTicks[i].n < 65535 )BTicks[i].n++;
                    BTicks[i].d = (BTicks[i].n == 1) || ((BTicks[i].n > 25) && ((LISRTicks & 3) == 1));
                }
                if(!B2){BTicks[1].n = 0;BTicks[1].d = 0;}
                if(!pars.Input){
                    if(!(pars.Buttons?B3:B1)){BTicks[0].n = 0;BTicks[0].d = 0;}
                    if(!(pars.Buttons?B1:B3)){BTicks[2].n = 0;BTicks[2].d = 0;}
                    if(BTicks[0].d) Enc += ((BTicks[0].n >> 6) + 1)<<2;
                    if(BTicks[2].d) Enc -= ((BTicks[2].n >> 6) + 1)<<2;
                }
                else{
                    BTicks[0].o = 0;
                    BTicks[0].n = 0;
                    BTicks[0].d = 0;
                    BTicks[2].o = 0;
                    BTicks[2].n = 0;
                    BTicks[2].d = 0;
                }
                {
                    int cEnc = Enc;
                    cEnc >>= 2;                    
                    if(LastEnc != cEnc){
                        EncDiff += (LastEnc - cEnc);
                        LastEnc = cEnc;
                    }
                }
                userInput = B2 | EncDiff;

                DispTemp -= DispTemp >> 3;
                i = PIDVars[0].CTemp[0];
                if(IronPars.Config[1].SensorConfig.Type) i = (i + PIDVars[1].CTemp[0]) >> 1;
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
                    CMode = DEFAULT_MENU;
                }
                
                if(CMode == TIP_CHANGE && IronPars.Config[0].SensorConfig.Type != SENSOR_NONE){
                    mainFlags.TipChange = Holder > 375 && Holder <= 750;
                    NapTicks = 0;
                    FNAP = 0;
                }
                else{
                    if (Holder <= 750 && IronPars.Config[0].SensorConfig.Type != SENSOR_NONE){ //instrument in holder or tip-change holder
                        mainFlags.HolderPresent = 1;
                        NapTicks = 0;
                        FNAP = 0;
                        if(Holder <=375){ //instrument in holder
                            TipChangeTicks = 0;
                            mainFlags.TipChange = 0;
                        }
                        else{ //instrument in tip-change holder
                            if(!mainFlags.Calibration && pars.Holder){
                                if(TipChangeTicks < 15){
                                    TipChangeTicks++;
                                }
                                else {
                                    CMode = TIP_CHANGE;
                                    mainFlags.TipChange = 1;
                                    ModeTicks = 100;
                                }               
                            }                            
                        }
                    }
                    else{ //instrument out of holder or no instrument
                        TipChangeTicks = 0;
                        mainFlags.TipChange = 0;
                        if (NapTicks <= pars.NapFilterTicks){
                            NapTicks++;
                        }
                        else{
                            FNAP = 1;
                        }
                    }
                }
                

                if(CMode == STANDBY){
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
                    
                    if(userInput || (((pars.Holder == 1) || ((pars.Holder == 2) && mainFlags.HolderPresent)) && (FNAP || CMode == TIP_CHANGE))){
                        CTicks = 0;
                        CSeconds = 0;
                        CMSeconds = 0;
                        CMinutes = 0;
                    }

                    i = TTemp;
                    if(!FNAP){
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
