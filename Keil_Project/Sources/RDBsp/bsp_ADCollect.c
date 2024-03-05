#include "globe.h"
#include  "bsp_ADCollect.h"
#include "FuncTab.h"//#include "config/default/peripheral/adc/plib_adc0.h"


uintptr_t adc_context;

#define AD_TO_SELECT_TOP  {}//sADcnt= 0; \
                          //ADC0_ChannelSelect(ADC_POSINPUT_AIN0,ADC_NEGINPUT_AIN0)


#define ADCHANAL_GetValue     0//ADC0_ConversionResultGet()
#define ADCHANAL_Select(X)    0//ADC0_ChannelSelect(ADC_POSINPUT_AIN##X,ADC_NEGINPUT_AIN##X); 
	
	
#define AD_COLLECT_ENABLE  {}//ADC0_Enable() 
#define AD_COLLECT_DIASBLE {}//ADC0_Disable()	
	
#define AD_CallBACK        {}//ADC0_CallbackRegister(ADC0_CallBack, adc_context)
#define AD_StartConver     {}//ADC0_ConversionStart()
	
#define ADXiShu 0.056	
float GetInputVoltage(void)
{
	return gstADCollect.PowerVoltage;
}
	
 
/************************************************************************* 
* 函数名称:	sysRuning
* 功能说明:	(gAD_Value[0]/4096)*5.2*10 = 52/4096 = 0.0126953125
* 功能说明:	
* 输    入: 无	
* 输    出: 无
*************************************************************************/


#define __HeatTemperatureCompensation  TemprertureTab[9].CompensationValue

//static 
 
unsigned char gTempAD_Cnt;

//u16 adc_value_max = 0;
//u16 adc_value_min = 0xffff;

u16 gTempAD_Ntc1,gTempAD_Ntc2;

u16 gAD_HeatCoolCurent;
u16 gADLedCurent;
u16 gADOzneCurent;
u16 gADVin;
//unsigned int adc_sum = 0;

#define ADAverage_CH_Num ADMax

typedef struct
{
		u16 adc_value_max[ADAverage_CH_Num];
		u16 adc_value_min[ADAverage_CH_Num];
		u32 adc_sum[ADAverage_CH_Num];

}ST_AD_Aversage;
 
ST_AD_Aversage volatile gstAD_Aversage
={
		{0,0,0,0,0,0},
		{0xffffU,0xffffU,0xffffU,0xffffU,0xffffU,0xffffU},
		{0,0,0,0,0,0}
 };

unsigned int adc_get_average(unsigned short ch,BSP_ADChangeEnum num)            
{
  
  
  unsigned int adc_current = 0;
 
  
  if(gTempAD_Cnt <= 10*ADAverage_CH_Num)//for(gTempAD_Cnt = 0;gTempAD_Cnt<10;gTempAD_Cnt++)
  {
		gTempAD_Cnt++;
    adc_current = ch;
    if(adc_current > gstAD_Aversage.adc_value_max[num])
    {
      gstAD_Aversage.adc_value_max[num] = adc_current;
    }
    if(adc_current < gstAD_Aversage.adc_value_min[num])
    {
      gstAD_Aversage.adc_value_min[num] = adc_current;
    }
    gstAD_Aversage.adc_sum[num] += adc_current;
		
		
  }
  if(gTempAD_Cnt >= 10*ADAverage_CH_Num)
	{
			return 1;
	}
	else
	{
			return 0;
	}
  
}

void GetavergeADValue(void)
{
	
	 u8 i;
	 if(gTempAD_Cnt >= 10*ADAverage_CH_Num)
	 {
			for(i= 0; i < ADAverage_CH_Num;i++)
			{
					gstAD_Aversage.adc_sum[i] -=  gstAD_Aversage.adc_value_min[i];
					gstAD_Aversage.adc_sum[i] -=  gstAD_Aversage.adc_value_max[i];
					gstAD_Aversage.adc_sum[i] = gstAD_Aversage.adc_sum[i]>>3;
					if(i == ADntc1)
					{
							gTempAD_Ntc1 = gstAD_Aversage.adc_sum[i];
					}
					else if(i == ADntc2)
					{
							gTempAD_Ntc2 = gstAD_Aversage.adc_sum[i];
					}
					
					else if(i == ADVin)
					{
							gADVin = gstAD_Aversage.adc_sum[i];
					}
					
					else if(i == ADled)
					{
							gADLedCurent = gstAD_Aversage.adc_sum[i];
					}
					
					else if(i == ADHeatCool)
					{
							gAD_HeatCoolCurent = gstAD_Aversage.adc_sum[i];
					}
					
					else if(i == ADOzne)
					{
							gADOzneCurent = gstAD_Aversage.adc_sum[i];
					}
					
					gstAD_Aversage.adc_sum[i] = 0;
					gstAD_Aversage.adc_value_min[i] = 0XFFFFUL;
					gstAD_Aversage.adc_value_max[i] = 0;
					gTempAD_Cnt = 0;
			}
		}
}



