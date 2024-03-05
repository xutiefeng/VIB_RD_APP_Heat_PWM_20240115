/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           CarSign.h
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
#ifndef __CARSIGN_H
#define __CARSIGN_H

// #include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define CAR_T_UNIT                      10                              /* ����ʱ��                     */
#define CAR_T_MS(n)                     (n/CAR_T_UNIT)                  /* ʱ��궨��, n��Ϊ10�ı���    */

#define CAR_EEP_BASE_ADDR               (EEP_BASE_ADDR + 0x700)         /* CAR��ʼ��ַ 0x14000700       */
#define CAR_EEP_TOTAL_SIZE              0x100                           /* CAR�ռ��С 256Byte          */
#define CAR_EEP_END_ADDR                (CAR_EEP_BASE_ADDR + CAR_EEP_TOTAL_SIZE - 1)    /* CAR������ַ  */

#define INTCARADDRU                     INTEEPADDRU
#define INTCARSIZEU                     INTEEPSIZEU

#define CAR_POWER_MODE_HAS_ACC          FALSE                           /* ������Դģʽ�Ƿ�ACC        */
#define CAR_POWER_MODE_HAS_START        FALSE                           /* ������Դģʽ�Ƿ�START      */

/*********************************************************************************************************
** �궨��-CAR�ռ�: 0x14000700~0x140007FF
*********************************************************************************************************/
#define CAR_EEP_ADDR_SwtXXXCur          (CAR_EEP_BASE_ADDR)             /* ��δɾ�������ο� */
#define CAR_EEP_SIZE_SwtXXXCur          1

/*********************************************************************************************************
** �궨��-PIN���� DKLai20230419
*********************************************************************************************************/


/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define CAR_VEH_ENGSPD_DEFAULT          0x0000
#define CAR_VEH_SPEED_DEFAULT           0x0000
#define CAR_VEH_SPEED_INVALID           0x1FFF
#define CAR_VEH_BATT_INVALID            0x3FFF
#define CAR_VEH_SOC_INIT                0x7FE
#define CAR_VEH_SOC_FAULT               0x7FF
#define CAR_VEH_MILEAGE_INVALID         0xFFFFFF
#define CAR_VEH_MILEAGEH_INVALID        0xFF
#define CAR_VEH_MILEAGEM_INVALID        0xFF
#define CAR_VEH_MILEAGEL_INVALID        0xFF
#define CAR_VEH_TIME_YEAR_DEFAULT       0x13    /* bcd. DKLai20230506 */
#define CAR_VEH_TIME_MONTH_DEFAULT      1
#define CAR_VEH_TIME_DAY_DEFAULT        1
#define CAR_VEH_TIME_HOUR_DEFAULT       0
#define CAR_VEH_TIME_MINUTE_DEFAULT     0
#define CAR_VEH_TIME_SECOND_DEFAULT     0
#define CAR_VEH_SPEED_PHY_TO_HEX(n)     (n*160/9)                       /* n/0.05625                    */
#define CAR_VEH_SPEED_HEX_5KM           0x59                            /* 5/0.05625                    */
#define CAR_VEH_SPEED_HEX_0KM           0                               /* 0/0.05625                    */

/*********************************************************************************************************
** �ṹ��
*********************************************************************************************************/
/*--ö������: �����ź�----------------------------------------------------------------------------------*/
typedef enum {
    CAR_VEH_POWER_OFF               = 0,                            /*                              */
    CAR_VEH_POWER_ACC,                                                  /*                              */
    CAR_VEH_POWER_ON,                                             /*                              */
    CAR_VEH_POWER_CRANK,                                            /*                              */         /*                              */
} CAR_VEH_POWER_ENUM;   /* DKLai20230504 */

/*--ö������: �����ź�----------------------------------------------------------------------------------*/

/************************************************/
/*--ö������: ------------------------------------------------------------------------------------------*/
typedef enum {
    CAR_CTRL_MODE_ECU                   = 0,                            /*                              */
    CAR_CTRL_MODE_TESTER,                                               /*                              */
} CAR_CTRL_MODE_ENUM;

typedef enum {
    CAR_CFGSWT_NO                       = 0,                            /*                              */
    CAR_CFGSWT_INACTIVE,                                                /*                              */
    CAR_CFGSWT_ACTIVE,                                                  /*                              */
    CAR_CFGSWT_RESERVED,                                                /*                              */
} CAR_CFGSWT_ENUM;

/*********************************************************************************************************
** �ṹ��
*********************************************************************************************************/
typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  SwtXXXCur                       :1;                     /*                              */
    } Bits;
} CarFlagEepWrtUnion;

typedef union {
    INT8U   Byte[2];
    struct {
        INTCPU  SwtXXXCur                       :1;                     /*                              */
    } Bits;
} CarFlagEepRadUnion;

typedef enum {
    CAR_DEAL_MODECUR_DEFAULT                    = 0,                    /* Ĭ��                         */
    CAR_DEAL_MODECUR_LPPOWER_ON,                                        /*                              */
    CAR_DEAL_MODECUR_DELAY,                                             /*                              */
} CAR_DEAL_MODECUR_ENUM;

