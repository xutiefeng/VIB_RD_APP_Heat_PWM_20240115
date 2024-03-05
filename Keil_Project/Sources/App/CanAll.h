
/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           CanAll.h
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
#ifndef __CANALL_H
#define __CANALL_H

#include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨�� set stb io. DKLai20230423 
*********************************************************************************************************/
//#define CTRL_TJA_STB_H()                PINS_DRV_SetPins(  PTD, (INT32U)(1 << 0))
//#define CTRL_TJA_STB_L()                PINS_DRV_ClearPins(PTD, (INT32U)(1 << 0))
#define CTRL_TJA_STB_H()                PINS_DRV_SetPins(  PTB, (INT32U)(1 << 4))
#define CTRL_TJA_STB_L()                PINS_DRV_ClearPins(PTB, (INT32U)(1 << 4))  /* DKLai20230428 */
#define CTRL_TJA_STB_NORMAL()           {CTRL_TJA_STB_L();}
#define CTRL_TJA_STB_STANDY()           {CTRL_TJA_STB_H();}

#define CHCK_TJA_ERR()                  (PINS_DRV_ReadPins(PTB) & (1 << 1))
#define CHCK_TJA_ERR_IS_NORMAL()        (!CHCK_TJA_ERROR())//����
#define CHCK_TJA_ERR_IS_ERROR()         (CHCK_TJA_ERROR())

/*********************************************************************************************************
** �궨��-Ӳ�����ͻ�����
*********************************************************************************************************/
#define CAN_HWTX_MODE_WAIT              0                               /* ���ͺ�ȴ�ֱ���ɹ���ʱ     */
#define CAN_HWTX_MODE_RANDOM            1                               /* ����ʱ�Զ�ѡLowestӲ�������� */
#define CAN_HWTX_MODE_FIXED             2                               /* ����ʱAPP-NM-DIAG���Թ̶������� */
#define CAN_HWTX_MODE                   CAN_HWTX_MODE_FIXED

#if CAN_HWTX_MODE == CAN_HWTX_MODE_FIXED
#define CAN_HWTX_NUM_APP                0                               /* ����ѡ���Ӳ�����������     */
#define CAN_HWTX_NUM_APP2               1                               /* ����ѡ���Ӳ�����������     */
#define CAN_HWTX_NUM_APP3               2                               /* ����ѡ���Ӳ�����������     */
#define CAN_HWTX_NUM_NM                 3                               /* ����ѡ���Ӳ�����������     */
#define CAN_HWTX_NUM_DIAG               4                               /* ����ѡ���Ӳ�����������     */
#define CAN_HWTX_NUM_TOTAL              5                               /* ����ѡ���Ӳ������������     */
#endif
/*********************************************************************************************************
** �궨��-���ı�� DKLai20230421
*********************************************************************************************************/
#define CAN_SEN_MSG_NUM_APP_VIB383      0                               /* ���ͱ��ı��                 */
#define CAN_SEN_MSG_NUM_NM              1                               /* ���ͱ��ı��                 */
#define CAN_SEN_MSG_NUM_DIAG            2                               /* ���ͱ��ı��                 */
#define CAN_SEN_MSG_APP_TOTAL           1                               /* ����APP��������              */
#define CAN_SEN_MSG_TOTAL               3                               /* �������б�������             */
#define CAN_SEN_MSG_APP_ALL             0xFF                            /* ����APP����-����             */
#define CAN_SEN_MSG_ALL                 0xFF                            /* ���ͱ���-����                */

#define CAN_RCV_MSG_NUM_APP_BCM318      0                               /* ���ձ��ı�� DKLai20230421   */
#define CAN_RCV_MSG_NUM_APP_ACU35A      1                               /* ���ձ��ı��                 */
#define CAN_RCV_MSG_NUM_APP_ICM31E      2                               /* ���ձ��ı��                 */
#define CAN_RCV_MSG_NUM_APP_VCU3F2      3                               /* ���ձ��ı�� DKLai20230907   */

/* DKLai20230907 */
#define CAN_RCV_MSG_NUM_APP_CDC093      4                               /* ���ձ��ı��                 */
#define CAN_RCV_MSG_NUM_APP_TEL097      5                               /* ���ձ��ı��                 */
#define CAN_RCV_MSG_APP_TOTAL           6                               /* ����APP��������              */

#define CAN_RCV_MSG_APP_ALL             0xFF                            /* ����APP����-����             */

/*********************************************************************************************************
** �ṹ��: �������ṹ��
*********************************************************************************************************/
/*
 * ����֡(ȫƪֻʹ�ñ�׼֡,����û��ucType֮�����)
 */
#define CAN_MSG_LEN                     8                               /* �̶�����,Msg����������,Byte  */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    INT8U   ucDat[CAN_MSG_LEN];
} CanMsgStruct;
/*
 * ������
 */
#define CAN_BUF_LEN                      16                             /* ���ò���,Buf�б�������       */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    INT8U   IndexW;
    INT8U   IndexR;
    INT8U   Len;
    CanMsgStruct    Msg[CAN_BUF_LEN];
} CanBufStruct;

