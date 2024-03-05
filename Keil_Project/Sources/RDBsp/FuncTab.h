#ifndef FUNCTAB_H
#define FUNCTAB_H

#include "RDBsp\globe.h"



#define LONG_TO_BIN(n)                       \
                     (                       \
                       ((n >> 21) & 0x80) |  \
                       ((n >> 18) & 0x40) |  \
                       ((n >> 15) & 0x20) |  \
                       ((n >> 12) & 0x10) |  \
                       ((n >> 9)  & 0x08) |  \
                       ((n >> 6)  & 0x04) |  \
                       ((n >> 3)  & 0x02) |  \
                       ((n )      & 0x01)    \
                     )

#define BIN(n) LONG_TO_BIN(0x##n##l)
#define B(n)   BIN(n)
#define b(n)   BIN(n)

#define  LING_MIN_DU 30
#define TAB_LENGTH  11
#define TAB_SIZE  22
extern  volatile STSetVaue  TemprertureTab[] ;
extern const  volatile STSetVaue  ImageTemprertureTab[] ;
extern STLingMin  gstLingMinConfig[] ;

#define  TAB_ISUM(x)              sizeof(x)//(sizeof(x)/sizeof(x[0]))
//extern u8 dgg[2];
#endif


