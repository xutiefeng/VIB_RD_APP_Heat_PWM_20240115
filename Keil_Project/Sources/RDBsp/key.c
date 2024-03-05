#include	"key.h"
#include "bsp_eeprom.h"
#include "FuncTab.h"
#include "includeall.h"
#include "Display.h"
#include "includeall.h"

//define AD_START   ADC0_Enable()
//#define AD_DISABLE ADC0_Disable()
/****************************************************************************************************************************************** 
* 函数名称:	SysRest
* 功能说明:	系统复位
* 输    入: 无	
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
 void  SysRest(void)
{
	gbFlagData[0].all = 0;
	gbFlagData[1].all = 0;
	gbFlagData[2].all = 0;
	gbFlagData[3].all = 0;
	gbFlagData[4].all = 0;	
	gbFlagData[5].all = 0;
}

/****************************************************************************************************************************************** 
* 函数名称:	KeyPower
* 功能说明:	电源开关键
* 输    入: 无	
* 输    出: 无
* 注意事项: 短按有效
******************************************************************************************************************************************/
void KeyPower(void)
{	
	
	if(!SysRunFlag)
	{	
				SysRunFlag = 1;
        ReadTempEeprom();
        CoolFlag  = gHeatCoolTemp.Bit.cool ;
        HeatFlag = gHeatCoolTemp.Bit.heat ;
        TempSetFlag = 0;
        BuzzerPowerOnFlag  =1;
	}
	else
	{
        SysRest();
        BuzzerPowerOffFlag  =1;
	}
  if(SysRunFlag != gHeatCoolTemp.Bit.SysRun)
  {
     gHeatCoolTemp.Bit.SysRun = SysRunFlag;
     gHeatCoolTemp.Bit.EEpromRun = 1;
  }
}



/****************************************************************************** 
* 函数名称:	KeyHeat
* 功能说明:	制热功能开关键
* 输    入: 无	
* 输    出: 无
* 注意事项: 短按有效
******************************************************************************/
void KeyHeat(void)
{
    if(!SysRunFlag)
    {
        return;
    }
 
		//gstDisplayCode.CurMode++;
			
		if(gstDisplayCode.CurMode == WenNaiMode)
	  {
				gstDisplayCode.CurMode = WenFanMode;
				gHeatCoolTemp.Bit.HeatTempSet  = 55;
		}
		else if(gstDisplayCode.CurMode == WenFanMode)
		{
				gstDisplayCode.CurMode = WenNaiMode;
				gHeatCoolTemp.Bit.HeatTempSet  = 45;
		}

		else
		{
				gstDisplayCode.CurMode = WenNaiMode;
				gHeatCoolTemp.Bit.HeatTempSet  = 45;
		}
		
    HeatFlag = 1;
    CoolFlag = 0;
    DisplayModeSet();//MoodeSetFlag = 1;
    CoolSuDongFlag = 0;//Buzzer5Flag =1; 
		VoiceSetFlag = 1;
		
    //if(gHeatCoolTemp.Bit.heat != HeatFlag)
    {
        gHeatCoolTemp.Bit.EEpromRun = 1;
        gHeatCoolTemp.Bit.heat = HeatFlag;
        gHeatCoolTemp.Bit.cool = CoolFlag;     
    }
}

