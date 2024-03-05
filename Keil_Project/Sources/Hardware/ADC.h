/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           ADC.h
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
#ifndef __ADC_H
#define __ADC_H

// #include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define ADC_RESULT_BUF_LEN                  16                          /* ADC�������������            */

/***********************************************************************
** ��ԴBAT
  ����ֵ�� (((nV     /1200K)*200K) / 3.3V     * 1024) = n*5120/99  = 51.717172n
           (((n*100mV/1200K)*200K) / 33*100mV * 1024) = n*512/99   = 5.1717172n
  ����˶�����ѹ�� 0mV
  ���㣺 AD1_BAT_7_0V                   (( 70 - 0) * 512/99)
         AD1_BAT_12_0V                  ((120 - 0) * 512/99) DKLai20230506
***********************************************************************/
#define AD1_BAT_DEVIA                   (0)//ƫ��(MCU����3.3V,ʵ��xxV)

#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L
#define AD1_BAT_7_7V                    142  // (398.2 + 12 + AD1_BAT_DEVIA)
#define AD1_BAT_7_8V                    145  // (403.4 + 10 + AD1_BAT_DEVIA)
#define AD1_BAT_8_7V                    161  // (449.9 + 13 + AD1_BAT_DEVIA)
#define AD1_BAT_8_8V                    163  // (455.1 + 14 + AD1_BAT_DEVIA)
#define AD1_BAT_8_9V                    165  // (460.3 + 13 + AD1_BAT_DEVIA)
#define AD1_BAT_9_0V                    167  // (465.5 + 14 + AD1_BAT_DEVIA)
#define AD1_BAT_9_1V                    169  // (470.6 + 12 + AD1_BAT_DEVIA)
#define AD1_BAT_10_0V                   185  // (517.2 + 15 + AD1_BAT_DEVIA)
#define AD1_BAT_12_0V                   222  // (620.6 + 18 + AD1_BAT_DEVIA)
#define AD1_BAT_15_0V                   271  // (775.8 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_15_9V                   285  // (822.3 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_16_0V                   286  // (827.5 + 29 + AD1_BAT_DEVIA)
#define AD1_BAT_16_1V                   287  // (832.6 + 28 + AD1_BAT_DEVIA)
#define AD1_BAT_16_2V                   289  // (837.8 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_16_3V                   291  // (843.0 + 28 + AD1_BAT_DEVIA)
#define AD1_BAT_18_2V                   315  // (941.3 + 32 + AD1_BAT_DEVIA)
#define AD1_BAT_18_3V                   317  // (946.4 + 32 + AD1_BAT_DEVIA)

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1
#define AD1_BAT_7_7V                    409  // (398.2 + 12 + AD1_BAT_DEVIA)
#define AD1_BAT_7_8V                    414  // (403.4 + 10 + AD1_BAT_DEVIA)
#define AD1_BAT_8_7V                    463  // (449.9 + 13 + AD1_BAT_DEVIA)
#define AD1_BAT_8_8V                    468  // (455.1 + 14 + AD1_BAT_DEVIA)
#define AD1_BAT_8_9V                    473  // (460.3 + 13 + AD1_BAT_DEVIA)
#define AD1_BAT_9_0V                    478  // (465.5 + 14 + AD1_BAT_DEVIA)
#define AD1_BAT_9_1V                    484  // (470.6 + 12 + AD1_BAT_DEVIA)
#define AD1_BAT_10_0V                   532  // (517.2 + 15 + AD1_BAT_DEVIA)
#define AD1_BAT_12_0V                   640  // (620.6 + 18 + AD1_BAT_DEVIA)
#define AD1_BAT_15_0V                   802  // (775.8 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_15_9V                   850  // (822.3 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_16_0V                   855  // (827.5 + 29 + AD1_BAT_DEVIA)
#define AD1_BAT_16_1V                   861  // (832.6 + 28 + AD1_BAT_DEVIA)
#define AD1_BAT_16_2V                   866  // (837.8 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_16_3V                   871  // (843.0 + 28 + AD1_BAT_DEVIA)
#define AD1_BAT_18_2V                   973  // (941.3 + 32 + AD1_BAT_DEVIA)
#define AD1_BAT_18_3V                   978  // (946.4 + 32 + AD1_BAT_DEVIA)

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2
#define AD1_BAT_7_7V                    409  // (398.2 + 12 + AD1_BAT_DEVIA)
#define AD1_BAT_7_8V                    414  // (403.4 + 10 + AD1_BAT_DEVIA)
#define AD1_BAT_8_7V                    463  // (449.9 + 13 + AD1_BAT_DEVIA)
#define AD1_BAT_8_8V                    468  // (455.1 + 14 + AD1_BAT_DEVIA)
#define AD1_BAT_8_9V                    473  // (460.3 + 13 + AD1_BAT_DEVIA)
#define AD1_BAT_9_0V                    478  // (465.5 + 14 + AD1_BAT_DEVIA)
#define AD1_BAT_9_1V                    484  // (470.6 + 12 + AD1_BAT_DEVIA)
#define AD1_BAT_10_0V                   532  // (517.2 + 15 + AD1_BAT_DEVIA)
#define AD1_BAT_12_0V                   640  // (620.6 + 18 + AD1_BAT_DEVIA)
#define AD1_BAT_15_0V                   802  // (775.8 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_15_9V                   850  // (822.3 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_16_0V                   855  // (827.5 + 29 + AD1_BAT_DEVIA)
#define AD1_BAT_16_1V                   861  // (832.6 + 28 + AD1_BAT_DEVIA)
#define AD1_BAT_16_2V                   866  // (837.8 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_16_3V                   871  // (843.0 + 28 + AD1_BAT_DEVIA)
#define AD1_BAT_18_2V                   973  // (941.3 + 32 + AD1_BAT_DEVIA)
#define AD1_BAT_18_3V                   978  // (946.4 + 32 + AD1_BAT_DEVIA)

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R
#define AD1_BAT_7_7V                    409  // (398.2 + 12 + AD1_BAT_DEVIA)
#define AD1_BAT_7_8V                    414  // (403.4 + 10 + AD1_BAT_DEVIA)
#define AD1_BAT_8_7V                    463  // (449.9 + 13 + AD1_BAT_DEVIA)
#define AD1_BAT_8_8V                    468  // (455.1 + 14 + AD1_BAT_DEVIA)
#define AD1_BAT_8_9V                    473  // (460.3 + 13 + AD1_BAT_DEVIA)
#define AD1_BAT_9_0V                    478  // (465.5 + 14 + AD1_BAT_DEVIA)
#define AD1_BAT_9_1V                    484  // (470.6 + 12 + AD1_BAT_DEVIA)
#define AD1_BAT_10_0V                   532  // (517.2 + 15 + AD1_BAT_DEVIA)
#define AD1_BAT_12_0V                   640  // (620.6 + 18 + AD1_BAT_DEVIA)
#define AD1_BAT_15_0V                   802  // (775.8 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_15_9V                   850  // (822.3 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_16_0V                   855  // (827.5 + 29 + AD1_BAT_DEVIA)
#define AD1_BAT_16_1V                   861  // (832.6 + 28 + AD1_BAT_DEVIA)
#define AD1_BAT_16_2V                   866  // (837.8 + 27 + AD1_BAT_DEVIA)
#define AD1_BAT_16_3V                   871  // (843.0 + 28 + AD1_BAT_DEVIA)
#define AD1_BAT_18_2V                   973  // (941.3 + 32 + AD1_BAT_DEVIA)
#define AD1_BAT_18_3V                   978  // (946.4 + 32 + AD1_BAT_DEVIA)

