#include "globe.h"
#include "clib.h"
#include "key.h"
#include "bsp_Led.h"
#include "sysRun.h"
#include "factory.h"
#include "Display.h"
#include "FuncTab.h"
////////////////////////////////////

#include "adc_driver.h"
#include "pins_driver.h"
#include "ftm_pwm_driver.h"
#include "bsp_eeprom.h"

#define uint8_t unsigned  char


extern void SetValidJudgment(void);
extern void KeyCooL(void);
extern void ReadBusState_318(void);


 void OpenYaSuoJi_1(void) 
 {
		 OpenYaSuoJiFlag =1; 
	   OpenHeatFlag =0;
	   if(!DayAndNightFlag)
		 {
				PINS_DRV_WritePin(PTA,13,1);PINS_DRV_WritePin(PTC,6,0);
		 }
		 else
		 {
				PINS_DRV_WritePin(PTC,6,1),PINS_DRV_WritePin(PTA,13,0);
		 }
			
 }	 
	
 
void ForceOutput(void)
{
	uint8_t fo_buf[8];
	uint8_t fo_len;
	uint8_t fo_modeTemp = 3;
	

	fo_modeTemp = __RTE_2FModeOnSt(fo_buf, &fo_len);
	__RTE_ClrRcv2FMsgSt();

	if(0 == fo_modeTemp)//quit 2F force mode
	{
		if(1 == gForceOutputFlag.Bit.b0)
		{
			gForceOutputFlag.Bit.b0 = 0;
		}
	}
	else if(1 == fo_modeTemp)//in 2F force mode
	{
		if(0 == gForceOutputFlag.Bit.b0)
		{
			gForceOutputFlag.Bit.b0 = 1;
		}
	}
	else if(2 == fo_modeTemp)//in 2F force mode, and new message received.
	{
		if(0 == gForceOutputFlag.Bit.b0)
		{
			gForceOutputFlag.Bit.b0 = 1;
		}
		
		if((2 == fo_len) && (3 == fo_buf[0]))
		{
			if(fo_buf[1] & 0x01)//cool active
			{
				gForceOutputFlag.Bit.b1 = 1;
			}
			else//cool inactive
			{
				gForceOutputFlag.Bit.b1 = 0;
			}
			
			if(fo_buf[1] & 0x02)//heat active
			{
				gForceOutputFlag.Bit.b2 = 1;
			}
			else//heat inactive
			{
				gForceOutputFlag.Bit.b2 = 0;
			}
			
			if(fo_buf[1] & 0x04)//button lock active
			{
				gForceOutputFlag.Bit.b3 = 1;
			}
			else//button lock inactive
			{
				gForceOutputFlag.Bit.b3 = 0;
			}
			
			if(fo_buf[1] & 0x08)//LED acitve
			{
				gForceOutputFlag.Bit.b4 = 1;
			}
			else//LED inactive
			{
				gForceOutputFlag.Bit.b4 = 0;
			}
			
			if(fo_buf[1] & 0x10)//door open
			{
				ChouTiFlag = 1;
			}
			else//
			{
			}
			
			if(fo_buf[1] & 0x20)//ozone acitve
			{
				gForceOutputFlag.Bit.b5 = 1;
			}
			else//ozone inactive
			{
				gForceOutputFlag.Bit.b5 = 0;
			}
		}
	}

	return;
}
#define CHOU_FAULT_TEST 0

void ChouTiMotor(void)
{
    static uint8_t ChouTiTimeCnt =0;
		static u8 sOutputHold = 0;
	
		if(RDFactoryTestFlag)
			return;
	
		if(HuoErIO_Flag == 0)
		{
			if(KEY_CHOU_TI_DealyTime > gChouTiOpenCnt)
				gChouTiOpenCnt++;
		}
		else
		{
			if(KEY_CHOU_TI_DealyTime_2 > gChouTiOpenCnt)
				gChouTiOpenCnt++;
		}
		 
		 
		if(ChouTiOutputHoldFlag)
		{
				sOutputHold++;
			#if CHOU_FAULT_TEST
			if(sOutputHold < 100) 100ms调用
			#else
			if(sOutputHold < 200)
			#endif
				{
					ChouTiMotor_set;
					if(sOutputHold ==2)
					{
						ChouTiCurentFlag = 1;
						Buzzer5Flag =1; 
					}
				}
				else
				{
						ChouTiMotor_clr;
						ChouTiCurentFlag = 0;
						sOutputHold = 0;
						ChouTiOutputHoldFlag =0;
				}
				
		}
		
    else if(ChouTiFlag)
    {
      #if 0//限量版抽屉是50ms
        ChouTiMotor_set;//抽屉推杆使能        
      #else  
		ChouTiMotor_set;//抽屉推杆使能
		if(ChouTiTimeCnt == ChouTiMotorTime -1)
		{
			ChouTiCurentFlag = 0; 
		}
				#if 1//CHOU_FAULT_TEST
				if(ChouTiTimeCnt == 2)
				{
					ChouTiCurentFlag = 1;
				}       
				#else
			    ChouTiCurentFlag = 1;
				#endif
			#endif
				
			
		if(ChouTiTimeCnt >= ChouTiMotorTime)
        {
            ChouTiFlag = 0;
            ChouTiTimeCnt =0;
			ChouTiMotor_clr;
			return;
        }
		ChouTiTimeCnt++;
    }
    
}


