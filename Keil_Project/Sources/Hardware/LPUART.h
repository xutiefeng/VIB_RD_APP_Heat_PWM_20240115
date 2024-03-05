/****************************************Copyright (c)****************************************************
**                            Guangzhou ZLGMCU Development Co., LTD
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           LPUART.h
** Last modified Date:  2021-05-12
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2021-05-12
** Version:             V1.00
** Descriptions:        
**                      
**--------------------------------------------------------------------------------------------------------
** Modified by:         zhaohai
** Modified date:       2021-05-12
** Version:             
** Descriptions:        
**
** Rechecked by:        
*********************************************************************************************************/
#ifndef __LPUART_H
#define __LPUART_H

#include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
#define EnableIRQ_UartRx()              NOP();//(LPC_UART->IER   |= (1 << 0))
#define DisableIRQ_UartRx()             NOP();//(LPC_UART->IER   &=~(1 << 0))
#define EnableIRQ_UartTx()              NOP();//(LPC_UART->IER   |= (1 << 1))
#define DisableIRQ_UartTx()             NOP();//(LPC_UART->IER   &=~(1 << 1))

#define EnableIRQ_Uart()                EnableIRQ_UartRx(); \
                                        EnableIRQ_UartTx()
#define DisableIRQ_Uart()               DisableIRQ_UartRx();\
                                        DisableIRQ_UartTx()

#define EnableIRQ_UART()                NOP();//NVIC_EnableIRQ(UART_IRQn);
#define DisableIRQ_UART()               NOP();//NVIC_DisableIRQ(UART_IRQn);
#define UART_INT_TX_EN()                NOP()

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/
#define INST_LPUART0					(0U)
extern  const                           lpuart_user_config_t lpuart0_InitConfig0;

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
//extern  volatile CanMbStruct        MbInfo;                             /* 单个邮箱控制信息             */

/*********************************************************************************************************
** 函数声明
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    LPUART0_InitReg(void);
extern  BOOLEAN                 LPUART0_SenByte(INT8U ucDat);
extern  BOOLEAN                 LPUART0_SenBuf(INT8U *pucDat, INT32U ulLen);
extern  void                    LPUART0_RcvByte(void);
extern  void                    LPUART0_RxTx_IRQHandler(void);
extern  void                    LPUART0_RcvDatPolling(INT8U *pucDat, INT32U ulLen);

/******************************************* Private Function *******************************************/
extern  void                    LPUART0_SetBaudRate(INT32U desiredBaudRate);

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __LPUART_H                  */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
