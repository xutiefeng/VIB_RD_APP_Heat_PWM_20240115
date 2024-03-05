
/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           CanApp.h
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
#ifndef __CANAPP_H
#define __CANAPP_H

// #include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
#define APP_T_UNIT                      2                               /* 调度时间                     */
#define APP_T_MS(n)                     (n/APP_T_UNIT)                  /* 时间宏定义, n需为2的倍数     */

#define APP_RCV_TIMEOUT_SUBS_CYCLE      5                               /* 设置替代值超时周期数         */
#define APP_RCV_TIMEOUT_LOST_CYCLE      10                              /* 设置丢失超时周期数           */
#define APP_RCV_CONTIN_CNT_MAX          1                               /* 设置连续接收计数             */
#define APP_RCV_ERROR_CONFIRM_CYCLE     3                               /* 设置错误确认周期数           */

#define CAN_MSG_ID_BCM318               0x318                           /* DKLai20230421 */
#define CAN_MSG_ID_ACU35A               0x35A
#define CAN_MSG_ID_ICM31E               0x31E                           /* DKLai20230421 */
#define CAN_MSG_ID_CDC093               0x093                           /* DKLai20230421 */
#define CAN_MSG_ID_TEL097               0x097                           /* DKLai20230421 */
#define CAN_MSG_ID_VCU3F2               0x3F2                           /* DKLai20230907 */

#define CAN_MSG_ID_VIB383               PROJECT_APP_SEN_ID

#define CAN_MSG_LEN_BCM318              8                               /* DKLai20230421 */
#define CAN_MSG_LEN_ACU35A              8
#define CAN_MSG_LEN_ICM31E              8
#define CAN_MSG_LEN_CDC093              8                               /* event signal. DKLai20230421 */
#define CAN_MSG_LEN_TEL097              8
#define CAN_MSG_LEN_VCU3F2              8                               /* DKLai20230907 */

#define CAN_MSG_LEN_VIB383              8

#define CAN_MSG_CYCLE_BCM318            100                             /* 设置接收报文周期,单位: ms DKLai20230421   */
#define CAN_MSG_CYCLE_ACU35A            1000
#define CAN_MSG_CYCLE_ICM31E            1000
#define CAN_MSG_CYCLE_VCU3F2            100                             /* 设置接收报文周期,单位: ms DKLai20230907   */

#define CAN_MSG_CYCLE_VIB383            200                             /* 设置正常发送周期,单位: ms DKLai20230630 */

#define CAN_MSG_ENENT_VIB383            40                              /* 设置快速发送周期,单位: ms DKLai20230425 */

/*********************************************************************************************************
** 枚举
*********************************************************************************************************/
typedef enum {
    APP_TIMEOUT_SUBS                    = 0,                            /* 超时标志-SUBS                */
    APP_TIMEOUT_LOST,                                                   /* 超时标志-LOST                */
    APP_TIMEOUT_ALL,                                                    /* 全部                         */
} APP_TIMEOUT_ENUM;
typedef enum {
    APP_ERROR_LIVE                      = 0,                            /* 错误标志-LIVE                */
    APP_ERROR_CONFIRM,                                                  /* 错误标志-CONFIRM             */
    APP_ERROR_ALL,                                                      /* 全部                         */
} APP_ERROR_ENUM;

/*********************************************************************************************************
** 结构体: 报文帧结构体
*********************************************************************************************************/
/*
 * 报文帧-接收 
 */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    union {
        INT8U   _Byte[CAN_MSG_LEN_BCM318];   /* DKLai20230421 */
        struct {
            INTCPU  BCM_KeySt                       :2; /* DKLai20230504 */
            INTCPU                                  :6;
            
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
        } Bits;
    } ucDat;
} CanRcvMsgBCM318Struct;   /* DKLai20230421 */

