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
    CJTicks = 0;
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
    VTIBuffCnt = 0;
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
    VTIBuffCnt = 0;
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
            PGD=1;
            if(!mainFlags.ACPower) OnPowerLost();
        case DCTimer:
            if(ISRStep != 9)ISRComplete = 0;
            ISRStep = 0;
            break;
        case CompL2H:
            PGD=0;
            return;
    }

    PV = (t_PIDVars *)&PIDVars[1];
    IC = (t_IronConfig *)&IronPars.Config[1];
    if((ADCStep < 2) || (IC->SensorConfig.Type == 0)){
        PV = (t_PIDVars *)&PIDVars[0];
        IC = (t_IronConfig *)&IronPars.Config[0];
    }

    switch (ISRStep){
        case 0: //AC - high to low point of comparator (around 4.5V), DC - DC Timer interrupt (110Hz);
            OldHeater = HEATER;
            if(ISRStopped){
                HEATER = 0;
                if(!(ISRStopped & 2)){
                    ISRStopped |= 2;
                    mcuADCStop();
                    VTIBuffCnt = 0;
                }
            }
            else{
                mcuCompDisable();
                if(mainFlags.PowerLost) return;
                dw = OffDelayOff;
                if(HEATER && dw < PV->OffDelay) dw = PV->OffDelay;
                dw >>= 4;
                if(dw >= 235) dw -= 215; 
                //dw -= ((OffDelayOff >> 4) * 115) >> 8;
                if(dw > 1000) dw = 1000;
                mcuStartISRTimer_us(dw); //AC - delay to zero cross
            }
            break;
        case 1: //215us before AC zero cross
            mcuReadTime_us(); //zero readtime counter
            if(PV->Power) HEATER = 0; //stop heater if 1/2 or 1/4 power in order for power to be same on odd and even mains half periods.
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
        case 2: //165us before zero cross - setup inputs and wait 150us to read room temperature
                //calculate RMS power and current in the mean time.
            mcuStartISRTimer_us(150);
            mcuADCStartManual();
            mcuADCRefVref();
            if(mainFlags.Calibration){
                CHSEL1 = CalCh ? 0 : 1;
                CHSEL2 = CalCh ? 1 : 0;
                CHPOL = CalCh ? 0 : 1;
            }
            else{
                CHSEL1 = IC->SensorConfig.InputP;
                CHSEL2 = IC->SensorConfig.InputN;
                CHPOL = IC->SensorConfig.InputInv;
            }
            if(ISRComplete){
                if((dw = VTIBuffCnt >> 2) && (VBuff[dw] < 90) && OldHeater && (TIBuff[dw] < 16)){ //power lost if <0.5A and <7.4V
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
                            dw += CompLowTimeOn - CompLowTimeOff; //when heater was on 1/2 or 1/4 power, comp low time is shorter then on full power - compensate for it;
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
                        if((i = l = VTIBuffCnt) > 1){
                            UINT32 cv, ci, sv = 0, si = 0, sp = 0, ri = 0, rv = 0, r = 0;
                            for(i--, l--; i--;){
                                cv = VBuff[i] + VBuff[i + 1];
                                ci = TIBuff[i];
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
                            if(IronPars.Config[1].SensorConfig.Type) dw >>= 1;
                            PV->HV = (mcuSqrt(sv * dw) + 32) >> 6;
                            PV->HI = (mcuSqrt(si * dw) + 16) >> 5;
                            PV->HP = ((sp * dw) + 512) >> 10;
                            PV->HR = r;

                            PV->HNewData = 1;
                        }
                    }
                    else{
                        if(IronPars.ColdJunctionSensorConfig && IC->SensorConfig.HChannel==IronPars.ColdJunctionSensorConfig->HChannel){
                        }
                    }
                }
            }
            VTIBuffCnt = 0;
            ISRComplete = 0;
            break;
        case 3: //15us before zero cross - read room temperature
            mcuADCRead(ADCH_RT,1);
            break;
        case 4: //zero cross - start reading iron temperature.
            if(ADCStep == 0){
                ADCData.VRT = mcuADCRES;
            }
            else{
                ADCData.VRT += mcuADCRES;
            }
            mcuADCRead(ADCH_TEMP, 4);
            break;
        case 5: //60uS after zero cross - check for sensor open, heater open, perform PID and wait to 1/2 power point (AC voltage point just between 2 adjacent zero crosses)
            dw = MAINS_PER_H_US - 60;
            mcuStartISRTimer_us(dw); //next step will be at the center of mains half period

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
            if((ADCStep < 2) || (IC->SensorConfig.Type == 0)){
                PV = (t_PIDVars *)&PIDVars[0];
                IC = (t_IronConfig *)&IronPars.Config[0];
            }
            
            HCH = IC->SensorConfig.HChannel;

            if(!(ADCStep & 1)){
                PV->PWM += PV->PIDDuty;
                PHEATER = ((PV->PWM>>24)!=0);
                PV->PWM &= 0x00FFFFFF;
            }
            
            if(mainFlags.PowerLost || PV->KeepOff || mainFlags.Calibration || IC->SensorConfig.Type == 0 || IC->SensorConfig.Type == 255 )PHEATER = 0;
            if(!PV->Power) HEATER = PHEATER;  //Turn on heater if on full power
            
            mcuADCStartAuto(PHEATER?0:1);
                        
            if(!PHEATER && !CJTicks && IronPars.ColdJunctionSensorConfig && IronPars.ColdJunctionSensorConfig->HChannel == IC->SensorConfig.HChannel){
                CHSEL1 = IronPars.ColdJunctionSensorConfig->InputP;
                CHSEL2 = IronPars.ColdJunctionSensorConfig->InputN;
                CHPOL = IronPars.ColdJunctionSensorConfig->InputInv;
                CBANDA = IronPars.ColdJunctionSensorConfig->CBandA;
                CBANDB = IronPars.ColdJunctionSensorConfig->CBandB;
                I2CData.CurrentA.ui16 = IronPars.ColdJunctionSensorConfig->CurrentA;
                I2CData.CurrentB.ui16 = IronPars.ColdJunctionSensorConfig->CurrentB;
                I2CData.Gain.ui16 = IronPars.ColdJunctionSensorConfig->Gain;
                I2CData.Offset.ui16 = IronPars.ColdJunctionSensorConfig->Offset;
                if(!mainFlags.PowerLost)I2CAddCommands(I2C_SET_CPOT | I2C_SET_GAINPOT | I2C_SET_OFFSET);
            }
            break;
        case 6:  //AC voltage highest point (center of half period) - check for power lost and turn on heater if 1/2 power and wait for 1/4 power point
            PGC=1;
            mcuStartISRTimer_us(MAINS_PER_Q_US); //Next step will be at 1/4 power point in the mains period
            if(!MAINS || ((VBuff[dw = (mcuTIBuffPos() >> 2) - 1] < 90) && PHEATER && (TIBuff[dw] < 16))){ //power lost if <0.5A and <7.4V
                OnPowerLost();
                return;
            }
            if(PV->Power < 2) HEATER = PHEATER;    
            
            if(!mainFlags.Calibration){
                CHSEL1 = 0;
                CHSEL2 = 0;
            }
            CBANDA = IC->SensorConfig.CBandA;
            CBANDB = IC->SensorConfig.CBandB;
            I2CData.CurrentA.ui16 = IC->SensorConfig.CurrentA;
            I2CData.CurrentB.ui16 = IC->SensorConfig.CurrentB;
            I2CData.Gain.ui16 = IC->SensorConfig.Gain;
            I2CData.Offset.ui16 = IC->SensorConfig.Offset;
            I2CAddCommands(I2C_SET_CPOT | I2C_SET_GAINPOT | I2C_SET_OFFSET);     
            if(!PHEATER && !CJTicks && IronPars.ColdJunctionSensorConfig && IronPars.ColdJunctionSensorConfig->HChannel == IC->SensorConfig.HChannel){
                ADCData.VCJ = TIBuff[(mcuTIBuffPos() >> 2) - 1];
                CJTicks = CJ_PERIOD;
            }
            else{
                ADCData.VCJ = 0;
                if(!IronPars.ColdJunctionSensorConfig) CJTicks = 0;
            }
            break;
        case 7: //1/4 power point - turn on heater
            PGC=0;
            HEATER = PHEATER;
            mcuStartISRTimer_us(100);
            break;
        case 8: //enable High-to low comparator event in order to start new cycle.
            mcuCompEnableH2L();
            ISRTicks++;
            if(CJTicks) CJTicks--;
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
