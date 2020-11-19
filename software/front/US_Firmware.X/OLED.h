/* 
 * File:   OLED.h
 * Author: Sparky
 *
 * Created on ?????, 2014, ??? 16, 18:51
 */

#ifndef OLED_H
#define	OLED_H



#ifdef	__cplusplus
extern "C" {
#endif

typedef struct __PACKED{
    int SH1106:1;
    int InternalChargePump:1;
}displaysetup_t;

#ifndef _OLED_C
#define OLEDC_EXTERN extern

extern volatile displaysetup_t DisplaySetup;

extern const UINT8 font8x8[128][8];
extern const UINT8 font6x8[96][5];
extern const UINT8 degrees4x8[4];
extern const UINT8 font8x16[128][16];
extern const UINT8 degrees4x16[8];
#else
#define OLEDC_EXTERN
#endif


OLEDC_EXTERN union {
    UINT32 D[8][32];
    UINT8 B[8][128];
}OLEDBUFF;

OLEDC_EXTERN void OLEDInit();
OLEDC_EXTERN void OLEDUpdate();
OLEDC_EXTERN void OLEDInvert(int col,int colnum, int row, int rownum);
OLEDC_EXTERN void OLEDInvertXY(int x, int dx, int y, int dy);
OLEDC_EXTERN void OLEDFill(int col, int colnum, int row, int rownum, UINT8 b);
OLEDC_EXTERN void OLEDPrintNum3248(int col, int row, int num);
OLEDC_EXTERN void OLEDPrintCF1648(int col, int row, int CF);
OLEDC_EXTERN void OLEDPrintNum(int col, int row, int dec, int num, void* font, int startChar, int width, int height, int blank );
OLEDC_EXTERN void OLEDPrintHex(int col, int row, int dec, unsigned int num, void* font, int startChar, int width, int height, int blank );
OLEDC_EXTERN void OLEDPrint(int col, int row, const char * s, int num, void * font, int startChar, int width, int height, int blank);
OLEDC_EXTERN void OLEDPrintXY(int col, int row, const char * s, int num, void * font, int startChar, int width, int height, int blank);


#define OLEDPrint68(col, row, s, num) OLEDPrint(col, row, s, num, font6x8, 32, 5, 1, 1)
#define OLEDPrintXY68(col, row, s, num) OLEDPrintXY(col, row, s, num, font6x8, 32, 5, 1, 1)
#define OLEDPrintNum68(col, row, dec, num) OLEDPrintNum(col, row, dec, num, font6x8, 32, 5, 1, 1)
#define OLEDPrintHex68(col, row, dec, num) OLEDPrintHex(col, row, dec, num, font6x8, 32, 5, 1, 1)
#define OLEDPrint88(col, row, s, num) OLEDPrint(col, row, s, num, font8x8, 0, 8, 1, 0)
#define OLEDPrintXY88(col, row, s, num) OLEDPrintXY(col, row, s, num, font8x8, 0, 8, 1, 0)
#define OLEDPrintNum88(col, row, dec, num) OLEDPrintNum(col, row, dec, num, font8x8, 0, 8, 1, 0)
#define OLEDPrintHex88(col, row, dec, num) OLEDPrintNum(col, row, dec, num, font8x8, 0, 8, 1, 0)
#define OLEDPrint816(col, row, s, num) OLEDPrint(col, row, s, num, font8x16, 0, 8, 2, 0)
#define OLEDPrintXY816(col, row, s, num) OLEDPrintXY(col, row, s, num, font8x16, 0, 8, 2, 0)
#define OLEDPrintNum816(col, row, dec, num) OLEDPrintNum(col, row, dec, num, font8x16, 0, 8, 2, 0)
#define OLEDPrintHex816(col, row, dec, num) OLEDPrintNum(col, row, dec, num, font8x16, 0, 8, 2, 0)

#undef OLEDC_EXTERN



#ifdef	__cplusplus
}
#endif

#endif	/* OLED_H */