#endif

#define AD1_BAT_MAX                     1023

//ͨѶ��ѹ:L����<8,ʹ��>8       H:ʹ��<18,����>18
#define AD1_BAT_COMM_STOPL_H            AD1_BAT_7_7V
#define AD1_BAT_COMM_NORMAL_L           AD1_BAT_7_8V
#define AD1_BAT_COMM_NORMAL_H           AD1_BAT_18_2V
#define AD1_BAT_COMM_STOPH_L            AD1_BAT_18_3V
//������ѹ:9~16V
#define AD1_BAT_WORK_STOPL_H            AD1_BAT_8_7V
#define AD1_BAT_WORK_NORMAL_L           AD1_BAT_8_8V
#define AD1_BAT_WORK_NORMAL_H           AD1_BAT_16_2V
#define AD1_BAT_WORK_STOPH_L            AD1_BAT_16_3V
//��ϵ�ѹ:L����<9,���>10      H:���<15,����>16
#define AD1_BAT_DIAG_STOPL_H            AD1_BAT_9_0V
#define AD1_BAT_DIAG_NORMAL_L           AD1_BAT_10_0V
#define AD1_BAT_DIAG_NORMAL_H           AD1_BAT_15_0V
#define AD1_BAT_DIAG_STOPH_L            AD1_BAT_16_0V
//��Դ����:L����<9,���>10      H:���<15,����>16
#define AD1_BAT_VOLT_LOW_H              AD1_BAT_8_9V
#define AD1_BAT_VOLT_NORMAL_L           AD1_BAT_10_0V
#define AD1_BAT_VOLT_NORMAL_H           AD1_BAT_15_0V
#define AD1_BAT_VOLT_HIGH_L             AD1_BAT_16_1V

