#define _ISR_C
#include <xc.h>
#include <GenericTypeDefs.h>
#include <peripheral/i2c.h>
#include <peripheral/adc10.h>
#include "mcu.h"
#include "isr.h"
#include "pars.h"
#include "main.h"
#include "iron.h"
#include "PID.h"
#include "io.h"

volatile unsigned int ISRComplete = 0;

volatile int I2CCommands;
volatile int I2CCCommand;

void ISRInit(){
    int i;
    ISRStep = 0;
    ADCStep = 0;
    ISRTicks = 1;
    PHEATER = 0;
    I2CStep = 0;
    I2CCommands = 0;
    I2CCCommand = 0;
    I2CIdle = 1;
    ISRStopped = 0;
    EEPAddrR = 0xFFFF;
    EEPDataR = 0;
    EEPCntR = 0;
    EEPAddrW = 0xFFFF;
    EEPDataW = 0;
    EEPCntW = 0;
    for(i = 2; i--;){
        PIDVars[i].NoHeater = 255;
        PIDVars[i].NoSensor = 255;
        PIDVars[i].ShortCircuit = 255;
        PIDVars[i].HInitData = 1;
        PIDVars[i].OffDelay = 1600;
    }
    OffDelayOff = 1600;
    VIBuffCnt = 0;
    mainFlags.Calibration = 0;
    ISRComplete = 0;
    mainFlags.PowerLost = 0;
}

void ISRStop(){
    ISRStopped = 1;
    while(!(ISRStopped & 2));
    while(!I2CIdle);
    mcuADCStop();
    mcuStopISRTimer();
    mcuCompDisable();
    mainFlags.PowerLost = 0;
}

void ISRStart(){
    mcuDisableInterrupts();
    mcuCompDisable();
    mcuADCStop();
    mcuStopISRTimer();
    if(mainFlags.ACPower){
        while(MAINS);
        while(!MAINS);
        _delay_us(1000);
    }
    mcuDCTimerReset();
    mcuCompEnableH2L();
    VIBuffCnt = 0;
    ISRStopped = 0;
    mainFlags.PowerLost = 0;
    mcuEnableInterrupts();
}

void I2CAddCommands(int c)
{
    int i;
    i=mcuDisableInterrupts();
    I2CCommands |= c;
    if(I2CIdle)mcuI2CWakeUp();
    mcuRestoreInterrupts(i);
}

void OnPowerLost(){
    if(!mainFlags.PowerLost){
        mainFlags.PowerLost = 1;
        HEATER = 0;
        mcuADCStop();
        mcuStopISRTimer();
        mcuCompDisable();
        ISRStep = 0;
        ADCStep = 0;
    }    
}

