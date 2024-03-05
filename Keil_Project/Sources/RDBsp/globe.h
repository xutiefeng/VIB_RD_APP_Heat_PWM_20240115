#ifndef GLOBLE_H
#define GLOBLE_H

#include "includeall.h"
#include "device_registers.h"           /* Device header */
//#include "cmsis_os2.h"                  /* ::CMSIS:RTOS2 */
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "config.h"


//#define  TAB_ISUM(tab)              (sizeof(tab)/sizeof(tab[0]))

#define Byte8	byte
#define u8	unsigned char
#define u16	unsigned short
#define Uchar	unsigned char
#define u32	unsigned int
#define EVENT_BUFFER_LENGTH  20


typedef enum
{
    ADntc1,
    ADntc2,
    ADVin,
	  ADled,
    ADHeatCool,
		
		ADOzne,
    ADMax 
}BSP_ADChangeEnum;

typedef enum
{
		TEL,
		CDC
}CanMessageType;


//typedef union
//{

//		u8	all;
//    struct
//    {
//        u8 CurMode          :4;     
//    }Bit;
//}STDisplayCode;

typedef struct
{

	 u8 dis1  ;
	 u8 dis2  ;
	 u8 dis3  ;
	 u8 CurMode;
	
}STDisplayCode;

typedef struct 
{
    float   PowerVoltage;
    float 	CoolCurent;
    float 	HeatCurent;
    float		ChouTiCurent;
		float 	LEDCurent;
		float 	OzneCurent;
}STAD_Collect;

typedef struct 
{
		uint8_t  FaultCnt;
    uint8_t  ErrorCodeDisplayData;  
    uint8_t  ErrorToNomalCnt;
    uint8_t  ErrorCodeData;
    uint8_t  YSJErrowCnt;    
    uint8_t  LowLevelTimeCnt;
    uint8_t  HighLevelTimeCnt;
    uint16_t ErrowCnt;
}STYaSuoJiErrow;
	
typedef struct 
{
    u8 WriteEventCount;
    u8 ReadEventCount;
}ST_PushPop;

typedef union 
{
    u32	all;
    struct
    {
        u8 HisEeprom        :8;
        u8 EEpromRun        :3;
				u8 HisPwrOFF        :1;
        u8 SysRun           :1;
        u8 cool             :1;
        u8 heat             :1;
				u8 Lock            	:1;
        signed char 	HeatTempSet      :8;
        signed char   CoolTempSet      :8;
    }Bit;
}STHeatCoolTemp;


typedef struct    
{
    uint8_t step			;
    uint8_t sFactoryTime	;
    uint8_t FactoryCnt	;
		uint8_t step1			;
}STFactory;

typedef union
{
    uint32_t	all;
    struct
    {
        uint16_t   HeatCnt						:10;
        uint16_t   CoolCnt						:16;
        uint16_t   CurHeat            :1;
        uint16_t   HeatHis            :1;
        uint16_t   CurCool            :1;
        uint16_t   CoolHis            :1;
        uint16_t   LLCoolHis          :1;
        uint16_t   HHHeatHis          :1;
    }Bit;
}STHeatCool;

typedef union
{
	uint8_t	all;
	 struct
   {
       uint8_t   BCM_KeySt						:3;  
   }Bit;
	
}STBusState;


typedef union
{
	 uint8_t	all;
	 struct
   {
				uint8_t   maintenance_mode :3;
				uint8_t		power_supply		 :1; 
   }Bit;
	
}VCU_VIBModeCfg;

typedef union
{
	uint8_t	all;
	struct
	{
		uint8_t up			:4;
		uint8_t down		:4;
	}Bit;
}UPower;

typedef union
{
	uint8_t	all;
	struct
	{
		uint8_t SysRun			:1;
		uint8_t lock		    :1;
    uint8_t mode			  :2;

	}Bit;
}STCAN;

typedef struct 
{
  u8 DisplayMode;
	signed char CompensationValue;
}STSetVaue;

typedef struct 
{
		u8 PowerOnTimer;
		u8 RecoverTimer;//u8 Run;
		union
		{
			struct
			{
				u8 RunFlag 			:1;
				u8 DisplayModeFlag 	:1;
				u8 DisplayValueFlag :1;
			}Bit;
			u8         All;
		}Run;
		
		u8 mode;
		u8 value;
		
}STSetTempCompensation;

typedef struct
{
    uint8_t  KeyNum;
    uint8_t  Value;
}STLingMin;


extern STBusState stBusState ;

