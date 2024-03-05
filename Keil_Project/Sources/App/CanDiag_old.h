/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           CanDiag.h
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
#ifndef __CANDIAG_H
#define __CANDIAG_H

#include "includeall.h"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define DIAG_T_UNIT                     100                             /* ����ʱ��                     */
#define DIAG_T_MS(n)                    (n/DIAG_T_UNIT)                 /* ʱ��궨��, n��Ϊ100�ı���   */

#define DIAG_EEP_BASE_ADDR              (EEP_BASE_ADDR + 0x000)         /* DIAG��ʼ��ַ 0x14000000      */
#define DIAG_EEP_TOTAL_SIZE             0x100                           /* DIAG�ռ��С 256Byte         */
#define DIAG_EEP_END_ADDR               (DIAG_EEP_BASE_ADDR + DIAG_EEP_TOTAL_SIZE - 1)  /* DIAG������ַ */

#define INTDIAGADDRU                    INTEEPADDRU
#define INTDIAGSIZEU                    INTEEPSIZEU

/* DKLai20230420 */
#define EEP_RESET_RESPONSE_FOR_DEFAULT_SESSION          0x01u           /**< \brief ��ӦĬ�ϻỰ���� */
#define EEP_RESET_RESPONSE_FOR_PROGRAM_SESSION          0x02u           /**< \brief ��Ӧ��̻Ự���� */
#define EEP_RESET_RESPONSE_FOR_HARDWARE_RESET           0x03u           /**< \brief ��ӦECU��λ���� */
#define EEP_RESET_RESPONSE_FOR_SOFTWARE_RESET           0x04u           /**< \brief ��ӦECU��λ���� */
#define EEP_RESET_FOR_ECU_RESET_SPRMIB                  0x05u           /**< \brief ECU��λ�����ֹ�϶���Ӧ */

#define __DIAG_FACTORYMODE_UNLOCK       0x10    /* 0x10~0xFF:unlock, 0x00~0x0F:lock. DKLai20230421 */  
#define __DIAG_FACTORYMODE_MP           0x00    /* MP:0x00 DKLai20230421 */

/*********************************************************************************************************
** �궨��: DIAG�ռ�: 0x14000000~0x140000FF
           ÿ��logical block��һ��meta data������Ŀֻ��һ��
*********************************************************************************************************/
#define DIAG_EEP_PROGREQ_VALID          0xB5                            /* ��Ч�ı�������־           */
#define DIAG_EEP_PROGREQ_INVALID        0xFF
#define DIAG_EEP_BLOCKVALID_BIT_APP     0                               /* BLOCKVALID��Bit0��ʾApp�Ƿ���Ч */
#define DIAG_EEP_ACCESSDELAY_ACTIVE     0xA7                            /* ��ȫ������ʱ����             */
#define DIAG_EEP_ACCESSDELAY_INACTIVE   0xFF                            /* ��ȫ������ʱδ����           */

/* Defines for general information part **************************************/
#define DIAG_EEP_ADDR_PROGREQ           DIAG_EEP_BASE_ADDR
#define DIAG_EEP_SIZE_PROGREQ           1
#define DIAG_EEP_ADDR_BLOCKVALID        (DIAG_EEP_ADDR_PROGREQ + DIAG_EEP_SIZE_PROGREQ)
#define DIAG_EEP_SIZE_BLOCKVALID        1
#define DIAG_EEP_ADDR_RESETRESP         (DIAG_EEP_ADDR_BLOCKVALID + DIAG_EEP_SIZE_BLOCKVALID)
#define DIAG_EEP_SIZE_RESETRESP         1
#define DIAG_EEP_ADDR_ACCESSDELAY       (DIAG_EEP_ADDR_RESETRESP + DIAG_EEP_SIZE_RESETRESP)
#define DIAG_EEP_SIZE_ACCESSDELAY       1
#define DIAG_EEP_ADDR_ACCESSINVALID     (DIAG_EEP_ADDR_ACCESSDELAY + DIAG_EEP_SIZE_ACCESSDELAY)
#define DIAG_EEP_SIZE_ACCESSINVALID     1

/* Defines for meta data part ************************************************/
#if 0   /* HYCAN require 10bytes. DKLai20230421 */

#define DIAG_EEP_ADDR_PROGDATE          (DIAG_EEP_ADDR_ACCESSINVALID + DIAG_EEP_SIZE_ACCESSINVALID)
#define DIAG_EEP_SIZE_PROGDATE          3