/***********************************************************************
** DCDC2004���7.5V
  ����ֵ�� (((nV     /300K)*100K) / 3.3V     * 1024) = n*10240/99  = 103.434343n
           (((n*100mV/300K)*100K) / 33*100mV * 1024) = n*1024/99   = 10.3434343n
  ���㣺 AD1_DCDC_7_5V                  (( 75) * 1024/99)
         AD1_DCDC_8_0V                  (( 80) * 1024/99)
***********************************************************************/
#define AD1_DCDC_DEVIA                  (0)//ƫ��(MCU����3.3V,ʵ��xxV)

#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L
#define AD1_DCDC_7_0V                   748  // (724.0 + 24 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_2V                   770  // (744.7 + 25 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_5V                   803  // (775.8 + 27 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_7V                   845  // (817.1 + 28 + AD1_DCDC_DEVIA)
#define AD1_DCDC_8_0V                   857  // (827.5 + 29 + AD1_DCDC_DEVIA)

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1
#define AD1_DCDC_7_0V                   748  // (724.0 + 24 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_2V                   770  // (744.7 + 25 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_5V                   803  // (775.8 + 27 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_7V                   845  // (817.1 + 28 + AD1_DCDC_DEVIA)
#define AD1_DCDC_8_0V                   857  // (827.5 + 29 + AD1_DCDC_DEVIA)

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2
#define AD1_DCDC_7_0V                   748  // (724.0 + 24 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_2V                   770  // (744.7 + 25 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_5V                   803  // (775.8 + 27 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_7V                   845  // (817.1 + 28 + AD1_DCDC_DEVIA)
#define AD1_DCDC_8_0V                   857  // (827.5 + 29 + AD1_DCDC_DEVIA)

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R
#define AD1_DCDC_7_0V                   748  // (724.0 + 24 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_2V                   770  // (744.7 + 25 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_5V                   803  // (775.8 + 27 + AD1_DCDC_DEVIA)
#define AD1_DCDC_7_7V                   845  // (817.1 + 28 + AD1_DCDC_DEVIA)
#define AD1_DCDC_8_0V                   857  // (827.5 + 29 + AD1_DCDC_DEVIA)

#endif

#define AD1_DCDC_MAX                    1023

//��ѹ����:L����<7.0,���>7.2       H:���<7.7,����>8.0
#define AD1_DCDC_VOLT_LOW_H             AD1_DCDC_7_0V
#define AD1_DCDC_VOLT_NORMAL_L          AD1_DCDC_7_2V
#define AD1_DCDC_VOLT_NORMAL_H          AD1_DCDC_7_7V
#define AD1_DCDC_VOLT_HIGH_L            AD1_DCDC_8_0V

