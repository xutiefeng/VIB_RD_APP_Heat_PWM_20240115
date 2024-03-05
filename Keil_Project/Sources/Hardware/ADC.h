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
** 宏定义
*********************************************************************************************************/
#define ADC_RESULT_BUF_LEN                  16                          /* ADC结果缓冲区容量            */

/***********************************************************************
** 电源BAT
  理论值： (((nV     /1200K)*200K) / 3.3V     * 1024) = n*5120/99  = 51.717172n
           (((n*100mV/1200K)*200K) / 33*100mV * 1024) = n*512/99   = 5.1717172n
  输入端二极管压降 0mV
  推算： AD1_BAT_7_0V                   (( 70 - 0) * 512/99)
         AD1_BAT_12_0V                  ((120 - 0) * 512/99) DKLai20230506
***********************************************************************/
#define AD1_BAT_DEVIA                   (0)//偏差(MCU供电3.3V,实测xxV)

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

//通讯电压:L禁能<8,使能>8       H:使能<18,禁能>18
#define AD1_BAT_COMM_STOPL_H            AD1_BAT_7_7V
#define AD1_BAT_COMM_NORMAL_L           AD1_BAT_7_8V
#define AD1_BAT_COMM_NORMAL_H           AD1_BAT_18_2V
#define AD1_BAT_COMM_STOPH_L            AD1_BAT_18_3V
//工作电压:9~16V
#define AD1_BAT_WORK_STOPL_H            AD1_BAT_8_7V
#define AD1_BAT_WORK_NORMAL_L           AD1_BAT_8_8V
#define AD1_BAT_WORK_NORMAL_H           AD1_BAT_16_2V
#define AD1_BAT_WORK_STOPH_L            AD1_BAT_16_3V
//诊断电压:L成熟<9,解除>10      H:解除<15,成熟>16
#define AD1_BAT_DIAG_STOPL_H            AD1_BAT_9_0V
#define AD1_BAT_DIAG_NORMAL_L           AD1_BAT_10_0V
#define AD1_BAT_DIAG_NORMAL_H           AD1_BAT_15_0V
#define AD1_BAT_DIAG_STOPH_L            AD1_BAT_16_0V
//电源故障:L成熟<9,解除>10      H:解除<15,成熟>16
#define AD1_BAT_VOLT_LOW_H              AD1_BAT_8_9V
#define AD1_BAT_VOLT_NORMAL_L           AD1_BAT_10_0V
#define AD1_BAT_VOLT_NORMAL_H           AD1_BAT_15_0V
#define AD1_BAT_VOLT_HIGH_L             AD1_BAT_16_1V

/***********************************************************************
** DCDC2004输出7.5V
  理论值： (((nV     /300K)*100K) / 3.3V     * 1024) = n*10240/99  = 103.434343n
           (((n*100mV/300K)*100K) / 33*100mV * 1024) = n*1024/99   = 10.3434343n
  推算： AD1_DCDC_7_5V                  (( 75) * 1024/99)
         AD1_DCDC_8_0V                  (( 80) * 1024/99)
***********************************************************************/
#define AD1_DCDC_DEVIA                  (0)//偏差(MCU供电3.3V,实测xxV)

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

//电压故障:L成熟<7.0,解除>7.2       H:解除<7.7,成熟>8.0
#define AD1_DCDC_VOLT_LOW_H             AD1_DCDC_7_0V
#define AD1_DCDC_VOLT_NORMAL_L          AD1_DCDC_7_2V
#define AD1_DCDC_VOLT_NORMAL_H          AD1_DCDC_7_7V
#define AD1_DCDC_VOLT_HIGH_L            AD1_DCDC_8_0V

