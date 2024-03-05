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
** 全局定量
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量
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
** Descriptions:        获取信号状态
** input parameters:    *pFlagCur:  当前状态
**                      *pFlagPre:  之前状态
** output parameters:   无
** Returned value:      当前相比之前的结果
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
** Descriptions:        循环FIFO 指针前进, 仅适用MAX_256长度的Buf
** input parameters:    ucPointer:  读写指针
**                      ucInc:      前进数量
**                      ucBufLen:   FIFO深度
** output parameters:   无
** Returned value:      前进后的读写指针位置
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
** Descriptions:        循环FIFO 指针后退, 仅适用MAX_256长度的Buf
** input parameters:    ucPointer:  读写指针
**                      ucDec:      后退数量
**                      ucBufLen:   FIFO深度
** output parameters:   无
** Returned value:      后退后的读写指针位置
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
** Descriptions:        循环FIFO 写指针领先读指针数量, 仅适用MAX_256长度的Buf
** input parameters:    ucPointerHead:  写指针
**                      ucPointerTail:  读指针
**                      ucBufLen:       FIFO深度
** output parameters:   无
** Returned value:      写指针领先读指针数量
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
** Descriptions:        乘除并四舍五入, 仅适用MAX_256之间的运算
** input parameters:    ucSourDat:  源数据
**                      ucMul:      乘数
**                      ucDiv:      除数
** output parameters:   无
** Returned value:      计算结果
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
#if 0   /* void uxDat[] 在KEIL中不通过 */
/*********************************************************************************************************
** Function name:       Sort_Bubble
** Descriptions:        冒泡排序
** input parameters:    uxDat:      排序前数据
**                      ucLen:      长度
**                      ucWidth:    宽度 1:8位 2:16位 4:32位
**                      blOrder:    TRUE:升序   FALSE:降序
** output parameters:   uxDat:      排序后数据
** Returned value:      无
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
                    if(pucDat[i] > pucDat[i+1]) { //升序
                        ucTmp       = pucDat[i];
                        pucDat[i]   = pucDat[i+1];
                        pucDat[i+1] = ucTmp;
                    }
                }
            }
        } else {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pucDat[i] < pucDat[i+1]) { //降序
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
                    if(pusDat[i] > pusDat[i+1]) { //升序
                        usTmp       = pusDat[i];
                        pusDat[i]   = pusDat[i+1];
                        pusDat[i+1] = usTmp;
                    }
                }
            }
        } else {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pusDat[i] < pusDat[i+1]) { //降序
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
                    if(pulDat[i] > pulDat[i+1]) { //升序
                        ulTmp       = pulDat[i];
                        pulDat[i]   = pulDat[i+1];
                        pulDat[i+1] = ulTmp;
                    }
                }
            }
        } else {
            for(j = 0; j < ucLen - 1; j++) {
                for(i = 0; i < ucLen - 1 - j; i++) {
                    if(pulDat[i] < pulDat[i+1]) { //降序
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
** Descriptions:        算术平均滤波法
** input parameters:    uxDat:      源数据
**                      ucLen:      长度
**                      ucWidth:    宽度 1:8位 2:16位 4:32位
** output parameters:   无
** Returned value:      计算结果
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
