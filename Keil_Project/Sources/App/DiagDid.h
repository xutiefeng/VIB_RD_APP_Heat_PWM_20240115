
/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           DiagDid.h
** Last modified Date:  2018-11-14
** Last Version:        V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2018-11-14
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
#ifndef __DIAGDID_H
#define __DIAGDID_H

#include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** 宏定义
*********************************************************************************************************/
#define DID_EEP_BASE_ADDR               (EEP_BASE_ADDR + 0x100)         /* DID起始地址     0x14000100   */
#define DID_EEP_TOTAL_SIZE              0x100                           /* DID空间大小     256Byte      */
#define DID_EEP_END_ADDR                (DID_EEP_BASE_ADDR + DID_EEP_TOTAL_SIZE - 1)    /* DID结束地址  */
#define DID_EEP_BAK_OFFSET              DID_EEP_TOTAL_SIZE              /* DID备份偏移地址 0x14000200   */
#define DID_EEP_BUF_MAX                 50                              /* DID数据最大长度 DKLai20230421 */

#define INTDIDADDRU                     INTEEPADDRU
#define INTDIDSIZEU                     INTEEPSIZEU

/* DKLai20230419 */
#define DID_2F_VIB_CTRL                (0xF100)    /* DKLai20230421 */

/*********************************************************************************************************
** 宏定义: EEP中的EEP表(APP或FBL写，APP或FBL读)
**         每一组数据：数据区 + 数据修改标记('w') + CRC8校验
**         DID空间: 0x14000100~0x140003FF
**         BAK空间: 0x14000400~0x140006FF  DKLai20230421
*********************************************************************************************************/
#define DID_EEP_ADDR_F18C               (DID_EEP_BASE_ADDR)
#define DID_EEP_SIZE_F18C               21
#define DID_EEP_ADDR_F190               (DID_EEP_ADDR_F18C + DID_EEP_SIZE_F18C + 2)
#define DID_EEP_SIZE_F190               17
#define DID_EEP_ADDR_F102               (DID_EEP_ADDR_F190 + DID_EEP_SIZE_F190 + 2)
#define DID_EEP_SIZE_F102               17
#define DID_EEP_ADDR_F103               (DID_EEP_ADDR_F102 + DID_EEP_SIZE_F102 + 2)
#define DID_EEP_SIZE_F103               50
#define DID_EEP_ADDR_0110               (DID_EEP_ADDR_F103 + DID_EEP_SIZE_F103 + 2)
#define DID_EEP_SIZE_0110               1

#define DID_EEP_ADDR_F184               DIAG_EEP_ADDR_FINGERPRINT
#define DID_EEP_SIZE_F184               DIAG_EEP_SIZE_FINGERPRINT

/* DKLai20230421 */
#define DID_EEP_ADDR_0201               DIAG_EEP_ADDR_PROGATTCNT
#define DID_EEP_SIZE_0201               DIAG_EEP_SIZE_PROGATTCNT
#define DID_EEP_ADDR_0200               DIAG_EEP_ADDR_PROGSUCCCNT
#define DID_EEP_SIZE_0200               DIAG_EEP_SIZE_PROGSUCCCNT

/* DKLai20230421 */
#define DID_EEP_ADDR_F199               DIAG_EEP_ADDR_PROGRAMDATE
#define DID_EEP_SIZE_F199               DIAG_EEP_SIZE_PROGRAMDATE

/*********************************************************************************************************
** 宏定义: APP中的ROM表(APP只读，FBL从APP的指定地址只读，在线升级后自动更新) DKLai20230421
*********************************************************************************************************/
#define DID_ROM_ADDR_F189               0x0001F400                      /* 车厂软件版本号               */
#define DID_ROM_SIZE_F189               17
#define DID_ROM_ADDR_F193               0x0001F420                      /* hardwarenumber DKLai20230421 */
#define DID_ROM_SIZE_F193               4
#define DID_ROM_ADDR_F195               0x0001F430                      /* 供应商软件版本号             */
#define DID_ROM_SIZE_F195               4

/*********************************************************************************************************
** 宏定义: FBL中的ROM表(FBL只读，APP从FBL的指定地址只读，在线升级后不更新) DKLai20230421
*********************************************************************************************************/
#define DID_ROM_ADDR_F17F               0x00009C00                      /* 车厂零件号                   */
#define DID_ROM_SIZE_F17F               17
#define DID_ROM_ADDR_F180               0x00009C20                      /* BootLoader软件版本号         */
#define DID_ROM_SIZE_F180               17
#define DID_ROM_ADDR_F187               0x00009C40                      /* 事业部零件号                 */
#define DID_ROM_SIZE_F187               14
#define DID_ROM_ADDR_F18E               0x00009C60                      /* DKLai20230421                */
#define DID_ROM_SIZE_F18E               14

