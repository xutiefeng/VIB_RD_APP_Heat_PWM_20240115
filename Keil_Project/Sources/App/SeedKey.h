//////////////////////////////////////////////////////////////////////
//
// SeedKey.h: interface for the SeedKey(based on 32bit algorithm).
//
//////////////////////////////////////////////////////////////////////

#ifndef SEEDKEY_H
#define SEEDKEY_H

#include <string.h>
#include <stdio.h>

#include "AES.h"
#include "ECU_Variant.h"

#ifdef  __cplusplus
extern "C" {
#endif

	int  Seed2Key(	const unsigned char*	iSeedArray,			/* Array for the seed [in] */
					const unsigned short	iSeedArraySize,		/* Length of the array for the seed [in] */
					const unsigned int		iSecurityLevel,		/* Security level [in] */
					const char*				iVariant, 			/* Name of the active variant [in] */
					unsigned char*			ioKeyArray, 		/* Array for the key [in, out] */
					unsigned int			iKeyArraySize,		/* Maximum length of the array for the key [in] */
					unsigned int*			oSize); 			/* Length of the key [out] */

#ifdef  __cplusplus//
}
#endif
	
#endif /*SEEDKEY_H*/
