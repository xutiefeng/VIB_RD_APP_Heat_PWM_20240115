/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           DiagSid.h
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
#ifndef __DIAGSID_H
#define __DIAGSID_H

#include "includeall.h"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
typedef void                            (*DiagSid_DealFun)(volatile DiagContextStruct *pContext);

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
extern  void                    DiagSid_Deal10(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal11(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal14(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal19(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal22(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal27(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal28(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal2E(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal2F(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal31(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal3E(volatile DiagContextStruct *pContext);
extern  void                    DiagSid_Deal85(volatile DiagContextStruct *pContext);

/******************************************* Private Function *******************************************/


/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __DIAGSID_H                 */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
