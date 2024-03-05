#ifndef CONGIG_H
#define CONGIG_H

#include  "globe.h"
#include  "bsp_ADCollect.h"
#include  "buzzer.h"


//#define OpenYaSuoJi  OpenYaSuoJiFlag =1 ;GPIO_PA28_Clear();GPIO_PA23_Set();
//#define CloseYaSuoJi OpenYaSuoJiFlag =0; GPIO_PA23_Clear();
//#define OpenHeat     OpenHeatFlag =1;    GPIO_PA23_Clear(); GPIO_PA28_Set();
//#define CloseHeat    OpenHeatFlag =0;    GPIO_PA28_Clear();

#define  TEMP_SET_VALUE   (50+TemprertureTab[6].CompensationValue)

typedef enum
{
    evReceivecmp = 0,
    evReceiveBMS,
    evReceiveDisplay,
    evReceiveZhuoDu,
    evSysRest = 10,
    evNoKeyProcess,
    evKeyPower,
    evCleanMode,
    evVoiceSwitch,
    evKeyLackWater,
    evAuto,
    evAuto3,
    evAuto4,
    ev5MS,
    ev20MS,
    ev50MS ,
    ev100MS,
    ev1S,
}Evnt_t;

typedef enum
{
	BingXianMode =1,
	LengYinMode,
	GuoShuMode,
	
	WenNaiMode =11,
	WenFanMode,
}ST_CurMode;

typedef enum
{
	Heat_temp  =1,
	///LengYinMode//,
	//GuoShuMode,
	
	//WenNaiMode =11,
	//WenFanMode,
}UT_Temp;


#define  CINGIG_SYSLOCK 0

#define COOLTEMPMin  TemprertureTab[0].CompensationValue//0//-20
#define COOLTEMPMax  TemprertureTab[1].CompensationValue//15

#define HEATEMPMin  TemprertureTab[2].CompensationValue//38
#define HEATEMPMax  TemprertureTab[3].CompensationValue//55

#define KEY_CHOU_TI_DealyTime     32//16*2
#define KEY_CHOU_TI_DealyTime_2   300//150*2

#define  CoolSuDongFlag				 		 							gbFlagData[0].Bit.b7 
#define  OpenAuxHeatFlag                        gbFlagData[0].Bit.b6 
#define  OpenHeatFlag                           gbFlagData[0].Bit.b5
#define  OpenYaSuoJiFlag                        gbFlagData[0].Bit.b4 
#define  RealTimeDisplayFlag										gbFlagData[0].Bit.b3 
#define  RDFactoryTestFlag                      gbFlagData[0].Bit.b2  
#define  EvRecvFlag                      				gbFlagData[0].Bit.b1 
#define  SysRunFlag                        			gbFlagData[0].Bit.b0

#define  ALLTempSenseErrowFlag					 			  gbFlagData[1].Bit.b0  
#define  OzoneRunFlag                   				gbFlagData[1].Bit.b1 
#define  ChouTiOutputHoldFlag                   gbFlagData[1].Bit.b2 
#define  ChouTiFlag     												gbFlagData[1].Bit.b3 
#define  HeatFlag   														gbFlagData[1].Bit.b4 
#define  CoolFlag																gbFlagData[1].Bit.b5 
#define  RecveFlag                              gbFlagData[1].Bit.b6 
#define  OzoneFlag                              gbFlagData[1].Bit.b7 


#define  TempSetFlag                            gbFlagData[2].Bit.b1 
#define  YaSuoJiErrowTimeCntFlag								gbFlagData[2].Bit.b2 
#define  MoodeSetFlag                      	    gbFlagData[2].Bit.b3 
#define  ChouTiCurentFlag						   					gbFlagData[2].Bit.b4 
#define  YaSuoJiErrowDisplayFlag                gbFlagData[2].Bit.b5 
#define  YaSuoJiErrowFlag												gbFlagData[2].Bit.b6 
#define  HeatErrowFlag 													gbFlagData[2].Bit.b7


#define  BuzzerFlag                             gbFlagData[3].Bit.b1 
#define  ShuiBengLevel_3												gbFlagData[3].Bit.b2 
#define  MainMotoeLevel_1												gbFlagData[3].Bit.b3 
#define  MainMotoeLevel_2												gbFlagData[3].Bit.b4 
#define  DiShuaMotoeLevel_1                     gbFlagData[3].Bit.b5 
#define  DiShuaMotoeLevel_2                     gbFlagData[3].Bit.b6 
#define  LowPowerBeepFlag												gbFlagData[3].Bit.b7 

