/****************************************Copyright (c)****************************************************
**                            Guangzhou ZLGMCU Development Co., LTD
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           LPUART.c
** Last modified Date:  2021-05-12
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2021-05-12
** Version:             V1.00
** Descriptions:        
**                      
**--------------------------------------------------------------------------------------------------------
** Modified by:         zhaohai
** Modified date:       2021-05-12
** Version:             
** Descriptions:        
**
** Rechecked by:        
*********************************************************************************************************/
#include "includeall.h"

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/
const lpuart_user_config_t lpuart0_InitConfig0 = {                      /* LPUART0参数表，500K          */
  .transferType     = LPUART_USING_INTERRUPTS,
  .baudRate         = 9600U,
  .parityMode       = LPUART_PARITY_DISABLED,
  .stopBitCount     = LPUART_ONE_STOP_BIT,
  .bitCountPerChar  = LPUART_8_BITS_PER_CHAR,
  .rxDMAChannel     = 0U,
  .txDMAChannel     = 0U,
};
/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:       UART_InitReg
** Descriptions:        串口初始化，设置为8位数据位，1位停止位，偶校验
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_Init
 * Description   : This function initializes a LPUART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the LPUART module, initialize the
 * module to user defined settings and default settings, configure the IRQ state
 * structure and enable the module-level interrupt to the core, and enable the
 * LPUART module transmitter and receiver.
 * The following is an example of how to set up the lpuart_state_t and the
 * lpuart_user_config_t parameters and how to call the LPUART_DRV_Init function
 * by passing in these parameters:
 *    lpuart_user_config_t lpuartConfig;
 *    lpuartConfig.baudRate = 9600;
 *    lpuartConfig.bitCountPerChar = LPUART_8_BITS_PER_CHAR;
 *    lpuartConfig.parityMode = LPUART_PARITY_DISABLED;
 *    lpuartConfig.stopBitCount = LPUART_ONE_STOP_BIT;
 *    lpuartConfig.transferType = LPUART_USING_INTERRUPTS;
 *    lpuart_state_t lpuartState;
 *    LPUART_DRV_Init(instance, &lpuartState, &lpuartConfig);
 *
 * Implements    : LPUART_DRV_Init_Activity
 *END**************************************************************************/