/****************************************************************************** 
* 函数名称:	KeyCooL
* 功能说明:	制冷功能开关键
* 输    入: 无	
* 输    出: 无
* 注意事项: 短按有效，长按每隔
******************************************************************************/
void KeyCooL(void)
{
		u8 i;
    if(!SysRunFlag)
    {
        return;
    }

		
				
		if(gstTempCompensation.Run.Bit.RunFlag)
		{
				for(i = 0; i<=TAB_LENGTH;i++ )
				{
						if(TemprertureTab[i].DisplayMode >0XEC || TemprertureTab[i].DisplayMode < 0XE0)
						{
								memcpy((void *)TemprertureTab,(void *)ImageTemprertureTab,TAB_SIZE);
						}
				}
				
				gstTempCompensation.Run.Bit.DisplayValueFlag = 0;//
				gstTempCompensation.Run.Bit.DisplayModeFlag = 1;
				gstTempCompensation.RecoverTimer = 0;
				
				if(gstTempCompensation.mode < ImageTemprertureTab[TAB_LENGTH].DisplayMode)
				{
						gstTempCompensation.mode++;
				}
				else
				{
						gstTempCompensation.mode = ImageTemprertureTab[0].DisplayMode;
				}
				MinusKeyFlag = 0 ;//ClearDelayCnt();

		}
		else
		{
				HeatFlag = 0;
				CoolFlag = 1;
				DisplayModeSet();//MoodeSetFlag = 1;
				VoiceSetFlag = 1;
			
				if(gstDisplayCode.CurMode == BingXianMode)
				{
						gstDisplayCode.CurMode = LengYinMode;
						gHeatCoolTemp.Bit.CoolTempSet  = 4;
				}
				else if(gstDisplayCode.CurMode == LengYinMode)
				{
						gstDisplayCode.CurMode = GuoShuMode;
						gHeatCoolTemp.Bit.CoolTempSet  = 9;
				}

				else if(gstDisplayCode.CurMode == GuoShuMode)
				{
						gstDisplayCode.CurMode = BingXianMode;
						gHeatCoolTemp.Bit.CoolTempSet  = COOLTEMPMin -1;
				}
				else
				{
						gstDisplayCode.CurMode = BingXianMode;
						gHeatCoolTemp.Bit.CoolTempSet  = COOLTEMPMin -1;
				}
				
				if(gHeatCoolTemp.Bit.CoolTempSet  == COOLTEMPMin -1)
					CoolSuDongFlag = 1;
				else
					CoolSuDongFlag = 0;

				gHeatCoolTemp.Bit.EEpromRun = 1;
				gHeatCoolTemp.Bit.heat = HeatFlag;
				gHeatCoolTemp.Bit.cool = CoolFlag;

		}
		Buzzer2Flag =1;
		
}

/****************************************************************************************************************************************** 
* 函数名称:	KeyTempDec
* 功能说明:	增加设置值有效判断
* 输    入: 无	
* 输    出: 无
* 注意事项: 触发时间50ms
******************************************************************************************************************************************/




/****************************************************************************************************************************************** 
* 函数名称:	SetValidJudgment
* 功能说明:	温度设置值判断
* 输    入: 无	
* 输    出: 无
 设置值(CoolTempSet,HeatTempSet)小于或大于配置(TemprertureTab)值,设置值=配置值

******************************************************************************************************************************************/
void SetValidJudgment(void)
{
		if(gHeatCoolTemp.Bit.CoolTempSet < TemprertureTab[0].CompensationValue )
		{
					gHeatCoolTemp.Bit.CoolTempSet = TemprertureTab[0].CompensationValue;
		}
						
		if(gHeatCoolTemp.Bit.CoolTempSet > TemprertureTab[1].CompensationValue )
		{
			 	  gHeatCoolTemp.Bit.CoolTempSet = TemprertureTab[1].CompensationValue;
		}
						
		if(gHeatCoolTemp.Bit.HeatTempSet < TemprertureTab[2].CompensationValue )
		{
					gHeatCoolTemp.Bit.HeatTempSet = TemprertureTab[2].CompensationValue;
		}
						
		if(gHeatCoolTemp.Bit.HeatTempSet > TemprertureTab[3].CompensationValue )
		{
					gHeatCoolTemp.Bit.HeatTempSet = TemprertureTab[3].CompensationValue;
		}
}


