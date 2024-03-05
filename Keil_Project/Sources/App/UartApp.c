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
** ȫ�ֶ���
*********************************************************************************************************/
/*
 *  ϵͳ-״̬
 */
const   INT8U   DSPCMD_SYS_RST[4]               = {0x4D, 0x0C, 0x02, 0x70};
const   INT8U   DSPCMD_SYS_CALE[4]              = {0x4D, 0x0D, 0x01, 0x60};
const   INT8U   DSPCMD_SYS_REC[4]               = {0x4D, 0x0D, 0x02, 0x7B};
const   INT8U   DSPCMD_SYS_PLAY[4]              = {0x4D, 0x0D, 0x03, 0x72};
/*
 *  ����-�ر�/DVR
 */
const   INT8U   DSPCMD_VIEW_DIS[4]              = {0x4D, 0x0A, 0x00, 0x58};
const   INT8U   DSPCMD_VIEW_DVR[4]              = {0x4D, 0x0A, 0x01, 0x51};
/*
 *  ����-ǰ/��/��/��
 */
const   INT8U   DSPCMD_VIEW_AROUND_FORWARD[4]   = {0x4D, 0x0A, 0x10, 0x41};
const   INT8U   DSPCMD_VIEW_AROUND_BACKOFF[4]   = {0x4D, 0x0A, 0x11, 0x48};
const   INT8U   DSPCMD_VIEW_AROUND_LEFT[4]      = {0x4D, 0x0A, 0x12, 0x53};
const   INT8U   DSPCMD_VIEW_AROUND_RIGHT[4]     = {0x4D, 0x0A, 0x13, 0x5A};
/*
 *  �Ŵ�-ǰ/��/��/��
 */
const   INT8U   DSPCMD_VIEW_EXPAND_FORWARD[4]   = {0x4D, 0x0A, 0x20, 0x6A};
const   INT8U   DSPCMD_VIEW_EXPAND_BACKOFF[4]   = {0x4D, 0x0A, 0x21, 0x63};
const   INT8U   DSPCMD_VIEW_EXPAND_LEFT[4]      = {0x4D, 0x0A, 0x22, 0x78};
const   INT8U   DSPCMD_VIEW_EXPAND_RIGHT[4]     = {0x4D, 0x0A, 0x23, 0x71};
/*
 *  ����-ǰ/��/��/��
 */
const   INT8U   DSPCMD_VIEW_FISHEYE_FORWARD[4]  = {0x4D, 0x0A, 0x30, 0x73};
const   INT8U   DSPCMD_VIEW_FISHEYE_BACKOFF[4]  = {0x4D, 0x0A, 0x31, 0x7A};
const   INT8U   DSPCMD_VIEW_FISHEYE_LEFT[4]     = {0x4D, 0x0A, 0x32, 0x61};
const   INT8U   DSPCMD_VIEW_FISHEYE_RIGHT[4]    = {0x4D, 0x0A, 0x33, 0x68};
/*
 *  ����-��ȫ/��ȫ
 */
const   INT8U   DSPCMD_VIEW_AROUND_LALL[4]      = {0x4D, 0x0A, 0x42, 0x2E};
const   INT8U   DSPCMD_VIEW_AROUND_RALL[4]      = {0x4D, 0x0A, 0x43, 0x27};
/*
 *  ��ѯ-���İ�״̬/Ӧ�ò�汾/�㷨��汾/�û��Զ��汾
 */
const   INT8U   DSPCMD_POLL_DSP_STAT[4]         = {0x4D, 0x80, 0x00, 0x45};
const   INT8U   DSPCMD_POLL_APP_VERSION[4]      = {0x4D, 0x81, 0x00, 0x4E};
const   INT8U   DSPCMD_POLL_CALE_VERSION[4]     = {0x4D, 0x81, 0x01, 0x47};
const   INT8U   DSPCMD_POLL_USER_VERSION[4]     = {0x4D, 0x81, 0x02, 0x5C};
/*
 *  ����-����/UI/����
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
 *  �궨-��ѯ
 */
const   INT8U   DSPCMD_CALE_POLL[4]             = {0x4D, 0x65, 0x00, 0x2E};
/*
 *  ¼��-����
 */
const   INT8U   DSPCMD_REC_PLAY[4]              = {0x4D, 0x6A, 0x00, 0x47};

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
/*
 * OSD��Ϣ����
 */
