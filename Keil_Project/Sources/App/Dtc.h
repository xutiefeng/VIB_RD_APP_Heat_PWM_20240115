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
** 宏定义
*********************************************************************************************************/
#define DTC_T_UNIT                      10                              /* 调度时间                     */
#define DTC_T_MS(n)                     (n/DTC_T_UNIT)                  /* 时间宏定义, n需为10的倍数    */

/* DKLai20230419 */
#define DTC_NUM_TOTAL                   8                              /* DTC总数量 DKLai20230423       */

/* DKLai20230506 */
#define DTC_BUF_LEN                     36                              /* 1个DTC缓冲区长度             */
#define DTC_BUF_IN_EEP_LEN              36                              /* 1个DTC缓冲区需存储在EEP的长度*/

#define DTC_EEP_BASE_ADDR               (EEP_BASE_ADDR + 0x300)         /* DTC起始地址 0x14000300       */
#define DTC_EEP_TOTAL_SIZE              0x400                           /* DTC空间大小 1024Byte         */
#define DTC_EEP_END_ADDR                (DTC_EEP_BASE_ADDR + DTC_EEP_TOTAL_SIZE - 1)    /* DTC结束地址  */

#define DTC_EEP_LEN_ONE                 DTC_BUF_IN_EEP_LEN              /* 1个DTC存储在EEP中的数据长度  */
#define DTC_EEP_LEN_ALL                 (DTC_NUM_TOTAL * DTC_EEP_LEN_ONE)

#define INTDTCADDRU                     INTEEPADDRU
#define INTDTCSIZEU                     INTEEPSIZEU

#define DTC_AGING_CFM_NUM               40                              /* 连续N个点火周期正常,则认为该DTC已消失,则自动清除*/
#define DTC_PowerHexToPhy(n)            ((35 * (INT32U)n) / 192 + 0)    /* (0-1023)to(4-254)            */

#define DTC_FORMAT_ISO15031_6           0x00                            /* ISO15031-6的DTC格式,总共4Bytes*/
#define DTC_FORMAT_ISO14229_1           0x01                            /*                              */
#define DTC_FORMAT_SAEJ1939_73          0x02                            /*                              */
#define DTC_FORMAT_MODE                 DTC_FORMAT_ISO14229_1           /* HYCAN require. DKLai20230420 */
#define DTC_STATUS_SUPPORT_MASK         0x2B                            /* 支持的DTC状态位 DKLai20230506 */

#define DTC_STATUS_EN_TestFailed                    (DTC_STATUS_SUPPORT_MASK & (1 << 0))
#define DTC_STATUS_EN_TestFailedThisOprCycle        (DTC_STATUS_SUPPORT_MASK & (1 << 1))
#define DTC_STATUS_EN_Pending                       (DTC_STATUS_SUPPORT_MASK & (1 << 2))
#define DTC_STATUS_EN_Confirmed                     (DTC_STATUS_SUPPORT_MASK & (1 << 3))
#define DTC_STATUS_EN_TestNotCompletedSinceLastClr  (DTC_STATUS_SUPPORT_MASK & (1 << 4))
#define DTC_STATUS_EN_TestFailedSinceLastClr        (DTC_STATUS_SUPPORT_MASK & (1 << 5))
#define DTC_STATUS_EN_TestNotCompletedThisOprCycle  (DTC_STATUS_SUPPORT_MASK & (1 << 6))
#define DTC_STATUS_EN_WarningIndicatorRequested     (DTC_STATUS_SUPPORT_MASK & (1 << 7))

#define DTC_SET_CTRL_EN                 FALSE                           /* DTC屏蔽方案使能              */

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

#define DTC_T_POWER_COMM_NOR            DTC_T_MS(200)                   /* 滞后Nms确认通讯电压正常      */
#define DTC_T_POWER_COMM_ERR            DTC_T_MS(200)                   /* 滞后Nms确认通讯电压异常      */
#define DTC_T_POWER_WORK_NOR            DTC_T_MS(200)                   /* 滞后Nms确认工作电压正常      */
#define DTC_T_POWER_WORK_ERR            DTC_T_MS(200)                   /* 滞后Nms确认工作电压异常      */
#define DTC_T_POWER_WORKNS_NOR          DTC_T_MS(1000)                  /* 滞后Nms确认工作电压稳定Ns    */
#define DTC_T_POWER_WORKNS_CLR          DTC_T_MS(50)                    /* 滞后Nms清除工作电压稳定Ns    */
#define DTC_T_POWER_DIAG_NOR            DTC_T_MS(1500)                  /* 滞后Nms确认诊断电压正常      */
#define DTC_T_POWER_DIAG_ERR            DTC_T_MS(200)                   /* 滞后Nms确认诊断电压异常      */
#define DTC_T_POWER_VOLT_NOR            DTC_T_MS(1000)                  /* 滞后Nms确认故障电压正常      */
#define DTC_T_POWER_VOLT_LOW            DTC_T_MS(1000)                  /* 滞后Nms确认故障电压低        */
#define DTC_T_POWER_VOLT_HIGH           DTC_T_MS(1000)                  /* 滞后Nms确认故障电压高        */

