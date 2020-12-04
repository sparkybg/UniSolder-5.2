#define _PIC32MX534F064H_C

#include <xc.h>
// DEVCFG3
// USERID = No Setting
#pragma config FSRSSEL = PRIORITY_7     // SRS Select (SRS Priority 7)
#pragma config FCANIO = OFF             // CAN I/O Pin Select (Alternate CAN I/O)
#pragma config FUSBIDIO = OFF           // USB USID Selection (Controlled by Port Function)
#pragma config FVBUSONIO = OFF          // USB VBUS OFF Selection (Not Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider (2x Divider)
#pragma config UPLLEN = ON              // USB PLL Enable (Enabled)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = XT             // Primary Oscillator Configuration (XT osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_2           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

#include <GenericTypeDefs.h>
#include "PIC32MX564F128H.h"
#include <peripheral/system.h>
#include <peripheral/cmp.h>
#include <peripheral/timer.h>
#include <peripheral/ports.h>
#include <peripheral/adc10.h>
#include <peripheral/dma.h>
#include <peripheral/cvref.h>
#include <peripheral/outcompare.h>
#include <peripheral/incap.h>
#include <peripheral/int.h>

#include "main.h"
#include "isr.h"
#include "OLED.h"

void GetBoardVersion(){
    BoardVersion = 0;
    OLED_DC_3S = 1;
    OLED_DC_PU = 1;
    REV_BC_3S = 0;
    REV_BC_PU = 0;
    _delay_ms(10);
    int i;
    for(i = 0b10101010; i; i >>= 1){
        REV_BC_OUT = (i & 1) ? 1 : 0;
        _delay_ms(1);
        if(REV_BC_IN != OLED_DC_IN) return;
    }
    REV_BC_3S = 1;
    REV_BC_PU = 1;
    OLED_DC_PU = 0;
    OLED_DC_3S = 0;
    _delay_ms(10);
    for(i = 0b10101010; i; i >>= 1){
        OLED_DC = (i & 1) ? 1 : 0;
        _delay_ms(1);
        if(REV_BC_IN != OLED_DC_IN) return;
    }
    BoardVersion = 1;
}


void mcuInit1(){
    INTDisableInterrupts();
    OpenCoreTimer(0xFFFFFFFF);
    SYSTEMConfigWaitStates(80000000);

    CNPUE = 0;
    
    TRISB = 0b1110000000111111;
    TRISC = 0b1001000000000000;
    TRISD = 0b0000000000100000;
    TRISE = 0;
    TRISF = 0;
    TRISG = 0b1000111111;

    ODCB = 0;
    ODCC = 0;
    ODCD = 0;
    ODCE = 0;
    ODCF = 0;
    ODCG = 0;

    LATB = 0b1000000000000000;
    LATC = 0;
    LATD = 0b0000100001010000;
    LATE = 0;
    LATF = 0;
    LATG = 0;
    
    HCH = 0;
    ID_3S = 0;
    ID_OUT = 0;
    HEATER = 0;
    CBANDA = 1;
    CBANDB = 1;
    CHSEL1 = 0;
    CHSEL2 = 1;
    CHPOL = 0;    

    mcuADCStop();
    mcuSPIStop();
    
    GetBoardVersion();    
}

