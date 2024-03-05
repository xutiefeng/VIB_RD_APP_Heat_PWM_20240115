/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:           includeall.h
** Last modified Date:  2011-12-01
** Last Version:        V1.01
** Descriptions:        User Configurable File
**
**--------------------------------------------------------------------------------------------------------
** Created By:          zhaohai
** Created date:        2011-12-01
** Version:             V1.00
** Descriptions:        First version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:       
** Version:             
** Descriptions:       
**
*********************************************************************************************************/
#ifndef __INCLUDEALL_H
#define __INCLUDEALL_H

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 通用宏定义
*********************************************************************************************************/
#ifndef TRUE
#define TRUE     1ul
#endif

#ifndef FALSE
#define FALSE    0ul
#endif

#ifndef NULL
#define NULL     ((void *)0)
#endif

#include "ProjectCfg.h"

/*********************************************************************************************************
** 定义与编译器无关的数据类型
*********************************************************************************************************/
typedef unsigned        char    BOOLEAN;
typedef unsigned        int     INTCPU;
typedef signed          int     INTCPS;
#define INT8U                   uint8_t
#define INT8S                    int8_t
#define INT16U                  uint16_t
#define INT16S                   int16_t
#define INT32U                  uint32_t
#define INT32S                   int32_t

#if defined(__ARMCC_VERSION)
#include <stdbool.h>

typedef bool BOOL;
typedef bool bool_t;

typedef   signed           char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;

//typedef unsigned           char uint8_t;
//typedef unsigned short     int uint16_t;
//typedef unsigned           int uint32_t;
#define uint8_t  unsigned           char
#define uint16_t  unsigned           short
#define uint32_t  unsigned           int

#elif defined(__CWCC__)
typedef uint8_t BOOL;
#elif defined(__GNUC__)
typedef uint8_t BOOL;
#endif
#define MyMemcpy(d,s,l)                             memcpy(d,s,l)    
#define MyMemcmp(s1,s2,l)                           memcmp(s1,s2,l) 
#define MyMemset(d,f,l)                             memset(d,f,l)

/*#define CLRWDT()                        WDOG_DRV_Trigger(INST_WATCHDOG1);*/
//**#define NOP()                           __NOP()
#define SetStopMode()                   //__asm("ANDCC #0x7F"); __asm("STOP");
#define EnableOSC()                     //CPMUPROT = 0x26;CPMUCLKS_PSTP = 1;CPMUPROT = 0x00;
#define DisableOSC()                    //CPMUPROT = 0x26;CPMUCLKS_PSTP = 0;CPMUPROT = 0x00;
#define EnableIRQ()                     INT_SYS_EnableIRQGlobal()
#define DisableIRQ()                    INT_SYS_DisableIRQGlobal()
#define EnableIRQ_Tick()                //影响计时准确，暂不使用 S32_SysTick->CSR = S32_SysTick_CSR_ENABLE(1u) | S32_SysTick_CSR_TICKINT(1u) | S32_SysTick_CSR_CLKSOURCE(1u);
#define DisableIRQ_Tick()               //影响计时准确，暂不使用 S32_SysTick->CSR = S32_SysTick_CSR_ENABLE(1u) | S32_SysTick_CSR_TICKINT(0u) | S32_SysTick_CSR_CLKSOURCE(1u);
#define EnableIRQ_CAN_RX()              INT_SYS_EnableIRQ(CAN0_ORed_0_31_MB_IRQn)
#define DisableIRQ_CAN_RX()             INT_SYS_DisableIRQ(CAN0_ORed_0_31_MB_IRQn)
#define Random()                        (S32_SysTick->CVR)

/*********************************************************************************************************
**
*********************************************************************************************************/

/*********************************************************************************************************
** 用户自己的配置代码定义 DKLai20230419
*********************************************************************************************************/
#define PROJECT_DIAG_REQ_ID             0x709
#define PROJECT_DIAG_RES_ID             0x789
#define PROJECT_APP_SEN_ID              0x383

