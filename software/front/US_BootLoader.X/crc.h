/* 
 * File:   crc.h
 * Author: Sparky
 *
 * Created on ??????????, 2013, ????????? 9, 4:08
 */

#ifndef CRC_H
#define	CRC_H

#ifdef	__cplusplus
extern "C" {
#endif

extern UINT16 CalculateCRC(UINT16 scrc, UINT8 *data, UINT32 len);

#ifdef	__cplusplus
}
#endif

#endif	/* CRC_H */

