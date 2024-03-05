#include "TELMessage.h"
#include "UpdataCanMessage.h"
#include "Display.h"


typedef enum
{
	TEL_PowerOff  = 0,
	TEL_HeatMode ,
	TEL_CoolMode,
	TEL_LoMode ,
	
}TEL_WorkModeSet;







void TELProcess(void)
{
		u8 tempTab[8],i;
		u8 *p = (u8*)&gstTELMessage;
	
	
	
		if(__RTE_RcvTELMsgSt(tempTab))
		{
				__RTE_ClrRcvTELMsgSt();
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
									
				if(gstTELMessage.len >= 16)
				{
			
						gstTELMessage.len = 0;	
					
						if(gstTELMessage.Set.Bit.VIB_WorkModeSet_VD)
						{

							if(gstTELMessage.Set.Bit.VIB_WorkModeSet == TEL_PowerOff)//
							{
									SysRunFlag = 1 ;
									KeyPower();
							}
							
							else if(gstTELMessage.Set.Bit.VIB_WorkModeSet == TEL_HeatMode)//
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
									 
							else if(gstTELMessage.Set.Bit.VIB_WorkModeSet == TEL_CoolMode)//
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
					}
						
					if(gstTELMessage.Set.Bit.TEL_VIB_TempSetReq_VD)
					{
						if(CoolFlag)
						{
							    if(gstTELMessage.TEL_VIB_TempSetReq >= 0x27 && gstTELMessage.TEL_VIB_TempSetReq <= 0x37)
									{
												if(gHeatCoolTemp.Bit.CoolTempSet  !=  (gstTELMessage.TEL_VIB_TempSetReq-40) )
												{	
														gHeatCoolTemp.Bit.CoolTempSet =  gstTELMessage.TEL_VIB_TempSetReq-40;
														EEPROM_REDY
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
							
						}
						else if(HeatFlag)
						{
								if(gstTELMessage.TEL_VIB_TempSetReq >=0x4e && gstTELMessage.TEL_VIB_TempSetReq <= 0x5f)
									{
												if(gHeatCoolTemp.Bit.HeatTempSet  !=  (gstTELMessage.TEL_VIB_TempSetReq-40) )
												{
														EEPROM_REDY
														gHeatCoolTemp.Bit.HeatTempSet =  gstTELMessage.TEL_VIB_TempSetReq-40;
												}
											
												if(gHeatCoolTemp.Bit.HeatTempSet == 45)
												{
														gstDisplayCode.CurMode = WenNaiMode;
														MoodeSetFlag = 1;
														VoiceSetFlag = 1;
												}
												
												else if(gHeatCoolTemp.Bit.HeatTempSet == 55)
												{
														gstDisplayCode.CurMode = WenFanMode;
														MoodeSetFlag = 1;
														VoiceSetFlag = 1;
												}
									}
									BuzzerPowerOnFlag  =1;
						}
					}
								
								
								for(i=0;i<8; i++)
								{
										tempTab[i] = 0;
								}

									Updata_TCL_TEL_CanMessage(tempTab,TEL);
								__RTE_SendAppMsg(tempTab);
								
						}
						else
						{
								for(i=0;i<8; i++)
								{
										p[gstTELMessage.len++] = tempTab[i];
								}	
						}
						gstTELMessage.lost = 0;
							
		}
		else
		{
			gstTELMessage.lost++;		
			if(gstTELMessage.lost > _150MS_Per5MS)
					gstTELMessage.len = 0;
		}
}
