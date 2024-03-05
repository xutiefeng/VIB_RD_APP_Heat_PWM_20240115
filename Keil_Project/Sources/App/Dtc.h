/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Dtc.h
** Last modified Date:  2018-03-08
** Last Version:        V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:          zhaohai
** Created date:        2018-03-08
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
#ifndef __DTC_H
#define __DTC_H

// #include "includeall.h"

#ifdef __cplusplus
extern  "C" {
#endif                                                                  /*  __cplusplus                 */

/*********************************************************************************************************
** �궨��
*********************************************************************************************************/
#define DTC_T_UNIT                      10                              /* ����ʱ��                     */
#define DTC_T_MS(n)                     (n/DTC_T_UNIT)                  /* ʱ��궨��, n��Ϊ10�ı���    */

/* DKLai20230419 */
#define DTC_NUM_TOTAL                   8                              /* DTC������ DKLai20230423       */

/* DKLai20230506 */
#define DTC_BUF_LEN                     36                              /* 1��DTC����������             */
#define DTC_BUF_IN_EEP_LEN              36                              /* 1��DTC��������洢��EEP�ĳ���*/

#define DTC_EEP_BASE_ADDR               (EEP_BASE_ADDR + 0x300)         /* DTC��ʼ��ַ 0x14000300       */
#define DTC_EEP_TOTAL_SIZE              0x400                           /* DTC�ռ��С 1024Byte         */
#define DTC_EEP_END_ADDR                (DTC_EEP_BASE_ADDR + DTC_EEP_TOTAL_SIZE - 1)    /* DTC������ַ  */

#define DTC_EEP_LEN_ONE                 DTC_BUF_IN_EEP_LEN              /* 1��DTC�洢��EEP�е����ݳ���  */
#define DTC_EEP_LEN_ALL                 (DTC_NUM_TOTAL * DTC_EEP_LEN_ONE)

#define INTDTCADDRU                     INTEEPADDRU
#define INTDTCSIZEU                     INTEEPSIZEU

#define DTC_AGING_CFM_NUM               40                              /* ����N�������������,����Ϊ��DTC����ʧ,���Զ����*/
#define DTC_PowerHexToPhy(n)            ((35 * (INT32U)n) / 192 + 0)    /* (0-1023)to(4-254)            */

#define DTC_FORMAT_ISO15031_6           0x00                            /* ISO15031-6��DTC��ʽ,�ܹ�4Bytes*/
#define DTC_FORMAT_ISO14229_1           0x01                            /*                              */
#define DTC_FORMAT_SAEJ1939_73          0x02                            /*                              */
#define DTC_FORMAT_MODE                 DTC_FORMAT_ISO14229_1           /* HYCAN require. DKLai20230420 */
#define DTC_STATUS_SUPPORT_MASK         0x2B                            /* ֧�ֵ�DTC״̬λ DKLai20230506 */

#define DTC_STATUS_EN_TestFailed                    (DTC_STATUS_SUPPORT_MASK & (1 << 0))
#define DTC_STATUS_EN_TestFailedThisOprCycle        (DTC_STATUS_SUPPORT_MASK & (1 << 1))
#define DTC_STATUS_EN_Pending                       (DTC_STATUS_SUPPORT_MASK & (1 << 2))
#define DTC_STATUS_EN_Confirmed                     (DTC_STATUS_SUPPORT_MASK & (1 << 3))
#define DTC_STATUS_EN_TestNotCompletedSinceLastClr  (DTC_STATUS_SUPPORT_MASK & (1 << 4))
#define DTC_STATUS_EN_TestFailedSinceLastClr        (DTC_STATUS_SUPPORT_MASK & (1 << 5))
#define DTC_STATUS_EN_TestNotCompletedThisOprCycle  (DTC_STATUS_SUPPORT_MASK & (1 << 6))
#define DTC_STATUS_EN_WarningIndicatorRequested     (DTC_STATUS_SUPPORT_MASK & (1 << 7))

#define DTC_SET_CTRL_EN                 FALSE                           /* DTC���η���ʹ��              */

#define DTC_POWER_BAT_IS_INVALID()      (DtcInfo.Stat.PowerAd1Value > AD1_BAT_MAX)
#define DTC_POWER_COMM_IS_NOR()         ((DtcInfo.Stat.PowerAd1Value >= AD1_BAT_COMM_NORMAL_L) && (DtcInfo.Stat.PowerAd1Value <= AD1_BAT_COMM_NORMAL_H))
#define DTC_POWER_COMM_IS_ERR()         ((DtcInfo.Stat.PowerAd1Value <= AD1_BAT_COMM_STOPL_H) || (DtcInfo.Stat.PowerAd1Value >= AD1_BAT_COMM_STOPH_L))
#define DTC_POWER_WORK_IS_NOR()         ((DtcInfo.Stat.PowerAd1Value >= AD1_BAT_WORK_NORMAL_L) && (DtcInfo.Stat.PowerAd1Value <= AD1_BAT_WORK_NORMAL_H))
#define DTC_POWER_WORK_IS_ERR()         ((DtcInfo.Stat.PowerAd1Value <= AD1_BAT_WORK_STOPL_H) || (DtcInfo.Stat.PowerAd1Value >= AD1_BAT_WORK_STOPH_L))
#define DTC_POWER_DIAG_IS_NOR()         ((DtcInfo.Stat.PowerAd1Value >= AD1_BAT_DIAG_NORMAL_L) && (DtcInfo.Stat.PowerAd1Value <= AD1_BAT_DIAG_NORMAL_H))
#define DTC_POWER_DIAG_IS_ERR()         ((DtcInfo.Stat.PowerAd1Value <= AD1_BAT_DIAG_STOPL_H) || (DtcInfo.Stat.PowerAd1Value >= AD1_BAT_DIAG_STOPH_L))
#define DTC_POWER_VOLT_IS_NOR()         ((DtcInfo.Stat.PowerAd1Value >= AD1_BAT_VOLT_NORMAL_L) && (DtcInfo.Stat.PowerAd1Value <= AD1_BAT_VOLT_NORMAL_H))
#define DTC_POWER_VOLT_IS_LOW()         (DtcInfo.Stat.PowerAd1Value <= AD1_BAT_VOLT_LOW_H)
#define DTC_POWER_VOLT_IS_HIGH()        (DtcInfo.Stat.PowerAd1Value >= AD1_BAT_VOLT_HIGH_L)

#define DTC_T_POWER_COMM_NOR            DTC_T_MS(200)                   /* �ͺ�Nmsȷ��ͨѶ��ѹ����      */
#define DTC_T_POWER_COMM_ERR            DTC_T_MS(200)                   /* �ͺ�Nmsȷ��ͨѶ��ѹ�쳣      */
#define DTC_T_POWER_WORK_NOR            DTC_T_MS(200)                   /* �ͺ�Nmsȷ�Ϲ�����ѹ����      */
#define DTC_T_POWER_WORK_ERR            DTC_T_MS(200)                   /* �ͺ�Nmsȷ�Ϲ�����ѹ�쳣      */
#define DTC_T_POWER_WORKNS_NOR          DTC_T_MS(1000)                  /* �ͺ�Nmsȷ�Ϲ�����ѹ�ȶ�Ns    */
#define DTC_T_POWER_WORKNS_CLR          DTC_T_MS(50)                    /* �ͺ�Nms���������ѹ�ȶ�Ns    */
#define DTC_T_POWER_DIAG_NOR            DTC_T_MS(1500)                  /* �ͺ�Nmsȷ����ϵ�ѹ����      */
#define DTC_T_POWER_DIAG_ERR            DTC_T_MS(200)                   /* �ͺ�Nmsȷ����ϵ�ѹ�쳣      */
#define DTC_T_POWER_VOLT_NOR            DTC_T_MS(1000)                  /* �ͺ�Nmsȷ�Ϲ��ϵ�ѹ����      */
#define DTC_T_POWER_VOLT_LOW            DTC_T_MS(1000)                  /* �ͺ�Nmsȷ�Ϲ��ϵ�ѹ��        */
#define DTC_T_POWER_VOLT_HIGH           DTC_T_MS(1000)                  /* �ͺ�Nmsȷ�Ϲ��ϵ�ѹ��        */

#define DTC_T_OFFNS                     DTC_T_MS(1500)                  /* �ͺ�Nmsȷ��OFF�ȶ�Ns         */
#define DTC_T_ACCNS                     DTC_T_MS(1500)                  /* �ͺ�Nmsȷ��ACC�ȶ�Ns         */
#define DTC_T_IGNNS                     DTC_T_MS(1500)                  /* �ͺ�Nmsȷ��IGN�ȶ�Ns         */
#define DTC_T_BUSNORNS                  DTC_T_MS(500)                   /* �ͺ�Nmsȷ��Bus�ȶ�Ns         */

/*********************************************************************************************************
** ö��
*********************************************************************************************************/
/*--ö������: ------------------------------------------------------------------------------------------*/
typedef enum {
    DTC_INIT_MODE_PWR_ON                = 0,                            /* �ϵ��ʼ��                   */
    DTC_INIT_MODE_XXXX,                                                 /* XXXX��ʼ��                   */
} DTC_INIT_MODE_ENUM;
/*--ö������: ------------------------------------------------------------------------------------------*/
typedef enum {
    DTC_WRITE_MODE_ALL                  = 0,                            /* ȫ��                         */
    DTC_WRITE_MODE_ONE,                                                 /* һ��                         */
} DTC_WRITE_MODE_ENUM;
/*--ö������: ------------------------------------------------------------------------------------------*/
typedef enum {
    DTC_NOR                             = 0,                            /* ����                         */
    DTC_ERR,                                                            /* �쳣                         */
} DTC_NOR_ERR_ENUM;

/*********************************************************************************************************
**  DTC��� DKLai20230423
*********************************************************************************************************/
#define DTC_INDX_ERR_COMPRESSOR         0           //ѹ��������
#define DTC_INDX_ERR_DISPLAY            1           //��ʾ��ͨ�Ź���
#define DTC_INDX_ERR_TEMPERATURE1       2           //�¶ȴ�����1����
#define DTC_INDX_ERR_TEMPERATURE2       3           //�¶ȴ�����2����
#define DTC_INDX_ERR_OZONE_CTRL         4           //��������������
#define DTC_INDX_ERR_HEATING            5           //���ȹ���
#define DTC_INDX_ERR_DOOR               6           //�Ź���
#define DTC_INDX_ERR_LIGHT              7           //�����ڵƹ���

#define DTC_INDX_ALL                    0xFF        //ȫ��

/*********************************************************************************************************
**  DTC���� DKLai20230423
*********************************************************************************************************/
#define DTC_CODE_ERR_COMPRESSOR           0xAD8009
#define DTC_CODE_ERR_DISPLAY              0xAD8002
#define DTC_CODE_ERR_TEMPERATURE1         0xAD8109
#define DTC_CODE_ERR_TEMPERATURE2         0xAD8209
#define DTC_CODE_ERR_OZONE_CTRL           0xAD8309
#define DTC_CODE_ERR_HEATING              0xAD8409
#define DTC_CODE_ERR_DOOR                 0xAD8509
#define DTC_CODE_ERR_LIGHT                0xAD8609

/*********************************************************************************************************
**  DTC���� DKLai20230423
*********************************************************************************************************/
typedef enum {
    DTC_TYPE_UNDEF                      = 0,                            /* δ�����DTC����              */
    DTC_TYPE_NET_BCAN,                                                  /* BCAN����DTC                  */
    DTC_TYPE_NET_LPCAN,                                                 /* LPCAN����DTC                 */
    DTC_TYPE_VOLT,                                                      /* ��ѹDTC                      */
    DTC_TYPE_APP,                                                       /* Ӧ��DTC                      */
    DTC_TYPE_ALL,                                                       /* ȫ��                         */
} DTC_TYPE_ENUM;

/* DKLai20230419 */
#define DTC_TYPE_ERR_COMPRESSOR          DTC_TYPE_APP
#define DTC_TYPE_ERR_DISPLAY             DTC_TYPE_APP
#define DTC_TYPE_ERR_TEMPERATURE1        DTC_TYPE_APP
#define DTC_TYPE_ERR_TEMPERATURE2        DTC_TYPE_APP
#define DTC_TYPE_ERR_OZONE_CTRL          DTC_TYPE_APP
#define DTC_TYPE_ERR_HEATING             DTC_TYPE_APP
#define DTC_TYPE_ERR_DOOR                DTC_TYPE_APP
#define DTC_TYPE_ERR_LIGHT               DTC_TYPE_APP


/*********************************************************************************************************
**  DTC�����ͷ��� DKLai20230423
*********************************************************************************************************/
typedef enum {
    DTC_MODELS_COM                      = 0,                            /* ����                         */
    DTC_MODELS_TCU,                                                     /* TCU����                      */
    DTC_MODELS_VCU,                                                     /* VCU����                      */
} DTC_MODELS_ENUM;

/* DKLai20230419 */
#define DTC_MODELS_ERR_COMPRESSOR          DTC_MODELS_COM
#define DTC_MODELS_ERR_DISPLAY             DTC_MODELS_COM
#define DTC_MODELS_ERR_TEMPERATURE1        DTC_MODELS_COM
#define DTC_MODELS_ERR_TEMPERATURE2        DTC_MODELS_COM
#define DTC_MODELS_ERR_OZONE_CTRL          DTC_MODELS_COM
#define DTC_MODELS_ERR_HEATING             DTC_MODELS_COM
#define DTC_MODELS_ERR_DOOR                DTC_MODELS_COM
#define DTC_MODELS_ERR_LIGHT               DTC_MODELS_COM

/*********************************************************************************************************
**  DTC��ʹ��ʱ������ DKLai20230423
*********************************************************************************************************/
typedef enum {
    DTC_MOMENT_OFF_BEFOR_NS             = 0x80,                         /* OFF��Nsǰ                    */
    DTC_MOMENT_OFF_AFTER_NS             = 0x40,                         /* OFF��Ns��                    */
    DTC_MOMENT_ACC_BEFOR_NS             = 0x20,                         /* ACC��Nsǰ                    */
    DTC_MOMENT_ACC_AFTER_NS             = 0x10,                         /* ACC��Ns��                    */
    DTC_MOMENT_IGN_BEFOR_NS             = 0x08,                         /* IGN��Nsǰ                    */
    DTC_MOMENT_IGN_AFTER_NS             = 0x04,                         /* IGN��Ns��                    */
    DTC_MOMENT_START                    = 0x02,                         /* START��                      */
    DTC_MOMENT_UNKONWN                  = 0x00,                         /* δ֪                         */
    DTC_MOMENT_ALL                      = 0xFF,                         /* ȫ��                         */
} DTC_MOMENT_ENUM;

#define DTC_MOMENT_OFF                          (DTC_MOMENT_OFF_BEFOR_NS + DTC_MOMENT_OFF_AFTER_NS)
#define DTC_MOMENT_ACC                          (DTC_MOMENT_ACC_BEFOR_NS + DTC_MOMENT_ACC_AFTER_NS)
#define DTC_MOMENT_IGN                          (DTC_MOMENT_IGN_BEFOR_NS + DTC_MOMENT_IGN_AFTER_NS)
#define DTC_MOMENT_OFF_ACC_IGN                  (DTC_MOMENT_OFF + DTC_MOMENT_ACC + DTC_MOMENT_IGN)
#define DTC_MOMENT_OFF_ACC_IGN_START            (DTC_MOMENT_OFF + DTC_MOMENT_ACC + DTC_MOMENT_IGN + DTC_MOMENT_START)
#define DTC_MOMENT_ACC_IGN                      (DTC_MOMENT_ACC + DTC_MOMENT_IGN)
#define DTC_MOMENT_ACC_IGN_START                (DTC_MOMENT_ACC + DTC_MOMENT_IGN + DTC_MOMENT_START)
#define DTC_MOMENT_OFF_AFTER_NS_ACC_IGN_START   (DTC_MOMENT_OFF_AFTER_NS + DTC_MOMENT_ACC + DTC_MOMENT_IGN + DTC_MOMENT_START)
#define DTC_MOMENT_ACC_AFTER_NS_IGN_START       (DTC_MOMENT_ACC_AFTER_NS + DTC_MOMENT_IGN + DTC_MOMENT_START)
#define DTC_MOMENT_IGN_AFTER_NS_START           (DTC_MOMENT_IGN_AFTER_NS + DTC_MOMENT_START)

/* DKLai20230419 */
#define DTC_MOMENT_ERR_COMPRESSOR          DTC_MOMENT_IGN_AFTER_NS
#define DTC_MOMENT_ERR_DISPLAY             DTC_MOMENT_IGN_AFTER_NS
#define DTC_MOMENT_ERR_TEMPERATURE1        DTC_MOMENT_IGN_AFTER_NS
#define DTC_MOMENT_ERR_TEMPERATURE2        DTC_MOMENT_IGN_AFTER_NS
#define DTC_MOMENT_ERR_OZONE_CTRL          DTC_MOMENT_IGN_AFTER_NS
#define DTC_MOMENT_ERR_HEATING             DTC_MOMENT_IGN_AFTER_NS
#define DTC_MOMENT_ERR_DOOR                DTC_MOMENT_IGN_AFTER_NS
#define DTC_MOMENT_ERR_LIGHT               DTC_MOMENT_IGN_AFTER_NS

/*********************************************************************************************************
**  DTCȷ��ʱ������ DKLai20230423
*********************************************************************************************************/
#define DTC_CFM_NUM_INIT                0x8000

/* DKLai20230419 */
#define DTC_CFM_NUM_ERR_COMPRESSOR           1
#define DTC_CFM_NUM_ERR_DISPLAY              1
#define DTC_CFM_NUM_ERR_TEMPERATURE1         1
#define DTC_CFM_NUM_ERR_TEMPERATURE2         1
#define DTC_CFM_NUM_ERR_OZONE_CTRL           1
#define DTC_CFM_NUM_ERR_HEATING              1
#define DTC_CFM_NUM_ERR_DOOR                 1
#define DTC_CFM_NUM_ERR_LIGHT                1


/*********************************************************************************************************
**  DTC�쳣�Ӽ�����λ,��DTC��ȷ����ʱ��ģʽʱ,1����λ���ڵ�������(��Ϊÿ����1�μ�һ��) DKLai20230423
*********************************************************************************************************/
/* DKLai20230419 */
#define DTC_ERR_UNIT_ERR_COMPRESSOR           1
#define DTC_ERR_UNIT_ERR_DISPLAY              1
#define DTC_ERR_UNIT_ERR_TEMPERATURE1         1
#define DTC_ERR_UNIT_ERR_TEMPERATURE2         1
#define DTC_ERR_UNIT_ERR_OZONE_CTRL           1
#define DTC_ERR_UNIT_ERR_HEATING              1
#define DTC_ERR_UNIT_ERR_DOOR                 1
#define DTC_ERR_UNIT_ERR_LIGHT                1

/*********************************************************************************************************
**  DTC������������λ  DKLai20230423
*********************************************************************************************************/
#define DTC_NOR_UNIT_ERR_COMPRESSOR           1
#define DTC_NOR_UNIT_ERR_DISPLAY              1
#define DTC_NOR_UNIT_ERR_TEMPERATURE1         1
#define DTC_NOR_UNIT_ERR_TEMPERATURE2         1
#define DTC_NOR_UNIT_ERR_OZONE_CTRL           1
#define DTC_NOR_UNIT_ERR_HEATING              1
#define DTC_NOR_UNIT_ERR_DOOR                 1
#define DTC_NOR_UNIT_ERR_LIGHT                1

#if DTC_SET_CTRL_EN

/*********************************************************************************************************
**  DTC��DtcSetCtrl[]�е�����,eg: 2,1 ��ʾ��2Byte��Bit1 DKLai20230423 
*********************************************************************************************************/
#define DTC_SET_CTRL_INDEX_ERR_COMPRESSOR           2,1
#define DTC_SET_CTRL_INDEX_ERR_DISPLAY              2,1
#define DTC_SET_CTRL_INDEX_ERR_TEMPERATURE1         2,1
#define DTC_SET_CTRL_INDEX_ERR_TEMPERATURE2         2,1
#define DTC_SET_CTRL_INDEX_ERR_OZONE_CTRL           2,1
#define DTC_SET_CTRL_INDEX_ERR_HEATING              2,1
#define DTC_SET_CTRL_INDEX_ERR_DOOR                 2,1
#define DTC_SET_CTRL_INDEX_ERR_LIGHT                2,1

#endif

/*********************************************************************************************************
**  DTC��Ӧ���ڲ���־���������
*********************************************************************************************************/
typedef void (*Dtc_FlagClrFun)(void);

/* DKLai20230423 */
#define DTC_FLAG_CLR_ERR_COMPRESSOR           NULL
#define DTC_FLAG_CLR_ERR_DISPLAY              NULL
#define DTC_FLAG_CLR_ERR_TEMPERATURE1         NULL
#define DTC_FLAG_CLR_ERR_TEMPERATURE2         NULL
#define DTC_FLAG_CLR_ERR_OZONE_CTRL           NULL
#define DTC_FLAG_CLR_ERR_HEATING              NULL
#define DTC_FLAG_CLR_ERR_DOOR                 NULL
#define DTC_FLAG_CLR_ERR_LIGHT                NULL

/*********************************************************************************************************
**  �ṹ��: �������ṹ�� DKLai20230506
*********************************************************************************************************/
typedef union {
    INT8U   Byte;
    struct {
        INT8U  TestEn                          :1;         // �Ƿ��������DTC,���ڲ�ͬ״̬�µĿ���
        INT8U  CtrlEn                          :1;         // ��δʹ��,����״̬,0-����,1-ʹ��
        INT8U  TimeMode                        :1;         // ��δʹ��,���ģʽ,0-����,1-��ʱ
        INT8U  LastSt                          :1;         // ��δʹ��,˲ʱ״̬
        INT8U  WriteToEep                      :1;         // Ϊ1��ʾ�������Eep����,����ɹ�����0
    } Bits;
} DtcConfigUnion;
typedef union {
    INT8U   Byte;
    struct {
        INT8U  TestFailed                      :1;         // ��DTC����Ĳ��Խ��Ϊʧ��//��ǰ����ȷ�ϳ���DTC
        INT8U  TestFailedThisOprCycle          :1;         // ��ǰ����ѭ�������DTC���ڹ���״̬
        INT8U  Pending                         :1;         // DTC�ڵ�ǰ��ǰһ������ѭ�����ڹ���״̬
        INT8U  Confirmed                       :1;         // DTC������ʱ����ȷ��//��ʷ���ߵ�ǰȷ�ϳ���DTC
        INT8U  TestNotCompletedSinceLastClr    :1;         // �Դ���һ�ι���������������δ���
        INT8U  TestFailedSinceLastClr          :1;         // �Դ���һ�ι�����������������ʧ��һ��
        INT8U  TestNotCompletedThisOprCycle    :1;         // ������ѭ������δ���//�ϵ�ʱ��1,һ��������ں���0
        INT8U  WarningIndicatorRequested       :1;         // ���DTC��صı���ָʾ�Ƶ�״̬
    } Bits;
} DtcStatusUnion;

/* DKLai20230504 */
typedef struct {
    INT16U  VoltFirst;                                      // ��ѹ
    INT8U   VehPowerModeFirst;                              // ��Դ״̬
    INT8U   VehOdoFirst[3];                                 // ��̱�-First
    INT8U   VehTimeFirst[6];                                // ʱ�� 
	
    INT16U  VoltLast;                                      // ��ѹ
    INT8U   VehPowerModeLast;                              // ��Դ״̬
    INT8U   VehOdoLast[3];                                 // ��̱�-First
    INT8U   VehTimeLast[6];                                // ʱ��
} DtcSnapshotStruct;

typedef struct {
    INT8U   CntOcc;                                         // �����ۼƷ�������,  �������л�Ϊ�쳣�ļ���,TestFailed��0->1�ļ���
    INT8U   CntAging;                                       // ���ϻ�����,�����������,������(NotTestFailed)����,������ڵļ����������Confirmed && ��ǰ����NotTestFailed,��ÿ��������ڼ�1;���TestFailed������(���Ͻ�Ϊ��ʷ����ʱ�ĵ������,�����˺�ʱ���DTC)
    INT8U   CntAged;                                        // ����ȥ����,���Ϊ�Զ����DTC�Ĵ���
} DtcExtendedStruct;
typedef union {
    INT8U   Buf[DTC_BUF_LEN];
    struct {                                                /* �ܼ�36Byte,���±����ʵ��ռ�ÿռ���ʵ�� DKLai20230506 */
        INT8U               CodeIndx;                       // ����, 1Byte,������0Byte,DTC�������
        DtcStatusUnion      Status;                         // ����, 1Byte,������0Byte,DTC״̬��
        DtcConfigUnion      Config;                         // ����, 1Byte,������1Byte,DTC������
        DtcSnapshotStruct   Snapshot;                       // ����,24Byte,������0Byte,��������
        DtcExtendedStruct   Extended;                       // ����, 3Byte,������1Byte,��չ����
        INT16U              CntFaultDect;                   // ����, 2Byte,������0Byte,����������,��δȷ��DTC������(�����˺�ʱPass��Fail)
        INT8U               End;                            // ����, 1Byte,������0Byte,����,��Ҫ���ڵ���ռ�ÿռ�,����ʹCrc�������1Byte��λ��,����Ӱ�����Crcʱ����(DTC_EEP_LEN_ONE - 1)���ж�
        INT8U               Crc;                            // ����, 1Byte,Crc
    } Bytes;
} DtcBufUnion;
/*********************************************************************************************************
**  �ṹ��: DTC�����̵Ŀ�����Ϣ
*********************************************************************************************************/
typedef union {
    INT8U   Byte[4];
    struct {
        INTCPU  PowerCommLive                   :1;         // ͨѶ��ѹ����Normal�ļ�ʱ״̬
        INTCPU  PowerCommNormal                 :1;         // ͨѶ��ѹ����Normal���ȶ�״̬
        INTCPU  PowerWorkLive                   :1;         // ������ѹ����Normal�ļ�ʱ״̬
        INTCPU  PowerWorkNormal                 :1;         // ������ѹ����Normal���ȶ�״̬
        INTCPU  PowerWorkNormalNs               :1;         // ������ѹ����Normal���ȶ�״̬����Ns
        INTCPU  PowerDiagLive                   :1;         // ��ϵ�ѹ����Normal�ļ�ʱ״̬
        INTCPU  PowerDiagNormal                 :1;         // ��ϵ�ѹ����Normal���ȶ�״̬
        INTCPU  PowerVoltLive                   :1;         // ���ϵ�ѹ����Normal�ļ�ʱ״̬
        INTCPU  PowerVoltNormal                 :1;         // ���ϵ�ѹ����Normal���ȶ�״̬
        INTCPU  BusNormalNs                     :1;         // ����BCAN����Normal���ȶ�״̬����Ns
        INTCPU  B2sNormalNs                     :1;         // ����LPCAN����Normal���ȶ�״̬����Ns
        INTCPU  OffNs                           :1;         // ����״̬�л���OFF�����Ns
        INTCPU  AccNs                           :1;         // ����״̬�л���ACC�����Ns
        INTCPU  IgnNs                           :1;         // ����״̬�л���IGN�����Ns
        INTCPU  OffIgn                          :1;         // �����л���OFFʱ��0,�����л���IGNʱ��1,����ʱ������һ״̬����
        INTCPU  DtcEnable                       :1;         // $85��DTC����
        INTCPU  DtcRuning                       :1;         // ����״̬
        INTCPU  IgnLostwhenIgn                  :1;         // IGNʱIGN�źŶ�ʧ
        INTCPU  EepWritting                     :1;         // ��δʹ��
    } Bits;
} DtcFlagCtrlUnion;
/*
 * ö��
 */
typedef enum {
    DTC_DEAL_XXXX_DEFAULT               = 0,                            /* Ĭ��                         */
    DTC_DEAL_XXXX_1,                                                    /*                              */
} DTC_DEAL_XXXX_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT16U                  PowerAd1Value;                              /* ��ǰϵͳ��ѹֵ(0-1023)       */
    INT8U                   PowerPhyValue;                              /* ��ǰϵͳ��ѹֵ(0-254)*0.1    */
    #if DTC_SET_CTRL_EN
    INT8U                   DtcSetCtrl[8];                              /* DTC���η��� ����=DID_EEP_SIZE_0120 */
    #endif
} DtcStatStruct;
typedef struct {
    INT32U                  PowerComm;                                  /* ͨѶ��ѹ��ʱ                 */
    INT32U                  PowerWork;                                  /* ������ѹ��ʱ                 */
    INT32U                  PowerDiag;                                  /* ��ϵ�ѹ��ʱ                 */
    INT32U                  PowerVolt;                                  /* ���ϵ�ѹ��ʱ                 */
    INT32U                  BusNormal;                                  /* ����������ʱ                 */
    INT32U                  Off;                                        /* OFF״̬��ʱ                  */
    INT32U                  Acc;                                        /* ACC״̬��ʱ                  */
    INT32U                  Ign;                                        /* IGN״̬��ʱ                  */
} DtcTimeStruct;
typedef struct {
    DtcFlagCtrlUnion        Ctrl;                                       /* DTC��ؿ�����Ϣ              */
} DtcFlagStruct;
typedef struct {
    DTC_DEAL_XXXX_ENUM      XXXX;                                       /* XXXX���̿���                 */
} DtcTaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    DtcStatStruct           Stat;
    DtcTimeStruct           Time;
    DtcFlagStruct           Flag;
    DtcTaskStruct           Task;
} DtcInfoStruct;

