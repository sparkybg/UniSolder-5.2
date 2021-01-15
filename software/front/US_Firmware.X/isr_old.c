#define _ISR_C
#include <GenericTypeDefs.h>
#include "typedefs.h"
#include "mcu_pic18f4550.h"
#include "isr.h"
#include "mul.h"
#include "main.h"
#include "disp.h"
#include "heater.h"
#include "iron.h"
#include "PID.h"

volatile UINT8 ISRStep=0;
volatile UINT8 ADCStep=0;
volatile UINT8 ISRTicks=1;                 //increased on every mains period

volatile ADCDataS ADCData;

volatile UINT8 I2CStep=0;
volatile I2CDataS I2CData;

volatile SUINT32 PWM;

volatile UINT8 PHEATER;

volatile SUINT16 CTemp;
volatile SUINT16 CRTemp;
volatile SUINT16 CTTemp;

volatile SUINT16 TAvg;
volatile SUINT16 TAvgF;
volatile SUINT16 TBuff[8];
volatile UINT8 TBPos=0;
volatile SUINT16 TSlope;
volatile SUINT16 SlopeBuff[8];
volatile UINT8 SBPos=0;
volatile SUINT16 TAvgS;
volatile SUINT16 Delta[2];

volatile UINT8 Starting = 1;

//volatile static UINT16 ADCData[5]={0,0,0,0,0};


void interrupt ISRHigh(){
    static UINT8 b;
    static SUINT16 w;
    if(PIR1bits.TMR1IF){
        ISRStep=0;
        TMR1H=T_PER.ui8[1];
        TMR1L=T_PER.ui8[0];
        PIR1bits.TMR1IF=0;
    }
    if(PIR2bits.CMIF && PIE2bits.CMIE){
        if(!CMCONbits.C1OUT){
            ISRStep=0;
            TMR1H=T_PER.ui8[1];
            TMR1L=T_PER.ui8[0];
            COMPREF=3;
        }
        else{
            COMPREF=2;
        }
        b=CMCON;
        PIR2bits.CMIF=0;
    }
    switch(ISRStep){
        case 0:
            PIE2bits.CMIE=0;
            ADCON1bits.VCFG=0b00; //ADC reference = Vdd
            TMR0H=(~_timer_us(100))>>8;
            TMR0L=(~_timer_us(100)) & 0x00FF;
            T0CONbits.TMR0ON=1;
            break;
        case 1:
            INTCONbits.TMR0IF=0;
            T0CONbits.TMR0ON=0;
            _readADC(ADCH_ID);
            break;
        case 2:
            ADCData.VID.ui16=ADCRESULT;
            PIR1bits.ADIF=0;
            ADCON1bits.VCFG=0b01; //ADC reference = Vref
            TMR0H=(~_timer_us(100))>>8;
            TMR0L=(~_timer_us(100)) & 0x00FF;
            T0CONbits.TMR0ON=1;
            break;
        case 3:
            INTCONbits.TMR0IF=0;
            T0CONbits.TMR0ON=0;
            _readADC(ADCH_RT);
            break;
        case 4:
            ADCData.VRT.ui16-=(ADCData.VRT.ui16>>2);
            ADCData.VRT.ui16+=ADCRESULT;
            PIR1bits.ADIF=0;
            TMR0H=(~_timer_us(800))>>8;
            TMR0L=(~_timer_us(800)) & 0x00FF;
            T0CONbits.TMR0ON=1;
            HEATER=0;
            break;
        case 5:
            //LATB3=0;
            INTCONbits.TMR0IF=0;
            T0CONbits.TMR0ON=0;
            _readADC(ADCH_TEMP);
            break;
        case 6:
            //LATB3=1;
            ADCData.VTEMP[ADCStep].ui16=ADCRESULT;
            PIR1bits.ADIF=0;

            if(ADCStep & 1){
                PIR1bits.CCP1IF=1; //CCP1 interrupt is used to run PID from lower priority ISR
            }
            else{
                PWM.ui32+=PIDDuty.ui32;
                PHEATER=(PWM.ui8[3]!=0);
                PWM.ui8[3]=0;
            }

            ADCStep++;
            ADCStep&=3;
            if((ADCStep & 2)==0){   //offset or TC measurement
                CBAND=1;
                I2CData.Current.ui16=0;
                I2CData.Offset.ui16=0;
            }
            if(ADCStep & 1){    //heater resistance measurement
                CHSEL=0;
                I2CData.Gain.ui16=HR_GAIN;
                if(ADCStep & 2){
                    CBAND=HR_CBAND;
                    I2CData.Current.ui16=HR_CURRENT;
                    I2CData.Offset.ui16=ADCData.VTEMP[1].ui16; //exclude offset from measurement
                }
            }else   //TC or resistive sensor measurement
            {
                CHSEL=IronPars.Channel;
                I2CData.Gain.ui16=IronPars.Gain.ui16;
                if(ADCStep & 2){
                    CBAND=IronPars.CBand;
                    I2CData.Current.ui16=IronPars.Current.ui16;
                    I2CData.Offset.ui16=ADCData.VTEMP[0].ui16+IronPars.Offset.ui16;
                }
            }
            _I2CStart;
            HEATER=PHEATER;
            _showChar(1);
            TMR0H=C_PER.i8[1];
            TMR0L=C_PER.i8[0];
            T0CONbits.TMR0ON=1;
            break;
        case 7:
            INTCONbits.TMR0IF=0;
            T0CONbits.TMR0ON=0;
            _showChar(2);
            TMR0H=C_PER.i8[1];
            TMR0L=C_PER.i8[0];
            T0CONbits.TMR0ON=1;
            break;
        case 8:
            INTCONbits.TMR0IF=0;
            T0CONbits.TMR0ON=0;
            _showChar(0);
            _readADC(ADCH_VIN);
            break;
        case 9:
            ADCData.VIN.ui16=ADCRESULT;
            PIR1bits.ADIF=0;
            b=CMCON;
            PIR2bits.CMIF=0;
            PIE2bits.CMIE=1;
            _showChar(3);
            TMR0H=C_PER.i8[1];
            TMR0L=C_PER.i8[0];
            T0CONbits.TMR0ON=1;
            break;
        case 10:
            _showChar(0);
            INTCONbits.TMR0IF=0;
            T0CONbits.TMR0ON=0;
            break;
    }
    //if(PIR1bits.ADIF){
      //  ADRES=ADRES;
        //PIR1bits.ADIF=0;
    //}
    if(ISRStep<255)ISRStep++;
}


