/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           FLEXCAN.h
** Last modified Date:  2019-07-08
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          tangjian
** Created date:        2017-12-26
** Version:             V1.00
** Descriptions:        CAN0 的 MB0~MB4用于发送，MB5~MB31用于接收。不使用 CAN-FD 功能，数据域设置为8bytes，使用标准帧方式
**                      不使能 FIFO 和 DMA。
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         zhaohai
** Modified date:       2019-07-08
** Version:
** Descriptions:
**
** Rechecked by:
*********************************************************************************************************/
#ifndef __FLEXCAN_H
#define __FLEXCAN_H

#include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
/* 禁止CAN模块，设置MCR等待进入低功耗,48M:while=1.8us */
#define CAN0_DISABLE_MODE()\
{\
    CAN0->MCR       |= CAN_MCR_MDIS_MASK;\
    TIME_WAIT_START(3000);\
    while ((CAN0->MCR & CAN_MCR_LPMACK_MASK) == 0){TIME_WAIT_LOOP()};\
}
/* BusOff自动恢复功能设置 */
#define CAN0_BUS_OFF_DISABLE()          CAN0->CTRL1     |= CAN_CTRL1_BOFFREC_MASK;
#define CAN0_BUS_OFF_ENABLE()           CAN0->CTRL1     &= (INT32U)(~CAN_CTRL1_BOFFREC_MASK)
#define CAN0_BUS_OFF_IND                (INT8U)(CAN0->CTRL1 & CAN_CTRL1_BOFFREC_MASK)

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
/*
 * 设置邮箱个数,CAN0通道设置
 */
#define CAN0_MB_NUM_MAX                 (INT8U)32
#define CAN0_MB_CFG_TX_TAB              (INT32U)0x0000001F              /* 发送邮箱配置 0b00000000000000000000000000011111 */
#define CAN0_MB_CFG_RX_TAB              (INT32U)0xFFFFFFE0              /* 接收邮箱配置 0b11111111111111111111111111100000 */
/*
 * 对于接收邮箱的设置，MASK: 1关心，0不关心，CODE: 11位标准帧
 */
#define CAN0_MB0_MASK                   (INT32U)0x7FF
#define CAN0_MB0_CODE                   (INT16U)0x000

#define CAN0_MB1_MASK                   (INT32U)0x7FF
#define CAN0_MB1_CODE                   (INT16U)0x000

#define CAN0_MB2_MASK                   (INT32U)0x7FF
#define CAN0_MB2_CODE                   (INT16U)0x000

#define CAN0_MB3_MASK                   (INT32U)0x7FF
#define CAN0_MB3_CODE                   (INT16U)0x000

#define CAN0_MB4_MASK                   (INT32U)0x7FF
#define CAN0_MB4_CODE                   (INT16U)0x000                   /* MB0~MB4  用于发送邮箱        */

#define CAN0_MB5_MASK                   (INT32U)0x7FF
#define CAN0_MB5_CODE                   (INT16U)PROJECT_DIAG_REQ_ID     /* 物理寻址                     */
                                        
#define CAN0_MB6_MASK                   (INT32U)0x7FF
#define CAN0_MB6_CODE                   (INT16U)0x7DF                   /* 功能寻址                     */
                                        
#define CAN0_MB7_MASK                   (INT32U)0x31E
#define CAN0_MB7_CODE                   (INT16U)0x31E                   /* icm        */
                                        
#define CAN0_MB8_MASK                   (INT32U)0x35A
#define CAN0_MB8_CODE                   (INT16U)0x35A                   /* acu                      *//*首选滤波器*/
                                        
#define CAN0_MB9_MASK                   (INT32U)0x318
#define CAN0_MB9_CODE                   (INT16U)0x318                   /* bcm                      */
                                        
#define CAN0_MB10_MASK                  (INT32U)0x093
#define CAN0_MB10_CODE                  (INT16U)0x093                   /* cdc                      */
                                        
#define CAN0_MB11_MASK                  (INT32U)0x097
#define CAN0_MB11_CODE                  (INT16U)0x097                   /* tel                      */
                                        
