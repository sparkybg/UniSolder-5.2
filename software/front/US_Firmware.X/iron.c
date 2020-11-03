#define _IRON_C
#include "iron.h"
#include "isr.h"
#include "mcu.h"
#include "PID.h"
               //ID       1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25
               //ID(HEX) 01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F   10   11   12   13   14   15   16   17   18   19
               //R      100  110  120  130  150  180  200  220  240  270  300  330  390  430  470  560  680  820   1K  1.2K 1.5k  2k   3k  5.6k inf.
const UINT16 IDHash[25] = { 87,  95, 104, 112, 123, 143, 161, 175, 188, 204, 223, 241, 264, 291, 310, 338, 380, 425, 470, 516, 563, 620, 690, 774, 875};


const t_IronPars NoIronPars = {
    0, 
    0x0000,
    "NO INSTRUMENT           ",
    {
        {
            255,                    //Type
            {
                0,                  //HChannel
                5,                  //SChannel
                1,                  //CBandA
                1,                  //CBandB
            },
            128,                    //CurrentA
            128,                    //CurrentB
            0,                      //HRCompCurrent
            128,                    //Gain
            0,                      //Offset
            {                       //TPoly
                0,                  //c0
                0,                  //c1
                0,                  //c2
                0,                  //c3
                0,                  //c4
                0,                  //c5
                0,                  //c6
                0,                  //c7
                0,                  //c8
                0                   //c9
            },
            0,                      //WSLength
            0,                      //PID_DGain
            0,                      //PID_KP
            0,                      //PID_KI
            0,                      //PID_OVSGain
            0,                      //PID_PMax
            0,                      //PID_PNom        
        },
        {0}
    }
};