volatile INT8U  DSPCMD_OSD[11]                  = {0x4D, 0xCA, 0x90, 0xA1, 0xA2, 0xA3, 0x00, 0x00, 0x00, 0x00, 0x00};
#if 0
/*********************************************************************************************************
** Function name:       UartApp_DealRcvMsg
** Descriptions:        Ӧ�ñ���֡����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ������
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
    ** ������֡��ʼ
    *****************************************************************************************************/
    ucMsgId  = UartAppRcvMsg.ucDat[1];
    switch (ucMsgId) {
        case UART_SYS_RST_MSG_ID:           /* CMDM12   ϵͳ��λ    */
            UartApp_DealRcvMsg_AckUsualDeal(UartAppRcvMsg.ucDat[2]);
            euDealRslt = STAT_MSG_DEALED;
            break;
        case UART_SYS_CALL_MSG_ID:          /* CMDM13   ϵͳ����    */
            if (!UartApp_DealRcvMsg_AckUsualDeal(UartAppRcvMsg.ucDat[2])) {
                euDealRslt = STAT_MSG_DEALED;
                break;
            }
            /*------------------------------------------------------------------------------------------*/
            // /* ͨ�Ų���OK */
            // Flag.UartIsOK   = TRUE;
            // /* �궨��ʽ��ʼ */
            // Stat.AvmCaleCur = STAT_AVM_CALE_ING;
            // Stat.System     = STAT_SYSTEM_CALE;
            /*------------------------------------------------------------------------------------------*/
            break;
        case UART_VIEW_MODE_MSG_ID:         /* CMDM10   ��ʾģʽ    */
            UartApp_DealRcvMsg_AckUsualDeal(UartAppRcvMsg.ucDat[2]);
            euDealRslt = STAT_MSG_DEALED;
            /*------------------------------------------------------------------------------------------*/
            // /* ͨ�Ų���OK */
            // Flag.UartIsOK   = TRUE;
            /*------------------------------------------------------------------------------------------*/
            break;
        case UART_POLL_VERSION_MSG_ID:      /* CMDM129  ��ѯ�汾    */
            if (!UartApp_DealRcvMsg_AckPollDeal(UartAppRcvMsg.ucDat[2], UartAppRcvMsg.ucDat[3])) {
                euDealRslt = STAT_MSG_DEALED;
                break;
            }
            /*------------------------------------------------------------------------------------------*/
            // /* ͨ�Ų���OK */
            // Flag.UartIsOK   = TRUE;
            /*------------------------------------------------------------------------------------------*/
            euDealRslt = STAT_MSG_DEALED;
            break;
        case UART_CALE_STAT_MSG_ID:         /* CMDM101  �궨״̬    */
            if (!UartApp_DealRcvMsg_AckUsualDeal(UartAppRcvMsg.ucDat[2])) {
                euDealRslt = STAT_MSG_DEALED;
                break;
            }
            // /* ͨ�Ų���OK */
            // Flag.UartIsOK   = TRUE;
            // /*------------------------------------------------------------------------------------------*/
            // if (UartAppRcvMsg.ucDat[2] == UART_CALE_STAT_MSG_ID_ING) {
                // Stat.AvmCaleCur = STAT_AVM_CALE_ING;
                // Stat.System     = STAT_SYSTEM_CALE;
            // } else if (UartAppRcvMsg.ucDat[2] == UART_CALE_STAT_MSG_ID_SUCC) {
                // /* �궨�ɹ� */
                // Stat.AvmCaleCur = STAT_AVM_CALE_SUCC;
                // Stat.System     = STAT_SYSTEM_INIT;
                // UartApp_SenCmd(DSPCMD_SYS_RST);
                // Time_Reset(&Time.AvmInitCore);
            // } else if (UartAppRcvMsg.ucDat[2] == UART_CALE_STAT_MSG_ID_FAIL) {
                // /* �궨ʧ�� */
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
    ** ������֡����
    *****************************************************************************************************/
    UartAppRcvMsg.blNew = FALSE;
    
    return euDealRslt;
}
/*********************************************************************************************************
** Function name:       UartApp_DealRcvMsg_AckUsualDeal
** Descriptions:        
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
BOOLEAN UartApp_DealRcvMsg_AckUsualDeal(INT8U ucErr)
{
    #if 0
    if (Flag.UartSenBufAckWait) {
        switch (ucErr) {
            case UART_ERR_SUCC:         /* �ɹ�             */
                UartAll_DealSenBuf_AckWaitSucc();               return TRUE;
                // break;
            case UART_ERR_OUT_ID:       /* ���֧��       */
                UartAll_DealSenBuf_AckWaitFail_NextSen();       return FALSE;
                // break;
            case UART_ERR_CODE_CRC:     /* ����CRCУ��ʧ��  */
                UartAll_DealSenBuf_AckWaitFail_ReSen();         return FALSE;
                // break;
            case UART_ERR_DATA_CRC:     /* ����CRCУ��ʧ��  */
                UartAll_DealSenBuf_AckWaitFail_ReSen();         return FALSE;
                // break;
            case UART_ERR_CALE_SUCC:    /* �궨�ɹ�         */
                UartAll_DealSenBuf_AckWaitSucc();               return TRUE;
                // break;
            case UART_ERR_CALE_FAIL:    /* �궨ʧ��         */
                UartAll_DealSenBuf_AckWaitSucc();               return TRUE;
                // break;
            default:                    /* ��������         */
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
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
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
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
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
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
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