#define CAN0_MB12_MASK                  (INT32U)0x31E
#define CAN0_MB12_CODE                  (INT16U)0x31E                   /* icm                  */
                                        
#define CAN0_MB13_MASK                  (INT32U)0x35A
#define CAN0_MB13_CODE                  (INT16U)0x35A                   /* acu                      */
                                        
#define CAN0_MB14_MASK                  (INT32U)0x318
#define CAN0_MB14_CODE                  (INT16U)0x318                   /* bcm                      *//*备用滤波器*/
                                        
#define CAN0_MB15_MASK                  (INT32U)0x093
#define CAN0_MB15_CODE                  (INT16U)0x093                   /* cdc                      */
                                        
#define CAN0_MB16_MASK                  (INT32U)0x097
#define CAN0_MB16_CODE                  (INT16U)0x097                   /* tel                      */
                                        
#define CAN0_MB17_MASK                  (INT32U)0x7FF
#define CAN0_MB17_CODE                  (INT16U)PROJECT_DIAG_REQ_ID     /*                       */
                                        
#define CAN0_MB18_MASK                  (INT32U)0x7FF
#define CAN0_MB18_CODE                  (INT16U)0x7DF                   /*                  */
                                        
#define CAN0_MB19_MASK                  (INT32U)0x3F2
#define CAN0_MB19_CODE                  (INT16U)0x3F2                   /* VCU_HVAC_CDC. DKLai20230907 */
                                        
#define CAN0_MB20_MASK                  (INT32U)0x3F2
#define CAN0_MB20_CODE                  (INT16U)0x3F2                   /*                      *//*备用滤波器*/
                                        
#define CAN0_MB21_MASK                  (INT32U)0x7FF
#define CAN0_MB21_CODE                  (INT16U)0x000                   /*                       */
                                        
#define CAN0_MB22_MASK                  (INT32U)0x7FF
#define CAN0_MB22_CODE                  (INT16U)0x000                   /*                       */
                                        
#define CAN0_MB23_MASK                  (INT32U)0x7FF
#define CAN0_MB23_CODE                  (INT16U)0x000                   /*                       */
                                        
#define CAN0_MB24_MASK                  (INT32U)0x7FF
#define CAN0_MB24_CODE                  (INT16U)0x000                   /*                   */
                                        
#define CAN0_MB25_MASK                  (INT32U)0x7FF
#define CAN0_MB25_CODE                  (INT16U)0x000                   /*                       */
                                        
#define CAN0_MB26_MASK                  (INT32U)0x7FF
#define CAN0_MB26_CODE                  (INT16U)0x000                   /*                       *//*备用滤波器*/
                                        
#define CAN0_MB27_MASK                  (INT32U)0x7FF
#define CAN0_MB27_CODE                  (INT16U)0x000                   /*                       */
                                        
#define CAN0_MB28_MASK                  (INT32U)0x7FF
#define CAN0_MB28_CODE                  (INT16U)0x000                   /*                      */
                                        
#define CAN0_MB29_MASK                  (INT32U)0x7FF
#define CAN0_MB29_CODE                  (INT16U)0x000                   /*                       */

#define CAN0_MB30_MASK                  (INT32U)0x7FF
#define CAN0_MB30_CODE                  (INT16U)0x000                   /*                          *//*调试*/

#define CAN0_MB31_MASK                  (INT32U)0x7FF
#define CAN0_MB31_CODE                  (INT16U)0x000                   /*                           */

/*********************************************************************************************************
**  结构体: Message buffer structure，mailbox
*********************************************************************************************************/
/*
 * 枚举
 */
