
#include "CDCMessage.h"
#include "UpdataCanMessage.h"
#include "config.h"
#include "Display.h"

#define CAN_TONG_SUO_MASK 0X80

typedef enum
{
	ChildLock_0n =  1,
	ChildLock_0ff = 2,
}CDC_ChildLock;

typedef enum
{
	CDC_CoolMode = 1,
	CDC_HeatMode ,
	CDC_PowerOff,
	CDC_PowerON ,
	
}CDC_WorkModeSet;


void CDCProcess(void)
{
		u8 tempTab[8],i;
		u8 *p = (u8*)&gstCDCMessage;
	
		if(__RTE_RcvCDCMsgSt(tempTab))
		{
				__RTE_ClrRcvCDCMsgSt();
				ClearDelayCnt();
				if(RDFactoryTestFlag)
				{
						CANTestFlag = 1;
						return;
				}		
				if(gVCU_VIBModeCfg.Bit.power_supply)
				{
						return;
				}						
				if(gstCDCMessage.len >= 16)
				{		
						gstCDCMessage.len = 0;

						if(gstCDCMessage.cdc.Bit.VIB_ChildLockSt == ChildLock_0n)//1
						{
								BuzzerPowerOnFlag  =1;
								sysLock = 1 ;
								gHeatCoolTemp.Bit.Lock = sysLock;
								EEPROM_REDY;
						}

						else if(gstCDCMessage.cdc.Bit.VIB_ChildLockSt == ChildLock_0ff)//2
						{
								BuzzerPowerOnFlag  =1;
								sysLock = 0;
								gHeatCoolTemp.Bit.Lock = 0;
								EEPROM_REDY;
						}
						
					
						if(!gstCDCMessage.cdc.Bit.VIB_dooropenReq )//1
						{
								BuzzerPowerOnFlag  =1;
								ChouTiFlag = 1;
						}
						
						if(gstCDCMessage.cdc.Bit.VIB_WorkModeSet == CDC_PowerOff)//3
						{
							if(SysRunFlag)
							{
//									SysRunFlag = 1 ;
									KeyPower();
							}
								
						}
						
						else if(gstCDCMessage.cdc.Bit.VIB_WorkModeSet == CDC_PowerON)//4
						{
							if(!SysRunFlag)
							{
//									SysRunFlag = 0 ;
									KeyPower();
							}
								
						}
						
					  else if(gstCDCMessage.cdc.Bit.VIB_WorkModeSet  == CDC_HeatMode)//2
						{
								SysRunFlag = 1;
								CoolSuDongFlag = 0;
									
								if(!HeatFlag)
								{
										CoolFlag  = 0 ;
										HeatFlag = 	1;
										gHeatCoolTemp.Bit.heat = HeatFlag;
										gHeatCoolTemp.Bit.cool = CoolFlag;
										gHeatCoolTemp.Bit.SysRun = SysRunFlag;
										EEPROM_REDY;
								}	
								BuzzerPowerOnFlag  =1;
						}
								 
						else if(gstCDCMessage.cdc.Bit.VIB_WorkModeSet  == CDC_CoolMode)//1
						{
								SysRunFlag = 1;	
								CoolSuDongFlag =0;
								if(!CoolFlag)
								{
										CoolFlag  = 1 ;
										HeatFlag = 	0;
										gHeatCoolTemp.Bit.heat = HeatFlag;
										gHeatCoolTemp.Bit.cool = CoolFlag;
										gHeatCoolTemp.Bit.SysRun = SysRunFlag;
										EEPROM_REDY;
								}		
								
								BuzzerPowerOnFlag  =1;
						}

						
						if(gstCDCMessage.VIB_SetTemp >=0x4e && gstCDCMessage.VIB_SetTemp <= 0x5f)
						{

							if(gHeatCoolTemp.Bit.HeatTempSet  !=  (gstCDCMessage.VIB_SetTemp -40) )
							{
								EEPROM_REDY;
							}
							gHeatCoolTemp.Bit.HeatTempSet =  gstCDCMessage.VIB_SetTemp -40;
							if(!HeatFlag)
							{
									CoolFlag  = 0 ;
									HeatFlag = 	1;
									gHeatCoolTemp.Bit.heat = HeatFlag;
									gHeatCoolTemp.Bit.cool = CoolFlag;
									EEPROM_REDY;
							}	
									
							if(gHeatCoolTemp.Bit.HeatTempSet == 45)
							{
									gstDisplayCode.CurMode = WenNaiMode;
									MoodeSetFlag = 1;
									VoiceSetFlag = 1;//
							}
										
							else if(gHeatCoolTemp.Bit.HeatTempSet == 55)
							{
									gstDisplayCode.CurMode = WenFanMode;
									MoodeSetFlag = 1;
									VoiceSetFlag = 1;
							}
							BuzzerPowerOnFlag  =1;
						}
					

						if(gstCDCMessage.VIB_SetTemp >= 27 && gstCDCMessage.VIB_SetTemp <= 0x37)
						{

							if(gHeatCoolTemp.Bit.CoolTempSet  !=  (gstCDCMessage.VIB_SetTemp-40) )
							{
								EEPROM_REDY													
							}
							gHeatCoolTemp.Bit.CoolTempSet =  gstCDCMessage.VIB_SetTemp-40;
											
							if(!CoolFlag)
							{
								CoolFlag  = 1 ;
								HeatFlag = 	0;
								gHeatCoolTemp.Bit.heat = HeatFlag;
								gHeatCoolTemp.Bit.cool = CoolFlag;
								EEPROM_REDY;
							}

							if(gHeatCoolTemp.Bit.CoolTempSet == -1)
							{
								CoolSuDongFlag = 1;
								gstDisplayCode.CurMode = BingXianMode;
								MoodeSetFlag = 1;
								VoiceSetFlag = 1;
							}
											
							else if(gHeatCoolTemp.Bit.CoolTempSet == 4)
							{
								gstDisplayCode.CurMode = LengYinMode;
								MoodeSetFlag = 1;
								VoiceSetFlag = 1;
							}
											
							else if(gHeatCoolTemp.Bit.CoolTempSet == 9)
							{
								gstDisplayCode.CurMode = GuoShuMode;
								MoodeSetFlag = 1;
								VoiceSetFlag = 1;
							}
											
							BuzzerPowerOnFlag  =1;
						}

						for(i=0;i<8; i++)
						{
									tempTab[i] = 0;
						}
						Updata_TCL_TEL_CanMessage(tempTab,CDC);
						__RTE_SendAppMsg(tempTab);
								
						}
						else
						{
								for(i=0;i<8; i++)
								{
										p[gstCDCMessage.len++] = tempTab[i];
								}	
						}
						gstCDCMessage.lost = 0;
							
		}
		else
		{
			gstCDCMessage.lost++;		
			if(gstCDCMessage.lost > _150MS_Per5MS)
					gstCDCMessage.len = 0;
		}
}