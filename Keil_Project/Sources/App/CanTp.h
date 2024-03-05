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
** 宏定义
*********************************************************************************************************/
#define TP_T_UNIT                       2                               /* 调度时间                     */
#define TP_T_MS(n)                      (n/TP_T_UNIT)                   /* 时间宏定义, n需为2的倍数     */

#define TP_MSG_ID_FUN                   CAN_MSG_ID_DIAG_FUN             /* 功能诊断                     */
#define TP_MSG_ID_PHY                   CAN_MSG_ID_DIAG_PHY             /* 物理诊断                     */
#define TP_MSG_ID_RSP                   CAN_MSG_ID_DIAG_ACK             /* 诊断响应                     */

/*********************************************************************************************************
** 宏定义: ISO15765-2
*********************************************************************************************************/
#define TP_MF_BUF_LEN                   512                             /* 多帧缓冲区大小 -- 由诊断协议中最大数据量的指令决定 */
#define TP_MF_BUF_LEN_MAX               4096                            /* 实际无效果 */

#define TP_MF_STmin_FC                  TP_T_MS(20)                     /* 帧间隔默认最小值，发送流控帧时采用 */
#define TP_MF_STmin_DEFAULT             TP_T_MS(22)                     /* 帧间隔默认最小值，本地计时实际采用 *//* 2019-05-13 zhaohai 假设UNIT=2,即将误差由-2ms~+2ms调整为+0~+4ms */
#define N_AS                            TP_T_MS(70)                     /* 发送方N_PDU发送超时参数  -- 发送方数据是否发送超时，从开始发送到发送成功，发送FF,CF */
#define N_AR                            TP_T_MS(70)                     /* 接收方N_PDU发送超时参数  -- 接收方数据是否发送超时，从开始发送到发送成功，发送FC */
#define N_BS                            TP_T_MS(150)                    /* 等待接收流控帧的超时参数 -- 发送首帧/发送连续帧后，等待接收方发送流控帧的时间 */
#define N_BR                            TP_T_MS(2)                      /* 发送流控帧之前的等待时间 -- 收到首帧/收到连续帧后，开始发送流控帧前的等待时间 */
#define N_CS                            TP_T_MS(20)                     /* 发送连续帧之前的等待时间 -- 收到流控帧/发送连续帧后，开始发送连续帧前的等待时间，通常接近STmin */
#define N_CR                            TP_T_MS(150)                    /* 等待接收连续帧的超时参数 -- 发送流控帧/接收连续帧后，等待发送方发送连续帧的时间 */
#define N_WFT_MAX                       0                               /* 流控帧等待次数           -- 设置流控帧等待最大次数 */

#define TP_FC_EN                        TRUE                            /* 是否使用流控帧 */
#define TP_MF_BS_DEFAULT                8                               /* 多帧数据通信，block size 范围：1~255  不使用流控帧时 bs为0 */
#define TP_MSG_FILL_BYTE                0xAA                            /* 诊断报文填充字符 DKLai20230424 */

#if TP_FC_EN
#define TP_MF_BS                        TP_MF_BS_DEFAULT
#else
#define TP_MF_BS                        0
#endif
/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
#define TP_FC_FS_CTS                    0x00
#define TP_FC_FS_WT                     0x01
#define TP_FC_FS_OVFLW                  0x02

/*********************************************************************************************************
** 结构体: 缓冲区结构体
*********************************************************************************************************/
#define TP_PHY_BUF_LEN                  512                             /* 设置参数,Buf中报文容量       */
typedef struct {
    INT16U  Index;
    INT16U  Len;
    INT8U   ucDat[TP_PHY_BUF_LEN + 8];
} TpPhyBufStruct;
#define TP_FUN_BUF_LEN                    8                             /* 设置参数,Buf中报文容量       */
typedef struct {
    INT16U  Index;
    INT16U  Len;
    INT8U   ucDat[TP_FUN_BUF_LEN];
} TpFunBufStruct;

/*
 * 枚举
 */
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  XXXX                            :1;                     /*                              */
        INTCPU  YYYY                            :1;                     /*                              */
    } Bits;
} TpFlagXXXXUnion;
typedef enum {
    TP_DEAL_PHY_DEFAULT                 = 0,                            /* 默认                         */
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
    TP_DEAL_FUN_DEFAULT                 = 0,                            /* 默认                         */
    TP_DEAL_FUN_RCV_SF,                                                 /*                              */
} TP_DEAL_FUN_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT32U                  STmin;                                      /* 帧间隔设置                   */
    INT8U                   MfRcvFS;                                    /* 接收多帧时流控帧的FS设置     */
    INT8U                   MfRcvBS;                                    /* 接收多帧时连续帧的BS计数     */
    INT8U                   MfRcvSN;                                    /* 接收多帧时连续帧的SN计数     */
    INT8U                   MfSenFS;                                    /* 发送多帧时流控帧的FS设置     */
    INT8U                   MfSenBS;                                    /* 发送多帧时连续帧的BS计数     */
    INT8U                   MfSenSN;                                    /* 发送多帧时连续帧的SN计数     */
    INT8U                   MfSenFcWaitCnt;                             /* 发送多帧时等待连续帧计数     */
} TpStatStruct;
typedef struct {
    INT32U                  STmin;                                      /* 帧间隔计时                   */
    INT32U                  Ar;                                         /* 接收端发送超时计时           */
    INT32U                  As;                                         /* 发送端发送超时计时           */
    INT32U                  Bs;                                         /* 等待流控帧的超时计时         */
    INT32U                  Br;                                         /* 发送流控帧前的延时计时       */
    INT32U                  Cr;                                         /* 等待连续帧的超时计时         */
    INT32U                  Cs;                                         /* 发送连续帧前的延时计时       */
} TpTimeStruct;
typedef struct {
    TpFlagXXXXUnion         XXXX;                                       /*                              */
    BOOLEAN                 RcvLastCf;                                  /* 收到最后一帧连续帧           */
    BOOLEAN                 MfSenFcNeed;                                /* 发送多帧时需要接收流控帧     */
} TpFlagStruct;
typedef struct {
    TP_DEAL_PHY_ENUM        TpPhy;                                      /* 物理寻址流程控制             */
    TP_DEAL_FUN_ENUM        TpFun;                                      /* 功能寻址流程控制             */
} TpTaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    TpStatStruct            Stat;
    TpTimeStruct            Time;
    TpFlagStruct            Flag;
    TpTaskStruct            Task;
} TpInfoStruct;

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
extern  volatile TpPhyBufStruct     TpPhyBuf;                           /* 物理寻址接收缓冲区           */
extern  volatile TpFunBufStruct     TpFunBuf;                           /* 功能寻址接收缓冲区           */
extern  volatile TpPhyBufStruct     TpSenBuf;                           /* 发送缓冲区                   */
extern  volatile CanMsgStruct       CanSenMsgTp;                        /* 发送报文帧-TP                */
extern  volatile TpInfoStruct       TpInfo;                             /* 控制信息                     */

/*********************************************************************************************************
** 函数声明
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