void mcuInit2(){
    OLEDPrintNum816(0, 0, 2, 10);
    OLEDUpdate();
    
    OpenTimer3(T3_ON | T3_IDLE_STOP | T3_GATE_OFF | T3_PS_1_256 | T3_SOURCE_INT, 40);
    OLEDPrintNum816(0, 0, 2, 11);
    OLEDUpdate();
    
    OpenOC1(OC_OFF | OC_IDLE_STOP | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0x20, 0);
    OLEDPrintNum816(0, 0, 2, 12);
    OLEDUpdate();
    
    DmaEnable(1);
    OLEDPrintNum816(0, 0, 2, 13);
    OLEDUpdate();
    
    I2CEnable(I2C4, FALSE);
    OLEDPrintNum816(0, 0, 2, 14);
    
    mcuI2CReset();
    OLEDPrintNum816(0, 0, 2, 15);
    OLEDUpdate();
    
    I2CSetFrequency(I2C4, PER_FREQ, 400000);
    OLEDPrintNum816(0, 0, 2, 16);
    OLEDUpdate();
    
    I2CEnable(I2C4,TRUE);
    OLEDPrintNum816(0, 0, 2, 17);
    OLEDUpdate();

    CVREFOpen(CVREF_ENABLE | CVREF_OUTPUT_DISABLE | CVREF_RANGE_HIGH | CVREF_SOURCE_VREF);
    OLEDPrintNum816(0, 0, 2, 18);
    OLEDUpdate();
    
    COMPREF = 2; //(3*(0.25+2/32))*6 = 5.625V on Vin
    CMP2Open(CMP_STOP_IN_IDLE | CMP_ENABLE | CMP_OUTPUT_DISABLE | CMP_OUTPUT_INVERT | CMP_EVENT_HIGH_TO_LOW | CMP_POS_INPUT_CVREF | CMP2_NEG_INPUT_C2IN_NEG);
    OLEDPrintNum816(0, 0, 2, 19);
    OLEDUpdate();
        
    OLEDPrintNum816(0, 0, 2, 20);
    OLEDUpdate();
    
    OpenTimer1(T1_ON | T1_IDLE_STOP | T1_TMWDIS_OFF | T1_GATE_OFF | T1_PS_1_256 | T1_SYNC_EXT_OFF | T1_SOURCE_INT,0xFFFF);
    ConfigIntTimer1(T1_INT_OFF | T1_INT_PRIOR_7 | T1_INT_SUB_PRIOR_3);
    _delay_ms(100);
    
    OLEDPrintNum816(0, 0, 2, 21);
    OLEDUpdate();
}

void mcuInit3(){
    CloseTimer1();
    OpenTimer1(T1_ON | T1_IDLE_STOP | T1_TMWDIS_OFF | T1_GATE_OFF | T1_PS_1_256 | T1_SYNC_EXT_OFF | T1_SOURCE_INT, T_PER);
    OLEDPrintNum816(0, 0, 2, 22);
    OLEDUpdate();
}

void mcuInit4(){
    CMP2ConfigInt(CMP_INT_ENABLE | CMP_INT_PRIOR_7 | CMP_INT_SUB_PRI_3);
    ConfigIntADC10(ADC_INT_ON | ADC_INT_PRI_7 | ADC_INT_SUB_PRI_3 );
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_7 | T1_INT_SUB_PRIOR_3);
    INTClearFlag(INT_I2C4B);
    INTClearFlag(INT_I2C4M);
    INTClearFlag(INT_I2C4S);
    INTClearFlag(INT_I2C4);
    INTSetVectorPriority(INT_I2C_4_VECTOR, INT_PRIORITY_LEVEL_6);
    INTSetVectorSubPriority(INT_I2C_4_VECTOR, INT_SUB_PRIORITY_LEVEL_3);
    INTEnable(INT_I2C4B,INT_ENABLED);
    INTEnable(INT_I2C4M,INT_ENABLED);
    INTEnable(INT_I2C4S,INT_ENABLED);
    INTEnable(INT_I2C4,INT_ENABLED);
    INTClearFlag(INT_OC2);
    INTSetVectorPriority(_OUTPUT_COMPARE_2_VECTOR, INT_PRIORITY_LEVEL_5);
    INTSetVectorSubPriority(_OUTPUT_COMPARE_2_VECTOR, INT_SUB_PRIORITY_LEVEL_3);
    INTEnable(INT_OC2,INT_ENABLED);
    ConfigIntCapture1(IC_INT_ON | IC_INT_PRIOR_4 | IC_INT_SUB_PRIOR_3);
    ConfigIntCapture3(IC_INT_ON | IC_INT_PRIOR_4 | IC_INT_SUB_PRIOR_3);    
    OLEDPrintNum816(0, 0, 2, 41);
    OLEDUpdate();

    mcuInitISRTimer();
    
    OpenCapture1(IC_ON | IC_CAP_32BIT | IC_INT_1CAPTURE | IC_EVERY_EDGE);
    OpenCapture3(IC_ON | IC_CAP_32BIT | IC_INT_1CAPTURE | IC_EVERY_EDGE);
    OLEDPrintNum816(0, 0, 2, 42);
    OLEDUpdate();
    
    INTEnableSystemMultiVectoredInt();
    OLEDPrintNum816(0, 0, 2, 43);
    OLEDUpdate();
}

unsigned int mcuSqrt(register unsigned int n){
    register unsigned int r, x;
    r = 0;
    for(x = 0x8000L; x; x >>= 1){
        r += x;
        if((UINT32)(r * r) > n)r -= x;
    }
    return r;
}

void DelayTicks(UINT32 a){
    UINT32 StartTime;
    StartTime = ReadCoreTimer();
    while((UINT32)(ReadCoreTimer()- StartTime) < a){};
}