/***********************************************************************
** NTC�¶�
** ʵ�⣺RLM-M2
   ��·  VDD------R10K------R1K------RNTC------GND
              |         |         |         |
            3.27V     1.590V    1.422V      0V
   ����  I    = (3.27V-1.59V)/10K = (1.59V-1.422V)/1K = 0.168mA
         RNTC = 1.422V/0.168mA = 8.46K
   ���ֲ�RNTC=8.46Kʱ���¶�ԼΪ29C
   MCU����AD��ѹ1.422V���Ĵ���ADֵ����ֵ445��ʵ��ֵ455~460
   ���㣺�¶�80Cʱ��RNTC=1.66K��MCU�����ѹ3.27V/12.66K*1.66K=0.429V--->AD����ֵ134
   (��ʽ�򻯺�R = (AD*11) / (1024-AD))
   ע��RLM-L��RLM-R��·��ȥ��R1K
** ʵ�⣺RLM-R
   ��·  VDD------R10K------RNTC------GND
              |          |         |
            3.27V      1.52V       0V
   ����  I    = (3.27V-1.52V)/10K = 0.175mA
         RNTC = 1.52V/0.175mA = 8.68K
   ���ֲ�RNTC=8.68Kʱ���¶�ԼΪ29C
   MCU����AD��ѹ1.52V���Ĵ���ADֵ����ֵ476��ʵ��ֵ486~495
   ���㣺�¶�80Cʱ��RNTC=1.66K��MCU�����ѹ3.27V/11.66K*1.66K=0.4655V--->AD����ֵ146
   (��ʽ�򻯺�R = (AD*10) / (1024-AD))
***********************************************************************/
#define AD1_NTC_DEVIA                   (10)//ƫ��

#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L
#define AD1_NTC_29C                     (486 + AD1_NTC_DEVIA)  //R=8.46K
#define AD1_NTC_60C                     (236 + AD1_NTC_DEVIA)  //R=3.00K
#define AD1_NTC_70C                     (185 + AD1_NTC_DEVIA)  //R=2.21K
#define AD1_NTC_80C                     (146 + AD1_NTC_DEVIA)  //R=1.66K
#define AD1_NTC_90C                     (115 + AD1_NTC_DEVIA)  //R=1.26K
#define AD1_NTC_100C                    ( 91 + AD1_NTC_DEVIA)  //R=0.97K
#define AD1_NTC_110C                    ( 72 + AD1_NTC_DEVIA)  //R=0.76K
#define AD1_NTC_120C                    ( 58 + AD1_NTC_DEVIA)  //R=0.60K

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1
#define AD1_NTC_29C                     (445 + AD1_NTC_DEVIA)  //R=8.46K
#define AD1_NTC_60C                     (219 + AD1_NTC_DEVIA)  //R=3.00K
#define AD1_NTC_70C                     (171 + AD1_NTC_DEVIA)  //R=2.21K
#define AD1_NTC_80C                     (134 + AD1_NTC_DEVIA)  //R=1.66K
#define AD1_NTC_90C                     (105 + AD1_NTC_DEVIA)  //R=1.26K
#define AD1_NTC_100C                    ( 83 + AD1_NTC_DEVIA)  //R=0.97K
#define AD1_NTC_110C                    ( 66 + AD1_NTC_DEVIA)  //R=0.76K
#define AD1_NTC_120C                    ( 53 + AD1_NTC_DEVIA)  //R=0.60K

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2
#define AD1_NTC_29C                     (445 + AD1_NTC_DEVIA)  //R=8.46K
#define AD1_NTC_60C                     (219 + AD1_NTC_DEVIA)  //R=3.00K
#define AD1_NTC_70C                     (171 + AD1_NTC_DEVIA)  //R=2.21K
#define AD1_NTC_80C                     (134 + AD1_NTC_DEVIA)  //R=1.66K
#define AD1_NTC_90C                     (105 + AD1_NTC_DEVIA)  //R=1.26K
#define AD1_NTC_100C                    ( 83 + AD1_NTC_DEVIA)  //R=0.97K
#define AD1_NTC_110C                    ( 66 + AD1_NTC_DEVIA)  //R=0.76K
#define AD1_NTC_120C                    ( 53 + AD1_NTC_DEVIA)  //R=0.60K

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R
#define AD1_NTC_29C                     (486 + AD1_NTC_DEVIA)  //R=8.46K
#define AD1_NTC_60C                     (236 + AD1_NTC_DEVIA)  //R=3.00K
#define AD1_NTC_70C                     (185 + AD1_NTC_DEVIA)  //R=2.21K
#define AD1_NTC_80C                     (146 + AD1_NTC_DEVIA)  //R=1.66K
#define AD1_NTC_90C                     (115 + AD1_NTC_DEVIA)  //R=1.26K
#define AD1_NTC_100C                    ( 91 + AD1_NTC_DEVIA)  //R=0.97K
#define AD1_NTC_110C                    ( 72 + AD1_NTC_DEVIA)  //R=0.76K
#define AD1_NTC_120C                    ( 58 + AD1_NTC_DEVIA)  //R=0.60K