#define DTC_T_OFFNS                     DTC_T_MS(1500)                  /* 滞后Nms确认OFF稳定Ns         */
#define DTC_T_ACCNS                     DTC_T_MS(1500)                  /* 滞后Nms确认ACC稳定Ns         */
#define DTC_T_IGNNS                     DTC_T_MS(1500)                  /* 滞后Nms确认IGN稳定Ns         */
#define DTC_T_BUSNORNS                  DTC_T_MS(500)                   /* 滞后Nms确认Bus稳定Ns         */

/*********************************************************************************************************
** 枚举
*********************************************************************************************************/
/*--枚举类型: ------------------------------------------------------------------------------------------*/
typedef enum {
    DTC_INIT_MODE_PWR_ON                = 0,                            /* 上电初始化                   */
    DTC_INIT_MODE_XXXX,                                                 /* XXXX初始化                   */
} DTC_INIT_MODE_ENUM;
/*--枚举类型: ------------------------------------------------------------------------------------------*/
typedef enum {
    DTC_WRITE_MODE_ALL                  = 0,                            /* 全部                         */
    DTC_WRITE_MODE_ONE,                                                 /* 一个                         */
} DTC_WRITE_MODE_ENUM;
/*--枚举类型: ------------------------------------------------------------------------------------------*/
typedef enum {
    DTC_NOR                             = 0,                            /* 正常                         */
    DTC_ERR,                                                            /* 异常                         */
} DTC_NOR_ERR_ENUM;

/*********************************************************************************************************
**  DTC序号 DKLai20230423
*********************************************************************************************************/
#define DTC_INDX_ERR_COMPRESSOR         0           //压缩机故障
#define DTC_INDX_ERR_DISPLAY            1           //显示器通信故障
#define DTC_INDX_ERR_TEMPERATURE1       2           //温度传感器1故障
#define DTC_INDX_ERR_TEMPERATURE2       3           //温度传感器2故障
#define DTC_INDX_ERR_OZONE_CTRL         4           //臭氧控制器故障
#define DTC_INDX_ERR_HEATING            5           //制热故障
#define DTC_INDX_ERR_DOOR               6           //门故障
#define DTC_INDX_ERR_LIGHT              7           //冰箱内灯故障

#define DTC_INDX_ALL                    0xFF        //全部

