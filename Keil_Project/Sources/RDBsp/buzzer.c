
#include "buzzer.h"

#define _100ms_Per5ms 20
#define _30ms_Per5ms  2
#define BUZZER_0N  1
#define BUZZER_0FF 0

#define BUZZER_POWER_ON   	 PINS_DRV_WritePin(PTD,16,1)//FTM_DRV_CounterStart(0)//GPIO_PA10_Set()
#define BUZZER_POWER_OFF  	 PINS_DRV_WritePin(PTD,16,0)// FTM_DRV_CounterStop(0)//GPIO_PA10_Clear()
#define BUEEER_SetFrq(X)  	 ((FTM0)->MOD) = ((((FTM0)->MOD) & ~(0xFFFFu)) | (40000000/X));((FTM0)->SYNC) = ((((FTM0)->SYNC) & ~(0x80)) | (0x80))//FTM_DRV_UpdatePwmPeriod(0,0,X,0)// {}//TCC1t_PWM24bitPeriodSet(X)
#define BUEEER_SetDuty_ON()    (FTM0)->CONTROLS[0].CnV = 0xF55;										((FTM0)->SYNC) = ((((FTM0)->SYNC) & ~(0x80)) | (0x80))//FTM_DRV_UpdatePwmChannel(0, 0U, 0U, X*0x4000U, 0U, true);  //(FTM0)->CONTROLS[0].CnV = 0x2000;
#define BUZZER_Stop   	        (FTM0)->CONTROLS[0].CnV = 0x0000;((FTM0)->SYNC) = ((((FTM0)->SYNC) & ~(0x80)) | (0x80))////FTM_DRV_UpdatePwmChannel(0, 0U, 0U, 0U, 0U, true);//FTM_DRV_DeinitPwm(0)//
#define BUEEER_SetDuty_OFF()    (FTM0)->CONTROLS[0].CnV = 0x2000;										((FTM0)->SYNC) = ((((FTM0)->SYNC) & ~(0x80)) | (0x80))//FTM_DRV_UpdatePwmChannel(0, 0U, 0U, X*0x4000U, 0U, true);  //(FTM0)->CONTROLS[0].CnV = 0x2000;

typedef struct
{
    uint32_t frq;
    uint16_t OpenTime;
    uint16_t CloseTime;
}ST_Buzzer;

typedef struct
{
    uint16_t OpenTime;
    uint16_t CloseTime;
    uint8_t   step;
}ST_BuzzerCanShu;

#define Buzzer0N_SingalKey 3400

ST_Buzzer stBuzzerTab[] =
{
		{1900    ,50,120},
		{2400    ,50,120},
		{2900    ,50,120},
		{3400    ,50,1200},
    {0xffffff   ,0xffff,0xffff}               
};


ST_Buzzer stBuzzerTab1[] =
{
		{3400    ,50,120},
    {2900    ,50,120},
		{2400    ,50,120},
		{1900    ,50,1200},
    {0xffffff   ,0xffff,0xffff}
};
////tong suo
ST_Buzzer stBuzzerTab2[] =
{
    {3400    ,50,120},
    {2900    ,50,120},
		{2400    ,50,120},
		{3400    ,50,120},
    {2900    ,50,120},
		{2400    ,50,1500},
    {0xffffff   ,0xffff,0xffff}
};

ST_Buzzer stBuzzerTab31[] =
{
    {1900    ,50,120},
		{2400    ,50,120},
		{2900    ,50,120},
		{1900    ,50,120},
		{2400    ,50,120},
		{2900    ,50,120},
		{1900    ,50,120},
		{2400    ,50,120},
		{2900    ,50,1200},
    {0xffffff   ,0xffff,0xffff}
};
///////////////////ZhiLeng
ST_Buzzer stBuzzerTab32[] =
{
    {Buzzer0N_SingalKey    ,100,1500},//2.0K
    {0xffffff   ,1500,0xffff}
};
///////////////////JianAnJian
ST_Buzzer stBuzzerTab33[] =
{
    {Buzzer0N_SingalKey    ,100,1500},//2.0K
    {0xffffff   ,0xffff,0xffff}
};

///////////////////JiaAnJian
ST_Buzzer stBuzzerTab34[] =
{
    {Buzzer0N_SingalKey    ,100,1500},//2.0K
    {0xffffff   ,0xffff,0xffff}
};