#endif

#define AD1_NTC_MAX                     1023

//���¹���:L����<60C,���>100C
#define AD1_NTC_NORMAL_H                AD1_NTC_90C
#define AD1_NTC_HIGH_L                  AD1_NTC_110C

/***********************************************************************
** 7040����AD�궨
** �����Ǻ���ʵ�⣺BTS7040��IS�˿ڲ�������R=4.7K
   �������ݾ���Ϻ�AD = 70.8182 + 0.757587*n
***********************************************************************/
#define AD1_7040_100MA                  147     //����ϵ��1012.79
#define AD1_7040_200MA                  222     //����ϵ��1316.86
#define AD1_7040_300MA                  298     //����ϵ��1475.64
#define AD1_7040_400MA                  373     //����ϵ��1561.90
#define AD1_7040_500MA                  449     //����ϵ��1615.09
#define AD1_7040_600MA                  525     //����ϵ��1660.45
#define AD1_7040_700MA                  601     //����ϵ��1687.43
#define AD1_7040_800MA                  677     //����ϵ��1717.06
#define AD1_7040_900MA                  753     //����ϵ��1740.82
#define AD1_7040_1000MA                 828     //����ϵ��1761.38
#define AD1_7040_1100MA                 904     //����ϵ��1778.57
#define AD1_7040_1200MA                 980     //����ϵ��1792.23

#define AD1_7040_150MA                  184
#define AD1_7040_250MA                  260
#define AD1_7040_350MA                  336
#define AD1_7040_450MA                  412
#define AD1_7040_550MA                  487
#define AD1_7040_650MA                  563
#define AD1_7040_750MA                  639
#define AD1_7040_850MA                  715
#define AD1_7040_950MA                  791
#define AD1_7040_1050MA                 866
#define AD1_7040_1150MA                 942
#define AD1_7040_1250MA                 1018

#define AD1_7040_MAX                    1023
/***********************************************************************
** ���յƵ���
** RLM-M2,BTS7040��IS�˿ڲ�������R=4.7K
** ����ʵ�⣺ BAT��V��	   ADֵ
                0	        72
                9	        78
                10	        81
                11	        83
                12	        86
                13	        89
                14	        91
                15	        94
                16	        96
                17	        99
                18	        102
***********************************************************************/
#define AD1_NUM_DEVIA                   (0)//ƫ��(MCU����3.3V,ʵ��xxV)

#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2
//#define AD1_NUM_10MA                    75   // 
//#define AD1_NUM_15MA                    77   // 
//#define AD1_NUM_28MA                    120  // ����18V����ʱ����
//#define AD1_NUM_33MA                    150  // ����18V����ʱ����
#define AD1_NUM_10MA                    1               // ��Ϊ��Сֵ����ͬ�ڲ�ʹ�ܵ�����С����
#define AD1_NUM_15MA                    5               // 
#define AD1_NUM_200MA                   AD1_7040_200MA  // 
#define AD1_NUM_300MA                   AD1_7040_300MA  // 

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R

#endif

#define AD1_CURRENT_NUM_MAX             AD1_7040_MAX

//��������:L����<10mA,���>15mA   H:���<200mA,����>300mA
#define AD1_CURRENT_NUM_LOW_H           AD1_NUM_10MA
#define AD1_CURRENT_NUM_NORMAL_L        AD1_NUM_15MA
#define AD1_CURRENT_NUM_NORMAL_H        AD1_NUM_200MA
#define AD1_CURRENT_NUM_HIGH_L          AD1_NUM_300MA

