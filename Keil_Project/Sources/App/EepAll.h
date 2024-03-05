/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           EepAll.h
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
#ifndef __EEPALL_H
#define __EEPALL_H

#include "includeall.h"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define EEP_WRT_BUF_REWRITE_CNT         3                               /* ��дEEP����                  */

#define INTEEPADDRU                     INT32U
#define INTEEPSIZEU                     INT32U
#define INTEEPBUFU                      INT8U

#if 0   //�ⲿ24CXX
#define EEP_BASE_ADDR                   0
#define EEP_TOTAL_SIZE                  EEPEXT_TOTAL_SIZE
#define EEP_END_ADDR                    (EEP_BASE_ADDR + EEP_TOTAL_SIZE - 1)
#define EEP_WRT_WAIT_TIME               EEPEXT_WRT_WAIT_TIME
#define EEP_WRT_DIS()                   EEPEXT_WRITE_DIS()
#define EEP_INIT()                      EEPEXT_Init()
#define EEP_WRITE_ACT(Add, Len, ucDat)  EEPEXT_Write24CXX(Add, ucDat, Len)
#define EEP_READ_ACT(Add, Len, ucDat)   EEPEXT_Read24CXX(Add, ucDat, Len)
#else
//#define EEP_BASE_ADDR                   EEP_BASE_ADDR
//#define EEP_TOTAL_SIZE                  EEP_TOTAL_SIZE
//#define EEP_END_ADDR                    (EEP_BASE_ADDR + EEP_TOTAL_SIZE - 1)
#define EEP_WRT_WAIT_TIME               0
#define EEP_WRT_DIS()                   NOP()
#define EEP_INIT()                      EEPROM_Init()
#define EEP_WRITE_ACT(Add, Len, ucDat)  EEPROM_Write(Add, Len, (INT8U *const)ucDat)
#define EEP_READ_ACT(Add, Len, ucDat)   EEPROM_Read(Add, Len, (INT8U *const)ucDat)
#endif
/*********************************************************************************************************
** ö��
*********************************************************************************************************/
typedef enum {
    EEP_EXTRA_NONE                      = 0,                            /* �޶�������                   */
    EEP_EXTRA_RESET,                                                    /*                              */
    EEP_EXTRA_READ_CHK,                                                 /*                              */
    EEP_EXTRA_FF_CHK,                                                   /*                              */
    EEP_EXTRA_DID_F190,                                                 /*                              */
} EEP_EXTRA_ENUM;
/*********************************************************************************************************
** �ṹ��: �������ṹ��
*********************************************************************************************************/
/*
 * ����֡
 */
#define EEP_WRT_MSG_LEN                 12                              /* ���ò���,Msg����������,Byte  *//* 2020-01-15 zhaohai ��ΪDTC_BUF_IN_EEP_LENһ�볤�ȣ���������д�����ռ��ʱ��Ӱ����ʱ�� */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INTEEPADDRU  Add;
    INTEEPSIZEU  Len;
    INT8U   ucDat[EEP_WRT_MSG_LEN];
    EEP_EXTRA_ENUM      Extra;
} EepWrtMsgStruct;
typedef struct {
    BOOLEAN blNew;
    INTEEPADDRU  Add;
    INTEEPSIZEU  Len;
    INT8U   *pucDat;
    EEP_EXTRA_ENUM      Extra;
} EepRadMsgStruct;
/*
 * ������
 */
#define EEP_WRT_BUF_LEN                 32                              /* ���ò���,Buf����������       */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    INTEEPBUFU   IndexW;
    INTEEPBUFU   IndexR;
    INTEEPBUFU   Len;
    EepWrtMsgStruct     Msg[EEP_WRT_BUF_LEN];
} EepWrtBufStruct;
#define EEP_RAD_BUF_LEN                 32                              /* ���ò���,Buf����������       */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    INTEEPBUFU   IndexW;
    INTEEPBUFU   IndexR;
    INTEEPBUFU   Len;
    EepRadMsgStruct     Msg[EEP_RAD_BUF_LEN];
} EepRadBufStruct;
/*
 * ö��
 */
