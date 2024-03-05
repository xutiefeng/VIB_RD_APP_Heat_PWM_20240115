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
** 宏定义
*********************************************************************************************************/
#define DIAG_T_UNIT                     100                             /* 调度时间                     */
#define DIAG_T_MS(n)                    (n/DIAG_T_UNIT)                 /* 时间宏定义, n需为100的倍数   */

#define DIAG_EEP_BASE_ADDR              (EEP_BASE_ADDR + 0x000)         /* DIAG起始地址 0x14000000      */
#define DIAG_EEP_TOTAL_SIZE             0x100                           /* DIAG空间大小 256Byte         */
#define DIAG_EEP_END_ADDR               (DIAG_EEP_BASE_ADDR + DIAG_EEP_TOTAL_SIZE - 1)  /* DIAG结束地址 */

#define INTDIAGADDRU                    INTEEPADDRU
#define INTDIAGSIZEU                    INTEEPSIZEU

/* DKLai20230420 */
#define EEP_RESET_RESPONSE_FOR_DEFAULT_SESSION          0x01u           /**< \brief 响应默认会话服务 */
#define EEP_RESET_RESPONSE_FOR_PROGRAM_SESSION          0x02u           /**< \brief 响应编程会话服务 */
#define EEP_RESET_RESPONSE_FOR_HARDWARE_RESET           0x03u           /**< \brief 响应ECU复位服务 */
#define EEP_RESET_RESPONSE_FOR_SOFTWARE_RESET           0x04u           /**< \brief 响应ECU复位服务 */
#define EEP_RESET_FOR_ECU_RESET_SPRMIB                  0x05u           /**< \brief ECU复位服务禁止肯定响应 */

#define __DIAG_FACTORYMODE_UNLOCK       0x10    /* 0x10~0xFF:unlock, 0x00~0x0F:lock. DKLai20230421 */  
#define __DIAG_FACTORYMODE_MP           0x00    /* MP:0x00 DKLai20230421 */

/*********************************************************************************************************
** 宏定义: DIAG空间: 0x14000000~0x140000FF
           每个logical block有一份meta data，该项目只有一份
*********************************************************************************************************/
#define DIAG_EEP_PROGREQ_VALID          0xB5                            /* 有效的编程请求标志           */
#define DIAG_EEP_PROGREQ_INVALID        0xFF
#define DIAG_EEP_BLOCKVALID_BIT_APP     0                               /* BLOCKVALID的Bit0表示App是否有效 */
#define DIAG_EEP_ACCESSDELAY_ACTIVE     0xA7                            /* 安全访问延时激活             */
#define DIAG_EEP_ACCESSDELAY_INACTIVE   0xFF                            /* 安全访问延时未激活           */

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
** 宏定义: 
*********************************************************************************************************/
#define CAN_MSG_ID_DIAG_PHY             PROJECT_DIAG_REQ_ID
#define CAN_MSG_ID_DIAG_FUN             0x7DF
#define CAN_MSG_LEN_DIAG_REQ            8

#define CAN_MSG_ID_DIAG_ACK             PROJECT_DIAG_RES_ID
#define CAN_MSG_LEN_DIAG_ACK            8

#define DIAG_22_MULT_READ_EN            TRUE                            /* 22服务支持多个DID读 DKLai20230420 */
#define DIAG_27_CNT_CLR_ON_KEY_OK_EN    TRUE                            /* 27服务成功后失败计数清0      */
#define DIAG_27_USE_OLD_SEED_EN         TRUE                            /* 27服务连续请求种子返回旧值   */
#define DIAG_T_ACCESS_DELAY             DIAG_T_MS(10000)                /* 27服务失败后延时设置         */
#define DIAG_KEY_INVALID_MAX            3                               /* 27服务启动延时功能失败次数   */
#define DIAG_28_NM_MSG_EN               FALSE                           /* 28服务支持网络管理报文设置 DKLai20230421 */

