/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           CanTp.h
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
#ifndef __CANTP_H
#define __CANTP_H

#include "includeall.h"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define TP_T_UNIT                       2                               /* ����ʱ��                     */
#define TP_T_MS(n)                      (n/TP_T_UNIT)                   /* ʱ��궨��, n��Ϊ2�ı���     */

#define TP_MSG_ID_FUN                   CAN_MSG_ID_DIAG_FUN             /* �������                     */
#define TP_MSG_ID_PHY                   CAN_MSG_ID_DIAG_PHY             /* �������                     */
#define TP_MSG_ID_RSP                   CAN_MSG_ID_DIAG_ACK             /* �����Ӧ                     */

/*********************************************************************************************************
** �궨��: ISO15765-2
*********************************************************************************************************/
#define TP_MF_BUF_LEN                   512                             /* ��֡��������С -- �����Э���������������ָ����� */
#define TP_MF_BUF_LEN_MAX               4096                            /* ʵ����Ч�� */

#define TP_MF_STmin_FC                  TP_T_MS(20)                     /* ֡���Ĭ����Сֵ����������֡ʱ���� */
#define TP_MF_STmin_DEFAULT             TP_T_MS(22)                     /* ֡���Ĭ����Сֵ�����ؼ�ʱʵ�ʲ��� *//* 2019-05-13 zhaohai ����UNIT=2,���������-2ms~+2ms����Ϊ+0~+4ms */
#define N_AS                            TP_T_MS(70)                     /* ���ͷ�N_PDU���ͳ�ʱ����  -- ���ͷ������Ƿ��ͳ�ʱ���ӿ�ʼ���͵����ͳɹ�������FF,CF */
#define N_AR                            TP_T_MS(70)                     /* ���շ�N_PDU���ͳ�ʱ����  -- ���շ������Ƿ��ͳ�ʱ���ӿ�ʼ���͵����ͳɹ�������FC */
#define N_BS                            TP_T_MS(150)                    /* �ȴ���������֡�ĳ�ʱ���� -- ������֡/��������֡�󣬵ȴ����շ���������֡��ʱ�� */
#define N_BR                            TP_T_MS(2)                      /* ��������֮֡ǰ�ĵȴ�ʱ�� -- �յ���֡/�յ�����֡�󣬿�ʼ��������֡ǰ�ĵȴ�ʱ�� */
#define N_CS                            TP_T_MS(20)                     /* ��������֮֡ǰ�ĵȴ�ʱ�� -- �յ�����֡/��������֡�󣬿�ʼ��������֡ǰ�ĵȴ�ʱ�䣬ͨ���ӽ�STmin */
#define N_CR                            TP_T_MS(150)                    /* �ȴ���������֡�ĳ�ʱ���� -- ��������֡/��������֡�󣬵ȴ����ͷ���������֡��ʱ�� */
#define N_WFT_MAX                       0                               /* ����֡�ȴ�����           -- ��������֡�ȴ������� */

#define TP_FC_EN                        TRUE                            /* �Ƿ�ʹ������֡ */
#define TP_MF_BS_DEFAULT                8                               /* ��֡����ͨ�ţ�block size ��Χ��1~255  ��ʹ������֡ʱ bsΪ0 */
#define TP_MSG_FILL_BYTE                0xAA                            /* ��ϱ�������ַ� DKLai20230424 */

#if TP_FC_EN
#define TP_MF_BS                        TP_MF_BS_DEFAULT
#else
#define TP_MF_BS                        0
#endif
/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define TP_FC_FS_CTS                    0x00
#define TP_FC_FS_WT                     0x01
#define TP_FC_FS_OVFLW                  0x02

/*********************************************************************************************************
** �ṹ��: �������ṹ��
*********************************************************************************************************/
#define TP_PHY_BUF_LEN                  512                             /* ���ò���,Buf�б�������       */
typedef struct {
    INT16U  Index;
    INT16U  Len;
    INT8U   ucDat[TP_PHY_BUF_LEN + 8];
} TpPhyBufStruct;
#define TP_FUN_BUF_LEN                    8                             /* ���ò���,Buf�б�������       */
typedef struct {
    INT16U  Index;
    INT16U  Len;
    INT8U   ucDat[TP_FUN_BUF_LEN];
} TpFunBufStruct;