/*
 * ��־ DKLai20230421 
 */
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  MsgVIB383                       :1;                     /* ��ȷ�ϵ������ͱ�־         */
        INTCPU  MsgNm                           :1;                     /* ��ȷ�ϵ������ͱ�־         */
        INTCPU  MsgDiag                         :1;                     /* ��ȷ�ϵ������ͱ�־         */
    } Bits;
} CanFlagSendUnion;
/*
 * ö��
 */
typedef enum {
    CAN_DEAL_XXXX_DEFAULT               = 0,                            /* Ĭ��                         */
    CAN_DEAL_XXXX_1,                                                    /*                              */
} CAN_DEAL_XXXX_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT8U                   XXXX;                                       /*                              */
    #if CAN_HWTX_MODE == CAN_HWTX_MODE_FIXED
    INT8U                   HwTxSt;                                     /* Ӳ��������Tx0~2�Ƿ�����ʹ��  */
    #elif   CAN_HWTX_MODE == CAN_HWTX_MODE_RANDOM
    INT8U                   HwTxSelVIB383;                              /* �ñ��ķ���ʱѡ���Ӳ�������� */
    INT8U                   HwTxSelNm;                                  /* �ñ��ķ���ʱѡ���Ӳ�������� */
    INT8U                   HwTxSelDiag;                                /* �ñ��ķ���ʱѡ���Ӳ�������� */
    #endif
} CanStatStruct;
typedef struct {
    INT32U                  XXXX;                                       /*                              */
} CanTimeStruct;
typedef struct {
    BOOLEAN                 CommTxDis;                                  /* ���ͽ�ֹ                     */
    BOOLEAN                 CommTxDisApp;                               /* Ӧ�ñ��ķ��ͽ�ֹ             */
    BOOLEAN                 CommRxDisApp;                               /* Ӧ�ñ��Ľ��ս�ֹ             */
    BOOLEAN                 CommTxDisNm;                                /* ���籨��ͨѶ��ֹ             */
    BOOLEAN                 CommTxDisDiag;                              /* ��ϱ���ͨѶ��ֹ             */
    BOOLEAN                 TxTaskActive;                               /* ��������������񼤻�״̬     */
    BOOLEAN                 TxConfirmActive;                            /* ���ͳɹ�������񼤻�״̬     */
    CanFlagSendUnion        Send;                                       /*                              */
} CanFlagStruct;
typedef struct {
    CAN_DEAL_XXXX_ENUM      XXXX;                                       /* XXXX���̿���                 */
} CanTaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    CanStatStruct           Stat;
    CanTimeStruct           Time;
    CanFlagStruct           Flag;
    CanTaskStruct           Task;
} CanInfoStruct;
#define CAN_MSG_SEND_DIRECT             1
#define CAN_MSG_SEND_USE_BUF            2

#if PROJECT_CUR == PROJECT_FOR_TEST

#define CAN_MSG_SEND_MODE               CAN_MSG_SEND_DIRECT

#else

#define CAN_MSG_SEND_MODE               CAN_MSG_SEND_DIRECT

#endif

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���: ������
*********************************************************************************************************/
extern  volatile CanBufStruct       CanRcvBuf;                          /* ���ջ�����                   */
#if CAN_MSG_SEND_MODE == CAN_MSG_SEND_USE_BUF
extern  volatile CanBufStruct       CanSenBuf;                          /* ���ͻ�����                   */
#endif
extern  volatile CanInfoStruct      CanInfo;                            /* ������Ϣ                     */
extern  volatile CanMsgStruct       CanRcvMsgWake;                      /* ���ձ���֡-����              */

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    CanAll_Init(void);
extern  STAT_MSG_RESULT_ENUM    CanAll_DealRcvBuf(volatile CanBufStruct *pBuf);
#if CAN_HWTX_MODE == CAN_HWTX_MODE_FIXED
extern  STAT_MSG_RESULT_ENUM    CanAll_SenMsg(volatile CanMsgStruct *pMsg, INT8U ucHwTxNum);
#elif   CAN_HWTX_MODE == CAN_HWTX_MODE_RANDOM
extern  INT8U                   CanAll_SenMsg(volatile CanMsgStruct *pMsg);
#elif   CAN_HWTX_MODE == CAN_HWTX_MODE_WAIT
extern  STAT_MSG_RESULT_ENUM    CanAll_SenMsg(volatile CanMsgStruct *pMsg);
#endif
extern  STAT_MSG_RESULT_ENUM    CanAll_ReqSenMsg(INT8U ucMsgNum);
extern  STAT_MSG_RESULT_ENUM    CanAll_CancelSenMsg(INT8U ucMsgNum);
extern  void                    CanAll_TxTask(void);
extern  void                    CanAll_TxConfirm(void);

extern  void                    CanAll_OnLine(void);
extern  void                    CanAll_OffLine(void);

extern  void                    CanAll_MsgCopyToMsg(volatile CanMsgStruct *pMsgSor, volatile CanMsgStruct *pMsgDst);
/******************************************* Private Function *******************************************/
static  void                    CanAll_InitBuf(volatile CanBufStruct *pBuf);
static  void                    CanAll_InitMsg(volatile CanMsgStruct *pMsg);

extern  void                    CanAll_ClrMsgData(volatile CanMsgStruct *pMsg);                  /* DKLai20230425 */
extern  void                    CanAll_CopyDataToMsg(uint8_t *buf, volatile CanMsgStruct *pMsg); /* DKLai20230425 */

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __CANALL_H                  */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
