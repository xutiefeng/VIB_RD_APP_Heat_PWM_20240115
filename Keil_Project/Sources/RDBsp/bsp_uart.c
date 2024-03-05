

#include "RDBsp\bsp_uart.h"

 volatile unsigned  char gKeyValue;;

#define		HEAD_CODE_NORMAL					0x03	
#define		HEAD_CODE_EVENT						0x06	
#define		ZHUKONGBAN_ADDR						0X01
#define		RX_Len                              0X05

//uint8_t     SCICheckout;                             
//uint8_t     RxLen; 

#define ReceiveRestart()	 RxLen = 0, SCICheckout  = 0
#define RECEIVE_CONTROLLER_DATA_LENGTH 2
/*
此函数
*/



void    RDUART0_RcvByte(void)
{
    INT8U   temp;
    static INT8U RxLen;
    static INT8U SCICheckout;
	  static INT8U rx[6];
    LPUART_Getchar(LPUART0, &temp);
   
			  if(AKFactoryTestFlag)
				{
						ReceiveRestart();
						return;
				}
				if(RxLen == 0)
				{
					if((temp == 3) || (temp == 6))
					{
						rx[0] = temp;
						SCICheckout += temp;
						RxLen++;
					}
					else
					{
						 ReceiveRestart();
					}
				}
				
				else if(RxLen == 1)
				{
					if(temp == 1 || temp == 2 || temp == 3)
					{
						rx[1]= temp;
						SCICheckout += temp;
						RxLen++;
					}
					else
					{
						 ReceiveRestart();
					}
				}
				else if(RxLen == (5-1))
				{
 					if(temp ==  SCICheckout)
					{
							gUartSingnalCnt = 0;
 						  gKeyValue = rx[2];  
							HuoErIO_Flag = (rx[3]&0x01)?1:0;
							//gbFlagData[7].all = rx[3];
							if(gKeyValue > 0)
							{
									EvRecvFlag = 1;
							}       
							PanelLostFlag = 0;
							if(rx[1] == 3)
							{
									RDFactoryTestFlag = 1;
							}
							else if(rx[2]&SRC_Config)
							{
									LinMingDuFlag = 1;//灵敏度设置完成
							}
							else
							{
									RDFactoryTestFlag = 0;
							}
							ReceiveRestart();
					}						
					else
					{
//						 if((rx[1] == 2) && rx[0] == 3)
//						 {
//									RDFactoryUartFlag = 1;
//						 }							
						 ReceiveRestart();
					}
				}
				
				else
				{
					rx[RxLen] = temp;
					RxLen++;
					SCICheckout += temp;
				}
}

void BSP_UART_Init(void)
{
		LPUART0_InitReg();
}


void BSP_UART_RegRxByteCBFunc (void)
{
  	//SERCOM0_USART_ReadCallbackRegister(UART_RXCallback1, (uintptr_t)NULL);   //uart rxd callback
    //SERCOM0_USART_Read(&uart_rxbuffer[0], 5);
}