void ISRHigh(int src){
    static int OldHeater;
    t_PIDVars *PV;
    t_IronConfig *IC;
    UINT32 dw;

    switch(src){
        case CompH2L:
            if(!mainFlags.ACPower) OnPowerLost();
        case DCTimer:
            if(ISRStep != 9)ISRComplete = 0;
            ISRStep = 0;
            break;
        case CompL2H:
            return;
    }

    PV = (t_PIDVars *)&PIDVars[1];
    IC = (t_IronConfig *)&IronPars.Config[1];
    if((ADCStep < 2) || (IC->Type == 0)){
        PV = (t_PIDVars *)&PIDVars[0];
        IC = (t_IronConfig *)&IronPars.Config[0];
    }

    switch (ISRStep){
        case 0:
            OldHeater = HEATER;
            if(ISRStopped){
                HEATER = 0;
                if(!(ISRStopped & 2)){
                    ISRStopped |= 2;
                    mcuADCStop();
                    VIBuffCnt = 0;
                }
            }
            else{
                mcuCompDisable();
                if(mainFlags.PowerLost) return;
                dw = OffDelayOff;
                if(HEATER && dw < PV->OffDelay) dw = PV->OffDelay;
                dw >>= 4;
                dw -= ((OffDelayOff >> 4) * 115) >> 8;
                if(dw > 1000) dw = 1000;
                mcuStartISRTimer_us(dw); //delay to zero current when AC power
            }
            break;
        case 1:
            //if(OldHeater && (ADCStep & 1))LATBbits.LATB7= ! LATBbits.LATB7;
            
            LATBbits.LATB7 = 1;
            mcuReadTime_us(); //zero readtime counter
            if(PV->Power) HEATER = 0;
            if(ADCStep & 1){
                HEATER = 0;
            }else{
                if(ISRComplete) mcuCompEnableL2H();                
            }
            if(mainFlags.ACPower){
                mcuStartISRTimer_us(50);
            }
            else{
                mcuStartISRTimer_us(450);
            }
            break;
        case 2:
            //if(OldHeater && (ADCStep & 1))LATBbits.LATB7= ! LATBbits.LATB7;
            mcuStartISRTimer_us(150);
            mcuADCStartManual();
            mcuADCRefVref();
            CHSEL1 = IC->InputP;
            CHSEL2 = IC->InputN;
            CHPOL = IC->InputInv;
            if(ISRComplete){
                if((dw = VIBuffCnt >> 2) && (VBuff[dw] < 90) && (IBuff[dw] < 16)){ //power lost if <0.5A and <7.4V
                    OnPowerLost();
                    ISRStep = 0;
                    return;
                }
                if(ADCStep & 1){
                    if(mainFlags.ACPower && CompLowTime){          //calculate delay from comparator trigger to zero current (just before zero cross)
                        dw = OldHeater ? PV->OffDelay : OffDelayOff;
                        if(dw <= 1600) dw = CompLowTime << 4;                                               
                        dw -= dw >> 4;
                        dw += CompLowTime;

                        if(OldHeater && PV->Power && CompLowTimeOn && CompLowTimeOff && CompLowTimeOn > CompLowTimeOff){
                            dw += CompLowTimeOn - CompLowTimeOff; //when heater was on and half power, comp low time is shorter then on full power - compensate for it;
                        }

                        if(dw < 1600) dw = 1600;

                        if(OldHeater){
                            PV->OffDelay = dw;                                
                        }
                        else{
                            OffDelayOff = dw;
                        }
                    }
                    else{
                        OffDelayOff = PV->OffDelay = 1600;
                    }
                    CompLowTime = 0;
                }
                else{
                    if(OldHeater){
                        UINT32 i, l;
                        if((i = l = VIBuffCnt) > 1){
                            UINT32 cv, ci, sv = 0, si = 0, sp = 0, ri = 0, rv = 0, r = 0;
                            for(i--, l--; i--;){
                                cv = (VBuff[i] + VBuff[i + 1]);
                                ci = IBuff[i];
                                if(ci < 1023 && ri < ci && VBuff[i] < 1023 && VBuff[i + 1] < 1023){
                                    ri = ci;
                                    rv = cv;
                                    r = 0;
                                }
                                if(ci >= 1023){
                                    if(!r && ri) r = ((rv * 6738) / ri) >> 9;
                                    if(r) ci = ((cv * 6738) / r) >> 9;
                                }
                                sv += cv * cv;
                                si += ci * ci;
                                sp += ci * cv;
                                if(BuffEmpty){
                                    Buff1[i] = ci;
                                    Buff2[i] = cv;
                                }
                            }
                            Buff1[l + 1] = 256;
                            BuffEmpty = 0;

                            r = (ri ? (((rv * 6738) / ri) + 256) >> 9 : 0x7FFF);
                            //if(ri)r = ((rv * 6738) / ri) >> 8;
                            // 6738 = 10 * 256 * (((Rs1 * (R48 / R42)) / VRef) * 1024) / (((R51 / (R47 + R51)) / VRef) * 1024)
                            //      = 10 * 256 * (((0.003 * (47K / 1.5K)) / 3.0V) *1024) / (((1K / (27K + 1K)) / 3.0V) * 1024)
                            //      = 6737.92

                            sv = (sv + (l >> 1)) / l;
                            si = (si + (l >> 1)) / l;
                            l *= (UINT32)(391 * 2);
                            sp = (sp + (l >> 1)) / l;
                            // 391 = (((R51 / (R47 + R51)) / VRef) * 1024) * (((Rs1 * (R48 / R42)) / VRef) * 1024)
                            //     = (((1K / (27K + 1K)) / 3.0V) * 1024) * (((0.003 * (47K / 1.5K)) /3.0V) * 1024)
                            //     = 391,13549206349206349206349206349

                            dw = 1024;
                            if(IronPars.Config[1].Type) dw >>= 1;
                            PV->HV = (mcuSqrt(sv * dw) + 32) >> 6;
                            PV->HI = (mcuSqrt(si * dw) + 16) >> 5;
                            PV->HP = ((sp * dw) + 512) >> 10;
                            PV->HR = r;

                            PV->HNewData = 1;
                        }
                    }
                }
            }
            VIBuffCnt = 0;
            ISRComplete = 0;
            break;
        case 3:
            mcuADCRead(ADCH_RT,1);
            break;
        case 4:
            if(ADCStep == 0){
                ADCData.VRT = mcuADCRES;
            }
            else{
                ADCData.VRT += mcuADCRES;
            }
            //if(OldHeater && (ADCStep & 1))LATBbits.LATB7= ! LATBbits.LATB7;
            mcuADCRead(ADCH_TEMP, 4);
            break;
        case 5:
            //if(OldHeater && (ADCStep & 1))LATBbits.LATB7= ! LATBbits.LATB7;
            if(!mainFlags.Calibration){
                CHSEL1 = 0;
                CHSEL2 = 0;
            }
            ADCData.HeaterOn = PHEATER;
            ADCData.VTEMP[ADCStep & 1] = mcuADCRES >> 2;
            
            if(ADCStep & 1) {
                if(PV->HR > 3000) {
                    if(PV->NoHeater < 255) PV->NoHeater++;
                }
                else{
                    PV->NoHeater = 0;
                }
                if(PV->HR < 8){
                    if(PV->ShortCircuit < 255) PV->ShortCircuit++;
                }
                else{
                    PV->ShortCircuit = 0;
                }
                if(ADCData.VTEMP[1] >= 1023){
                    if(PV->NoSensor < 255) PV->NoSensor++;
                }
                else{
                    PV->NoSensor = 0;
                }
                PID(ADCStep >> 1);
                if(PV->KeepOff)PV->KeepOff--;
            }


            ADCStep = (ADCStep + 1) & 3;
            
            PV = (t_PIDVars *)&PIDVars[1];
            IC = (t_IronConfig *)&IronPars.Config[1];
            if((ADCStep < 2) || (IC->Type == 0)){
                PV = (t_PIDVars *)&PIDVars[0];
                IC = (t_IronConfig *)&IronPars.Config[0];
            }
            
            HCH = IC->HChannel;
            CBANDA = IC->CBandA;
            CBANDB = IC->CBandB;
            I2CData.CurrentA.ui16 = IC->CurrentA;
            I2CData.CurrentB.ui16 = IC->CurrentB;
            I2CData.Gain.ui16 = IC->Gain;
            I2CData.Offset.ui16 = IC->Offset;
            if(!mainFlags.PowerLost)I2CAddCommands(I2C_SET_CPOT | I2C_SET_GAINPOT | I2C_SET_OFFSET);

            if(!(ADCStep & 1)){
                PV->PWM += PV->PIDDuty;
                PHEATER = ((PV->PWM>>24)!=0);
                PV->PWM &= 0x00FFFFFF;
            }
            
            if(mainFlags.PowerLost || PV->KeepOff || mainFlags.Calibration || IC->Type == 0 || IC->Type == 255 )PHEATER = 0;
            if(!PV->Power) HEATER = PHEATER;
            mcuADCStartAuto();
            dw = MAINS_PER_H_US;
            dw -= mcuReadTime_us();
            mcuStartISRTimer_us(dw);
            break;
        case 6:
            LATBbits.LATB7 = 0;
            mcuStartISRTimer_us(MAINS_PER_Q_US);
            if(!MAINS || ((VBuff[dw = (mcuIBuffPos() >> 2) - 1] < 90) && (IBuff[dw] < 16))){ //power lost if <0.5A and <7.4V
                OnPowerLost();
                return;
            }
            if(PV->Power < 2) HEATER = PHEATER;
            break;
        case 7:
            HEATER = PHEATER;
            mcuStartISRTimer_us(100);
            break;
        case 8:
            mcuCompEnableH2L();
            ISRTicks++;
            ISRComplete = 1;
            break;
    }
    if(ISRStep<255)ISRStep++;    
}