void interrupt low_priority ISRlow(){
    volatile static SUINT16 w;
    volatile static SUINT32 dw;
    volatile static SUINT32 pdt;
    //LATB3=!LATB3;
    if(PIR1bits.SSPIF){
        switch(I2CStep){
            //Set current pot position
            case 0:
                SSPCON2bits.SEN=1;
                break;
            case 1:
                SSPBUF=CPOT;
                break;
            case 2:
                SSPBUF=I2CData.Current.ui8[1] & 1;
                break;
            case 3:
                SSPBUF=I2CData.Current.ui8[0];
                break;
            case 4:
                SSPCON2bits.PEN=1;
                break;

            //Set gain pot position
            case 5:
                SSPCON2bits.SEN=1;
                break;
            case 6:
                SSPBUF=GAINPOT;
                break;
            case 7:
                SSPBUF=I2CData.Gain.ui8[1] & 1;
                break;
            case 8:
                SSPBUF=I2CData.Gain.ui8[0];
                break;
            case 9:
                SSPCON2bits.PEN=1;
                break;

            //Set offset
            case 10:
                SSPCON2bits.SEN=1;
                break;
            case 11:
                SSPBUF=OFFADC;
                break;
            case 12:
                SSPBUF=0b01011000;
                break;
            case 13:
                w.ui16=I2CData.Offset.ui16;
                w.ui16<<=6;
                SSPBUF=w.ui8[1];
                break;
            case 14:
                w.ui16=I2CData.Offset.ui16;
                w.ui16<<=6;
                SSPBUF=w.ui8[0];
                break;
            case 15:
                SSPCON2bits.PEN=1;
                break;
            default:
                I2CStep--;
                break;
        }
        I2CStep++;
        PIR1bits.SSPIF=0;
    }

    if(PIR1bits.CCP1IF){
        LATB3=0;
        PIR1bits.CCP1IF=0;
        
/**** GET ROOM TEMPERATURE **********************************************************/
        GIE=0;
        w.ui16=ADCData.VRT.ui16;
        GIE=1;
        w.i16>>=2;
        w.i16-=125;
        mul16s8u(dw,w,182);
        CRTemp.i16=dw.mi16;
/************************************************************************************/

/**** GET AND NORMALISE IRON TEMPRATURE *********************************************/
        if(IronPars.Type){
            GIE=0;
            w.ui16=ADCData.VTEMP[2].ui16;
            GIE=1;
        }
        else
        {
            GIE=0;
            w.ui16=ADCData.VTEMP[0].ui16;
            GIE=1;
        }
        mul16s16u(dw,IronPars.SoftGain,w);
        dw.hi24>>=2;
        dw.mi16+=IronPars.SoftOffset.i16;
        if(IronPars.Type==0)dw.mi16+=CRTemp.i16;
        if(dw.mi16<0)dw.mi16=0;
        CTemp.ui16=dw.mi16;
/************************************************************************************/

        if(Starting){
            TAvg.ui16=0;
            for(w.i8[0]=0;w.ui8[0]<4;w.ui8[0]++){
                TAvg.ui16+=CTemp.ui16;
                TBuff[w.ui8[0]].ui16=CTemp.ui16;
            }
            TAvgF.ui16=TAvg.ui16;
            TSlope.ui16=TAvg.ui16>>2;
            for(w.i8[0]=0;w.ui8[0]<4;w.ui8[0]++){
                SlopeBuff[w.ui8[0]].ui16=TSlope.ui16;
            }
            TSlope.ui16=0;
            Starting=0;
        }

        TAvg.ui16-=TBuff[TBPos].ui16;
        TAvg.ui16+=CTemp.ui16;
        TBuff[TBPos].ui16=CTemp.ui16;
        TBPos++;
        TBPos&=3;

        TAvgF.ui16-=TAvgF.ui16>>2;
        TAvgF.ui16+=CTemp.ui16;

        SlopeBuff[SBPos].ui16=TAvg.ui16>>2;
        SBPos++;
        SBPos&=3;

        w.i16=TSlope.i16;
        if(w.i16<0)w.i16=-w.i16;
        w.ui16>>=2;
        if(TSlope.i16<0)w.i16=-w.i16;
        TSlope.i16-=w.i16;
        TSlope.i16-=SlopeBuff[(SBPos-1)&3].i16;
        TSlope.i16+=SlopeBuff[SBPos].i16;

        w.i16=TSlope.i16;
        if(w.i16<0)w.i16=-w.i16;
        w.ui16>>=2;
        mul16u8u(dw,w,IronPars.PID_DGain);
        dw.lui24>>=2;
        if(TSlope.i16<0)dw.i16[0]=-dw.i16[0];

        Delta[1].i16=Delta[0].i16;
        Delta[0].i16=CTTemp.i16;
        Delta[0].i16-=(TAvgF.i16>>2);
        Delta[0].i16-=dw.i16[0];
        Delta[0].i16<<=2;

        pdt.ui32=PIDDuty.ui32;

        mul16s16u(dw, Delta[0], IronPars.PID_K1);
        pdt.i32+=dw.i32;
        mul16s16u(dw, Delta[1], IronPars.PID_K2);
        pdt.i32-=dw.i32;

        if(pdt.i32<0){
            pdt.i32=0;
        }
        else{
            if(pdt.ui32>0x00FFFFFF){
                pdt.ui32=0x00FFFFFF;
            }
            w.i16=-(Delta[0].i16>>2);
            if(w.i16<=0){
                if(w.i16<-200)pdt.ui32=0x00FFFFFF;
            }
            else{
                w.i16<<=4;
                if(w.i16>255)w.ui8[0]=255;
                w.ui8[0]=~w.ui8[0];
                if(pdt.ui8[2]>w.ui8[0]){
                    pdt.ui8[2]=w.ui8[0];
                    pdt.ui16[0]=0xFFFF;
                }
            }
        }
        GIE=0;
        PIDDuty.ui32=pdt.ui32;
        GIE=1;
/*                if(PWM.i32<0){
                    PWM.i32=0;
                    PWMCNT.lui24=0;
                }
                else{
                    SUINT16 w;
                    if(PWM.ui32>0x00FFFFFF){
                        PWM.ui32=0x00FFFFFF;
                    }
                    w.i16=FPAVGT.i16-PTT.i16;
                    if(w.i16<0){
                        if(w.i16<-200)PWM.ui32=0x00FFFFFF;
                    }
                    else{
                        w.i16<<=4;
                        if(w.i16>255)w.ui8[0]=255;
                        w.ui8[0]=~w.ui8[0];
                        if(PWM.ui8[2]>w.ui8[0]){
                            PWM.ui8[2]=w.ui8[0];
                            PWM.ui16[0]=0xFFFF;
                        }
                        w.i16=FPAVGT.i16-PTT.i16;
                    }
                    if(CTTemp==0)PWM.ui32=0;
                    PWMCNT.ui32+=PWM.ui32;
                    PHEATER=(PWMCNT.ui8[3]!=0);
                    if(w.i16>40)PHEATER=0;
                    if(CTemp>460)PHEATER=0;
                }
                PWMCNT.ui8[3]=0;
*/


/*                    SUINT16 w;
                    if(PWM.ui32>0x00FFFFFF){
                        PWM.ui32=0x00FFFFFF;
                    }
                    w.i16=FPAVGT.i16-PTT.i16;
                    if(w.i16<0){
                        if(w.i16<-200)PWM.ui32=0x00FFFFFF;
                    }
                    else{
                        w.i16<<=4;
                        if(w.i16>255)w.ui8[0]=255;
                        w.ui8[0]=~w.ui8[0];
                        if(PWM.ui8[2]>w.ui8[0]){
                            PWM.ui8[2]=w.ui8[0];
                            PWM.ui16[0]=0xFFFF;
                        }
                        w.i16=FPAVGT.i16-PTT.i16;
                    }
                    if(CTTemp==0)PWM.ui32=0;
                    PWMCNT.ui32+=PWM.ui32;
                    PHEATER=(PWMCNT.ui8[3]!=0);
                    if(w.i16>40)PHEATER=0;
                    if(CTemp>460)PHEATER=0;
*/
        






/*                    FPAVGT.i16=PAVGT.i16+dw.i16[0];
                    Delta[1].i16=Delta[0].i16;
                    Delta[0].i16=(PTT.i16-FPAVGT.i16);
                    if(Delta[0].i16<0)Delta[0].i16=-Delta[0].i16;
                    Delta[0].i16<<=2;
                    if(PTT.i16<FPAVGT.i16)Delta[0].i16=-Delta[0].i16;*/






        LATB3=1;
    }

}

