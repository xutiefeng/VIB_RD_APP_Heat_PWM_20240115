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
* 
**--------------------------------------------------------------------------------------------------------
** Modified by:         zhaohai
** Modified date:       2019-10-21
** Version:
** Descriptions:
**
** Rechecked by:
*********************************************************************************************************/
#include "includeall.h"

/*********************************************************************************************************
** 全局定量
*********************************************************************************************************/
/* 指针数组,命令操作序列,特别关注实际的索引序列 */
static  volatile    INT8U   *pCmdReg[12] = {
    &(FTFC->FCCOB[3]),  &(FTFC->FCCOB[2]),  &(FTFC->FCCOB[1]), &(FTFC->FCCOB[0]),
    &(FTFC->FCCOB[7]),  &(FTFC->FCCOB[6]),  &(FTFC->FCCOB[5]), &(FTFC->FCCOB[4]),
    &(FTFC->FCCOB[11]), &(FTFC->FCCOB[10]), &(FTFC->FCCOB[9]), &(FTFC->FCCOB[8]),
};

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:       FlashDriver_CmdSequence
** Descriptions:        命令执行函数，需要在RAM中执行
** input parameters:    pCmdDat：命令序列
**                      ucLen：  命令长度
** output parameters:   无
** Returned value:      执行结果
*********************************************************************************************************/
static  INT8U   __attribute__((section(".code_ram"))) EEPROM_CmdSequence(INT8U *pCmdDat, INT8U ucLen)
{
    INT8U   i;
    
    DisableIRQ();
    /*
     * 1.等待正在执行的命令完成，并清除相关错误标志位
     */
    TIME_WAIT_START(3000);
    while(!(FTFC->FSTAT & 0x80)){TIME_WAIT_LOOP()}; /*48M:620ns*/
    FTFC->FSTAT     = 0x70;                 /* 清错误标志位,此处不允许有置位CCIF的时序，否则操作错误 */
    /*
     * 2.写命令
     */
    for (i = 0; i < ucLen; i++) {
        *(pCmdReg[i])   = pCmdDat[i];
    }
    /*
     * 3.启动命令并等待执行完成(CCIF=1)或者出错(MGSTATO=1)
     */
    FTFC->FSTAT    |= 0x80;
    while(!(FTFC->FSTAT & 0x81));           /*48M:460us,此处不加TIME_WAIT_LOOP(),否则实测将导致复位 */
    
    EnableIRQ();
    return FTFC->FSTAT;
}

