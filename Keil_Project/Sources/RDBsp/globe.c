#include "globe.h"

volatile uint8_t uart_txbuffer[10];
u8  gLightAdjust = 0xc0;
uint8_t  gtab[8] = {0x03,0x02,0x80,0x00,0x00,0x84};
volatile uint16_t ADtable[ADMax];
STAD_Collect   gstADCollect;;
volatile sysTick_t gstRDsysTick;
Uchar gEventBuffer[EVENT_BUFFER_LENGTH];
byte gbNoInitFlagData[10];
volatile byte	gbFlagData[10];
uint8_t gErrorCode;
ST_PushPop gstPushPop;
byte gSendData[3];
signed char gTempHeat,gTempAD;
byte gEEpromData[3];
volatile STHeatCool  gHeatCool;
volatile u8 gPwmDuty;
VCU_VIBModeCfg gVCU_VIBModeCfg;
STHeatCoolTemp gHeatCoolTemp;
STSetTempCompensation gstTempCompensation;
STBusState stBusState ;
STYaSuoJiErrow gstYaSuoJiErrow;
STMessage22_2EMessage gst22_2EMessage;
STCAN_TELMessage gstTELMessage;
STCAN_CDCMessage gstCDCMessage;
volatile u8 gUartSingnalCnt;
byte gForceOutputFlag;
STCANDtcCnt gstCANDtcCnt;
STFactory   gstFactory; 
STDisplayCode gstDisplayCode;
u16 gPauseCnt;
//u16 gAccToOff_DelayCnt;
uint16_t gChouTiOpenCnt;
volatile STMessage  gstCanMessage;
volatile LightByte       gLightByte;
uint16_t TempTab[] ={

973 ,
968 ,
963 ,
958 ,
953 ,
947 ,
942 ,
935 ,
929 ,
921 ,
914 ,
907 ,
900 ,
892 ,
884 ,
874 ,
866 ,
857 ,
848 ,
838 ,
828 ,
817 ,
807 ,
797 ,
786 ,
774 ,
762 ,
751 ,
739 ,
727 ,
714 ,
702 ,
690 ,
677 ,
664 ,
651 ,
638 ,
626 ,
612 ,
599 ,
586 ,
572 ,
559 ,
546 ,
534 ,
520 ,
507 ,
495 ,
483 ,
469 ,
457 ,
445 ,
433 ,
421 ,
409 ,
398 ,
387 ,
376 ,
364 ,
354 ,
344 ,
334 ,
323 ,
313 ,
304 ,
295 ,
286 ,
277 ,
268 ,
260 ,
252 ,
244 ,
236 ,
229 ,
221 ,
214 ,
207 ,
201 ,
195 ,
188 ,
183 ,
177 ,
170 ,
165 ,
160 ,
155 ,
150 ,
145 ,
140 ,
136 ,
132 ,
128 ,
123 ,
119 ,
115 ,
111 ,
108 ,
105 ,
101 ,
98 ,
95 ,
92 ,
89 ,
87 ,
84 ,
82 ,
79 ,
77 ,
73 ,
71 ,
69 ,
67 ,
65 ,
63 ,
61 ,
59 ,
58 ,
56 ,
54 ,
53 ,
51 ,
50 ,
48 ,
47 ,
46 ,
44 ,
43 ,
42 ,
41 ,
40 ,
38 ,
37 ,
36 ,
35 ,
34 ,
34 ,
33 ,
32 ,
31 ,
30 ,
29 ,

};