typedef struct 
{
  union
  {
    struct
    {
			
      uint8_t       LostPanel                  :1;      
      uint8_t       TempState1                 :1;      
      uint8_t       TempState2                 :1;     
      uint8_t       OzneState                  :1;     
      uint8_t       HeatState                  :1;     
      uint8_t       DoorState                  :1;      
			uint8_t       LedState                  :1;      
    }Bit;
    uint8_t         All;
  }DTC;
}STCANMessageByte;

typedef struct 
{
    uint8_t rev[2];
  	uint8_t VIB_SetTemp;
		union
		{
			struct
			{
				uint8_t       VIB_WorkModeSet                 :3;  
				uint8_t       VIB_ChildLockSt                 :2;  
				uint8_t       VIB_dooropenReq                 :1;  
				uint8_t       VC_ON														:2;
				      
			}Bit;
			uint8_t         All;
		}cdc; 
		uint8_t rev2[4];
    uint8_t rel3[8*5];
    uint8_t len;
    uint8_t lost; 
}STCAN_CDCMessage;

//typedef struct 
//{
//    uint8_t rev[6];
//    uint8_t VIB_WorkModeSet;
//    uint8_t TEL_VIB_TempSetReq;
//    uint8_t rel[8*5];
//    uint8_t len;
//    uint8_t lost;   
//}STCAN_TELMessage;


//typedef struct 
//{
//    uint8_t rev[6];
//    uint8_t VIB_WorkModeSet;
//    uint8_t TEL_VIB_TempSetReq;
//    uint8_t rel[8*5];
//    uint8_t len;
//    uint8_t lost;   
//}STCAN_TELMessage;


typedef struct 
{
    uint8_t rev[6];
	
    union
		{
			struct
			{
				
				uint8_t 			VIB_WorkModeSet                :3;				   
				uint8_t       VIB_WorkModeSet_VD             :1;   
				uint8_t       TEL_VIB_TempSetReq_VD          :1; 
			}Bit;
			uint8_t         All;
		}Set;
		
    uint8_t TEL_VIB_TempSetReq;
    uint8_t rel[8*5];
    uint8_t len;
    uint8_t lost;   
}STCAN_TELMessage;


 typedef union
{
	uint8_t	all;
	struct
	{
		uint8_t REV         :6;
		uint8_t LightByte	:2;
	}Bit;
}LightByte;
		


typedef struct 
{
    STCAN state;
    uint8_t SetValue;
    uint8_t RealValue;
    uint8_t verson;  
    uint8_t rev[8];
}STCANMessage;

typedef struct 
{ 
    uint8_t Ntc1Cnt;
    uint8_t Ntc2Cnt;
    uint8_t lostPanaSingnalCnt;  
    uint8_t LedCnt;
		uint8_t OzneCnt;
		uint8_t DoorCnt;
		uint16_t HeatCnt;
	  uint16_t YaSuiJiCnt;
}STCANDtcCnt;


typedef union
{
	uint8_t	all;
	struct
	{
		uint8_t Flag		:1;
		uint8_t cnt			:3;
		uint8_t lost		:4;
	}Bit;
}UCharging;

typedef union
{
	uint8_t	all;
	struct
	{
		uint8_t run         :1;
		uint8_t cnt			:7;
	}Bit;
}ST_Heat;

typedef union
{
	uint8_t	all;
	struct
	{
		uint8_t His         :1;
		uint8_t cnt			:7;
        
	}Bit;
}ST_Beep;

/////////////////////////
 typedef union
{
	uint8_t	all;
	struct
	{
		uint8_t b0	:1;
		uint8_t b1	:1;
		uint8_t b2	:1;
		uint8_t b3	:1;
		uint8_t b4	:1;
		uint8_t b5	:1;
		uint8_t b6	:1;
		uint8_t b7	:1;
	}Bit;
}byte;


typedef enum
{
    BSP_USART0,               
    BSP_USART1,               
    BSP_USART2,               
    BSP_USART3,               
    BSP_UART_MAX = BSP_USART3
}BSP_UART_Port_t;

typedef enum
{
    APP_STATE_CAN_RECEIVE,
    APP_STATE_CAN_TRANSMIT,
    APP_STATE_CAN_IDLE,
    APP_STATE_CAN_XFER_SUCCESSFUL,
    APP_STATE_CAN_XFER_ERROR,
    APP_STATE_CAN_USER_INPUT
} APP_CAN_STATES;


typedef enum
{
    BSP_BrshMotor,
    BSP_WaterPump,
    BSP_WaterAbsorption,
}MainCircuit_t;