void SetPause(void)
{
		//Pause_Flag =  1;
		gPauseCnt = _30S_Per100MS;
}


/****************************************************************************************************************************************** 
* 函数名称:	HuoErIOProcess
* 功能说明:	臭氧功能处理
* 输    入: 无	
* 输    出: 无
* 备注：每隔一秒钟运行一次 
******************************************************************************************************************************************/
void HuoErIOProcess(void)
{
	static uint16_t HuoErCnt;
	static uint8_t DoorOpenCnt;
	
	if(RDFactoryTestFlag)
					return;

	if(AbnormalPowerFlag)
	{
			CloseOzne_IO;
			return;
	}
	
	
	if(AiKaiOzneTestFlag)
	{
		if(HuoErCnt <  _1h_Per1S  )
		{
				HuoErCnt++;
//				HuoErCnt = 0;
//				if(HuoErIO_Flag )
//				{
//						HuoErCnt = 0;
//				}
			  OpenOzne_IO;OzoneFlag = 1;
		}
		else
		{
				AiKaiOzneTestFlag  = 0;
				CloseOzne_IO;//OzoneFlag = 0;
		}
		return;
	}
	
	if(HeatFlag)
	{
			OzoneFlag = 0;
			CloseOzne_IO;
			return;
	}
			
		
	
	if(HuoErIO_Flag == 0)
	{
		HuoErCnt++;
		DoorOpenCnt = 0;
		if(HuoErCnt <  _1h_Per1S  )
		{
			OzoneFlag = 0;//OzoneFlag = 1;
		}

		else if(HuoErCnt < _1h_Per1S + _2Min_Per1S)
		{
			OzoneFlag = 1;
		}
		else if(HuoErCnt < _1h_Per1S+_1h_Per1S)
		{
			OzoneFlag = 0;		
		}
		else
		{
				HuoErCnt = _1h_Per1S;
		}
		
	}
    else
    {
				SetPause();
				OzoneFlag = 0;
				HuoErCnt = 0;
			
				if(DoorOpenCnt <= 65)
					DoorOpenCnt++;
				
				if(DoorOpenCnt >= 60 && DoorOpenCnt < 65)
				{
						Buzzer5Flag = 1;
			  }				
    }
		
    
    if(OzoneFlag)
    {
        OpenOzne_IO;//set the Ozonator
    }
    else
    {
        CloseOzne_IO;//stop the Ozonator
    }
}

/****************************************************************************************************************************************** 
* 函数名称:	CoolProcess
* 功能说明:	压缩机逻辑处理
* 输    入: 无	
* 输    出: 无
* 备注：切换到制冷，若当前温度高于设置温度，且冰箱温度小于（TEMP_SET_VALUE）30摄氏度，则打开压缩机。否则延迟15min。
 *      运行中，若温度达到设置温度关闭压缩机， 当当前温度达比设置温度高2°，则再次打开压缩机   
******************************************************************************************************************************************/

#define COOL_TEMP_SET (gHeatCoolTemp.Bit.CoolTempSet+ TemprertureTab[5].CompensationValue)
#define HEAT_TEMP_SET (gHeatCoolTemp.Bit.HeatTempSet  )
#define TEMP_BACK_SET  TemprertureTab[4].CompensationValue//hui wen cha



