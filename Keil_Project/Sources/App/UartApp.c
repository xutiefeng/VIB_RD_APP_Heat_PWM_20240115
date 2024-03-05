/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           UartApp.c
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
#include "includeall.h"

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/
/*
 *  系统-状态
 */
const   INT8U   DSPCMD_SYS_RST[4]               = {0x4D, 0x0C, 0x02, 0x70};
const   INT8U   DSPCMD_SYS_CALE[4]              = {0x4D, 0x0D, 0x01, 0x60};
const   INT8U   DSPCMD_SYS_REC[4]               = {0x4D, 0x0D, 0x02, 0x7B};
const   INT8U   DSPCMD_SYS_PLAY[4]              = {0x4D, 0x0D, 0x03, 0x72};
/*
 *  基本-关闭/DVR
 */
const   INT8U   DSPCMD_VIEW_DIS[4]              = {0x4D, 0x0A, 0x00, 0x58};
const   INT8U   DSPCMD_VIEW_DVR[4]              = {0x4D, 0x0A, 0x01, 0x51};
/*
 *  环视-前/后/左/右
 */
const   INT8U   DSPCMD_VIEW_AROUND_FORWARD[4]   = {0x4D, 0x0A, 0x10, 0x41};
const   INT8U   DSPCMD_VIEW_AROUND_BACKOFF[4]   = {0x4D, 0x0A, 0x11, 0x48};
const   INT8U   DSPCMD_VIEW_AROUND_LEFT[4]      = {0x4D, 0x0A, 0x12, 0x53};
const   INT8U   DSPCMD_VIEW_AROUND_RIGHT[4]     = {0x4D, 0x0A, 0x13, 0x5A};
/*
 *  放大-前/后/左/右
 */
const   INT8U   DSPCMD_VIEW_EXPAND_FORWARD[4]   = {0x4D, 0x0A, 0x20, 0x6A};
const   INT8U   DSPCMD_VIEW_EXPAND_BACKOFF[4]   = {0x4D, 0x0A, 0x21, 0x63};
const   INT8U   DSPCMD_VIEW_EXPAND_LEFT[4]      = {0x4D, 0x0A, 0x22, 0x78};
const   INT8U   DSPCMD_VIEW_EXPAND_RIGHT[4]     = {0x4D, 0x0A, 0x23, 0x71};
/*
 *  鱼眼-前/后/左/右
 */
const   INT8U   DSPCMD_VIEW_FISHEYE_FORWARD[4]  = {0x4D, 0x0A, 0x30, 0x73};
const   INT8U   DSPCMD_VIEW_FISHEYE_BACKOFF[4]  = {0x4D, 0x0A, 0x31, 0x7A};
const   INT8U   DSPCMD_VIEW_FISHEYE_LEFT[4]     = {0x4D, 0x0A, 0x32, 0x61};
const   INT8U   DSPCMD_VIEW_FISHEYE_RIGHT[4]    = {0x4D, 0x0A, 0x33, 0x68};
/*
 *  环视-左全/右全
 */
const   INT8U   DSPCMD_VIEW_AROUND_LALL[4]      = {0x4D, 0x0A, 0x42, 0x2E};
const   INT8U   DSPCMD_VIEW_AROUND_RALL[4]      = {0x4D, 0x0A, 0x43, 0x27};
/*
 *  查询-核心板状态/应用层版本/算法库版本/用户自定版本
 */
const   INT8U   DSPCMD_POLL_DSP_STAT[4]         = {0x4D, 0x80, 0x00, 0x45};
const   INT8U   DSPCMD_POLL_APP_VERSION[4]      = {0x4D, 0x81, 0x00, 0x4E};
const   INT8U   DSPCMD_POLL_CALE_VERSION[4]     = {0x4D, 0x81, 0x01, 0x47};
const   INT8U   DSPCMD_POLL_USER_VERSION[4]     = {0x4D, 0x81, 0x02, 0x5C};
/*
 *  升级-程序/UI/参数
 */
const   INT8U   DSPCMD_UPDATE_APP_FROM_USB[4]   = {0x4D, 0x07, 0x01, 0x2E};
const   INT8U   DSPCMD_UPDATE_CALE_FROM_USB[4]  = {0x4D, 0x07, 0x05, 0x0A};
const   INT8U   DSPCMD_UPDATE_REC_FROM_USB[4]   = {0x4D, 0x07, 0x09, 0x66};
const   INT8U   DSPCMD_UPDATE_PLAY_FROM_USB[4]  = {0x4D, 0x07, 0x0D, 0x42};

const   INT8U   DSPCMD_UPDATE_BV_SV_FROM_USB[4] = {0x4D, 0x08, 0x01, 0x47};
const   INT8U   DSPCMD_UPDATE_BV_FROM_USB[4]    = {0x4D, 0x08, 0x05, 0x63};
const   INT8U   DSPCMD_UPDATE_SV_FROM_USB[4]    = {0x4D, 0x08, 0x09, 0x0F};
const   INT8U   DSPCMD_UPDATE_OSD_FROM_USB[4]   = {0x4D, 0x08, 0x0D, 0x2B};
const   INT8U   DSPCMD_UPDATE_OSD2_FROM_USB[4]  = {0x4D, 0x08, 0x11, 0x5E};