/***********************************************************************
** ��ɲ�Ƶ���
** RLM-M2,BTS7040��IS�˿ڲ�������R=4.7K
** ����ʵ�⣺
   �ܵ���400~500mA,BTS7040��IS��ѹ1.68~1.90V,��IS����0.3574~0.4043mA,����BTS7040����ϵ��Լ1200�����ֲ���1750(����19%)ƫ��ϴ�
   MCU����AD��ѹ1.68~1.90V���Ĵ���ADֵ����ֵ526~595��ʵ��ֵ410~620��ƫ��ϴ�
** ��·1��LED��
   �ܵ���500~540mA,BTS7040��IS��ѹ1.96~2.06V,�Ĵ���ADʵ��ֵ620~640
** ��·2��LED��
   �ܵ���580~660mA,BTS7040��IS��ѹԼ2.20V,   �Ĵ���ADʵ��ֵ650~700
** ��·4·LED��
   �ܵ���320~350mA,BTS7040��IS��ѹ1.25~1.3V, �Ĵ���ADʵ��ֵ430~450
   
** �ܽ᣺���һظ�����Ϊ550mA(����20%)������ֵ���ո�30%���ã�����ֵ����1A���ã��ͼδ�Ը���ֵ��Ҫ��
***********************************************************************/
#define AD1_HBRAK1_DEVIA                (0)//ƫ��(MCU����3.3V,ʵ��xxV)

#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2
#define AD1_HBRAK1_350MA                AD1_7040_350MA  // (000.0 + 0 + AD1_HBRAK1_DEVIA)
#define AD1_HBRAK1_400MA                AD1_7040_400MA  // (000.0 + 0 + AD1_HBRAK1_DEVIA)
#define AD1_HBRAK1_900MA                AD1_7040_900MA  // (000.0 + 0 + AD1_HBRAK1_DEVIA)
#define AD1_HBRAK1_1000MA               AD1_7040_1000MA // (000.0 + 0 + AD1_HBRAK1_DEVIA)

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R

#endif

#define AD1_CURRENT_HBRAK1_MAX          AD1_7040_MAX

//��������:L����<350mA,���>400mA   H:���<900mA,����>1000mA
#define AD1_CURRENT_HBRAK1_LOW_H        AD1_HBRAK1_350MA
#define AD1_CURRENT_HBRAK1_NORMAL_L     AD1_HBRAK1_400MA
#define AD1_CURRENT_HBRAK1_NORMAL_H     AD1_HBRAK1_900MA
#define AD1_CURRENT_HBRAK1_HIGH_L       AD1_HBRAK1_1000MA

/***********************************************************************
** ����Ƶ���
** RLM-R,BTS7040��IS�˿ڲ�������R=4.7K
** ����ʵ�⣺
   
** �ܽ᣺���һظ�����Ϊ600mA(����20%)������ֵ���ո�30%���ã�����ֵ����1A���ã��ͼδ�Ը���ֵ��Ҫ��
   2022-03-16 ���ڲ������棬���ҵ�����Ϊ300mA(����20%)������ֵ���ո�50%���ã�����ֵ����1A���ã��ͼδ�Ը���ֵ��Ҫ��
***********************************************************************/
#define AD1_FOG_DEVIA                   (0)//ƫ��(MCU����3.3V,ʵ��xxV)

#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R
#define AD1_FOG_150MA                   AD1_7040_150MA  // (000.0 + 0 + AD1_FOG_DEVIA)
#define AD1_FOG_200MA                   AD1_7040_200MA  // (000.0 + 0 + AD1_FOG_DEVIA)
#define AD1_FOG_900MA                   AD1_7040_900MA  // (000.0 + 0 + AD1_FOG_DEVIA)
#define AD1_FOG_1000MA                  AD1_7040_1000MA // (000.0 + 0 + AD1_FOG_DEVIA)

#endif

#define AD1_CURRENT_FOG_MAX             AD1_7040_MAX

//��������:L����<150mA,���>200mA   H:���<900mA,����>1000mA
#define AD1_CURRENT_FOG_LOW_H           AD1_FOG_150MA
#define AD1_CURRENT_FOG_NORMAL_L        AD1_FOG_200MA
#define AD1_CURRENT_FOG_NORMAL_H        AD1_FOG_900MA
#define AD1_CURRENT_FOG_HIGH_L          AD1_FOG_1000MA

