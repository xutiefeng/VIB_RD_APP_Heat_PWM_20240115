/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           SYS.h
** Last modified Date:  2012-06-01
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2012-06-01
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
#ifndef __SYS_H
#define __SYS_H

// #include "includeall.h"
#include "lptmr_driver.h"
#include "lpTmr1.h"
#include "flexTimer_mc1.h"
#include "ftm_common.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define SYSTICK_USE_LPTMR               0                               /* ����ʹ�õĶ�ʱ��             */

/* Definition of power modes indexes, as configured in Power Manager Component
 *  Refer to the Reference Manual for details about the power modes.
 */
#define RUN   (0u) /* Run                 */
//#define VLPR  (1u) /* Very low power run  */
//#define STOP1 (2u) /* Stop option 1       */
//#define STOP2 (3u) /* Stop option 2       */
#define VLPS  (1u) /* Very low power stop */

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
extern  volatile ftm_state_t        ftmStateStruct;

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void    SYS_Init(void);
extern  void    PORT_Init(void);
#if !SYSTICK_USE_LPTMR
extern  void    SysTick_Config(INT32U ulTick);
#else
extern  void    LPTMR_Config(void);
#endif
extern  void    FTM_Config(void);
extern void   PORT_FactoryInit(void);
extern void   PORT_RecoverInit(void);
/******************************************* Private Function *******************************************/

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __SYS_H                     */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/