/* DKLai20230504 */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    union {
        INT8U   _Byte[CAN_MSG_LEN_ACU35A];
        struct {
            INTCPU  timeInfoYear                    :8;
					
            INTCPU  timeInfoDayH                    :4;
            INTCPU  timeInfoMonth                   :4;
					
            INTCPU  timeInfoMinuteH                 :2;
            INTCPU  timeInfoHour                    :5;
            INTCPU  timeInfoDayL                    :1;
            
            INTCPU  timeInfoSecondH                 :4;
            INTCPU  timeInfoMinuteL                 :4;
            
            INTCPU                                  :6;
            INTCPU  timeInfoSecondL                 :2;
            
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
        } Bits;
    } ucDat;
} CanRcvMsgACU35AStruct;

/* DKLai20230504 */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    union {
        INT8U   _Byte[CAN_MSG_LEN_ICM31E];
        struct {
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            
            INTCPU  OdoH                            :8;
            INTCPU  OdoM                            :8;  
            INTCPU  OdoL                            :8;
            
            INTCPU                                  :8;
            INTCPU                                  :8;
        } Bits;
    } ucDat;
} CanRcvMsgICM31EStruct;

/* DKLai20230421 */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    union {
        INT8U   _Byte[CAN_MSG_LEN_CDC093];
        struct {
            INTCPU    notused                              :8;
        } Bits;
    } ucDat;
} CanRcvMsgCDC093Struct;

/* DKLai20230421 */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    union {
        INT8U   _Byte[CAN_MSG_LEN_TEL097];
        struct {
            INTCPU    notused                              :8;
        } Bits;
    } ucDat;
} CanRcvMsgTEL097Struct;

/* DKLai20230907 */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    union {
        INT8U   _Byte[CAN_MSG_LEN_VCU3F2];   
        struct {
            INTCPU                                  :8; 
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU   vibmodecfg                     :3;
            INTCPU   vibpwroff                      :1;
            INTCPU                                  :4;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
        } Bits;
    } ucDat;
} CanRcvMsgVCU3F2Struct;   

/*
 * 报文帧-发送 DKLai20230419
 */
typedef struct {
    BOOLEAN blAllowW;
    BOOLEAN blAllowR;
    BOOLEAN blNew;
    INT8U   ucDlc;
    INT32U  ulId;
    union {
        INT8U   _Byte[CAN_MSG_LEN_VIB383];
        struct {
            INTCPU  LeftPositionLampSts             :1;
            INTCPU  LeftPositionLampFault           :1;
            INTCPU  LeftRearfogLampSts              :1;
            INTCPU  LeftRearfogLampFault            :1;
            INTCPU  LeftReverseLampSts              :1;
            INTCPU  LeftReversingLampFault          :1;
            INTCPU  LeftTurnLampSts                 :1;
            INTCPU  LeftStopLampSts                 :1;
            
            INTCPU  LeftTurnLampFault               :2;
            INTCPU  LeftStopLampFault               :1;
            INTCPU                                  :5;
            
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
            INTCPU                                  :8;
        } Bits;
    } ucDat;
} CanSenMsgVIB383Struct;

/*
 * 标志:状态
 */
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU vcuvibpwroff                     :1;
    } Bits;
} AppFlagCtrlUnion;

/*
 * 报文控制信息
 */
typedef union {
    INT8U   Byte[1];
    struct {
        INTCPU  CycleEn                         :1;                     /* 周期性报文标志 1:周期型 0:非周期型 */
        INTCPU                                  :1;
        INTCPU  SenReq                          :1;                     /* APP内部请求发送标志 1:时间到等原因请求发送 */
    } Bits;
} AppMsgSenStatUnion;

typedef struct {
    INT16U              TimeMin;                                        /* 报文发送最小间隔             */
    INT16U              TimeCycle;                                      /* 正常发送周期计时             */
    INT16U              TimeEvent;                                      /* 快速发送周期计时             */
    INT16U              EventCnt;                                       /* 快速发送计数                 */
    AppMsgSenStatUnion  SenStat;
} AppMsgSenCtrlStruct;

