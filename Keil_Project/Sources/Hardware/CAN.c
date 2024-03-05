/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           CAN.c
** Last modified Date:  2012-06-01
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2012-06-01
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

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:       CAN_Init
** Descriptions:        ��ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void   CAN_Init(void)
{
    FLEXCAN0_InitReg();
}
/*********************************************************************************************************
** Function name:       CAN_SenMsg
** Descriptions:        CAN����һ֡����
** input parameters:    *pMsg: һ֡����
**                      ucHwTxNum��Ӳ�����������
** output parameters:   ��
** Returned value:      ������
*********************************************************************************************************/
#if CAN_HWTX_MODE == CAN_HWTX_MODE_FIXED
BOOLEAN CAN_SenMsg(volatile CanMsgStruct *pMsg, INT8U ucHwTxNum)
{
    FLEXCAN_TxData(CAN0, ucHwTxNum, pMsg->ulId, (INT8U *)pMsg->ucDat, pMsg->ucDlc);
    
    return TRUE;
}
#elif CAN_HWTX_MODE == CAN_HWTX_MODE_RANDOM
INT8U   CAN_SenMsg(volatile CanMsgStruct *pMsg)
{
    INT8U   TxBufNum = 0;                                       /* ѡ��ʹ�õķ��ͻ�����                 */
    
    FLEXCAN_TxData(CAN0, ucHwTxNum, pMsg->ulId, pMsg->ucDat, pMsg->ucDlc);
    
    return TxBufNum;
}
#elif CAN_HWTX_MODE == CAN_HWTX_MODE_WAIT
BOOLEAN CAN_SenMsg(volatile CanMsgStruct *pMsg)
{
    INT8U   TxBufNum = 0;                                       /* ѡ��ʹ�õķ��ͻ�����                 */
    
    FLEXCAN_TxData(CAN0, ucHwTxNum, pMsg->ulId, pMsg->ucDat, pMsg->ucDlc);
    #if 0
    i = 60000;
    while ((CANTFLG & TxBufNum) != TxBufNum) {                  /* Wait for Transmission completion     */
        if (--i == 0) {
            return FALSE;
        }
    }
    #endif
    
    return TRUE;
}
#endif
/*********************************************************************************************************
** Function name:       CAN_RcvMsg
** Descriptions:        CAN����һ֡����
** input parameters:    *pBuf: ������
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void    CAN_RcvMsg(volatile CanMbStruct *pMbInfo)
{
    INT8U   ucIndex;
    
    ucIndex                             = CanRcvBuf.IndexW;
    CanRcvBuf.IndexW                    = (CanRcvBuf.IndexW + 1) % CAN_BUF_LEN;
    CanRcvBuf.Len++;
    CanRcvBuf.Msg[ucIndex].ulId         = pMbInfo->pId->Bits.ID_STD;
    CanRcvBuf.Msg[ucIndex].ucDlc        = pMbInfo->pCs->Bits.DLC;
    CanRcvBuf.Msg[ucIndex].ucDat[0]     = pMbInfo->pRegion0->Bits.Data0;
    CanRcvBuf.Msg[ucIndex].ucDat[1]     = pMbInfo->pRegion0->Bits.Data1;
    CanRcvBuf.Msg[ucIndex].ucDat[2]     = pMbInfo->pRegion0->Bits.Data2;
    CanRcvBuf.Msg[ucIndex].ucDat[3]     = pMbInfo->pRegion0->Bits.Data3;
    CanRcvBuf.Msg[ucIndex].ucDat[4]     = pMbInfo->pRegion1->Bits.Data4;
    CanRcvBuf.Msg[ucIndex].ucDat[5]     = pMbInfo->pRegion1->Bits.Data5;
    CanRcvBuf.Msg[ucIndex].ucDat[6]     = pMbInfo->pRegion1->Bits.Data6;
    CanRcvBuf.Msg[ucIndex].ucDat[7]     = pMbInfo->pRegion1->Bits.Data7;
    CarSign_SleepBusAllowSet();
}

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