/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    CAR_VEH_POWER_ENUM      VehPowerCur;                                /* ������Դģʽ                 */
    CAR_VEH_POWER_ENUM      VehPowerPre;                                /* ������Դģʽ                 */
    
    /* CAN �����źŶ�Ӧ�ı��� */
    CAR_VEH_POWER_ENUM      VehBcmPowerCur;                             /* BCM��Դģʽ                  */
    CAR_VEH_POWER_ENUM      VehBcmPowerPre;                             /* BCM��Դģʽ                  */
    
    INT16U                  VehSpeedCur;                                /* ����                         */
    INT16U                  VehSpeedPre;                                /* ����                         */
    INT16U                  VehSpeedProgram;                            /* ����-�������ʹ��             */
    
    INT32U                  VehMileage;                                 /* �����                       */
    INT8U                   VehMileageH;                                /*                              */
    INT8U                   VehMileageM;                                /*                              */
    INT8U                   VehMileageL;                                /*                              */
    
    INT8U                   VehTimeYear;                                /* ��                           */
    INT8U                   VehTimeMonth;                               /* ��                           */
    INT8U                   VehTimeDay;                                 /* ��                           */
    INT8U                   VehTimeHour;                                /* ʱ                           */
    INT8U                   VehTimeMinute;                              /* ��                           */
    INT8U                   VehTimeSecond;                              /* ��                           */
    
    INT16U                  VehBattCur;                                 /* ��ص�ѹ                     */
    INT16U                  VehBattPre;                                 /* ��ص�ѹ                     */
    
    /* CAN �����źŶ�Ӧ�ı��� */
    /* ���ͱ���XXX */
    
    
    /* Ӳ���źŶ�Ӧ�ı��� */

    /***************************************/
    CAR_CTRL_MODE_ENUM      CtrlModeCur;                                /* ����ģʽ                     */
    CAR_CTRL_MODE_ENUM      CtrlModePre;                                /* ����ģʽ                     */
    CAR_CFGSWT_ENUM         SwtXXXCur;                                  /* XXX����                      */
    CAR_CFGSWT_ENUM         SwtXXXPre;                                  /* XXX����                      */
} CarStatStruct;
typedef struct {
    INT32U                  DealModeCur;                                /*                              */
} CarTimeStruct;

typedef struct {
    CarFlagEepWrtUnion      EepWrt;                                     /*                              */
    CarFlagEepRadUnion      EepRad;                                     /*                              */
} CarFlagStruct;

typedef struct {
    CAR_DEAL_MODECUR_ENUM   DealModeCur;                                /* ���̿���                     */
} CarTaskStruct;

/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    CarStatStruct           Stat;
    CarTimeStruct           Time;
    CarFlagStruct           Flag;
    CarTaskStruct           Task;
} CarInfoStruct;

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/

/*********************************************************************************************************
** ȫ�ֱ���
*********************************************************************************************************/
extern  volatile CarInfoStruct      CarInfo;                            /* ������Ϣ                     */

/* DKLai20230504 */
#define CAR_VEH_POWER_MODE_IS_OFF()                         (CarInfo.Stat.VehPowerCur == CAR_VEH_POWER_OFF)
#define CAR_VEH_POWER_MODE_IS_IGN()                         (CarInfo.Stat.VehPowerCur == CAR_VEH_POWER_ON)

#define CarInfo_Flag_EepWrt_SwtXXXCur                       CarInfo.Flag.EepWrt.Bits.SwtXXXCur

#define CarInfo_Flag_EepRad_SwtXXXCur                       CarInfo.Flag.EepRad.Bits.SwtXXXCur

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  void                    CarSign_Init(void);
extern  void                    CarSign_TimeTask(void);
extern  void                    CarSign_StatTask(void);

extern  BOOLEAN                 CarSign_SleepLocAllow(void);
extern  BOOLEAN                 CarSign_SleepBusAllow(void);
extern  void                    CarSign_SleepBusAllowSet(void);
extern  void                    CarSign_SleepBusAllowClr(void);
extern  BOOLEAN                 CarSign_ProgramAllow(void);
extern  void                    CarSign_ModeTesterStart(INT8U ucCtrlStat, INT8U ucCtrlMask);
extern  void                    CarSign_ModeTesterStop(void);

/******************************************* Private Function *******************************************/
extern  void                    CarSign_UpDateSignFromCan(void);
extern  void                    CarSign_DealSignFromCan(void);
extern  void                    CarSign_UpDateSignForCan(void);

extern  void                    CarSign_UpdateVehPower(void);

extern  STAT_MSG_RESULT_ENUM    CarSign_ReadFromEep(INTCARADDRU Add, INTCARSIZEU Len, INT8U *pucDatDst, EEP_EXTRA_ENUM euExtra);
extern  STAT_MSG_RESULT_ENUM    CarSign_WriteToEep(INTCARADDRU Add, INTCARSIZEU Len, INT8U *pucDatSor, EEP_EXTRA_ENUM euExtra);
extern  void                    CarSign_WriteEepTask(void);
extern  void                    CarSign_ReadEepTask(void);

extern  void                    CarSign_DealCpuSleep(void);

static  void                    CAR_ERROR(INT8U ucErr);

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __CARSIGN_H                 */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