void CoolProcess(void)
{
        static  uint16_t suiCoolTime;
        static  uint32_t  sLLCoolTime;
				u8 temp1;
	
				if(RDFactoryTestFlag)
					return;
				
				if(AbnormalPowerFlag)
				{
						CloseYaSuoJi ;
						return;
				}
				
				if(gHeatCool.Bit.CoolCnt > 0 && (COOL_TEMP_SET!= -10)/*急冻*/)
        {
              gHeatCool.Bit.CoolCnt--;
							if(gTempAD <= TEMP_SET_VALUE)
							{
                  gHeatCool.Bit.CoolCnt = 0;
							}
							CloseYaSuoJi ;
							return;
         }
				
				if(gPauseCnt > 0 && (COOL_TEMP_SET!= -10)/*急冻*/)
				{
						gPauseCnt--;
						CloseYaSuoJi; 
						return;
				}
				
				
				
        if(!CoolFlag || !SysRunFlag || ALLTempSenseErrowFlag)
        {
             CloseYaSuoJi; 
             gHeatCool.Bit.CoolHis = 0;
            return;
        }
				
				
				
        if(gHeatCool.Bit.CoolHis ^ CoolFlag && (COOL_TEMP_SET != -1))// TemprertureTab[0]-1
        {
            gHeatCool.Bit.CoolHis =  CoolFlag;         
            if(gTempAD > TEMP_SET_VALUE )
            {	
								if(CoolFlag_FromEEprom)
								{
									CoolFlag_FromEEprom = 0;
								}
								else
								{
										gHeatCool.Bit.CoolCnt = _15Min_Per100MS;
								}
                  
								return;						
            } 
						
            else if(COOL_TEMP_SET < gTempAD )   
            {
                   OpenYaSuoJi;
            }
            if(ALLTempSenseErrowFlag)
            {
                    suiCoolTime = 0;
            }
         }
    
        if(gHeatCool.Bit.LLCoolHis ^ CoolSuDongFlag)
        {
							gHeatCool.Bit.LLCoolHis = CoolSuDongFlag;
              sLLCoolTime = _90Min_Per100MS;
							
        }
				
				if(gHeatCoolTemp.Bit.CoolTempSet == -10)
				{
						OpenYaSuoJi;
						CoolSuDongFlag = 0;
				}
        
        else if(CoolSuDongFlag &&(gHeatCool.Bit.CoolCnt == 0) )
        {
					
            if(sLLCoolTime-- > 0)
            {
                OpenYaSuoJi;
								if(gTempAD == -5)
								{
									sLLCoolTime = 0;
								}
					
            }
            else
            {
                 CloseYaSuoJi;
								 CoolSuDongFlag = 0;
								 gHeatCoolTemp.Bit.CoolTempSet= 0;
            }
        }
        else
        {
  
    
            if(ALLTempSenseErrowFlag)
              suiCoolTime++;
          
						if(ALLTempSenseErrowFlag)
						{
									CloseYaSuoJi;
						}
						else
						{ 
							 //当前温度比设置温度高两度以上
							
							//temp1 = COOL_TEMP_SET;
								
							 if((gTempAD-COOL_TEMP_SET >= TEMP_BACK_SET) /*&& (gHeatCool.Bit.CoolCnt ==0)*/)  
							 {
									OpenYaSuoJi;
							 }
								//当前温度小于或者等于设置温度
						   else if(COOL_TEMP_SET >= gTempAD )  
							 {
									CloseYaSuoJi;
							 }
						}
						
						
						 
				}    
       
}



/****************************************************************************************************************************************** 
* 函数名称:	AuxHeatProcess
* 功能说明:	辅助加热处理
* 输    入: 无	
* 输    出: 无
* 备注：
******************************************************************************************************************************************/

