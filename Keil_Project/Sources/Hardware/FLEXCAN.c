/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           FLEXCAN.c
** Last modified Date:  2019-07-08
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          tangjian
** Created date:        2017-12-26
** Version:             V1.00
** Descriptions:        CAN0 的 MB0~MB2用于发送，MB3~MB31用于接收。不使用 CAN-FD 功能，数据域设置为8bytes，使用标准帧方式
**                      MB1 用于应用APP报文发送，MB0 用于网络管理报文发送，MB2 用于诊断报文发送。不使能 FIFO 和 DMA。
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         zhaohai
** Modified date:       2019-07-08
** Version:             
** Descriptions:        
**
** Rechecked by:        
*********************************************************************************************************/
#include "includeall.h"

/*********************************************************************************************************
** 全局定量 DKLai20230505 
*********************************************************************************************************/
#if 1   /* 40MHz晶振 */
const   flexcan_time_segment_t  FLEXCAN0_TIME_TAB = {                   /* CAN0时间参数表，500K，81%    */
    .propSeg        = 7,
    .phaseSeg1      = 6,
    .phaseSeg2      = 3,
    .preDivider     = 1,
    .rJumpwidth     = 1
};
#else   /* 16MHz晶振 */
const   flexcan_time_segment_t  FLEXCAN0_TIME_TAB = {                   /* CAN0时间参数表，500K，81%    */
    .propSeg        = 7,
    .phaseSeg1      = 3,
    .phaseSeg2      = 2,
    .preDivider     = 0,
    .rJumpwidth     = 1
};
#endif
const INT32U    CAN0_MB_MASK_TAB[CAN0_MB_NUM_MAX] = {                   /* CAN0滤波器                   */
    CAN0_MB0_MASK,  CAN0_MB1_MASK,  CAN0_MB2_MASK,  CAN0_MB3_MASK,
    CAN0_MB4_MASK,  CAN0_MB5_MASK,  CAN0_MB6_MASK,  CAN0_MB7_MASK,
    CAN0_MB8_MASK,  CAN0_MB9_MASK,  CAN0_MB10_MASK, CAN0_MB11_MASK,
    CAN0_MB12_MASK, CAN0_MB13_MASK, CAN0_MB14_MASK, CAN0_MB15_MASK,
    CAN0_MB16_MASK, CAN0_MB17_MASK, CAN0_MB18_MASK, CAN0_MB19_MASK,
    CAN0_MB20_MASK, CAN0_MB21_MASK, CAN0_MB22_MASK, CAN0_MB23_MASK,
    CAN0_MB24_MASK, CAN0_MB25_MASK, CAN0_MB26_MASK, CAN0_MB27_MASK,
    CAN0_MB28_MASK, CAN0_MB29_MASK, CAN0_MB30_MASK, CAN0_MB31_MASK
};
const INT16U    CAN0_MB_CODE_TAB[CAN0_MB_NUM_MAX] = {                   /* CAN0 ID                      */
    CAN0_MB0_CODE,  CAN0_MB1_CODE,  CAN0_MB2_CODE,  CAN0_MB3_CODE,
    CAN0_MB4_CODE,  CAN0_MB5_CODE,  CAN0_MB6_CODE,  CAN0_MB7_CODE,
    CAN0_MB8_CODE,  CAN0_MB9_CODE,  CAN0_MB10_CODE, CAN0_MB11_CODE,
    CAN0_MB12_CODE, CAN0_MB13_CODE, CAN0_MB14_CODE, CAN0_MB15_CODE,
    CAN0_MB16_CODE, CAN0_MB17_CODE, CAN0_MB18_CODE, CAN0_MB19_CODE,
    CAN0_MB20_CODE, CAN0_MB21_CODE, CAN0_MB22_CODE, CAN0_MB23_CODE,
    CAN0_MB24_CODE, CAN0_MB25_CODE, CAN0_MB26_CODE, CAN0_MB27_CODE,
    CAN0_MB28_CODE, CAN0_MB29_CODE, CAN0_MB30_CODE, CAN0_MB31_CODE
};

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
volatile CanMbStruct        MbInfo;                                     /* 单个邮箱控制信息             */

