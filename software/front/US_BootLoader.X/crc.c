#include <GenericTypeDefs.h>

UINT16 CalculateCRC(UINT16 scrc, UINT8 *data, UINT32 len)
{
	static const UINT16 crc_table[16] =
	{
	    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
	};
    UINT32 i;

    while(len--)
    {
        i = (scrc >> 12) ^ (*data >> 4);
	scrc = crc_table[i & 0x0F] ^ (scrc << 4);
	i = (scrc >> 12) ^ (*data >> 0);
	scrc = crc_table[i & 0x0F] ^ (scrc << 4);
	data++;
    }
    return scrc;
}

