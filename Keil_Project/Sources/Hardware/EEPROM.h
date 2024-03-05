/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           EEPROM.c
** Last modified Date:  2019-10-21
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          tangjian
** Created date:        2017-12-26
** Version:             V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         zhaohai
** Modified date:       2019-10-21
** Version:             
** Descriptions:        
**
** Rechecked by:        
*********************************************************************************************************/
#ifndef __EEPROM_H
#define __EEPROM_H

// #include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
#define EEP_BASE_ADDR           0x14000000                              /* EEPROM起始地址               */
#define EEP_TOTAL_SIZE          0x800                                   /* EEPROM空间大小 2K            */
#define EEP_END_ADDR            (EEP_BASE_ADDR + EEP_TOTAL_SIZE - 1)    /* EEPROM结束地址               */

/*********************************************************************************************************
** 宏定义：FLASH命令
*********************************************************************************************************/
#define FLS_CMD_READ_1S_BLOCK               (INT8U)0x00                 /* 校验块是否擦除成功           */
#define FLS_CMD_READ_1S_SECTION             (INT8U)0x01                 /* 校验扇区是否擦除成功         */
#define FLS_CMD_PROG_CHK                    (INT8U)0x02
#define FLS_CMD_PROG_8BYTE                  (INT8U)0x07                 /* 编程8byte                    */
#define FLS_CMD_ERASE_BLOCK                 (INT8U)0x08                 /* 块擦除命令                   */
#define FLS_CMD_ERASE_SECTOR                (INT8U)0x09                 /* 扇区擦除命令                 */
#define FLS_CMD_PROG_SECTION                (INT8U)0x0B
#define FLS_CMD_READ_1S_ALL_BLOCK           (INT8U)0x40                 /* 校验所有的块,擦除IFR,解锁MCU */
#define FLS_CMD_READ_ONCE                   (INT8U)0x41                 /* IFR                          */
#define FLS_CMD_PROG_ONCE                   (INT8U)0x43                 /* IFR                          */
#define FLS_CMD_ERASE_ALL_BLOCK             (INT8U)0x44                 /* 擦除所有块，并校验，解锁MCU  */
#define FLS_CMD_VERIFY_BKDOOR_KEY           (INT8U)0x45                 /* 校验后门钥匙,解锁MCU         */
#define FLS_CMD_ERASE_ALL_BLOCK_UNSECURE    (INT8U)0x49
#define FLS_CMD_PROG_PARTITION              (INT8U)0x80                 /* FlexNVM分区指令              */
#define FLS_CMD_SET_FLEXRAM                 (INT8U)0x81                 /* 设置FlexRam做EEPROM还是RAM   */

/*********************************************************************************************************
** 枚举
*********************************************************************************************************/
typedef enum {
    EEP_ENABLE                          = 0x00U,    /*!< Make FlexRAM available for emulated EEPROM     */
    EEP_QUICK_WRITE                     = 0x55U,    /*!< Make FlexRAM available for EEPROM quick writes */
    EEP_STATUS_QUERY                    = 0x77U,    /*!< EEPROM quick write status query                */
    EEP_COMPLETE_INTERRUPT_QUICK_WRITE  = 0xAAU,    /*!< Complete interrupted EEPROM quick write process*/
    EEP_DISABLE                         = 0xFFU,    /*!< Make FlexRAM available as RAM                  */
} FLEXRAM_FUNC_ENUM;

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
extern  void                    EEPROM_Init(void);
extern  BOOLEAN                 EEPROM_Write(INT32U ulAdd, INT32U ulLen, const INT8U *pucDat);
extern  BOOLEAN                 EEPROM_Read(INT32U ulAdd, INT32U ulLen, INT8U *const pucDat);

/******************************************* Private Function *******************************************/
static  INT8U                   EEPROM_CmdSequence(INT8U *pCmdDat, INT8U ucLen);
static  BOOLEAN                 EEPROM_ProgPartition(void);
static  BOOLEAN                 EEPROM_SetFlexRam(void);

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __EEPROM_H                  */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