typedef union {
    INT8U   Byte[1];
    struct {
        INTCPU  TimeOutEn                       :1;                     /* 是否使能超时检测 1:使能 0:禁能 */
        INTCPU                                  :1;
        INTCPU  TimeOutSubs                     :1;                     /* 超时标志                     *///专用于设置故障替代值, 超时APP_RCV_TIMEOUT_SUBS_CYCLE帧时置位,收到1帧即清除
        INTCPU  TimeOutLost                     :1;                     /* 超时标志                     *///专用于记录节点丢失DTC,超时APP_RCV_TIMEOUT_LOST_CYCLE帧时置位,收到APP_RCV_CONTIN_CNT_MAX帧清除
        INTCPU  ContinSucc                      :1;                     /* 连续接收成功标志             *///专用于清除节点丢失DTC,收到APP_RCV_CONTIN_CNT_MAX帧时置位,超时1个周期时清除
        INTCPU  ErrorLive                       :1;                     /* 错误标志                     *///专用于记录无效DTC,实时状态,收到有错误时置位,                     收到无错误时清除
        INTCPU  ErrorConfirm                    :1;                     /* 错误标志                     *///专用于记录无效DTC,确认状态,错误维持APP_ERROR_CONFIRM_CYCLE时置位,收到无错误时清除
    } Bits;
} AppMsgRcvStatUnion;

typedef struct {
    INT16U              TimeOut;                                        /* 超时计时                     */
    INT8U               ContinCnt;                                      /* 连续接收计数                 */
    INT16U              TimeError;                                      /* 错误计时                     */
    AppMsgRcvStatUnion  RcvStat;
} AppMsgRcvCtrlStruct;

/*
 * 枚举
 */
typedef enum {
    APP_DEAL_XXXX_DEFAULT               = 0,                            /* 默认                         */
    APP_DEAL_XXXX_1,                                                    /*                              */
} APP_DEAL_XXXX_ENUM;

/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT8U                   XXXX;                                       /*                              */
} AppStatStruct;

typedef struct {
    INT32U                  XXXX;                                       /*                              */
} AppTimeStruct;

typedef struct {
    AppFlagCtrlUnion        Ctrl;                                       /*                              */
} AppFlagStruct;

typedef struct {
    APP_DEAL_XXXX_ENUM      XXXX;                                       /* XXXX流程控制                 */
} AppTaskStruct;

/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    AppStatStruct           Stat;
    AppTimeStruct           Time;
    AppFlagStruct           Flag;
    AppTaskStruct           Task;
    AppMsgSenCtrlStruct     SenCtrl[CAN_SEN_MSG_APP_TOTAL];             /* 发送报文控制信息             */
    AppMsgRcvCtrlStruct     RcvCtrl[CAN_RCV_MSG_APP_TOTAL];             /* 接收报文控制信息             */
} AppInfoStruct;

typedef void (*CanApp_RcvTimeOutFun) (void);

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/
extern  const INT16U    CAN_APP_SEN_CYCLE_TBL[CAN_SEN_MSG_APP_TOTAL];           /* 正常发送周期                 */
extern  const INT16U    CAN_APP_SEN_EVENT_TBL[CAN_SEN_MSG_APP_TOTAL];           /* 快速发送周期                 */
extern  const INT16U    CAN_APP_RCV_CYCLE_TBL[CAN_RCV_MSG_APP_TOTAL];           /* 正常接收周期                 */
extern  const INT16U    CAN_APP_RCV_TIMEOUT_SUBS_TBL[CAN_RCV_MSG_APP_TOTAL];    /* 设置替代值超时周期           */
extern  const INT16U    CAN_APP_RCV_TIMEOUT_LOST_TBL[CAN_RCV_MSG_APP_TOTAL];    /* 设置丢失超时周期             */
extern  const CanApp_RcvTimeOutFun   CanApp_RcvTimeOutTbl[CAN_RCV_MSG_APP_TOTAL];   /* 超时回调                     */

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
extern  volatile CanMsgStruct               CanRcvMsgApp;               /* 接收报文帧-应用              */
extern  volatile CanMsgStruct               CanSenMsgApp;               /* 发送报文帧-应用              */
extern  volatile CanRcvMsgBCM318Struct      CanRcvMsgBCM318;            /* DKLai20230421 */
extern  volatile CanRcvMsgVCU3F2Struct      CanRcvMsgVCU3F2;            /* DKLai20230907 */
extern  volatile CanRcvMsgACU35AStruct      CanRcvMsgACU35A;
extern  volatile CanRcvMsgICM31EStruct      CanRcvMsgICM31E;
extern  volatile CanRcvMsgCDC093Struct      CanRcvMsgCDC093;
extern  volatile CanRcvMsgTEL097Struct      CanRcvMsgTEL097;
extern  volatile CanSenMsgVIB383Struct      CanSenMsgVIB383;

