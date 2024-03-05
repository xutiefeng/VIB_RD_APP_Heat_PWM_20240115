/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           UartApp.h
** Last modified Date:  2011-06-01
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2011-06-01
** Version:             V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
** Rechecked by:
*********************************************************************************************************/
#ifndef __UARTAPP_H
#define __UARTAPP_H

// #include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
/*
 *  CMDM
 */
#define UART_SYS_RST_MSG_ID             0x0C    /* CMDM12   ϵͳ��λ    */
#define UART_SYS_CALL_MSG_ID            0x0D    /* CMDM13   ϵͳ����    */
#define UART_VIEW_MODE_MSG_ID           0x0A    /* CMDM10   ��ʾģʽ    */
#define UART_POLL_STAT_MSG_ID           0x80    /* CMDM128  ��ѯ״̬    */
#define UART_POLL_VERSION_MSG_ID        0x81    /* CMDM129  ��ѯ�汾    */
#define UART_CALE_STAT_MSG_ID           0x65    /* CMDM101  �궨״̬    */
#define UART_OSD_MSG_ID                 0xCA    /* CMDM202  OSD�趨     */

/*
 *  PARAM-��ѯ�궨״̬�Ĳ���
 */
#define UART_CALE_STAT_MSG_ID_ING       0x00
#define UART_CALE_STAT_MSG_ID_SUCC      0x0E
#define UART_CALE_STAT_MSG_ID_FAIL      0x0F

/*
 *  PARAM-OSDͼ����Ϣ�趨�Ĳ������
 */
#define UART_OSD_SET                    0x80
#define UART_OSD_CLR                    0x00
#define UART_OSD_AROUND_SOLID           0x10
#define UART_OSD_AROUND_DASHED          0x20
#define UART_OSD_EXPAND_SOLID           0x30
#define UART_OSD_EXPAND_DASHED          0x40
#define UART_OSD_FORWARD                0x00
#define UART_OSD_BACKOFF                0x01
#define UART_OSD_LEFT                   0x02
#define UART_OSD_RIGHT                  0x03
#define UART_OSD_CENTER                 0x04

/*
 *  PARAM-�����붨��
 */
#define UART_ERR_SUCC                   0x00
#define UART_ERR_OUT_ID                 0x01
#define UART_ERR_CODE_CRC               0x02
#define UART_ERR_DATA_CRC               0x03
#define UART_ERR_CALE_SUCC              0x0E
#define UART_ERR_CALE_FAIL              0x0F
#define UART_ERR_OTHER                  0xFF
/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/
extern  const   INT8U   DSPCMD_SYS_RST[4];
extern  const   INT8U   DSPCMD_SYS_CALE[4];
extern  const   INT8U   DSPCMD_SYS_REC[4];
extern  const   INT8U   DSPCMD_SYS_PLAY[4];

extern  const   INT8U   DSPCMD_VIEW_DIS[4];
extern  const   INT8U   DSPCMD_VIEW_DVR[4];

extern  const   INT8U   DSPCMD_VIEW_AROUND_FORWARD[4];
extern  const   INT8U   DSPCMD_VIEW_AROUND_BACKOFF[4];
extern  const   INT8U   DSPCMD_VIEW_AROUND_LEFT[4];
extern  const   INT8U   DSPCMD_VIEW_AROUND_RIGHT[4];

extern  const   INT8U   DSPCMD_VIEW_EXPAND_FORWARD[4];
extern  const   INT8U   DSPCMD_VIEW_EXPAND_BACKOFF[4];
extern  const   INT8U   DSPCMD_VIEW_EXPAND_LEFT[4];
extern  const   INT8U   DSPCMD_VIEW_EXPAND_RIGHT[4];

extern  const   INT8U   DSPCMD_VIEW_FISHEYE_FORWARD[4];
extern  const   INT8U   DSPCMD_VIEW_FISHEYE_BACKOFF[4];
extern  const   INT8U   DSPCMD_VIEW_FISHEYE_LEFT[4];
extern  const   INT8U   DSPCMD_VIEW_FISHEYE_RIGHT[4];

extern  const   INT8U   DSPCMD_VIEW_AROUND_LALL[4];
extern  const   INT8U   DSPCMD_VIEW_AROUND_RALL[4];

extern  const   INT8U   DSPCMD_POLL_DSP_STAT[4];
extern  const   INT8U   DSPCMD_POLL_APP_VERSION[4];
extern  const   INT8U   DSPCMD_POLL_CALE_VERSION[4];
extern  const   INT8U   DSPCMD_POLL_USER_VERSION[4];

extern  const   INT8U   DSPCMD_UPDATE_APP_FROM_USB[4];
extern  const   INT8U   DSPCMD_UPDATE_CALE_FROM_USB[4];
extern  const   INT8U   DSPCMD_UPDATE_REC_FROM_USB[4];
extern  const   INT8U   DSPCMD_UPDATE_PLAY_FROM_USB[4];

extern  const   INT8U   DSPCMD_UPDATE_BV_SV_FROM_USB[4];
extern  const   INT8U   DSPCMD_UPDATE_BV_FROM_USB[4];
extern  const   INT8U   DSPCMD_UPDATE_SV_FROM_USB[4];
extern  const   INT8U   DSPCMD_UPDATE_OSD_FROM_USB[4];
extern  const   INT8U   DSPCMD_UPDATE_OSD2_FROM_USB[4];

extern  const   INT8U   DSPCMD_UPDATE_PARAM_FROM_USB[4];
extern  const   INT8U   DSPCMD_UPDATE_PACK_FROM_USB[4];

extern  const   INT8U   DSPCMD_CALE_POLL[4];

extern  const   INT8U   DSPCMD_REC_PLAY[4];

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
extern  volatile    INT8U   DSPCMD_OSD[11];

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  STAT_MSG_RESULT_ENUM    UartApp_DealRcvMsg(void);
extern  BOOLEAN                 UartApp_DealRcvMsg_AckUsualDeal(INT8U ucErr);
extern  BOOLEAN                 UartApp_DealRcvMsg_AckPollDeal(INT8U ucErr1, INT8U ucErr2);
extern  void                    UartApp_SenCmd(const INT8U *pCmd);
extern  void                    UartApp_SenCmdN(volatile INT8U *pCmd, INT8U ucLen);

/******************************************* Private Function *******************************************/

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __UARTAPP_H                 */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
