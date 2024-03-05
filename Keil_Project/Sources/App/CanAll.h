
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
** 宏定义 set stb io. DKLai20230423 
*********************************************************************************************************/
//#define CTRL_TJA_STB_H()                PINS_DRV_SetPins(  PTD, (INT32U)(1 << 0))
//#define CTRL_TJA_STB_L()                PINS_DRV_ClearPins(PTD, (INT32U)(1 << 0))
#define CTRL_TJA_STB_H()                PINS_DRV_SetPins(  PTB, (INT32U)(1 << 4))
#define CTRL_TJA_STB_L()                PINS_DRV_ClearPins(PTB, (INT32U)(1 << 4))  /* DKLai20230428 */
#define CTRL_TJA_STB_NORMAL()           {CTRL_TJA_STB_L();}
#define CTRL_TJA_STB_STANDY()           {CTRL_TJA_STB_H();}

#define CHCK_TJA_ERR()                  (PINS_DRV_ReadPins(PTB) & (1 << 1))
#define CHCK_TJA_ERR_IS_NORMAL()        (!CHCK_TJA_ERROR())//待查
#define CHCK_TJA_ERR_IS_ERROR()         (CHCK_TJA_ERROR())

/*********************************************************************************************************
** 宏定义-硬件发送缓冲区
*********************************************************************************************************/
#define CAN_HWTX_MODE_WAIT              0                               /* 发送后等待直到成功或超时     */
#define CAN_HWTX_MODE_RANDOM            1                               /* 发送时自动选Lowest硬件缓冲区 */
#define CAN_HWTX_MODE_FIXED             2                               /* 发送时APP-NM-DIAG各自固定缓冲区 */
#define CAN_HWTX_MODE                   CAN_HWTX_MODE_FIXED

#if CAN_HWTX_MODE == CAN_HWTX_MODE_FIXED
#define CAN_HWTX_NUM_APP                0                               /* 报文选择的硬件缓冲区编号     */
#define CAN_HWTX_NUM_APP2               1                               /* 报文选择的硬件缓冲区编号     */
#define CAN_HWTX_NUM_APP3               2                               /* 报文选择的硬件缓冲区编号     */
#define CAN_HWTX_NUM_NM                 3                               /* 报文选择的硬件缓冲区编号     */
#define CAN_HWTX_NUM_DIAG               4                               /* 报文选择的硬件缓冲区编号     */
#define CAN_HWTX_NUM_TOTAL              5                               /* 报文选择的硬件缓冲区总数     */
#endif
/*********************************************************************************************************
** 宏定义-报文编号 DKLai20230421
*********************************************************************************************************/
#define CAN_SEN_MSG_NUM_APP_VIB383      0                               /* 发送报文编号                 */
#define CAN_SEN_MSG_NUM_NM              1                               /* 发送报文编号                 */
#define CAN_SEN_MSG_NUM_DIAG            2                               /* 发送报文编号                 */
#define CAN_SEN_MSG_APP_TOTAL           1                               /* 发送APP报文总数              */
#define CAN_SEN_MSG_TOTAL               3                               /* 发送所有报文总数             */
#define CAN_SEN_MSG_APP_ALL             0xFF                            /* 发送APP报文-所有             */
#define CAN_SEN_MSG_ALL                 0xFF                            /* 发送报文-所有                */

#define CAN_RCV_MSG_NUM_APP_BCM318      0                               /* 接收报文编号 DKLai20230421   */
#define CAN_RCV_MSG_NUM_APP_ACU35A      1                               /* 接收报文编号                 */
#define CAN_RCV_MSG_NUM_APP_ICM31E      2                               /* 接收报文编号                 */
#define CAN_RCV_MSG_NUM_APP_VCU3F2      3                               /* 接收报文编号 DKLai20230907   */