/*********************************************************************************************************
** ȫ�ֶ���
*********************************************************************************************************/
extern  const   INT32U  DTC_CODE_TBL[DTC_NUM_TOTAL];
extern  const   INT8U   DTC_TYPE_TBL[DTC_NUM_TOTAL];
extern  const   INT8U   DTC_MODELS_TBL[DTC_NUM_TOTAL];
extern  const   INT8U   DTC_MOMENT_TBL[DTC_NUM_TOTAL];
extern  const   INT8U   DTC_CFM_NUM_TBL[DTC_NUM_TOTAL];
extern  const   INT8U   DTC_ERR_UNIT_TBL[DTC_NUM_TOTAL];
extern  const   INT8U   DTC_NOR_UNIT_TBL[DTC_NUM_TOTAL];
#if DTC_SET_CTRL_EN
extern  const   INT8U   DTC_SET_CTRL_INDEX[DTC_NUM_TOTAL][2];
#endif
extern  const   Dtc_FlagClrFun  Dtc_FlagClrTbl[DTC_NUM_TOTAL];

#define DTCCodeHighByte(ucIndex)                            ((INT8U)(DTC_CODE_TBL[ucIndex]>>16))
#define DTCCodeMidByte(ucIndex)                             ((INT8U)(DTC_CODE_TBL[ucIndex]>>8))
#define DTCCodeLowByte(ucIndex)                             ((INT8U)(DTC_CODE_TBL[ucIndex]))

