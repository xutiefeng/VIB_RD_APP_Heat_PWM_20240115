/****************************************Copyright (c)****************************************************
**                            Guangzhou ZLGMCU Development Co., LTD
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Rte.h
** Last modified Date:  2023-04-17
** Last Version:        V1.0
** Descriptions:        The rte header file
**
**--------------------------------------------------------------------------------------------------------
** Created by:          DKLai
** Created date:        2023-04-17
** Version:             V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         DKLai
** Modified date:       2023-04-19
** Version:             V
** Descriptions:        1.01
** Rechecked by:
*********************************************************************************************************/
#ifndef __VIB_RTE_H__

#define __VIB_RTE_H__

/****************************************************************************
       DTC API   故障码接口函数
*   故障设置流程：
*   1.若某个故障发生，则调用__RTE_UpdateDTC(),并设置错误状态__DTC_ERR
*   2.若故障恢复，则调用__RTE_UpdateDTC()，并清除故障状态__RTE_DTC_NOR
 ****************************************************************************/
/****************************************************************************
       DTC number
****************************************************************************/
#define __RTE_DTC_INDX_ERR_COMPRESSOR         0           //压缩机故障
#define __RTE_DTC_INDX_ERR_DISPLAY            1           //显示器通信故障
#define __RTE_DTC_INDX_ERR_TEMPERATURE1       2           //温度传感器1故障
#define __RTE_DTC_INDX_ERR_TEMPERATURE2       3           //温度传感器2故障
#define __RTE_DTC_INDX_ERR_OZONE_CTRL         4           //臭氧控制器故障
#define __RTE_DTC_INDX_ERR_HEATING            5           //制热故障
#define __RTE_DTC_INDX_ERR_DOOR               6           //门故障
#define __RTE_DTC_INDX_ERR_LIGHT              7           //冰箱内灯故障

typedef enum {
    __RTE_DTC_NOR                             = 0,        /* 正常                         */
    __DTC_ERR,                                            /* 故障                         */
} __RTE_DTC_NOR_ERR_ENUM;


/**
* \brief   __RTE_UpdateDTC 
*
* \details 故障信息设置函数
* 
* \param[in] dtcnumber, 故障标识符, 最大值为总故障数减1；
* \param[in] errstate，故障状态，0--正常，1--故障
*
* \retval    0--设置成功， 1--设置失败
*/
uint8_t __RTE_UpdateDTC(uint8_t dtcnumber, __RTE_DTC_NOR_ERR_ENUM errstate);


/****************************************************************************
   APP message API 冰箱应用报文发送与接收
*  应用报文处理过程：
*  1.冰箱周期性查询__RTE_RcvTELMsgSt()与__RTE_RcvCDCMsgSt()
*  2.若检测到有收到报文标志，通过__RTE_ClrRcvTELMsgSt()与__RTE_ClrRcvCDCMsgSt()，
*    清除相应报文接收标志 
*  3.清除相应标志后，再执行接收到的命令
*  4.命令执行完成后，调用__RTE_SendAppMsg(),发送命令反馈信息
*  5.反馈信息必须只发一次，不能反复调用
 ****************************************************************************/
/**
* \brief   __RTE_SendAppMsg 
*
* \details 冰箱反馈报文发送函数
* 
* \param[in] *msg, 待发送的报文缓冲区首地址；
*
* \retval    0--发送成功， 1--发送失败
*
* \note 缓冲区长度必须为8字节，与单帧CAN报文对应
*/
uint8_t __RTE_SendAppMsg(uint8_t *msg);


/**
* \brief   __RTE_RcvTELMsgSt 
*
* \details 接收报文TEL状态
* 
* \param[in] -
*
* \retval    0--没有收到报文， 1--收到TEL报文
*
* \note - DKLai20230425 
*/
uint8_t __RTE_RcvTELMsgSt(uint8_t *telmsg);


/**
* \brief   __RTE_ClrRcvTELMsgSt 
*
* \details 清除接收报文TEL状态
* 
* \param[in] -
*
* \retval    0--清除状态成功 1--清除TEL报文接收状态失败
*
* \note -
*/
uint8_t __RTE_ClrRcvTELMsgSt(void);