void AuxHeatProcess(void)
{
				static  uint16_t suiAuxHeatOpenTime;
				static  uint16_t suiAuxHeatCloseTime;
				if(RDFactoryTestFlag)
					return;
				
				if(AbnormalPowerFlag)
				{
						CloseAuxHeat ;
						return;
				}
        
        if( !SysRunFlag || AbnormalPowerFlag || ALLTempSenseErrowFlag)
        {
             gHeatCool.Bit.HeatHis = 0;
             CloseAuxHeat;
            return;
        }
				
				
				if(gTempAD <= 10)
				{
					if(CoolSuDongFlag)
					{
							OpenAuxHeat;
							suiAuxHeatOpenTime =0;
					}
					else
					{
							suiAuxHeatOpenTime++;
							if(suiAuxHeatOpenTime <= _40Min_Per100MS)
							{
									OpenAuxHeat;
							}
							else if(suiAuxHeatOpenTime < _20Min_Per100MS+_40Min_Per100MS)
							{
									CloseAuxHeat;
							}
							else
							{
									suiAuxHeatOpenTime = 0;
							}
							suiAuxHeatCloseTime = 0;
					}				
				}
			
				else
				{
						suiAuxHeatOpenTime = 0;
						CloseAuxHeat;
				}
			
//			 else if(OpenAuxHeatFlag)
//			 {
//						suiAuxHeatOpenTime = 0;
//						suiAuxHeatCloseTime++;
//						if(suiAuxHeatCloseTime >= _30Min_Per100MS)
//						{
//								CloseAuxHeat;
//						}
//						
//			 }
}
/****************************************************************************************************************************************** 
* 函数名称:	HeatPWM_ioProcess
* 功能说明:	加热PWM处理
* 输    入: 无	
* 输    出: 无
* 备注：
******************************************************************************************************************************************/
void HeatPWM_ioProcess(void)
{
		if(!OpenHeatFlag)
			return;
		
		if(gTempAD < 45)
		{
				gPwmDuty = 100;
				return;
		}
#if 0
		if(HEAT_TEMP_SET - gTempAD == 1)
		{
				gPwmDuty = 45;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 2)
		{
				gPwmDuty = 50;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 3)
		{
				gPwmDuty = 55;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 4)
		{
				gPwmDuty = 60;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 5)
		{
				gPwmDuty = 65;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 6)
		{
				gPwmDuty = 70;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 7)
		{
				gPwmDuty = 75;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 8)
		{
				gPwmDuty = 80;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 9)
		{
				gPwmDuty = 85;
		}
		
		
	#else
		/* // 10%
		if(HEAT_TEMP_SET - gTempAD == 1)
		{
				gPwmDuty = 50;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 2)
		{
				gPwmDuty = 55;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 3)
		{
				gPwmDuty = 60;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 4)
		{
				gPwmDuty = 65;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 5)
		{
				gPwmDuty = 70;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 6)
		{
				gPwmDuty = 75;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 7)
		{
				gPwmDuty = 80;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 8)
		{
				gPwmDuty = 85;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 9)
		{
				gPwmDuty = 90;
		}*/
		///20%
		
		
		
		if(HEAT_TEMP_SET - gTempAD == 1)
		{
				gPwmDuty = 40;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 2)
		{
				gPwmDuty = 40;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 3)
		{
				gPwmDuty = 45;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 4)
		{
				gPwmDuty = 50;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 5)
		{
				gPwmDuty = 55;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 6)
		{
				gPwmDuty = 60;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 7)
		{
				gPwmDuty = 65;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 8)
		{
				gPwmDuty = 70;
		}
		
		else if(HEAT_TEMP_SET - gTempAD == 9)
		{
				gPwmDuty = 75;
		}
		else if(HEAT_TEMP_SET - gTempAD == 10)
		{
				gPwmDuty = 80;
		}
		
#endif		
		else
		{
				gPwmDuty = 100;
		}
		
}

/****************************************************************************************************************************************** 
* 函数名称:	HeatProcess
* 功能说明:	加热处理
* 输    入: 无	
* 输    出: 无
* 备注：
******************************************************************************************************************************************/
void HeatProcess(void)
{
        static  uint16_t suiHeatTime;
	
				if(RDFactoryTestFlag)
					return;
				
				if(AbnormalPowerFlag || HeatErrowFlag)
				{
						CloseHeat; 
						return;
				}
        
        if(!HeatFlag  || !SysRunFlag || AbnormalPowerFlag || ALLTempSenseErrowFlag)
        {
             gHeatCool.Bit.HeatHis = 0;
             CloseHeat;
            return;
        }
        if(gHeatCool.Bit.HeatHis ^ HeatFlag)
        {
             gHeatCool.Bit.HeatHis =  HeatFlag;         
             gHeatCool.Bit.HeatCnt = _15S_Per100MS;
             if(ALLTempSenseErrowFlag)
             {
                 suiHeatTime = 0;
             }        
        }
        
        if(gHeatCool.Bit.HeatCnt > 0)
        {
            gHeatCool.Bit.HeatCnt--;
        }
       
         if(ALLTempSenseErrowFlag)
            suiHeatTime++;
    
        if(ALLTempSenseErrowFlag)
        {
//            if(suiHeatTime <= _3Min_Per100MS)
//            {
//                OpenHeat;
//            }
//            else if(suiHeatTime < _13Min_Per100MS)
//            {
//                CloseHeat;
//            }
//            else
//            {
//                suiHeatTime = 0;
//            }
							CloseHeat;
        }
        else
        {
            //设置温度比当前温度高两度以上
            if((HEAT_TEMP_SET-gTempAD >= 2) && (gHeatCool.Bit.HeatCnt ==0))  
            {
                OpenHeat;
            }
             //当前温度大于或者等于设置温度
            else if(gHeatCoolTemp.Bit.HeatTempSet <= gTempAD )  
            {
                CloseHeat;
            }   
        }
            
}