typedef enum {
    EEP_DEAL_WRT_BUF_DEFAULT           = 0,                             /* Ĭ��                         */
    EEP_DEAL_WRT_BUF_WRITE,                                             /*                              */
    EEP_DEAL_WRT_BUF_WAIT,                                              /*                              */
    EEP_DEAL_WRT_BUF_READ_CHK,                                          /*                              */
    EEP_DEAL_WRT_BUF_REWRITE,                                           /*                              */
    EEP_DEAL_WRT_BUF_SUCC,                                              /*                              */
    EEP_DEAL_WRT_BUF_NEXT,                                              /*                              */
} EEP_DEAL_WRT_BUF_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT8U                   ReWriteCnt;                                 /* ��дEEP����                  */
} EepStatStruct;
typedef struct {
    INT32U                  DealWrtBuf;                                 /* EepAll_DealWrtBuf���̿���    */
} EepTimeStruct;
typedef struct {
    BOOLEAN                 Busy;                                       /* д����æ��ʶ                 */
} EepFlagStruct;
typedef struct {
    EEP_DEAL_WRT_BUF_ENUM   DealWrtBuf;                                 /* EepAll_DealWrtBuf���̿���    */
} EepTaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    EepStatStruct           Stat;
    EepTimeStruct           Time;
    EepFlagStruct           Flag;
    EepTaskStruct           Task;
    
} EepInfoStruct;

#define EEP_MSG_READ_DIRECT             1
#define EEP_MSG_READ_WAIT               2
#define EEP_MSG_READ_USE_BUF            3

#if PROJECT_CUR == PROJECT_FOR_TEST

#define EEP_MSG_READ_MODE               EEP_MSG_READ_DIRECT

#else

#define EEP_MSG_READ_MODE               EEP_MSG_READ_DIRECT

#endif

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���: ������
*********************************************************************************************************/
extern  volatile EepWrtBufStruct    EepWrtBuf;                          /* д�뻺��������               */
#if EEP_MSG_READ_MODE == EEP_MSG_READ_USE_BUF
extern  volatile EepRadBufStruct    EepRadBuf;                          /* ��ȡ����������               */
#endif
extern  volatile EepWrtMsgStruct    EepWrtMsg;                          /* д�뱨��֡                   */
extern  volatile EepRadMsgStruct    EepRadMsg;                          /* ��ȡ����֡                   */
extern  volatile EepInfoStruct      EepInfo;                            /* EEP������Ϣ                  */

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    EepAll_Init(void);
extern  STAT_MSG_RESULT_ENUM    EepAll_DealWrtBuf(volatile EepWrtBufStruct *pBuf);
extern  STAT_MSG_RESULT_ENUM    EepAll_DealRadBuf(volatile EepRadBufStruct *pBuf);
extern  STAT_MSG_RESULT_ENUM    EepAll_LoadWrtMsg(INTEEPADDRU Add, INTEEPSIZEU Len, INT8U *pucDatAdd, EEP_EXTRA_ENUM euExtra);
extern  STAT_MSG_RESULT_ENUM    EepAll_LoadRadMsg(INTEEPADDRU Add, INTEEPSIZEU Len, INT8U *pucDatAdd, EEP_EXTRA_ENUM euExtra);
extern  INTEEPBUFU              EepAll_GetWrtBufIdleSize(volatile EepWrtBufStruct *pBuf);
extern  INTEEPBUFU              EepAll_GetRadBufIdleSize(volatile EepRadBufStruct *pBuf);

/******************************************* Private Function *******************************************/
static  void                    EepAll_InitWrtBuf(volatile EepWrtBufStruct *pBuf);
static  void                    EepAll_InitWrtMsg(volatile EepWrtMsgStruct *pMsg);
static  void                    EepAll_InitRadBuf(volatile EepRadBufStruct *pBuf);
static  void                    EepAll_InitRadMsg(volatile EepRadMsgStruct *pMsg);
static  STAT_MSG_RESULT_ENUM    EepAll_WrtMsg(volatile EepWrtMsgStruct *pMsg);
static  STAT_MSG_RESULT_ENUM    EepAll_RadMsg(volatile EepRadMsgStruct *pMsg);
static  STAT_MSG_RESULT_ENUM    EepAll_WrtMsgCopyToBuf(volatile EepWrtMsgStruct *pMsg, volatile EepWrtBufStruct *pBuf);
static  STAT_MSG_RESULT_ENUM    EepAll_RadMsgCopyToBuf(volatile EepRadMsgStruct *pMsg, volatile EepRadBufStruct *pBuf);

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __EEPALL_H                  */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
