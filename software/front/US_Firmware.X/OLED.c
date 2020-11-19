#define _OLED_C

#include "main.h"
#include "mcu.h"
#include "font32x48numbers.h"
#include "fonts.h"
#include "font6x8.h"
#include "font8x16.h"
#include "OLED.h"

#define CmdNOP 0xE3
#define CmdRot0 0xC0A0
#define CmdRot180 0xC8A1
#define CmdCol 0x21
#define CmdRow 0x22
#define CmdBri 0x81

volatile displaysetup_t DisplaySetup = {0, 0};

const unsigned char OLEDInitBuff1[]={
    0xAE,       //display control ([AE] OFF, AF ON)
    0xD5,0x80,  //set clock & divide ratio [50]
    0xA8,0x3F,  //set MUX ratio [3F]
    0xD3,0x00,  //set display offset [00]
    0x40,       //set display start line [40]
};

const unsigned char OLEDInitBuff2[]={

    0xDA,0x12,  //set COM hardware config (02 sequential, [12] alternative)
    0xD9,0x22,  //set precharge period [22]
    0xDB,0x35,  //set VCOM deselect level [35] //020
    0xA4,       //entire display on ([A4] normal, A5 entire on)
    0xA6,       //normal/reversed display ([A6] normal, A7 reversed)
    0xAF,       //display ON
    //0x20,0x02,  //set page addressing mode //no need - state after reset
};

typedef union {
    struct __PACKED {
        struct __PACKED{
            UINT8 BriCmd;
            UINT8 Bri;
            UINT16 Rot;
        } PreDisplayUpdate;
        struct __PACKED{
            UINT8 Row;
            UINT8 ColHi;
            UINT8 ColLow;
        } PreRowUpdate;
    };
}preUpdate_t;

preUpdate_t PreUpdateBuff = {
    CmdBri, 225,
    CmdRot0,
    0xB0,
    0x10,
    0
};

void OLEDInit(){
    mcuSPIClose();
    OLED_VCC = 1; //turn off display VCC
    OLED_VDD = 1; //turn off display VDD
    OLED_RES = 0; //Reset display
    OLED_DC = 0;
    OLED_CS = 0;
    OLED_SCK = 0;
    OLED_SDI = 0;
    OLED_SDO = 0;
    OLED_RES_3S = 0;
    OLED_DC_3S = 0;  
    OLED_CS_3S = 0;
    SDI_3S = 0;
    SDO_3S = 0;
    SCK_3S = 0;            
    _delay_ms(100);
                
    //DisplaySetup.SH1106 = OLED_CS_IN; //no power, and weak pull-up. If CS pull-up resistor is installed, it will dominate, and OLED_CS will be low => display controller is SSH1106
    OLED_CS_3S = 1;  //everything but reset - 3state
    OLED_DC_3S = 1;  
    SDI_3S = 1;
    SDO_3S = 1;
    SCK_3S = 1;        
    OLED_VDD = 0;    //Turn on display VDD 
    OLED_CS_PU = 1; //enable weak internal pull-up on CS in order to check for pull-down resistor on CS
    OLED_DC_PU = 1; //enable weak internal pull-up on DC in order to check if resistor between OLED_RES and OLED_DC is installed
    _delay_ms(100);

    DisplaySetup.SH1106 = !OLED_CS_IN; //If CS pull-down resistor is installed, OLED_CS will be low => display controller is SH1106    
    DisplaySetup.InternalChargePump = !OLED_DC_IN; //If resistor between OLED-RES is installed, it will dominate and OLED_DC will be low => display uses internal charge pump.
    
    OLED_DC_PU = 0;//bring all IOs to operational state (outputs, no internal pull-ups)
    OLED_CS_3S = 0;
    OLED_DC_3S = 0;
    SCK_3S = 0;
    SDI_3S = 0;
    SDO_3S = 0;    
    OLED_CS = 1;
    OLED_DC = 1;    
    _delay_ms(10);
    
    SDI_OUT = 0;
    SDO_OUT = 0;
    OLED_RES = 1;
    mcuSPIOpen();    
    _delay_ms(1);
    OLED_VCC = 0; ///turn on display VCC
    _delay_ms(100);
    
    OLED_DC = 0;
    OLED_CS = 0;
    _delay_ms(10);
    
    mcuSPISendBytes((int*)OLEDInitBuff1, sizeof(OLEDInitBuff1));
    mcuSPIWait();
    if(DisplaySetup.SH1106){
        PreUpdateBuff.PreRowUpdate.ColLow = 2; //SSH1106 is 131x64 - shift right by 2
        mcuSPISendByte(0x30); //charge pump voltage level [30]-33: 7.4, 8.0, 8.4, 9.0)
        mcuSPISendByte(0x8D); //charge pump control       
        mcuSPISendByte(DisplaySetup.InternalChargePump ? 0x14 : 0x10);        
    }
    else{
        PreUpdateBuff.PreRowUpdate.ColLow = 0; //SSD1306 is 128x64 - no need to shift
        mcuSPISendByte(0xAD); //charge pump control       
        mcuSPISendByte(DisplaySetup.InternalChargePump ? 0x8B : 0x8A);
    }
    mcuSPIWait();
    mcuSPISendBytes((int*)OLEDInitBuff2, sizeof(OLEDInitBuff2));     

    OLEDFill(0, 128, 0, 8, 0);
    OLEDUpdate();
}