/***********************************************************************
** NTC温度
** 实测：RLM-M2
   电路  VDD------R10K------R1K------RNTC------GND
              |         |         |         |
            3.27V     1.590V    1.422V      0V
   电流  I    = (3.27V-1.59V)/10K = (1.59V-1.422V)/1K = 0.168mA
         RNTC = 1.422V/0.168mA = 8.46K
   查手册RNTC=8.46K时，温度约为29C
   MCU输入AD电压1.422V，寄存器AD值理论值445，实际值455~460
   推算：温度80C时，RNTC=1.66K，MCU输入电压3.27V/12.66K*1.66K=0.429V--->AD理论值134
   (公式简化后：R = (AD*11) / (1024-AD))
   注：RLM-L和RLM-R电路中去掉R1K
** 实测：RLM-R
   电路  VDD------R10K------RNTC------GND
              |          |         |
            3.27V      1.52V       0V
   电流  I    = (3.27V-1.52V)/10K = 0.175mA
         RNTC = 1.52V/0.175mA = 8.68K
   查手册RNTC=8.68K时，温度约为29C
   MCU输入AD电压1.52V，寄存器AD值理论值476，实际值486~495
   推算：温度80C时，RNTC=1.66K，MCU输入电压3.27V/11.66K*1.66K=0.4655V--->AD理论值146
   (公式简化后：R = (AD*10) / (1024-AD))
***********************************************************************/
#define AD1_NTC_DEVIA                   (10)//偏差

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

//高温故障:L成熟<60C,解除>100C
#define AD1_NTC_NORMAL_H                AD1_NTC_90C
#define AD1_NTC_HIGH_L                  AD1_NTC_110C

/***********************************************************************
** 7040电流AD标定
** 负载仪恒流实测：BTS7040的IS端口测量电阻R=4.7K
   以下数据经拟合后，AD = 70.8182 + 0.757587*n
***********************************************************************/
#define AD1_7040_100MA                  147     //电流系数1012.79
#define AD1_7040_200MA                  222     //电流系数1316.86
#define AD1_7040_300MA                  298     //电流系数1475.64
#define AD1_7040_400MA                  373     //电流系数1561.90
#define AD1_7040_500MA                  449     //电流系数1615.09
#define AD1_7040_600MA                  525     //电流系数1660.45
#define AD1_7040_700MA                  601     //电流系数1687.43
#define AD1_7040_800MA                  677     //电流系数1717.06
#define AD1_7040_900MA                  753     //电流系数1740.82
#define AD1_7040_1000MA                 828     //电流系数1761.38
#define AD1_7040_1100MA                 904     //电流系数1778.57
#define AD1_7040_1200MA                 980     //电流系数1792.23

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
** 牌照灯电流
** RLM-M2,BTS7040的IS端口测量电阻R=4.7K
** 正常实测： BAT（V）	   AD值
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
#define AD1_NUM_DEVIA                   (0)//偏差(MCU供电3.3V,实测xxV)

#if     PROJECT_CUR == PROJECT_FOR_H56_RLM_L

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M1

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_M2
//#define AD1_NUM_10MA                    75   // 
//#define AD1_NUM_15MA                    77   // 
//#define AD1_NUM_28MA                    120  // 按照18V以上时估算
//#define AD1_NUM_33MA                    150  // 按照18V以上时估算
#define AD1_NUM_10MA                    1               // 设为极小值，等同于不使能电流过小故障
#define AD1_NUM_15MA                    5               // 
#define AD1_NUM_200MA                   AD1_7040_200MA  // 
#define AD1_NUM_300MA                   AD1_7040_300MA  // 

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R

#endif

#define AD1_CURRENT_NUM_MAX             AD1_7040_MAX

//电流故障:L成熟<10mA,解除>15mA   H:解除<200mA,成熟>300mA
#define AD1_CURRENT_NUM_LOW_H           AD1_NUM_10MA
#define AD1_CURRENT_NUM_NORMAL_L        AD1_NUM_15MA
#define AD1_CURRENT_NUM_NORMAL_H        AD1_NUM_200MA
#define AD1_CURRENT_NUM_HIGH_L          AD1_NUM_300MA

/***********************************************************************
** 高刹灯电流
** RLM-M2,BTS7040的IS端口测量电阻R=4.7K
** 正常实测：
   总电流400~500mA,BTS7040的IS电压1.68~1.90V,则IS电流0.3574~0.4043mA,推算BTS7040电流系数约1200，与手册中1750(正负19%)偏差较大
   MCU输入AD电压1.68~1.90V，寄存器AD值理论值526~595，实际值410~620，偏差较大
** 短路1颗LED：
   总电流500~540mA,BTS7040的IS电压1.96~2.06V,寄存器AD实际值620~640
** 短路2颗LED：
   总电流580~660mA,BTS7040的IS电压约2.20V,   寄存器AD实际值650~700
** 开路4路LED：
   总电流320~350mA,BTS7040的IS电压1.25~1.3V, 寄存器AD实际值430~450
   
** 总结：厂家回复电流为550mA(正负20%)，低阈值按照负30%设置，高阈值按照1A设置（岚图未对高阈值做要求）
***********************************************************************/
#define AD1_HBRAK1_DEVIA                (0)//偏差(MCU供电3.3V,实测xxV)

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