#else

#define DIAG_EEP_ADDR_SUPPLIERID        (DIAG_EEP_ADDR_ACCESSINVALID + DIAG_EEP_SIZE_ACCESSINVALID)
#define DIAG_EEP_SIZE_SUPPLIERID        1
#define DIAG_EEP_ADDR_PROGDATE          (DIAG_EEP_ADDR_SUPPLIERID + DIAG_EEP_SIZE_SUPPLIERID)
#define DIAG_EEP_SIZE_PROGDATE          3

#endif

#define DIAG_EEP_ADDR_TESTERNUM         (DIAG_EEP_ADDR_PROGDATE + DIAG_EEP_SIZE_PROGDATE)
#define DIAG_EEP_SIZE_TESTERNUM         6
#define DIAG_EEP_ADDR_PROGSUCCCNT       (DIAG_EEP_ADDR_TESTERNUM + DIAG_EEP_SIZE_TESTERNUM)
#define DIAG_EEP_SIZE_PROGSUCCCNT       2
#define DIAG_EEP_ADDR_PROGATTCNT        (DIAG_EEP_ADDR_PROGSUCCCNT + DIAG_EEP_SIZE_PROGSUCCCNT)
#define DIAG_EEP_SIZE_PROGATTCNT        2
#define DIAG_EEP_ADDR_CRC               (DIAG_EEP_ADDR_PROGATTCNT + DIAG_EEP_SIZE_PROGATTCNT)
#define DIAG_EEP_SIZE_CRC               4
#define DIAG_EEP_ADDR_CRCSTART          (DIAG_EEP_ADDR_CRC + DIAG_EEP_SIZE_CRC)
#define DIAG_EEP_SIZE_CRCSTART          4
#define DIAG_EEP_ADDR_CRCLENGTH         (DIAG_EEP_ADDR_CRCSTART + DIAG_EEP_SIZE_CRCSTART)
#define DIAG_EEP_SIZE_CRCLENGTH         4

#if 0   /* HYCAN require 10bytes. DKLai20230421 */

#define DIAG_EEP_ADDR_FINGERPRINT       (DIAG_EEP_ADDR_PROGDATE)
#define DIAG_EEP_SIZE_FINGERPRINT       (DIAG_EEP_SIZE_PROGDATE + DIAG_EEP_SIZE_TESTERNUM)

#else

#define DIAG_EEP_ADDR_FINGERPRINT       (DIAG_EEP_ADDR_SUPPLIERID)
#define DIAG_EEP_SIZE_FINGERPRINT       (DIAG_EEP_SIZE_SUPPLIERID + DIAG_EEP_SIZE_PROGDATE + DIAG_EEP_SIZE_TESTERNUM)

#endif

/* F199 4Bytes. DKLai20230421 */
#define DIAG_EEP_ADDR_PROGRAMDATE       (DIAG_EEP_ADDR_CRCLENGTH + DIAG_EEP_SIZE_CRCLENGTH)
#define DIAG_EEP_SIZE_PROGRAMDATE       4

/*********************************************************************************************************
** �궨��: 
*********************************************************************************************************/
#define CAN_MSG_ID_DIAG_PHY             PROJECT_DIAG_REQ_ID
#define CAN_MSG_ID_DIAG_FUN             0x7DF
#define CAN_MSG_LEN_DIAG_REQ            8

#define CAN_MSG_ID_DIAG_ACK             PROJECT_DIAG_RES_ID
#define CAN_MSG_LEN_DIAG_ACK            8

#define DIAG_22_MULT_READ_EN            TRUE                            /* 22����֧�ֶ��DID�� DKLai20230420 */
#define DIAG_27_CNT_CLR_ON_KEY_OK_EN    TRUE                            /* 27����ɹ���ʧ�ܼ�����0      */
#define DIAG_27_USE_OLD_SEED_EN         TRUE                            /* 27���������������ӷ��ؾ�ֵ   */
#define DIAG_T_ACCESS_DELAY             DIAG_T_MS(10000)                /* 27����ʧ�ܺ���ʱ����         */
#define DIAG_KEY_INVALID_MAX            3                               /* 27����������ʱ����ʧ�ܴ���   */
#define DIAG_28_NM_MSG_EN               FALSE                           /* 28����֧��������������� DKLai20230421 */

