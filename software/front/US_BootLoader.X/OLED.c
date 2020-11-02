#define _OLED_C

#include "mcu.h"
#include "OLED.h"

const unsigned char OLEDInitBuff[31]={0xAE,0xD5,0xF0,0xA8,0x3F,0xD3,0x00,0x40,0x8D,0x10,0xA0,0xC0,0xDA,0x12,0x81,0xFF,0xD9,0x22,0xDB,0x40,0xA4,0xA6,0xAF,0x20,0x00,0x21,0,127,0x22,0,7};

void OLEDInit(){
    int i;
    _delay_ms(1);
    OLED_RES = 0;
    _delay_ms(1);
    OLED_RES = 1;
    OLED_VCC = 0;
    _delay_ms(100);    
    OLED_DC = 0;
    OLED_CS = 0;
    _delay_ms(100);
    mcuSPISendBytes((int*)OLEDInitBuff, 31);
    mcuSPIWait();
    for(i=0;i<256;i++)OLEDBUFF.D[0][i]=0;
    OLEDUpdate();
}

void OLEDUpdate(){
    OLED_DC = 1;
    OLED_CS = 0;
    mcuSPISendBytes((unsigned int *) OLEDBUFF.B[0], 128*8);
    mcuSPIWait();
    OLED_CS = 1;
}

#undef _OLED_C