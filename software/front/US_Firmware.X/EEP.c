#define _EEP_C

#include "isr.h"

void EEPWrite(UINT16 a, UINT8 * b, UINT16 c){
    if(c){
        while(EEPAddrW != 0xFFFF){};
        EEPAddrW = a;
        EEPDataW = b;
        EEPCntW = c;
        I2CAddCommands(I2C_EEPWRITE);
        while(EEPAddrW != 0xFFFF){};
    }
}

void EEPWriteImm(UINT16 a, UINT8 b){
        while(EEPAddrW != 0xFFFF){};
        EEPAddrW = a;
        EEPDataW = &b;
        EEPCntW = 1;
        I2CAddCommands(I2C_EEPWRITE);
        while(EEPAddrW != 0xFFFF){};
}

UINT8 EEPRead(UINT16 a, UINT8 * b, UINT16 c){
    UINT8 lb;
    if(c){
        if(b == 0){
            b = &lb;
            c = 1;
        }
        while(EEPAddrR != 0xFFFF);
        EEPAddrR = a;
        EEPDataR = b;
        EEPCntR = c;
        I2CAddCommands(I2C_EEPREAD);
        while(EEPAddrR != 0xFFFF);
        return b[c-1];
    }
    return 0xFF;
}

#undef __EEP_C