/*********************************************************************************************************
** ȫ�ֱ��� DKLai20230506
*********************************************************************************************************/
extern  volatile DtcBufUnion        DtcBuf[DTC_NUM_TOTAL];              /* ȫ��DTC�������ݻ�����        */
extern  volatile DtcInfoStruct      DtcInfo;                            /* Dtc������Ϣ                  */

#define DtcBufBuf(ucIndex)                                  (DtcBuf[ucIndex].Buf)
#define DtcBufCodeIndx(ucIndex)                             (DtcBuf[ucIndex].Bytes.CodeIndx)
#define DtcBufConfig(ucIndex)                               (DtcBuf[ucIndex].Bytes.Config.Byte)
#define DtcBufConfig_TestEn(ucIndex)                        (DtcBuf[ucIndex].Bytes.Config.Bits.TestEn)
#define DtcBufConfig_CtrlEn(ucIndex)                        (DtcBuf[ucIndex].Bytes.Config.Bits.CtrlEn)
#define DtcBufConfig_TimeMode(ucIndex)                      (DtcBuf[ucIndex].Bytes.Config.Bits.TimeMode)
#define DtcBufConfig_LastSt(ucIndex)                        (DtcBuf[ucIndex].Bytes.Config.Bits.LastSt)
#define DtcBufConfig_WriteToEep(ucIndex)                    (DtcBuf[ucIndex].Bytes.Config.Bits.WriteToEep)
#define DtcBufStatus(ucIndex)                               (DtcBuf[ucIndex].Bytes.Status.Byte)
#define DtcBufStatus_TestFailed(ucIndex)                    (DtcBuf[ucIndex].Bytes.Status.Bits.TestFailed)
#define DtcBufStatus_TestFailedThisOprCycle(ucIndex)        (DtcBuf[ucIndex].Bytes.Status.Bits.TestFailedThisOprCycle)
#define DtcBufStatus_Pending(ucIndex)                       (DtcBuf[ucIndex].Bytes.Status.Bits.Pending)
#define DtcBufStatus_Confirmed(ucIndex)                     (DtcBuf[ucIndex].Bytes.Status.Bits.Confirmed)
#define DtcBufStatus_TestNotCompletedSinceLastClr(ucIndex)  (DtcBuf[ucIndex].Bytes.Status.Bits.TestNotCompletedSinceLastClr)
#define DtcBufStatus_TestFailedSinceLastClr(ucIndex)        (DtcBuf[ucIndex].Bytes.Status.Bits.TestFailedSinceLastClr)
#define DtcBufStatus_TestNotCompletedThisOprCycle(ucIndex)  (DtcBuf[ucIndex].Bytes.Status.Bits.TestNotCompletedThisOprCycle)
#define DtcBufStatus_WarningIndicatorRequested(ucIndex)     (DtcBuf[ucIndex].Bytes.Status.Bits.WarningIndicatorRequested)