void Rest_YaSuoJiData(void)
{
		YaSuoJiErrowFlag = 0;
		YaSuoJiErrowDisplayFlag = 0;
		gstYaSuoJiErrow.ErrorCodeDisplayData = 0;
		gstYaSuoJiErrow.HighLevelTimeCnt =0 ;
    gstYaSuoJiErrow.LowLevelTimeCnt = 0; 
    gstYaSuoJiErrow.ErrorCodeData = 0;
		YaSuoJiErrowTimeCntFlag = 0;
		//gstYaSuoJiErrow.FaultCnt=0; 
}
/****************************************************************************************************************************************** 
* 函数名称:	ReadYaSuoJiData
* 功能说明:	读取压缩机故障代码
* 输    入: 无	
* 输    出: 无
* 注意事项: 在高电平时间段检测低电平的持续时间，若持续时间大于100ms，则认为是有效计数，
 *          高电平时间若大于200ms，这里取280ms，则认为采集周期结束
******************************************************************************************************************************************/

void YaSuoJiErrowTimeCnt(void)
{
		static u16 sResumptionCnt =0 ;

		if(YaSuoJiErrowTimeCntFlag )
		{
			sResumptionCnt = 0;
			if(gstYaSuoJiErrow.FaultCnt <0xff)
				gstYaSuoJiErrow.FaultCnt++;
		}
		else
		{
				sResumptionCnt++;
				if(sResumptionCnt > _35S_Per1S)
				{
						gstYaSuoJiErrow.FaultCnt = 0;
						sResumptionCnt = 0;
				}
		}
}


void ReadYaSuoJiData(void)
{
	
    if((GetActiveSignal_YAJ == 0) &&(gstYaSuoJiErrow.LowLevelTimeCnt  <= _220MS_Per20MS))
    {
						gstYaSuoJiErrow.LowLevelTimeCnt ++;
            gstYaSuoJiErrow.ErrorToNomalCnt = 0;
            gstYaSuoJiErrow.HighLevelTimeCnt  = 0;
            
    }
    else if(GetActiveSignal_YAJ )
    {
        if(gstYaSuoJiErrow.HighLevelTimeCnt <0xff)
        {
            gstYaSuoJiErrow.HighLevelTimeCnt++;      
        }
 
        if( gstYaSuoJiErrow.HighLevelTimeCnt  <= _260MS_Per20MS)
        {
            if( gstYaSuoJiErrow.LowLevelTimeCnt > _140MS_Per20MS)
            {
                gstYaSuoJiErrow.ErrorCodeData++;
								gstYaSuoJiErrow.LowLevelTimeCnt = 0;
                            
            } 
        }          
        else if(gstYaSuoJiErrow.HighLevelTimeCnt >= _280MS_Per20MS)
        { 
            YaSuoJiErrowFlag = 0;
            
						if((gstYaSuoJiErrow.ErrorCodeData&0x07) > 0)
						{
								if(gstYaSuoJiErrow.FaultCnt >= _4Min_Per1S)
								{
										gstYaSuoJiErrow.ErrorCodeDisplayData = gstYaSuoJiErrow.ErrorCodeData|0xf0;
										YaSuoJiErrowDisplayFlag = 1;
										
								}
								gstYaSuoJiErrow.ErrorCodeData = 0;
								YaSuoJiErrowTimeCntFlag =  1;
								gstYaSuoJiErrow.HighLevelTimeCnt =0 ;
								gstYaSuoJiErrow.LowLevelTimeCnt = 0; 
						}
						else
						{
								Rest_YaSuoJiData();
						}
        }    
				else
				{
						Rest_YaSuoJiData();
				}
    }
    else
    {
       YaSuoJiErrowFlag = 0; //while(1);
			 gstYaSuoJiErrow.HighLevelTimeCnt =0 ;
       gstYaSuoJiErrow.LowLevelTimeCnt = 0; 
       gstYaSuoJiErrow.ErrorCodeData = 0;
    }

}




