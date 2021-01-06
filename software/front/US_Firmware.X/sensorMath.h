/* 
 * File:   sensorMath.h
 * Author: Sparky
 *
 * Created on ??????, 2015, ??? 17, 19:35
 */

#ifndef SENSORMATH_H
#define	SENSORMATH_H

#include <GenericTypeDefs.h>
#include "typedefs.h"
#include "iron.h"


#ifdef	__cplusplus
extern "C" {
#endif
    

typedef union{
    struct __PACKED
    {
        unsigned int m:23;
        unsigned int e:8;
        unsigned int s:1;
    };
    float f;
}SFLOAT;

typedef struct {
    UINT32 m;
    INT32 e;
}ExtFloat;

#define float2ExtFloat(ef, f) \
{ \
    ef.m = ( ((UINT32)((SFLOAT)f).m) & 0x7FFFFFUL) << 8; \
    if((ef.e = ((SFLOAT)f).e)) ef.m |= 0x80000000; \
}

#define ExtFloatDivByUInt(ef, ui) \
{ \
    if(ef.m /= ui){ \
        while (ef.m < 0x80000000UL){ \
            ef.m <<= 1; \
            ef.e--; \
        } \
    } \
    else { \
        ef.e = 0; \
    } \
}

#define ExtFloatMul(ef1, ef2) \
{ \
    if((ef1.m = ((UINT64)ef1.m * (UINT64)ef2.m) >> 32)){ \
        ef1.e += ef2.e - 126; \
        while(ef1.m < 0x80000000UL){ \
            ef1.m <<= 1; \
            ef1.e--; \
        } \
    } \
    else { \
        ef1.e = 0; \
    } \
}

#define ExtFloatAdd(ef1, ef2) \
{\
    if(ef1.e >= ef2.e){ \
        if((ef1.e - ef2.e) < 31){ \
            if((ef1.m = (ef1.m >> 1) + (ef2.m >> (ef1.e - ef2.e + 1)))){ \
                if(ef1.m >= 0x80000000UL){ \
                    ef1.e++; \
                } \
                else{ \
                    ef1.m <<= 1; \
                } \
            }\
            else{ \
                ef1.e = 0; \
            } \
        } \
    } \
    else { \
        if((ef2.e - ef1.e) < 31){ \
            if((ef1.m = (ef2.m >> 1) + (ef1.m >> (ef2.e - ef1.e + 1)))){ \
                ef1.e = ef2.e; \
                if(ef1.m >= 0x80000000UL){ \
                    ef1.e++; \
                } \
                else{ \
                    ef1.m <<= 1; \
                } \
            }\
            else{ \
                ef1.e = 0; \
            } \
        } \
        else{ \
            ef1 = ef2; \
        } \
    } \
}

#ifndef _SENSORMATH_C
#define SENSORMATH_H_EXTERN extern
#else
#define SENSORMATH_H_EXTERN
#endif

INT32 GetSensorTemperature(int input, t_SensorConfig * SC);

#undef SENSORMATH_H_EXTERN

#ifdef	__cplusplus
}
#endif

#endif	/* SENSORMATH_H */