void mcuJumpToBootLoader(){
    NVMDATA = 0x6193471A;
    SoftReset();
}

void mcuSPIWait(){
    while(mcuSPIIsBusy());
}

void mcuI2CReset()
{
    SDALAT = 0;
    SCLLAT = 0;
    SCL = 1;
    SDAOUT = 1;
    _delay_us(100);
    while(SDA == 0){
        SCL = 0;
        _delay_us(100);
        SCL = 1;
        _delay_us(100);
    }
    SDAOUT = 0;
    _delay_us(100);
    SDAOUT = 1;
    _delay_us(100);
}

void mcuDCTimerReset(){
    WriteTimer1(0);
    mT1ClearIntFlag();
}

void mcuInitISRTimer(){
    OpenTimer2(T2_OFF | T2_IDLE_STOP | T2_GATE_OFF | T2_PS_1_256 | T2_32BIT_MODE_OFF | T2_SOURCE_INT,0xFFFF);
    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_7 | T2_INT_SUB_PRIOR_3);
}

void mcuStartISRTimer(unsigned int per)
{
    WriteTimer2(0);
    WritePeriod2(per);
    T2CONbits.ON = 1;
}

void mcuStopISRTimer(){
    WriteTimer2(0);
    T2CONbits.ON = 0;
    mT2ClearIntFlag();
}

int ADCAuto = 0;

void mcuADCStop(){
    int i;
    if(ADCAuto && !VTIBuffCnt) VTIBuffCnt = DmaChnGetDstPnt(DMA_CHANNEL0) >> 2;
    DmaChnAbortTxfer(DMA_CHANNEL0);
    DmaChnAbortTxfer(DMA_CHANNEL1);
    DmaChnDisable(DMA_CHANNEL0);
    DmaChnDisable(DMA_CHANNEL1);
    CloseADC10();
    i=ADC1BUF0;
    i=ADC1BUF1;
    i=ADC1BUF2;
    i=ADC1BUF3;
    i=ADC1BUF4;
    i=ADC1BUF5;
    i=ADC1BUF6;
    i=ADC1BUF7;
    i=ADC1BUF8;
    i=ADC1BUF9;
    i=ADC1BUFA;
    i=ADC1BUFB;
    i=ADC1BUFC;
    i=ADC1BUFD;
    i=ADC1BUFE;
    i=ADC1BUFF;
    mAD1ClearIntFlag();
    mAD1IntEnable(0);
    ADCAuto=0;
}

void mcuADCStartManualVRef(){
    mcuADCStop();
    OpenADC10(\
            ADC_MODULE_ON | ADC_IDLE_STOP | ADC_FORMAT_INTG16 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF | ADC_SAMP_OFF , \
            ADC_VREF_EXT_EXT | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 | ADC_BUF_16 | ADC_ALT_INPUT_OFF, \
            ADC_SAMPLE_TIME_12 | ADC_CONV_CLK_PB | ADC_CONV_CLK_5Tcy, \
            ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN4_ANA | ENABLE_AN5_ANA | ENABLE_AN14_ANA, \
            SKIP_SCAN_ALL);
    AD1CON1bits.CLRASAM = 0;
    mAD1IntEnable(1);
    ADCAuto = 0;
}
void mcuADCStartManualAVdd(){
    mcuADCStop();
    OpenADC10(\
            ADC_MODULE_ON | ADC_IDLE_STOP | ADC_FORMAT_INTG16 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF | ADC_SAMP_OFF , \
            ADC_VREF_AVDD_EXT | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 | ADC_BUF_16 | ADC_ALT_INPUT_OFF, \
            ADC_SAMPLE_TIME_12 | ADC_CONV_CLK_PB | ADC_CONV_CLK_5Tcy, \
            ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN4_ANA | ENABLE_AN5_ANA | ENABLE_AN14_ANA, \
            SKIP_SCAN_ALL);
    AD1CON1bits.CLRASAM = 0;
    mAD1IntEnable(1);
    ADCAuto = 0;
}