///////////////////jiaRe
ST_Buzzer stBuzzerTab35[] =
{
    {Buzzer0N_SingalKey    ,100,1500},//2.0K
    {0xffffff   ,0xffff,0xffff}
};

///////////////////chouTi 
ST_Buzzer stBuzzerTab36[] =
{
    {1700    ,90,90},//1760 6 la
    {2300    ,50,1500},//1560 5 suo
    {0xffffff   ,0xffff,0xffff}
};



uint8_t  BuzzerStart(ST_Buzzer  *stBuzzerTab, uint16_t  *stimeOpenPower,uint16_t  *stimeClosePower,uint8_t * step)
{
    static float  voliceNum = 0.25;
		static uint32_t HisFrq;
		static float HisDuty;

	  if(*step == 0xff)
    {
        return 1;
    }
    
    if(*stimeOpenPower < stBuzzerTab[*step].OpenTime * 0.2)
    {
			  BUZZER_POWER_ON; 
				if(stBuzzerTab[*step].frq != HisFrq)
				{
						HisFrq = stBuzzerTab[*step].frq ;
						BUEEER_SetFrq(stBuzzerTab[*step].frq);
				}
				
			  if(voliceNum != HisDuty)
				{
						HisDuty = voliceNum;
						BUEEER_SetDuty_ON();
				}
        (*stimeOpenPower)++;

    }
    else if(*stimeClosePower < stBuzzerTab[*step].CloseTime * 0.2)
    {
        BUZZER_POWER_OFF;
				if(voliceNum != HisDuty)
				{
						HisDuty = voliceNum;
						BUEEER_SetDuty_OFF();
				}
        (*stimeClosePower)++;
    }
    else
    {
        (*step)++;
        *stimeOpenPower = 0;
        *stimeClosePower = 0;
        
        if(stBuzzerTab[*step].frq == 0xfffffful)
        {
            *step = 0xff;
						HisDuty = 0;
            BUZZER_Stop;
            return 1;
        }        
    }
    return 0;

}

void BuzzerProcess(void)
{
    static ST_Heat sBuzzerDelay;
    static uint8_t  voliceNum;
    static uint16_t  sstimeOpenPower;
    static uint16_t  sstimeClosePower;
    static uint8_t   sstep;
 
    if( BuzzerFlag || gbFlagData[5].all > 0)
    {

        sBuzzerDelay.Bit.run = 1;
    
        
        if(BuzzerPowerOnFlag)
        {
            voliceNum = 1;
        }
            
        else if(BuzzerPowerOffFlag)
        {
            voliceNum = 2;
        }
            
        else if(BuzzerFlag)
        {
            voliceNum = 3;
        }
        
        else if(Buzzer1Flag)
        {
            voliceNum = 31;
        }
        else if(Buzzer2Flag)
        {
            voliceNum = 32;
        }
        else if(Buzzer3Flag)
        {
            voliceNum = 33;
        }
        else if(Buzzer4Flag)
        {
            voliceNum = 34;
        }
        else if(Buzzer5Flag)
        {
            voliceNum = 35;
        }
        else if(Buzzer6Flag)
        {
            voliceNum = 36;
        }
        BuzzerFlag = 0;
        gbFlagData[5].all = 0;
        
        sstep = 0;
        sstimeOpenPower = 0;
        sstimeClosePower = 0;
    }
    if(sBuzzerDelay.Bit.run)
    {
        if(voliceNum == 1)
        {
            if(BuzzerStart(stBuzzerTab,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
        else if(voliceNum == 2)
        {
            if(BuzzerStart(stBuzzerTab1,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
        
        else if(voliceNum == 3)
        {
            if(BuzzerStart(stBuzzerTab2,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
        
        else if(voliceNum == 31)
        {
            if(BuzzerStart(stBuzzerTab31,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
        else if(voliceNum == 32)
        {
            if(BuzzerStart(stBuzzerTab32,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
        else if(voliceNum == 33)
        {
            if(BuzzerStart(stBuzzerTab33,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
        
        else if(voliceNum == 34)
        {
            if(BuzzerStart(stBuzzerTab34,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
        
        else if(voliceNum == 35)
        {
            if(BuzzerStart(stBuzzerTab35,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
        
        else if(voliceNum == 36)
        {
            if(BuzzerStart(stBuzzerTab36,&sstimeOpenPower,&sstimeClosePower,&sstep)==1)
            {
                sBuzzerDelay.Bit.run = 0;
            }
        }
    }
    else
    {
            BUZZER_Stop;
    }
}
