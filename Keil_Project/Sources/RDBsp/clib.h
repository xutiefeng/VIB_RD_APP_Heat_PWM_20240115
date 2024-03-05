#ifndef CLIB_H
#define CLIB_H

#include "globe.h"


unsigned char	PopEvent(void);
void    PushEvent(unsigned char	 event);
void	EventCollect(void) ;
void    ClibInit(void);


#endif
