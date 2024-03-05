/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ADC.c
** Last modified Date:  2018-02-01
** Last Version:        V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2018-02-01
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
** 宏定义
*********************************************************************************************************/

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/
const adc_chan_config_t* ADC_CONFIG_TBL[ADC_INDEX_TOTAL] = {
#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L
    &adConv1_ChnConfig0,
    &adConv1_ChnConfig1,
    &adConv1_ChnConfig2,
    &adConv1_ChnConfig3,
    &adConv1_ChnConfig4,
		&adConv1_ChnConfig5,
#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1
    &adConv1_ChnConfig0,
    &adConv1_ChnConfig1,
    &adConv1_ChnConfig2,
    &adConv1_ChnConfig3,
    &adConv1_ChnConfig4,
#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2
    &adConv1_ChnConfig0,
    &adConv1_ChnConfig1,
    &adConv1_ChnConfig2,
    &adConv1_ChnConfig3,
    &adConv1_ChnConfig4,
    &adConv1_ChnConfig5,
    &adConv1_ChnConfig6,
    &adConv1_ChnConfig7,
#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R
    &adConv1_ChnConfig0,
    &adConv1_ChnConfig1,
    &adConv1_ChnConfig2,
    &adConv1_ChnConfig3,
#endif
};

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
//volatile INT16U             AdcResultBuf[ADC_RESULT_BUF_LEN];           /* ADC结果                      */

/*********************************************************************************************************
** Function name:       ADC_Init
** Descriptions:        初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void   ADC_Init(void)
{
    INT8U   i;
    /*********************************************************************************************************
    **ADC配置
    *********************************************************************************************************/
    ADC_DRV_ConfigConverter(INST_ADCONV1, &adConv1_ConvConfig0);
    ADC_DRV_ConfigHwAverage(INST_ADCONV1, &adConv1_HwAvgConfig0);
    ADC_DRV_ConfigChan(INST_ADCONV1, 0, 	&adConv1_ChnConfig0);
    
    for (i = 0; i < ADMax; i++) {
        ADtable[i] = 0;
    }
}
/*********************************************************************************************************
** Function name:       ADC_GetADC0Chn5Value
** Descriptions:        获取ADC0-CHN5通道值，10位采样，硬件16次采样取的平均值
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
INT16U  ADC_GetADC0Chn5Value(void)
{
    INT16U ret;
    
    ADC_DRV_ConfigChan(INST_ADCONV1, 0, &adConv1_ChnConfig0);
    ADC_DRV_WaitConvDone(INST_ADCONV1);
    ADC_DRV_GetChanResult(INST_ADCONV1, 0, (INT16U *)&ret);
    
    return (INT16U)ret;
}
/*********************************************************************************************************
** Function name:       ADC_GetADC0Task
** Descriptions:        获取通道值，10位采样，硬件16次采样取的平均值，调度周期：2ms
**                      注：区别于直接每个通道读取的方式,此任务主要用于多通道时每次仅读取一个通道,避免采用
**                      连续ADC_GetADC0Chn5Value(),ADC_GetADC0Chn6Value(),ADC_GetADC0Chn7Value()时占用一个节拍时间过长
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    ADC_GetADC0Task(void)
{
    static INT8U    ucADCTask   = 0;
    static INT8U    ucIndex     = 0;
    #if     PROJECT_CUR == PROJECT_FOR_H56_RLM_R
    static BOOLEAN  blFogorRever    = FALSE;
    #endif
    
    switch (ucADCTask) {
        case 0:
            ADC_DRV_ConfigChan(INST_ADCONV1, 0, ADC_CONFIG_TBL[ucIndex]);
            ucADCTask   = 1;
            break;
        case 1:
            ADC_DRV_WaitConvDone(INST_ADCONV1);
            #if     PROJECT_CUR == PROJECT_FOR_H56_RLM_R//PROJECT_FOR_H56_RLM_L
            if (ucIndex == ADC_INDEX_CURRENT_OTHER) 
						{
                if (blFogorRever) {
                    blFogorRever    = FALSE;
                    CTRL_OTHER_DIAG_REVER();
                    ADC_DRV_GetChanResult(INST_ADCONV1, 0, (INT16U *)&ADtable[ADC_INDEX_CURRENT_FOG]);
                } else {
                    blFogorRever    = TRUE;
                    CTRL_OTHER_DIAG_FOG();
                    ADC_DRV_GetChanResult(INST_ADCONV1, 0, (INT16U *)&ADtable[ADC_INDEX_CURRENT_REVER]);
                }
            } 
						else 
						{
                ADC_DRV_GetChanResult(INST_ADCONV1, 0, (INT16U *)&+[ucIndex]);
            }
            #else
            ADC_DRV_GetChanResult(INST_ADCONV1, 0, (INT16U *)&ADtable[ucIndex]);
            #endif
				
						ADC_DRV_GetChanResult(INST_ADCONV1, 0, (INT16U *)&ADtable[ucIndex]);
				
            if ((++ucIndex) >= ADC_INDEX_TOTAL) {
                ucIndex  = 0;
            }
            ADC_DRV_ConfigChan(INST_ADCONV1, 0, ADC_CONFIG_TBL[ucIndex]);
            break;
        default:
            break;
    }
}

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
