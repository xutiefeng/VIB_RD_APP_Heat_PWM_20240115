//////////////////////////////////////////////////////////////////////
//
// SeedKey.c: implementation of the SeedKey(based on 32bit algorithm).
//
//////////////////////////////////////////////////////////////////////
#include "SeedKey.h"

int  Seed2Key(const unsigned char*  iSeedArray, const unsigned short iSeedArraySize, const unsigned int iSecurityLevel,
	const char* iVariant, unsigned char* ioKeyArray, unsigned int iKeyArraySize, unsigned int *oSize)
{
	unsigned char temp[16] = {0};
	unsigned int Size = 0;
	unsigned char dat = iSecurityLevel;
	unsigned char data[16];
	unsigned char i;

	if (iSecurityLevel != 0x01 && iSecurityLevel != 0x03 && iSecurityLevel != 0x11)
		return 0;

	AES_Init(Var);
	for (i = 0; i < 16; i++)
	{
		temp[i] = dat;
	}
	for (i = 0; i < 4; i++)
	{
		temp[i] = iSeedArray[i];
	}
	AES_Cipher(temp);
	for (i = 0; i < 8; i++)
	{
		data[i] = temp[i] ^ temp[15-i];
	}
	for (i = 0; i < 4; i++)
	{
		data[i] = data[i] ^ data[3 - i];
	}
	for (i = 0; i < 4; i++)
	{
		ioKeyArray[i] = data[i];
	}
	
	*oSize = 4;
	return 1;
}