#undef _ISR_C

/*{
    static SUINT32 dw;
    static SUINT16 w;
    static SUINT16 PIDK;
    static UINT8 PIDDGAIN;
    static UINT8 PIDTIME;

    if(PIR2bits.CMIF){
        PIR2bits.CMIF=0;
        if(MAINS)return;
        ISRStep=0;
    }

    switch(ISRStep){
        case 0: //wait 320us to start ADC conversion
            HEATER=0;
            TMR0H=0xFF;
            TMR0L=235;
            T0CONbits.TMR0ON=1;
            break;
        case 1: //start ADC conversion of first channel (AN10)
            INTCONbits.TMR0IF=0;
            T0CONbits.TMR0ON=0;
            ADCON0=0b00110001;
            ADCON0bits.GO_DONE=1;
            break;
        case 2: //start ADC conversion of second channel (AN12)
            PIR1bits.ADIF=0;
            if(ISRTicks & 1){
                ADCData[1]=ADRES;
                //ADBuff[1].byte.LB=ADRESL;
                //ADBuff[1].byte.HB=ADRESH & 0b00000011;
            }
            else{
                ADCData[3]=ADRES;
                //ADBuff[3].byte.LB=ADRESL;
                //ADBuff[3].byte.HB=ADRESH & 0b00000011;
            }
            ADCON0=0b00101001;
            ADCON0bits.GO_DONE=1;
            break;
        case 3: //display 1st character and do PID 1/3 of a PID;
            HEATER=(PHEATER!=0);
            PIR1bits.ADIF=0;
            ADBuff[((ISRTicks & 1)<<1)].byte.LB=ADRESL;
            ADBuff[((ISRTicks & 1)<<1)].byte.HB=ADRESH & 0b00000011;
            if(ISRTicks & 1){
                ADBuff[0].byte.LB=ADRESL;
                ADBuff[0].byte.HB=ADRESH & 0b00000011;
                VREFCON0=0b10110000; //FVR Enabled, 4.096V
            }
            else{
                ADBuff[2].byte.LB=ADRESL;
                ADBuff[2].byte.HB=ADRESH & 0b00000011;
                VREFCON0=0b10100000; //FVR Enabled, 2.048V
            }
            ADCON0bits.ADON=0;
            TMR0H=(DispTime.byte.HB);
            TMR0L=(DispTime.byte.LB);
            T0CONbits.TMR0ON=1;
            LATC=DISPLAY[0];
            IND1=0;

            if((ISRTicks&1)==0){
            //1/4 PID
                IronType=0;
                ADVal.Val=ADBuff[2].Val;  //HAKKO T12 on channel 1
                PIDTIME=PID1_TIME;
                PIDDGAIN=PID1_DGAIN;
                if((ADBuff[1].Val<1020)||(ADBuff[3].Val<1020)){
                    IronType=1;
                    //ADVal.Val=ADBuff[1].Val; //JBC C245 on channel 2
                    ADVal.Val=ADBuff[3].Val; //HAKKO Clone on channel 2
                    PIDTIME=PID2_TIME;
                    PIDDGAIN=PID2_DGAIN;
                }
                ADVal.Val+=44; //Add 22 degrees for room temperature
                if(!Started){
                    Started=1;
                    for(TBPos=0;TBPos<(1<<ADC_AVG);TBPos++){
                        TempBuff[TBPos]=ADVal.Val;
                        TempAVG.ui16+=ADVal.Val;
                        TempAVG2.ui16+=ADVal.Val;
                    }
                    TBPos=0;
                    SlopeBuff[0].ui16=TempAVG.ui16>>ADC_AVG;
                    for(SBPos=1;SBPos<(1<<SLOPE_SIZE);SBPos++){
                        SlopeBuff[SBPos].ui16=SlopeBuff[0].ui16;
                    }
                    SBPos=0;
                }
                TempAVG.ui16-=TempBuff[TBPos];
                TempAVG.ui16+=ADVal.Val;
                TempBuff[TBPos]=ADVal.Val;
                TempAVG2.ui16-=(TempAVG2.ui16>>ADC_AVG);
                TempAVG2.ui16+=ADVal.Val;
                TBPos++;
                TBPos&=((1<<ADC_AVG)-1);
                SlopeBuff[SBPos].ui16=TempAVG.ui16>>ADC_AVG;
                SBPos++;
                SBPos&=((1<<SLOPE_SIZE)-1);
                if((ISRTicks&PIDTIME)==0){
                    CTemp=TempAVG.ui16>>(ADC_AVG+1);
                    w.i16=TSlope.i16;
                    if(w.i16<0)w.i16=-w.i16;
                    w.i16>>=2;
                    if(TSlope.i16<0)w.i16=-w.i16;
                    TSlope.i16-=w.i16;
                    TSlope.i16+=SlopeBuff[(SBPos-1)&((1<<SLOPE_SIZE)-1)].i16;
                    TSlope.i16-=SlopeBuff[SBPos].i16;
                    //PAVGT.ui16=TempAVG.ui16>>ADC_AVG;
                    PAVGT.ui16=TempAVG2.ui16>>ADC_AVG;
                    PTT.ui16=CTTemp;
                    PTT.ui16<<=2;

                    w.i16=TSlope.i16;
                    if(w.i16<0)w.i16=-w.i16;
                    w.i16>>=2;
                    dw.ui16[1]=0;
                    dw.ui16[0]=w.ui8[0]*PIDDGAIN;
                    dw.mui16+=w.ui8[1]*PIDDGAIN;
                    dw.lui24>>=2;
                    if(TSlope.i16<0)dw.i16[0]=-dw.i16[0];

                    FPAVGT.i16=PAVGT.i16+dw.i16[0];
                    Delta[1].i16=Delta[0].i16;
                    Delta[0].i16=(PTT.i16-FPAVGT.i16);
                    if(Delta[0].i16<0)Delta[0].i16=-Delta[0].i16;
                    Delta[0].i16<<=2;
                    if(PTT.i16<FPAVGT.i16)Delta[0].i16=-Delta[0].i16;
                }
            }
            break;
        case 4: //display 2nd character
            INTCONbits.T0IF=0;
            TMR0H=(DispTime.byte.HB);
            TMR0L=(DispTime.byte.LB);
            LATC=DISPLAY[1];
            IND1=1;
            IND2=0;
            // 2/4 PID
            if((ISRTicks&1)==0){
                switch(IronType){
                    case 0:
                        PIDK.ui16=PID1_K1;
                        break;
                    case 1:
                        PIDK.ui16=PID2_K1;
                        break;
                }
                if((ISRTicks&PIDTIME)==0){
                    mul16s16u(dw, Delta[0], PIDK);
                    PWM.i32+=dw.i32;
                }
            }
            break;
        case 5: //display 3rd character
            INTCONbits.T0IF=0;
            TMR0H=(DispTime.byte.HB);
            TMR0L=(DispTime.byte.LB);
            LATC=DISPLAY[2];
            IND1=1;
            IND2=1;
            IND3=0;
            // 3/4 PID
            if((ISRTicks&1)==0){
                switch(IronType){
                    case 0:
                        PIDK.ui16=PID1_K2;
                        break;
                    case 1:
                        PIDK.ui16=PID2_K2;
                        break;
                }
                if((ISRTicks&PIDTIME)==0){
                    mul16s16u(dw,Delta[1],PIDK);
                    PWM.i32-=dw.i32;
                }
            }
            break;
        case 6: //turn display off
            INTCONbits.T0IF=0;
            T0CONbits.TMR0ON=0;
            LATC=1;
            IND2=1;
            IND3=1;
            if(!MAINS){
                PowerLost=1; //POWER LOST - SAVE DATA TO EEPROM
                LATC=2;
                IND2=0;
                IND3=0;
                HEATER=0;
            }
            // 4/4 PID
            if((ISRTicks&1)==0){
                PHEATER=0;
                if(PWM.i32<0){
                    PWM.i32=0;
                    PWMCNT.lui24=0;
                }
                else{
                    SUINT16 w;
                    if(PWM.ui32>0x00FFFFFF){
                        PWM.ui32=0x00FFFFFF;
                    }
                    w.i16=FPAVGT.i16-PTT.i16;
                    if(w.i16<0){
                        if(w.i16<-200)PWM.ui32=0x00FFFFFF;
                    }
                    else{
                        w.i16<<=4;
                        if(w.i16>255)w.ui8[0]=255;
                        w.ui8[0]=~w.ui8[0];
                        if(PWM.ui8[2]>w.ui8[0]){
                            PWM.ui8[2]=w.ui8[0];
                            PWM.ui16[0]=0xFFFF;
                        }
                        w.i16=FPAVGT.i16-PTT.i16;
                    }
                    if(CTTemp==0)PWM.ui32=0;
                    PWMCNT.ui32+=PWM.ui32;
                    PHEATER=(PWMCNT.ui8[3]!=0);
                    if(w.i16>40)PHEATER=0;
                    if(CTemp>460)PHEATER=0;
                }
                PWMCNT.ui8[3]=0;
            }
            ISRTicks++;
            break;
        default:
            LATC=8;
            IND2=0;
            IND1=0;
            HEATER=0;
            break;
    }
    ISRStep++;
}*/

