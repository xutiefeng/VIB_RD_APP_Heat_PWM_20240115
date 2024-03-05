/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           SYS.c
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
#include "includeall.h"
#include "flexTimer_pwm1.h"


/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
volatile ftm_state_t        ftmStateStruct;

/*********************************************************************************************************
** Function name:       SYS_Init
** Descriptions:        �ж�,ʱ��,��Դ�ȳ�ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void   SYS_Init(void)
{
    /*********************************************************************************************************
    ** ʱ������
    *********************************************************************************************************/
    CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
    CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_FORCIBLE);
    /* SystemCoreClockUpdate(); �����ɴ����о���궨����S32K116�����(system_S32K116.h)�ľ���궨��������������δ������SystemCoreClock������ */
    
    /*********************************************************************************************************
    ** SysTick����
    *********************************************************************************************************/
    #if !SYSTICK_USE_LPTMR
    SysTick_Config(1000);                                               /* 1s/1000 = 1ms �ж�               */
    #else
    LPTMR_Config();
    #endif
    
    /*********************************************************************************************************
    ** FTM����
    *********************************************************************************************************/
    FTM_Config();
	
	
    /*********************************************************************************************************
    ** ���Ź�����
    *********************************************************************************************************/
    #if !DEBUG_PROJECT_MASK_WDOG
    WDOG_DRV_Init(INST_WATCHDOG1, &watchdog1_Config0);
    #endif
    /*********************************************************************************************************
    ** ��Դ��������
    *********************************************************************************************************/
    #if DEBUG_PROJECT_MCU_SLEEP_EN
    POWER_SYS_Init(&powerConfigsArr, POWER_MANAGER_CONFIG_CNT, &powerStaticCallbacksConfigsArr, POWER_MANAGER_CALLBACK_CNT);    
    #endif
}
/*********************************************************************************************************
** Function name:       PORT_Init
** Descriptions:        �˿ڳ�ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void   PORT_Init(void)
{
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
    INT_SYS_EnableIRQ(PORT_IRQn);                                       /* ��Ҫʹ��CANRx�ܽű����ж�    */
}

void   PORT_FactoryInit(void)
{
    PINS_DRV_Init(2, g_pin_Factory_InitConfigArr);
}

