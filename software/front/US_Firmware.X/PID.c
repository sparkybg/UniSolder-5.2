#define _PID_C

#include <GenericTypeDefs.h>
#include "PID.h"
#include "isr.h"
#include "iron.h"
#include "ExtFloat.h"

//volatile int LastOn;
//volatile unsigned char OffCnt;
//volatile unsigned char NoHeaterCnt;

void PIDInit(){
    int i;
    for(i = 2; i--;){
        PIDVars[i].Starting = 1;
        PIDVars[i].PIDDuty = 0;
        PIDVars[i].PIDDutyP = 0;
        PIDVars[i].PIDDutyI = 0;
        PIDVars[i].PIDDutyFull = 0;
        PIDVars[i].PWM = 0;
        PIDVars[i].OffDelay = 1600;
        PIDVars[i].Power = 0;
    }
};

#define intshr(a,b) ((a < 0) ? (-((-a) >> b)) : (a >> b))

#define assertin(a,b,c) \
    if(b<c){\
        if(a<b)a=b;\
        if(a>c)a=c;\
    }\
    else{\
        if(a<c)a=c;\
        if(a>b)a=b;\
    }

void PID(int PIDStep) {
    int i, w, AVG;
    INT32 dw, pdt;    
    t_PIDVars * PV;
    t_IronConfig * IC;
    int WSL;
    
    AVG = ADCAVG;
    PV =(t_PIDVars *)&PIDVars[PIDStep];
    IC =(t_IronConfig *)&IronPars.Config[PIDStep];
    if(IronPars.Config[1].Type){
        AVG--;
    }
    else{
        PV =(t_PIDVars *)&PIDVars[0];
        IC =(t_IronConfig *)&IronPars.Config[0];
    }
    WSL = IC->WSLen;
    if(WSL < 0) WSL = (IronPars.Config[1].Type ? 4 : 8);
    
    if(PV->NoHeater || PV->NoSensor || PV->Starting || PV->ShortCircuit || PV->LastTTemp != CTTemp)PV->DestinationReached = 0;
    PV->LastTTemp = CTTemp;

/**** GET ROOM TEMPERATURE **********************************************************/
    if(PIDStep){
        dw = ADCData.VRT >> 2;
        dw *= 147;
        dw >>= 8;
        dw -= 100;
        RTAvg -= intshr(RTAvg, ADCAVG);
        RTAvg += dw;
        CRTemp = intshr(RTAvg, ADCAVG);
    }
/************************************************************************************/

/**** GET HEATER RESISTANCE *********************************************************/
    if(PV->NoHeater) PV->NoHeaterCnt = (1 << (AVG + 1));
    if(PV->NoHeaterCnt) PV->NoHeaterCnt--;
    if(PV->NoHeater){
        PV->HInitData = 1;
        PV->HVAvg = 0;
        PV->HIAvg = 0;
        PV->HRAvg = 0x7FFF;
        PV->HPAvg = 0;
        PV->OffDelay = 1600;
    }
    else{
        if(PV->HInitData) PV->HRAvg = PV->HR << AVG;
        if(PV->HNewData){
            if(PV->HInitData){
                PV->HVAvg = PV->HV << AVG;
                PV->HIAvg = PV->HI << AVG;
                PV->HRAvg = PV->HR << AVG;
                PV->HPAvg = PV->HP << AVG;
                PV->HInitData = 0;
            }
            PV->HVAvg -= PV->HVAvg >> AVG;
            PV->HVAvg += PV->HV;
            PV->HIAvg -= PV->HIAvg >> AVG;
            PV->HIAvg += PV->HI;
            PV->HRAvg -= PV->HRAvg >> AVG;
            PV->HRAvg += PV->HR;
            PV->HPAvg -= PV->HPAvg >> AVG;
            PV->HPAvg += PV->HP;
            PV->HNewData=0;
        }
    }
/************************************************************************************/
    
    PV->ADCTemp[1]=PV->ADCTemp[0];
    PV->ADCTemp[0] = ADCData.VTEMP[1];

/**** WAVE SHAPING *****************************************************/
    PV->WSCorr = 0;
    if(IC->WSLen){
        if(PV->Starting || PV->NoHeaterCnt || PV->NoSensor || PV->ShortCircuit){
            for(i = 8; i--; ){
                PV->WSDelta[i].cnt = 0;
                PV->WSDelta[i].val = 0;
                PV->WSMul = 32768;
                PV->WSTemp = 0;
            }
        }
        else{
            //if(PV->DestinationReached == 0) for(i = 8; i--;) PV->WSDelta[i].cnt = 0;            
            if(ADCData.HeaterOn){
                if(PV->OffCnt > 1){
                    i = min(PV->OffCnt, 8);
                    w = PV->WSDelta[0].val;
                    if(i > PV->WSDelta[0].cnt){
                        PV->WSDelta[0].cnt = i;
                        PV->WSDelta[0].val = (PV->ADCTemp[1] - PV->ADCTemp[0]) << 1;
                    }
                    else if(i == PV->WSDelta[0].cnt){
                        PV->WSDelta[0].val = intshr(PV->WSDelta[0].val, 1);
                        PV->WSDelta[0].val += (PV->ADCTemp[1] - PV->ADCTemp[0]);
                    }
                    w -= PV->WSDelta[0].val;
                    for(i = 1; i < 8; i++) PV->WSDelta[i].val -= w;
                }
                PV->LastOn = PV->ADCTemp[0];
                PV->OffCnt = 0;                
                PV->WSCorr = intshr(PV->WSDelta[0].val, 1);
            }
            else{
                if(PV->OffCnt < 8){
                    if(PV->OffCnt > 0){
                        if(PV->WSDelta[PV->OffCnt].cnt==0){
                            PV->WSDelta[PV->OffCnt].val = intshr(PV->WSDelta[0].val, 1) - (PV->ADCTemp[0] - PV->LastOn);
                            PV->WSDelta[PV->OffCnt].cnt = 1;
                        }
                        else{
                            PV->WSDelta[PV->OffCnt].val = intshr(PV->WSDelta[PV->OffCnt].val, 1);
                        }
                        PV->WSDelta[PV->OffCnt].val += intshr(PV->WSDelta[0].val, 1) - (PV->ADCTemp[0] - PV->LastOn);
                        assertin(PV->WSDelta[PV->OffCnt].val, 0, PV->WSDelta[PV->OffCnt - 1].val);
                        if(PV->OffCnt == 1){                        
                            //WSMul = multiplier for damping waveshaping
                            if(PV->WSDelta[0].val != 0){
                                PV->WSMul = (((INT32)PV->WSDelta[1].val) << 16) / ((INT32)PV->WSDelta[0].val);                             
                                //PV->WSMul *= 1200;
                                //PV->WSMul >>= 10;
                                if(PV->WSMul < 0) PV->WSMul = 0;
                                if(PV->WSMul > 32768) PV->WSMul = 32768;
                            }
                        }
                    }
                    if(IC->WSLen < 0){
                        //damping waveshaping
                        if(PV->WSDelta[0].val > 0){
                            dw = (PV->WSMul * 1152) >> 10;
                            for(i = 1; i < PV->OffCnt; i++){
                                dw = (dw * ((PV->WSMul * 1700) >> 10)) >> 16;
                            }
                        }
                        else{
                            dw = PV->WSMul;
                            for(i = 1; i < PV->OffCnt; i++){
                                dw = (dw * PV->WSMul) >> 16;
                            }                            
                        }
                        PV->WSCorr = intshr((((INT32)PV->WSDelta[0].val) * dw), 17);                    
                    }
                    else{
                        //sample waveshaping
                        if(PV->OffCnt < IC->WSLen)PV->WSCorr = intshr(PV->WSDelta[PV->OffCnt].val, 1);
                    }
                }
            }
            //if(IC->WSLen > 0){ 
                //sample waveshaping
                //if(PV->OffCnt < IC->WSLen){
                    //PV->WSCorr = intshr(PV->WSDelta[PV->OffCnt].val, 1);
                //}
                //else{
                    //PV->WSCorr += (intshr(PV->WSDelta[IC->WSLen - 1].val, 1) * (IC->WSLen-1)) / PV->OffCnt;
                //}
            //}
            if(PV->OffCnt < 255)PV->OffCnt++;
        }
    }
/************************************************************************************/
    w = PV->WSCorr *= 1024;
    w >>= 10;//PV->WSCorr >>= 10
/**** GET AND NORMALISE IRON TEMPRATURE *********************************************/
    w += PV->ADCTemp[0];
    //w = PV->ADCTemp[0] + PV->WSCorr;
    if(w < 0) w = 0;

    //heater resistance compensation for series TC
    //compensation = (HRCompCurrent * 19.6 * Gain * HRAvg)/65536
    //compensation = (((HRCompCurrent * Gain * 20070) / 32767) * HRAvg) / 2048;
    w -= ((((INT32)IC->Gain * (INT32)IC->HRCompCurrent * 20070L) >> 15) * (INT32)(PV->HRAvg >> AVG)) >> 11;


/************************************************************************************/
    
    {
        dw = w + IC->Offset;
        if(dw < 0)dw = 0;
        if(dw > 2047)dw = 2047;

/******* INPUT MILLIVOLTS CALCULATION ***********************************************/
        //ADC = Vin * 750 * (IC->Gain / 256) * (1024 / 3000mV)
        //mV = (256 * 3000 * ADC) / (750 * 1024 * IC->Gain)) = ADC / IC->Gain
        ExtFloat x1;
        if(x1.m = ((UINT32)dw) << 20){
            x1.e = 138;
            while (x1.m < 0x80000000){
                x1.m <<=1;
                x1.e--;
            }
        }
        ExtFloatDivByUInt(x1, IC->Gain);

/******* Resistance calculation if resistive sensor *********************************/
        //R=mV/Current=mV / ((1.225V * IC->Current) / (1600 * 256))
        if(IC->Type==2){
            const ExtFloat rcc = {
                0xA72F0539,   //1.6*256/1.225 32 bit mantissa
                127+8        //1.6*256/1.225 exponent
            };
            ExtFloatMul(x1, rcc);
            UINT32 Current;
            if(IC->InputInv){
                Current = IC->CurrentA;         //divide by current A if channel A selected as positive input
                if(!IC->CBandA) x1.e -=4;       //divide by 16 if higher current band on channel A
            }
            else{
                Current = IC->CurrentB;         //divide by current B if channel B selected as positive input
                if(!IC->CBandB) x1.e =-4;       //divide by 16 if higher current band on channel B
            }
            if(Current == 0) Current = 1;
            ExtFloatDivByUInt(x1, Current);
        }
        SFLOAT CX = {
            {
                x1.m >> 8,
                x1.e,
                0
            }
        };
        PV->CPolyX = CX.f;
        
// >>> At this point in x1 we have millivolts if thermocouple sensor, or ohms if PTC/NTC sensor. <<<

/******* TEMPERATURE POLYNOMIAL CALCULATION *****************************************************/
        //T = C0 + C1 * X + c2 * X^2 + C3 * X^3 + ... + C9 * X^9

        //LATBbits.LATB7 = 0;

        int n; //current polynomial power
        ExtFloat xn = x1;
        ExtFloat PSum;
        ExtFloat NSum;

        //Load positive or negative sum with the first polynomial coefficient depending on it's sign
        float2ExtFloat(PSum, IC->TPoly[0]);
        if(((SFLOAT)IC->TPoly[0]).s){
            NSum = PSum;
            PSum.m = 0;
            PSum.e = 0;
        }

        for(n = 1; n < 10; n++){
            ExtFloat CSum, cn;

            float2ExtFloat(cn, IC->TPoly[n]);

            //get positive or negative sum depending on current coefficient sign
            if(((SFLOAT)IC->TPoly[n]).s){
                CSum = NSum;
            }
            else{
                CSum = PSum;
            }

            ExtFloatMul(cn, xn);

            ExtFloatAdd(CSum, cn);

            //store in positive or negative sum depending on current coefficient
            if(((SFLOAT)IC->TPoly[n]).s){
                NSum = CSum;
            }
            else{
                PSum = CSum;
            }

            //don't calculate next argument power if the end is reached
            if(n >= 9) break;

            //calculate next polynomial argument power
            ExtFloatMul(xn, x1);
        }

        //calculate (PSum - NSum) * 2 in order to get integer temperature * 2
        dw=0;
        if(PSum.e >= NSum.e){
            NSum.m >>= min(PSum.e - NSum.e, 32);
            if(PSum.m > NSum.m){
                if(PSum.e >= 125 + 32){
                    dw=1023;
                }
                else{
                    PSum.m -= NSum.m;
                    dw = ((UINT64)PSum.m << (PSum.e - 125)) >> 32;
                    if(dw > 1023)dw = 1023;
                }
            }
        }

        //Add room temperature if thermocouple
        if(IC->Type == 1) dw += CRTemp;
        if(dw > 1023)dw = 1023;

        PV->CTemp[0] = dw;
        //LATBbits.LATB7 = 1;

    }
    
// >>> At this point in CTemp[0] we have temeprature in degrees Celsius, multiplied by 2. <<<    

    if(PV->Starting || PV->NoHeaterCnt){
        PV->Starting = 0;
        i = (1 << ADCAVG);
        while(i--){
            PV->TBuff[i] = PV->CTemp[0];
            PV->SlopeBuff[i] = PV->CTemp[0];
        }
        PV->TAvgP[0] = PV->CTemp[0];
        PV->TAvgP[1] = PV->CTemp[0];
        PV->TAvg=PV->CTemp[0];
        i = AVG;
        while(i--)PV->TAvg += PV->TAvg;
        PV->TAvgF[0] = PV->TAvg;
        PV->TAvgF[1] = PV->TAvg;
        PV->TSlope = 0;
        PV->TBPos = 0;
        PV->SBPos = 0;
    }

    //TAvg = averaged temperature
    PV->TAvg -= PV->TBuff[PV->TBPos];
    PV->TAvg += PV->CTemp[0];

    //TBuff is array with most recent temperatures, used for TAvg calculation
    PV->TBuff[PV->TBPos] = PV->CTemp[0];
    PV->TBPos++;
    PV->TBPos &= (1 << AVG) - 1;

    //TAvgF = software RC filtered temperature
    PV->TAvgF[1] = PV->TAvgF[0];
    PV->TAvgF[0] -= PV->TAvgF[0] >> AVG;
    PV->TAvgF[0] += PV->CTemp[0];

    //SlopeBuff is array with most recent averaged temperatures, used for TSlope calculation
    PV->SlopeBuff[PV->SBPos] = PV->TAvg;
    PV->SBPos++;
    PV->SBPos &= (1 << AVG) - 1;

    //TSlope is current temperature slope, used with DGain to calculate current predicted temperature for PI controller
    PV->TSlope -= intshr(PV->TSlope, 2);
    PV->TSlope += PV->SlopeBuff[(PV->SBPos - 1) & ((1 << AVG) - 1)];
    PV->TSlope -= PV->SlopeBuff[PV->SBPos];
    
    dw = ((INT32)IC->PID_DGain) * intshr(PV->TSlope, 2);
    dw = intshr(dw, AVG + 2);
    
    //TAvgP is array with current end previous temperature for PI controller, TAvgP=TAvgF + (TSlope * DGain) / 4
    PV->TAvgP[1] = PV->TAvgP[0];
    PV->TAvgP[0] = (PV->TAvgF[0] >> AVG);
    PV->TAvgP[0] += dw;
    if(PV->TAvgP[0] < 0) PV->TAvgP[0] = 0;
    if(PV->TAvgP[0] > 2047) PV->TAvgP[0] = 2047;

    if(PV->DestinationReached == 0 && WSL > 0){
        if(!PV->NoHeater && !PV->NoSensor && !PV->Starting && !PV->ShortCircuit){
            w = CTTemp << 2;
            if( ((PV->TAvgP[0] >= w) && (PV->TAvgP[1] < w)) || ((PV->CTemp[0] >= w) && (PV->CTemp[1] < w)) ){
                //Shut off the power when destination is reached in order to calculate waveshaping shape.
                PV->WSDelta[0].cnt = WSL - 1;
                PV->KeepOff = WSL + 1; //(1 << AVG) + 1;
                PV->DestinationReached = 1;
            }
        }
        
        if(PV->DestinationReached == 0){
            w = PV->TAvgF[0] >> AVG;
            w -= PV->WSTemp;
            if(w <= -99 || w > 99){
                PV->WSTemp += w;//PV->TAvgF[0] >> AVG;
                PV->WSDelta[0].cnt = WSL - 1;
                PV->KeepOff = WSL + 1; //(1 << AVG) + 1;
            }            
        }
        
        if(PV->KeepOff && (PV->NoHeater || PV->ShortCircuit || PV->NoSensor)) PV->KeepOff = 0;
    }
    
    
    //Delta is array with current and previous difference between set and current TAvgP, multiplied by 8
    PV->Delta[1] = PV->Delta[0];
    PV->Delta[0] = CTTemp << 2;
    PV->Delta[0] -= PV->TAvgP[0];
    if(PV->Delta[0] > 511) PV->Delta[0] = 511;
    if(PV->Delta[0] < -511) PV->Delta[0] = -511;
    PV->Delta[0] <<= 5;
    
    
    PV->PIDDutyI += PV->Delta[0] * (int)IC->PID_KI;        
    if((PV->PIDDutyP = PV->Delta[0] * (int)IC->PID_KP) >= 0){
        dw = 0x00FFFFFF;
        if(PV->PIDDutyP > dw) PV->PIDDutyP = dw;
        dw -= PV->PIDDutyP;
        if(PV->PIDDutyI > dw || (PV->DestinationReached == 0 && PV->Delta[0] > (100<<6) )) PV->PIDDutyI = dw;        
    }
    else{
        if(PV->PIDDutyI < 0) PV->PIDDutyI = 0; 
        dw = -(PV->Delta[0]) * (int)IC->PID_OVSGain;
        if(dw > 4095) dw = 4095;
        dw <<= 12;
        dw = 0x00FFFFFF - dw;
        if(PV->PIDDutyI > dw) PV->PIDDutyI = dw;
    }
    pdt = PV->PIDDutyP + PV->PIDDutyI;
    if(pdt < 0) pdt = 0;
    if((IC->Type == 0) || (IC->Type == 255) || PV->NoSensor) pdt = 0;
    
    PV->PIDDutyFull = pdt; //normalized duty

/**** RECALCULATE DUTY FOR REAL VS RATED POWER*********************************/
    //Duty=Duty * rated power / peak power
    pdt += 0x7FL;
    pdt >>= 8;
    if(PV->HP){        
        dw = PV->HPAvg >> AVG;
        if(PV->Power < 1 && dw >= ((INT32)IC->PID_PMax << 1)) PV->Power = 1;
        if(PV->Power < 2 && dw >= ((INT32)IC->PID_PMax << 2)) PV->Power = 2;
        pdt *= (INT32)IC->PID_PMax;
        pdt /= dw;
    }
/******************************************************************************/

/**** RECALCULATE DUTY FOR MAX 6.0A RMS CURRENT******************************/
    dw=0xFA00L;
    if(PV->HI){
        dw = PV->HIAvg >> AVG;
        if(dw > 192){
            dw = (INT32)(65535 * 192) / dw;
        }
        else{
            dw=0xFA00;
        }
    }
    if(pdt > dw) pdt = dw;
/******************************************************************************/

    pdt <<= 8;
    if(PV->NoHeater) pdt=0x28F5C; //PWM = once per 2 seconds in order to detect heater resistance on open heater
    if(PV->ShortCircuit) pdt=0x10624; //PWM = once per 5 seconds in order to detect heater resistance on short circuit

    PV->PIDDuty = pdt;

}

#undef _PID_C
