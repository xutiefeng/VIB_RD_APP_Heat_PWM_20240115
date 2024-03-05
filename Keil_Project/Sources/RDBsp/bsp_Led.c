#include "bsp_Led.h"






void LED_ForceOutput(u8 v)
{
		if(v == 1)
		{
				Led_Blue_(1);
				Led_Orange_(0);
		}
		else if(v == 2)
		{
				Led_Blue_(0);
				Led_Orange_(1);
		}
		else
		{
				Led_Blue_(0);
				Led_Orange_(0);
		}
			 
}



	
void LED_Process(void)
{
		static uint8_t LEDCnt = 0;
		if(RDFactoryTestFlag)
					return;
		
    if(!HuoErIO_Flag)
    {
				LEDCnt++;
			
				if(LEDCnt > 30)
				{
						Led_Blue_(0);
						Led_Orange_(0);
				}
        
    }
    else if(CoolFlag && SysRunFlag)
    {
				LEDCnt = 0;
        Led_Blue_(1);
        Led_Orange_(0);
    }
    else if(HeatFlag && SysRunFlag)
    {
				LEDCnt = 0;
        Led_Blue_(0);
        Led_Orange_(1);
    }
    else
    {
				LEDCnt = 0;
        Led_Blue_(1);
        Led_Orange_(1);
    }
}