/**
* \brief   __RTE_RcvCDCMsgSt 
*
* \details CDC报文接收状态
* 
* \param[in] -
*
* \retval    0--没有收到报文， 1--收到CDC报文
*
* \note -  DKLai20230425 
*/
uint8_t __RTE_RcvCDCMsgSt(uint8_t *cdcmsg);


/**
* \brief   __RTE_ClrRcvCDCMsgSt 
*
* \details 清除CDC报文收到状态
* 
* \param[in] -
*
* \retval    0--清除状态成功 1--清除CDC报文收到状态失败
*
* \note -
*/
uint8_t __RTE_ClrRcvCDCMsgSt(void);


/****************************************************************************
*   2F service API 强制输出交互函数
*   强制输出模式处理流程：
*   1.查询函数__RTE_2FModeOnSt(),确认是否处于强制输出模式
*   2.若返回1，则处于强制输出模式，不需要进行任何操作
*   3.若返回2，先调用函数__RTE_ClrRcv2FMsgSt()清除2F收到新命令标志，
*     然后再根据输出参数，进行相应操作(参数定义参考诊断参数列表)
*   4.若返回0，则已经退出强制输出模式，不需要任何操作
*****************************************************************************/
/**
* \brief   __RTE_2FModeOnSt 
*
* \details 强制输出2F模式开启状态
* 
* \param[in] rcvbuf,接收到报文缓冲区首地址
* \param[in] len，接收到的报文长度存放地址
*
* \retval    0--退出2F模式， 1--处于2F模式中，2--处于2F模式中，并有新命令输入
*
* \note 2F强制输出命令：03--强制输出控制，接收到数据为2字节，第1字节为03，
*       第2字节为控制命令字节，参考诊断参数列表信息
* \note 2F强制输出命令：00--强制输出控制，接收到数据为1字节，第1字节为00
*/
uint8_t __RTE_2FModeOnSt(uint8_t *rcvbuf, uint8_t *len);


/**
* \brief   __RTE_ClrRcv2FMsgSt 
*
* \details 清除2F报文收到状态
* 
* \param[in] -
*
* \retval    0--清除状态成功 1--清除CDC报文收到状态失败
*
* \note -
*/
uint8_t __RTE_ClrRcv2FMsgSt(void);

/****************************************************************************
*   DID service API DID相关接口函数
*   DID中2E写入服务流程：
*   1.冰箱应用通过周期查询__RTE_ReadWriteDIDSt()函数，判断是否有数据写入标志
*   2.若有写入标志，，并通过调用__RTE_ClrWriteDIDSt()函数，清除写入数据标志
*   3.清除标志后，再进行相应的冰箱操作
*   4.每次操作冰箱都要清除标志，以防无限操作的异常
*   DID中22读冰箱状态数据：
*   1.通过函数__RTE_ReadVIBData()读取冰箱状态数据，冰箱准备缓冲区，缓冲区长度必须为
*     8字节，与诊断参数列表一致，由诊断服务去读取即可
 ****************************************************************************/
 /****************************************************************************
       DID number 冰箱应用中使用的DID标识符
****************************************************************************/
#define __RTE_DID_0100_NUMBER                 0           //设置工作模式
#define __RTE_DID_0101_NUMBER                 1           //设置温度
#define __RTE_DID_0102_NUMBER                 2           //开机或关机
#define __RTE_DID_0103_NUMBER                 3           //童锁命令
#define __RTE_DID_0104_NUMBER                 4           //开门命令

/**
* \brief   __RTE_ReadWriteDIDSt 
*
* \details 2E服务写入状态
* 
* \param[in] didnumber,写入的DID标识符缓冲区地址
* \param[in] didbuf,写入的DID缓冲区首地址
* \param[in] len,写入DID的字节长度地址
*
* \retval    0--无2E数据写入 1--有2E数据写入
*
* \note 若有2E数据写入，刚可读出写入数据，并进行相应操作
*/
uint8_t __RTE_ReadWriteDIDSt(uint8_t *didnumber, uint8_t *didbuf, uint8_t *len);


/**
* \brief   __RTE_ClrWriteDIDSt 
*
* \details 清除2E服务写入状态
* 
* \param[in] -
*
* \retval    0--清除成功 1--清除失败
*
* \note -
*/
uint8_t __RTE_ClrWriteDIDSt(void);

