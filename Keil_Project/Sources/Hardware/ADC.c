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
** �궨��
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֶ���
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
** ȫ�ֱ���
*********************************************************************************************************/
//volatile INT16U             AdcResultBuf[ADC_RESULT_BUF_LEN];           /* ADC���                      */

/*********************************************************************************************************
** Function name:       ADC_Init
** Descriptions:        ��ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void   ADC_Init(void)
{
    INT8U   i;
    /*********************************************************************************************************
    **ADC����
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
** Descriptions:        ��ȡADC0-CHN5ͨ��ֵ��10λ������Ӳ��16�β���ȡ��ƽ��ֵ
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
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
** Descriptions:        ��ȡͨ��ֵ��10λ������Ӳ��16�β���ȡ��ƽ��ֵ���������ڣ�2ms
**                      ע��������ֱ��ÿ��ͨ����ȡ�ķ�ʽ,��������Ҫ���ڶ�ͨ��ʱÿ�ν���ȡһ��ͨ��,�������
**                      ����ADC_GetADC0Chn5Value(),ADC_GetADC0Chn6Value(),ADC_GetADC0Chn7Value()ʱռ��һ������ʱ�����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
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