/* DKLai20230427 */
#define DIAG_FUNC_NOT_RESPONSE_11       TRUE                            /* ����Ѱַ����Ӧ��Ӧ��       */
#define DIAG_FUNC_NOT_RESPONSE_12       TRUE                            /* ����Ѱַ����Ӧ��Ӧ��       */
#define DIAG_FUNC_NOT_RESPONSE_31       TRUE                            /* ����Ѱַ����Ӧ��Ӧ��       */
#define DIAG_FUNC_NOT_RESPONSE_7E       TRUE                            /* ����Ѱַ����Ӧ��Ӧ��       *//* ISO14229-1(2006)Ҫ��Ӧ��ISO14229-1(2013)Ҫ��Ӧ�� */
#define DIAG_FUNC_NOT_RESPONSE_7F       TRUE                            /* ����Ѱַ����Ӧ��Ӧ��       *//* ISO14229-1(2006)Ҫ��Ӧ��ISO14229-1(2013)Ҫ��Ӧ�� */

/*********************************************************************************************************
** �궨��: UDS ��׼ ISO14229,ISO15765-3
*********************************************************************************************************/
#define DTC_STA_MASK                    DTC_STATUS_SUPPORT_MASK
#define DTC_DAT_FORMAT                  DTC_FORMAT_MODE

#define DIAG_P2_CAN_SERVER              50                  /* ��λ:1ms  ���������յ�������Ϣ�󵽷�����Ӧ��Ϣ��ʱ������Ҫ�� */
#define DIAG_P2_Ex_CAN_SERVER           500                 /* ��λ:10ms ���������ͷ���Ӧ��0x78�󣬵��������ٴη�����Ӧ��Ϣʱ�������Ҫ�� */
#define DIAG_T_S3_SERVER                DIAG_T_MS(5000)     /* �����ڷ�Ĭ����ϻỰ��ʱ�� 5s */

#define CanDiag_InitS3()\
{\
    DiagInfo.Time.S3            = 0;                    \
    DiagInfo.Flag.ProgressIng   = FALSE;                \
}
#define CanDiag_ReloadS3()\
{\
    DiagInfo.Time.S3            = DIAG_T_S3_SERVER;     \
    DiagInfo.Flag.ProgressIng   = TRUE;                 \
}
/*********************************************************************************************************
** ö��: ����Ӧ�� ISO14229  256ҳ
*********************************************************************************************************/
typedef enum
{
    DIAG_NR_NULL                        = (INT8U)0x00,      /* û�з��룬���� */
    DIAG_NR_GENERAL_REJECT              = (INT8U)0x10,      /* General reject */
    DIAG_NR_SRV_NOT_SUPPORT             = (INT8U)0x11,      /* ��֧���������Ϸ��� serviceNotSupported */
    DIAG_NR_SUB_NOT_SUPPORT             = (INT8U)0x12,      /* ��֧�����������ӹ��� subFunctionNotSupported */
    DIAG_NR_LENGTH_ERR                  = (INT8U)0x13,      /* ���ݳ��ȴ�����ʽ���� incorrectMessageLengthOrInvalidFormat */
    DIAG_NR_BUSY                        = (INT8U)0x21,      /* ������æ busyRespeatRequest */
    DIAG_NR_CONDITION_ERR               = (INT8U)0x22,      /* ������ִ����Ϸ�������������� conditionsNotCorrect */
    DIAG_NR_SEQUENCE_ERR                = (INT8U)0x24,      /* ˳����� requestSequenceError */
    DIAG_NR_OUT_RANGE                   = (INT8U)0x31,      /* ������û�пͻ������������ requestOutOfRange */
    DIAG_NR_SECURITY_DENY               = (INT8U)0x33,      /* ��ȫ���ʾܾ� securityAccessDenied */
    DIAG_NR_INVALID_KEY                 = (INT8U)0x35,      /* ��������Ϊ������Կ���� invalidKey */
    DIAG_NR_EXCEED_ATTEMPTS             = (INT8U)0x36,      /* �������Դ��� exceedNumberOfAttempts */
    DIAG_NR_OVER_TIME                   = (INT8U)0x37,      /* ������ʱ�׶� requiredTimeDelayNotExpired */
    DIAG_NR_LOAD_NOT_ACCEPTED           = (INT8U)0x70,      /* �������ܾ��ڴ���ϴ�/���ز��� uploadDownloadNotAccepted */
    DIAG_NR_TRANSFER_SUSPENDED          = (INT8U)0x71,      /* �����ֹ���ݴ��� transferDataSuspended */
    DIAG_NR_PROGRAM_FAILURE             = (INT8U)0x72,      /* ����������,���ִ����ֹͣ generalProgrammingFailure */
    DIAG_NR_DL_BLOCK_CNT_ERR            = (INT8U)0x73,      /* �������ݹ�����,����BLOCK�������� wrongBlockSequenceCounter */
    DIAG_NR_POS_RESP_PENDING            = (INT8U)0x78,      /* requestCorrectlyReceived-ResponsePending */
    DIAG_NR_SUB_NOT_SUPPORT_IN_SESSION  = (INT8U)0x7E,      /* subFunctionNotSupportedInActiveSession  ��ģʽ�²�֧�ִ˷�����ӹ��� */
    DIAG_NR_SRV_NOT_SUPPORT_IN_SESSION  = (INT8U)0x7F,      /* serviceNotSupportedInActiveSession */
    
} DIAG_NRC_ENUM;