void TemperatureCollect(void)
{
       uint8_t i;
       uint16_t temp;
				
				
			//////////////////////////////////////////////
//			gTempAD_Ntc1  = 40;
//			gTempAD_Ntc2  = 40;
			//////////////////////////////////////////////
				
//			if(gTempAD_Ntc1 == 0 || gTempAD_Ntc2 == 0)
//			{
//						return;
//			}
				
       if(gTempAD_Ntc1>= ADMAX /* 开路 */ || gTempAD_Ntc1 <= ADMIN /* 对应100摄氏度 */ )//if(ADtable[ADntc1] >= ADMAX /* 开路 */ || ADtable[ADntc1] <= ADMIN /* 对应100摄氏度 */ )
       {
            Temp1SenseErrowFlag = 1;
       }
			 else
			 {
						Temp1SenseErrowFlag = 0;
			 }
			 
       
       if(gTempAD_Ntc2 >= ADMAX /* 开路 */  || gTempAD_Ntc2 <= ADMIN /* 对应100摄氏度 */ )
       {
            Temp2SenseErrowFlag = 1;
						
       }
			 else
			 {
						Temp2SenseErrowFlag = 0;
			 }
			 
       if(gTempAD_Ntc1 < ADMAX /* 开路 */  && gTempAD_Ntc1 >  ADMIN /* 对应100摄氏度 */  )
       {
            temp =  gTempAD_Ntc1;//temp = ADtable[ADntc1];
						ALLTempSenseErrowFlag= 0;
       }
       else if(gTempAD_Ntc2 < ADMAX /* 开路 */  && gTempAD_Ntc2 >  ADMIN /* 对应100摄氏度 */  )
       {
           temp =  gTempAD_Ntc2;//temp = ADtable[ADntc2];
						ALLTempSenseErrowFlag= 0;
       }
       else
       {
           ALLTempSenseErrowFlag  =1;
       }
       
    
         for(i=0; i<= 140; i++)
         {
            if(temp  > TempTab[i])//if(temp*0.98  > TempTab[i])
            {
                break;
            }
         }
         
        gTempAD = i-40;
				 
        if(CoolFlag)
        {
            
            if(gHeatCoolTemp.Bit.CoolTempSet < -9)
            {
                gTempAD += TemprertureTab[8].CompensationValue;
            }
            else if(gHeatCoolTemp.Bit.CoolTempSet >= -9 && gHeatCoolTemp.Bit.CoolTempSet < 0)
            {
                gTempAD += TemprertureTab[7].CompensationValue;
            }

            else
            {
                gTempAD += TemprertureTab[6].CompensationValue;
            }
        }
        
        if(HeatFlag)
        {      
            //if(gTempAD >= 35)
						//{
						gTempAD += __HeatTemperatureCompensation;
						//}               
        }
       
}

void ADPowerColect(void)
{
		static  u16  sADcnt =0;
		//adc_get_average(ADtable[ADntc2],ADntc2);
    gstADCollect.PowerVoltage = gADVin/*ADtable[ADVin]*/*ADXiShu;//0.013432;
    if(gstADCollect.PowerVoltage <= 8.5 || gstADCollect.PowerVoltage >= 17)
    {
				if(sADcnt< 0xffFFU)
					sADcnt++;
				
				if(sADcnt > 6000 || (gstYaSuoJiErrow.ErrorCodeDisplayData == 0xf1 && YaSuoJiErrowDisplayFlag))
					AbnormalPowerFlag = 1;	
    }
		else if(gstADCollect.PowerVoltage >= 10.9)
		{
				AbnormalPowerFlag = 0;
				sADcnt = 0;
		}
	

}

void ADHeatCollCollect(void)
{
		if(gAD_HeatCoolCurent == 0 || ChouTiFlag)
		{
				return ;
		}
		
    if(CoolFlag)
    {
				gstADCollect.HeatCurent = 0;
        gstADCollect.CoolCurent = gAD_HeatCoolCurent*0.051;// ADtable[ADHeatCool]*0.051;//1.3432;		
    }
    else if(HeatFlag)
    {
				gstADCollect.CoolCurent = 0;
        gstADCollect.HeatCurent = gAD_HeatCoolCurent*0.051;//ADtable[ADHeatCool]*0.051;//1.3432;
    }
}

void ADDoorCollect(void)
{
		if(gAD_HeatCoolCurent == 0)
		{
				return ;
		}
		
	  //gstADCollect.CoolCurent = 0;
		//gstADCollect.HeatCurent = 0;
    if(ChouTiCurentFlag)
    {

			gstADCollect.ChouTiCurent = /*ADtable[ADHeatCool]*/gAD_HeatCoolCurent*0.051;

			if(CoolFlag)
					gstADCollect.ChouTiCurent -=gstADCollect.CoolCurent;
		  else if(HeatFlag)
				gstADCollect.ChouTiCurent -=gstADCollect.HeatCurent;
    }
		
			
		
}



void ADLedCollect(void)
{
			gstADCollect.LEDCurent = ADtable[ADled]* 0.9957 ;//(5.2 *1000)/ (5100*1024) ma
}

void ADOzneCollect(void)
{
		gstADCollect.OzneCurent  = ADtable[ADOzne]*0.9957;
}

void ADCollectProcess(void)
{
	
		adc_get_average(ADtable[ADntc1],ADntc1);
		adc_get_average(ADtable[ADntc2],ADntc2);
		adc_get_average(ADtable[ADVin] ,ADVin);
		adc_get_average(ADtable[ADled],ADled);
		adc_get_average(ADtable[ADHeatCool],ADHeatCool);
		adc_get_average(ADtable[ADOzne],ADOzne);
		GetavergeADValue();
//		if(gstADCollect.LEDCurent == 0)
//		{
//				GetavergeADValue();
//		}
    ADPowerColect();
    ADDoorCollect();
    ADHeatCollCollect();
		ADLedCollect();
		ADOzneCollect();
    AD_COLLECT_ENABLE;
}