typedef struct
{
  uint32_t tickCnt;
	Uchar tickCnt1;
	Uchar tickCnt2;
	Uchar tickCnt3;
  Uchar tickCnt4;
	Evnt_t parameter;
  void  (*pTickCBFunc)(Uchar evt);                    
 	void  (*pTickEvent)(void); 
}sysTick_t;


typedef struct
{
		u8       WorkMode;
		u8       HeatLastTempSet;
		u8			 CoolLastTempSet ;
		u8 			 SetTempValue;
		u8 			 RealTempValue;
		union
		{
			struct
			{
				
				uint8_t       DoorState                      :2;				   
				uint8_t       LockStte                       :2;   
				uint8_t       RunState                       :2; 
				uint8_t       VIB_VoiceSet                   :2;				//uint8_t       QuickCoolState                 :2;
			}Bit;
			uint8_t         All;
		}SysState;  
		u8 rev[2];
}STMessage;

typedef struct
{
  union
  {
    struct
    {
      uint8_t       RunState                       :1;    
      uint8_t       LockStte                       :1;   
      uint8_t       HeatState                  	   :1;
      uint8_t       OzneState                      :1;
      uint8_t       DoorState                      :1;
      uint8_t       WorkMode                       :3;// 
    }Bit;
    uint8_t         All;
  }func;    
  
  uint8_t          TempValueSet; 
  uint8_t          RealTempValueSet; 
  uint8_t          YaSuoJiErrowCode;
  union
  {
    struct
    {
      uint8_t       LostPanel                  :1;      
      uint8_t       TempState1                 :1;      
      uint8_t       TempState2                 :1;     
      uint8_t       OzneState                  :1;     
      uint8_t       HeatState                  :1;     
      uint8_t       DoorState                  :1;      
    }Bit;
    uint8_t         All;
  }ErrowFunc;
  
  uint16_t         Wdata;
   uint8_t         SoftVersion;
 
}MessageTxState;



typedef struct
{
  union
  {
    struct
    {
      uint8_t       RunState                       :1;    
      uint8_t       LockStte                       :1;   
      uint8_t       HeatState                 		 :1;
      uint8_t       OzneState                      :1;
      uint8_t       DoorState                      :1;
      uint8_t       WorkMode                       :3;//     0:???? 1:  ?? 2:?? 3:?? 4:  ?? 5:??
    }Bit;
    uint8_t         All;
  }func;    
  
  uint8_t          TempValueSet; 
  uint8_t          RealTempValueSet; 
  uint8_t          YaSuoJiErrowCode;
  union
  {
    struct
    {
      uint8_t       LostPanel                  :1;      
      uint8_t       TempState1                 :1;      
      uint8_t       TempState2                 :1;     
      uint8_t       OzneState                  :1;     
      uint8_t       HeatState                  :1;     
      uint8_t       DoorState                  :1;  
			uint8_t       LEDState                   :1;
    }Bit;
    uint8_t         All;
  }ErrowFunc;
  
  uint8_t         Wdata;
  uint8_t         SoftVersion;
 
}STMessage22_2EMessage;

void BSP_RegSysTickFunc(void  (*pTickCBFunc)(void));
void BSP_RegTickEvntFunc(void  (*pTickCBFunc)(Uchar evt));

extern volatile sysTick_t sysTick;
extern STDisplayCode gstDisplayCode;  
extern Uchar	gEventBuffer[EVENT_BUFFER_LENGTH];
extern Uchar	gWriteEventCount,gReadEventCount;
volatile extern Byte8	gbFlagData[10];
extern  volatile uint8_t gKeyValue;;
extern Uchar	gIR2118DData;
extern ST_PushPop gstPushPop;
extern STSetTempCompensation gstTempCompensation;
extern  byte gSendData[];
extern  signed char gTempHeat,gTempAD;
extern  STAD_Collect   gstADCollect;//extern uint8_t gKeyPressValue;
extern byte gEEpromData[3];
extern uint8_t gErrorCode;
extern uint16_t TempTab[];
extern volatile STHeatCool  gHeatCool;
extern STHeatCoolTemp gHeatCoolTemp;
extern STYaSuoJiErrow gstYaSuoJiErrow;
extern volatile uint16_t ADtable[ADMax];
extern STMessage22_2EMessage gst22_2EMessage;;
extern volatile sysTick_t gstRDsysTick;
extern uint8_t  gtab[];
extern STCAN_TELMessage gstTELMessage;
extern STCAN_CDCMessage gstCDCMessage;
extern u8  gLightAdjust;
extern  volatile u8 gPwmDuty;
extern byte gForceOutputFlag;
extern STCANDtcCnt gstCANDtcCnt;
volatile extern u8 gUartSingnalCnt;
extern STFactory   gstFactory;
extern volatile STMessage  gstCanMessage;
extern volatile LightByte       gLightByte;
extern u16 gPauseCnt;
//extern u16 gAccToOff_DelayCnt;
extern VCU_VIBModeCfg gVCU_VIBModeCfg;
extern uint16_t gChouTiOpenCnt;
#define  EEPROM_REDY  			 gHeatCoolTemp.Bit.EEpromRun =1;TempSetFlag =0;

