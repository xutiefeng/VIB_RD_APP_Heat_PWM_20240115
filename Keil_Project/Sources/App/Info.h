/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Info.h
** Last modified Date:  2019-11-15
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2019-11-15
** Version:             V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         zhaohai
** Modified date:       2019-11-15
** Version:
** Descriptions:
**
** Rechecked by:
*********************************************************************************************************/
#ifndef __INFO_H
#define __INFO_H

#include "includeall.h"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/

/*******************************************************************
** 系统名称 + 零件号 + APP软件版本号配置 DKLai20230419
*******************************************************************/
#define SPN1                    'X','F','S','8','2','8','0','0','2','0','0','0'  /* 12Byte, Spare Part Number */
#define VEHSWV                  'S','.','0','0','1'                              /* 车厂软件版本号 DKLai20231008 */

/* DKLai20230421 */
#define SPLHWV                  '0','0','0','0'                                  /*  DID 0xF193 供应商硬件版本号      */
#define SPLSWV                  '0','0','0','0'                                  /*  DID 0xF195 供应商软件版本号      */

/*******************************************************************
** 日期配置 DKLai20230421 
*******************************************************************/
/*  4Byte   BCD,年月日 */
#define ECU_YEARH               0x20
#define ECU_YEARL               0x23
#define ECU_MONTH               0x04
#define ECU_DAY                 0x21

/*******************************************************************
** DID配置 DKLai20230423 
*******************************************************************/
/*  10Byte   F184 */
#define ECU_FINGER_DEVICE_ID    0xFF
#define ECU_FINGER_YEAR         ECU_YEARL
#define ECU_FINGER_MONTH        ECU_MONTH
#define ECU_FINGER_DAY          ECU_DAY
#define ECU_FINGER_TESTER_SN    0x00,0x00,0x00,0x00,0x00,0x00
#define ECU_FINGER              ECU_FINGER_DEVICE_ID,ECU_FINGER_YEAR,ECU_FINGER_MONTH,ECU_FINGER_DAY,ECU_FINGER_TESTER_SN


/* 17Byte   F102 */
#define ECU_MTOC                0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30

/* 17Byte   F190 */
#define ECU_VIN                 0x00

/* 17Byte   F189 车厂软件版本号. DKLai20230421 */
#define ECU_VER_VEHSOFT         SPN1,VEHSWV

/* 4Byte   F193 */
#define ECU_VER_SPLHARD         SPLHWV

/* 4Byte   F195 */
#define ECU_VER_SPLSOFT         SPLSWV

/* 4Byte   F199 default program date. DKLai20230421 */
#define ECU_VER_PROGRAMDATE     ECU_YEARH,ECU_YEARL,ECU_MONTH,ECU_DAY

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/

/*********************************************************************************************************
** 函数声明
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/

/******************************************* Private Function *******************************************/

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __INFO_H                    */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
