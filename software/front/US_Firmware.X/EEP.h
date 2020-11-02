/* 
 * File:   EEP.h
 * Author: Sparky
 *
 * Created on ?????, 2013, ????????? 6, 15:20
 */

#ifndef EEP_H
#define	EEP_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef _EEP_C
#define EEP_EXTERN extern
#else
#define EEP_EXTERN
#endif

EEP_EXTERN void EEPWrite(UINT16 a, UINT8 * b, UINT16 c);
EEP_EXTERN void EEPWriteImm(UINT16 a, UINT8 b);
EEP_EXTERN UINT8 EEPRead(UINT16 a, UINT8 * b, UINT16 c);
    
#ifdef	__cplusplus
}
#endif

#endif	/* EEP_H */