/* DKLai20230427 */
#define DIAG_FUNC_NOT_RESPONSE_11       TRUE                            /* 功能寻址否定响应不应答       */
#define DIAG_FUNC_NOT_RESPONSE_12       TRUE                            /* 功能寻址否定响应不应答       */
#define DIAG_FUNC_NOT_RESPONSE_31       TRUE                            /* 功能寻址否定响应不应答       */
#define DIAG_FUNC_NOT_RESPONSE_7E       TRUE                            /* 功能寻址否定响应不应答       *//* ISO14229-1(2006)要求应答，ISO14229-1(2013)要求不应答 */
#define DIAG_FUNC_NOT_RESPONSE_7F       TRUE                            /* 功能寻址否定响应不应答       *//* ISO14229-1(2006)要求应答，ISO14229-1(2013)要求不应答 */

/*********************************************************************************************************
** 宏定义: UDS 标准 ISO14229,ISO15765-3
*********************************************************************************************************/
#define DTC_STA_MASK                    DTC_STATUS_SUPPORT_MASK
#define DTC_DAT_FORMAT                  DTC_FORMAT_MODE

#define DIAG_P2_CAN_SERVER              50                  /* 单位:1ms  服务器接收到请求消息后到发出响应消息的时间性能要求 */
#define DIAG_P2_Ex_CAN_SERVER           500                 /* 单位:10ms 服务器发送否定响应码0x78后，到服务器再次发送响应消息时间的性能要求 */
#define DIAG_T_S3_SERVER                DIAG_T_MS(5000)     /* 保持在非默认诊断会话的时间 5s */

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
** 枚举: 否定响应码 ISO14229  256页
*********************************************************************************************************/
typedef enum
{
    DIAG_NR_NULL                        = (INT8U)0x00,      /* 没有否定码，正常 */
    DIAG_NR_GENERAL_REJECT              = (INT8U)0x10,      /* General reject */
    DIAG_NR_SRV_NOT_SUPPORT             = (INT8U)0x11,      /* 不支持请求的诊断服务 serviceNotSupported */
    DIAG_NR_SUB_NOT_SUPPORT             = (INT8U)0x12,      /* 不支持请求服务的子功能 subFunctionNotSupported */
    DIAG_NR_LENGTH_ERR                  = (INT8U)0x13,      /* 数据长度错误或格式错误 incorrectMessageLengthOrInvalidFormat */
    DIAG_NR_BUSY                        = (INT8U)0x21,      /* 服务器忙 busyRespeatRequest */
    DIAG_NR_CONDITION_ERR               = (INT8U)0x22,      /* 服务器执行诊断服务的条件不满足 conditionsNotCorrect */
    DIAG_NR_SEQUENCE_ERR                = (INT8U)0x24,      /* 顺序错误 requestSequenceError */
    DIAG_NR_OUT_RANGE                   = (INT8U)0x31,      /* 服务器没有客户端请求的数据 requestOutOfRange */
    DIAG_NR_SECURITY_DENY               = (INT8U)0x33,      /* 安全访问拒绝 securityAccessDenied */
    DIAG_NR_INVALID_KEY                 = (INT8U)0x35,      /* 服务器认为返回密钥错误 invalidKey */
    DIAG_NR_EXCEED_ATTEMPTS             = (INT8U)0x36,      /* 超出尝试次数 exceedNumberOfAttempts */
    DIAG_NR_OVER_TIME                   = (INT8U)0x37,      /* 请求延时阶段 requiredTimeDelayNotExpired */
    DIAG_NR_LOAD_NOT_ACCEPTED           = (INT8U)0x70,      /* 服务器拒绝内存的上传/下载操作 uploadDownloadNotAccepted */
    DIAG_NR_TRANSFER_SUSPENDED          = (INT8U)0x71,      /* 因故中止数据传输 transferDataSuspended */
    DIAG_NR_PROGRAM_FAILURE             = (INT8U)0x72,      /* 擦除或编程中,发现错误而停止 generalProgrammingFailure */
    DIAG_NR_DL_BLOCK_CNT_ERR            = (INT8U)0x73,      /* 发送数据过程中,发现BLOCK计数错误 wrongBlockSequenceCounter */
    DIAG_NR_POS_RESP_PENDING            = (INT8U)0x78,      /* requestCorrectlyReceived-ResponsePending */
    DIAG_NR_SUB_NOT_SUPPORT_IN_SESSION  = (INT8U)0x7E,      /* subFunctionNotSupportedInActiveSession  该模式下不支持此服务和子功能 */
    DIAG_NR_SRV_NOT_SUPPORT_IN_SESSION  = (INT8U)0x7F,      /* serviceNotSupportedInActiveSession */
    
} DIAG_NRC_ENUM;