/**
* \brief   __RTE_SetDidVIBData 
*
* \details DID0x1002读取冰箱状态相关信息
* 
* \param[in] databuf，用于存放读到的冰箱数据缓冲区首地址
*
* \retval    0--成功 1--失败
*
* \note   数据长度必须为8Bytes DKLai20230425
*/
uint8_t __RTE_SetDidVIBData(uint8_t *databuf);


/****************************************************************************
   EEPROM API EEPROM接口函数
   EEPROM中分配了256字节区域给到冰箱应用使用，读写接口函数都在这个区域内操作
 ****************************************************************************/
/**
* \brief   __RTE_AppEepromWrite 
*
* \details 写EEPROM函数
* 
* \param[in] address,相对冰箱应用使用的区域的偏移量
* \param[in] wbuf,写入数据缓冲区首地址
* \param[in] len,写入数据长度
*
* \retval    0--写入成功 1--写入失败
*
* \note 1.偏移量与字节长度的和（address + len<256）必须小于256
* \note 2.len最大值为256
*/
uint8_t __RTE_AppEepromWrite(uint32_t address, uint8_t *wbuf, uint8_t len);


/**
* \brief   __RTE_AppEepromRead 
*
* \details 读EEPROM函数
*
* \param[in] address,相对冰箱应用使用的区域的偏移量 
* \param[in] oufbuf，读出数据存放的缓冲区首地址
* \param[in] len，读出数据的长度
*
* \retval    0--读取成功 1--读取失败
*
* \note 1.偏移量与字节长度的和（address + len<256）必须小于256
* \note 2.len最大值为256  DKLai20230425 
*/
uint8_t __RTE_AppEepromRead(uint32_t address, uint8_t *outbuf, uint8_t len);


/****************************************************************************
*     电源电压相关
*     冰箱工作模式：
*     1.冰箱应用检测函数__RTE_AppCurPWMode()
*     2.若返回为0，则冰箱正常工作
*     3.若返回为1，则系统处于电源异常状态，冰箱不工作
*     系统电源检测：
*     1.冰箱应用调用函数__RTE_AppPWADCValue(),向诊断模块传递电压信息，用于判断
*       当前的电源模式
 ****************************************************************************/
/**
* \brief   __RTE_AppCurWorkMode 
*
* \details App当前电源模式
* 
* \param[in] -
*
* \retval    0--正常工作范围（9V~16V） 1--异常工作范围（<9V 或者 >16V）
*
* \note -
*/
uint8_t __RTE_AppCurPWMode(void);


/**
* \brief   __RTE_AppPWADCValue 
*
* \details App电压值传递至诊断模块
* 
* \param[in] -
*
* \retval    0--传递成功 1--传递失败
*
* \note -  
*/
uint8_t __RTE_AppPWADCValue(void);

/**
* \brief   __RTE_AppFillPriodicMsg 
*
* \details App 周期报文内容填充函数
* 
* \param[in] -
*
* \retval    0--填充成功 1--填充失败
*
* \note -    在2ms周期任务中调用即可 DKLai20230705
*/
uint8_t __RTE_AppFillPriodicMsg(uint8_t *sendbuffer);

/* APP 接收到的周期报文ID. DKLai20230814 */
#define __RTE_TIME_MESSAGE_ID      0x35A
#define __RTE_KEY_STATE_MESSAGE_ID 0x318
#define __RTE_MILEAGE_MESSAGE_ID   0x31E
#define __RTE_VCU_VIB_PWR_STATE_ID 0x3F2   /* DKLai20230907 */

/**
* \brief   __RTE_AppRxPriodicMsg 
*
* \details App 获取接收周期报文内容函数
* 
* \param[in]  - msgid, 根据周期报文ID读取相应报文内容
* \param[out] - rxbuffer, 存放读取的报文内容的缓冲区
*
* \retval    0--读取失败（报文错误或报文丢失） 1--读取成功
*
* \note -    由冰箱应用决定何时读取 DKLai20230814
*/
uint8_t __RTE_AppRxPriodicMsg(uint16_t msgid, uint8_t *rxbuffer);

/**
* \brief   __RTE_5sAppMsgTriggerByLocalEvent_Start 
*
* \details    Start to send 5 seconds app message, when key state is off, 
*             if local screen set event happen.
* \param[in]  - 
* \param[out] - 
*
* \retval    
*
* \note   DKLai20231026
*/
void __RTE_5sAppMsgTriggerByLocalEvent_Start(void);

#endif