void I2CISRTasks(){
    
    int i;
    UINT16 ui;
    BOOL CmdOK;

    if(I2CCCommand){
        I2CStep++;
    }
    else{
        I2CStep=0;
        i=mcuDisableInterrupts();
        if(I2CCommands &= 0xFF){
            I2CCCommand = 1;
            while(I2CCCommand &= 0xFF){
                if(I2CCommands & I2CCCommand){
                    I2CCommands -= I2CCCommand;
                    I2CIdle=0;
                    break;
                }
                I2CCCommand <<= 1;
            }
        }
        else{
            I2CIdle=1;
        }
        mcuRestoreInterrupts(i);
    }
    
    CmdOK = TRUE;
    switch(I2CCCommand){
        case I2C_SET_CPOT:
            switch(I2CStep){
                case 0:
                    mcuI2CStart();
                    break;
                case 1:
                    mcuI2CSendAddrW(CPOT);
                    break;
                case 2:
                    mcuI2CSendByte(0x40); //write to TCON, disable general ca??
                    break;
                case 3:
                    ui=0xFF;
                    if(I2CData.CurrentA.ui16 == 0) ui &= 0xF0;      //disconnect R0A when currentA is 0
                    if(I2CData.CurrentA.ui16 >= 256) ui &= 0xFE;    //disconnect R0B when currentA is MAX
                    if(I2CData.CurrentB.ui16 == 0) ui &= 0x0F;      //disconnect R1A when currentB is 0
                    if(I2CData.CurrentB.ui16 >= 256) ui &=0xEF;     //disconnect R1B when currentB is MAX
                    mcuI2CSendByte(ui); //write to TCON
                    break;
                case 4:
                    mcuI2CSendByte(I2CData.CurrentA.ui16 >> 8); //Wiper0
                    break;
                case 5:
                    mcuI2CSendByte(I2CData.CurrentA.ui16 & 0xFF);
                    break;
                case 6:
                    mcuI2CSendByte((I2CData.CurrentB.ui16 >> 8) | 0x10); //Wiper1
                    break;
                case 7:
                    mcuI2CSendByte(I2CData.CurrentB.ui16 & 0xFF);
                    break;
                case 8:
                    I2CCCommand=0;
                    mcuI2CStop();
                    break;
            }
            break;
        case I2C_SET_GAINPOT:
            switch(I2CStep){
                case 0:
                    mcuI2CStart();
                    break;
                case 1:
                    mcuI2CSendAddrW(GAINPOT);
                    break;
                case 2:
                    mcuI2CSendByte(I2CData.Gain.ui16 >> 8);
                    break;
                case 3:
                    mcuI2CSendByte(I2CData.Gain.ui16 & 0xFF);
                    break;
                case 4:
                    I2CCCommand=0;
                    mcuI2CStop();
                    break;
            }
            break;
        case I2C_SET_OFFSET:
            switch(I2CStep){
                case 0:
                    mcuI2CStart();
                    break;
                case 1:
                    mcuI2CSendAddrW(OFFADC);
                    break;
                case 2:
                    mcuI2CSendByte(0b01011000);
                    break;
                case 3:
                    mcuI2CSendByte(I2CData.Offset.ui16 >> 2);
                    break;
                case 4:
                    mcuI2CSendByte((I2CData.Offset.ui16 << 6) & 0xFF);
                    break;
                case 5:
                    I2CCCommand=0;
                    mcuI2CStop();
                    break;
            }
            break;
        case I2C_EEPWRITE:
            switch(I2CStep){
                case 0:
                    mcuI2CStart();
                    break;
                case 1:
                    mcuI2CSendAddrW(EEP);
                    break;
                case 2:
                    if(CmdOK = mcuI2CIsACK())mcuI2CSendByte(EEPAddrW >> 8);
                    break;
                case 3:
                    mcuI2CSendByte(EEPAddrW & 0xFF);
                    break;
                case 4:
                    mcuI2CSendByte(*((UINT8*)EEPDataW));
                    break;
                case 5:
                    EEPCntW--;
                    if(EEPCntW){
                        EEPDataW++;
                        EEPAddrW++;
                        if(((EEPAddrW & 31) == 0) || (I2CCommands & (I2CCCommand-1))){ //Abort if EEPROM page boundary is crossed, or if there is pending higher priority command
                            CmdOK = FALSE;
                        }
                        else {
                            I2CStep = 4;
                            mcuI2CSendByte(*((UINT8*)EEPDataW));
                        }
                    }
                    else{
                        EEPAddrW=0xFFFF;
                        I2CCCommand=0;
                        mcuI2CStop();
                    }
                    break;
            }
            break;
        case I2C_EEPREAD:
            switch(I2CStep){
                case 0:
                    mcuI2CStart();
                    break;
                case 1:
                    mcuI2CSendAddrW(EEP);
                    break;
                case 2:
                    if(CmdOK = mcuI2CIsACK())mcuI2CSendByte(EEPAddrR >> 8);
                    break;
                case 3:
                    mcuI2CSendByte(EEPAddrR & 0xFF);
                    break;
                case 4:
                    mcuI2CStart();
                    break;
                case 5:
                    mcuI2CSendAddrR(EEP);
                    break;
                case 6:
                    mcuI2CReceiverEnable();
                    break;
                case 7:
                    *((UINT8 *)EEPDataR) = mcuI2CGetByte();
                    EEPCntR--;
                    if(EEPCntR){
                        EEPDataR++;
                        EEPAddrR++;
                        if(((EEPAddrR & 31) == 0) || (I2CCommands & (I2CCCommand - 1))){ //Abort if EEPROM page boundary is crossed, or if there is pending higher priority command
                            mcuI2CReceiverDisable();
                            CmdOK = FALSE;                            
                        }
                        else{
                            mcuI2CACK();
                            I2CStep = 5;
                        }
                    }
                    else{
                        mcuI2CReceiverDisable();
                        EEPAddrR = 0xFFFF;
                        I2CCCommand=0;
                        mcuI2CStop();
                    }
                    break;
            }
            break;
        default:
            I2CCCommand=0;
            break;
    }
    if(CmdOK == FALSE){
        I2CCommands |= I2CCCommand;
        I2CCCommand=0;
        mcuI2CStop();
    }    
}

#undef _ISR_C
