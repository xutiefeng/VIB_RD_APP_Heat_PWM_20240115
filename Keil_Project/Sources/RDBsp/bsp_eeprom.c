

#include <string.h>
#include "bsp_eeprom.h"
#include "globe.h"
#include "FuncTab.h"
#include "UpdataCanMessage.h"

/****************************************************************************************************************************************** 
* ��������:	 WriteTempEeprom
* ����˵��:  д��EEPROM�ӿ�
* ��    ��: ��	
* ��    ��: ��
******************************************************************************************************************************************/
void WriteTempEeprom(void)
{
	if(__RTE_AppEepromWrite(0,(u8*)&gHeatCoolTemp,4) )
	{
			__RTE_AppEepromWrite(0,(u8*)&gHeatCoolTemp,4) ;
	}
	
	if(__RTE_AppEepromWrite(32,(u8*)&TemprertureTab,TAB_SIZE) )
	{
			__RTE_AppEepromWrite(32,(u8*)&TemprertureTab,TAB_SIZE) ;
	}
		
	
//	if( stBusState.Bit.BCM_KeySt == 0)
//	 __RTE_SendAppMsg(UpdataCanMessage());
}


/****************************************************************************************************************************************** 
* ��������:	 ReadTempEeprom
* ����˵��:  ��ȡEEPROM�ӿ�
* ��    ��: ��	
* ��    ��: ��
******************************************************************************************************************************************/
#define _INIT_DADA 0x5b

void EEpromInit(void)
{
		gHeatCoolTemp.Bit.HisEeprom = _INIT_DADA;
    gHeatCoolTemp.Bit.HeatTempSet = 40;
    gHeatCoolTemp.Bit.CoolTempSet = 0;
    gHeatCoolTemp.Bit.cool = 1;
    gHeatCoolTemp.Bit.heat = 0;
    gHeatCoolTemp.Bit.SysRun = 0;
		gHeatCoolTemp.Bit.Lock = 0;
		memcpy((void *)TemprertureTab,(void *)ImageTemprertureTab,TAB_SIZE);
		WriteTempEeprom();
}

void ReadTempEeprom(void)
{
		u8 i;
		if(__RTE_AppEepromRead(0,(u8*)&gHeatCoolTemp,4))
		{
				__RTE_AppEepromRead(0,(u8*)&gHeatCoolTemp,4);
		}
		
    if(gHeatCoolTemp.Bit.HisEeprom != _INIT_DADA)
    {     
       EEpromInit();  		
    }
		else
		{
				if(__RTE_AppEepromRead(32,(u8*)&TemprertureTab,20))
				{
						__RTE_AppEepromRead(32,(u8*)&TemprertureTab,20);
				}
		}
		
		if(gHeatCoolTemp.Bit.heat)
		{
				if(gHeatCoolTemp.Bit.HeatTempSet == 45)
				{
							gstDisplayCode.CurMode = WenNaiMode;
							MoodeSetFlag = 1;
				}
												
				else if(gHeatCoolTemp.Bit.HeatTempSet == 55)
				{
						gstDisplayCode.CurMode = WenFanMode;
						MoodeSetFlag = 1;
				}
		}
		else
		{
			  if(gHeatCoolTemp.Bit.CoolTempSet == -1)
				{
							CoolSuDongFlag = 1;
							gstDisplayCode.CurMode = BingXianMode;			
							MoodeSetFlag = 1;
				}
												
				else if(gHeatCoolTemp.Bit.CoolTempSet == 4)
				{
						gstDisplayCode.CurMode = LengYinMode;
						MoodeSetFlag = 1;
				}
												
			  else if(gHeatCoolTemp.Bit.CoolTempSet == 9)
			  {
						gstDisplayCode.CurMode = GuoShuMode;
						MoodeSetFlag = 1;
			  }
		}
		if(gHeatCoolTemp.Bit.CoolTempSet < -9 )
		{
				gHeatCoolTemp.Bit.CoolTempSet = 0;
		}
		
		if(gHeatCoolTemp.Bit.HeatTempSet > 65)
		{
				gHeatCoolTemp.Bit.HeatTempSet = 40;
		}
		
		
				
		if( gHeatCoolTemp.Bit.cool ^ gHeatCoolTemp.Bit.heat)
		{
				for(i = 0; i<=TAB_LENGTH;i++ )
				{
						if(TemprertureTab[i].DisplayMode != ImageTemprertureTab[i].DisplayMode)
						{
								EEpromInit();
						}
							
						if(gHeatCoolTemp.Bit.CoolTempSet  < -10 || gHeatCoolTemp.Bit.CoolTempSet > 25||  (gHeatCoolTemp.Bit.HeatTempSet < 35) || (gHeatCoolTemp.Bit.HeatTempSet > 80))
						{
									EEpromInit();
						}
				}			
		}
		else
		{
				EEpromInit();
		}
	 
}

/****************************************************************************************************************************************** 
* ��������:	 ReadBingXangState
* ����˵��:  ��ȡ����״̬	 
* ��    ��: ��	
* ��    ��: ��
******************************************************************************************************************************************/
void ReadBingXangState(void )
{
    HeatFlag = gHeatCoolTemp.Bit.heat;
    CoolFlag = gHeatCoolTemp.Bit.cool;
    SysRunFlag = gHeatCoolTemp.Bit.SysRun ;
		sysLock=  gHeatCoolTemp.Bit.Lock;
	  CoolFlag_FromEEprom= gHeatCoolTemp.Bit.cool?1:0;
		//gHeatCoolTemp.Bit.EEpromRun = SysRunFlag;
}

/****************************************************************************************************************************************** 
* ��������:	 BSP_EEPROM_Initialize
* ����˵��:  ��ʼ��EEPROM
* ��    ��: ��	
* ��    ��: ��
******************************************************************************************************************************************/
void BSP_EEPROM_Initialize ( void )
{
    ReadTempEeprom();
    ReadBingXangState();
	
}




/****************************************************************************************************************************************** 
* ��������:	EepromProcess
* ����˵��:	ÿ��100ms���һ�Σ��Ƿ��п���״̬�仯���¶����õı仯
* ��    ��: ��	
* ��    ��: ��
******************************************************************************************************************************************/
void EepromProcess(void)
{
		if(gVCU_VIBModeCfg.Bit.power_supply)
		{
			 	gHeatCoolTemp.Bit.EEpromRun = 0;
				return;
		}	
		
    if(gHeatCoolTemp.Bit.EEpromRun && !MoodeSetFlag && !TempSetFlag)
    {
         gHeatCoolTemp.Bit.EEpromRun = 0;
         WriteTempEeprom();
    }
}
