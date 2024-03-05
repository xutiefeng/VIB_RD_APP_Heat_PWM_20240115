#include "clib.h"

#define DIS_INTRUPT     {}//NVIC_INT_Enable()
#define EN_INTRUPT      {}//NVIC_INT_Disable()

void PushEvent(Uchar event)
{	
	Uchar temp;

	if(gstPushPop.WriteEventCount >= EVENT_BUFFER_LENGTH)
	{
		gstPushPop.WriteEventCount = 0;
	}
	for(temp = 0; temp <= gstPushPop.WriteEventCount; temp++)
	{
		if(event == gEventBuffer[temp] && event != ev20MS && event != ev50MS && event != ev100MS && event != ev1S && event != ev5MS)
		{
			return;
		}
	}
	gEventBuffer[gstPushPop.WriteEventCount] = event;
	gstPushPop.WriteEventCount++;	
}

Uchar PopEvent(void)
{
    Uchar event;
    DIS_INTRUPT;
    if(gstPushPop.ReadEventCount >= EVENT_BUFFER_LENGTH)
    {
        gstPushPop.ReadEventCount = 0;
        event = gEventBuffer[gstPushPop.ReadEventCount];
    }
		else
		{	
			if(gstPushPop.ReadEventCount >= gstPushPop.WriteEventCount)
			{	
				gstPushPop.ReadEventCount = 0;
				gstPushPop.WriteEventCount = 0;

				event = 0xff;
			}
			else
			{
				event = gEventBuffer[gstPushPop.ReadEventCount];
				gEventBuffer[gstPushPop.ReadEventCount] = 0xff;
				gstPushPop.ReadEventCount++;
			}
		}
	EN_INTRUPT;
    
	return (event);
}
/************************************************************************************************************************************************
 * �������򴮿�ע���ֽڽ��ջص�����       
 * ������UARTPort      -- ����
				 evt					 --�ź���
 *       pRxByteCBFunc -- Ҫע��Ļص�������    
 * ���أ���
 * ע�⣺��
*************************************************************************************************************************************************/
void ClibInit(void)
{
	//**********************************ע�ᴮ�ں���******************************************
	//BSP_UART_RegRxByteCBFunc(BSP_USART0,PushEvent,evReceiveZhuoDu);//ע�����ذ���Ƕȴ��������ͨ�ź���
	//BSP_UART_RegRxByteCBFunc(BSP_USART1,PushEvent,evReceiveDisplay);//ע����ʾ����
	//BSP_UART_RegRxByteCBFunc(BSP_USART2,PushEvent,evReceiveBMS);//ע�����ذ��BMS��ļ��ͨ�ź���
	//BSP_UART_RegRxByteCBFunc(BSP_USART3,PushEvent,evReceiveJiZhan);//ע�����ذ� �� ��վ��ļ��ͨ�ź���
	//**********************************ע�ᶨʱ���¼�******************************************
	//BSP_RegTickEvntFunc(PushEvent );
}

void EventCollect(void) 
{
  if(EvRecvFlag)
	{
      EvRecvFlag = 0;
      PushEvent(evReceiveDisplay);
	}
    
  if(Ev5MSFlag)
	{
		Ev5MSFlag = 0;
		PushEvent(ev5MS);
	}
    
	if(Ev20MSFlag)
	{
		Ev20MSFlag = 0;
		PushEvent(ev20MS);
	}
	if(Ev50MSFlag)
	{
		Ev50MSFlag = 0;
		PushEvent(ev50MS);
	}
	if(Ev100MSFlag)
	{
		Ev100MSFlag = 0;
		PushEvent(ev100MS);
	}
	if(Ev1SFlag)
	{
		Ev1SFlag = 0;
		PushEvent(ev1S);
	}
#if 0
	if(EvSysResetFlag)
	{
		EvSysResetFlag = 0;
		PushEvent(evSysRest);
	}
	if(EvReceiveControlFlag)
	{
		EvReceiveControlFlag = 0;
		PushEvent(evReceiveControl);
	}
	if(EvReceiveCoreFlag)
	{
		EvReceiveCoreFlag = 0;
		PushEvent(evReceiveCore);
	}
	if(Ev25MsFlag)
	{
		Ev25MsFlag = 0;
		PushEvent(evTime25MS);
	}
	if(Ev50MsFlag)
	{
		Ev50MsFlag = 0;
		PushEvent(evTime50MS);
	}
	if(Ev100MsFlag)
	{
		Ev100MsFlag = 0;
		PushEvent(evTime100MS);
	}
	if(Ev500MsFlag)
	{
		Ev500MsFlag = 0;
		PushEvent(evTime500MS);
	}
	if(Ev1SFlag)
	{
		Ev1SFlag = 0;
		PushEvent(evTime1S);
	}
#endif
}





















