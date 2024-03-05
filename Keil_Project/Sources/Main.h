
/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.h
** Last modified Date:  2011-12-01
** Last Version:        V1.00
** Descriptions:        main配置文件
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2011-12-01
** Version:             V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
** Rechecked by:
*********************************************************************************************************/
#ifndef __MAIN_H
#define __MAIN_H

#include "includeall.h"

#ifdef __cplusplus
{
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
#if DEBUG_PROJECT_PRINT_EN
#define PrintUart(n)    UART_SendByte(n);//DelayMS(5);
#define PrintDec(n)                     Print(0x30 + (n/1000)%10);  \
                                        Print(0x30 + (n/100)%10);   \
                                        Print(0x30 + (n/10)%10);    \
                                        Print(0x30 + (n%10));       \
                                        Print('\n');                \
                                        Print('\r');
#else
#define PrintUart(n)        NOP();
#define PrintDec(n)         NOP();
#endif

#if DEBUG_PROJECT_PRINT_EN
#define PrintCan0(ucDat)                                                                        PrintCan(CAN0, 0x667, 1, ucDat, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
#define PrintCan0xx(ulID, ucDat0, ucDat1, ucDat2, ucDat3, ucDat4, ucDat5, ucDat6, ucDat7)       PrintCan(CAN0, ulID,  8, ucDat0, ucDat1, ucDat2, ucDat3, ucDat4, ucDat5, ucDat6, ucDat7);
#define PrintCan1(ucDat)                                                                        PrintCan(CAN1, 0x667, 1, ucDat, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
#define PrintCan1xx(ulID, ucDat0, ucDat1, ucDat2, ucDat3, ucDat4, ucDat5, ucDat6, ucDat7)       PrintCan(CAN1, ulID,  8, ucDat0, ucDat1, ucDat2, ucDat3, ucDat4, ucDat5, ucDat6, ucDat7);
#else
#define PrintCan0(ucDat)                                                                        NOP();
#define PrintCan0xx(ulID, ucDat0, ucDat1, ucDat2, ucDat3, ucDat4, ucDat5, ucDat6, ucDat7)       NOP();
#define PrintCan1(ucDat)                                                                        NOP();
#define PrintCan1xx(ulID, ucDat0, ucDat1, ucDat2, ucDat3, ucDat4, ucDat5, ucDat6, ucDat7)       NOP();
#endif
/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/

/*********************************************************************************************************
** 函数声明
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    PrintCan(CAN_Type *canType, INT32U ulID, INT8U ulLen, INT8U ucDat0, INT8U ucDat1, INT8U ucDat2, INT8U ucDat3, INT8U ucDat4, INT8U ucDat5, INT8U ucDat6, INT8U ucDat7);

/******************************************* Private Function *******************************************/
static  void                    SysInit(void);
static  void                    SysTask(void);
static  void                    SpeTask(void);
static  void                    SysMonitor(void);

/*********************************************************************************************************
**
*********************************************************************************************************/

#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __MAIN_H                    */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
