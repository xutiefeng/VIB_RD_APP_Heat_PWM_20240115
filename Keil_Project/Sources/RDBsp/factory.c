#include "factory.h"
#include	"CanAll.h"
u8  Stab[10];

	/************************************************************************* 
* 函数名称:	FactoryErrowDisplay
* 功能说明:	功能检测失败后，提示方式
* 输    入: 无	
* 输    出: 无
*************************************************************************/
void FactoryErrowDisplay(u8 v)
{
		static u8 sledCnt =0;
		if(v == 0)
		{
				Led_RED4_(LED_OFF);
				Led_RED5_(LED_OFF);
				Led_RED6_(LED_OFF);
				Led_RED7_(LED_OFF);
		}
	 	else if(v == 1)
		{
				Led_RED4_(LED_OFF);
				Led_RED5_(LED_OFF);
				Led_RED6_(LED_ON);
				Led_RED7_(LED_OFF);			
		}
		
		else if(v == 2)
		{
				Led_RED4_(LED_OFF);
				Led_RED5_(LED_OFF);
				Led_RED6_(LED_OFF);
				Led_RED7_(LED_ON);
		}
		
		else if(v == 3)
		{
			if(sledCnt < 5)
			{
					Led_RED4_(LED_OFF);
					Led_RED5_(LED_OFF);
					Led_RED6_(LED_ON);
					Led_RED7_(LED_OFF);
			}
			else
			{
					Led_RED4_(LED_OFF);
					Led_RED5_(LED_OFF);
					Led_RED6_(LED_OFF);
					Led_RED7_(LED_OFF);
					sledCnt = 0;
			}
				
		}
		
		else if(v == 4)
		{
				if(sledCnt < 5)
				{
						Led_RED4_(LED_OFF);
						Led_RED5_(LED_OFF);
						Led_RED6_(LED_OFF);
						Led_RED7_(LED_ON);
				}
				else
				{
						Led_RED4_(LED_OFF);
						Led_RED5_(LED_OFF);
						Led_RED6_(LED_OFF);
						Led_RED7_(LED_OFF);
						sledCnt = 0;
				}
		}
		
		else if(v == 255)
		{
				Led_RED4_(LED_ON);
				Led_RED5_(LED_ON);
				Led_RED6_(LED_ON);
				Led_RED7_(LED_ON);
		}
	}

	/************************************************************************* 
* 函数名称:	FactoryEerow
* 功能说明:	功能通过后，选择蜂鸣器提示音
* 输    入: 无	
* 输    出: 无
*************************************************************************/
	void FactoryEerow(u8 v)
{
	if(v == 1)
	{
			RDFactoryTestFlag = 0;
			BuzzerPowerOffFlag = 1;
	}
	else if(v == 2)
	{
			RDFactoryTestFlag = 0;
			BuzzerPowerOffFlag = 1;
	}
	
	else if(v == 3)
	{
			RDFactoryTestFlag = 0;
			BuzzerPowerOffFlag = 1;
	}	
	
	else if(v == 4)
	{
			RDFactoryTestFlag = 0;
			BuzzerPowerOffFlag = 1;
	}
	
	else if(v == 5)
	{
			FactoryErrowDisplay(gstFactory.step);
			RDFactoryTestFlag = 0;
	}
}
#if 1
#define VER_TEST 2