typedef enum {
    CAN_MB_TX_CODE_INACTIVE             = 0x8,                          /*                              */
    CAN_MB_TX_CODE_ABORT                = 0x9,                          /* 取消发送                     */
    CAN_MB_TX_CODE_DATA                 = 0xC,                          /* 发送数据                     */
    CAN_MB_TX_CODE_TANSWER              = 0xE,                          /*                              */
} CAN_MB_TX_CODE_ENUM;
typedef enum {
    CAN_MB_RX_CODE_INACTIVE             = 0x0,                          /* 不使用                       */
    CAN_MB_RX_CODE_BUSY                 = 0x1,                          /* 忙                           */
    CAN_MB_RX_CODE_EMPTY                = 0x4,                          /* 空                           */
    CAN_MB_RX_CODE_FULL                 = 0x2,                          /* 满                           */
    CAN_MB_RX_CODE_OVERRUN              = 0x6,                          /* 溢出                         */
    CAN_MB_RX_CODE_RANSWER              = 0xA,                          /*                              */
} CAN_MB_RX_CODE_ENUM;
typedef union {
    INT32U  DWord;
    struct {
        INTCPU  TIME_STAMP                      :16;                    /*                              */
        INTCPU  DLC                             :4;                     /*                              */
        INTCPU  RTR                             :1;                     /*                              */
        INTCPU  IDE                             :1;                     /*                              */
        INTCPU  SRR                             :1;                     /*                              */
        INTCPU                                  :1;                     /*                              */
        INTCPU  CODE                            :4;                     /*                              */
        INTCPU                                  :1;                     /*                              */
        INTCPU  ESI                             :1;                     /*                              */
        INTCPU  BRS                             :1;                     /*                              */
        INTCPU  EDL                             :1;                     /*                              */
    } Bits;
} CanMbCsUnion;
typedef union {
    INT32U  DWord;
    struct {
        INTCPU  ID_EXT                          :18;                    /*                              */
        INTCPU  ID_STD                          :11;                    /*                              */
        INTCPU  PRIO                            :3;                     /*                              */
    } Bits;
} CanMbIdUnion;
typedef union {
    INT32U  DWord;
    struct {
        INTCPU  Data3                           :8;                     /*                              */
        INTCPU  Data2                           :8;                     /*                              */
        INTCPU  Data1                           :8;                     /*                              */
        INTCPU  Data0                           :8;                     /*                              */
    } Bits;
} CanMbRegion0Union;
typedef union {
    INT8U  DWord;
    struct {
        INTCPU  Data7                           :8;                     /*                              */
        INTCPU  Data6                           :8;                     /*                              */
        INTCPU  Data5                           :8;                     /*                              */
        INTCPU  Data4                           :8;                     /*                              */
    } Bits;
} CanMbRegion1Union;
typedef struct {
    CanMbCsUnion            *pCs;                                       /*                              */
    CanMbIdUnion            *pId;                                       /*                              */
    CanMbRegion0Union       *pRegion0;                                  /*                              */
    CanMbRegion1Union       *pRegion1;                                  /*                              */
} CanMbStruct;
/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
extern  volatile CanMbStruct        MbInfo;                             /* 单个邮箱控制信息             */

/*********************************************************************************************************
** 函数声明
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    FLEXCAN0_InitReg(void);
extern  void                    FLEXCAN0_DeInitReg(void);
extern  BOOLEAN                 FLEXCAN_TxData(CAN_Type *pCanNum, INT8U ucMbNum, INT16U usID, INT8U *pData, INT8U uclen);
extern  BOOLEAN                 FLEXCAN_GetTxSt(CAN_Type *pCanNum, INT8U ucMbNum);
extern  void                    CAN0_ORed_Err_Wakeup_IRQHandler(void);
extern  void                    CAN0_ORed_0_31_MB_IRQHandler(void);

/******************************************* Private Function *******************************************/
static  void                    FLEXCAN_UpdateMbInfo(CAN_Type *pCanNum, INT8U ucMbNum, volatile CanMbStruct *pMbInfo);
static  void                    FLEXCAN_MbCfgForTx(CAN_Type *pCanNum, INT32U ulMbCfgTx);
static  void                    FLEXCAN_MbCfgForRx(CAN_Type *pCanNum, INT32U ulMbCfgRx);
static  void                    FLEXCAN_MbLock(CAN_Type *pCanNum, INT8U ucMbNum);
static  void                    FLEXCAN_MbUnLock(CAN_Type *pCanNum);

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __FLEXCAN_H                 */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