/*
 * ö��
 */
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  XXXX                            :1;                     /*                              */
        INTCPU  YYYY                            :1;                     /*                              */
    } Bits;
} TpFlagXXXXUnion;
typedef enum {
    TP_DEAL_PHY_DEFAULT                 = 0,                            /* Ĭ��                         */
    TP_DEAL_PHY_SEN_SF,                                                 /*                              */
    TP_DEAL_PHY_SEN_SF_CONF,                                            /*                              */
    TP_DEAL_PHY_RCV_SF,                                                 /*                              */
    TP_DEAL_PHY_SEN_FF,                                                 /*                              */
    TP_DEAL_PHY_SEN_FF_CONF,                                            /*                              */
    TP_DEAL_PHY_RCV_FF,                                                 /*                              */
    TP_DEAL_PHY_SEN_FC,                                                 /*                              */
    TP_DEAL_PHY_SEN_FC_CONF,                                            /*                              */
    TP_DEAL_PHY_RCV_FC,                                                 /*                              */
    TP_DEAL_PHY_SEN_CF,                                                 /*                              */
    TP_DEAL_PHY_SEN_CF_CONF,                                            /*                              */
    TP_DEAL_PHY_RCV_CF,                                                 /*                              */
} TP_DEAL_PHY_ENUM;
typedef enum {
    TP_DEAL_FUN_DEFAULT                 = 0,                            /* Ĭ��                         */
    TP_DEAL_FUN_RCV_SF,                                                 /*                              */
} TP_DEAL_FUN_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT32U                  STmin;                                      /* ֡�������                   */
    INT8U                   MfRcvFS;                                    /* ���ն�֡ʱ����֡��FS����     */
    INT8U                   MfRcvBS;                                    /* ���ն�֡ʱ����֡��BS����     */
    INT8U                   MfRcvSN;                                    /* ���ն�֡ʱ����֡��SN����     */
    INT8U                   MfSenFS;                                    /* ���Ͷ�֡ʱ����֡��FS����     */
    INT8U                   MfSenBS;                                    /* ���Ͷ�֡ʱ����֡��BS����     */
    INT8U                   MfSenSN;                                    /* ���Ͷ�֡ʱ����֡��SN����     */
    INT8U                   MfSenFcWaitCnt;                             /* ���Ͷ�֡ʱ�ȴ�����֡����     */
} TpStatStruct;
typedef struct {
    INT32U                  STmin;                                      /* ֡�����ʱ                   */
    INT32U                  Ar;                                         /* ���ն˷��ͳ�ʱ��ʱ           */
    INT32U                  As;                                         /* ���Ͷ˷��ͳ�ʱ��ʱ           */
    INT32U                  Bs;                                         /* �ȴ�����֡�ĳ�ʱ��ʱ         */
    INT32U                  Br;                                         /* ��������֡ǰ����ʱ��ʱ       */
    INT32U                  Cr;                                         /* �ȴ�����֡�ĳ�ʱ��ʱ         */
    INT32U                  Cs;                                         /* ��������֡ǰ����ʱ��ʱ       */
} TpTimeStruct;
typedef struct {
    TpFlagXXXXUnion         XXXX;                                       /*                              */
    BOOLEAN                 RcvLastCf;                                  /* �յ����һ֡����֡           */
    BOOLEAN                 MfSenFcNeed;                                /* ���Ͷ�֡ʱ��Ҫ��������֡     */
} TpFlagStruct;
typedef struct {
    TP_DEAL_PHY_ENUM        TpPhy;                                      /* ����Ѱַ���̿���             */
    TP_DEAL_FUN_ENUM        TpFun;                                      /* ����Ѱַ���̿���             */
} TpTaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    TpStatStruct            Stat;
    TpTimeStruct            Time;
    TpFlagStruct            Flag;
    TpTaskStruct            Task;
} TpInfoStruct;

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
extern  volatile TpPhyBufStruct     TpPhyBuf;                           /* ����Ѱַ���ջ�����           */
extern  volatile TpFunBufStruct     TpFunBuf;                           /* ����Ѱַ���ջ�����           */
extern  volatile TpPhyBufStruct     TpSenBuf;                           /* ���ͻ�����                   */
extern  volatile CanMsgStruct       CanSenMsgTp;                        /* ���ͱ���֡-TP                */
extern  volatile TpInfoStruct       TpInfo;                             /* ������Ϣ                     */

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    CanTp_Init(void);
extern  STAT_MSG_RESULT_ENUM    CanTp_DealRcvMsg(volatile CanMsgStruct *pMsg);
extern  void                    CanTp_TimeTask(void);
extern  void                    CanTp_StatTask(void);
extern  void                    CanTp_TxConfirm(void);
extern  BOOLEAN                 CanTp_DealSenBuf(INT32U ulLen, INT8U *pucDat);

/******************************************* Private Function *******************************************/
static  void                    CanTp_DealSenBufSF(INT32U ulLen, INT8U *pucDat);
static  void                    CanTp_DealSenBufMF(INT32U ulLen, INT8U *pucDat);
static  void                    CanTp_DealPhyTask(void);
static  void                    CanTp_DealFunTask(void);

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __CANTP_H                   */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
