#include "UpdataCanMessage.h"
#include "FuncTab.h"
#include "bsp_eeprom.h"

typedef enum
{
	OFF,
	ACC,
	ON,
	Crank
}CheJi_Power;

/****************************************************************************************************************************************** 
* 函数名称:	UpdataCanMessage
* 功能说明:	用于更新383周期报文
* 输    入: 无	
* 输    出: 返回8字节缓冲区首地址
******************************************************************************************************************************************/
#define VCU_POWER_OFF 1

u8*  UpdataCanMessage(void)
{
	
//    if(gVCU_VIBModeCfg.Bit.power_supply == VCU_POWER_OFF )
//		{
//				gstCanMessage.WorkMode = 0;	
//		}
//		else
		{
				if(SysRunFlag)
				{
						gstCanMessage.WorkMode =(HeatFlag)?1:2;
				}
				else
				{
						gstCanMessage.WorkMode = 0;	
				}
		}
		if(gstCanMessage.CoolLastTempSet ==  COOLTEMPMin-1)
		{
				gstCanMessage.CoolLastTempSet = COOLTEMPMin+40;
		}
		else
		{
				gstCanMessage.CoolLastTempSet = gHeatCoolTemp.Bit.CoolTempSet+40;
		}
		
		gstCanMessage.HeatLastTempSet = gHeatCoolTemp.Bit.HeatTempSet+40;
		gstCanMessage.SetTempValue    = (gHeatCoolTemp.Bit.cool>0)?gstCanMessage.CoolLastTempSet:gstCanMessage.HeatLastTempSet;
		gstCanMessage.SetTempValue = (gstCanMessage.SetTempValue == 0x27)?(gstCanMessage.SetTempValue= 0x28):gstCanMessage.SetTempValue;
		gstCanMessage.RealTempValue   =  gTempAD+40;
		gstCanMessage.SysState.Bit.DoorState = HuoErIO_Flag;
		gstCanMessage.SysState.Bit.LockStte = sysLock;
		
		
		gstCanMessage.SysState.Bit.RunState = (ALLTempSenseErrowFlag || PanelLostFlag || AbnormalPowerFlag||HeatErrowFlag || gstYaSuoJiErrow.ErrorCodeDisplayData >0xf0)?1:0;	
		gstCanMessage.SysState.Bit.VIB_VoiceSet = VoiceSetFlag;
		gstCanMessage.rev[1] = gKeyValue;
		return (u8*)&gstCanMessage;
}

u8*  UpdataCanMessage_OFF(void)
{
		gstCanMessage.WorkMode = 0;			
		gstCanMessage.CoolLastTempSet = gHeatCoolTemp.Bit.CoolTempSet+40;
		gstCanMessage.HeatLastTempSet = gHeatCoolTemp.Bit.HeatTempSet+40;
		gstCanMessage.SetTempValue    = (gHeatCoolTemp.Bit.cool>0)?gstCanMessage.CoolLastTempSet:gstCanMessage.HeatLastTempSet;
		gstCanMessage.RealTempValue   =  gTempAD+40;
		gstCanMessage.SetTempValue = (gstCanMessage.SetTempValue == 0x27)?(gstCanMessage.SetTempValue= 0x28):gstCanMessage.SetTempValue;
		gstCanMessage.SysState.Bit.DoorState = HuoErIO_Flag;
		gstCanMessage.SysState.Bit.LockStte = sysLock;
		//gstCanMessage.SysState.Bit.RunState = (ALLTempSenseErrowFlag || AbnormalPowerFlag)?1:0;
		gstCanMessage.SysState.Bit.RunState =(ALLTempSenseErrowFlag || PanelLostFlag || AbnormalPowerFlag||HeatErrowFlag || gstYaSuoJiErrow.ErrorCodeDisplayData >0xf0)?1:0;
		return (u8*)&gstCanMessage;
}

#define VIB_WorkModeSet_VD    0x08
#define TEL_VIB_TempSetReq_VD 0x10

