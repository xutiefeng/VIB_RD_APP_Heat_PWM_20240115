#ifndef sysRun_H
#define sysRun_H

//#include "includeall.h"
#include "RDBsp\bsp_uart.h"
//BOOLEAN LPUART0_SenBuf(INT8U *pucDat, INT32U ulLen)
void sysRuning(void);
void CAN_22_2E_FillData(void);
void SetPause(void);
#define  BSP_UART_TxData     LPUART0_SenBuf//SERCOM0_USART_Write

#endif