void mcuADCStartAutoVRef(int temp){
    mcuADCStop();

    DmaChnOpen(DMA_CHANNEL0,DMA_CHN_PRI1, DMA_OPEN_DEFAULT);
    DmaChnSetEventControl(DMA_CHANNEL0, DMA_EV_START_IRQ_EN | DMA_EV_START_IRQ(_ADC_IRQ));
    DmaChnSetTxfer(DMA_CHANNEL0,(void*)&ADC1BUF0,(void*)VBuff,4,sizeof(VBuff),2);
    DmaChnWriteEvEnableFlags(DMA_CHANNEL0, DMA_EV_CELL_DONE);
    DmaChnEnable(DMA_CHANNEL0);

    DmaChnOpen(DMA_CHANNEL1,DMA_CHN_PRI0, DMA_OPEN_DEFAULT);
    DmaChnSetEventControl(DMA_CHANNEL1, DMA_EV_START_IRQ_EN | DMA_EV_START_IRQ(_ADC_IRQ));
    DmaChnSetTxfer(DMA_CHANNEL1,(void*)&ADC1BUF1,(void*)TIBuff,4,sizeof(TIBuff),4);
    DmaChnWriteEvEnableFlags(DMA_CHANNEL1, 0);
    DmaChnEnable(DMA_CHANNEL1);

    SetChanADC10(ADCH_VIN);// | (ADCH_VSHUNT<<8));
    OpenADC10(\
            ADC_MODULE_ON | ADC_IDLE_STOP | ADC_FORMAT_INTG32 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON | ADC_SAMP_ON , \
            ADC_VREF_EXT_EXT | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF, \
            ADC_SAMPLE_TIME_31 | ADC_CONV_CLK_PB | ADC_CONV_CLK_35Tcy2, \
            /*ADC_SAMPLE_TIME_31 | ADC_CONV_CLK_PB | ADC_CONV_CLK_23Tcy2, \*/
            ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN4_ANA | ENABLE_AN5_ANA | ENABLE_AN14_ANA, \
            SKIP_SCAN_ALL ^ (ADCH_VIN_SCAN | (temp? ADCH_TEMP_SCAN : ADCH_VSHUNT_SCAN)));
    AD1CON1bits.CLRASAM = 0;
    ADCAuto = 1;
}

void mcuADCRead(int ADCCH, int num){
    SetChanADC10(ADCCH);
    AD1CON2bits.SMPI = num-1;
    AD1CON1bits.ASAM = 1;
    AD1CON1bits.CLRASAM = 1;
    AcquireADC10();
}

int mcuADCReadWait(int ADCCH, int num){
    int ADCInt,i;
    ADCInt = mAD1GetIntEnable();
    mAD1IntEnable(0);
    mAD1ClearIntFlag();
    mcuADCRead(ADCCH, num);
    while(!mAD1GetIntFlag());
    i=0;
    while(num--) i += ReadADC10(num);
    mAD1ClearIntFlag();
    mAD1IntEnable(ADCInt);
    return i;
}

volatile UINT32 _MRT_LastCoreTimer;
int mcuReadTime_us(){ //returns time in us from last call
    UINT32 dw = _MRT_LastCoreTimer;
    _MRT_LastCoreTimer = ReadCoreTimer();
    dw = _MRT_LastCoreTimer - dw;
    dw /= (CORETIMER_FREQ/1000000);
    return dw;
}

static UINT32 H2LTime = 0;
void __ISR(_COMPARATOR_2_VECTOR, IPL7SRS) ComparatorISR(void)
{
    static int oh;
    static int oas;
    UINT32 ccon = CM2CON;
    mcuCompDisable();
    if(ccon & CMP_EVENT_HIGH_TO_LOW){
        mcuDCTimerReset();
        oh = HEATER;
        oas = (ADCStep & 1);
        H2LTime = ReadCoreTimer();
        ISRHigh(CompH2L);
    }
    else{
        CompLowTime = 0;
        if(H2LTime){
            CompLowTime = (ReadCoreTimer() - H2LTime) / 80;
            if(oh) CompLowTimeOn = CompLowTime;
            if(!oh) CompLowTimeOff = CompLowTime;
            H2LTime = 0;
        }
        ISRHigh(CompL2H);
    }
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) Timer1ISR(void)
{
    mT1ClearIntFlag();
    H2LTime = 0;
    CompLowTime = 0;
    ISRHigh(DCTimer);
}

void __ISR(_TIMER_2_VECTOR, IPL7SRS) Timer2ISR(void)
{
    mT2ClearIntFlag();
    T2CONbits.ON = 0;
    ISRHigh(0);
}

void __ISR(_ADC_VECTOR, IPL7SRS) ADCISR(void)
{
    int n, i=0;
    for(n = AD1CON2bits.SMPI + 1; n--;) i += ReadADC10(n);
    mcuADCRES = i;
    mAD1ClearIntFlag();
    ISRHigh(0);
}