void KeyTempDec(void)
{
		u8 i;
		ParameterRecoverFlag = 0;
    if(!SysRunFlag)
    {
        return;
    }
    
		if(gstTempCompensation.Run.Bit.RunFlag)
		{
			
				
			
				if(0xec == gstTempCompensation.mode)
				{
						return;
				}
				gstTempCompensation.Run.Bit.DisplayValueFlag = 1;//
				gstTempCompensation.Run.Bit.DisplayModeFlag = 0;
				gstTempCompensation.RecoverTimer = 0;
				if(!MinusKeyFlag )
				{
						MinusKeyFlag = 1;
						Buzzer2Flag =1;
						MoodeSetFlag = 0;
						return;
				}
				
				
				
			
				for(i = 0; i<=TAB_LENGTH;i++ )
				{
						if(TemprertureTab[i].DisplayMode >0XEC || TemprertureTab[i].DisplayMode < 0XE0)
						{
								memcpy((void *)TemprertureTab,(void *)ImageTemprertureTab,TAB_SIZE);
						}
				}
				
			
				for( i= 0; i<= TAB_LENGTH ;i++)
				{
						
						if(gstTempCompensation.mode  ==  TemprertureTab[i].DisplayMode)
						{
								TemprertureTab[i].CompensationValue--;
						}
						
						if(TemprertureTab[0].CompensationValue < -10)//极冻模式
						{
								TemprertureTab[0].CompensationValue = -10;
						}	

						if(TemprertureTab[1].CompensationValue < 9 )//和艾凯李工11.14日晚沟通，改成固定值
						{
								TemprertureTab[1].CompensationValue = 9 ;
						}
	
						if(TemprertureTab[2].CompensationValue < 30)
						{
								TemprertureTab[2].CompensationValue = 30;
						}
						
						if(TemprertureTab[3].CompensationValue < 55 )//和艾凯李工11.14日晚沟通，改成固定值
						{
								TemprertureTab[3].CompensationValue = 55 ;
						}
						
						if(TemprertureTab[4].CompensationValue < 1)
						{
								TemprertureTab[4].CompensationValue = 1;
						}
						
						
						
						if(TemprertureTab[5].CompensationValue < -9)
						{
								TemprertureTab[5].CompensationValue = -9;
						}
						
						if(TemprertureTab[6].CompensationValue < -9)
						{
								TemprertureTab[6].CompensationValue = -9;
						}
						
						
						if(TemprertureTab[7].CompensationValue < -9)
						{
								TemprertureTab[7].CompensationValue = -9;
						}
						
						if(TemprertureTab[8].CompensationValue < -9)
						{
								TemprertureTab[8].CompensationValue = -9;
						}
						
						if(TemprertureTab[9].CompensationValue < -9)
						{
								TemprertureTab[9].CompensationValue = -9;
						}
						
						if(TemprertureTab[10].CompensationValue < 0)
						{
								TemprertureTab[10].CompensationValue  = 0;
						}
				}
				
		}
		else
		{
    
				CoolSuDongFlag = 0;
				VoiceSetFlag = 0;
				gstDisplayCode.CurMode  = 0;
				if(HeatFlag )
				{
						if(gHeatCoolTemp.Bit.HeatTempSet > HEATEMPMin)
						{
								gHeatCoolTemp.Bit.HeatTempSet--;
						}
						else
						{
								gHeatCoolTemp.Bit.HeatTempSet = HEATEMPMin;
						}
				}
				else if(CoolFlag)
				{
						if(gHeatCoolTemp.Bit.CoolTempSet > COOLTEMPMin)
						{
								gHeatCoolTemp.Bit.CoolTempSet--;
								
						}
						else
						{
								gHeatCoolTemp.Bit.CoolTempSet = COOLTEMPMin;
						}
						
				}
				
				gHeatCoolTemp.Bit.EEpromRun = 1;
				
				DisplayTempSet();
		}
    
    Buzzer4Flag =1;
}

/****************************************************************************************************************************************** 
* 函数名称:	KeyTempAdd
* 功能说明:	温度调节加
* 输    入: 无	
* 输    出: 无
* 注意事项: 触发时间50ms
******************************************************************************************************************************************/

