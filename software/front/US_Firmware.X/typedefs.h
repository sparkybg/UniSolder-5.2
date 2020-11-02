/* 
 * File:   typedefs.h
 * Author: Sparky
 *
 * Created on ??????, 2013, ?????? 19, 0:40
 */

#ifndef __TYPEDEFS_H__
#define	__TYPEDEFS_H__

#ifdef	__cplusplus
extern "C" {
#endif

#include <GenericTypeDefs.h>

#if !defined(__PACKED)
    #define __PACKED __attribute__((__packed__))
#endif

typedef union{
    int i;
    unsigned int ui;
}SUINT;

typedef union{
    INT8 i8;
    UINT8 ui8;
}SUINT8;

typedef union{
    INT16 i16;
    UINT16 ui16;
    INT8 i8[2];
    UINT8 ui8[2];
}SUINT16;

typedef union {
    INT32 i32;
    UINT32 ui32;
    INT16 i16[2] __PACKED;
    UINT16 ui16[2] __PACKED;
    INT8 i8[4];
    UINT8 ui8[4];
    struct __PACKED
    {
        UINT8 z1;
        INT16 mi16;
        UINT8 z2;
    };
    struct __PACKED
    {
        UINT8 z3;
        INT16 mui16;
        UINT8 z4;
    };
}SUINT32;

typedef union {
    INT64 i64;
    UINT64 ui64;
    INT32 i32[2];
    UINT32 ui32[2];
    INT16 i16[4] __PACKED;
    UINT16 ui16[4] __PACKED;
    INT8 i8[8];
    UINT8 ui8[8];
}SUINT64;


#ifdef	__cplusplus
}
#endif


#endif	/* __TYPEDEFS_H__ */