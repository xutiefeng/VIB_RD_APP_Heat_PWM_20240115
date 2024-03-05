/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           CanNM2.h
** Last modified Date:  2011-06-01
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2011-06-01
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
#ifndef __CANNM2_H
#define __CANNM2_H

#include "includeall.h"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define NM2_T_UNIT                      2                               /* ����ʱ��                     */
#define NM2_T_MS(n)                     (n/NM2_T_UNIT)                  /* ʱ��궨��, n��Ϊ2�ı���     */

#define NM2_T_BUSOFF_FAST               NM2_T_MS(200)                   /* ��ָ�200ms                  */
#define NM2_T_BUSOFF_NORM               NM2_T_MS(200)                   /* ���ָ�200ms                  */
#define NM2_N_BUSOFF_FAST               1                               /* ��ָ�����                   */

/*
 * ö��
 */
typedef enum {
    NM2_BUS_MODE_PWR_ON                 = 0,                            /* �ϵ��ʼ��                   */
    NM2_BUS_MODE_NORMAL,                                                /* ��������                     */
    NM2_BUS_MODE_BUSOFF,                                                /* �޷�����ʱ(256)����������״̬*/
} NM2_BUS_MODE_ENUM;
/*
 * ��־:
 */
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  TxDisApp                        :1;                     /* 1:NMģ���ֹ����APP          */
        INTCPU  BusOff                          :1;                     /* 1:BusOff�ж�����             */
    } Bits;
} Nm2FlagCtrlUnion;
/*
 * ö��
 */
typedef enum {
    NM2_DEAL_XXXX_DEFAULT               = 0,                            /* Ĭ��                         */
    NM2_DEAL_XXXX_1,                                                    /*                              */
} NM2_DEAL_XXXX_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT8U                   XXXX;                                       /*                              */
    NM2_BUS_MODE_ENUM       BusMode;                                    /*                              */
    INT8U                   BusOffCnt;                                  /*                              */
} Nm2StatStruct;
typedef struct {
    INT32U                  XXXX;                                       /*                              */
    INT32U                  Mode;                                       /*                              */
    INT32U                  ReSen;                                      /*                              */
} Nm2TimeStruct;
typedef struct {
    BOOLEAN                 XXXX;                                       /*                              */
    Nm2FlagCtrlUnion        Ctrl;                                       /*                              */
} Nm2FlagStruct;
typedef struct {
    NM2_DEAL_XXXX_ENUM      XXXX;                                       /* XXXX���̿���                 */
} Nm2TaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    Nm2StatStruct           Stat;
    Nm2TimeStruct           Time;
    Nm2FlagStruct           Flag;
    Nm2TaskStruct           Task;
} Nm2InfoStruct;

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
extern  volatile Nm2InfoStruct      Nm2Info;                            /* ������Ϣ                     */

#define Nm2Info_Flag_TxDisApp       Nm2Info.Flag.Ctrl.Bits.TxDisApp
#define Nm2Info_Flag_BusOff         Nm2Info.Flag.Ctrl.Bits.BusOff

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    CanNm2_Init(void);
extern  void                    CanNm2_TimeTask(void);
extern  void                    CanNm2_StatTask(void);
extern  void                    CanNm2_TxStart(STAT_MSG_RESULT_ENUM euDealRslt);
extern  void                    CanNm2_TxConfirm(void);
extern  void                    CanNm2_BusOffEntry(void);
extern  void                    CanNm2_BusOffExit(void);
extern  void                    CanNm2_BusOffDeal(void);

/******************************************* Private Function *******************************************/

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __CA2NM2_H                  */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
