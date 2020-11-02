#define _PIC32MX564F128H_C

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
#include <peripheral/int.h>
#include <peripheral/nvm.h>
#include "usb/usb.h"
#include "crc.h"

typedef struct
{
	UINT32 Address;
	UINT16 RecDataLen;
	UINT8* Data;
}T_FLASH_RECORD;

void DelayTicks(UINT32 a){
    UINT32 StartTime;
    StartTime=ReadCoreTimer();
    while((UINT32)(ReadCoreTimer()-StartTime)<a){};
}

void mcuInit(void)
{
    INTDisableInterrupts();
    OpenCoreTimer(0xFFFFFFFF);
    SYSTEMConfigWaitStates(80000000);

    LATB=0b1000000000000000;
    LATC=0b0110000000000000;
    LATD=0b100001010000;
    LATE=0;
    LATF=0;
    LATG=0;
    TRISB=0b1100000000111111;
    TRISC=0b1001000000000000;
    TRISD=0;
    TRISE=0;
    TRISF=0;
    TRISG=0b1000111111;
    ODCB=0;
    ODCC=0;
    ODCD=0;
    ODCE=0;
    ODCF=0;
    ODCG=0;

    HCH=0;
    ID_3S=0;
    ID_OUT=0;
    HEATER=0;
    CBANDA=1;
    CBANDB=1;
    CHSEL1=0;
    CHSEL2=1;
    CHPOL=0;

    OpenTimer3(T3_ON | T3_IDLE_STOP | T3_GATE_OFF | T3_PS_1_256 | T3_SOURCE_INT, 40);
    OpenOC1(OC_ON | OC_IDLE_STOP | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0x20, 0);
    SPKOFF;
}

void mcuDisableUSB(void)
{
    unsigned int IntState;
    IntState = INTDisableInterrupts();
    USBDisableInterrupts();
    USBModuleDisable();
    USBClearUSBInterrupt();
    INTRestoreInterrupts(IntState);
}

void mcuJumpToApp(void)
{
	void (*fptr)(void);
	fptr = (void (*)(void))USER_APP_RESET_ADDRESS;
	fptr();
}

UINT mcuEraseFlash(void){
    UINT Result;
    UINT32 i;
    void* pFlash;
    Result = 1;
    pFlash = (void*)APP_FLASH_BASE_ADDRESS;
    for( i = 0; i < ((APP_FLASH_END_ADDRESS - APP_FLASH_BASE_ADDRESS + 1)/FLASH_PAGE_SIZE); i++ )
    {
        Result = NVMErasePage( pFlash + (i*FLASH_PAGE_SIZE) );
        if(Result)break;
    }
    pFlash = (void*)APP_IVT_BASE_ADDRESS;
    for( i = 0; i < ((APP_IVT_END_ADDRESS - APP_IVT_BASE_ADDRESS + 1)/FLASH_PAGE_SIZE); i++ )
    {
        Result = NVMErasePage( pFlash + (i*FLASH_PAGE_SIZE) );
        if(Result)break;
    }
    return Result;
}

UINT mcuWriteFlashRecord(void * RecordData)
{
    T_FLASH_RECORD lFR;
    void* ProgAddress;
    void* ProgAddressEnd;
    UINT32 WrData;
    UINT Result;
    lFR.Address = *((UINT32 *)RecordData);
    lFR.RecDataLen = *((UINT32 *)(RecordData+4));
    lFR.Data = (RecordData + 8);

    Result=0;
    while(lFR.RecDataLen)
    {
        ProgAddress = PA_TO_KVA0(lFR.Address);
        ProgAddressEnd = ProgAddress + lFR.RecDataLen;
        if((lFR.RecDataLen>=512)&&((lFR.Address & 511L)==0))
        {
            Result=NVMWriteRow(ProgAddress,lFR.Data);
            lFR.Address+=512;
            lFR.RecDataLen-=512;
            lFR.Data+=512;
        }
        else
        {
            if((((ProgAddress >= (void *)APP_FLASH_BASE_ADDRESS) && (ProgAddressEnd <= (void *)APP_FLASH_END_ADDRESS)) ||
                ((ProgAddress >= (void *)APP_IVT_BASE_ADDRESS) && (ProgAddressEnd <= (void *)APP_IVT_END_ADDRESS))) &&
               ((ProgAddressEnd <= (void*)DEV_CONFIG_REG_BASE_ADDRESS) || (ProgAddress > (void*)DEV_CONFIG_REG_END_ADDRESS)))
            {
                WrData = 0xFFFFFFFF;
                memcpy(&WrData,lFR.Data,min(4,lFR.RecDataLen));
                Result = NVMWriteWord(ProgAddress, WrData);
            }
            lFR.Address += 4;
            lFR.Data += 4;
            if(lFR.RecDataLen > 3)
            {
                lFR.RecDataLen -= 4;
            }
            else
            {
                lFR.RecDataLen = 0;
            }
        }
        if(Result)break;
    }
    return Result;
}

UINT32 mcuProgramComplete(){
    UINT32 pCRC;
    pCRC = CalculateCRC(1234, (void *)KVA0_TO_KVA1(APP_FLASH_BASE_ADDRESS), (APP_FLASH_END_ADDRESS - APP_FLASH_BASE_ADDRESS) - 3);
    NVMWriteWord((void *)(APP_FLASH_END_ADDRESS - 3), pCRC);
    return pCRC;
}

UINT mcuValidAppPresent()
{
    UINT32 pCRC;
    pCRC = CalculateCRC(1234, (void *)KVA0_TO_KVA1(APP_FLASH_BASE_ADDRESS), (APP_FLASH_END_ADDRESS - APP_FLASH_BASE_ADDRESS) - 3);
    if(pCRC == (*((UINT32 *)KVA0_TO_KVA1(APP_FLASH_END_ADDRESS - 3))))return 1;
    return 0;
}

void mcuSPIWait(){
    while(mcuSPIIsBusy());
}


#undef _PIC32MX564F128H_C