//电流故障:L成熟<350mA,解除>400mA   H:解除<900mA,成熟>1000mA
#define AD1_CURRENT_HBRAK1_LOW_H        AD1_HBRAK1_350MA
#define AD1_CURRENT_HBRAK1_NORMAL_L     AD1_HBRAK1_400MA
#define AD1_CURRENT_HBRAK1_NORMAL_H     AD1_HBRAK1_900MA
#define AD1_CURRENT_HBRAK1_HIGH_L       AD1_HBRAK1_1000MA

/***********************************************************************
** 后雾灯电流
** RLM-R,BTS7040的IS端口测量电阻R=4.7K
** 正常实测：
   
** 总结：厂家回复电流为600mA(正负20%)，低阈值按照负30%设置，高阈值按照1A设置（岚图未对高阈值做要求）
   2022-03-16 由于不过法规，厂家电流改为300mA(正负20%)，低阈值按照负50%设置，高阈值按照1A设置（岚图未对高阈值做要求）
***********************************************************************/
#define AD1_FOG_DEVIA                   (0)//偏差(MCU供电3.3V,实测xxV)

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

//电流故障:L成熟<150mA,解除>200mA   H:解除<900mA,成熟>1000mA
#define AD1_CURRENT_FOG_LOW_H           AD1_FOG_150MA
#define AD1_CURRENT_FOG_NORMAL_L        AD1_FOG_200MA
#define AD1_CURRENT_FOG_NORMAL_H        AD1_FOG_900MA
#define AD1_CURRENT_FOG_HIGH_L          AD1_FOG_1000MA

/***********************************************************************
** 倒车灯电流
** RLM-R,BTS7040的IS端口测量电阻R=4.7K
** 正常实测：
   
** 总结：厂家回复电流为800mA(正负20%)，低阈值按照负30%设置，高阈值按照1.25A设置（岚图未对高阈值做要求）
***********************************************************************/
#define AD1_REVER_DEVIA                 (0)//偏差(MCU供电3.3V,实测xxV)

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

//电流故障:L成熟<500mA,解除>550mA   H:解除<1200mA,成熟>1250mA
#define AD1_CURRENT_REVER_LOW_H         AD1_REVER_500MA
#define AD1_CURRENT_REVER_NORMAL_L      AD1_REVER_550MA
#define AD1_CURRENT_REVER_NORMAL_H      AD1_REVER_1200MA
#define AD1_CURRENT_REVER_HIGH_L        AD1_REVER_1250MA

/*********************************************************************************************************
** 全局定量
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
#define ADC_INDEX_CURRENT_HBRAK2        7   /* 采样芯片(未贴) */
#define ADC_INDEX_TOTAL                 8

#elif   PROJECT_CUR == PROJECT_FOR_H56_RLM_R
#define ADC_INDEX_POWER_DCDC1           0
#define ADC_INDEX_BAT                   1
#define ADC_INDEX_NTC_BRAK1             2
#define ADC_INDEX_CURRENT_OTHER         3   /* FOG和REVER复用       */
#define ADC_INDEX_TOTAL                 4

#define ADC_INDEX_CURRENT_FOG           3   /* 通道3分时复用为FOG  时，结果存放在AdcResultBuf[3] */
#define ADC_INDEX_CURRENT_REVER         4   /* 通道3分时复用为REVER时，结果存放在AdcResultBuf[4] */

#endif
#if ADC_INDEX_TOTAL > ADC_RESULT_BUF_LEN
#error "ADC_RESULT_BUF_LEN容量不足"
#endif
extern  const   adc_chan_config_t*  ADC_CONFIG_TBL[ADC_INDEX_TOTAL];

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
extern  volatile INT16U             AdcResultBuf[ADC_RESULT_BUF_LEN];   /* ADC结果                      */

/*********************************************************************************************************
** 函数声明
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
