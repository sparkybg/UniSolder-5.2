#define _OLED_C

#include "main.h"
#include "mcu.h"
#include "font32x48numbers.h"
#include "fonts.h"
#include "font6x8.h"
#include "font8x16.h"
#include "OLED.h"

//const unsigned char OLEDInitBuff[31]={0xAE, 0xD5,0xF0,0xA8,0x3F,0xD3,0x00,0x40,0x8D,0x10,0xA0,0xC0,0xDA,0x12,0x81,0xFF,0xD9,0x22,0xDB,0x40,0xA4,0xA6,0xAF,0x20,0x00,0x21,0,127,0x22,0,7};
const unsigned char OLEDInitBuff[]={
    0xAE,       //display off
    0xD5,0x80,  //set clock & divide ratio
    0xA8,0x3F,  //set MUX ratio
    0xD3,0x00,  //set display offset
    0x40,       //set display start line
    0x8D, 0x10, //disable charge pump
    0xA0,       //set segment remap
    0xC0,       //set COM direction
    0xDA,0x12,  //set COM hardware configuration
    0x81,0xFF,  //set contrast
    0xD9,0x22,  //set precharge period
    0xDB,0x20,  //set DCOM deselect level
    0xA4,       //disable entire on
    0xA6,       //set normal display
    0xAF,       //display on
    0x20,0x00,  //set horizontal addressing mode
};

const unsigned char OLEDPreUpdateBuff[]={
    0x21,0,127,  //start/end column
    0x22,0,7,    //start/end row
    0x81         //contrast
};

void OLEDInit(){
    _delay_ms(1);
    OLED_RES = 0;
    _delay_ms(1);
    OLED_RES = 1;
    OLED_VCC = 0;
    _delay_ms(100);
    OLED_DC = 0;
    OLED_CS = 0;
    _delay_ms(100);
    mcuSPISendBytes((int*)OLEDInitBuff, sizeof(OLEDInitBuff));
    OLEDFill(0, 128, 0, 8, 0);
    OLEDUpdate();
}

void OLEDUpdate(){
    mcuSPIWait();
    mcuSPIStop();
    OLED_DC = 0;
    OLED_CS = 0;
    mcuSPISendBytes((int*)OLEDPreUpdateBuff, sizeof(OLEDPreUpdateBuff));
    mcuSPISendByte((pars.Bri << 4) - 15);           //brightness
    mcuSPISendByte(pars.DispRot ? 0xC8 : 0xC0);     //rotation H
    mcuSPISendByte(pars.DispRot ? 0xA1 : 0xA0);     //rotation V
    mcuSPIWait();
    
    OLED_DC = 1;
    mcuSPISendAuto(OLEDBUFF.B[0],128*8);
}

void OLEDFill(int col, int colnum, int row, int rownum, UINT8 b){
    int cc;
    while(rownum--){
        cc = colnum;
        while(cc--)OLEDBUFF.B[row][col++] = b;
        col -= colnum;
        row++;
    }
}

void OLEDInvert(int col,int colnum, int row, int rownum){
    int cc;
    while(rownum--){
        cc = colnum;
        while(cc--)OLEDBUFF.B[row][col++] ^= 255;
        col -= colnum;
        row++;
    }
}

void OLEDWrite(int col, int colnum, int row, void * buf, int num){
    int cc;
    while(num){
        cc = colnum;
        while(num && cc--){
            OLEDBUFF.B[row][col++] = *(UINT8*)buf;
            buf++;
            num--;
        }
        col -= colnum;
        row++;
    }
}


void OLEDPrintNum3248(int col, int row, int num){
    int i, cd;
    col += 64;
    i = 3;
    while(i--){
        cd = num % 10;
        num /= 10;
        if(num || cd || (i>1)) {
            OLEDWrite(col, 32, row, (void *)numbers32x48[cd],192);
        }
        else{
            OLEDFill(col, 32, row, 6, 0);
        }
        col -= 32;
    }
}
void OLEDPrintCF1648(int col, int row, int CF){
    CF+=10;
    OLEDWrite(col, 16, row++, (void *)&numbers32x48[CF][0],16);
    OLEDWrite(col, 16, row++, (void *)&numbers32x48[CF][32],16);
    OLEDWrite(col, 16, row++, (void *)&numbers32x48[CF][64],16);
    OLEDWrite(col, 16, row++, (void *)&numbers32x48[CF][96],16);
    OLEDWrite(col, 16, row++, (void *)&numbers32x48[CF][128],16);
}

void OLEDPrintNum(int col, int row, int dec, int num, void* font, int startChar, int width, int height, int blank ){    
    int cb = width * height;
    int cw = width + blank;
    int i, cd;
    i = dec;
    dec--;
    col += cw * dec;
    if(num<0)num=-num;
    while(i--){
        cd = num % 10;
        num /= 10;
        if(num || cd || (i == dec)) {
            OLEDWrite(col, width, row, (void *)font + cb * (cd + 0x30 - startChar), cb);
            OLEDFill(col + width, blank, row, height, 0);
        }
        else{
            OLEDFill(col, cw, row, height, 0);
        }
        col -= cw;
    }
}

void OLEDPrint(int col, int row, const char * s, int num, void * font, int startChar, int width, int height, int blank){
    int cb = width * height;
    if(num == 0) num = 128;
    while(num--){
        if(s[0] == 0) break;
        OLEDWrite(col, width, row, (void *)font + cb * (s[0] - startChar), cb);
        col += width;
        OLEDFill(col, blank, row, height, 0);
        col += blank;
        s++;
    }
}
#undef _OLED_C
