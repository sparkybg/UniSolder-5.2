#define _OLED_C

#include "mcu.h"
#include "OLED.h"
#include "typedefs.h"


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
    0x81, 0xFF,  //max brightness
            
    //0x20,0x02,  //set page addressing mode //no need - state after reset
};

typedef union {
    struct __PACKED {
        struct __PACKED{
            UINT8 Row;
            UINT8 ColHi;
            UINT8 ColLow;
        } PreRowUpdate;
    };
}preUpdate_t;

preUpdate_t PreUpdateBuff = {
    {{0xB0,0x10,0}}
};

void OLEDInit(){
    mcuSPIClose();
    OLED_VCC = 1;   //Turn off display VCC
    OLED_VDD = 1;   //Turn off display VDD
    OLED_RES = 0;   //Reset display
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
                
    OLED_CS_3S = 1; //Everything but reset - 3state
    OLED_DC_3S = 1;  
    SDI_3S = 1;
    SDO_3S = 1;
    SCK_3S = 1;        
    OLED_VDD = 0;   //Turn on display VDD 
    OLED_CS_PU = 1; //Enable internal pull-up on CS in order to check if resistor between CS and GND is installed
    OLED_DC_PU = 1; //Enable internal pull-up on D/C in order to check if resistor between OLED_RES and OLED_DC is installed
    _delay_ms(100);

    DisplaySetup.SH1106 = !OLED_CS_IN;              //If CS pull-down resistor is installed, OLED_CS will be low => display controller is SH1106    
    DisplaySetup.InternalChargePump = !OLED_DC_IN;  //If resistor between OLED_DC and OLED-RES is installed, it will dominate and OLED_DC will be low => display uses internal charge pump.
    
    OLED_CS_PU = 0; //Bring all IOs to operational state (outputs, no internal pull-ups)
    OLED_DC_PU = 0;
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
    
    mcuSPISendBytes((unsigned int*)OLEDInitBuff1, sizeof(OLEDInitBuff1));
    mcuSPIWait();
    if(DisplaySetup.SH1106){
        PreUpdateBuff.PreRowUpdate.ColLow = 2; //SSH1106 is 131x64 - shift right by 2
        mcuSPISendByte(0xAD); //charge pump control       
        mcuSPISendByte(DisplaySetup.InternalChargePump ? 0x8B : 0x8A);
    }
    else{
        PreUpdateBuff.PreRowUpdate.ColLow = 0; //SSD1306 is 128x64 - no need to shift
        mcuSPISendByte(0x8D); //charge pump control       
        mcuSPISendByte(DisplaySetup.InternalChargePump ? 0x14 : 0x10);
    }
    mcuSPIWait();
    mcuSPISendBytes((unsigned int*)OLEDInitBuff2, sizeof(OLEDInitBuff2));     
}

void OLEDUpdate(){
    UINT8 r;
    for(r=0;r<=7;r++ ){
        PreUpdateBuff.PreRowUpdate.Row = 0xB0 + r;
        mcuSPIWait();       
        OLED_DC = 0;
        OLED_CS = 0;
        mcuSPISendBytes((unsigned int*)&PreUpdateBuff.PreRowUpdate, sizeof(PreUpdateBuff.PreRowUpdate));
        mcuSPIWait();
        OLED_DC = 1;    
        mcuSPISendBytes((unsigned int*)OLEDBUFF.B[r], 128 );
    }
}
#undef _OLED_C