#define  RDSystickProcess() gstRDsysTick.tickCnt++; \
	gstRDsysTick.tickCnt1++;\
	gstRDsysTick.tickCnt2++;\
	gstRDsysTick.tickCnt3++;\
  gstRDsysTick.tickCnt4++;\
  if(0 == gstRDsysTick.tickCnt4%5){Ev5MSFlag = 1; gstRDsysTick.tickCnt4  = 0;}\
	if(0 == gstRDsysTick.tickCnt3%20){Ev20MSFlag = 1;gstRDsysTick.tickCnt3  = 0;}\
	if(0 == gstRDsysTick.tickCnt2%50){Ev50MSFlag = 1;gstRDsysTick.tickCnt2  = 0;}\
	if(0 == (gstRDsysTick.tickCnt)%1000){Ev1SFlag = 1;gstRDsysTick.tickCnt = 0;}\
	if(0 == (gstRDsysTick.tickCnt1)%100){Ev100MSFlag = 1;gstRDsysTick.tickCnt1 = 0;}
	
#define  SCUCESS        1
#define  FAIL           0

#if 1//µ⁄“ª∞Êœ‘ æ∞Â
#define KEY1_MASK 0x01
#define KEY2_MASK 0x02
#define KEY3_MASK 0x04
#define KEY4_MASK 0x08
#define KEY5_MASK 0x10
#define KEY6_MASK 0x20
#define KEY7_MASK 0x40
#define KEY8_MASK 0x80
#else
#define KEY1_MASK 0x20
#define KEY2_MASK 0x10
#define KEY3_MASK 0x08
#define KEY4_MASK 0x04
#define KEY5_MASK 0x02
#define KEY6_MASK 0x01
#define KEY7_MASK 0x40
#define KEY8_MASK 0x80
#endif

#define  _150MS_Per5MS     30
#define  _100MS_Per5MS     20

#define  _100MS_Per20MS    5
#define  _120MS_Per20MS    6
#define  _140MS_Per20MS    7
#define  _200MS_Per20MS    10
#define  _220MS_Per20MS    11
#define  _240MS_Per20MS    12
#define  _260MS_Per20MS    13
#define  _280MS_Per20MS    14
#define  _3S_Per20MS      50*3
#define  _4S_Per20MS      50*4

#define  _10S_Per50MS  20*10
#define  _5S_Per50MS   20*5
#define  _3S_Per50MS   20*3
#define  _2S_Per50MS   20*2
#define  _1S_Per50MS   20*1
#define  _30S_Per50MS  20*30


#define  _90Min_Per100MS      10*60*90
#define  _15Min_Per100MS      10*60*15
#define  _3S400MS_Per100MS         34
#define  _15S_Per100MS        10*15
#define  _30S_Per100MS        10*30
#define  _3Min_Per100MS       10*60*3
#define  _13Min_Per100MS      10*60*13
#define  _20Min_Per100MS      10*60*20
#define  _30Min_Per100MS      10*60*30
#define  _40Min_Per100MS      10*60*40

#define  _200MS_Per100MS   2
#define  _500MS_Per100MS   5
#define  _2S_Per100MS   10*2
#define  _1S_Per100MS   10*1
#define  _10S_Per100MS   10*10
#define  _25S_Per100MS  10*20

#define  _1h_Per1S      60*60
#define  _30Min_Per1S   60*30
#define  _60Min_Per1S   120*30
#define  _15Min_Per1S   60*15
#define  _20Min_Per1S   60*20
#define  _5Min_Per1S		60*5
#define  _2Min_Per1S		60*2
#define  _4Min_Per1S		60*4
#define  _1Min_Per1S		60*1
#define  _35S_Per1S		  35
#define  _50S_Per1S		  50
#define  _3Min_Per1S		60*3
#endif