#if DEBUG_PROJECT_CAN_DEBUG_MSG

    #define CAN_MSG_ID_DEBUG                0x3FF
    #define CAN_MSG_LEN_DEBUG               8
		
extern  volatile CanMsgStruct               CanRcvMsgDebug;

#endif

extern  volatile AppInfoStruct      AppInfo;                            /* 控制信息                     */

/*********************************************************************************************************
** 接收信号读取宏定义 DKLai20230504
*********************************************************************************************************/
#define APP_GET_VEH_KEY_STATE()                 (CanRcvMsgBCM318.ucDat.Bits.BCM_KeySt)
#define APP_VEH_KEY_STATE_OFF()                 (CanRcvMsgBCM318.ucDat.Bits.BCM_KeySt  == 0)
#define APP_VEH_KEY_STATE_ACC()                 (CanRcvMsgBCM318.ucDat.Bits.BCM_KeySt  == 1)
#define APP_VEH_KEY_STATE_ON()                  (CanRcvMsgBCM318.ucDat.Bits.BCM_KeySt  == 2)
#define APP_VEH_KEY_STATE_CRANK()               (CanRcvMsgBCM318.ucDat.Bits.BCM_KeySt  == 3)

#define APP_GET_TIME_YEAR()                     (CanRcvMsgACU35A.ucDat.Bits.timeInfoYear)
#define APP_GET_TIME_MONTH()                    (CanRcvMsgACU35A.ucDat.Bits.timeInfoMonth)
#define APP_GET_TIME_DAY()                      (((INT8U)(CanRcvMsgACU35A.ucDat.Bits.timeInfoDayH << 1)) + ((INT8U)(CanRcvMsgACU35A.ucDat.Bits.timeInfoDayL)))
#define APP_GET_TIME_HOUR()                     (CanRcvMsgACU35A.ucDat.Bits.timeInfoHour)
#define APP_GET_TIME_MINUTE()                   (((INT8U)(CanRcvMsgACU35A.ucDat.Bits.timeInfoMinuteH << 4)) + ((INT8U)(CanRcvMsgACU35A.ucDat.Bits.timeInfoMinuteL)))
#define APP_GET_TIME_SECOND()                   (((INT8U)(CanRcvMsgACU35A.ucDat.Bits.timeInfoSecondH << 2)) + ((INT8U)(CanRcvMsgACU35A.ucDat.Bits.timeInfoSecondL)))

#define APP_TIME_MONTH_DATA_VALID()             ((APP_GET_TIME_MONTH() <= 12) && (APP_GET_TIME_MONTH()))
#define APP_TIME_DAY_DATA_VALID()               ((APP_GET_TIME_DAY()   <= 31) && (APP_GET_TIME_DAY()))
#define APP_TIME_HOUR_DATA_VALID()              (APP_GET_TIME_HOUR()   <= 23)
#define APP_TIME_MINUTE_DATA_VALID()            (APP_GET_TIME_MINUTE() <= 59)
#define APP_TIME_SECOND_DATA_VALID()            (APP_GET_TIME_SECOND() <= 59)