void KeyTempAdd(void)
{
		u8 i;
		ParameterRecoverFlag = 0;
    if(!SysRunFlag)
    {
        return;
    }
	
			
    CoolSuDongFlag = 0;
		
		if(gstTempCompensation.Run.Bit.RunFlag)
		{
				
				
				
//				if(!TempSetFlag )
//				{
//						TempSetFlag = 1;
//						Buzzer2Flag =1;
//					  MoodeSetFlag = 0;
//						return;
//				}
			
				if(0xec == gstTempCompensation.mode)
				{
						return;
				}
				gstTempCompensation.Run.Bit.DisplayValueFlag = 1;//
				gstTempCompensation.Run.Bit.DisplayModeFlag = 0;
				gstTempCompensation.RecoverTimer = 0;
			
				if(!MinusKeyFlag )
				{
						MinusKeyFlag = 1;
						Buzzer2Flag =1;
					  MoodeSetFlag = 0;
						return;
				}
				
				
				
				
				for(i = 0; i<=TAB_LENGTH;i++ )
				{
						if(TemprertureTab[i].DisplayMode >0XEC || TemprertureTab[i].DisplayMode < 0XE0)
						{
								memcpy((void *)TemprertureTab,(void *)ImageTemprertureTab,TAB_SIZE);
						}
				}
				
			 	for( i= 0; i<= TAB_LENGTH ;i++)
				{
						if(gstTempCompensation.mode  ==  TemprertureTab[i].DisplayMode)
						{
								TemprertureTab[i].CompensationValue ++;//TemprertureTab[i].CompensationValue = 0;
						}
						
						if(TemprertureTab[0].CompensationValue > 0 ) //这个值最小9，触及不到最小值
						{
								TemprertureTab[0].CompensationValue = 0;
						}
						
						if(TemprertureTab[1].CompensationValue > 25)
						{
								TemprertureTab[1].CompensationValue = 25;
						}
						
						if(TemprertureTab[2].CompensationValue > 45) //这个值最小55，触及不到最小值
						{
										TemprertureTab[2].CompensationValue = 45;
						}
						
						if(TemprertureTab[3].CompensationValue > 65)
						{
								TemprertureTab[3].CompensationValue = 65;
						}
						
						if(TemprertureTab[4].CompensationValue >10)
						{
								TemprertureTab[4].CompensationValue = 10;
						}
						
						if(TemprertureTab[5].CompensationValue >0)
						{
								TemprertureTab[5].CompensationValue = 0;
						}
						
						if(TemprertureTab[6].CompensationValue >  10)
						{
								TemprertureTab[6].CompensationValue = 10;
						}
						
						if(TemprertureTab[7].CompensationValue >  10)
						{
								TemprertureTab[7].CompensationValue = 10;
						}
						
						if(TemprertureTab[8].CompensationValue >  10)
						{
								TemprertureTab[8].CompensationValue = 10;
						}
						
						if(TemprertureTab[9].CompensationValue >  10)
						{
								TemprertureTab[9].CompensationValue = 10;
						}
						
						if(TemprertureTab[10].CompensationValue > 1)
						{
								TemprertureTab[10].CompensationValue = 1;
						}
						//gHeatCoolTemp.Bit.EEpromRun = 1; 退出工程模式再次写入eeprom，操作过程中不写入 
						
				}
		}
		else
		{
				gstDisplayCode.CurMode  = 0;
				VoiceSetFlag = 0;

				if(CoolFlag)
				{
						if(gHeatCoolTemp.Bit.CoolTempSet < COOLTEMPMax)
						{
								gHeatCoolTemp.Bit.CoolTempSet++;
						}
						else
						{
								gHeatCoolTemp.Bit.CoolTempSet = COOLTEMPMax;
						}
				}
				else if(HeatFlag)
				{
						if(gHeatCoolTemp.Bit.HeatTempSet <  HEATEMPMax)
						{
								gHeatCoolTemp.Bit.HeatTempSet++;
						}
						else
						{
								gHeatCoolTemp.Bit.HeatTempSet = HEATEMPMax;
						}
						/////////////////////////取消速热模式/////////////////////////
						/* ////////////////
						if(gHeatCoolTemp.Bit.HeatTempSet == HEATEMPMax+1)
						{
								HeatSuReFlag = 1;
								gHeatCoolTemp.Bit.HeatTempSet  = HEATEMPMax;
						}*/
				}
				gHeatCoolTemp.Bit.EEpromRun = 1;
				DisplayTempSet();//TempSetFlag = 1;
				
		}
    
    Buzzer4Flag =1;
}
/****************************************************************************** 
* 函数名称:	KeyChouTi
* 功能说明:	抽屉功能开关键
* 输    入: 无	
* 输    出: 无
* 注意事项: 短按有效
******************************************************************************/
void KeyChouTi(void)
{
		if(HuoErIO_Flag == 0)
		{
				if(gChouTiOpenCnt < KEY_CHOU_TI_DealyTime)
				{
						return;
				}	
		}
		else
		{
				if(gChouTiOpenCnt < KEY_CHOU_TI_DealyTime_2)
				{
						return;
				}
		}
	 
		
		gChouTiOpenCnt = 0;
		
    ChouTiFlag = 1;
}