const t_IronPars Irons[12] = {
    {
        0, 
        0x1011,
        "PACE TD-100 BLACK       ",
        {
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                0,                          //CurrentA
                10,                         //CurrentB
                10,                         //HRCompCurrent
                120,                        //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    61,                     //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                -1,                         //WSLength
                4,                          //PID_DGain
                (UINT16)(0.07 * 32768),     //PID_KP
                (UINT16)(0.001 * 32768),    //PID_KI
                4,                          //PID_OVSGain
                120,                        //PID_PMax
                120                         //PID_PNom
            },
            {0}
        }
    },
    {
        0, 
        0x0F11,
        "PACE TD-200 BLUE        ",
        {
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                0,                          //CurrentA
                10,                         //CurrentB
                10,                         //HRCompCurrent
                53,                         //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    27.7,                   //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                -1,                         //WSLength
                3,                          //PID_DGain
                (UINT16)(0.2 * 32768),      //PID_KP
                (UINT16)(0.005 * 32768),    //PID_KI
                6,                          //PID_OVSGain
                120,                        //PID_PMax
                120                         //PID_PNom
            },
            {0}
        }
    },
    
    {
        0,
        0x1813,
        "HAKKO T15               ",
        {//--Type----HChannel----SChannel----CBand----CurrentA----CurrentB----HRCompCurrent---Gain----Offset--SoftGain----SoftOffset--WSLength----PID_DGain---PID_KP--------------------PID_KI--------------------PID_OVFGain-PID_PMax
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                10,                         //CurrentA
                0,                          //CurrentB
                10,                         //HRCompCurrent
                100,                        //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    50.1,                   //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                -1,                         //WSLength
                2,                          //PID_DGain
                (UINT16)(0.08 * 32768),     //PID_KP
                (UINT16)(0.0015 * 32768),   //PID_KI
                3,                          //PID_OVSGain
                70,                         //PID_PMax
                60                          //PID_PNom
            },
            {0}
        }
    },

    {
        0, 
        0x1213,
        "HAKKO FX8801            ",
        {//-----------------------------------------------------------------------------------------
            {
                2,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },                          
                205,                        //CurrentA
                0,                          //CurrentB
                0,                          //HRCompCurrent
                13,                         //Gain
                331,                        //Offset
                {                           //TPoly
                    -165.5,                 //c0
                    3.98513793,             //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                0,                          //WSLength
                20,                         //PID_DGain
                (UINT16)(0.4 * 32768),      //PID_KP
                (UINT16)(0.02 * 32768),     //PID_KI
                14,                         //PID_OVSGain
                65,                         //PID_PMax
                65                          //PID_PNom
            },
            {0}
        }
    },

    {
        0,
        0x0501,
        "CHIN. HAKKO 907         ",
        {
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                10,                         //CurrentA
                0,                          //CurrentB
                0,                          //HRCompCurrent
                49,                         //Gain
                0,                          //Offset
                {                           //TPoly (TC Type K)
                    0,                      //c0
                    2.508355e+1,            //c1
                    7.860106e-2,            //c2
                   -2.503131e-1,            //c3
                    8.315270e-2,            //c4
                   -1.228034e-2,            //c5
                    9.804036e-4,            //c6
                   -4.413030e-5,            //c7
                    1.057734e-6,            //c8
                   -1.052755e-8             //c9
                },
                0,                          //WSLength
                11,                         //PID_DGain
                (UINT16)(0.4 * 32768),      //PID_KP
                (UINT16)(0.01 * 32768),     //PID_KI
                16,                         //PID_OVSGain
                50,                         //PID_PMax
                50                          //PID_PNom
            },
            {0}
        }
    },

    {
        0, 
        0x1805,
        "JBC C245                ",
        {
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    7,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                0,                          //CurrentA
                10,                         //CurrentB
                0,                          //HRCompCurrent
                87,                         //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    43.5,                   //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                1,                          //WSLength
                11,                         //PID_DGain
                (UINT16)(0.3 * 32768),      //PID_KP
                (UINT16)(0.003 * 32768),    //PID_KI
                10,                         //PID_OVSGain
                130,                        //PID_PMax
                130                         //PID_PNom
            },
            {0}
        }
    },

    {
        0, 
        0x1817,
        "JBC C210                ",
        {
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    7,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                10,                         //CurrentA
                0,                          //CurrentB
                10,                         //HRCompCurrent
                202,                        //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    126.25,                 //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },

                -1,                         //WSLength
                1,                          //PID_DGain
                (UINT16)(0.25 * 32768),     //PID_KP
                (UINT16)(0.003 * 32768),    //PID_KI
                4,                          //PID_OVSGain
                40,                         //PID_PMax
                40                          //PID_PNom
            },
            {0}
        }
    },
    {
        0, 
        0x1317,
        "JBC C105/C115           ",
        {
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                10,                         //CurrentA
                0,                          //CurrentB
                10,                         //HRCompCurrent
                170,                        //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    101.9,                  //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },

                -1,                         //WSLength
                1,                          //PID_DGain
                (UINT16)(0.25 * 32768),     //PID_KP
                (UINT16)(0.003 * 32768),    //PID_KI
                4,                          //PID_OVSGain
                14,                         //PID_PMax
                14                          //PID_PNom
            },
            {0}
        }
    },

    {
        0, 
        0x1313,
        "JBC Microtweezers       ",
        {
            {
                1,                          //Type
                {
                    1,                      //HChannel
                    2,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
//                    3                       //CBand
                },
                0,                          //CurrentA
                10,                         //CurrentB
                10,                         //HRCompCurrent
                202,                        //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    126.25,                 //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                -1,                         //WSLength
                1,                          //PID_DGain
                (UINT16)(0.25 * 32768),      //PID_KP
                (UINT16)(0.004 * 32768),    //PID_KI
                4,                          //PID_OVSGain
                40,                         //PID_PMax
                40                          //PID_PNom
            },
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                10,                         //CurrentA
                0,                          //CurrentB
                10,                         //HRCompCurrent
                202,                        //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    126.25,                 //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                -1,                         //WSLength
                1,                          //PID_DGain
                (UINT16)(0.25 * 32768),     //PID_KP
                (UINT16)(0.004 * 32768),    //PID_KI
                4,                          //PID_OVSGain
                40,                         //PID_PMax
                40                          //PID_PNom
            }
        }
    },
    {
        0, 
        0x1111,
        "Weller WMRT             ",
        {
            {
                1,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
//                    3                       //CBand
                },
                0,                          //CurrentA
                0,                          //CurrentB
                0,                          //HRCompCurrent
                128,                        //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    67.95,                 //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                0,                          //WSLength
                1,                          //PID_DGain
                (UINT16)(0.25 * 32768),     //PID_KP
                (UINT16)(0.004 * 32768),    //PID_KI
                4,                          //PID_OVSGain
                40,                         //PID_PMax
                40                          //PID_PNom
            },
            {
                1,                          //Type
                {
                    1,                      //HChannel
                    2,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                0,                          //CurrentA
                0,                          //CurrentB
                0,                          //HRCompCurrent
                128,                        //Gain
                0,                          //Offset
                {                           //TPoly
                    0,                      //c0
                    67.95,                  //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                0,                          //WSLength
                1,                          //PID_DGain
                (UINT16)(0.025 * 32768),    //PID_KP
                (UINT16)(0.004 * 32768),    //PID_KI
                4,                          //PID_OVSGain
                40,                         //PID_PMax
                40                          //PID_PNom
            }
        }
    },

    {
        0, 
        0x1803,
        "WELLER WSP80            ",
        {
            {
                2,                          //Type
                {                           
                    0,                      //HChannel
                    5,                      //SChannel
                    1,                      //CBandA
                    1,                      //CBandB
                },
                195,                        //CurrentA
                0,                          //CurrentB
                0,                          //HRCompCurrent
                49,                         //Gain
                627,                        //Offset
                {                           //TPoly
                    -313.5,                 //c0
                    14.2881775,             //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },

                0,                          //WSLength
                30,                         //PID_DGain
                (UINT16)(0.2 * 32768),      //PID_KP
                (UINT16)(0.008 * 32768),    //PID_KI
                4,                          //PID_OVSGain
                80,                         //PID_PMax
                80                          //PID_PNom
            },
            {0}
        }
    },
    
    {
        0, 
        0x020B,
        "ERSA RT80               ",
        {//-----------------------------------------------------------------------------------------
            {
                2,                          //Type
                {
                    0,                      //HChannel
                    5,                      //SChannel
                    0,                      //CBandA
                    1,                      //CBandB
                },                          
                167,                        //CurrentA
                0,                          //CurrentB
                0,                          //HRCompCurrent
                21,                         //Gain
                284,                        //Offset
                {                           //TPoly
                    -145.7299,              //c0
                    86.2582,                //c1
                    0,                      //c2
                    0,                      //c3
                    0,                      //c4
                    0,                      //c5
                    0,                      //c6
                    0,                      //c7
                    0,                      //c8
                    0                       //c9
                },
                -1,                        //WSLength
                0,                         //PID_DGain
                (UINT16)(0.4 * 32768),     //PID_KP
                (UINT16)(0.02 * 32768),    //PID_KI
                4,                         //PID_OVSGain
                80,                        //PID_PMax
                80                         //PID_PNom
            },
            {0}
        }
    }    
};

volatile int IronTicks;

void IronIdentify(){
    static UINT16_VAL OID;
    static UINT8 IDCnt;
    UINT16_VAL CID;
    UINT16_VAL NewIronID;
    int i;
    UINT16 w;

    ISRStop();

    I2CData.CurrentA.ui16 = 0;
    I2CData.CurrentB.ui16 = 0;
    I2CAddCommands(I2C_SET_CPOT);
    CBANDA = 1;
    CBANDB = 1;
    while(!I2CIdle);

    HCH = 0;
    ID_3S = 1;
    ID_OUT = 1;
    mcuADCStartManual();
    mcuADCRefVdd();

    _delay_us(1000);
    w = mcuADCReadWait(ADCH_ID, 16) >> 4;
    HCH = 1;
    for(i = 0; i <= 24; i++)if(w < IDHash[i])break;
    CID.v[0] = i;

    _delay_us(1000);
    w = mcuADCReadWait(ADCH_ID, 16) >> 4;
    HCH=0;
    for(i = 0; i <= 24; i++)if(w < IDHash[i])break;
    CID.v[1] = i;
    
    mcuADCRefVref();

    NewIronID.Val = 0x1919;
    if(CID.Val == OID.Val){
        if(IDCnt < 255)IDCnt++;
        if(IDCnt > 2)NewIronID.Val = CID.Val;
    }
    else{
        IDCnt = 0;
    }
    OID.Val = CID.Val;
    
    if(NewIronID.v[0] >= 0x19)NewIronID.v[0] = NewIronID.v[1];
    if(NewIronID.v[1] >= 0x19)NewIronID.v[1] = NewIronID.v[0];

    if(NewIronID.Val != 0x1919){
        if(IronID != NewIronID.Val){
            IronPars = NoIronPars;
            for(i = 2; i--; ){
                PIDVars[i].HR = 0x7FFF;
                PIDVars[i].HNewData = 0;
                PIDVars[i].HInitData = 1;
                PIDVars[i].HP = 0;
                PIDVars[i].HI = 0;
                PIDVars[i].HV = 0;
                PIDVars[i].OffDelay = 1600;
            }
            for(i = (sizeof(Irons) / sizeof(Irons[0])); i--; ){
                if(Irons[i].ID.Val == NewIronID.Val){
                    IronPars = Irons[i];
                    for(i = 2; i--; )PIDVars[i].HR = 8;
                    break;
                }
            }
            PIDInit();
        }
    }
    else{
        if(IronID != 0x1919)IronPars = NoIronPars;
        for(i = 2; i--; ){
            PIDVars[i].HInitData = 1;
            PIDVars[i].HP = 0;
            PIDVars[i].HI = 0;
            PIDVars[i].HV = 0;
            PIDVars[i].OffDelay = 1600;
        }
    }
    IronID = NewIronID.Val;
    ID_OUT = 0;
    ID_3S = 0;
    ISRStart();
}

void IronInit(){
    IronID = 0x1919;
    IronPars = NoIronPars;
}

void IronTasks(){
    int i;
    if(IronTicks != ISRTicks){
        IronTicks = ISRTicks;
        if((IronTicks & 15) == 15){
            switch(IronID){
                case 0x1919:
                    IronIdentify();
                    break;
                default:
                    for(i = 2; i--;){
                        if(IronPars.Config[i].Type && (PIDVars[i].NoSensor || PIDVars[i].NoHeater)){
                            IronIdentify();
                            break;
                        }
                    }
                    break;
            }
        }
    }
}

#undef _IRON_C