void   PORT_RecoverInit(void)
{
		PINS_DRV_Init(2, g_pin_RecoverFactory_InitConfigArr);
}
/*********************************************************************************************************
** Function name:       PORT_IRQHandler
** Descriptions:        PORT�ж�
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    PORT_IRQHandler(void)
{
    PINS_DRV_SetPinIntSel(PORTE, 4, PORT_DMA_INT_DISABLED);             /* ���ܱ����ж�                 */
    PINS_DRV_ClearPortIntFlagCmd(PORTE);                                /* ����жϱ�־                 */
}
#if !SYSTICK_USE_LPTMR
/*********************************************************************************************************
** Function name:       SysTick_Config
** Descriptions:        SysTick��ʼ��
** input parameters:    ulTick: Reloadֵ
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    SysTick_Config(INT32U ulTick)
{
    uint32_t core_freq = 0u;
    /* Get the correct name of the core clock */
    clock_names_t coreclk = CORE_CLK;
    status_t clk_status = CLOCK_SYS_GetFreq(coreclk, &core_freq);
    DEV_ASSERT(clk_status == STATUS_SUCCESS);
    DEV_ASSERT(core_freq > 0u);
    (void)clk_status;

    /* For Cortex-M0 devices the systick counter is initialized with an undefined
     value, so make sure to initialize it to 0 before starting */
    S32_SysTick->CSR = S32_SysTick_CSR_ENABLE(0u);
    #if 0
    S32_SysTick->RVR = S32_SysTick_RVR_RELOAD(core_freq / 1000u);
    #else
    S32_SysTick->RVR = S32_SysTick_RVR_RELOAD(core_freq / ulTick );//S32_SysTick_RVR_RELOAD(core_freq / ulTick );
    #endif
    S32_SysTick->CVR = S32_SysTick_CVR_CURRENT(0U);
    S32_SysTick->CSR = S32_SysTick_CSR_ENABLE(1u) | S32_SysTick_CSR_TICKINT(1u) | S32_SysTick_CSR_CLKSOURCE(1u);
}
/*********************************************************************************************************
** Function name:       SysTick_Handler
** Descriptions:        SysTick�ж�
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    SysTick_Handler(void)
{
    #if 1   /* ��ʱ1ms */
    static  INT8U   ucIrqTick = 0;
    
    SysTickCnt++;
    if (++ucIrqTick >= 2) {
        ucIrqTick   -= 2;
        SysTickNms++;
    }
    #else   /* ��ʱ2ms */
    SysTickCnt++;
    SysTickCnt++;
    SysTickNms++;
    #endif
    RDSystickProcess();
		
		static u8 sIOpwm = 0;
		if(OpenHeatFlag )
		{
			
			  if(gPwmDuty == 35)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 7 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				 if(gPwmDuty == 40)
				{
						if(sIOpwm >= 5)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm >2 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
			
			  else if(gPwmDuty == 45)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 9 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 50)
				{
						if(sIOpwm >= 2)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm%2 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				else if(gPwmDuty == 55)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 11 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 60)
				{
						if(sIOpwm >= 5)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 3 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 65)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 13 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 70)
				{
						if(sIOpwm >= 10)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 7 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 75)
				{
						if(sIOpwm >= 4)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 3 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 80)
				{
						if(sIOpwm >= 5)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 4 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 85)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 17 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 90)
				{
						if(sIOpwm >= 10)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 9 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 95)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 19 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else
				{

						PINS_DRV_WritePin(PTA,0,1);

				}
		}
		else
		{
				PINS_DRV_WritePin(PTA,0,0);
		}
}
#else
/*********************************************************************************************************
** Function name:       LPTMR_Config
** Descriptions:        LPTMR��ʼ��    ��ʱ���ڣ�1ms
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    LPTMR_Config(void)
{
	 LPTMR_DRV_Init(INST_LPTMR1, &lpTmr1_config0, false);
	 INT_SYS_EnableIRQ(LPTMR0_IRQn);
    	INT_SYS_SetPriority(LPTMR0_IRQn, 2);
	 LPTMR_DRV_StartCounter(INST_LPTMR1);
}
/*********************************************************************************************************
** Function name:       LPTMR0_IRQHandler
** Descriptions:        LPTMR0�ж�
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    LPTMR0_IRQHandler(void)
{
    static  INT8U   ucIrqTick = 0;
    
    LPTMR_DRV_ClearCompareFlag(INST_LPTMR1);
    
    SysTickCnt++;
    if (++ucIrqTick >= 2) {
        ucIrqTick   -= 2;
        SysTickNms++;
    }
    RDSystickProcess();
		
		static u32 sHeatPwmCnt = 0;
		
		
		if(OpenHeatFlag )
		{
				
				if(gPwmDuty == 50)
				{
						if(sIOpwm >= 2)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm%2 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				else if(gPwmDuty == 55)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 11 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 60)
				{
						if(sIOpwm >= 5)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 3 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 65)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 13 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 70)
				{
						if(sIOpwm >= 10)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 7 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 75)
				{
						if(sIOpwm >= 4)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 3 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 80)
				{
						if(sIOpwm >= 5)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 4 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 85)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 17 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 90)
				{
						if(sIOpwm >= 10)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 9 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else if(gPwmDuty == 95)
				{
						if(sIOpwm >= 20)
							sIOpwm = 0;
						
						sIOpwm++;
						
						if(sIOpwm > 19 )
						{
								PINS_DRV_WritePin(PTA,0,0);
						}
						else
						{
								PINS_DRV_WritePin(PTA,0,1);
						}
				}
				
				else
				{

						PINS_DRV_WritePin(PTA,0,1);

				}
		}
		else
		{
				PINS_DRV_WritePin(PTA,0,0);
		}
}
#endif
/*********************************************************************************************************
** Function name:       FTM_Config
** Descriptions:        FTM��ʼ��      ��ʱ���ڣ�50us
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    FTM_Config(void)
{
    /* Initialize Flex Timer instance as simple timer */
	//FTM_DRV_Init(0u, &flexTimer_mc1_InitConfig, &ftmStateStruct);
//	INT_SYS_EnableIRQ(FTM0_Ovf_Reload_IRQn);
//	INT_SYS_SetPriority(FTM0_Ovf_Reload_IRQn, 2);
//	/* Setup the counter to trigger an interrupt every 50 us */
//	FTM_DRV_InitCounter(INST_FLEXTIMER_MC1, &flexTimer_mc1_TimerConfig);
    /* Start the counter */
	//FTM_DRV_CounterStart(INST_FLEXTIMER_MC1);
   FTM_DRV_Init(INST_FLEXTIMER_PWM1, &flexTimer_pwm1_InitConfig, &ftmStateStruct);
   FTM_DRV_InitPwm(INST_FLEXTIMER_PWM1, &flexTimer_pwm1_PwmConfig);
   FTM_DRV_UpdatePwmChannel(0, 0U, 0U, 0U, 0U, true);
  	
}
/*********************************************************************************************************
** Function name:       FTM0_Ovf_Reload_IRQHandler
** Descriptions:        FTM0�ж�
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    FTM0_Ovf_Reload_IRQHandler(void)
{
    FTM_DRV_ClearStatusFlags(0U, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);
}

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
