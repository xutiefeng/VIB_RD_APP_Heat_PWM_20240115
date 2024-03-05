#include "bsp_Led.h"


#define Led_Orange_(x)  {}//TCC0_PWM24bitDutySet(TCC0_CHANNEL3, x)
#define Led_Blue_(x)  {}//TCC0_PWM24bitDutySet(TCC0_CHANNEL3, x)

void LED_Process(void)
{
    if(!HuoErIO_Flag)
    {
        Led_Blue_(0);//TCC0_PWM24bitDutySet(TCC0_CHANNEL3, 0);     //ice blue
        Led_Orange_(0);//TCC0_PWM24bitDutySet(TCC0_CHANNEL2, 0);     //orange
    }
    else if(CoolFlag)
    {
        Led_Blue_(2000);//TCC0_PWM24bitDutySet(TCC0_CHANNEL3, 2000);  //ice blue
        Led_Orange_(0);//TCC0_PWM24bitDutySet(TCC0_CHANNEL2, 0);     //orange
    }
    else if(HeatFlag)
    {
        Led_Blue_(0);//TCC0_PWM24bitDutySet(TCC0_CHANNEL3, 0);     //ice blue
        Led_Orange_(2000);//TCC0_PWM24bitDutySet(TCC0_CHANNEL2, 2000);  //orange
    }
    else
    {
        //TCC0_PWM24bitDutySet(TCC0_CHANNEL3, 0);     //ice blue
        //TCC0_PWM24bitDutySet(TCC0_CHANNEL2, 0);     //orange
    }
}