#define APP_GET_VEH_MILEAGE()                   (((INT32U)CanRcvMsgICM31E.ucDat.Bits.OdoH << 16) + ((INT32U)CanRcvMsgICM31E.ucDat.Bits.OdoM << 8) + ((INT32U)CanRcvMsgICM31E.ucDat.Bits.OdoL << 0))
#define APP_GET_VEH_MILEAGE_H()                 (CanRcvMsgICM31E.ucDat.Bits.OdoH)
#define APP_GET_VEH_MILEAGE_M()                 (CanRcvMsgICM31E.ucDat.Bits.OdoM)
#define APP_GET_VEH_MILEAGE_L()                 (CanRcvMsgICM31E.ucDat.Bits.OdoL)

#define APP_VEH_MILEAGE_DATA_VALID()            ( APP_GET_VEH_MILEAGE() <= 0x98967F )  /* 999999.9 km.  */

#define APP_GET_VCU_VIB_POWER_STATE()           (CanRcvMsgVCU3F2.ucDat.Bits.vibpwroff)      /* DKLai20230907 */
#define APP_GET_VCU_VIB_POWER_OFF()             (CanRcvMsgVCU3F2.ucDat.Bits.vibpwroff == 1) /* DKLai20230907 */

/*********************************************************************************************************
** 发送信号设置宏定义 DKLai20230419
*********************************************************************************************************/


/*********************************************************************************************************
** 
*********************************************************************************************************/
/*** AppInfo ***/
#define AppInfo_Flag_RmtStartReqStart   AppInfo.Flag.Ctrl.Bits.RmtStartReqStart
#define AppInfo_Flag_RmtStartReqStop    AppInfo.Flag.Ctrl.Bits.RmtStartReqStop
#define AppInfo_Flag_VinInqueryReq      AppInfo.Flag.Ctrl.Bits.VinInqueryReq

/*********************************************************************************************************
** 函数声明
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    CanApp_Init(void);
extern  STAT_MSG_RESULT_ENUM    CanApp_DealRcvMsg(volatile CanMsgStruct *pMsg);
extern  BOOLEAN                 CanApp_ReqSenMsg(INT8U ucMsgNum);
extern  void                    CanApp_TxCycleEnable(INT8U ucMsgNum, BOOLEAN blEnable);
extern  void                    CanApp_TxCycleReload(INT8U ucMsgNum);
extern  void                    CanApp_TxFastOnStart(INT8U ucMsgNum);
extern  void                    CanApp_TxEventCntSet(INT8U ucMsgNum, INT8U ucCnt);
extern  void                    CanApp_RxTimeOutEnable(INT8U ucMsgNum, BOOLEAN blEnable);
extern  void                    CanApp_RxTimeOutReload(INT8U ucMsgNum);
extern  void                    CanApp_RxTimeOutFlagClr(INT8U ucMsgNum, APP_TIMEOUT_ENUM euTimeOut);
extern  void                    CanApp_RxErrorFlagClr(INT8U ucMsgNum, APP_ERROR_ENUM euError);
extern  void                    CanApp_RxContinCntInc(INT8U ucMsgNum);

extern  void                    CanApp_RxTimeOutFlagClrForLostCGW(void);

extern  void                    CanApp_TxTimeTask(void);
extern  void                    CanApp_TxStatTask(void);
extern  void                    CanApp_TxStartVIB383(STAT_MSG_RESULT_ENUM euDealRslt);
extern  void                    CanApp_TxConfirmVIB383(void);

extern  void                    CanApp_RxTimeTask(void);
extern  void                    CanApp_RxStatTask(void);
/******************************************* Private Function *******************************************/


#if DEBUG_PROJECT_CAN_DEBUG_MSG
static  STAT_MSG_RESULT_ENUM    CanApp_DealRcvMsgDebug(volatile CanMsgStruct *pMsg);
#endif



/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __CANAPP_H                  */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