#define  SysOffDelayFlag												gbFlagData[4].Bit.b0 
#define  ParameterRecoverFlag										gbFlagData[4].Bit.b1 
#define  AbnormalPowerFlag											gbFlagData[4].Bit.b2 
#define  AiKaiOzneTestFlag											gbFlagData[4].Bit.b3
#define  DayAndNightFlag											  gbFlagData[4].Bit.b4
#define  MinusKeyFlag                      			gbFlagData[4].Bit.b5 
//#define  CoolFlag_FromEEprom                    gbFlagData[4].Bit.b6 

#define  Buzzer1Flag                            gbFlagData[5].Bit.b0 
#define  Buzzer2Flag                            gbFlagData[5].Bit.b1 
#define  Buzzer3Flag                            gbFlagData[5].Bit.b2 
#define  Buzzer4Flag                            gbFlagData[5].Bit.b3 
#define  Buzzer5Flag                            gbFlagData[5].Bit.b4 
#define  Buzzer6Flag                            gbFlagData[5].Bit.b5 
#define  BuzzerPowerOnFlag                      gbFlagData[5].Bit.b6 
#define  BuzzerPowerOffFlag                     gbFlagData[5].Bit.b7 



#define  Temp1SenseErrowFlag     								gbFlagData[6].Bit.b0 
#define  Temp2SenseErrowFlag										gbFlagData[6].Bit.b1 
#define  DoorErrowFlag                          gbFlagData[6].Bit.b2 
#define  sysLock                            		gbFlagData[6].Bit.b3 
#define  CoolErrowFlag                      		gbFlagData[6].Bit.b4  
#define  OzneErrowFlag                          gbFlagData[6].Bit.b5 
#define  LedErrowFlag                           gbFlagData[6].Bit.b6 
#define  ManelErrowFlag                         gbFlagData[6].Bit.b7 
//#define  HeatErrowFlag                          gbFlagData[6].Bit.b3  



#define  HuoErIO_Flag                           gbFlagData[7].Bit.b0 
#define  Pause_Flag                         	  gbFlagData[7].Bit.b1 
#define  AKFactoryTestFlag                      gbFlagData[7].Bit.b2 
#define  AKFinishTestFlag                       gbFlagData[7].Bit.b3 
#define  VoiceSetFlag                       		gbFlagData[7].Bit.b4
#define  LMDConfigFlag                         	gbFlagData[7].Bit.b7 


#define  PanelLostFlag                          gbFlagData[8].Bit.b0
#define  RDFactoryModeFlag                      gbFlagData[8].Bit.b1 
#define  RDFactoryUartFlag                      gbFlagData[8].Bit.b2 
#define  CANTestFlag                            gbFlagData[8].Bit.b3 
#define  LinMingDuFlag                          gbFlagData[8].Bit.b4 
#define  CoolFlag_FromEEprom										gbFlagData[8].Bit.b5 
#define  HisVCU_VIBPwrOff                       gbFlagData[8].Bit.b5 

#define  Ev100MSFlag                            gbFlagData[9].Bit.b0 
#define  Ev20MSFlag                             gbFlagData[9].Bit.b1 
#define  Ev50MSFlag                             gbFlagData[9].Bit.b2 
#define  Ev1SFlag                               gbFlagData[9].Bit.b3 
#define  Ev5MSFlag                              gbFlagData[9].Bit.b4

//////////////////////////////???????? ///////////////////////////////////////////////

#define  LED1_DisplayFlag                           gSendData[0].Bit.b0 //led power
#define  LED2_DisplayFlag                           gSendData[0].Bit.b1 //led cool white
#define  LED9_DisplayFlag                           gSendData[0].Bit.b2 //led cool blue
#define  LED10_DisplayFlag                          gSendData[0].Bit.b3 //led minus
#define  LED11_DisplayFlag                          gSendData[0].Bit.b4 //led add
#define  LED12_DisplayFlag                          gSendData[0].Bit.b5 //led heat white
#define  LED13_DisplayFlag                          gSendData[0].Bit.b6 //led heat orange
#define  LED14_DisplayFlag                          gSendData[0].Bit.b7 //led push motor

#define  LED15_DisplayFlag                      	 gSendData[1].Bit.b0 //led lock
#define  LED16_DisplayFlag                      	 gSendData[1].Bit.b1 //led lock
#define  SysRun_DisplayFlag                      	 gSendData[1].Bit.b2 
#define  ErrowCodeFlag                             gSendData[1].Bit.b3
#define  HeatSuReDisplayFlag                       gSendData[1].Bit.b4
#define  CoolSuDongDisplayFlag                     gSendData[1].Bit.b5