/*********************************************************************************************************
** �ṹ��: �������ṹ��
*********************************************************************************************************/
/* Context information of a request */
typedef struct
{
    INTCPU      ReqType                         :2;                     /* 0x01: Phys 0x02: Func        */
    INTCPU      ResOnReq                        :2;                     /* 0x01: Phys 0x02: Func        */
    INTCPU      SuppPosRes                      :1;                     /* 0x00: No   0x02: Yes         */
} DiagAddInfo;
typedef struct
{
    INT8U              *ReqDat;
    INT16U              ReqLen;
    INT8U              *ResDat;
    INT16U              ResLen;
    DiagAddInfo         AddInfo;
} DiagContextStruct;
#define DIAG_RES_BUF_LEN                512                             /* ���ò���,Buf�б�������       */
typedef struct {
    INT16U  Index;
    INT16U  Len;
    INT8U   ucDat[DIAG_RES_BUF_LEN];
} DiagResBufStruct;

/*
 * ö��
 */
typedef enum {
	DIAG_REQTYPE_PHYS                   = 0x00,                         /* ����Ѱַ                     */
	DIAG_REQTYPE_FUNC                                                   /* ����Ѱַ                     */
} DIAG_REQTYPE_ENUM;
typedef enum {
	DIAG_SESSION_DEFAULT                = 0x01,                         /* Ĭ�ϻỰ                     */
	DIAG_SESSION_PROGRAM                = 0x02,                         /* ��̻Ự                     */
	DIAG_SESSION_EXTENDED               = 0x03,                         /* ��չ�Ự                     */
} DIAG_SESSION_ENUM;
typedef enum {
	DIAG_SECURITY_INVALID               = 0x00,                         /* ��Ч                         */
	DIAG_SECURITY_L1                    = 0x55,                         /* Level1                       */
	DIAG_SECURITY_L2                    = 0x66,                         /* Level2                       */
	DIAG_SECURITY_LFBL                  = 0xAA,                         /* LevelFlash                   */
} DIAG_SECURITY_ENUM;
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  XXXX                            :1;                     /*                              */
    } Bits;
} DiagFlagEepWrtUnion;
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  XXXX                            :1;                     /*                              */
    } Bits;
} DiagFlagEepRadUnion;
typedef enum {
    DIAG_DEAL_XXXX_DEFAULT              = 0,                            /* Ĭ��                         */
    DIAG_DEAL_XXXX_1,                                                   /*                              */
} DIAG_DEAL_XXXX_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    DIAG_REQTYPE_ENUM       ReqType;                                    /* Ѱַģʽ                     */
    DIAG_SESSION_ENUM       Session;                                    /* �Ựģʽ                     */
    DIAG_SECURITY_ENUM      Security;                                   /* ���ܵȼ�                     */
    DIAG_SECURITY_ENUM      SecurityReq;                                /* ����������ܵȼ�             */
    INT8U                   AccessInvalid;                              /* ʧ����֤����                 */
    INT8U                   AuthSeed[4];                                /* ����                         */
    INT8U                   AuthKey[4];                                 /* ��Կ                         */
} DiagStatStruct;
typedef struct {
    INT32U                  S3;                                         /* ��Ĭ�ϻỰ���ּ�ʱ           */
    INT32U                  AccessDelay;                                /* ��֤ʧ�ܵ���ʱ               */
} DiagTimeStruct;
typedef struct {
    BOOLEAN                 PhyID;                                      /* ����ѰַID                   */
    BOOLEAN                 ProgressIng;                                /* ��Ϲ�����                   */
    BOOLEAN                 DtcClrIng;                                  /* ���DTC������                */
    BOOLEAN                 ReqReset;                                   /* ����λ                     */
    BOOLEAN                 IsKeyWaited;                                /* ���ڵȴ���Կ                 */
    BOOLEAN                 CommTxDisApp;                               /* Ӧ�ñ��ķ��ͽ�ֹ             */
    BOOLEAN                 CommRxDisApp;                               /* Ӧ�ñ��Ľ��ս�ֹ             */
    BOOLEAN                 CommTxDisNm;                                /* ���籨��ͨѶ��ֹ             */
    BOOLEAN                 DtcSetDis;                                  /* DTC���ý�ֹ                  */
    DiagFlagEepWrtUnion     EepWrt;                                     /*                              */
    DiagFlagEepRadUnion     EepRad;                                     /*                              */
} DiagFlagStruct;
typedef struct {
    DIAG_DEAL_XXXX_ENUM     XXXX;                                       /* XXXX���̿���                 */
} DiagTaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    DiagStatStruct          Stat;
    DiagTimeStruct          Time;
    DiagFlagStruct          Flag;
    DiagTaskStruct          Task;
} DiagInfoStruct;

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
extern  volatile CanMsgStruct       CanRcvMsgDiag;                      /* ���ձ���֡-���              */
extern  volatile CanMsgStruct       CanSenMsgDiag;                      /* ���ͱ���֡-���              */
extern  volatile DiagContextStruct  DiagContext;                        /* Context information of a request */
extern  volatile DiagResBufStruct   DiagResBuf;                         /* ��Ӧ������                   */
extern  volatile DiagInfoStruct     DiagInfo;                           /* ������Ϣ                     */

