#include "Display.h"
#include "FuncTab.h"

#define FACTORY_MODE gTempHeat
#define DISPLAY_F_x  0XB0

static u8 sLMD_ConfigCnt = 0xff;//
static uint16_t  TempSetCnt;


void ClearDelayCnt(void)
{
		TempSetCnt = 0U;
		TempSetFlag = 0;
}


void  LightAdjust(void)
{
		static u8 sMode =0 ;
	
		if(sMode == 0)
		{
				if(gLightAdjust == 0xc0)
				{
						gLightAdjust = 0x80;
				}
				
				else if(gLightAdjust == 0x80)
				{
						gLightAdjust = 0x40;
				}
				
				else if(gLightAdjust == 0x40)
				{
						gLightAdjust = 0x00;
				}
				
				else if(gLightAdjust == 0x00)
				{
						gLightAdjust = 0x40;
						sMode = 1;
				}
		}
		else
		{
				if(gLightAdjust == 0x40)
				{
						gLightAdjust = 0x80;
				}
				
				else if(gLightAdjust == 0x80)
				{
						gLightAdjust = 0xc0;
				}
				
				else if(gLightAdjust == 0xc0)
				{
						gLightAdjust = 0x80;
						sMode = 0;
				}
	
		}
		
		
}

void LED_Blink(void )
{
				TempSetCnt++;
				
				if(TempSetCnt > _1S_Per50MS)
				{
            TempSetCnt = 0;
            if(MoodeSetFlag)
							MoodeSetFlag = 0;
						else
							TempSetFlag = 0;	
				}
	
/* 2023.8.18 …¡À∏»°œ˚µÙ¡À */				
//        if(TempSetCnt < _3S_Per50MS)
//        {
//					
//            if(TempSetCnt < _1S_Per50MS/4)
//            {
//                SysRun_DisplayFlag = 1;
//            }
//            else if(TempSetCnt < _1S_Per50MS/2)
//            {
//                SysRun_DisplayFlag = 0;
//            }
//            
//            else if(TempSetCnt < _3S_Per50MS/4)
//            {
//                SysRun_DisplayFlag = 1;
//            }
//            else if(TempSetCnt < _1S_Per50MS)
//            {
//                SysRun_DisplayFlag = 0;
//            }
//            
//            else if(TempSetCnt < _5S_Per50MS/4)
//            {
//                SysRun_DisplayFlag = 1;
//            }
//            else if(TempSetCnt < _3S_Per50MS/2)
//            {
//                SysRun_DisplayFlag = 0;

//            }
//            
//            else if(TempSetCnt < _2S_Per50MS-10)
//            {
//                SysRun_DisplayFlag = 1;
//            }
//            else if(TempSetCnt < _2S_Per50MS)
//            {
//                SysRun_DisplayFlag = 0;
//                TempSetCnt = 0;
//                if(MoodeSetFlag)
//									MoodeSetFlag = 0;
//								else
//									TempSetFlag = 0;	
//            }
//        }
  
}

//void ResetBlinkCnt(void)
//{
//		TempSetCnt = 0;
//}

void DisplayModeSet(void)
{
		TempSetCnt = 0;
		TempSetFlag = 0;
		MoodeSetFlag = 1;
}

void DisplayTempSet(void)
{
		TempSetCnt = 0;
		TempSetFlag = 1;
		MoodeSetFlag = 0;
}

void SetDisplayBoard(u8 type)
{
		static u8 sLMD_ConfigCnt1 =0;
		u8 i;
	
		switch(type)
		{
		
			case SRC_Config:
			{
					if(sLMD_ConfigCnt1 < 6)
					{
							sLMD_ConfigCnt1++;
							gtab[1] = SRC_Config;
							gtab[2] = gstLingMinConfig[sLMD_ConfigCnt1].KeyNum;
							gtab[3] = gstLingMinConfig[sLMD_ConfigCnt1].Value;
							gtab[4] = gTempHeat;
							gtab[5] = 0;
					}
			}
			
			case Display_config:
			{
					sLMD_ConfigCnt1++;
					gtab[1] = Display_config;
					gtab[2] = 13;
					gtab[3] = 0x47;
					gtab[4] = gTempHeat;
					gtab[5] = 0;
			}
			default:
				break;
		
		}
		
		for(i =0; i< 5; i++)
		{
			gtab[5] +=gtab[i];
		}
		LPUART_Putchar(LPUART0, gtab[0]);
		LPUART_SetIntMode(LPUART0, LPUART_INT_TX_COMPLETE, true);
}



//void LMD_Start(void)
//{
//		LinMingDuFlag = 1;
//		sLMD_ConfigCnt =  0;
//}