#define DtcBufSnapshot_VoltFirst(ucIndex)                   (DtcBuf[ucIndex].Bytes.Snapshot.VoltFirst)
#define DtcBufSnapshot_VehPowerModeFirst(ucIndex)           (DtcBuf[ucIndex].Bytes.Snapshot.VehPowerModeFirst)
#define DtcBufSnapshot_VehOdoFirstH(ucIndex)                (DtcBuf[ucIndex].Bytes.Snapshot.VehOdoFirst[0])
#define DtcBufSnapshot_VehOdoFirstM(ucIndex)                (DtcBuf[ucIndex].Bytes.Snapshot.VehOdoFirst[1])
#define DtcBufSnapshot_VehOdoFirstL(ucIndex)                (DtcBuf[ucIndex].Bytes.Snapshot.VehOdoFirst[2])
#define DtcBufSnapshot_VehTimeYearFirst(ucIndex)            (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeFirst[0])
#define DtcBufSnapshot_VehTimeMonthFirst(ucIndex)           (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeFirst[1])
#define DtcBufSnapshot_VehTimeDayFirst(ucIndex)             (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeFirst[2])
#define DtcBufSnapshot_VehTimeHourFirst(ucIndex)            (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeFirst[3])
#define DtcBufSnapshot_VehTimeMinuteFirst(ucIndex)          (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeFirst[4])
#define DtcBufSnapshot_VehTimeSecondFirst(ucIndex)          (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeFirst[5])

