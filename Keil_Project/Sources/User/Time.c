/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Time.c
** Last modified Date:  2011-12-01
** Last Version:        V1.00
** Descriptions:        ʱ�����
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
#include "includeall.h"

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
volatile INT32U             SysTickCnt  = 0;
volatile TimeStruct         Time;
volatile INTCPU             SysTickNms;
volatile INTCPU             SysTick10ms;
volatile INTCPU             SysTick100ms;
volatile INTCPU             SysTick1s;

#if 1
/*********************************************************************************************************
** Function name:       DelayUS
** Descriptions:        ΢����ʱ��S32K116:CPU = 40MHzʱ��
** input parameters:    �����±�
** output parameters:   ��
** Returned value:      ��
** Reference value:
**                         1 ->    2.1 us
**                        10 ->   11.0 us
**                        20 ->   20.8 us
**                        50 ->   51   us
**                       100 ->  101   us
*********************************************************************************************************/
void    DelayUS(INT16U usDly)
{
    INT8U   i;
    for(; usDly > 0; usDly--) {
        for (i = 3; i > 0; i--) {
            NOP();NOP();
        }
    }
}
#elif 0
/*********************************************************************************************************
** Function name:       DelayUS
** Descriptions:        ΢����ʱ��S32K116:CPU = 16MHzʱ��
** input parameters:    �����±�
** output parameters:   ��
** Returned value:      ��
** Reference value:
**                         1 ->    4.5 us
**                        10 ->   14.1 us
**                       100 ->  103.6 us
**                       200 ->  204   us
**                       250 ->  253   us
*********************************************************************************************************/
void    DelayUS(INT16U usDly)
{
    for(; usDly > 0; usDly--) {
            NOP();NOP();NOP();NOP();
    }
}
#else
/*********************************************************************************************************
** Function name:       DelayUS
** Descriptions:        ΢����ʱ��S32K142:CPU = 48MHzʱ��
** input parameters:    �����±�
** output parameters:   ��
** Returned value:      ��
** Reference value:
**                         1 ->    1.7 us
**                        10 ->   10.6 us
**                       100 ->   98   us
**                       200 ->  197   us
**                       250 ->  246   us
*********************************************************************************************************/
void    DelayUS(INT16U usDly)
{
    INT8U   i;
    for(; usDly > 0; usDly--) {
        for (i = 3; i > 0; i--) {
            NOP();
        }
    }
}
#endif
/*********************************************************************************************************
** Function name:       DelayMS
** Descriptions:        ������ʱ
** input parameters:    usDly:
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    DelayMS(INT16U usDly)
{
    for(; usDly > 0; usDly--) {
        DelayUS(250);CLRWDT();
        DelayUS(250);CLRWDT();
        DelayUS(250);CLRWDT();
        DelayUS(250);CLRWDT();
    }
}
/*****************************************************************************************************************
** ��λ: 1ms
*****************************************************************************************************************/
/*********************************************************************************************************
** Function name:       Time_GetSysTick
** Descriptions:        ��ȡϵͳ����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
INT32U  Time_GetSysTick(void)
{
    INT32U  ulTmp;
    
    DisableIRQ_Tick();
    ulTmp           = SysTickCnt;
    EnableIRQ_Tick();
    
    return ulTmp;
}
/*********************************************************************************************************
** Function name:       Time_Reset
** Descriptions:        ��λ��ʱ����
** input parameters:    *pTimeVar:      ��ʱ����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    Time_Reset(volatile INT32U *pTimeVar)
{
    *pTimeVar       = Time_GetSysTick();                                /* ��λ��ʱ����                 */
}
/*********************************************************************************************************
** Function name:       Time_Out
** Descriptions:        �����·��ʱ
** input parameters:    *pTimeVar:      ��ʱ����
**                      ucTimeOut:      ��ʱ���
** output parameters:   ��
** Returned value:      0<=N<0xFFFFFFFF:��ǰʵ����ʱ(N����ʱ��λ) 0xFFFFFFFF:��ʱ��
*********************************************************************************************************/
INT32U   Time_Out(volatile INT32U *pTimeVar, INT32U ucTimeOut)
{
    INT32U uldiff;
    
    if (ucTimeOut == OUT) {
        return 0;
    }
    uldiff      = Time_GetSysTick() - *pTimeVar;                        /* ���㶨ʱʱ����             */
    if (uldiff >= ucTimeOut) {                                          /* ��ʱʱ�䵽                   */
        *pTimeVar = Time_GetSysTick();                                  /* ���¶�ʱ��������ʼ��һ�ζ�ʱ */
        return OUT;
    } else {
        return uldiff;
    }
}
/*********************************************************************************************************
** Function name:       Time_WaitMS
** Descriptions:        ��ʱ����ʱ,��Ҫ������ DelayMS()
** input parameters:    ulWait:     ��ʱN����ʱ��λ
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    Time_WaitMS(INT32U ulWait)
{
    Time_Reset(&Time.WaitMS);
    while(OUT != Time_Out(&Time.WaitMS, ulWait)) {
        /* ������� */
        
    }
}
/*********************************************************************************************************
** Function name:       Time_ResetN
** Descriptions:        ��λ��ʱ����
** input parameters:    *pTimeVar:      ��ʱ����
**                      *pTimeVarCnt:   ��ʱ����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    Time_ResetN(volatile INT32U *pTimeVar, volatile INT32U *pTimeVarCnt)
{
    *pTimeVar       = Time_GetSysTick();                                /* ��λ��ʱ����                 */
    *pTimeVarCnt    = 0;                                                /* ��λ��ʱ����                 */
}
/*********************************************************************************************************
** Function name:       Time_OutN
** Descriptions:        �����·��ʱ
** input parameters:    *pTimeVar:      ��ʱ����
**                      *pTimeVarCnt:   ��ʱ����
**                      ucTimeOut:      ��ʱ���
**                      ucTimeOutCnt:   ��ʱ����
** output parameters:   ��
** Returned value:      0<=N<0xFFFFFFFF:��ǰʵ����ʱ(N����ʱ����) 0xFFFFFFFF:��ʱ��
*********************************************************************************************************/
INT32U   Time_OutN(volatile INT32U *pTimeVar, volatile INT32U *pTimeVarCnt, INT32U ucTimeOut, INT32U ucTimeOutCnt)
{
    INT32U uldiff;
    
    if (ucTimeOut == OUT) {
        return 0;
    }
    uldiff      = Time_GetSysTick() - *pTimeVar;                        /* ���㶨ʱʱ����             */
    if (uldiff >= ucTimeOut) {                                          /* ��ʱʱ�䵽                   */
        *pTimeVar   = Time_GetSysTick();                                /* ���¶�ʱ��������ʼ��һ�ζ�ʱ */
        (*pTimeVarCnt)++;
    }
    if (*pTimeVarCnt >= ucTimeOutCnt) {
        *pTimeVarCnt  = 0;
        return OUT;
    } else {
        return ucTimeOutCnt;
    }
}
/*********************************************************************************************************
** Function name:       Time_Init
** Descriptions:        ��ʱ������ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    Time_Init(void)
{
    Time_Reset(&Time.EveryN1ms);
    Time_Reset(&Time.EveryN2ms);
    Time_Reset(&Time.EveryN3ms);
    Time_Reset(&Time.EveryN4ms);
    Time_Reset(&Time.EveryN5ms);
    Time_Reset(&Time.EveryN6ms);
    Time_Reset(&Time.EveryN7ms);
    Time_Reset(&Time.EveryN8ms);
    /* �����ã���Ϊ�����ڵ�ǰTick
    Time.EveryN2ms  = Time.EveryN1ms + 3*1;
    Time.EveryN3ms  = Time.EveryN1ms + 3*2;
    Time.EveryN4ms  = Time.EveryN1ms + 3*3;
    Time.EveryN5ms  = Time.EveryN1ms + 3*4;
    Time.EveryN6ms  = Time.EveryN1ms + 3*5;
    Time.EveryN7ms  = Time.EveryN1ms + 3*6;
    Time.EveryN8ms  = Time.EveryN1ms + 3*7;
    */
}

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