void  SendDataDiaplay(void)
{
    static char  OldCoolValue = 60;
		static char  OldHeatValue = -10;
		static u8 HisMode = 0;
		static u8 HisTempMode = 0;
    uint8_t i;
    u8      ShuMaGuanValue = 0; 
	
		if(AKFactoryTestFlag)
		{

						gtab[0] = 6;
						gtab[1] = 2;
						gtab[2] = 255;
						gtab[3] = 255;
						gstDisplayCode.dis1 &=0x0f;
						gtab[4] = 0x80|gstDisplayCode.dis1;
						gtab[5] = 0;
						for(i =0; i< 5; i++)
						{
							gtab[5] +=gtab[i];
						}	
						LPUART_Putchar(LPUART0, gtab[0]);
						LPUART_SetIntMode(LPUART0, LPUART_INT_TX_COMPLETE, true);
						
					return;
		}
			
			
					
    
		HEX_DISPLAY = 0;

//		if(  sLMD_ConfigCnt < 1 && !RDFactoryTestFlag)
//		{
//				 sLMD_ConfigCnt++;
//				
//			
//				if(sLMD_ConfigCnt == 1)
//				{
//						LinMingDuFlag = 0;
//						sLMD_ConfigCnt++;
//						gtab[1] = SRC_Config;
//						gtab[2] = 0xff;
//						gtab[3] = LING_MIN_DU;
//						gtab[4] = gTempHeat;
//	
//						gtab[5] = 0;
//						for(i =0; i< 5; i++)
//						{
//							gtab[5] +=gtab[i];
//						}
//						
//						LPUART_Putchar(LPUART0, gtab[0]);
//						LPUART_SetIntMode(LPUART0, LPUART_INT_TX_COMPLETE, true);
//				}
//		}
//		else
		{
				
				if(RDFactoryTestFlag)
				{
						gtab[0] = 6;
						gtab[1] = 3;
						gtab[2] = gstDisplayCode.dis1;
						gtab[3] = gstDisplayCode.dis2;
						gtab[4] = gstDisplayCode.dis3 | (CANRLostFlag<<7);

						
						gtab[5] = 0;
						for(i =0; i< 5; i++)
						{
							gtab[5] +=gtab[i];
						}	
						LPUART_Putchar(LPUART0, gtab[0]);
						LPUART_SetIntMode(LPUART0, LPUART_INT_TX_COMPLETE, true);
						return;
				}
				else
				{
						gSendData[0].all = 0;
						gSendData[1].all = 0; 
						SysRun_DisplayFlag  = SysRunFlag;
				}
    
		
				if(ALLTempSenseErrowFlag)
				{
						gTempHeat = 0xf7;
						ErrowCodeFlag = 1;
				}
				else if(PanelLostFlag )
				{
						gTempHeat = 0xf8;
						ErrowCodeFlag = 1;
				}
				
				else if(YaSuoJiErrowDisplayFlag || (gstTempCompensation.Run.Bit.RunFlag))
				{
					if(gstTempCompensation.Run.Bit.RunFlag)
					{
						if(gstTempCompensation.Run.Bit.DisplayModeFlag)
						{
								FACTORY_MODE = gstTempCompensation.mode|0xe0;
							
								if((FACTORY_MODE&0x000000ff) == (TemprertureTab[TAB_LENGTH].DisplayMode&0x000000ff))
								{
										FACTORY_MODE =TemprertureTab[TAB_LENGTH].CompensationValue|DISPLAY_F_x;
								}	
								
								
								ErrowCodeFlag = 1; 
						}
						else 
						{
							for(i= 0; i<=TAB_LENGTH;i++ ) 
							{
								if(gstTempCompensation.mode  ==  TemprertureTab[i].DisplayMode)
								{
										if(gstTempCompensation.mode == 0xeb)
										{
												if(TemprertureTab[i].CompensationValue >0)
												{
														AiKaiOzneTestFlag = 1;
												}
										}
									
										if(TemprertureTab[i].CompensationValue <= 65 && TemprertureTab[i].CompensationValue >= -10)
										{
												gTempHeat = TemprertureTab[i].CompensationValue ;
												break;
										}
								}					
							}
							if(ParameterRecoverFlag)
							{
									gTempHeat = 0x88;
									HEX_DISPLAY  = 1;
							}
								
							else 
							{
									if((gstTempCompensation.mode == 0xe1)&& (TemprertureTab[0].CompensationValue == -10) )
									{
											gTempHeat = -TemprertureTab[0].CompensationValue ;
											HEX_DISPLAY = 1;
									}
									else
									{
											HEX_DISPLAY = 0; 
									}
							}
							
								
						}
						LED_Blink();	
					}
					else
					{
							gTempHeat = gstYaSuoJiErrow.ErrorCodeDisplayData;
							ErrowCodeFlag = 1; 
							
					}
					
				}
		
				else if(AbnormalPowerFlag)
				{
						gTempHeat = 0xf1;
						ErrowCodeFlag = 1; 
				}
				
				else if(HeatErrowFlag && HeatFlag)
				{
						gTempHeat = 0xf9;
						ErrowCodeFlag = 1; 
				}
				
				else if(RealTimeDisplayFlag)
				{
						gTempHeat = gTempAD;
						HEX_DISPLAY = 0;
						TempSetFlag =0;
						MoodeSetFlag = 0;
				}

				else if(TempSetFlag || MoodeSetFlag)
				{

						if(TempSetFlag)
						{
								
								if(CoolSuDongFlag)
								{
										gTempHeat = 0;//CoolSuDongDisplayFlag =1;
								}
								else if(CoolFlag)
								{
										gTempHeat = gHeatCoolTemp.Bit.CoolTempSet;
								}
								else if(HeatFlag)
								{
										gTempHeat = gHeatCoolTemp.Bit.HeatTempSet;
								}
								HEX_DISPLAY = 0;
									
						}
						
						
						else if(MoodeSetFlag  )
						{

							  if(gstDisplayCode.CurMode == BingXianMode)
								{
										gTempHeat = 0xd1;
								}
								else if(gstDisplayCode.CurMode == LengYinMode)
								{
										gTempHeat = 0xd2;
								}

								else if(gstDisplayCode.CurMode == GuoShuMode)
								{
										gTempHeat = 0xd3;
					
								}
										
								else if(gstDisplayCode.CurMode == WenNaiMode)
								{
										gTempHeat = 161;
	
								}
								else if(gstDisplayCode.CurMode == WenFanMode)
								{
										gTempHeat = 162;			
								}
								HEX_DISPLAY = 1; 	
						}
						
						
						LED_Blink();	
						
				}
				else
				{
								//RealTimeDisplayFlag = 0;
								HEX_DISPLAY = 0; 
								
								if(CoolFlag)
								{               
										gTempHeat = gHeatCoolTemp.Bit.CoolTempSet;
									
										if((COOLTEMPMin-1) == -1)
										{
												if(gTempHeat == (COOLTEMPMin-1))
												{
														gTempHeat = 0;
												}
										}
										else if(gTempHeat == (COOLTEMPMin-1))
										{
												
												{
														gTempHeat = 0xdb;
														HEX_DISPLAY = 1; 	
												}
										}
								}
								else
								{
										gTempHeat = gHeatCoolTemp.Bit.HeatTempSet;
								}
									
								if(gTempHeat == -10 && !CoolSuDongFlag)
								{
										gTempHeat = -gHeatCoolTemp.Bit.CoolTempSet;
										HEX_DISPLAY = 1; 
								}
				}
				if(SysRunFlag)
				{
						LED2_DisplayFlag = 1;//cool
						LED10_DisplayFlag = 1;//minus
						LED11_DisplayFlag = 1;//add
						LED12_DisplayFlag = 1;//heat
						
						if(CoolFlag)
						{
								LED2_DisplayFlag = 0;//cool
								LED9_DisplayFlag = 1;
						}
						if(HeatFlag)
						{
								LED12_DisplayFlag = 0;//heat
								LED13_DisplayFlag = 1;
						}  
						if(sysLock)
						{  
									LED15_DisplayFlag = 0;
									LED16_DisplayFlag = 1;  
						}
						else
						{
								LED15_DisplayFlag = 1;
								LED16_DisplayFlag = 0;
						}
				}
				else
				{
						if(HuoErIO_Flag )
						{
						
						}
				}
    
    
				LED14_DisplayFlag = 1;//push motor
				LED1_DisplayFlag = 1;//power
				DisplayPanelLostFlag = PanelLostFlag;
				
//				if(!RealTimeDisplayFlag)
//				{
//						//CoolSuDongDisplayFlag = CoolSuDongFlag;
//					if(CoolSuDongFlag)
//						gTempHeat = 0;
//				} 
				gtab[0] = 3;
				gtab[1] = 2;
				gtab[2] = gSendData[0].all;
				gtab[3] = gSendData[1].all|gLightAdjust;
				gtab[4] = gTempHeat;
				gtab[5] = 0;
				
				if(1 == gForceOutputFlag.Bit.b0)//force output mode active
				{
					LED1_DisplayFlag	= 0;
					LED2_DisplayFlag	= 0;
					LED9_DisplayFlag	= 0;
					LED10_DisplayFlag	= 0;
					LED11_DisplayFlag	= 0;
					LED12_DisplayFlag = 0;
					LED13_DisplayFlag	= 0;
					LED14_DisplayFlag	= 0;
					LED15_DisplayFlag	= 0;
					LED16_DisplayFlag	= 0;
				}
				
				for(i =0; i< 5; i++)
				{
					gtab[5] +=gtab[i];
				}	
				LPUART_Putchar(LPUART0, gtab[0]);
				LPUART_SetIntMode(LPUART0, LPUART_INT_TX_COMPLETE, true);
		}
	
}

