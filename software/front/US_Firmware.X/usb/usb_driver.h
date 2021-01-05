/* 
 * File:   usb_driver.h
 * Author: Sparky
 *
 * Created on ??????????, 2013, ?????? 5, 23:55
 */

#ifndef USB_DRIVER_H
#define	USB_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "../typedefs.h"

extern void USBDriverInit(void);
extern unsigned char USBTxBuffer[64];
extern unsigned char USBRxBuffer[64];
extern volatile USB_HANDLE USBOutHandle;    //USB handle.  Must be initialized to 0 at startup.
extern volatile USB_HANDLE USBInHandle;     //USB handle.  Must be initialized to 0 at startup.

#ifdef	__cplusplus
}
#endif

#endif	/* USB_DRIVER_H */