extern uint8_t __RTE_SetDidVIBData(uint8_t *databuf);
void CAN_22_2E_FillData(void)
{
	static u8 sDelayTime =0 ;
	gst22_2EMessage.func.Bit.RunState = SysRunFlag;
	gst22_2EMessage.func.Bit.LockStte = sysLock;
	gst22_2EMessage.func.Bit.HeatState = OpenHeatFlag>0?1:0;
	gst22_2EMessage.func.Bit.OzneState = OzoneFlag;
	gst22_2EMessage.func.Bit.DoorState =	PanelLostFlag?0:HuoErIO_Flag;
	gst22_2EMessage.TempValueSet = (HeatFlag>0)?gHeatCoolTemp.Bit.HeatTempSet:gHeatCoolTemp.Bit.CoolTempSet;
	gst22_2EMessage.RealTempValueSet = gTempAD;
	
	gst22_2EMessage.YaSuoJiErrowCode = gstYaSuoJiErrow.ErrorCodeDisplayData ;
	gst22_2EMessage.ErrowFunc.Bit.LostPanel = PanelLostFlag;
	gst22_2EMessage.ErrowFunc.Bit.TempState1 = Temp1SenseErrowFlag;
	gst22_2EMessage.ErrowFunc.Bit.TempState2 = Temp2SenseErrowFlag;
	gst22_2EMessage.ErrowFunc.Bit.HeatState = HeatErrowFlag;
	gst22_2EMessage.ErrowFunc.Bit.OzneState = (gstCANDtcCnt.OzneCnt > 3)?1:0;
	gst22_2EMessage.Wdata = ADtable[ADVin]*0.051*ADtable[ADHeatCool]*0.056	;
	gst22_2EMessage.SoftVersion = gHeatCoolTemp.Bit.HisEeprom;
	
	__RTE_SetDidVIBData((u8*)&gst22_2EMessage);
	
	if((gPwmDuty = 100)&&(gForceOutputFlag.Bit.b2 ||OpenHeatFlag))
	{
		if(sDelayTime == 0)
		{
				if(gstADCollect.HeatCurent < 1 || gstADCollect.HeatCurent > 8)
				{
					if(gstCANDtcCnt.HeatCnt <0xffff)
					{	
							gstCANDtcCnt.HeatCnt++;
					}
					if(gstADCollect.HeatCurent < 0  )
					{
							gstCANDtcCnt.HeatCnt = 0;
							sDelayTime = 200;
							gstADCollect.HeatCurent = 4;
					}
					
				}
				else
				{
					 gstCANDtcCnt.HeatCnt = 0;
				}
				//gst22_2EMessage.func.Bit.HeatState =		(gstCANDtcCnt.HeatCnt>3000)?1:0;
		
		}
		else
		{
				if(sDelayTime > 0 )
					sDelayTime--;

		}	
	}
	else
	{
			gstCANDtcCnt.HeatCnt = 0;
	}
	
	
		if( ChouTiCurentFlag )//7.2A ChouTiFlag
		{
			if(gstADCollect.ChouTiCurent  == 0)
			{
					return;
			}

			if(gstADCollect.ChouTiCurent < 1.5 || gstADCollect.ChouTiCurent > 8)
			{
					gst22_2EMessage.func.Bit.DoorState = 1;
					if(gstCANDtcCnt.DoorCnt<0xff)
						gstCANDtcCnt.DoorCnt++;
					
			}
			else				
			{
					gst22_2EMessage.func.Bit.DoorState = 0;
			}
		}
		else
		{
				gstCANDtcCnt.DoorCnt = 0;
		}

		
		if(gForceOutputFlag.Bit.b5 || OzoneFlag)
		{
			if(gstADCollect.OzneCurent < 5 || gstADCollect.OzneCurent > 100)
			{
					gst22_2EMessage.func.Bit.OzneState = 1;
					if(gstCANDtcCnt.OzneCnt<0xff)
						gstCANDtcCnt.OzneCnt++;
			}
			else				
			{
					gst22_2EMessage.func.Bit.OzneState = 0;
					//gstADCollect.OzneCurent = 0;
					gstCANDtcCnt.OzneCnt  = 0;
			}
		}
		else
		{
				gstCANDtcCnt.OzneCnt  = 0;
		}

		if((gForceOutputFlag.Bit.b4 || CoolFlag ||HeatFlag )&& HuoErIO_Flag)
		{
			if(gstADCollect.LEDCurent < 5 || gstADCollect.LEDCurent > 100)
			{
					gst22_2EMessage.ErrowFunc.Bit.LEDState = 1;
					if(gstCANDtcCnt.LedCnt <0xff)
						gstCANDtcCnt.LedCnt++;
			}
			else				
			{
					gst22_2EMessage.ErrowFunc.Bit.LEDState = 0;
					//gstADCollect.LEDCurent = 0;//gstADCollect.OzneCurent = 0;
					gstCANDtcCnt.LedCnt = 0;
			}
		}
		else
		{
				gstCANDtcCnt.LedCnt = 0;
		}
	
		if(gst22_2EMessage.YaSuoJiErrowCode > 0xf0)
		{
			if(gstCANDtcCnt.YaSuiJiCnt < 0xffff)
				gstCANDtcCnt.YaSuiJiCnt++;
		}
		else
		{
				gstCANDtcCnt.YaSuiJiCnt = 0;
		}
		
		if(gst22_2EMessage.ErrowFunc.Bit.LostPanel)
		{
			if(gstCANDtcCnt.lostPanaSingnalCnt < 0xff)
				gstCANDtcCnt.lostPanaSingnalCnt++; 
		}
		else
		{
				gstCANDtcCnt.lostPanaSingnalCnt = 0;
		}
		
		if(gst22_2EMessage.ErrowFunc.Bit.TempState1)
		{
			if(gstCANDtcCnt.Ntc1Cnt < 0xff)
				gstCANDtcCnt.Ntc1Cnt++;
		}
		else
		{
				gstCANDtcCnt.Ntc1Cnt = 0;
		}
		
		if(gst22_2EMessage.ErrowFunc.Bit.TempState2)
		{
			if(gstCANDtcCnt.Ntc2Cnt < 0xff)
				gstCANDtcCnt.Ntc2Cnt++;
		}
		else
		{
				gstCANDtcCnt.Ntc2Cnt = 0;
		}
}

