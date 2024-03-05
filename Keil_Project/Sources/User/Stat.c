/****************************************Copyright (c)****************************************************
**                            Guangzhou ZLGMCU Development Co., LTD
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Stat.c
** Last modified Date:  2011-12-01
** Last Version:        V1.0
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2011-12-01
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
volatile StatStruct         Stat;

/*********************************************************************************************************
** Stat_Init
*********************************************************************************************************/
void    Stat_Init(void)
{
    /*--------------------------------------------------------------------------------------------------*/
    Stat.Sysrun         = STAT_RUNSTS_INIT;
    Stat.Canrun         = STAT_RUNSTS_INIT;
    Stat.System         = STAT_SYSTEM_INIT;
    /*--------------------------------------------------------------------------------------------------*/
    
    /*--------------------------------------------------------------------------------------------------*/
    
}
/*********************************************************************************************************
** Function name:       Stat_DealSign
** Descriptions:        ��ȡ�ź�״̬
** input parameters:    *pFlagCur:  ��ǰ״̬
**                      *pFlagPre:  ֮ǰ״̬
** output parameters:   ��
** Returned value:      ��ǰ���֮ǰ�Ľ��
*********************************************************************************************************/
STAT_SIGN_ENUM  Stat_DealSign(volatile BOOLEAN *pFlagCur, volatile BOOLEAN *pFlagPre)
{
    if (*pFlagPre) {
        if (*pFlagCur) {
            *pFlagPre   = TRUE;
            return        STAT_SIGN_H;
        } else {
            *pFlagPre   = FALSE;
            return        STAT_SIGN_FALL;
        }
    } else {
        if (*pFlagCur) {
            *pFlagPre   = TRUE;
            return        STAT_SIGN_RISE;
        } else {
            *pFlagPre   = FALSE;
            return        STAT_SIGN_L;
        }
    }
    // return STAT_SIGN_UNKNOWN;
}
/*********************************************************************************************************
** Function name:       CirBufPointerInc
** Descriptions:        ѭ��FIFO ָ��ǰ��, ������MAX_256���ȵ�Buf
** input parameters:    ucPointer:  ��дָ��
**                      ucInc:      ǰ������
**                      ucBufLen:   FIFO���
** output parameters:   ��
** Returned value:      ǰ����Ķ�дָ��λ��
*********************************************************************************************************/
INT8U   CirBufPointerInc(INT8U ucPointer, INT8U ucInc, INT8U ucBufLen)
{
    INT16U  usTmp;
    
    usTmp   = (INT16U)(ucPointer + ucInc);
    if (usTmp >= ucBufLen) {
        usTmp -= ucBufLen;
    }
    return (INT8U)(usTmp);
}
/*********************************************************************************************************
** Function name:       CirBufPointerDec
** Descriptions:        ѭ��FIFO ָ�����, ������MAX_256���ȵ�Buf
** input parameters:    ucPointer:  ��дָ��
**                      ucDec:      ��������
**                      ucBufLen:   FIFO���
** output parameters:   ��
** Returned value:      ���˺�Ķ�дָ��λ��
*********************************************************************************************************/
INT8U   CirBufPointerDec(INT8U ucPointer, INT8U ucDec, INT8U ucBufLen)
{
    INT8U   ucTmp;
    
    if (ucPointer < ucDec) {
        ucTmp   = ucBufLen - ucDec + ucPointer;
    } else {
        ucTmp   = ucPointer - ucDec;
    }
    return ucTmp;
}
/*********************************************************************************************************
** Function name:       CirBufPointerGap
** Descriptions:        ѭ��FIFO дָ�����ȶ�ָ������, ������MAX_256���ȵ�Buf
** input parameters:    ucPointerHead:  дָ��
**                      ucPointerTail:  ��ָ��
**                      ucBufLen:       FIFO���
** output parameters:   ��
** Returned value:      дָ�����ȶ�ָ������
*********************************************************************************************************/
INT8U   CirBufPointerGap(INT8U ucPointerHead, INT8U ucPointerTail, INT8U ucBufLen)
{
    INT8U   ucTmp;
    
    if (ucPointerHead > ucPointerTail) {
        ucTmp   = ucPointerHead - ucPointerTail;
    } else {
        ucTmp   = ucBufLen - ucPointerTail + ucPointerHead;
    }
    return ucTmp;
}
/*********************************************************************************************************
** Function name:       CalcAndFourDecFiveInc
** Descriptions:        �˳�����������, ������MAX_256֮�������
** input parameters:    ucSourDat:  Դ����
**                      ucMul:      ����
**                      ucDiv:      ����
** output parameters:   ��
** Returned value:      ������
*********************************************************************************************************/
INT16U  CalcAndFourDecFiveInc(INT8U ucSourDat, INT8U ucMul, INT8U ucDiv)
{
    INT16U  usTmp;
    INT16U  usResult;
    
    usResult    = ((INT16U)(ucSourDat * ucMul)) / ucDiv;
    usTmp       =  (INT16U)(ucSourDat * ucMul) - (INT16U)(usResult * ucDiv);
    usTmp       =  (INT16U)(usTmp * 2);
    if (usTmp >= ucDiv) {
        usResult += 1;
    }
    return usResult;
}
#if 0   /* void uxDat[] ��KEIL�в�ͨ�� */
/*********************************************************************************************************
** Function name:       Sort_Bubble
** Descriptions:        ð������
** input parameters:    uxDat:      ����ǰ����
**                      ucLen:      ����
**                      ucWidth:    ��� 1:8λ 2:16λ 4:32λ
**                      blOrder:    TRUE:����   FALSE:����
** output parameters:   uxDat:      ���������
** Returned value:      ��
*********************************************************************************************************/
void    Sort_Bubble(void uxDat[], INT8U ucLen, INT8U ucWidth, BOOLEAN blOrder)
{
    INT8U   i, j;
    INT8U   *pucDat;
    INT8U   ucTmp;
    INT16U  *pusDat;
    INT16U  usTmp;
    INT32U  *pulDat;
    INT32U  ulTmp;
    
    if (ucWidth == 1) {
        pucDat  = (INT8U *)uxDat;
        if (blOrder) {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pucDat[i] > pucDat[i+1]) { //����
                        ucTmp       = pucDat[i];
                        pucDat[i]   = pucDat[i+1];
                        pucDat[i+1] = ucTmp;
                    }
                }
            }
        } else {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pucDat[i] < pucDat[i+1]) { //����
                        ucTmp       = pucDat[i];
                        pucDat[i]   = pucDat[i+1];
                        pucDat[i+1] = ucTmp;
                    }
                }
            }
        }
    }
    
    if (ucWidth == 2) {
        pusDat  = (INT16U *)uxDat;
        if (blOrder) {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pusDat[i] > pusDat[i+1]) { //����
                        usTmp       = pusDat[i];
                        pusDat[i]   = pusDat[i+1];
                        pusDat[i+1] = usTmp;
                    }
                }
            }
        } else {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pusDat[i] < pusDat[i+1]) { //����
                        usTmp       = pusDat[i];
                        pusDat[i]   = pusDat[i+1];
                        pusDat[i+1] = usTmp;
                    }
                }
            }
        }
    }
    
    if (ucWidth == 4) {
        pulDat  = (INT32U *)uxDat;
        if (blOrder) {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pulDat[i] > pulDat[i+1]) { //����
                        ulTmp       = pulDat[i];
                        pulDat[i]   = pulDat[i+1];
                        pulDat[i+1] = ulTmp;
                    }
                }
            }
        } else {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pulDat[i] < pulDat[i+1]) { //����
                        ulTmp       = pulDat[i];
                        pulDat[i]   = pulDat[i+1];
                        pulDat[i+1] = ulTmp;
                    }
                }
            }
        }
    }
}
/*********************************************************************************************************
** Function name:       Filter_ArithmeticalAverage
** Descriptions:        ����ƽ���˲���
** input parameters:    uxDat:      Դ����
**                      ucLen:      ����
**                      ucWidth:    ��� 1:8λ 2:16λ 4:32λ
** output parameters:   ��
** Returned value:      ������
*********************************************************************************************************/
INT32U  Filter_ArithmeticalAverage(void uxDat[], INT8U ucLen, INT8U ucWidth)
{
    INT8U   i;
    INT8U   *pucDat;
    INT16U  usTmp   = 0;
    INT16U  *pusDat;
    INT32U  ulTmp   = 0;
    INT32U  *pulDat;
    unsigned long long  ullTmp = 0;
    
    if (ucWidth == 1) {
        pucDat  = (INT8U *)uxDat;
        for (i = 0; i < ucLen; i++) {
            usTmp     += pucDat[i];
        }
        return (INT32U)(usTmp / ucLen);
    }
    if (ucWidth == 2) {
        pusDat  = (INT16U *)uxDat;
        for (i = 0; i < ucLen; i++) {
            ulTmp     += pusDat[i];
        }
        return (INT32U)(ulTmp / ucLen);
    }
    if (ucWidth == 4) {
        pulDat  = (INT32U *)uxDat;
        for (i = 0; i < ucLen; i++) {
            ullTmp    += pulDat[i];
        }
        return (INT32U)(ullTmp / ucLen);
    }
}
#endif

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