const   INT8U   DSPCMD_UPDATE_PARAM_FROM_USB[4] = {0x4D, 0x09, 0x01, 0x4C};
const   INT8U   DSPCMD_UPDATE_PACK_FROM_USB[4]  = {0x4D, 0x09, 0x05, 0x68};
/*
 *  标定-查询
 */
const   INT8U   DSPCMD_CALE_POLL[4]             = {0x4D, 0x65, 0x00, 0x2E};
/*
 *  录像-播放
 */
const   INT8U   DSPCMD_REC_PLAY[4]              = {0x4D, 0x6A, 0x00, 0x47};

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
/*
 * OSD信息设置
 */
volatile INT8U  DSPCMD_OSD[11]                  = {0x4D, 0xCA, 0x90, 0xA1, 0xA2, 0xA3, 0x00, 0x00, 0x00, 0x00, 0x00};
#if 0
/*********************************************************************************************************
** Function name:       UartApp_DealRcvMsg
** Descriptions:        应用报文帧处理
** input parameters:    无
** output parameters:   无
** Returned value:      处理结果
*********************************************************************************************************/
STAT_MSG_RESULT_ENUM    UartApp_DealRcvMsg(void)
{
    STAT_MSG_RESULT_ENUM    euDealRslt = STAT_MSG_NOT_ALLOWR;
    INT8U   ucMsgId;
    INT8U   ucCrc;
    
    if (!UartAppRcvMsg.blAllowR) {
        return STAT_MSG_NOT_ALLOWR;
    }
    if (!UartAppRcvMsg.blNew) {
        return STAT_MSG_NOT_NEW;
    }
    ucCrc   = Crc_Crc7(0x00, (INT8U *)UartAppRcvMsg.ucDat, UartAppRcvMsg.Len - 1);
    if (ucCrc != UartAppRcvMsg.ucDat[UartAppRcvMsg.Len - 1]) {
        return STAT_MSG_ERR_CRC;
    }
    /*****************************************************************************************************
    ** 处理报文帧开始
    *****************************************************************************************************/
    ucMsgId  = UartAppRcvMsg.ucDat[1];
    switch (ucMsgId) {
        case UART_SYS_RST_MSG_ID:           /* CMDM12   系统复位    */
            UartApp_DealRcvMsg_AckUsualDeal(UartAppRcvMsg.ucDat[2]);
            euDealRslt = STAT_MSG_DEALED;
            break;
        case UART_SYS_CALL_MSG_ID:          /* CMDM13   系统调用    */
            if (!UartApp_DealRcvMsg_AckUsualDeal(UartAppRcvMsg.ucDat[2])) {
                euDealRslt = STAT_MSG_DEALED;
                break;
            }
            /*------------------------------------------------------------------------------------------*/
            // /* 通信测试OK */
            // Flag.UartIsOK   = TRUE;
            // /* 标定正式开始 */
            // Stat.AvmCaleCur = STAT_AVM_CALE_ING;
            // Stat.System     = STAT_SYSTEM_CALE;
            /*------------------------------------------------------------------------------------------*/
            break;
        case UART_VIEW_MODE_MSG_ID:         /* CMDM10   显示模式    */
            UartApp_DealRcvMsg_AckUsualDeal(UartAppRcvMsg.ucDat[2]);
            euDealRslt = STAT_MSG_DEALED;
            /*------------------------------------------------------------------------------------------*/
            // /* 通信测试OK */
            // Flag.UartIsOK   = TRUE;
            /*------------------------------------------------------------------------------------------*/
            break;
        case UART_POLL_VERSION_MSG_ID:      /* CMDM129  查询版本    */
            if (!UartApp_DealRcvMsg_AckPollDeal(UartAppRcvMsg.ucDat[2], UartAppRcvMsg.ucDat[3])) {
                euDealRslt = STAT_MSG_DEALED;
                break;
            }
            /*------------------------------------------------------------------------------------------*/
            // /* 通信测试OK */
            // Flag.UartIsOK   = TRUE;
            /*------------------------------------------------------------------------------------------*/
            euDealRslt = STAT_MSG_DEALED;
            break;
        case UART_CALE_STAT_MSG_ID:         /* CMDM101  标定状态    */
            if (!UartApp_DealRcvMsg_AckUsualDeal(UartAppRcvMsg.ucDat[2])) {
                euDealRslt = STAT_MSG_DEALED;
                break;
            }
            // /* 通信测试OK */
            // Flag.UartIsOK   = TRUE;
            // /*------------------------------------------------------------------------------------------*/
            // if (UartAppRcvMsg.ucDat[2] == UART_CALE_STAT_MSG_ID_ING) {
                // Stat.AvmCaleCur = STAT_AVM_CALE_ING;
                // Stat.System     = STAT_SYSTEM_CALE;
            // } else if (UartAppRcvMsg.ucDat[2] == UART_CALE_STAT_MSG_ID_SUCC) {
                // /* 标定成功 */
                // Stat.AvmCaleCur = STAT_AVM_CALE_SUCC;
                // Stat.System     = STAT_SYSTEM_INIT;
                // UartApp_SenCmd(DSPCMD_SYS_RST);
                // Time_Reset(&Time.AvmInitCore);
            // } else if (UartAppRcvMsg.ucDat[2] == UART_CALE_STAT_MSG_ID_FAIL) {
                // /* 标定失败 */
                // Stat.AvmCaleCur = STAT_AVM_CALE_FAIL;
                // Stat.System     = STAT_SYSTEM_INIT;
                // UartApp_SenCmd(DSPCMD_SYS_RST);
                // Time_Reset(&Time.AvmInitCore);
            // }
            /*------------------------------------------------------------------------------------------*/
            euDealRslt = STAT_MSG_DEALED;
            break;
        default:
            break;
    }
    /*****************************************************************************************************
    ** 处理报文帧结束
    *****************************************************************************************************/
    UartAppRcvMsg.blNew = FALSE;
    
    return euDealRslt;
}
/*********************************************************************************************************
** Function name:       UartApp_DealRcvMsg_AckUsualDeal
** Descriptions:        
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
BOOLEAN UartApp_DealRcvMsg_AckUsualDeal(INT8U ucErr)
{
    #if 0
    if (Flag.UartSenBufAckWait) {
        switch (ucErr) {
            case UART_ERR_SUCC:         /* 成功             */
                UartAll_DealSenBuf_AckWaitSucc();               return TRUE;
                // break;
            case UART_ERR_OUT_ID:       /* 命令不支持       */
                UartAll_DealSenBuf_AckWaitFail_NextSen();       return FALSE;
                // break;
            case UART_ERR_CODE_CRC:     /* 命令CRC校验失败  */
                UartAll_DealSenBuf_AckWaitFail_ReSen();         return FALSE;
                // break;
            case UART_ERR_DATA_CRC:     /* 数据CRC校验失败  */
                UartAll_DealSenBuf_AckWaitFail_ReSen();         return FALSE;
                // break;
            case UART_ERR_CALE_SUCC:    /* 标定成功         */
                UartAll_DealSenBuf_AckWaitSucc();               return TRUE;
                // break;
            case UART_ERR_CALE_FAIL:    /* 标定失败         */
                UartAll_DealSenBuf_AckWaitSucc();               return TRUE;
                // break;
            default:                    /* 其它错误         */
                UartAll_DealSenBuf_AckWaitFail_NextSen();       return FALSE;
                // break;
        }
    }
    #endif
    return FALSE;
}
/*********************************************************************************************************
** Function name:       UartApp_DealRcvMsg_AckPollDeal
** Descriptions:        
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
BOOLEAN UartApp_DealRcvMsg_AckPollDeal(INT8U ucErr1, INT8U ucErr2)
{
    if (Flag.UartSenBufAckWait) {
        if (ucErr1 == 0xFF) {
            return UartApp_DealRcvMsg_AckUsualDeal(ucErr2);
        } else {
            return UartApp_DealRcvMsg_AckUsualDeal(UART_ERR_SUCC);
        }
    }
    return FALSE;
}
/*********************************************************************************************************
** Function name:       UartApp_SenCmd
** Descriptions:        
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    UartApp_SenCmd(const INT8U *pCmd)
{
    UartAppSenMsg.blNew     = TRUE;
    UartAppSenMsg.Len       = 4;
    UartAppSenMsg.ucDat[0]  = *(pCmd + 0);
    UartAppSenMsg.ucDat[1]  = *(pCmd + 1);
    UartAppSenMsg.ucDat[2]  = *(pCmd + 2);
    UartAppSenMsg.ucDat[3]  = Crc_Crc7(0x00, (INT8U *)UartAppSenMsg.ucDat, 3);
    // UartAppSenMsg.ucDat[3]  = *(pCmd + 3);
    (void)UartAll_SenMsg(&UartAppSenMsg);
}
/*********************************************************************************************************
** Function name:       UartApp_SenCmdN
** Descriptions:        
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    UartApp_SenCmdN(volatile INT8U *pCmd, INT8U ucLen)
{
    INT8U   i;
    
    UartAppSenMsg.blNew     = TRUE;
    UartAppSenMsg.Len       = ucLen;
    for (i = 0; i < (UartAppSenMsg.Len - 1); i++) {
        UartAppSenMsg.ucDat[i]  = *(pCmd + i);
    }
    UartAppSenMsg.ucDat[UartAppSenMsg.Len - 1]  = Crc_Crc7(0x00, (INT8U *)UartAppSenMsg.ucDat, UartAppSenMsg.Len - 1);
    (void)UartAll_SenMsg(&UartAppSenMsg);
}
#endif
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
