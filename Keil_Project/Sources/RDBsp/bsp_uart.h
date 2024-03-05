/* 
 * File:   bsp_uart.h
 * Author: lix
 *
 * Created on 2022?11?16?, ??3:45
 */

#ifndef BSP_UART_H
#define	BSP_UART_H


#include "globe.h"

#ifdef	__cplusplus
extern "C" {
#endif

void RDUART0_RcvByte(void);
void BSP_UART_Init(void);	


#ifdef	__cplusplus
}
#endif

#endif	/* BSP_UART_H */

