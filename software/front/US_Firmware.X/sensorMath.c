#define _SENSORMATH_C
#include <stdlib.h>
#include "sensorMath.h"
#include "iron.h"
#include "PID.h"
#include "main.h"

INT32 GetSensorTemperature(UINT16 input, t_SensorConfig * SC){
    INT32 dw = input + SC->Offset;
    if(dw < 0)dw = 0;
    if(dw > 2047)dw = 2047;

///******* INPUT MILLIVOLTS CALCULATION ***********************************************/
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
    ExtFloatDivByUInt(x1, SC->Gain);

///******* Resistance calculation if resistive sensor *********************************/
    //R=mV/Current=mV / ((1.225V * IC->Current) / (1600 * 256))
    if(SC->Type == 2){
        const ExtFloat rcc = {
            0xA72F0539,   //1.6*256/1.225 32 bit mantissa
            127+8        //1.6*256/1.225 exponent
        };
        ExtFloatMul(x1, rcc);
        UINT32 current;
        int cBand;
        if(SC->InputInv){
            current = SC->CurrentA;
            cBand = SC->CBandA;
        }
        else{
            current = SC->CurrentB;
            cBand = SC->CBandB;                
        }
        if(!cBand) x1.e -=4;       //divide by 16 if higher current band on channel A
        if(current == 0) current = 1;
        ExtFloatDivByUInt(x1, current);
    }
// >>> At this point in x1 we have millivolts if thermocouple sensor, or ohms if PTC/NTC sensor. <<<

/******* TEMPERATURE POLYNOMIAL CALCULATION *****************************************************/
    //T = C0 + C1 * X + c2 * X^2 + C3 * X^3 + ... + C9 * X^9
    {
        ExtFloat PSum;
        ExtFloat NSum;

        {
            int n; //current polynomial power
            ExtFloat xn = x1;
            SFLOAT cp;

            cp.f = SC->TPoly[0];
            //Load positive or negative sum with the first polynomial coefficient depending on it's sign
            float2ExtFloat(PSum, cp.f);
            if(cp.s){
                NSum = PSum;
                PSum.m = 0;
                PSum.e = 0;
            }

            for(n = 1; n < 10; n++){
                ExtFloat CSum, cn;
                cp.f = SC->TPoly[n];

                float2ExtFloat(cn, cp.f);

                //get positive or negative sum depending on current coefficient sign
                if(cp.s){
                    CSum = NSum;
                }
                else{
                    CSum = PSum;
                }

                ExtFloatMul(cn, xn);

                ExtFloatAdd(CSum, cn);

                //store in positive or negative sum depending on current coefficient
                if(cp.s){
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
        }

        //calculate (PSum - NSum) * 2 in order to get integer temperature * 2
        if(PSum.e > NSum.e || (PSum.e == NSum.e && PSum.m >= NSum.m)){
            //positive result
            int s = PSum.e - NSum.e;
            if(s >= 32){
                NSum.m = 0;
            }
            else if(s){
                NSum.m >>= s;
            }
            PSum.m -= NSum.m;
            s = -((PSum.e - 125) - 32);
            if(s <= 0){
                dw = 0x7FFFFFFF;
            }
            else{
                dw = PSum.m >> s;
            }
        }
        else{
            //negative result
            int s = NSum.e - PSum.e;
            if(s >= 32){
                PSum.m = 0;
            }
            else if(s){
                PSum.m >>= s;
            }
            NSum.m -= PSum.m;
            s = -((NSum.e - 125) - 32);
            if(s <= 0){
                dw = 0x80000000;
            }
            else{
                dw = -(INT32)(NSum.m >> s);
            }            
        }
    }

    //Add room temperature if thermocouple
    if(SC->Type == 1){
        int temp = CRTemp;
        if(CJTemp > -273*2) temp = CJTemp;
        if(CRTemp > 0 && dw <= (0x7FFFFFFFU - temp)) dw += temp;
        if(CRTemp < 0 && (UINT32)dw >= (0x80000000U + (-temp))) dw -= temp;
    }

    return dw;
 }   

#define _SENSORMATH_C