void OLEDUpdateDMA(){
    mcuSPIWait();
    mcuSPIStop();
    PreUpdateBuff.PreDisplayUpdate.Bri = (pars.Bri << 4) - 15;
    PreUpdateBuff.PreDisplayUpdate.Rot = pars.DispRot ? CmdRot180 : CmdRot0;
    OLED_DC = 0;
    OLED_CS = 0;
    mcuSPISendBytes((int*)&PreUpdateBuff, sizeof(PreUpdateBuff));
    mcuSPIWait();    
    OLED_DC = 1;
    mcuSPISendAuto(OLEDBUFF.B[0],128*8);
}

void OLEDUpdate(){
    UINT8 r;
    mcuSPIWait();
    OLED_DC = 0;
    OLED_CS = 0;
    PreUpdateBuff.PreDisplayUpdate.Bri = (pars.Bri << 4) - 15;
    PreUpdateBuff.PreDisplayUpdate.Rot = pars.DispRot ? CmdRot180 : CmdRot0;
    mcuSPISendBytes((int*)&PreUpdateBuff.PreDisplayUpdate, sizeof(PreUpdateBuff.PreDisplayUpdate) );    
    for(r=0;r<=7;r++ ){
        PreUpdateBuff.PreRowUpdate.Row = 0xB0+r;
        mcuSPIWait();       
        OLED_DC = 0;
        OLED_CS = 0;
        mcuSPISendBytes((int*)&PreUpdateBuff.PreRowUpdate, sizeof(PreUpdateBuff.PreRowUpdate));
        mcuSPIWait();
        OLED_DC = 1;    
        mcuSPISendBytes((int*)OLEDBUFF.B[r], 128 );
    }
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

void OLEDFillGr(int col, int colnum, int row, int rownum, UINT8 b){
    if(!(row & 7)) return OLEDFill(col, colnum, row >> 3, rownum, b);
    int cc;
    while(rownum--){
        cc = colnum;
        //while(cc--)OLEDBUFF.B[row][col++] = b;
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

void OLEDInvertXY(int x, int dx, int y, int dy){
    if(!(y & 7) && !(dy & 7)) return OLEDInvert(x, dx, y >> 3, dy >> 3 );    
    while(dy > 0){
        int row7 = y & 7;
        int rowL = 8 - row7;
        UINT8 mask = 0xFF << row7;
        if(dy < rowL) mask &= 0xFF >> (rowL - dy);
        int cx = x;        
        int cc = dx;
        while(cc--)OLEDBUFF.B[y >> 3][cx++] ^= mask;
        dy -= rowL;
        y += rowL;
    }
}

void OLEDWrite(int col, int colnum, int row, void * buf, int num){
    while(num){
        int cc = colnum;
        while(num && cc--){
            OLEDBUFF.B[row][col++] = *(UINT8*)buf;
            buf++;
            num--;
        }
        col -= colnum;
        row ++;        
    }
}

void OLEDWriteXY(int x, int colnum, int y, void * buf, int num){
    if(!(y & 7)) return OLEDWrite(x, colnum, y >> 3, buf, num );    
    int row70 = y & 7;
    int row71 = 8 - row70;
    UINT8 mask0 = 0xFF >> row71;
    UINT8 mask1 = 0xFF << row70;
    while(num){
        int cc = colnum;
        int buffRow = y >> 3;
        while(num && cc--){
            UINT8 b = (*(UINT8*)buf);
            if(row70){
                OLEDBUFF.B[buffRow][x] &= mask0;
                OLEDBUFF.B[buffRow][x] |= b << row70;
                OLEDBUFF.B[buffRow+1][x] &= mask1;
                OLEDBUFF.B[buffRow+1][x++] |= b >> row71;
            }
            else{
                OLEDBUFF.B[buffRow][x] = b;
            }
            buf++;
            num--;
        }
        x -= colnum;
        y += 8;        
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
    int minus=0;
    if(num<0){
        num=-num;
        minus=1;
    }
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
            if(minus){
                OLEDWrite(col, width, row, (void *)font + cb * ('-' - startChar), cb);
                OLEDFill(col + width, blank, row, height, 0);
                minus=0;
            }
            else{
                OLEDFill(col, cw, row, height, 0);
            }
        }
        col -= cw;
    }
}
void OLEDPrintHex(int col, int row, int dec, unsigned int num, void* font, int startChar, int width, int height, int blank ){    
    int cb = width * height;
    int cw = width + blank;
    unsigned int i, cd;
    i = dec;
    dec--;
    col += cw * dec;
    if(num<0)num=-num;
    while(i--){
        cd = num & 15;
        num >>= 4;
        //if(num || cd || (i == dec)) {
            OLEDWrite(col, width, row, (void *)font + cb * (cd + (cd <= 9 ? 0x30 : 0x37) - startChar), cb);
            OLEDFill(col + width, blank, row, height, 0);
        //}
        //else{
            //OLEDFill(col, cw, row, height, 0);
        //}
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

void OLEDPrintXY(int x, int y, const char * s, int num, void * font, int startChar, int width, int height, int blank){
    int cb = width * height;
    if(num == 0) num = 128;
    while(num--){
        if(s[0] == 0) break;
        OLEDWriteXY(x, width, y, (void *)font + cb * (s[0] - startChar), cb);
        x += width;
        OLEDFillGr(x, blank, y, height, 0);
        x += blank;
        s++;
    }
}
#undef _OLED_C