/****************************************************************************************************************************************** 
* 函数名称:	KeyShortPressFunc1
* 功能说明:	短按处理函数,对KeyShortPressFunc 的补充
* 输    入: 无	
* 输    出: 无
* 注意事项: 触发时间50ms
******************************************************************************************************************************************/

void  KeyShortPressFunc_1(uint8_t Key)
{

        
			 #if  (CINGIG_SYSLOCK )  
				 if(Key == KEY6_MASK)
         {
             if(sysLock )
             {
                 return;
             }               
             KeyChouTi();     
         }
				 
         if(Key == KEY5_MASK)
         {
            if(!SysRunFlag || sysLock )
            {
                  return;
             }
            KeyHeat();           
         }
				 #endif
}


/****************************************************************************************************************************************** 
* 函数名称:	KeyShortPressFunc
* 功能说明:	短按处理函数
* 输    入: 无	
* 输    出: 无
* 注意事项: 触发时间50ms
******************************************************************************************************************************************/

void  KeyShortPressFunc(uint8_t Key)
{
        if(Key == KEY4_MASK)
        {
             if(!SysRunFlag   )
             {
                  return;
             }
						 
						 if(sysLock)
						 {
							 BuzzerFlag = 1;
							 return;
						 }
						KeyTempAdd();   
        }
    
        else if(Key ==  KEY3_MASK)
        {
            if(!SysRunFlag )
            {
                 return;
            }
						if(sysLock)
						{
							BuzzerFlag = 1;
							return;
						}
            KeyTempDec();      
        }

        if(Key== KEY2_MASK)
        {
             if(!SysRunFlag  )
             {
                  return;
             }
						 if(sysLock)
						 {
							BuzzerFlag = 1;
							return;
						 }
             KeyCooL();        
        }

        if(Key == KEY8_MASK)
        {   
            BuzzerFlag =1;           
        }
    
        if(Key == KEY1_MASK )
        {
						if(sysLock)
							{
							BuzzerFlag = 1;
							return;
						}
            KeyPower();   
        }
				
	///////////////////////////////////

     #if  (CINGIG_SYSLOCK == 0) 
         if(Key == KEY5_MASK)
         {
            if(!SysRunFlag || sysLock )
            {
                  return;
            }
            KeyHeat();           
         }
				 
				if(Key == KEY6_MASK)
        {
             if(sysLock )
             {
                 return;
             }               
             KeyChouTi();     
         }
		#endif
	///////////////////////////////////				 
}
/****************************************************************************************************************************************** 
* 函数名称:	KeyLongPressFunc
* 功能说明:	长按处理函数
* 输    入: 无	
* 输    出: 无
* 注意事项: 触发时间50ms
******************************************************************************************************************************************/



void KeyLongPressFunc(uint32_t time)
{
				if(time >= _1S_Per50MS)
        {
            if((gKeyValue == KEY4_MASK) && SysRunFlag && !sysLock)
            {
                 if(!SysRunFlag || sysLock  )
                 {
                      time = 0;
                      return;
                 }
								 
                 if(time % 6 == 0)
                 {
                     time = _1S_Per50MS;
                     KeyTempAdd();
                     Buzzer4Flag = 0;
                 }                   
            }
    
            else if((gKeyValue == KEY3_MASK )&& SysRunFlag && !sysLock)
            {
                  if(!SysRunFlag || sysLock )
                  {
                       time = 0;
                       return;
                  }
                  if(time %6 == 0)
                  {
                      time = _1S_Per50MS;
                       KeyTempDec();
                       Buzzer4Flag =0;
                  }                     
            }
        }  

        if(time >= _3S_Per50MS)
        {
		 #if  (CINGIG_SYSLOCK ) 
						 if(gKeyValue == (KEY5_MASK|KEY6_MASK)  && SysRunFlag && sysLock)//lock
             {
                sysLock = 0;
                SysOffDelayFlag = 1;
                BuzzerFlag =1; 
             }
		 #endif
						 
						 if(gKeyValue == (KEY3_MASK|KEY4_MASK)  )
						 {
							 ClearDelayCnt();
							 if( gstTempCompensation.mode == 0xe1 && !ParameterRecoverFlag)
							 {
									//time = _1S_Per50MS;
									ParameterRecoverFlag =1;
									gstTempCompensation.RecoverTimer = 0;
									BuzzerPowerOnFlag =1;
									memcpy((void *)TemprertureTab,(void *)ImageTemprertureTab,TAB_SIZE);
									SetValidJudgment();
							 }
							 
							#if  (CINGIG_SYSLOCK == 1) 
							 else
							 {
								 if(sysLock)
								 {
										sysLock = 0;
										SysOffDelayFlag = 1;
										Buzzer1Flag =1; 
										
								 }				
							 }
							#endif
						}
        }
				
				if(time >= _5S_Per50MS)
        {
						 if((gKeyValue == (KEY2_MASK|KEY5_MASK))  && SysRunFlag)
             {
								if(gstTempCompensation.PowerOnTimer <= 100 )
								{
										BuzzerPowerOnFlag =1;
										gstTempCompensation.Run.Bit.DisplayModeFlag = 1;
										gstTempCompensation.Run.Bit.RunFlag   =   1;
										gstTempCompensation.mode = 0xe1;
										gstTempCompensation.RecoverTimer = 0;
												
								}									
             }
						 
						 
        }
				
				if(time >=  _10S_Per50MS)
        {
             if(gKeyValue == KEY6_MASK )//lock
             {
								ChouTiOutputHoldFlag = 1;
								
             }
        }
}