void   Updata_TCL_TEL_CanMessage(u8* Tab,CanMessageType num)
{
#if 1
		STMessage *stTab;
		stTab = (STMessage *)Tab;

		if(SysRunFlag)
		{
				stTab->WorkMode =(HeatFlag)?1:2;
		}
		else
		{
				stTab->WorkMode = 0;	
		}
		
		

		stTab->CoolLastTempSet = gHeatCoolTemp.Bit.CoolTempSet+40;
		stTab->HeatLastTempSet = gHeatCoolTemp.Bit.HeatTempSet+40;
		if(stTab->CoolLastTempSet ==  COOLTEMPMin-1)
		{
				stTab->CoolLastTempSet = COOLTEMPMin+40;
		}
		else
		{
				stTab->CoolLastTempSet = gHeatCoolTemp.Bit.CoolTempSet+40;
		}
		stTab->SetTempValue    = (gHeatCoolTemp.Bit.cool>0)?stTab->CoolLastTempSet:stTab->HeatLastTempSet;
		stTab->RealTempValue   = gTempAD+40;
		if(num == CDC)
		{
			if(gstCDCMessage.cdc.Bit.VIB_dooropenReq == 0)
			{
					stTab->SysState.Bit.DoorState = 1;
			}
			else
			{
					stTab->SysState.Bit.DoorState = 3;
			}
			
			if(gstCDCMessage.cdc.Bit.VIB_ChildLockSt == 1)
			{
					stTab->SysState.Bit.LockStte = 1;
			}
			else if(gstCDCMessage.cdc.Bit.VIB_ChildLockSt == 2)
			{
					stTab->SysState.Bit.LockStte = 0;
			}
			else
			{
					stTab->SysState.Bit.LockStte = 3;
			}
					
		}
		else
		{
				stTab->SysState.Bit.DoorState = HuoErIO_Flag;//stTab->SysState.Bit.DoorState = (ChouTiFlag)?1:3;
				stTab->SysState.Bit.LockStte = sysLock;
		}
		stTab->SysState.Bit.RunState = (ALLTempSenseErrowFlag || PanelLostFlag || AbnormalPowerFlag||HeatErrowFlag || gstYaSuoJiErrow.ErrorCodeDisplayData >0xf0)?1:0;
#endif 
}

void ReadBusState_318(void)
{
	u8 tab[8],i,tempTab[8];
  static u8 sHisBusState = OFF;

	
	for(i=0;i<8; i++)
	{
			tab[i] =0;
			tempTab[i] = 0;
	}

	if(	__RTE_AppRxPriodicMsg(0x318,tab))
	{
			stBusState.all = tab[0];
			DayAndNightFlag = (tab[3]> 0)?1:0;
			gLightAdjust =(tab[3]> 0)?0:0xc0;
		
//			if(stBusState.Bit.BCM_KeySt == OFF)
//			{
//					if(sHisBusState == ACC || sHisBusState == ON)
//					{
//							gAccToOff_DelayCnt = _3S400MS_Per100MS;//__RTE_SendAppMsg(UpdataCanMessage_OFF());					
//					}
//			}	
		
			if(stBusState.Bit.BCM_KeySt == ACC || stBusState.Bit.BCM_KeySt == ON)
			{
				if(sHisBusState == OFF)
				{					
						UpdataCanMessage();
						gVCU_VIBModeCfg.all = 0;
				}
//				gAccToOff_DelayCnt = 0;	
			}
			sHisBusState = stBusState.all;
	}
	
	if(	__RTE_AppRxPriodicMsg(0x3F2,tab))
	{
			if((tab[0] == 6) && (tab[1] == 0) &&(tab[2] == 3) && (tab[3] == 3) && (tab[4] == 9) &&(tab[5] == 9) &&(tab[6] == 0x55) &&(tab[7] == 0xaa)&& !AKFactoryTestFlag)
			{
						SysRest();
						RDFactoryTestFlag = 1;
						AKFactoryTestFlag = 1;
						Buzzer2Flag =1;			
			}
			else if((tab[0] == 1) && (tab[1] == 0) &&(tab[2] == 2) && (tab[3] == 2) && (tab[4] == 3) &&(tab[5] == 3) &&(tab[6] == 0x55) &&(tab[7] == 0xaa)&& !AKFactoryTestFlag)
			{
						tempTab[0] = gstADCollect.OzneCurent;
						tempTab[1] = gstADCollect.HeatCurent;
						tempTab[2] = gstADCollect.CoolCurent;
						tempTab[3] = gstADCollect.LEDCurent;
						tempTab[4] = gstADCollect.ChouTiCurent;
						tempTab[5] = gKeyValue;
						tempTab[6] = TemprertureTab[11].DisplayMode;//gbFlagData[1].all;
						tempTab[7] = gst22_2EMessage.Wdata;//TemprertureTab[11].CompensationValue;//gbFlagData[2].all;
						tab[0] = 0;
						AiKaiOzneTestFlag = 1;
						FLEXCAN_TxData(CAN0, 0, 0x093, tempTab, 8);
			}
			else
			{
					gVCU_VIBModeCfg.all = tab[3];	
					if(gVCU_VIBModeCfg.Bit.power_supply ^ HisVCU_VIBPwrOff)
					{				
						HisVCU_VIBPwrOff = gVCU_VIBModeCfg.Bit.power_supply;
						if(gVCU_VIBModeCfg.Bit.power_supply )
						{	
								SysRunFlag = 1 ;
								KeyPower();
						}
						else
						{
							#if 0
								if(!SysRunFlag)
								{
										KeyPower();
								}
							#else
								BSP_EEPROM_Initialize();
								UpdataCanMessage();
							#endif
						}												
					}
			}
	}
//	if(gAccToOff_DelayCnt > 0)
//	{
//			gAccToOff_DelayCnt--;
//			__RTE_SendAppMsg(UpdataCanMessage_OFF());			
//	}
	
}