#define DtcBufSnapshot_VoltLast(ucIndex)                    (DtcBuf[ucIndex].Bytes.Snapshot.VoltLast)
#define DtcBufSnapshot_VehPowerModeLast(ucIndex)            (DtcBuf[ucIndex].Bytes.Snapshot.VehPowerModeLast)
#define DtcBufSnapshot_VehOdoLastH(ucIndex)                 (DtcBuf[ucIndex].Bytes.Snapshot.VehOdoLast[0])
#define DtcBufSnapshot_VehOdoLastM(ucIndex)                 (DtcBuf[ucIndex].Bytes.Snapshot.VehOdoLast[1])
#define DtcBufSnapshot_VehOdoLastL(ucIndex)                 (DtcBuf[ucIndex].Bytes.Snapshot.VehOdoLast[2])
#define DtcBufSnapshot_VehTimeYearLast(ucIndex)             (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeLast[0])
#define DtcBufSnapshot_VehTimeMonthLast(ucIndex)            (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeLast[1])
#define DtcBufSnapshot_VehTimeDayLast(ucIndex)              (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeLast[2])
#define DtcBufSnapshot_VehTimeHourLast(ucIndex)             (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeLast[3])
#define DtcBufSnapshot_VehTimeMinuteLast(ucIndex)           (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeLast[4])
#define DtcBufSnapshot_VehTimeSecondLast(ucIndex)           (DtcBuf[ucIndex].Bytes.Snapshot.VehTimeLast[5])

