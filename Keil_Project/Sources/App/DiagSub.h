/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           DiagSub.h
** Last modified Date:  2019-02-11
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2019-02-11
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
#ifndef __DIAGSUB_H
#define __DIAGSUB_H

#include "includeall.h"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/

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
extern  DIAG_NRC_ENUM           DiagSub_Deal14(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal1901(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal1902(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal1904(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal1906(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal190A(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal22(volatile DiagContextStruct *pContext);

extern  DIAG_NRC_ENUM           DiagSub_Deal2701(volatile DiagContextStruct *pContext);  /* DKLai20230420 */
extern  DIAG_NRC_ENUM           DiagSub_Deal2702(volatile DiagContextStruct *pContext);
extern  void                    DiagSub_Deal2761(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal2762(volatile DiagContextStruct *pContext);

extern  DIAG_NRC_ENUM           DiagSub_Deal2E(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal2F(volatile DiagContextStruct *pContext);
extern  DIAG_NRC_ENUM           DiagSub_Deal31(volatile DiagContextStruct *pContext);

/******************************************* Private Function *******************************************/
static  void                    CalculateRandom(void);
static  void                    CalculateKey(DIAG_SECURITY_ENUM euLevel);
static  INT32U                  CalculateKey_L1(INT32U ulSeed);
static  INT32U                  CalculateKey_L2(INT32U ulSeed);
static  INT32U                  CalculateKey_LFbl(INT32U ulSeed);

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __DIAGSUB_H                 */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