/***********************************************************************
** �����Ƶ���
** RLM-R,BTS7040��IS�˿ڲ�������R=4.7K
** ����ʵ�⣺
   
** �ܽ᣺���һظ�����Ϊ800mA(����20%)������ֵ���ո�30%���ã�����ֵ����1.25A���ã��ͼδ�Ը���ֵ��Ҫ��
***********************************************************************/
#define AD1_REVER_DEVIA                 (0)//ƫ��(MCU����3.3V,ʵ��xxV)

#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R
#define AD1_REVER_500MA                 AD1_7040_500MA  // (000.0 + 0 + AD1_REVER_DEVIA)
#define AD1_REVER_550MA                 AD1_7040_550MA  // (000.0 + 0 + AD1_REVER_DEVIA)
#define AD1_REVER_1200MA                AD1_7040_1200MA // (000.0 + 0 + AD1_REVER_DEVIA)
#define AD1_REVER_1250MA                AD1_7040_1250MA // (000.0 + 0 + AD1_REVER_DEVIA)

#endif

#define AD1_CURRENT_REVER_MAX           AD1_7040_MAX

//��������:L����<500mA,���>550mA   H:���<1200mA,����>1250mA
#define AD1_CURRENT_REVER_LOW_H         AD1_REVER_500MA
#define AD1_CURRENT_REVER_NORMAL_L      AD1_REVER_550MA
#define AD1_CURRENT_REVER_NORMAL_H      AD1_REVER_1200MA
#define AD1_CURRENT_REVER_HIGH_L        AD1_REVER_1250MA

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/
#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L
#define ADC_INDEX_POWER_DCDC1           0
#define ADC_INDEX_BAT                   1
#define ADC_INDEX_NTC_BRAK1             2
#define ADC_INDEX_TOTAL                 6

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1
#define ADC_INDEX_NTC_BRAK1             0
#define ADC_INDEX_NTC_BRAK2             1
#define ADC_INDEX_POWER_DCDC1           2   /* BRAK_TURN */
#define ADC_INDEX_BAT                   3
#define ADC_INDEX_POWER_DCDC2           4   /* POST */
#define ADC_INDEX_TOTAL                 5

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2
#define ADC_INDEX_NTC_BRAK1             0
#define ADC_INDEX_NTC_BRAK2             1
#define ADC_INDEX_POWER_DCDC1           2   /* BRAK_TURN */
#define ADC_INDEX_BAT                   3
#define ADC_INDEX_POWER_DCDC2           4   /* POST */
#define ADC_INDEX_CURRENT_NUM           5
#define ADC_INDEX_CURRENT_HBRAK1        6
#define ADC_INDEX_CURRENT_HBRAK2        7   /* ����оƬ(δ��) */
#define ADC_INDEX_TOTAL                 8

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R
#define ADC_INDEX_POWER_DCDC1           0
#define ADC_INDEX_BAT                   1
#define ADC_INDEX_NTC_BRAK1             2
#define ADC_INDEX_CURRENT_OTHER         3   /* FOG��REVER����       */
#define ADC_INDEX_TOTAL                 4

#define ADC_INDEX_CURRENT_FOG           3   /* ͨ��3��ʱ����ΪFOG  ʱ����������AdcResultBuf[3] */
#define ADC_INDEX_CURRENT_REVER         4   /* ͨ��3��ʱ����ΪREVERʱ����������AdcResultBuf[4] */

#endif
#if ADC_INDEX_TOTAL > ADC_RESULT_BUF_LEN
#error "ADC_RESULT_BUF_LEN��������"
#endif
extern  const   adc_chan_config_t*  ADC_CONFIG_TBL[ADC_INDEX_TOTAL];

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
extern  volatile INT16U             AdcResultBuf[ADC_RESULT_BUF_LEN];   /* ADC���                      */

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void    ADC_Init(void);
extern  INT16U  ADC_GetADC0Chn5Value(void);
extern  void    ADC_GetADC0Task(void);

/******************************************* Private Function *******************************************/

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __ADC_H                     */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
