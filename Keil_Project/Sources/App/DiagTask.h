/****************************************Copyright (c)****************************************************
**                            Guangzhou ZLGMCU Development Co., LTD
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           DiagTask.c
** Last modified Date:  2023-04-24
** Last Version:        V1.0
** Descriptions:        The rte header file
**
**--------------------------------------------------------------------------------------------------------
** Created by:          DKLai
** Created date:        2023-04-24
** Version:             V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         DKLai
** Modified date:       2023-04-24
** Version:             V
** Descriptions:        1.00
** Rechecked by:
*********************************************************************************************************/
#ifndef __VIB_DIAG_TASK_H_

#define __VIB_DIAG_TASK_H_

extern void    __DiagTask_Init(void);
extern void    __DiagTask_HandleTask(void);
extern void    __DiagTask_Period2msTask(void);
extern void    __DiagTask_Period10msTask(void);
extern void    __DiagTask_Period100msTask(void);
extern void    __DiagTask_EEPTask(void);
extern uint8_t __DiagTask_UpdateDTC(uint8_t dtcnumber, uint8_t errstate);
extern uint8_t __DiagTask_SendAppMsg(uint8_t *appmsg);

/* DKLai20230425 */
extern uint8_t __DiagTask_RcvTELCheck(uint8_t *appmsg);
extern uint8_t __DiagTask_ClrRcvTELFlag(void);
extern uint8_t __DiagTask_RcvCDCCheck(uint8_t *appmsg);
extern uint8_t __DiagTask_ClrRcvCDCFlag(void);
extern uint8_t __DiagTask_Rcv2FCheck(uint8_t *ctrlbytes, uint8_t *len);
extern uint8_t __DiagTask_Clr2FRcvFlag(void);
extern void    __DiagTask_DidVibDataSet(uint8_t *buf);
extern uint8_t __DiagTask_EEPWrite(uint32_t address, uint8_t *wbuf, uint8_t len);
extern uint8_t __DiagTask_EEPRead(uint32_t address, uint8_t *wbuf, uint8_t len);
extern uint8_t __DiagTask_SetPowerValue(uint16_t *adcbuf);
extern uint8_t __DiagTask_UpdatePriodicMsg(uint8_t *sendbuffer);       /* DKLai20230705 */
extern uint8_t __DiagTask_RxPeriodMsg(uint16_t msgid, uint8_t *rxbuf); /* DKLai20230814 */
extern void    __DiagTask_5sAppMsg_Start(void);                        /* DKLai20231026 */

#endif

