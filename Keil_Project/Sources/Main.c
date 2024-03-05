/****************************************Copyright (c)****************************************************
**                            Guangzhou ZLGMCU Development Co., LTD
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.c
** Last modified Date:  2012-04-01
** Last Version:        V1.0
** Descriptions:        The main() function example template
** 1:增加加热故障显示F9
	 2：优化工程模式
	 3：压缩机报警五分钟内超过三次
	 4：车机报文加热无记忆及语音唤醒
	 5：
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2012-04-01
** Version:             V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         zhaohai
** Modified date:       2015-05-01
** Version:             V
** Descriptions:        1. 
** Rechecked by:
*********************************************************************************************************/
#include "includeall.h"
#include "RDBsp\bsp_eeprom.h"
#include "RDBsp\UpdataCanMessage.h"
#include "RDBsp\FuncTab.h"

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/
#if 0
#ifdef __CC_ARM
extern  INT32U  Image$$ARM_LIB_STACK$$ZI$$Limit[];
extern  void    Reset_Handler(void);
const   INT32U  __attribute__((at(0x0)))                        AppStartCfg[2] = {
    (INT32U)Image$$ARM_LIB_STACK$$ZI$$Limit,
    (const INT32U)Reset_Handler,
};
#elif ((__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
extern  INT32U  Image$$ARM_LIB_STACK$$ZI$$Limit[];
extern  void    Reset_Handler(void);
const   INT32U  __attribute__((section(".ARM.__at_0x0")))       AppStartCfg[2] = {
    (INT32U)Image$$ARM_LIB_STACK$$ZI$$Limit,
    (const INT32U)Reset_Handler,
};
#else
extern  INT32U  __StackTop;
extern  void    Reset_Handler(void);
const   INT32U  __attribute__((section(".Appinterrupts2")))     AppStartCfg[2] = {
    (const INT32U)0x20003800,   /* (const INT32U)__StackTop, */
    (const INT32U)Reset_Handler,
};
#endif

#endif