#define DtcBufExtended_CntOcc(ucIndex)                      (DtcBuf[ucIndex].Bytes.Extended.CntOcc)
#define DtcBufExtended_CntAging(ucIndex)                    (DtcBuf[ucIndex].Bytes.Extended.CntAging)
#define DtcBufExtended_CntAged(ucIndex)                     (DtcBuf[ucIndex].Bytes.Extended.CntAged)
#define DtcBufCntFaultDect(ucIndex)                         (DtcBuf[ucIndex].Bytes.CntFaultDect)

/*#define DtcBufEnd(ucIndex)                                (DtcBuf[ucIndex].Bytes.End)*/

#define DtcBufCrc(ucIndex)                                  (DtcBuf[ucIndex].Bytes.Crc)

#define DtcInfo_Flag_PowerCommLive                          DtcInfo.Flag.Ctrl.Bits.PowerCommLive
#define DtcInfo_Flag_PowerCommNormal                        DtcInfo.Flag.Ctrl.Bits.PowerCommNormal
#define DtcInfo_Flag_PowerWorkLive                          DtcInfo.Flag.Ctrl.Bits.PowerWorkLive
#define DtcInfo_Flag_PowerWorkNormal                        DtcInfo.Flag.Ctrl.Bits.PowerWorkNormal
#define DtcInfo_Flag_PowerWorkNormalNs                      DtcInfo.Flag.Ctrl.Bits.PowerWorkNormalNs
#define DtcInfo_Flag_PowerDiagLive                          DtcInfo.Flag.Ctrl.Bits.PowerDiagLive
#define DtcInfo_Flag_PowerDiagNormal                        DtcInfo.Flag.Ctrl.Bits.PowerDiagNormal
#define DtcInfo_Flag_PowerVoltLive                          DtcInfo.Flag.Ctrl.Bits.PowerVoltLive
#define DtcInfo_Flag_PowerVoltNormal                        DtcInfo.Flag.Ctrl.Bits.PowerVoltNormal
#define DtcInfo_Flag_BusNormalNs                            DtcInfo.Flag.Ctrl.Bits.BusNormalNs
#define DtcInfo_Flag_B2sNormalNs                            DtcInfo.Flag.Ctrl.Bits.B2sNormalNs
#define DtcInfo_Flag_OffNs                                  DtcInfo.Flag.Ctrl.Bits.OffNs
#define DtcInfo_Flag_AccNs                                  DtcInfo.Flag.Ctrl.Bits.AccNs
#define DtcInfo_Flag_IgnNs                                  DtcInfo.Flag.Ctrl.Bits.IgnNs
#define DtcInfo_Flag_OffIgn                                 DtcInfo.Flag.Ctrl.Bits.OffIgn
#define DtcInfo_Flag_DtcEnable                              DtcInfo.Flag.Ctrl.Bits.DtcEnable
#define DtcInfo_Flag_DtcRuning                              DtcInfo.Flag.Ctrl.Bits.DtcRuning
#define DtcInfo_Flag_IgnLostwhenIgn                         DtcInfo.Flag.Ctrl.Bits.IgnLostwhenIgn
#define DtcInfo_Flag_EepWritting                            DtcInfo.Flag.Ctrl.Bits.EepWritting