/*********************************************************************************************************
** 结构体: 缓冲区结构体
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
#define DIAG_RES_BUF_LEN                512                             /* 设置参数,Buf中报文容量       */
typedef struct {
    INT16U  Index;
    INT16U  Len;
    INT8U   ucDat[DIAG_RES_BUF_LEN];
} DiagResBufStruct;

/*
 * 枚举
 */
typedef enum {
	DIAG_REQTYPE_PHYS                   = 0x00,                         /* 物理寻址                     */
	DIAG_REQTYPE_FUNC                                                   /* 功能寻址                     */
} DIAG_REQTYPE_ENUM;
typedef enum {
	DIAG_SESSION_DEFAULT                = 0x01,                         /* 默认会话                     */
	DIAG_SESSION_PROGRAM                = 0x02,                         /* 编程会话                     */
	DIAG_SESSION_EXTENDED               = 0x03,                         /* 扩展会话                     */
} DIAG_SESSION_ENUM;
typedef enum {
	DIAG_SECURITY_INVALID               = 0x00,                         /* 无效                         */
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
    DIAG_DEAL_XXXX_DEFAULT              = 0,                            /* 默认                         */
    DIAG_DEAL_XXXX_1,                                                   /*                              */
} DIAG_DEAL_XXXX_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    DIAG_REQTYPE_ENUM       ReqType;                                    /* 寻址模式                     */
    DIAG_SESSION_ENUM       Session;                                    /* 会话模式                     */
    DIAG_SECURITY_ENUM      Security;                                   /* 加密等级                     */
    DIAG_SECURITY_ENUM      SecurityReq;                                /* 正在请求加密等级             */
    INT8U                   AccessInvalid;                              /* 失败认证计数                 */
    INT8U                   AuthSeed[4];                                /* 种子                         */
    INT8U                   AuthKey[4];                                 /* 密钥                         */
} DiagStatStruct;
typedef struct {
    INT32U                  S3;                                         /* 非默认会话保持计时           */
    INT32U                  AccessDelay;                                /* 认证失败倒计时               */
} DiagTimeStruct;
typedef struct {
    BOOLEAN                 PhyID;                                      /* 物理寻址ID                   */
    BOOLEAN                 ProgressIng;                                /* 诊断过程中                   */
    BOOLEAN                 DtcClrIng;                                  /* 清除DTC过程中                */
    BOOLEAN                 ReqReset;                                   /* 请求复位                     */
    BOOLEAN                 IsKeyWaited;                                /* 正在等待密钥                 */
    BOOLEAN                 CommTxDisApp;                               /* 应用报文发送禁止             */
    BOOLEAN                 CommRxDisApp;                               /* 应用报文接收禁止             */
    BOOLEAN                 CommTxDisNm;                                /* 网络报文通讯禁止             */
    BOOLEAN                 DtcSetDis;                                  /* DTC设置禁止                  */
    DiagFlagEepWrtUnion     EepWrt;                                     /*                              */
    DiagFlagEepRadUnion     EepRad;                                     /*                              */
} DiagFlagStruct;
typedef struct {
    DIAG_DEAL_XXXX_ENUM     XXXX;                                       /* XXXX流程控制                 */
} DiagTaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    DiagStatStruct          Stat;
    DiagTimeStruct          Time;
    DiagFlagStruct          Flag;
    DiagTaskStruct          Task;
} DiagInfoStruct;

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
extern  volatile CanMsgStruct       CanRcvMsgDiag;                      /* 接收报文帧-诊断              */
extern  volatile CanMsgStruct       CanSenMsgDiag;                      /* 发送报文帧-诊断              */
extern  volatile DiagContextStruct  DiagContext;                        /* Context information of a request */
extern  volatile DiagResBufStruct   DiagResBuf;                         /* 响应缓冲区                   */
extern  volatile DiagInfoStruct     DiagInfo;                           /* 控制信息                     */

extern  volatile INT8U              __g_factorymode;                    /* DKLai20230421 */

/*********************************************************************************************************
** 函数声明
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