void UartSingnalCollect(void)
{
	gUartSingnalCnt++;
	
	if(gUartSingnalCnt >= 40)
	{
			PanelLostFlag = 1;
			HuoErIO_Flag = 0;
	}
}
#define  CAN_YA_SUO_JI_MASK    0
#define  CAN_PanalSingnal_Lost 1

void DTCDataCollect(void)
{
	
		if(gstCANDtcCnt.YaSuiJiCnt > 3)
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_COMPRESSOR,__DTC_ERR);
		}   
		else 
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_COMPRESSOR,__RTE_DTC_NOR);
		}

		if(gstCANDtcCnt.lostPanaSingnalCnt > 3)
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_DISPLAY,__DTC_ERR);
		}		
		else
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_DISPLAY,__RTE_DTC_NOR);
		}
		
		if(gstCANDtcCnt.Ntc1Cnt > 100)
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_TEMPERATURE1,__DTC_ERR);
		}
		else
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_TEMPERATURE1,__RTE_DTC_NOR);
		}
		
		if(gstCANDtcCnt.Ntc2Cnt > 100)
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_TEMPERATURE2,__DTC_ERR);
		}
		else
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_TEMPERATURE2,__RTE_DTC_NOR);
		}
		
		if(gstCANDtcCnt.HeatCnt >= 150 )
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_HEATING,__DTC_ERR);
				//HeatFlag = 0;
				//SysRunFlag = 1 ;
				//KeyPower();
				//gstYaSuoJiErrow.ErrorCodeDisplayData = 0xf9;
				HeatErrowFlag = 1;

		}
		else
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_HEATING,__RTE_DTC_NOR);
		}
		
		if(gstCANDtcCnt.DoorCnt > 1)
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_DOOR,__DTC_ERR);
		}
		else
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_DOOR,__RTE_DTC_NOR);
		}
		
		if(gstCANDtcCnt.OzneCnt > 3)
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_OZONE_CTRL,__DTC_ERR);
		}
		else
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_OZONE_CTRL,__RTE_DTC_NOR);
		}
		
		if(gstCANDtcCnt.LedCnt > 3)
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_LIGHT,__DTC_ERR);
		}
		else
		{
				__RTE_UpdateDTC(__RTE_DTC_INDX_ERR_LIGHT,__RTE_DTC_NOR);
		}
}

void YaSuoJiProcess(void)
{
		static u8 sYaSuoJiFailCnt = 0;
		if(YaSuoJiErrowFlag)
    {
				sYaSuoJiFailCnt = 0;
        ReadYaSuoJiData();           
    }   
    else if(GetActiveSignal_YAJ == 0)
    {
				//sYaSuoJiFailCnt++;			
				//if(sYaSuoJiFailCnt > 2)
         YaSuoJiErrowFlag = 1;
    }
    else
    {
       gstYaSuoJiErrow.ErrorToNomalCnt++;
       if(gstYaSuoJiErrow.ErrorToNomalCnt == _4S_Per20MS)
       {
           gstYaSuoJiErrow.ErrorToNomalCnt = 0;                    
           YaSuoJiErrowDisplayFlag = 0;
				 Rest_YaSuoJiData();
       }
    }
}