void __ISR(_I2C_4_VECTOR,IPL6SOFT) I2CISR(void)
{
    INTClearFlag(INT_I2C4B);
    INTClearFlag(INT_I2C4M);
    INTClearFlag(INT_I2C4S);
    INTClearFlag(INT_I2C4);
    I2CISRTasks();
}

void __ISR(_OUTPUT_COMPARE_2_VECTOR,IPL5SOFT) PIDISR(void){    
    INTClearFlag(INT_OC2);
}

void __ISR(_INPUT_CAPTURE_1_VECTOR, IPL4SOFT) IC1ISR(void){
    static int AInc[]={0, 4, 2, 2, 1};
    int inc;
    if(pars.Input > 4) pars.Input = 4;
    if(inc = AInc[pars.Input]){    
        if(pars.Buttons) inc =- inc;
        if(B1 != B3) inc = -inc;
        Enc += inc;
    }
    while(mIC1CaptureReady()) mIC1ReadCapture();
    INTClearFlag(INT_IC1);
}
void __ISR(_INPUT_CAPTURE_3_VECTOR, IPL4SOFT) IC3ISR(void){
    static int BInc[]={0, 0, 2, 0, 1};
    int inc;
    if(pars.Input > 4) pars.Input = 4;
    if(inc = BInc[pars.Input]){    
        if(pars.Buttons) inc =- inc;
        if(B1 == B3) inc = -inc;
        Enc += inc;
    }
    while(mIC3CaptureReady()) mIC3ReadCapture();    
    INTClearFlag(INT_IC3);    
}

int SPIAuto;
void mcuSPIStop()
{
    //DmaChnAbortTxfer(DMA_CHANNEL2);
    //mcuSPIClose();
    mSPI3AClearAllIntFlags();
    mSPI3ATXIntEnable(0);
    mSPI3ARXIntEnable(0);
    //mcuSPIOpen()
    SPIAuto=0;
};

void mcuSPISendAuto(void * buffer, int len)
{
    SPIAuto = 1;
    mcuSPIStop();
    //mcuSPIOpen();
    //DmaChnOpen(DMA_CHANNEL2,DMA_CHN_PRI3, DMA_OPEN_DEFAULT);
    //DmaChnSetEventControl(DMA_CHANNEL2, DMA_EV_START_IRQ_EN | DMA_EV_START_IRQ(_SPI3_TX_IRQ));
	//DmaChnSetTxfer(DMA_CHANNEL2,(void*)buffer,(void*)&SPI3BUF, len, 1, 1);
    //DmaChnWriteEvEnableFlags(DMA_CHANNEL2, DMA_EV_CELL_DONE);
    //DmaChnEnable(DMA_CHANNEL2);

	//DmaChnSetEvEnableFlags(dmaTxChn, DMA_EV_BLOCK_DONE);	// enable the transfer done interrupt, when all buffer transferred
    //INTSetVectorPriority(DMA_CHANNEL3, INT_PRIORITY_LEVEL_5);
	//INTSetVectorSubPriority(INT_VECTOR_DMA3, INT_SUB_PRIORITY_LEVEL_2);
	//INTEnable(INT_SOURCE_DMA(dmaTxChn), INT_ENABLED);		// enable the chn interrupt in the INT controller
	//DmaTxIntFlag=0;			// clear the interrupt flag we're  waiting on

	// wait for the transfer to complete
	// In a real application you can do some other stuff while the DMA transfer is taking place
	//while(!DmaTxIntFlag);
	// ok, we've sent the data in the buffer
	//return 1;
}

// handler for the DMA channel 1 interrupt
//void __ISR(_DMA1_VECTOR, IPL5SOFT) DmaHandler1(void)
//{
	//int	evFlags;				// event flags when getting the interrupt
//
	//INTClearFlag(INT_SOURCE_DMA(DMA_CHANNEL1));	// acknowledge the INT controller, we're servicing int
//
	//evFlags=DmaChnGetEvFlags(DMA_CHANNEL1);	// get the event flags
//
//    if(evFlags&DMA_EV_BLOCK_DONE)
//    { // just a sanity check. we enabled just the DMA_EV_BLOCK_DONE transfer done interrupt
//    	DmaTxIntFlag=1;
//        DmaChnClrEvFlags(DMA_CHANNEL1, DMA_EV_BLOCK_DONE);
//    }
//}

#undef _PIC32MX534F064H_C