/*********************************************************************************************************
** Function name:       EEPROM_ProgPartition
** Descriptions:        FlexNVM分区操作，把FlexNVM分成DFlash和EEPROM，并初始化FlexRAM.
**                      --此函数验证发现分区时发生错误ACC访问错误，可能与芯片版本有关
** input parameters:    无
** output parameters:   无
** Returned value:      执行结果
*********************************************************************************************************/
static  BOOLEAN EEPROM_ProgPartition(void)
{
    INT8U   ucCmdDat[6];
    INT8U   ucRet;
    
    ucCmdDat[0]     = FLS_CMD_PROG_PARTITION;
    ucCmdDat[1]     = 0x00;
    ucCmdDat[2]     = 0x00;
    ucCmdDat[3]     = 0x00;                 /* 0x00 复位期间加载ROM中的数据到RAM，0x01 不加载          */
    ucCmdDat[4]     = 0x03;                 /* EEPROM Data 大小设置 0x03:2K,0x0F:无                    */
    ucCmdDat[5]     = 0x03;                 /* FlexNVM Partition Code设置DFlash = 0K，EEPROM bk = 32K  */
    
    ucRet   = EEPROM_CmdSequence(ucCmdDat, 6);
    if (!(ucRet & 0x21)) {
        return TRUE;
    }
    return FALSE;
}
/*********************************************************************************************************
** Function name:       EEPROM_SetFlexRam
** Descriptions:        挂载FlexRAM区域, 使能FlexRAM作为EEPROM操作区
** input parameters:    无
** output parameters:   无
** Returned value:      执行结果
*********************************************************************************************************/
static  BOOLEAN EEPROM_SetFlexRam(void)
{
    INT8U   ucCmdDat[2];
    INT8U   ucRet;
    
    ucCmdDat[0]     = FLS_CMD_SET_FLEXRAM;
    ucCmdDat[1]     = (INT8U)EEP_ENABLE;
    
    ucRet   = EEPROM_CmdSequence(ucCmdDat, 2);
    if (!(ucRet & 0x20)) {
        return TRUE;
    }
    return FALSE;
}
/*********************************************************************************************************
** Function name:       EEPROM_Init
** Descriptions:        初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void    EEPROM_Init(void)
{
    INT8U   ucPartition;
    BOOLEAN ulRet;
    
    /* DisableIRQ(); */
    ucPartition = (INT8U)((SIM->FCFG1 & SIM_FCFG1_DEPART_MASK) >> SIM_FCFG1_DEPART_SHIFT);  /* 获取分区指令代码 */
    if (ucPartition == 0x0F) {                                          /* 未分区的情况                */
        ulRet   = EEPROM_ProgPartition();
        if (ulRet) {
            ulRet   = EEPROM_SetFlexRam();                              /* 挂载FlexRAM                 */
        }
    } else if (ucPartition == 0x04) {                                   /* 第一次分区由本程序分的情况  */
        ulRet   = EEPROM_SetFlexRam();                                  /* 挂载 FlexRAM                */
    } else {                                                            /* 未分区或非法分区情况        */
        /* EnableIRQ(); */
        return;
    }
    
    if (ulRet) {
        TIME_WAIT_START(3000);
        while(!(FTFC->FCNFG & 0x01)){TIME_WAIT_LOOP()};                 /* 等待EEPROM完成初始化,48M:760ns*/
    }
    /* EnableIRQ(); */
}
/*********************************************************************************************************
** Function name:       EEPROM_Write
** Descriptions:        EEPROM写
** input parameters:    ulAdd：      地址
**                      ucLen：      长度
**                      *pucDat： 将写数据储存地址
** output parameters:   无
** Returned value:      执行结果
*********************************************************************************************************/
BOOLEAN EEPROM_Write(INT32U ulAdd, INT32U ulLen, const INT8U *pucDat)
{
    INT32U  i;
    
    if (!(FTFC->FCNFG & 0x01)) {
        return FALSE;
    }
    if ((!(ulAdd >= EEP_BASE_ADDR)) || ((ulAdd + ulLen - 1) > EEP_END_ADDR)) {
        return FALSE;
    }
    
    for (i = 0; i < ulLen; i++) {
        ((INT8U *)ulAdd)[i] = pucDat[i];
        
        #if 0   /* 第一版 */
        while(!(FTFC->FCNFG & 0x01));                       /* tangjian2018-07-10 添加等待，修正连续写两个字节Bug,48M:125us */
        #endif
        #if 0   /* 第二版 */
        TIME_WAIT_START(3000);                              /* zhaohai2019-10-30 时间若不够长(eg:1000),将偶发进入HardFault，所以改为3000 */
        while(!(FTFC->FCNFG & 0x01)){TIME_WAIT_LOOP()};
        #endif
        #if 0   /* 第三版*/
        TIME_WAIT_START(3000);                              /* zhaohai2019-11-29 若写超时则返回，避免继续写造成HardFault */
        while(!(FTFC->FCNFG & 0x01)){if (--ulLoop == 0) {return FALSE;}};
        #endif
        #if 1   /* 第四版*/
        TIME_WAIT_START(10000);                             /* zhaohai2020-04-21 若写超时则返回，避免继续写造成HardFault */
        while(!(FTFC->FCNFG & 0x01)){if (--ulLoop == 0) {return FALSE;}};
        #endif
    }
    
    return TRUE;
}
/*********************************************************************************************************
** Function name:       EEPROM_Read
** Descriptions:        EEPROM读
** input parameters:    ulAdd：      地址
**                      ucLen：      长度
**                      *pucDat：    读出数据储存地址
** output parameters:   无
** Returned value:      执行结果
*********************************************************************************************************/
BOOLEAN EEPROM_Read(INT32U ulAdd, INT32U ulLen, INT8U *const pucDat)
{
    INT32U  i;
    
    if (!(FTFC->FCNFG & 0x01)) {
        return FALSE;
    }
    if ((!(ulAdd >= EEP_BASE_ADDR)) || ((ulAdd + ulLen - 1) > EEP_END_ADDR)) {
        return FALSE;
    }
    
    for (i = 0; i < ulLen; i++) {
        pucDat[i]   = ((INT8U *)ulAdd)[i];
    }
    
    return TRUE;
}

/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