void 	FactoryProcess(void)
{
//	if(TestPointTringer_1 == 0 && TestPointTringer_2 == 0)
//	{
//			RDFactoryTestFlag = 1;

//	}
		static  u8 sFacFlag = 0;
		gstDisplayCode.dis3 = 8;
	  if(RDFactoryTestFlag || AKFactoryTestFlag)
		{
			switch(gstFactory.step)		
			{
				case 0:		

						gstFactory.FactoryCnt = 0;
						if(sFacFlag)
						{
								sFacFlag = 1;
								gstDisplayCode.dis1= VER_TEST;
								gstDisplayCode.dis2 = 0;
						}
						
						
				
						if(GetActiveSignal_YAJ == 0 )//ya suo ji
						{
								gstDisplayCode.dis1 = 0x01;
								gstDisplayCode.dis2 = 0x0e;	
								gstDisplayCode.dis3 = 0; 
						}
						//else if(AKFactoryTestFlag)
						//{
								else if(( ADtable[ADntc1]  < ADMIN || ADtable[ADntc1]  > ADMAX) && AKFactoryTestFlag)//temperture 1
								{
										gstDisplayCode.dis1 = 0x02;
										gstDisplayCode.dis2 = 0x0e;	
										gstDisplayCode.dis3 = 0;
										
								}
								else if(( ADtable[ADntc2]  < ADMIN || ADtable[ADntc2]  > ADMAX) && AKFactoryTestFlag)//temperture 2
								{
										gstDisplayCode.dis1 = 0x02;
										gstDisplayCode.dis2 = 0x0e;			
										gstDisplayCode.dis3 = 0;	
								}
						//}
						
						
					  else if( !AKFactoryTestFlag && ( ADtable[ADntc1]  < 300 || ADtable[ADntc1]  > 700))//temperture 1
						{
								gstDisplayCode.dis1 = 0x02;
								gstDisplayCode.dis2 = 0x0e;	
								gstDisplayCode.dis3 = 0;
						}
						
						else if(!AKFactoryTestFlag && (ADtable[ADntc2]  < 300 || ADtable[ADntc2]  > 700))//temperture 2
						{
								gstDisplayCode.dis1 = 0x02;
								gstDisplayCode.dis2 = 0x0e;			
								gstDisplayCode.dis3 = 0;	
						}
						else if(PanelLostFlag)//uart
						{
								gstDisplayCode.dis1 = 0x03;
								gstDisplayCode.dis2 = 0x0e;
								gstDisplayCode.dis3 = 0;
						}								
						else
						{
								gstFactory.step++;
								gstDisplayCode.dis1= VER_TEST;
								gstDisplayCode.dis2 = 0;
						}
						SysRest();			
						RDFactoryTestFlag =1;	
				break;
				
			  case 1:	
						OpenHeat;
						HeatFlag = 1;
						gstFactory.FactoryCnt++;				
						if(gstFactory.FactoryCnt >  _500MS_Per100MS) 
						{
								HeatFlag = 0;
								Buzzer5Flag =1;
								Stab[gstFactory.step-1] = gstADCollect.HeatCurent;

								if(gstADCollect.HeatCurent >1 && gstADCollect.HeatCurent < 6 )
								{
										gstFactory.step++;	
										gstDisplayCode.dis1= VER_TEST;
										gstDisplayCode.dis2 = 0;
								}
								else
								{
										gstDisplayCode.dis1= 0x04;
										gstDisplayCode.dis2 = 0x0e;
										gstDisplayCode.dis3 = 0;
								}
							  CloseHeat;
								gstFactory.FactoryCnt = 0;
						}					
				break;
						
			 case 2:	
						OpenAuxHeat;
						HeatFlag = 1;
						gstFactory.FactoryCnt++;				
						if(gstFactory.FactoryCnt >  _500MS_Per100MS) 
						{
								HeatFlag = 0;
								Buzzer5Flag =1;
								Stab[gstFactory.step-1] = gstADCollect.HeatCurent;
							
							  if(AKFactoryTestFlag)
								{
										if(gstADCollect.HeatCurent > 0.1 && gstADCollect.HeatCurent < 2.4 )
										{
												gstFactory.step++;	
												gstDisplayCode.dis1= VER_TEST;
												gstDisplayCode.dis2 = 0;									
										}
								}
								else if(gstADCollect.HeatCurent >1 && gstADCollect.HeatCurent < 2 )
								{
										gstFactory.step++;										
								}
								else
								{
										gstDisplayCode.dis1= 0x05;
										gstDisplayCode.dis2 = 0x0e;
										//gstDisplayCode.dis3 =0;
								}
								CloseAuxHeat;
								gstFactory.FactoryCnt = 0;
								
							
						}					
				break;
				
				case 3:
					CoolFlag = 1;
					HeatFlag = 0;
					OpenYaSuoJi;
					//gstDisplayCode.dis1= VER_TEST;
					//gstDisplayCode.dis2 = 0;
					gstFactory.FactoryCnt++;
					Stab[gstFactory.step-1] = gstADCollect.CoolCurent;
				
					if(gstFactory.FactoryCnt > _1S_Per100MS)
					{							
							gstFactory.FactoryCnt = 0;
							if(AKFactoryTestFlag)
							{
										//if(gstADCollect.CoolCurent >= 1 && gstADCollect.CoolCurent <= 5)
											gstFactory.step++;	
											gstDisplayCode.dis1= VER_TEST;
										  gstDisplayCode.dis2 = 0;
							}
							else
							{
									if((GetActiveSignal_YAJ == 0))
									{									
											gstFactory.step++;
											CoolFlag = 0;
									}
									else
									{
											//RDFactoryTestFlag = 0;
											gstDisplayCode.dis1 = 0x01;
											gstDisplayCode.dis2 = 0x0e;	
									}
							}
					 	
							
							
							Buzzer5Flag =1;
					}
				break;
					
				case 4:
					gstFactory.FactoryCnt++;
					OpenOzne_IO;
					Stab[gstFactory.step-1] = gstADCollect.OzneCurent;
					if(gstFactory.FactoryCnt > _500MS_Per100MS)
					{
							gstFactory.FactoryCnt = 0;							
							if((gstADCollect.OzneCurent >= 5 && gstADCollect.OzneCurent <= 40)&& (AKFactoryTestFlag ))
							{
											
										gstFactory.step++;
										gstDisplayCode.dis1= VER_TEST;
										gstDisplayCode.dis2 = 0;
							}
						
						
							else if(!AKFactoryTestFlag && (gstADCollect.OzneCurent >= 10 && gstADCollect.OzneCurent <= 400))
							{									
									gstFactory.step++;
									gstDisplayCode.dis1= VER_TEST;
									gstDisplayCode.dis2 = 0;
									ChouTiMotor_set;
								  ChouTiCurentFlag  = 1;
							}
							else
							{
									gstDisplayCode.dis1 = 0x07;
									gstDisplayCode.dis2 = 0x0e;	
							}
							
							Buzzer5Flag =1;
					}
					
				break;
						
				
				case 5:
						
						ChouTiFlag = 1;
						ChouTiMotor_set;
						Stab[gstFactory.step-1] = gstADCollect.ChouTiCurent;
						gstFactory.FactoryCnt++;
						if(gstFactory.FactoryCnt > _500MS_Per100MS)
						{			
								
								if(gstADCollect.ChouTiCurent > 1 && gstADCollect.ChouTiCurent <  7)
								{ 										
										gstFactory.step++;
										gstDisplayCode.dis1= VER_TEST;
										gstDisplayCode.dis2 = 0;
										
										ChouTiMotor_clr;
										ChouTiFlag = 0;
										gstFactory.FactoryCnt = 0;
										Buzzer5Flag =1;
								}
								else
								{
										gstDisplayCode.dis1 = 0x08;
										gstDisplayCode.dis2 = 0x0e;	
								}
						}	
						
				break;
				
				case 6:
					gstFactory.FactoryCnt++;
				  LED_ForceOutput(1);//LED1
//					gstDisplayCode.dis1= VER_TEST;
//					gstDisplayCode.dis2 = 0;
					if(gstFactory.FactoryCnt > _500MS_Per100MS)
					{
							gstFactory.FactoryCnt = 0;
							if(gstADCollect.LEDCurent > 10 && gstADCollect.LEDCurent < 200)
							{
									gstFactory.step++;
									gstDisplayCode.dis1= VER_TEST;
								  gstDisplayCode.dis2 = 0;
							}
							else
							{
									//RDFactoryTestFlag = 0;
									gstDisplayCode.dis1 = 0x09;
								  gstDisplayCode.dis2 = 0x0e;	
							}
					}
				
				break;
				
				case 7:
					gstFactory.FactoryCnt++;
					LED_ForceOutput(2);//LED2
					if(gstFactory.FactoryCnt > _500MS_Per100MS)
					{
							gstFactory.FactoryCnt = 0;
							if(gstADCollect.LEDCurent > 10 && gstADCollect.LEDCurent < 200)
							{
									gstFactory.step++;
									Buzzer5Flag =1;
									if(!CANTestFlag)
										FLEXCAN_TxData(CAN0, 0, 0x093, gtab, 8);
									
							}
							else
							{
									gstDisplayCode.dis1 = 10;
								  gstDisplayCode.dis2 = 0x0e;	
							}
					}
				break;
					
				case 8:
//						gstDisplayCode.dis1= VER_TEST;
//						gstDisplayCode.dis2 = 0;
				    gstFactory.FactoryCnt++;
						if(AKFactoryTestFlag)
						{
							if(gstFactory.FactoryCnt > _1S_Per100MS)
							{
									gstFactory.FactoryCnt = 0;
								
									if(gstADCollect.CoolCurent >= 1 && gstADCollect.CoolCurent <= 5)
									{	
											//CloseOzne_IO;
											//CoolFlag = 0;
											DayAndNightFlag = 1;
											gstFactory.step++;
											Buzzer5Flag =1;	
									}
									
							}
							
						}
						else
						{
								if(CANTestFlag)
								{
										gstFactory.step++;
										gstDisplayCode.dis1= 0;
										gstDisplayCode.dis2 = 0;
										gstDisplayCode.dis3 = 14;
								}
								else
								{
										gstDisplayCode.dis1= 11;
										gstDisplayCode.dis2 = 0x0e;
										gstDisplayCode.dis3 =0;
										CANRLostFlag = 1;
								}
						}
						
				break;
						
				case 9:
				{
					gstDisplayCode.dis1= VER_TEST;
					gstDisplayCode.dis2 = 0;
					
					//OpenYaSuoJi;
					gstFactory.FactoryCnt++;
					Stab[gstFactory.step-1] = gstADCollect.CoolCurent;
				
					if(gstFactory.FactoryCnt > _1S_Per100MS)
					{							
							gstFactory.FactoryCnt = 0;
						
							if(AKFactoryTestFlag)
							{
									if(gstADCollect.CoolCurent >= 1 && gstADCollect.CoolCurent <= 5)
									{	
											CloseOzne_IO;
											CoolFlag = 0;
											gstFactory.step++;		
									}
							}
							else
							{
									if((GetActiveSignal_YAJ == 0))
									{									
											gstFactory.step++;		
											
									}
									else
									{
											//RDFactoryTestFlag = 0;
										
											gstDisplayCode.dis1 = 0x06;
											gstDisplayCode.dis2 = 0x0e;	
									}
							}
						
					 		
							CloseYaSuoJi;
							CoolFlag = 0;
							
							Buzzer5Flag =1;
					}
				}
					
				break;
				
				case 10:
						gstDisplayCode.dis1= 8;
						gstDisplayCode.dis2 = 8;
						gstDisplayCode.dis3 = 14;
						AKFinishTestFlag = 1;
				break;

					
				default:
					break;
					
			}

		}
}
#else