/*********************************************************************************************************
** 结构体: 函数指针
*********************************************************************************************************/
#define DID_22_LIST_LEN                 19
#define DID_2E_LIST_LEN                 5     /* DKLai20230426 */
#define DID_2F_LIST_LEN                 1
typedef DIAG_NRC_ENUM                   (*DID22Func)(INT8U *pucDatDst, INT16U *usLen);
typedef DIAG_NRC_ENUM                   (*DID2EFunc)(INT8U *pucDatSor, INT16U *usLen);
typedef DIAG_NRC_ENUM                   (*DID2FFunc)(INT8U ucCtrlType, INT8U ucCtrlStat, INT8U ucCtrlMask);
typedef struct {
    INT16U      usDid;
    DID22Func   pFunc;
} DID_22_TYPE;
typedef struct {
    INT16U      usDid;
    DID2EFunc   pFunc;
} DID_2E_TYPE;
typedef struct {
    INT16U      usDid;
    DID2FFunc   pFunc;
} DID_2F_TYPE;

/*********************************************************************************************************
** 全局定量: EEPROM中数据的默认值
*********************************************************************************************************/
extern  const INT8U             DID_ROM_F18C_TBL[DID_EEP_SIZE_F18C];
extern  const INT8U             DID_ROM_F190_TBL[DID_EEP_SIZE_F190];

extern  const INT8U             DID_ROM_F184_TBL[DID_EEP_SIZE_F184];

/* DKLai20230421 */
extern  const INT8U             DID_ROM_F102_TBL[DID_EEP_SIZE_F102];
extern  const INT8U             DID_ROM_F103_TBL[DID_EEP_SIZE_F103]; 

/* DKLai20230421 */
extern  const INT8U             DID_ROM_F199_TBL[DID_EEP_SIZE_F199];

/*********************************************************************************************************
** 全局定量: APP中的ROM表
*********************************************************************************************************/
extern  const INT8U             DID_ROM_F189_TBL[DID_ROM_SIZE_F189];
extern  const INT8U             DID_ROM_F193_TBL[DID_ROM_SIZE_F193]; /* DKLai20230421 */
extern  const INT8U             DID_ROM_F195_TBL[DID_ROM_SIZE_F195];

/*********************************************************************************************************
** 全局定量: FBL中的ROM表
*********************************************************************************************************/

/*********************************************************************************************************
** 全局变量
*********************************************************************************************************/
extern  volatile DID_22_TYPE    DID22List[DID_22_LIST_LEN];
extern  volatile DID_2E_TYPE    DID2EList[DID_2E_LIST_LEN];
extern  volatile DID_2F_TYPE    DID2FList[DID_2F_LIST_LEN];

/*********************************************************************************************************
** 函数声明
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    DiagDid_Init(void);

extern  STAT_MSG_RESULT_ENUM    DiagDid_ReadFromEep(INTDIDADDRU Add, INTDIDADDRU Len, INT8U *pucDatDst, EEP_EXTRA_ENUM euExtra);
extern  STAT_MSG_RESULT_ENUM    DiagDid_WriteToEep(INTDIDADDRU Add, INTDIDADDRU Len, INT8U *pucDatSor, EEP_EXTRA_ENUM euExtra);

extern  void                    GetDataFromRom(INT8U *pData, const INT8U *pRom, INT16U usLen);
extern  BOOLEAN                 ChckDateIsCorrect(INT8U *pData);
extern  BOOLEAN                 ChckDataIsBCD(INT8U ucBcd);
extern  BOOLEAN                 ChckDataIsASCII(INT8U *pData, INT16U usLen);
extern  BOOLEAN                 ChckDataIsSpecify(INT8U *pData, INT16U usLen, INT8U ucSpecify);

/******************************************* Private Function DKLai20230421*****************************/
static  DIAG_NRC_ENUM           DiagDid_Read_0110(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_0200(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_0201(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F102(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F103(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F17F(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F180(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F184(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F186(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F187(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F189(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F18C(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F18E(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F190(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F193(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F195(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_F199(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_1000(INT8U *pucDatDst, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Read_1002(INT8U *pucDatDst, INT16U *usLen);

static  DIAG_NRC_ENUM           DiagDid_Write_F18C(INT8U *pucDatSor, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Write_F190(INT8U *pucDatSor, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Write_F102(INT8U *pucDatSor, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Write_F103(INT8U *pucDatSor, INT16U *usLen);
static  DIAG_NRC_ENUM           DiagDid_Write_0110(INT8U *pucDatSor, INT16U *usLen);  /* DKLai20230426 */

static  DIAG_NRC_ENUM           DiagDid_IOCtrl_LampCtrl(INT8U ucCtrlType, INT8U ucCtrlStat, INT8U ucCtrlMask);

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __DIAGDID_H                 */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