/*********************************************************************************************************
**  DTC编码 DKLai20230423
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
**  DTC类型 DKLai20230423
*********************************************************************************************************/
typedef enum {
    DTC_TYPE_UNDEF                      = 0,                            /* 未定义的DTC类型              */
    DTC_TYPE_NET_BCAN,                                                  /* BCAN网络DTC                  */
    DTC_TYPE_NET_LPCAN,                                                 /* LPCAN网络DTC                 */
    DTC_TYPE_VOLT,                                                      /* 电压DTC                      */
    DTC_TYPE_APP,                                                       /* 应用DTC                      */
    DTC_TYPE_ALL,                                                       /* 全部                         */
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
**  DTC按车型分类 DKLai20230423
*********************************************************************************************************/
typedef enum {
    DTC_MODELS_COM                      = 0,                            /* 公共                         */
    DTC_MODELS_TCU,                                                     /* TCU车型                      */
    DTC_MODELS_VCU,                                                     /* VCU车型                      */
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
**  DTC按使能时机分类 DKLai20230423
*********************************************************************************************************/
typedef enum {
    DTC_MOMENT_OFF_BEFOR_NS             = 0x80,                         /* OFF档Ns前                    */
    DTC_MOMENT_OFF_AFTER_NS             = 0x40,                         /* OFF档Ns后                    */
    DTC_MOMENT_ACC_BEFOR_NS             = 0x20,                         /* ACC档Ns前                    */
    DTC_MOMENT_ACC_AFTER_NS             = 0x10,                         /* ACC档Ns后                    */
    DTC_MOMENT_IGN_BEFOR_NS             = 0x08,                         /* IGN档Ns前                    */
    DTC_MOMENT_IGN_AFTER_NS             = 0x04,                         /* IGN档Ns后                    */
    DTC_MOMENT_START                    = 0x02,                         /* START档                      */
    DTC_MOMENT_UNKONWN                  = 0x00,                         /* 未知                         */
    DTC_MOMENT_ALL                      = 0xFF,                         /* 全部                         */
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
**  DTC确认时间或次数 DKLai20230423
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
**  DTC异常加计数单位,当DTC的确认是时间模式时,1个单位等于调用周期(因为每调用1次加一次) DKLai20230423
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
**  DTC正常减计数单位  DKLai20230423
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
**  DTC在DtcSetCtrl[]中的索引,eg: 2,1 表示第2Byte第Bit1 DKLai20230423 
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
**  DTC对应的内部标志的清除函数
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
**  结构体: 缓冲区结构体 DKLai20230506
*********************************************************************************************************/
typedef union {
    INT8U   Byte;
    struct {
        INT8U  TestEn                          :1;         // 是否允许检测该DTC,用于不同状态下的控制
        INT8U  CtrlEn                          :1;         // 暂未使用,屏蔽状态,0-禁能,1-使能
        INT8U  TimeMode                        :1;         // 暂未使用,检测模式,0-计数,1-计时
        INT8U  LastSt                          :1;         // 暂未使用,瞬时状态
        INT8U  WriteToEep                      :1;         // 为1表示必须进行Eep保存,保存成功后清0
    } Bits;
} DtcConfigUnion;
typedef union {
    INT8U   Byte;
    struct {
        INT8U  TestFailed                      :1;         // 该DTC最近的测试结果为失败//当前周期确认出现DTC
        INT8U  TestFailedThisOprCycle          :1;         // 当前监视循环报告该DTC处于故障状态
        INT8U  Pending                         :1;         // DTC在当前或前一个监视循环处于故障状态
        INT8U  Confirmed                       :1;         // DTC在请求时经过确认//历史或者当前确认出现DTC
        INT8U  TestNotCompletedSinceLastClr    :1;         // 自从上一次故障码清除后测试尚未完成
        INT8U  TestFailedSinceLastClr          :1;         // 自从上一次故障码清除后测试至少失败一次
        INT8U  TestNotCompletedThisOprCycle    :1;         // 本监视循环测试未完成//上电时置1,一定检测周期后清0
        INT8U  WarningIndicatorRequested       :1;         // 与该DTC相关的报警指示灯的状态
    } Bits;
} DtcStatusUnion;

/* DKLai20230504 */
typedef struct {
    INT16U  VoltFirst;                                      // 电压
    INT8U   VehPowerModeFirst;                              // 电源状态
    INT8U   VehOdoFirst[3];                                 // 里程表-First
    INT8U   VehTimeFirst[6];                                // 时间 
	
    INT16U  VoltLast;                                      // 电压
    INT8U   VehPowerModeLast;                              // 电源状态
    INT8U   VehOdoLast[3];                                 // 里程表-First
    INT8U   VehTimeLast[6];                                // 时间
} DtcSnapshotStruct;

typedef struct {
    INT8U   CntOcc;                                         // 计数累计发生次数,  从正常切换为异常的计数,TestFailed从0->1的计数
    INT8U   CntAging;                                       // 正老化计数,计数点火周期,自正常(NotTestFailed)以来,点火周期的计数。即如果Confirmed && 当前周期NotTestFailed,则每个点火周期加1;如果TestFailed则清零(故障仅为历史故障时的点火周期,决定了何时清除DTC)
    INT8U   CntAged;                                        // 已老去计数,理解为自动清除DTC的次数
} DtcExtendedStruct;
typedef union {
    INT8U   Buf[DTC_BUF_LEN];
    struct {                                                /* 总计36Byte,以下编译后实际占用空间需实测 DKLai20230506 */
        INT8U               CodeIndx;                       // 保存, 1Byte,编译后空0Byte,DTC代码序号
        DtcStatusUnion      Status;                         // 保存, 1Byte,编译后空0Byte,DTC状态码
        DtcConfigUnion      Config;                         // 保存, 1Byte,编译后空1Byte,DTC配置码
        DtcSnapshotStruct   Snapshot;                       // 保存,24Byte,编译后空0Byte,快照数据
        DtcExtendedStruct   Extended;                       // 保存, 3Byte,编译后空1Byte,扩展数据
        INT16U              CntFaultDect;                   // 保存, 2Byte,编译后空0Byte,计数检测次数,对未确认DTC检测次数(决定了何时Pass或Fail)
        INT8U               End;                            // 保存, 1Byte,编译后空0Byte,结束,主要用于调节占用空间,必须使Crc处于最后1Byte的位置,否则影响计算Crc时长度(DTC_EEP_LEN_ONE - 1)的判断
        INT8U               Crc;                            // 保存, 1Byte,Crc
    } Bytes;
} DtcBufUnion;
/*********************************************************************************************************
**  结构体: DTC检测过程的控制信息
*********************************************************************************************************/
typedef union {
    INT8U   Byte[4];
    struct {
        INTCPU  PowerCommLive                   :1;         // 通讯电压处于Normal的即时状态
        INTCPU  PowerCommNormal                 :1;         // 通讯电压处于Normal的稳定状态
        INTCPU  PowerWorkLive                   :1;         // 工作电压处于Normal的即时状态
        INTCPU  PowerWorkNormal                 :1;         // 工作电压处于Normal的稳定状态
        INTCPU  PowerWorkNormalNs               :1;         // 工作电压处于Normal的稳定状态持续Ns
        INTCPU  PowerDiagLive                   :1;         // 诊断电压处于Normal的即时状态
        INTCPU  PowerDiagNormal                 :1;         // 诊断电压处于Normal的稳定状态
        INTCPU  PowerVoltLive                   :1;         // 故障电压处于Normal的即时状态
        INTCPU  PowerVoltNormal                 :1;         // 故障电压处于Normal的稳定状态
        INTCPU  BusNormalNs                     :1;         // 总线BCAN处于Normal的稳定状态持续Ns
        INTCPU  B2sNormalNs                     :1;         // 总线LPCAN处于Normal的稳定状态持续Ns
        INTCPU  OffNs                           :1;         // 其它状态切换到OFF后持续Ns
        INTCPU  AccNs                           :1;         // 其它状态切换到ACC后持续Ns
        INTCPU  IgnNs                           :1;         // 其它状态切换到IGN后持续Ns
        INTCPU  OffIgn                          :1;         // 整车切换到OFF时置0,整车切换到IGN时置1,其它时保持上一状态不变
        INTCPU  DtcEnable                       :1;         // $85的DTC开关
        INTCPU  DtcRuning                       :1;         // 运行状态
        INTCPU  IgnLostwhenIgn                  :1;         // IGN时IGN信号丢失
        INTCPU  EepWritting                     :1;         // 暂未使用
    } Bits;
} DtcFlagCtrlUnion;
/*
 * 枚举
 */
typedef enum {
    DTC_DEAL_XXXX_DEFAULT               = 0,                            /* 默认                         */
    DTC_DEAL_XXXX_1,                                                    /*                              */
} DTC_DEAL_XXXX_ENUM;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    INT16U                  PowerAd1Value;                              /* 当前系统电压值(0-1023)       */
    INT8U                   PowerPhyValue;                              /* 当前系统电压值(0-254)*0.1    */
    #if DTC_SET_CTRL_EN
    INT8U                   DtcSetCtrl[8];                              /* DTC屏蔽方案 长度=DID_EEP_SIZE_0120 */
    #endif
} DtcStatStruct;
typedef struct {
    INT32U                  PowerComm;                                  /* 通讯电压计时                 */
    INT32U                  PowerWork;                                  /* 工作电压计时                 */
    INT32U                  PowerDiag;                                  /* 诊断电压计时                 */
    INT32U                  PowerVolt;                                  /* 故障电压计时                 */
    INT32U                  BusNormal;                                  /* 总线正常计时                 */
    INT32U                  Off;                                        /* OFF状态计时                  */
    INT32U                  Acc;                                        /* ACC状态计时                  */
    INT32U                  Ign;                                        /* IGN状态计时                  */
} DtcTimeStruct;
typedef struct {
    DtcFlagCtrlUnion        Ctrl;                                       /* DTC相关控制信息              */
} DtcFlagStruct;
typedef struct {
    DTC_DEAL_XXXX_ENUM      XXXX;                                       /* XXXX流程控制                 */
} DtcTaskStruct;
/*------------------------------------------------------------------------------------------------------*/
typedef struct {
    DtcStatStruct           Stat;
    DtcTimeStruct           Time;
    DtcFlagStruct           Flag;
    DtcTaskStruct           Task;
} DtcInfoStruct;

/*********************************************************************************************************
** 全局定量
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
** 全局变量 DKLai20230506
*********************************************************************************************************/
extern  volatile DtcBufUnion        DtcBuf[DTC_NUM_TOTAL];              /* 全部DTC管理数据缓冲区        */
extern  volatile DtcInfoStruct      DtcInfo;                            /* Dtc控制信息                  */

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
** 函数声明
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