void 	FactoryProcess(void)
{
//	if(TestPointTringer_1 == 0 && TestPointTringer_2 == 0)
//	{
//			RDFactoryTestFlag = 1;

//	}
		gstDisplayCode.dis3 = 8;
	  if(RDFactoryTestFlag)
		{
			switch(gstFactory.step)		
			{
				case 0:		

						gstFactory.FactoryCnt = 0;
				
						gstDisplayCode.dis1= 1;
						gstDisplayCode.dis2 = 0;
						
				
						if(GetActiveSignal_YAJ == 0 )//ya suo ji
						{
							  //FactoryEerow(1);
								gstDisplayCode.dis1 = 0x01;
								gstDisplayCode.dis2 = 0;	
								gstDisplayCode.dis3 = 13;
								 
						}
						
					  else if( ADtable[ADntc1]  < 300 || ADtable[ADntc1]  > 700)//temperture 1
						{
								gstDisplayCode.dis1 = 0x02;
								gstDisplayCode.dis2 = 0;	
								gstDisplayCode.dis3 = 13;
								
						}
						
						else if( ADtable[ADntc2]  < 300 || ADtable[ADntc2]  > 700)//temperture 2
						{
								gstDisplayCode.dis1 = 0x02;
								gstDisplayCode.dis2 = 0;			
								gstDisplayCode.dis3 = 13;
								
						}
										

						else if(PanelLostFlag)//uart
						{
								//FactoryEerow(4);
								gstDisplayCode.dis1 = 0x03;
								gstDisplayCode.dis2 = 0;
								gstDisplayCode.dis3 = 0x0e;
						}								
						
						else
							gstFactory.step++;
						
						SysRest();			
						RDFactoryTestFlag =1;	
				break;
				
			  case 1:	
						OpenHeat;
						HeatFlag = 1;
						gstFactory.FactoryCnt++;				
						if(gstFactory.FactoryCnt >  _500MS_Per100MS) 
						{
								HeatFlag = 0;
								Buzzer5Flag =1;
								Stab[gstFactory.step-1] = gstADCollect.HeatCurent;
							
							
								if(gstADCollect.HeatCurent >1 && gstADCollect.HeatCurent < 5 )
								{
										gstFactory.step++;										
								}
								else
								{
										gstDisplayCode.dis1= 0x04;
										gstDisplayCode.dis2 = 0;
										gstDisplayCode.dis3 = 0x0e;
								}
							  CloseHeat;
								gstFactory.FactoryCnt = 0;
								
								//gstFactory.step++;gstFactory.step = 2;// 跳过加热
					
						}					
				break;
						
			 case 2:	
						OpenAuxHeat;
						HeatFlag = 1;
						gstFactory.FactoryCnt++;				
						if(gstFactory.FactoryCnt >  _500MS_Per100MS) 
						{
								HeatFlag = 0;
								Buzzer5Flag =1;
								Stab[gstFactory.step-1] = gstADCollect.HeatCurent;
							
							
								if(gstADCollect.HeatCurent >1 && gstADCollect.HeatCurent < 2 )
								{
										gstFactory.step++;										
								}
								else
								{
										gstDisplayCode.dis1= 0x05;
										gstDisplayCode.dis2 = 0x0e;
										gstDisplayCode.dis3 =0;
										//gstFactory.step = 10;
										gstDisplayCode.dis1 = 0x05;
								    gstDisplayCode.dis2 = 0x0e;	
								}
								CloseAuxHeat;
								gstFactory.FactoryCnt = 0;
								
							
						}					
				break;
				
				case 3:
					CoolFlag = 1;
					OpenYaSuoJi;
					gstFactory.FactoryCnt++;
					Stab[gstFactory.step-1] = gstADCollect.CoolCurent;
				
					if(gstFactory.FactoryCnt > _1S_Per100MS)
					{							
							gstFactory.FactoryCnt = 0;
						
					 		if((GetActiveSignal_YAJ == 0))
							{									
									gstFactory.step++;		
							}
							else
							{
									RDFactoryTestFlag = 0;
									gstDisplayCode.dis1 = 0x01;
								  gstDisplayCode.dis2 = 0x0e;	
							}
							CloseYaSuoJi;
							CoolFlag = 0;
							
							Buzzer5Flag =1;
					}
				break;
					
				case 4:
					gstFactory.FactoryCnt++;
					OpenOzne_IO;
					Stab[gstFactory.step-1] = gstADCollect.OzneCurent;
					if(gstFactory.FactoryCnt > _2S_Per100MS)
					{
							gstFactory.FactoryCnt = 0;
							if((gstADCollect.OzneCurent >100 || gstADCollect.OzneCurent < 400)&& (GetActiveSignal_YAJ ))
							{
									
									gstFactory.step++;
									ChouTiMotor_set;
							}
							else
							{
									RDFactoryTestFlag = 0;
									gstDisplayCode.dis1 = 0x07;
									gstDisplayCode.dis2 = 0x0e;	
							}
							CloseOzne_IO;
							Buzzer5Flag =1;
					}
					
				break;
						
				
				case 5:
						gstFactory.FactoryCnt++;
						ChouTiFlag = 1;
						ChouTiMotor_set;
						Stab[gstFactory.step-1] = gstADCollect.ChouTiCurent;
						if(gstFactory.FactoryCnt > _500MS_Per100MS)
						{
								gstFactory.FactoryCnt = 0;
						
								if(gstADCollect.ChouTiCurent >1 && gstADCollect.ChouTiCurent <5)
								{ 
										
										gstFactory.step++;
								}
								else
								{
										RDFactoryTestFlag = 0;
										gstDisplayCode.dis1 = 0x08;
										gstDisplayCode.dis2 = 0x0e;	
								}
								ChouTiMotor_clr;
								ChouTiFlag = 0;
								Buzzer5Flag =1;
						}	
				break;
				
				case 6:
					gstFactory.FactoryCnt++;
				  LED_ForceOutput(1);//LED1
					if(gstFactory.FactoryCnt > _500MS_Per100MS)
					{
							gstFactory.FactoryCnt = 0;
							if(gstADCollect.LEDCurent > 10)
							{
									gstFactory.step++;
									FLEXCAN_TxData(CAN0, 0, 0x093, gtab, 8);
							}
							else
							{
									RDFactoryTestFlag = 0;
									gstDisplayCode.dis1 = 0x09;
								  gstDisplayCode.dis2 = 0x0e;	
							}
					}
				
				break;
				
				case 7:
					gstFactory.FactoryCnt++;
					LED_ForceOutput(2);//LED2
					if(gstFactory.FactoryCnt > _500MS_Per100MS)
					{
							gstFactory.FactoryCnt = 0;
							if(gstADCollect.LEDCurent > 10)
							{
									gstFactory.step++;
									Buzzer5Flag =1;
									if(!CANTestFlag)
										FLEXCAN_TxData(CAN0, 0, 0x093, gtab, 8);
									
							}
							else
							{
									RDFactoryTestFlag = 0;
									gstDisplayCode.dis1 = 10;
								  gstDisplayCode.dis2 = 0x0e;	
							}
					}
				break;
					
				case 8:
						if(CANTestFlag)
						{
								gstFactory.step++;
								gstDisplayCode.dis1= 0;
								gstDisplayCode.dis2 = 0;
								gstDisplayCode.dis3 = 14;
						}
						else
						{
								gstDisplayCode.dis1= 11;
								gstDisplayCode.dis2 = 0x0e;
								gstDisplayCode.dis3 =0;
								CANRLostFlag = 1;
						}
				break;
				
				case 9:
						gstDisplayCode.dis1= 8;
						gstDisplayCode.dis2 = 8;
						gstDisplayCode.dis3 = 14;
				break;

					
				default:
					break;
					
			}

		}
}
#endif