#ifdef __CC_ARM
const   INT8U   __attribute__((at(0x1F800)))                    AppValidFlag[8] = {
#elif ((__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
const   INT8U   __attribute__((section(".ARM.__at_0x1F800")))   AppValidFlag[8] = {
#else
const   INT8U   __attribute__((section(".AppTbl")))             AppValidFlag[8] = {
#endif

    'V','I','B','V','A','L','I','D'    /* DKLai20230505 */
};

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:       SysInit
** Descriptions:        系统初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    SysInit(void)
{

	  Stat.Sysrun         = STAT_RUNSTS_INIT;
    Stat.Canrun         = STAT_RUNSTS_INIT;
    Stat.System         = STAT_SYSTEM_INIT;
    DisableIRQ();
    /*****************************************************************************************************
    **  系统外设 等的初始化
    *****************************************************************************************************/
    SYS_Init();
    ADC_Init();
    PORT_Init();
    BSP_UART_Init();
    __DiagTask_Init();  /* init diag task. DKLai20230505 */
    /*****************************************************************************************************
    **  软定时器,全局变量,全局标志 等的初始化
    *****************************************************************************************************/
    Time_Init();
    Stat_Init();
    Flag_Init();
    /*****************************************************************************************************
    **  初始化
    *****************************************************************************************************/
    
    /*****************************************************************************************************
    **  应用功能等的上电操作
    *****************************************************************************************************/
    Stat.Sysrun         = STAT_RUNSTS_RUN;
    Stat.Canrun         = STAT_RUNSTS_RUN;
    Stat.System         = STAT_SYSTEM_NORMAL;
		gstRDsysTick.tickCnt = 3;
    gstRDsysTick.tickCnt1 = 65;
    gstRDsysTick.tickCnt2 = 25;
	  gstRDsysTick.tickCnt4 =  0;
		
		//memcpy(TemprertureTab,ImageTemprertureTab,20);
    BSP_EEPROM_Initialize();
    EnableIRQ();   
}
/*********************************************************************************************************
** Function name:       SysTask
** Descriptions:        系统任务
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    SysTask(void)
{
    SysMonitor();
    /***************************************************
    ** 上电后仅执行一次的任务
    ***************************************************/
    if (Flag.PowerOnOnceTask0) {
        Flag.PowerOnOnceTask0   = FALSE;
        /***************************************************
        ** 读取配置
        ***************************************************/
        
    }
    /***************************************************
    ** 上电后需要等待延时且仅执行一次的任务
    ***************************************************/
    if (Flag.PowerOnOverTime1) {
        if (Flag.PowerOnOnceTask1) {
            Flag.PowerOnOnceTask1   = FALSE;
            /***************************************************
            ** 
            ***************************************************/
            
        }
    }
    if (Flag.PowerOnOverTime2) {
        if (Flag.PowerOnOnceTask2) {
            Flag.PowerOnOnceTask2   = FALSE;
            /***************************************************
            ** 
            ***************************************************/
            
        }
    }
}
/*********************************************************************************************************
** Function name:       SpeTask
** Descriptions:        特殊任务,eg:EepTask,区别于通用的查询任务,防止递归调用问题
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    SpeTask(void)
{
    static  INT8U   ucPoll;
    if ((++ucPoll) % 5) {   /* 2020-01-15 zhaohai 改为非每轮都执行，避免软定时器SysTick10ms等被延迟 */
        return;
    }
    
    if (Stat.Sysrun == STAT_RUNSTS_INIT) {
        return;
    }
		
    __DiagTask_EEPTask();  /* DKLai20230505 */
}
/*********************************************************************************************************
** Function name:       SysMonitor
** Descriptions:        系统监控任务
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    SysMonitor(void)
{
		static unsigned char v1 =0;
	
    CLRWDT();
    /*****************************************************************************************************
    ** 周期任务：
    *****************************************************************************************************/
    if (OUT == Time_Out(&Time.EveryN1ms, 5000)) {
        Flag.PowerOnOverTime2   = TRUE;
				//RDSystickProcess();
        
    }
    if (OUT == Time_Out(&Time.EveryN2ms, 3000)) {
        
        
    }
    if (OUT == Time_Out(&Time.EveryN3ms, 1500)) {
        Flag.PowerOnOverTime1   = TRUE;
        
        
    }
    if (OUT == Time_Out(&Time.EveryN4ms, 500)) {
        
        
    }
    if (OUT == Time_Out(&Time.EveryN5ms, 200)) {
        
        
    }
    if (OUT == Time_Out(&Time.EveryN6ms, 25)) {   
        
    }
    if (OUT == Time_Out(&Time.EveryN7ms, 20)) {

      
        
    }
    if (OUT == Time_Out(&Time.EveryN8ms, 10)) {
        
        
    }
    /*****************************************************************************************************
    ** 查询任务
    *****************************************************************************************************/
    __DiagTask_HandleTask();  /* DKLai20230505 */
		
    /*****************************************************************************************************
    ** 周期任务：2ms
    *****************************************************************************************************/
    if (SysTickNmsCntIsTrue()) 
		{
        SysTickNmsCntDec();
        SysTick10msInc();
        SysTick100msInc();
        SysTick1sInc();
				__RTE_AppFillPriodicMsg(UpdataCanMessage());
        __DiagTask_Period2msTask(); /* DKLai20230505 */
			
        ADC_GetADC0Task();
    }
    /*****************************************************************************************************
    ** 周期任务：10ms
    *****************************************************************************************************/
    if (SysTick10msIsTrue()) {
        SysTick10msClr();
				
        __DiagTask_Period10msTask();       /* DKLai20230505 */
        __RTE_AppPWADCValue();             /* DKLai20230506 */
    }
		
    /*****************************************************************************************************
    ** 周期任务：100ms
    *****************************************************************************************************/
    if (SysTick100msIsTrue()) {
        SysTick100msClr();
			
					CAN_22_2E_FillData();//
        __DiagTask_Period100msTask();      /* DKLai20230505 */
    }
		
    /*****************************************************************************************************
    ** 周期任务：1s
    *****************************************************************************************************/
    if (SysTick1sIsTrue()) 
		{
        SysTick1sClr();
			
				
    }
}

/*********************************************************************************************************
** Function name:       main
** Descriptions:
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int     main(void)
{
    SysInit();
    
    SysTickCnt = 0;
    SysTickNms = 0;
		HuoErIO_Flag = 0;
		gPauseCnt = _10S_Per100MS;
		
    for (;;) 
		{
        CLRWDT();
        SysTask();
        SpeTask();
				sysRuning();
    }
}

/*********************************************************************************************************
** PrintCan
*********************************************************************************************************/
#if DEBUG_PROJECT_PRINT_EN
void    PrintCan(CAN_Type *canType, INT32U ulID, INT8U ulLen, INT8U ucDat0, INT8U ucDat1, INT8U ucDat2, INT8U ucDat3, INT8U ucDat4, INT8U ucDat5, INT8U ucDat6, INT8U ucDat7)
{
    INT8U   ucBuf[8];
    static  INT8U   HwTxNum;
    
    ucBuf[0] = ucDat0;
    ucBuf[1] = ucDat1;
    ucBuf[2] = ucDat2;
    ucBuf[3] = ucDat3;
    ucBuf[4] = ucDat4;
    ucBuf[5] = ucDat5;
    ucBuf[6] = ucDat6;
    ucBuf[7] = ucDat7;
    if (HwTxNum == CAN_HWTX_NUM_NM) {
        HwTxNum = CAN_HWTX_NUM_APP;
    } else if (HwTxNum == CAN_HWTX_NUM_APP) {
        HwTxNum = CAN_HWTX_NUM_APP2;
    } else if (HwTxNum == CAN_HWTX_NUM_APP2) {
        HwTxNum = CAN_HWTX_NUM_APP3;
    } else if (HwTxNum == CAN_HWTX_NUM_APP3) {
        HwTxNum = CAN_HWTX_NUM_NM;
    }
    FLEXCAN_TxData(canType, HwTxNum, ulID, ucBuf, ulLen);
}
#endif

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