void    LPUART0_InitReg(void)
{
    uint32_t lpuartSourceClock;

    (void)CLOCK_SYS_GetFreq(LPUART0_CLK, &lpuartSourceClock);
    DEV_ASSERT(lpuartSourceClock > 0U);
    
    /* initialize the LPUART instance */
    LPUART_Init(LPUART0);

    /* initialize the parameters of the LPUART config structure with desired data */
    LPUART0_SetBaudRate(lpuart0_InitConfig0.baudRate);
    
    #if 0
    LPUART_SetBitCountPerChar(LPUART0, lpuart0_InitConfig0.bitCountPerChar);
    /* zhaohai 2021-05-14 使能校验位，要设置CTRL中的Bit4 或 BAND中的Bit29。注意：此处仅处理了8+1宽度，未处理9+1宽度 */
    if (lpuart0_InitConfig0.parityMode != LPUART_PARITY_DISABLED) {
        LPUART0->CTRL   = (LPUART0->CTRL & ~LPUART_CTRL_M_MASK) | ((uint32_t)1U << LPUART_CTRL_M_SHIFT);
    } else {
        LPUART0->CTRL  &= ~LPUART_CTRL_M_MASK;
    }
    #endif
    if (lpuart0_InitConfig0.parityMode != LPUART_PARITY_DISABLED) {
        LPUART_SetBitCountPerChar(LPUART0, lpuart0_InitConfig0.bitCountPerChar, true);
    } else {
        LPUART_SetBitCountPerChar(LPUART0, lpuart0_InitConfig0.bitCountPerChar, false);
    }
    LPUART_SetParityMode(LPUART0, lpuart0_InitConfig0.parityMode);
    LPUART_SetStopBitCount(LPUART0, lpuart0_InitConfig0.stopBitCount);

    /* finally, enable the LPUART transmitter and receiver */
    LPUART_SetTransmitterCmd(LPUART0, true);
    LPUART_SetReceiverCmd(LPUART0, true);
		//FLEXIO_UART_DRV_Init(0, &0, &0);
    //INT_SYS_InstallHandler(LPUART0_RxTx_IRQn, LPUART0_RxTx_IRQHandler, (isr_t*) 0);
    /* Enable LPUART interrupt. */
    LPUART_SetIntMode(LPUART0, LPUART_INT_RX_DATA_REG_FULL, true);
    LPUART_SetIntMode(LPUART0, LPUART_INT_RX_OVERRUN, true);
    
    INT_SYS_EnableIRQ(LPUART0_RxTx_IRQn);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_Deinit
 * Description   : This function shuts down the UART by disabling interrupts and
 *                 transmitter/receiver.
 *
 * Implements    : LPUART_DRV_Deinit_Activity
 *END**************************************************************************/
void    LPUART0_Deinit(void)
{

    uint32_t lpuartSourceClock;

    (void)CLOCK_SYS_GetFreq(LPUART0_CLK, &lpuartSourceClock);

    /* Check if current instance is already de-initialized or is gated.*/
    DEV_ASSERT(s_lpuartStatePtr[instance] != NULL);
    DEV_ASSERT(lpuartSourceClock > 0U);

    /* Wait until the data is completely shifted out of shift register */
    while (!LPUART_GetStatusFlag(LPUART0, LPUART_TX_COMPLETE)) {}

    /* Disable LPUART interrupt. */
    INT_SYS_DisableIRQ(LPUART0_RxTx_IRQn);

    /* disable tx and rx */
    LPUART_SetTransmitterCmd(LPUART0, false);
    LPUART_SetReceiverCmd(LPUART0, false);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_SetBaudRate
 * Description   : Configures the LPUART baud rate.
 * In some LPUART instances the user must disable the transmitter/receiver
 * before calling this function.
 * Generally, this may be applied to all LPUARTs to ensure safe operation.
 *
 * Implements    : LPUART_DRV_SetBaudRate_Activity
 *END**************************************************************************/
void    LPUART0_SetBaudRate(INT32U desiredBaudRate)
{
    uint16_t sbr, sbrTemp, i;
    uint32_t osr, tempDiff, calculatedBaud, baudDiff;
    uint32_t lpuartSourceClock;

    /* Get the LPUART clock as configured in the clock manager */
    (void)CLOCK_SYS_GetFreq(LPUART0_CLK, &lpuartSourceClock);

    /* Check if current instance is clock gated off. */
    DEV_ASSERT(lpuartSourceClock > 0U);
    /* Check if the desired baud rate can be configured with the current protocol clock. */
    DEV_ASSERT(lpuartSourceClock >= (desiredBaudRate * 4U));

    /* This lpuart instantiation uses a slightly different baud rate calculation
     * The idea is to use the best OSR (over-sampling rate) possible
     * Note, osr is typically hard-set to 16 in other lpuart instantiations
     * First calculate the baud rate using the minimum OSR possible (4) */
    osr = 4;
    sbr = (uint16_t)(lpuartSourceClock / (desiredBaudRate * osr));
    calculatedBaud = (lpuartSourceClock / (osr * sbr));

    if (calculatedBaud > desiredBaudRate)
    {
        baudDiff = calculatedBaud - desiredBaudRate;
    }
    else
    {
        baudDiff = desiredBaudRate - calculatedBaud;
    }

    /* loop to find the best osr value possible, one that generates minimum baudDiff
     * iterate through the rest of the supported values of osr */
    for (i = 5U; i <= 32U; i++)
    {
        /* calculate the temporary sbr value   */
        sbrTemp = (uint16_t)(lpuartSourceClock / (desiredBaudRate * i));
        /* calculate the baud rate based on the temporary osr and sbr values */
        calculatedBaud = (lpuartSourceClock / (i * sbrTemp));

        if (calculatedBaud > desiredBaudRate)
        {
            tempDiff = calculatedBaud - desiredBaudRate;
        }
        else
        {
            tempDiff = desiredBaudRate - calculatedBaud;
        }

        if (tempDiff <= baudDiff)
        {
            baudDiff = tempDiff;
            osr = i;  /* update and store the best osr value calculated */
            sbr = sbrTemp;  /* update store the best sbr value calculated */
        }
    }

    /* Check if osr is between 4x and 7x oversampling.
     * If so, then "BOTHEDGE" sampling must be turned on */
    if ((osr > 3U) && (osr < 8U))
    {
        LPUART_EnableBothEdgeSamplingCmd(LPUART0);
    }

    /* program the osr value (bit value is one less than actual value) */
    LPUART_SetOversamplingRatio(LPUART0, (osr - 1U));

    /* write the sbr value to the BAUD registers */
    LPUART_SetBaudRateDivisor(LPUART0, sbr);
}
/*********************************************************************************************************
** Function name:       LPUART0_SenByte
** Descriptions:        向串口发送子节数据，并等待数据发送完成，使用查询方式
** input parameters:    ucDat:  要发送的数据
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
BOOLEAN LPUART0_SenByte(INT8U ucDat)
{
    INT32U  i = 60000;
    while(!LPUART_GetStatusFlag(LPUART0, LPUART_TX_DATA_REG_EMPTY)) {
        if (--i == 0) {
            return FALSE;
        }
    }
    LPUART_Putchar(LPUART0, ucDat);
    return TRUE;
}
/*********************************************************************************************************
** Function name:       LPUART0_SenBuf
** Descriptions:        向串口发送字符串
** input parameters:    pucDat: 要发送的字符串指针
**                      ulLen:  要发送的数据个数
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
BOOLEAN LPUART0_SenBuf(INT8U *pucDat, INT32U ulLen)
{
    INT32U i;
    
    for (i = 0; i < ulLen; i++) {
        if (!LPUART0_SenByte(*pucDat++)) {
            return FALSE;
        }
    }
    return TRUE;
}
/*********************************************************************************************************
** Function name:       LPUART0_RcvByte
** Descriptions:        接收数据
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

#define RECEIVE_CONTROLLER_DATA_LENGTH 2
#define ReceiveRestart()		RxLen = 0,SCICheckout  = 0

void    LPUART0_RcvByte(void)
{
//    INT8U   temp;
//    static INT8U RxLen;
//    static INT8U SCICheckout;
//	 
//    LPUART_Getchar(LPUART0, &temp);
//   
//			
//				if(RxLen == 0)
//				{
//					if((temp == 3) || (temp == 6))
//					{
//						uart_txbuffer[0] = temp;
//						SCICheckout += temp;
//						RxLen++;
//					}
//					else
//					{
//						 ReceiveRestart();
//					}
//				}
//				
//				else if(RxLen == 1)
//				{
//					if(temp == 1)
//					{
//						uart_txbuffer[1]= temp;
//						SCICheckout += temp;
//						RxLen++;
//					}
//					else
//					{
//						 ReceiveRestart();
//					}
//				}
//				else if(RxLen == (RECEIVE_CONTROLLER_DATA_LENGTH+3-1))
//				{
//					if(temp ==  SCICheckout)
//					{
// 						  gKeyValue = uart_rxbuffer[2];  
//							HuoErIO_Flag = uart_rxbuffer[3]?1:0;
//							if(gKeyValue > 0)
//                EvRecvFlag = 1;
//					}						
//					else
//					{
//						 ReceiveRestart();
//					}
//				}
//				
//				else
//				{
//					uart_txbuffer[RxLen] = temp;
//					RxLen++;
//					SCICheckout += temp;
//				}
}
/*********************************************************************************************************
** Function name:       LPUART0_RxTx_IRQHandler
** Descriptions:        UART中断服务函数
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    LPUART0_RxTx_IRQHandler(void)
{
	 static  unsigned char sUartLen;
	 /* Handle transmitter data register empty interrupt */
    if (LPUART_GetIntMode(LPUART0, LPUART_INT_TX_DATA_REG_EMPTY))
    {
        if (LPUART_GetStatusFlag(LPUART0, LPUART_TX_DATA_REG_EMPTY))
        {
            /* Transmit the data */
            //LPUART_DRV_PutData(instance);
					
        }
    }
		
		if (LPUART_GetIntMode(LPUART0, LPUART_INT_TX_COMPLETE))
    {
        if (LPUART_GetStatusFlag(LPUART0, LPUART_TX_COMPLETE ))
        {
           //LPUART_Putchar(LPUART0, 0x55); /* Transmit the data */
					
					sUartLen++;
					if(sUartLen < 6)
					{
							LPUART_Putchar(LPUART0,gtab[sUartLen]);
					}
					else
					{
							sUartLen =0 ;
							LPUART_SetIntMode(LPUART0, LPUART_INT_TX_COMPLETE, false);
					}
						
        }
    }
		
		
    /* Handle receive data full interrupt */
    if (LPUART_GetIntMode(LPUART0, LPUART_INT_RX_DATA_REG_FULL))
    {
        if (LPUART_GetStatusFlag(LPUART0, LPUART_RX_DATA_REG_FULL))
        {
            RDUART0_RcvByte();//LPUART0_RcvByte();
        }
    }
    
   
    
    /* Handle receive overrun interrupt */
    if (LPUART_GetStatusFlag(LPUART0, LPUART_RX_OVERRUN))
    {
        /* Clear the flag, OR the rxDataRegFull will not be set any more */
        (void)LPUART_ClearStatusFlag(LPUART0, LPUART_RX_OVERRUN);
    }
}
/*********************************************************************************************************
** Function name:       LPUART0_RcvDatPolling
** Descriptions:        接收数据
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    LPUART0_RcvDatPolling(INT8U *pucDat, INT32U ulLen)
{
    INT8U   ucDat;
    
    while (ulLen > 0U) {
        while (!LPUART_GetStatusFlag(LPUART0, LPUART_RX_DATA_REG_FULL));
        
        LPUART_Getchar(LPUART0, pucDat);
        ulLen--;
    }
    
    /* Read dummy to clear RDRF flag */
    LPUART_Getchar(LPUART0, &ucDat);
    LPUART_ClearStatusFlag(LPUART0, LPUART_RX_OVERRUN);
}
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/