extern  volatile INT8U              __g_factorymode;                    /* DKLai20230421 */

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    CanDiag_Init(void);
extern  STAT_MSG_RESULT_ENUM    CanDiag_DealRcvMsg(volatile CanMsgStruct *pMsg);
extern  BOOLEAN                 CanDiag_ReqSenMsg(volatile CanMsgStruct *pMsg);
extern  void                    CanDiag_Dispatcher(volatile DiagContextStruct *pContext);
extern  void                    CanDiag_TimeTask(void);
extern  void                    CanDiag_StatTask(void);
extern  void                    CanDiag_TxStart(STAT_MSG_RESULT_ENUM euDealRslt);
extern  void                    CanDiag_TxConfirm(void);

extern  void                    CanDiag_NegResponse(INT8U ucSid, DIAG_NRC_ENUM euNrc);
extern  void                    CanDiag_PosResponse(volatile DiagContextStruct *pContext);

extern  STAT_MSG_RESULT_ENUM    CanDiag_ReadFromEep(INTDIAGADDRU Add, INTDIAGSIZEU Len, INT8U *pucDatDst, EEP_EXTRA_ENUM euExtra);
extern  STAT_MSG_RESULT_ENUM    CanDiag_WriteToEep(INTDIAGADDRU Add, INTDIAGSIZEU Len, INT8U *pucDatSor, EEP_EXTRA_ENUM euExtra);

extern  void                    CanDiag_WriteEepTask(void);
extern  void                    CanDiag_ReadEepTask(void);

extern  void                    CanDiag_FactoryModeCTRL(void);    /* DKLai20230421 */

extern  DIAG_SECURITY_ENUM      CanDiag_SecurityGet(void);

extern  BOOLEAN                 CanDiag_AccessDelaySet(void);
extern  BOOLEAN                 CanDiag_AccessDelayClr(void);
extern  BOOLEAN                 CanDiag_AccessDelayCheck(void);
extern  BOOLEAN                 CanDiag_AccessInvalidWrite(INT8U *pucDat);
extern  BOOLEAN                 CanDiag_AccessInvalidRead(INT8U *pucDat);

extern  BOOLEAN                 CanDiag_ProgReqSet(void);

extern  BOOLEAN                 CanDiag_FactoryModeCheck(void);  /* DKLai20230421 */

/******************************************* Private Function *******************************************/

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __CANDIAG_H                 */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