/* DKLai20230907 */
#define CAN_RCV_MSG_NUM_APP_CDC093      4                               /* 接收报文编号                 */
#define CAN_RCV_MSG_NUM_APP_TEL097      5                               /* 接收报文编号                 */
#define CAN_RCV_MSG_APP_TOTAL           6                               /* 接收APP报文总数              */

#define CAN_RCV_MSG_APP_ALL             0xFF                            /* 接收APP报文-所有             */

/*********************************************************************************************************
** 结构体: 缓冲区结构体
*********************************************************************************************************/
/*
 * 报文帧(全篇只使用标准帧,所以没有ucType之类参数)
 */
#define CAN_MSG_LEN                     8                               /* 固定参数,Msg中数据容量,Byte  */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    INT8U   ucDat[CAN_MSG_LEN];
} CanMsgStruct;
/*
 * 缓冲区
 */
#define CAN_BUF_LEN                      16                             /* 设置参数,Buf中报文容量       */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    INT8U   IndexW;
    INT8U   IndexR;
    INT8U   Len;
    CanMsgStruct    Msg[CAN_BUF_LEN];
} CanBufStruct;

/*
 * 标志 DKLai20230421 
 */
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  MsgVIB383                       :1;                     /* 已确认的请求发送标志         */
        INTCPU  MsgNm                           :1;                     /* 已确认的请求发送标志         */
        INTCPU  MsgDiag                         :1;                     /* 已确认的请求发送标志         */
    } Bits;
} CanFlagSendUnion;
/*
 * 枚举
 */
typedef enum {
    CAN_DEAL_XXXX_DEFAULT               = 0,                            /* 默认                         */
    CAN_DEAL_XXXX_1,                                                    /*                              */
} CAN_DEAL_XXXX_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT8U                   XXXX;                                       /*                              */
    #if CAN_HWTX_MODE == CAN_HWTX_MODE_FIXED
    INT8U                   HwTxSt;                                     /* 硬件缓冲区Tx0~2是否正在使用  */
    #elif   CAN_HWTX_MODE == CAN_HWTX_MODE_RANDOM
    INT8U                   HwTxSelVIB383;                              /* 该报文发送时选择的硬件缓冲区 */
    INT8U                   HwTxSelNm;                                  /* 该报文发送时选择的硬件缓冲区 */
    INT8U                   HwTxSelDiag;                                /* 该报文发送时选择的硬件缓冲区 */
    #endif
} CanStatStruct;
typedef struct {
    INT32U                  XXXX;                                       /*                              */
} CanTimeStruct;
typedef struct {
    BOOLEAN                 CommTxDis;                                  /* 发送禁止                     */
    BOOLEAN                 CommTxDisApp;                               /* 应用报文发送禁止             */
    BOOLEAN                 CommRxDisApp;                               /* 应用报文接收禁止             */
    BOOLEAN                 CommTxDisNm;                                /* 网络报文通讯禁止             */
    BOOLEAN                 CommTxDisDiag;                              /* 诊断报文通讯禁止             */
    BOOLEAN                 TxTaskActive;                               /* 发送启动检测任务激活状态     */
    BOOLEAN                 TxConfirmActive;                            /* 发送成功检测任务激活状态     */
    CanFlagSendUnion        Send;                                       /*                              */
} CanFlagStruct;
typedef struct {
    CAN_DEAL_XXXX_ENUM      XXXX;                                       /* XXXX流程控制                 */
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
** 全局定量
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量: 缓冲区
*********************************************************************************************************/
extern  volatile CanBufStruct       CanRcvBuf;                          /* 接收缓冲区                   */
#if CAN_MSG_SEND_MODE == CAN_MSG_SEND_USE_BUF
extern  volatile CanBufStruct       CanSenBuf;                          /* 发送缓冲区                   */
#endif
extern  volatile CanInfoStruct      CanInfo;                            /* 控制信息                     */
extern  volatile CanMsgStruct       CanRcvMsgWake;                      /* 接收报文帧-唤醒              */

/*********************************************************************************************************
** 函数声明
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
