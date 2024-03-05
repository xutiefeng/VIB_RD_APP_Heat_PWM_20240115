
/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Time.h
** Last modified Date:  2011-12-01
** Last Version:        V1.00
** Descriptions:
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
#ifndef __TIME_H
#define __TIME_H

// #include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define OUT                             0xFFFFFFFF                      /* �ѳ�ʱ                       */


/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define SYS_T_UNIT1                     1                               /* ��ʱ��1����1��1ms            */
#define SYS_T_UNIT2                     2                               /* ��ʱ��1����2��2ms            */
#define SYS_T_UNIT3                     50                              /* ��ʱ��2��50us                */

#if 0   /* TIME_WAIT_START ���Խ�� */
INT8U   ucLoop1 = 0xFF;
INT16U  usLoop2 = 0xFFFF;
INT32U  ulLoop3 = 0xFFFF;
while (1) {if (--ucLoop1 == 0)      {break;}}/*48M:0xFF-360us,                     */
while (1) {if (--usLoop2 == 0)      {break;}}/*48M:0xFF-70us,1000-260us,0xFFFF-19ms*/
while (1) {if (--ulLoop3 == 0)      {break;}}/*48M:0xFF-65us,1000-260us,0xFFFF-19ms*/
INT8U   ucLoop4 = 0;
INT16U  usLoop5 = 0;
INT32U  ulLoop6 = 0;
while (1) {if (++ucLoop4 >= 0xFF)   {break;}}/*48M:0xFF-360us,                     */
while (1) {if (++usLoop5 >= 0xFFFF) {break;}}/*48M:0xFF-70us,1000-250us,0xFFFF-19ms*/
while (1) {if (++ulLoop6 >= 0xFFFF) {break;}}/*48M:0xFF-65us,1000-270us,0xFFFF-16ms*/
#endif
#define TIME_WAIT_START(n)               INT32U ulLoop = n;
#define TIME_WAIT_RESTART(n)             ulLoop = n;
#define TIME_WAIT_LOOP()                {if (--ulLoop == 0) {break;}}

#define SysTickNmsCntIsTrue()           SysTickNms
#define SysTickNmsCntDec()              DisableIRQ_Tick(); SysTickNms--;    EnableIRQ_Tick();
#define SysTick10msIsTrue()             (SysTick10ms   >= (10/SYS_T_UNIT2 + 0))
#define SysTick10msClr()                SysTick10ms     = 0;
#define SysTick10msInc()                SysTick10ms++;
#define SysTick100msIsTrue()            (SysTick100ms  >= (100/SYS_T_UNIT2 + 3))
#define SysTick100msClr()               SysTick100ms    = 3;
#define SysTick100msInc()               SysTick100ms++;
#define SysTick1sIsTrue()               (SysTick1s     >= (1000/SYS_T_UNIT2 + 7))
#define SysTick1sClr()                  SysTick1s       = 7;
#define SysTick1sInc()                  SysTick1s++;
/*********************************************************************************************************
** �ṹ��: �㼯�����ܹ�����ʱ����  ��Time_Reset() Time_Out()����ר�á�
*********************************************************************************************************/
typedef struct {
    INT32U                  WaitMS;
    INT32U                  SysSleep;
    INT32U                  EveryN1ms;                                  /* �򵥹�����ʱ                 */
    INT32U                  EveryN2ms;
    INT32U                  EveryN3ms;
    INT32U                  EveryN4ms;
    INT32U                  EveryN5ms;
    INT32U                  EveryN6ms;
    INT32U                  EveryN7ms;
    INT32U                  EveryN8ms;
    /*--------------------------------------------------------------------------------------------------*/
    
    /*--------------------------------------------------------------------------------------------------*/
    INT32U                  Test1;
    INT32U                  Test2;
} TimeStruct;
/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
extern  volatile INT32U             SysTickCnt;
extern  volatile TimeStruct         Time;
extern  volatile INTCPU             SysTickNms;
extern  volatile INTCPU             SysTick10ms;
extern  volatile INTCPU             SysTick100ms;
extern  volatile INTCPU             SysTick1s;

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void    DelayUS(INT16U usDly);
extern  void    DelayMS(INT16U usDly);

extern  INT32U  Time_GetSysTick(void);
extern  void    Time_Reset(volatile INT32U *pTimeVar);
extern  INT32U  Time_Out  (volatile INT32U *pTimeVar, INT32U ucTimeOut);
extern  void    Time_WaitMS(INT32U ucWait);
extern  void    Time_ResetN(volatile INT32U *pTimeVar, volatile INT32U *pTimeVarCnt);
extern  INT32U  Time_OutN  (volatile INT32U *pTimeVar, volatile INT32U *pTimeVarCnt, INT32U ucTimeOut, INT32U ucTimeOutCnt);

extern  void    Time_Init(void);

/******************************************* Private Function *******************************************/

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __TIME_H                    */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