/************************************************************************* 
* 函数名称:	TemCompasationProcess
* 功能说明:	温度补偿处理
* 输    入: 无	
* 输    出: 无
*************************************************************************/
void TemCompasationProcess(void)
{
	
	if(gstTempCompensation.PowerOnTimer <= 100)
	{
			gstTempCompensation.PowerOnTimer++;
	}
	
 if(!gstTempCompensation.Run.Bit.RunFlag )
				return;
	
//	if((gstTempCompensation.PowerOnTimer == 1)&&(!LMDConfigFlag))
//	{
////			LMD_Start();
//	}

		
//	if(gstTempCompensation.Run.Bit.RunFlag )
//	{
//			gstTempCompensation.RecoverTimer++;
//			if(gstTempCompensation.RecoverTimer > 5)
//			{
//					gstTempCompensation.RecoverTimer =0;
//					gstTempCompensation.Run.All  = 0 ;
//			}
//	}
	

			if(gstTempCompensation.RecoverTimer < 5)
			{
					gstTempCompensation.RecoverTimer++;
			}
			else
			{
					gstTempCompensation.Run.All  = 0 ;
					gstTempCompensation.mode = 0;
					ParameterRecoverFlag = 0;
					gHeatCoolTemp.Bit.EEpromRun = 1;
					SetValidJudgment();
			}
}






/************************************************************************* 
* 函数名称:	sysRuning
* 功能说明:	程序运行主体
* 输    入: 无	
* 输    出: 无
*************************************************************************/
void sysRuning(void)
{
	
		//static u8 time_1s_cnt =0;
    u8 canTestMessageTab[8] ={1,2,3,4,5,6,6,7};
		
		EventCollect();
    switch(PopEvent())
    {        
        case ev5MS:
						//sCnt++;
            BuzzerProcess();
						HeatPWM_ioProcess();
//						if( (sCnt%2) == 0)
//						{
//							sCnt = 0;
//							
//						}
						
        break;  
    
        case ev20MS:
        {
						TELProcess();
						CDCProcess();						
            YaSuoJiProcess();
						ADCollectProcess();	
        }				
        break;
				
        case ev50MS:
        {
						UartSingnalCollect();
						ForceOutput();						
            
            TemperatureCollect();          
            if(0 == gForceOutputFlag.Bit.b0)//force output mode inactive
						{
								KeyProcess();
								ChouTiMotor();
						}
						
        }
        break;
				
        case ev100MS:
        {
						FactoryProcess();
            KeyEnterFactory();
            DTCDataCollect();	
					 	ReadBusState_318();
						if(0 == gForceOutputFlag.Bit.b0)//force output mode inactive
						{
							LED_Process();
							CoolProcess();
							HeatProcess();
							AuxHeatProcess();
							
						}
						else//force output mode active
						{
							if(gForceOutputFlag.Bit.b1)
							{
								OpenYaSuoJi;
							}
							else
							{
								CloseYaSuoJi;
							}
							
							if(gForceOutputFlag.Bit.b2)
							{
								OpenHeat;
							}
							else
							{
								CloseHeat;
							}
							
							if(gForceOutputFlag.Bit.b4)
							{
								PINS_DRV_WritePin(PTD,2,1);//Orange LED on
								PINS_DRV_WritePin(PTD,3,1);//Blue LED on
							}
							else
							{
								PINS_DRV_WritePin(PTD,2,0);//Orange LED off
								PINS_DRV_WritePin(PTD,3,0);//Blue LED off
							}
						}
            
            SendDataDiaplay();
            EepromProcess();
        }
        break;
				
        case ev1S:
        {
//						time_1s_cnt++;
//						
//						if(time_1s_cnt == 3)
//						{
//								
//							LightAdjust();
//							time_1s_cnt = 0;
//						}
						YaSuoJiErrowTimeCnt();
						TemCompasationProcess();
						if(0 == gForceOutputFlag.Bit.b0)//force output mode inactive
						{
								HuoErIOProcess();
						}
							
						else 
						{
							if(gForceOutputFlag.Bit.b5)
							{
								OpenOzne_IO;
							}
							else
							{
								CloseOzne_IO;
							}
						}
					
						
        }
        break;
   
        default:
        break;
    }
}
