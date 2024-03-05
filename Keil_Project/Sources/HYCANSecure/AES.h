//////////////////////////////////////////////////////////////////////
//
// AES.h: interface for the AES class(based on 128bit algorithm).
//
//////////////////////////////////////////////////////////////////////

#ifndef AES_H
#define AES_H

#include <string.h>
#include <stdio.h>

#ifdef  __cplusplus
extern "C" {
#endif

	void AES_Init(const unsigned char* key);				//key(128bit)
	unsigned char* AES_Cipher(unsigned char* ioput);		//encryption method(128bit)
	unsigned char* AES_InvCipher(unsigned char* ioput);		//Decryption method(128bit)

#ifdef  __cplusplus
}
#endif
	
#endif /*AES_H*/