/*********************************************************************************************************
** Function name:       CAN_UpdateMbInfo
** Descriptions:        重新设置MbInfo地址
** input parameters:    pCanNum：    CAN模块，范围：CAN0，CAN1
**                      ucMbNum：    邮箱编号，范围：0~CAN0_MB_NUM_MAX/CAN1_MB_NUM_MAX
** output parameters:   pMbInfo：    邮箱控制信息指针
** Returned value:      无
*********************************************************************************************************/
static  void    FLEXCAN_UpdateMbInfo(CAN_Type *pCanNum, INT8U ucMbNum, volatile CanMbStruct *pMbInfo)
{
    INT8U   ucMbLen;
    INT8U   ucIndex;    /* RAMn范围：128*INT32U */
    
    if (pCanNum == CAN0) {
        if (ucMbNum > CAN0_MB_NUM_MAX) {
            return;
        }
    } else {
        return;
    }
    
    ucMbLen             = (sizeof(CanMbCsUnion) + sizeof(CanMbIdUnion) + sizeof(CanMbRegion0Union) + sizeof(CanMbRegion1Union)) / sizeof(INT32U);
    ucIndex             = ucMbNum * ucMbLen;
    
    pMbInfo->pCs        = (CanMbCsUnion *)&(pCanNum->RAMn[ucIndex]);
    pMbInfo->pId        = (CanMbIdUnion *)&(pCanNum->RAMn[ucIndex + 1]);
    pMbInfo->pRegion0   = (CanMbRegion0Union *)&(pCanNum->RAMn[ucIndex + 2]);
    pMbInfo->pRegion1   = (CanMbRegion1Union *)&(pCanNum->RAMn[ucIndex + 3]);
}
/*********************************************************************************************************
** Function name:       CAN_MbCfgForTx
** Descriptions:        配置邮箱状态为Tx
** input parameters:    pCanNum：    CAN模块，范围：CAN0，CAN1
**                      ulMbCfgTx：  邮箱配置状态，一个Bit代表一个邮箱
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static  void    FLEXCAN_MbCfgForTx(CAN_Type *pCanNum, INT32U ulMbCfgTx)
{
    INT8U   i, ucMbNum;
    
    if (pCanNum == CAN0) {
        ucMbNum                     = CAN0_MB_NUM_MAX;
    } else {
        return;
    }
    
    for (i = 0; i < ucMbNum; i++) {
        if (ulMbCfgTx & (INT32U)(1 << i)) {
            /*
             * 设置邮箱
             */
            FLEXCAN_UpdateMbInfo(pCanNum, i, &MbInfo);
            MbInfo.pCs->DWord       = 0x00000000;
            MbInfo.pId->DWord       = 0x00000000;
            MbInfo.pRegion0->DWord  = 0x00000000;
            MbInfo.pRegion1->DWord  = 0x00000000;
            MbInfo.pCs->Bits.CODE   = CAN_MB_TX_CODE_INACTIVE;
            MbInfo.pCs->Bits.DLC    = 8;
        }
    }
}
/*********************************************************************************************************
** Function name:       CAN_MbCfgForRx
** Descriptions:        配置邮箱状态为Rx
** input parameters:    pCanNum：    CAN模块，范围：CAN0，CAN1
**                      ulMbCfgTx：  邮箱配置状态，一个Bit代表一个邮箱
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static  void    FLEXCAN_MbCfgForRx(CAN_Type *pCanNum, INT32U ulMbCfgRx)
{
    const   INT16U  *pCode;
    const   INT32U  *pMask;
    INT8U   i, ucMbNum;
    
    if (pCanNum == CAN0) {
        ucMbNum                     = CAN0_MB_NUM_MAX;
        pCode                       = CAN0_MB_CODE_TAB;
        pMask                       = CAN0_MB_MASK_TAB;
    } else {
        return;
    }
    
    for (i = 0; i < ucMbNum; i++) {
        if (ulMbCfgRx & (INT32U)(1 << i)) {
            /*
             * 设置滤波器
             */
            FLEXCAN_EnterFreezeMode(pCanNum);
            pCanNum->RXIMR[i]       = (pMask[i] << CAN_ID_STD_SHIFT) & CAN_ID_STD_MASK;
            FLEXCAN_ExitFreezeMode(pCanNum);
            /*
             * 设置邮箱
             */
            FLEXCAN_UpdateMbInfo(pCanNum, i, &MbInfo);
            MbInfo.pCs->DWord       = 0x00000000;
            MbInfo.pCs->Bits.CODE   = CAN_MB_RX_CODE_INACTIVE;
            MbInfo.pId->Bits.ID_STD = pCode[i];
            MbInfo.pCs->Bits.CODE   = CAN_MB_RX_CODE_EMPTY;
            /*
             * 使能接收中断
             */
            pCanNum->IFLAG1         = (INT32U)(1 << i);                 /* 写1清除,写0无影响           */
            pCanNum->IMASK1        |= (INT32U)(1 << i);
        }
    }
}
/*********************************************************************************************************
** Function name:       CAN_MbLock
** Descriptions:        锁定邮箱，通过读取邮箱的c/s域来锁定
** input parameters:    pCanNum：    CAN模块，范围：CAN0，CAN1
**                      ucMbNum：    邮箱编号，范围：0~CAN0_MB_NUM_MAX/CAN1_MB_NUM_MAX
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static  void    FLEXCAN_MbLock(CAN_Type *pCanNum, INT8U ucMbNum)
{
    INT8U   ucMbLen;
    INT8U   ucIndex;
    INT32U  ulTmp;
    
    ucMbLen         = (sizeof(CanMbCsUnion) + sizeof(CanMbIdUnion) + sizeof(CanMbRegion0Union) + sizeof(CanMbRegion1Union)) / sizeof(INT32U);
    ucIndex         = ucMbNum * ucMbLen;
    
    ulTmp           = pCanNum->RAMn[ucIndex];
    (void)ulTmp;
}
/*********************************************************************************************************
** Function name:       CAN_MbUnLock
** Descriptions:        解锁邮箱，通过读取时间戳定时器来解锁
** input parameters:    pCanNum：    CAN模块，范围：CAN0，CAN1
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static  void    FLEXCAN_MbUnLock(CAN_Type *pCanNum)
{
    (void)pCanNum->TIMER;
}
/*********************************************************************************************************
** Function name:       FLEXCAN0_InitReg/FLEXCAN1_InitReg
** Descriptions:        CAN初始化，中断方式接收，不支持DMA，为了兼容CAN1/2，设置16个邮箱
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    FLEXCAN0_InitReg(void)
{
    if(FLEXCAN_IsEnabled(CAN0)) {
        /* To enter Disable Mode requires FreezMode first */
        FLEXCAN_EnterFreezeMode(CAN0);
        FLEXCAN_Disable(CAN0);
    }
    FLEXCAN_SelectClock(CAN0, FLEXCAN_CLK_SOURCE_OSC);                  /* 选择OSC作为FlexCan时钟       */
    INT_SYS_DisableIRQ(CAN0_ORed_Err_Wakeup_IRQn);
    INT_SYS_DisableIRQ(CAN0_ORed_0_31_MB_IRQn);
    
    FLEXCAN_Enable(CAN0);                                               /* 使能模块时钟                 */
    
    FLEXCAN_Init(CAN0);                                                 /* 初始化模块                   */
    FLEXCAN_SetFDEnabled(CAN0, FALSE);                                  /* 禁止CAN FD功能               */
    FLEXCAN_SetSelfReception(CAN0, FALSE);                              /* 禁止回环模式                 */
    FLEXCAN_SetPayloadSize(CAN0, FLEXCAN_PAYLOAD_SIZE_8);               /* 8byte 数据域长度             */
    FLEXCAN_SetMaxMsgBuffNum(CAN0, CAN0_MB_NUM_MAX);                    /* 设置32个MBs                  */
    FLEXCAN_SetTimeSegments(CAN0, &FLEXCAN0_TIME_TAB);                  /* 设置时间相关参数             */
    
    FLEXCAN_SetOperationMode(CAN0, FLEXCAN_NORMAL_MODE);                /* 设置正常操作模式             */
    
    FLEXCAN_SetRxMaskType(CAN0, FLEXCAN_RX_MASK_INDIVIDUAL);            /* 设置邮箱独立滤波             */
    
    CAN0->IFLAG1    = 0xFFFFFFFF;                                       /* 清中断标志                   */
    FLEXCAN_MbCfgForTx(CAN0, CAN0_MB_CFG_TX_TAB);
    FLEXCAN_MbCfgForRx(CAN0, CAN0_MB_CFG_RX_TAB);
    
    TIME_WAIT_START(3000);
    while((CAN0->ESR1 & CAN_ESR1_SYNCH_MASK) == 0){TIME_WAIT_LOOP()};   /* 等待CAN模块同步,48M:正常时18us,繁忙时140us,异常时无限卡死 */
    
    FLEXCAN_SetErrIntCmd(CAN0, FLEXCAN_INT_ERR, TRUE);                  /* 开启错误中断                 */
    FLEXCAN_SetErrIntCmd(CAN0, FLEXCAN_INT_BUSOFF, TRUE);               /* 开启BusOff中断               */
    CAN0_BUS_OFF_DISABLE();                                             /* 禁止BusOff中断恢复           */
    
    INT_SYS_EnableIRQ(CAN0_ORed_Err_Wakeup_IRQn);
    INT_SYS_EnableIRQ(CAN0_ORed_0_31_MB_IRQn);
}
/*********************************************************************************************************
** Function name:       FLEXCAN0_DeInitReg/FLEXCAN1_DeInitReg
** Descriptions:        CAN反初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    FLEXCAN0_DeInitReg(void)
{
    FLEXCAN_SetErrIntCmd(CAN0, FLEXCAN_INT_ERR, FALSE);                 /* 关闭错误中断                 */
    FLEXCAN_SetErrIntCmd(CAN0, FLEXCAN_INT_BUSOFF, FALSE);              /* 关闭BusOff中断               */
    INT_SYS_DisableIRQ(CAN0_ORed_Err_Wakeup_IRQn);
    INT_SYS_DisableIRQ(CAN0_ORed_0_31_MB_IRQn);
    if(FLEXCAN_IsEnabled(CAN0)) {
        /* To enter Disable Mode requires FreezMode first */
        FLEXCAN_EnterFreezeMode(CAN0);
        FLEXCAN_Disable(CAN0);
    }
}
/*********************************************************************************************************
** Function name:       FLEXCAN_TxData
** Descriptions:        CAN发送数据
** input parameters:    pCanNum：    CAN模块，范围：CAN0，CAN1
**                      ucMbNum：    邮箱编号，范围：0~CAN0_MB_NUM_MAX/CAN1_MB_NUM_MAX
**                      usID：       标准帧ID
**                      pData：      待发送数据地址
**                      uclen：      待发送数据长度
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
BOOLEAN FLEXCAN_TxData(CAN_Type *pCanNum, INT8U ucMbNum, INT16U usID, INT8U *pData, INT8U uclen)
{
    if ((pCanNum == CAN0) && (ucMbNum > CAN0_MB_NUM_MAX)) {
        return FALSE;
    }
    if (uclen > 8) {
        return FALSE;
    }
    DisableIRQ();                                                       /* 禁止中断                     */
    
    pCanNum->IFLAG1                 = (INT32U)(1 << ucMbNum);           /* 写1清除,写0无影响            */
    
    FLEXCAN_UpdateMbInfo(pCanNum, ucMbNum, &MbInfo);
    MbInfo.pCs->Bits.CODE           = CAN_MB_TX_CODE_INACTIVE;          /* 禁能MB                       */
    MbInfo.pId->Bits.ID_STD         = usID;
    MbInfo.pCs->Bits.DLC            = uclen;
    MbInfo.pRegion0->Bits.Data0     = pData[0];
    MbInfo.pRegion0->Bits.Data1     = pData[1];
    MbInfo.pRegion0->Bits.Data2     = pData[2];
    MbInfo.pRegion0->Bits.Data3     = pData[3];
    MbInfo.pRegion1->Bits.Data4     = pData[4];
    MbInfo.pRegion1->Bits.Data5     = pData[5];
    MbInfo.pRegion1->Bits.Data6     = pData[6];
    MbInfo.pRegion1->Bits.Data7     = pData[7];
    MbInfo.pCs->Bits.IDE            = 0;                                /* 标准数据帧                   */
    MbInfo.pCs->Bits.RTR            = 0;
    MbInfo.pCs->Bits.CODE           = CAN_MB_TX_CODE_DATA;              /* 激活MB启动发送               */
    
    EnableIRQ();                                                        /* 恢复中断                     */
    
    return TRUE;
}
/*********************************************************************************************************
** Function name:       FLEXCAN_GetTxSt
** Descriptions:        获取邮箱发送状态，发送成功后IFLAG相应的MB置1，因未使能发送中断，需通过查询方式获取
** input parameters:    pCanNum：    CAN模块，范围：CAN0，CAN1
**                      ucMbNum：    邮箱编号，范围：0~CAN0_MB_NUM_MAX/CAN1_MB_NUM_MAX
** output parameters:   无
** Returned value:      TRUE:        成功
*********************************************************************************************************/
BOOLEAN FLEXCAN_GetTxSt(CAN_Type *pCanNum, INT8U ucMbNum)
{
    if (pCanNum->IFLAG1 & (INT32U)(1 << ucMbNum)) {
        pCanNum->IFLAG1 = (INT32U)(1 << ucMbNum);                       /* 写1清除,写0无影响            */
        return TRUE;
    } else {
        return FALSE;
    }
}
/*********************************************************************************************************
** Function name:       FLEXCAN0中断
** Descriptions:        
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    CAN0_ORed_Err_Wakeup_IRQHandler(void)                           /* BusOff中断,总线错误中断,唤醒中断 */
{
    if (CAN0->ESR1 & (1 << 2)) {
        CAN0->ESR1      = (INT32U)(1 << 2);
        
        #if DEBUG_PROJECT_MASK_NM
        CanNm2_BusOffEntry();
        #else
        CanNm_EntryBusOff();
        #endif
    }
    
    if (CAN0->ESR1 & (1 << 1)) {
        CAN0->ESR1      = (INT32U)(1 << 1);
    }
    
    if (CAN0->WU_MTC & 0x00030000) {
        CAN0->WU_MTC            = 0x00030000;
    }
    
}
void    CAN0_ORed_0_31_MB_IRQHandler(void)                              /* 接收中断 MB5~MB31            */
{
    INT8U   i;
    volatile    CanMbStruct stMbInfo;                                   /* 不使用全局MbInfo，避免出问题 */
    
    for (i = 5; i < 32; i++) {
        if (CAN0->IFLAG1 & (INT32U)(1 << i)) {
            FLEXCAN_MbLock(CAN0, i);                                    /* 锁定相应邮箱                 */
            FLEXCAN_UpdateMbInfo(CAN0, i, &stMbInfo);
            if (stMbInfo.pCs->Bits.CODE == CAN_MB_RX_CODE_FULL) {
                CAN_RcvMsg(&stMbInfo);/*8M-26us,48M-4.6us*/
            }
            stMbInfo.pCs->Bits.CODE = CAN_MB_RX_CODE_EMPTY;             /* 清空邮箱                     */
            CAN0->IFLAG1            = (INT32U)(1 << i);                 /* 写1清除,写0无影响            */
        }
        FLEXCAN_MbUnLock(CAN0);                                         /* 解锁邮箱                     */
    }
}
/*********************************************************************************************************
** Function name:       FLEXCAN0_InitPretendNetFun
** Descriptions:        初始化整个 Pretended Networking 网络唤醒功能。并开启。(CANFD 无唤醒功能)
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    FLEXCAN0_InitPretendNetFun(void)
{
    FLEXCAN_EnterFreezeMode(CAN0);
    
    FLEXCAN_SetPN(CAN0, TRUE);                                          /* 使能模块功能                 */
    CAN0->WU_MTC        = 0x00030000;                                   /* 清中断标志位                 */
    CAN0->CTRL1_PN      = 0x0001010C;                                   /* 使能匹配中断，只设置id滤波，使用范围范围，设置接收一帧唤醒数据 */
    CAN0->CTRL2_PN      = 0x00000000;                                   /* 不使能定时唤醒中断           */
    CAN0->FLT_ID1       = (INT32U)0x100 << 18;                          /* 设置滤波id范围的低地址，标准帧，数据帧 */
    CAN0->FLT_DLC       = 0x00080008;                                   /* 帧长为 8                     */
    
    /* 使用id范围时，该寄存器作为范围的高地址，使用id匹配等于时该寄存器作为FLT_ID1的mask寄存器 */
    CAN0->FLT_ID2_IDMASK    = (INT32U)0x7FF << 18;                      /* 设置滤波id范围的高地址，标准帧，数据帧 */
    
    FLEXCAN_ExitFreezeMode(CAN0);
    
    /* 清唤醒帧接收数据 */
    DisableIRQ();
    CanRcvMsgWake.ulId  = 0x00;
    CanRcvMsgWake.ucDlc = 0x00;
    for (INT8U i = 0;i < 8;i++) {
        CanRcvMsgWake.ucDat[i]  = 0;
    }
    EnableIRQ();
}
/*********************************************************************************************************
** Function name:       FLEXCAN0_DisablePretendNetFun
** Descriptions:        唤醒后应调用该函数，禁止Pretended Networking功能，及相关中断
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    FLEXCAN0_DisablePretendNetFun(void)
{
    FLEXCAN_EnterFreezeMode(CAN0);      
    
    CAN0->CTRL1_PN      = 0x00000000;                                   /* 清中断使能位，禁止模块功能   */
    FLEXCAN_SetPN(CAN0, FALSE);
    
    FLEXCAN_ExitFreezeMode(CAN0);
}
/*********************************************************************************************************
** Function name:       唤醒中断
** Descriptions:        匹配帧中断
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    CAN0_Wake_Up_IRQHandler(void)
{
    CanRcvMsgWake.ucDlc     = (INT8U)(CAN0->WMB[0].WMBn_CS >> 16) & 0x0F;
    CanRcvMsgWake.ulId      = (INT16U)(CAN0->WMB[0].WMBn_ID >> 18) & 0x7FF;
    CanRcvMsgWake.ucDat[0]  = (INT8U)(CAN0->WMB[0].WMBn_D03 >> 24);
    CanRcvMsgWake.ucDat[1]  = (INT8U)(CAN0->WMB[0].WMBn_D03 >> 16);
    CanRcvMsgWake.ucDat[2]  = (INT8U)(CAN0->WMB[0].WMBn_D03 >> 8);
    CanRcvMsgWake.ucDat[3]  = (INT8U)(CAN0->WMB[0].WMBn_D03 >> 0);
    CanRcvMsgWake.ucDat[4]  = (INT8U)(CAN0->WMB[0].WMBn_D47 >> 24);
    CanRcvMsgWake.ucDat[5]  = (INT8U)(CAN0->WMB[0].WMBn_D47 >> 16);
    CanRcvMsgWake.ucDat[6]  = (INT8U)(CAN0->WMB[0].WMBn_D47 >> 8);
    CanRcvMsgWake.ucDat[7]  = (INT8U)(CAN0->WMB[0].WMBn_D47 >> 0);
    
    CAN0->WU_MTC            = 0x00030000;                               /* 清中断标志位                 */
}

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