/*********************************************************************************************************
** ��������
*********************************************************************************************************/
/******************************************* Public  Function *******************************************/
extern  STAT_MSG_RESULT_ENUM    Dtc_Init(DTC_INIT_MODE_ENUM euMode);
extern  STAT_MSG_RESULT_ENUM    Dtc_ReadOneFromEep(INT8U ucIndex, INT8U *pucDatDst);
extern  STAT_MSG_RESULT_ENUM    Dtc_WriteOneToEep(INT8U ucIndex, INT8U *pucDatSor);
extern  STAT_MSG_RESULT_ENUM    Dtc_ClrDtc(INT8U ucIndex);
extern  STAT_MSG_RESULT_ENUM    Dtc_ResetDtc(INT8U ucIndex, DTC_TYPE_ENUM euType);
extern  void                    Dtc_ResetFlag(DTC_MOMENT_ENUM euMoment, DTC_TYPE_ENUM euType);
extern  STAT_MSG_RESULT_ENUM    Dtc_UpdateDtcBuf(INT8U ucIndex, DTC_NOR_ERR_ENUM euNorErr);
extern  void                    Dtc_UpdateBattFlagTask(void);
extern  void                    Dtc_UpdateCtrlFlagTask(void);
extern  void                    Dtc_UpdateDtcTask(void);
extern  STAT_MSG_RESULT_ENUM    Dtc_WriteEepTask(DTC_WRITE_MODE_ENUM euMode);
extern  void                    Dtc_TimeTask(void);
extern  void                    Dtc_StatTask(void);

extern  STAT_MSG_RESULT_ENUM    Dtc_OprCycleStart(INT8U ucIndex);
extern  STAT_MSG_RESULT_ENUM    Dtc_OprCycleStop(INT8U ucIndex);
extern  DTC_MOMENT_ENUM         Dtc_EnableMomentGet(INT8U ucIndex);

/******************************************* Private Function *******************************************/

/*********************************************************************************************************
**
*********************************************************************************************************/
#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  __DTC_H                     */
/*********************************************************************************************************
** END FILE
*********************************************************************************************************/
