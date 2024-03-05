/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Time.c
** Last modified Date:  2011-12-01
** Last Version:        V1.00
** Descriptions:        时间管理
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
** 全局定量
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量
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
** Descriptions:        微秒延时【S32K116:CPU = 40MHz时】
** input parameters:    误差见下表
** output parameters:   无
** Returned value:      无
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
** Descriptions:        微秒延时【S32K116:CPU = 16MHz时】
** input parameters:    误差见下表
** output parameters:   无
** Returned value:      无
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
** Descriptions:        微秒延时【S32K142:CPU = 48MHz时】
** input parameters:    误差见下表
** output parameters:   无
** Returned value:      无
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
** Descriptions:        毫秒延时
** input parameters:    usDly:
** output parameters:   无
** Returned value:      无
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
** 单位: 1ms
*****************************************************************************************************************/
/*********************************************************************************************************
** Function name:       Time_GetSysTick
** Descriptions:        获取系统节拍
** input parameters:    无
** output parameters:   无
** Returned value:      无
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
** Descriptions:        复位计时变量
** input parameters:    *pTimeVar:      计时变量
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    Time_Reset(volatile INT32U *pTimeVar)
{
    *pTimeVar       = Time_GetSysTick();                                /* 复位定时变量                 */
}
/*********************************************************************************************************
** Function name:       Time_Out
** Descriptions:        任意多路定时
** input parameters:    *pTimeVar:      计时变量
**                      ucTimeOut:      定时间隔
** output parameters:   无
** Returned value:      0<=N<0xFFFFFFFF:当前实际延时(N个定时单位) 0xFFFFFFFF:定时到
*********************************************************************************************************/
INT32U   Time_Out(volatile INT32U *pTimeVar, INT32U ucTimeOut)
{
    INT32U uldiff;
    
    if (ucTimeOut == OUT) {
        return 0;
    }
    uldiff      = Time_GetSysTick() - *pTimeVar;                        /* 计算定时时间间隔             */
    if (uldiff >= ucTimeOut) {                                          /* 定时时间到                   */
        *pTimeVar = Time_GetSysTick();                                  /* 更新定时变量，开始下一次定时 */
        return OUT;
    } else {
        return uldiff;
    }
}
/*********************************************************************************************************
** Function name:       Time_WaitMS
** Descriptions:        定时器延时,主要区别于 DelayMS()
** input parameters:    ulWait:     延时N个定时单位
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    Time_WaitMS(INT32U ulWait)
{
    Time_Reset(&Time.WaitMS);
    while(OUT != Time_Out(&Time.WaitMS, ulWait)) {
        /* 添加任务 */
        
    }
}
/*********************************************************************************************************
** Function name:       Time_ResetN
** Descriptions:        复位计时变量
** input parameters:    *pTimeVar:      计时变量
**                      *pTimeVarCnt:   超时计数
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    Time_ResetN(volatile INT32U *pTimeVar, volatile INT32U *pTimeVarCnt)
{
    *pTimeVar       = Time_GetSysTick();                                /* 复位定时变量                 */
    *pTimeVarCnt    = 0;                                                /* 复位超时计数                 */
}
/*********************************************************************************************************
** Function name:       Time_OutN
** Descriptions:        任意多路定时
** input parameters:    *pTimeVar:      计时变量
**                      *pTimeVarCnt:   超时计数
**                      ucTimeOut:      定时间隔
**                      ucTimeOutCnt:   超时数量
** output parameters:   无
** Returned value:      0<=N<0xFFFFFFFF:当前实际延时(N个超时计数) 0xFFFFFFFF:定时到
*********************************************************************************************************/
INT32U   Time_OutN(volatile INT32U *pTimeVar, volatile INT32U *pTimeVarCnt, INT32U ucTimeOut, INT32U ucTimeOutCnt)
{
    INT32U uldiff;
    
    if (ucTimeOut == OUT) {
        return 0;
    }
    uldiff      = Time_GetSysTick() - *pTimeVar;                        /* 计算定时时间间隔             */
    if (uldiff >= ucTimeOut) {                                          /* 定时时间到                   */
        *pTimeVar   = Time_GetSysTick();                                /* 更新定时变量，开始下一次定时 */
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
** Descriptions:        计时变量初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
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
    /* 不可用，因为将大于当前Tick
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