void KeyEnterFactory(void)
{
	
     if((gKeyValue == KEY2_MASK) ||  (gKeyValue == KEY5_MASK))
     {
         gstFactory.sFactoryTime ++;
         if(gstFactory.sFactoryTime > _25S_Per100MS)
         {
             RealTimeDisplayFlag  = !RealTimeDisplayFlag;
             gstFactory.sFactoryTime = 0;
             Buzzer2Flag = 1;
         }
     }

     else
     {
        gstFactory.sFactoryTime = 0;
     }
				
		

}
/****************************************************************************************************************************************** 
* 函数名称:	KeyProcess
* 功能说明:	处理按键长按短按功能
* 输    入: 无	
* 输    出: 无
* 注意事项: 触发时间50ms
******************************************************************************************************************************************/
void KeyProcess(void)
{ 
     static unsigned char  KeyPressCnt = 0;  
     static unsigned int  NoAcctionCnt = 0;
     static unsigned char sKeyValue = 0;
     
     
    if(gKeyValue > 0)
    {       
			   __RTE_5sAppMsgTriggerByLocalEvent_Start();
				if(NoAcctionCnt > 0 )
				{
						NoAcctionCnt >>=2;
				}
			
        if(SysOffDelayFlag)
            return;

        if(KeyPressCnt < 0xff)
        	KeyPressCnt++;
				
				
        
        if(KeyPressCnt == 1)
        {
            if(gKeyValue == KEY5_MASK || gKeyValue == KEY6_MASK )
            {
							
                 sKeyValue = gKeyValue;
							
								 if(sysLock)
								 {
											BuzzerFlag = 1;
											return;
								 }
								 else
								 {
										if(gKeyValue == KEY5_MASK && SysRunFlag )
										{
												Buzzer5Flag =1; 
										}
										else if(gKeyValue == KEY6_MASK )
										{
												Buzzer6Flag =1; 
										}
								}
            } 
						KeyShortPressFunc(gKeyValue);
        }
        
//        else if(KeyPressCnt == 2)
//        {
//            KeyShortPressFunc(gKeyValue);
//        }  
        else
        {
            KeyLongPressFunc(KeyPressCnt);
        }
    }
    else
    {  
				
				KeyPressCnt =0;
			
        if(!sysLock && !SysOffDelayFlag && ( sKeyValue == KEY5_MASK || sKeyValue == KEY6_MASK ))
        {
					if(NoAcctionCnt == 0)
					{
							KeyShortPressFunc_1(sKeyValue);
              sKeyValue = 0;
					}             
        }
         
				if(SysOffDelayFlag)
				{
					sKeyValue = 0;
					if(NoAcctionCnt < 20)
					{
							NoAcctionCnt++;
					}
					else
					{
							SysOffDelayFlag = 0;
					}
				}
         
     }     
}