/*******************************************************************
** 调试选项
*******************************************************************/
#define DEBUG_PROJECT_MASK_SEEDKEY      (0)     /* 为1则屏蔽Seedkey算法 */
#define DEBUG_PROJECT_MASK_WDOG         (0)     /* 为1则屏蔽MCU内部看门狗 DKLai20230425 */
#define DEBUG_PROJECT_MASK_NM           (1)     /* 为1则屏蔽网络管理 */
#define DEBUG_PROJECT_MASK_SBC          (1)     /* 为1则屏蔽SBC功能 DKLai20230423 */
#define DEBUG_PROJECT_MCU_SLEEP_EN      (0)     /* 为1则使能MCU电源管理功能 */
#define DEBUG_PROJECT_PRINT_EN          (0)     /* 为1则使能打印输出 */
#define DEBUG_PROJECT_DEBUG             (0)     /* 为1则为调试模式 */

#define DEBUG_PROJECT_SOME_DID_IN_APP_AND_BOOT  (1)     /* 为1则部分DID也存储在APP的ROM表中 */

#if DEBUG_PROJECT_MASK_WDOG
#define CLRWDT()                        NOP()
#else
#define CLRWDT()                        WDOG_DRV_Trigger(INST_WATCHDOG1);
#endif
#if DEBUG_PROJECT_DEBUG
#define DEBUG_PROJECT_CAN_DEBUG_MSG     (0)
#define DEBUG_PROJECT_MASK_CAN_RX       (0)
#define DEBUG_PROJECT_MASK_CAN_TX_APP   (0)
#define DEBUG_PROJECT_MASK_AD_BAT       (0)
#define DEBUG_PROJECT_MASK_BCM_PWR      (0)
#define DEBUG_PROJECT_MASK_SLEEP        (1)
#else
#define DEBUG_PROJECT_CAN_DEBUG_MSG     (0)
#define DEBUG_PROJECT_MASK_CAN_RX       (0)
#define DEBUG_PROJECT_MASK_CAN_TX_APP   (0)
#define DEBUG_PROJECT_MASK_AD_BAT       (0)  /* DKLai20230506 */
#define DEBUG_PROJECT_MASK_BCM_PWR      (0)  /* DKLai20230506 */
#define DEBUG_PROJECT_MASK_SLEEP        (0)
#endif

/*********************************************************************************************************
** 头文件
*********************************************************************************************************/

/* CM0 系统头文件 */
#include "S32K116.h"
//#include "s32_core_cm0.h"
#include "stdio.h"
#include <string.h>
/* SDK 生成配置文件 */
#include "Cpu.h"

/* User */
#include "Main.h"
#include "User\Time.h"
#include "User\Stat.h"
#include "User\Flag.h"
#include "User\Crc.h"

/* App */
#include "App\EepAll.h"
#include "App\EepApp.h"
#include "App\CanAll.h"
#include "App\CanApp.h"
#include "App\CanNM2.h"
#include "App\CanDiag.h"
#include "App\CanTp.h"
#include "App\CarSign.h"
#include "App\DiagSid.h"
#include "App\DiagSub.h"
#include "App\DiagDid.h"
#include "App\Dtc.h"
#include "App\Info.h"
#include "App\DiagTask.h"  /* DKLai20230425 */
#include "App\Rte.h"
/* Device */

/* Hardware */
#include "Hardware\flexcan_hw_access.h"
#include "Hardware\FLEXCAN.h"
#include "Hardware\SYS.h"
#include "Hardware\ADC.h"
#include "Hardware\CAN.h"
#include "Hardware\EEPROM.h"
#include "Hardware\lpuart_hw_access.h"
#include "Hardware\LPUART.h"


/* RDBsp */
#include "RDBsp\globe.h"
#include "RDBsp\bsp_uart.h"
#include "RDBsp\sysRun.h"
#include "RDBsp\clib.h"
#include "RDBsp\CDCMessage.h"
#include "RDBsp\TELMessage.h"
//#include "RDBsp\UpdataCanMessage.h"
/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __INCLUDEALL_H              */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