#define  CANRLostFlag                      				 gSendData[1].Bit.b6
#define  DisplayPanelLostFlag                      gSendData[1].Bit.b7
#define  HEX_DISPLAY ErrowCodeFlag 
#define	 ChouTiMotorTime													 8

#define LED_ON  0
#define LED_OFF 1


#if 1 
  #define OpenYaSuoJi OpenYaSuoJi_1()			
#else
#define OpenYaSuoJi  OpenYaSuoJiFlag =1; OpenHeatFlag =0; PINS_DRV_WritePin(PTA,13,1)//PINS_DRV_WritePin(PTC,6,1)
#define CloseYaSuoJi OpenYaSuoJiFlag =0;  PINS_DRV_WritePin(PTA,13,0)//PINS_DRV_WritePin(PTC,6,0)

#define OpenYaSuoJi  OpenYaSuoJiFlag =1; OpenHeatFlag =0;\
				if(!DayAndNightFlag)\
				{\
					PINS_DRV_WritePin(PTA,13,1);PINS_DRV_WritePin(PTC,6,0);\
				}\
				else\
				{\
					PINS_DRV_WritePin(PTC,6,1),PINS_DRV_WritePin(PTA,13,0);\
				}\

#endif				 
					
#define CloseYaSuoJi OpenYaSuoJiFlag =0;  PINS_DRV_WritePin(PTA,13,0),PINS_DRV_WritePin(PTC,6,0)

//#define  HisVCU_VIBPwrOff                       gHeatCoolTemp.Bit.HisPwrOFF				
				

#define OpenYaSuoJi_T2  OpenYaSuoJiFlag =1; OpenHeatFlag =0; PINS_DRV_WritePin(PTC,6,1),PINS_DRV_WritePin(PTA,13,0)
#define CloseYaSuoJi_T2 OpenYaSuoJiFlag =0;  PINS_DRV_WritePin(PTC,6,0)

#define OpenHeat     OpenHeatFlag =1;  OpenYaSuoJiFlag =0; 	 //PINS_DRV_WritePin(PTA,0,1)
#define OpenAuxHeat     OpenAuxHeatFlag =1;  OpenYaSuoJiFlag =0;  PINS_DRV_WritePin(PTB,0,1)
#define CloseHeat       OpenHeatFlag =0;    PINS_DRV_WritePin(PTA,0,0)
#define CloseAuxHeat    OpenAuxHeatFlag =0;    PINS_DRV_WritePin(PTB,0,0)
#define GetActiveSignal_YAJ               ((PINS_DRV_ReadPins(PTC)&0X80U))  //CloseAuxHeat
#define TestPointTringer_1             		(PINS_DRV_ReadPins(PTA)&0X80U)//
#define TestPointTringer_2             		(PINS_DRV_ReadPins(PTC)&0X0200U)
#define  ChouTiMotor_set     PINS_DRV_WritePin(PTA,1,1)
#define  ChouTiMotor_clr     PINS_DRV_WritePin(PTA,1,0)
#define  OpenOzne_IO         PINS_DRV_WritePin(PTD,5,1)//PINS_DRV_WritePin(PTB,1,1)
#define  CloseOzne_IO        PINS_DRV_WritePin(PTD,5,0)//PINS_DRV_WritePin(PTB,1,0)
#define  EEPROM_REDY  			 gHeatCoolTemp.Bit.EEpromRun =1;

#define	SRC_Config                          0x80
#define	Display_config                      0x40

#define ADMAX 1010//1000
#define ADMIN 18//20


#define Led_Orange_(x)  PINS_DRV_WritePin(PTD,2,x)//{}//TCC0_PWM24bitDutySet(TCC0_CHANNEL3, x)
#define Led_Blue_(x)    PINS_DRV_WritePin(PTD,3,x)//{}//TCC0_PWM24bitDutySet(TCC0_CHANNEL3, x)

#define Led_RED4_(x)    ;//PINS_DRV_WritePin(PTA,4,x)
#define Led_RED5_(x)    ;//PINS_DRV_WritePin(PTC,4,x)
#define Led_RED6_(x)    ;//PINS_DRV_WritePin(PTA,10,x)
#define Led_RED7_(x)    ;//PINS_DRV_WritePin(PTC,5,x)


#endif
