/* 
 * File:   PIC32MX.h
 * Author: Sparky
 *
 * Created on ???????, 2013, ??? 30, 1:56
 */

#ifndef PIC32MX564F128H_H
#define	PIC32MX564F128H_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <GenericTypeDefs.h>
#include <peripheral/adc10.h>
#include <peripheral/cmp.h>
#include <peripheral/i2c.h>
#include <peripheral/spi.h>

#ifdef _PIC32MX564F128H_C
#define P32_EXTERN
#else
#define P32_EXTERN extern
#endif

#define SYS_FREQ                    (80000000UL)
#define CORETIMER_FREQ              (SYS_FREQ/2UL)
#define PER_FREQ                    (SYS_FREQ/2UL)
#define I2C_CLOCK_FREQ              (400000UL)

P32_EXTERN void DelayTicks(UINT32 a);
#define _delay_us(a) DelayTicks(a*(CORETIMER_FREQ/1000000UL))
#define _delay_ms(a) DelayTicks(a*(CORETIMER_FREQ/1000UL))

#ifdef _PIC32MX564F128H_C
#define P32_EXTERN
#else
#define P32_EXTERN extern
#endif

extern const void _RESET_ADDR;
#define DEVICE_ID                   0x23248568
#define DEVICE_MAJOR_VERSION        1
#define DEVICE_MINOR_VERSION        0
#define DEVICE_RESET_ENTRY          (void *)&_RESET_ADDR

#define BOOTLOADER_MAJOR_VERSION    1
#define BOOTLOADER_MINOR_VERSION    0

#define PROGRAM_FLASH_END_ADRESS    (0x9D000000+BMXPFMSZ-1)

#define APP_FLASH_BASE_ADDRESS      0x9D003000
#define APP_FLASH_END_ADDRESS       PROGRAM_FLASH_END_ADRESS

#define APP_IVT_BASE_ADDRESS        0x9FC01000
#define APP_IVT_END_ADDRESS         0x9FC01FFF

#define USER_APP_RESET_ADDRESS      0x9D003000

#define FLASH_PAGE_SIZE		 	4096
#define DEV_CONFIG_REG_BASE_ADDRESS     0x9FC02FF0
#define DEV_CONFIG_REG_END_ADDRESS      0x9FC02FFF

//outputs
#define HEATER      LATEbits.LATE6
#define HCH         LATEbits.LATE7
#define CBANDA      LATEbits.LATE2
#define CBANDB      LATFbits.LATF3
#define CHSEL1      LATEbits.LATE5
#define CHSEL2      LATEbits.LATE4
#define CHPOL       LATEbits.LATE3
#define OLED_VCC    LATCbits.LATC14
#define OLED_RES    LATDbits.LATD7
#define OLED_DC     LATDbits.LATD6
#define OLED_CS     LATDbits.LATD4
#define ID_OUT      LATBbits.LATB15

//inputs
#define B1          PORTDbits.RD8
#define B2          PORTDbits.RD9
#define B3          PORTDbits.RD10
#define ID_IN       PORTBbits.RB15
#define NAP         PORTGbits.RG9
#define ID_3S       TRISBbits.TRISB15

#define SPEAKER     OC1CONbits.ON
#define SPKON       if(!SPEAKER)SPEAKER=1
#define SPKOFF      if(SPEAKER)SPEAKER=0

#define SDISDO_OO   {TRISDCLR=0b1100;}
#define SDI_OUT     LATDbits.LATD2
#define SDO_OUT     LATDbits.LATD3

#define mcuDisableInterrupts() INTDisableInterrupts()

//USB Stack definitions
#define self_power          1
#define USB_BUS_SENSE       1

P32_EXTERN void mcuInit(void);
P32_EXTERN void mcuDisableUSB(void);
P32_EXTERN void mcuJumpToApp(void);
P32_EXTERN UINT mcuEraseFlash();
P32_EXTERN UINT mcuWriteFlashRecord(void * RecordData);
P32_EXTERN UINT32 mcuProgramComplete(void);
P32_EXTERN UINT mcuValidAppPresent();

#define mcuReset() Reset()

#define mcuSPIOpen() SpiChnOpen(SPI_CHANNEL3,SPI_OPEN_MSTEN | SPI_OPEN_MODE8 | SPI_OPEN_CKP_HIGH, 4)
#define mcuSPIClose() SpiChnClose(SPI_CHANNEL3)
#define mcuSPISendByte(b) SpiChnPutC(SPI_CHANNEL3, b)
#define mcuSPISendBytes(b,n) SpiChnPutS(SPI_CHANNEL3,b,n)
#define mcuSPIIsBusy() SpiChnIsBusy(SPI_CHANNEL3)
P32_EXTERN void mcuSPIWait();


#undef P32_EXTERN

#ifdef	__cplusplus
}
#endif

#endif	/* PIC32MX_H */
