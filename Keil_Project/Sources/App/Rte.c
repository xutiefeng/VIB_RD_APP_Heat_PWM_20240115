/****************************************Copyright (c)****************************************************
**                            Guangzhou ZLGMCU Development Co., LTD
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           Rte.c
** Last modified Date:  2023-04-20
** Last Version:        V1.0
** Descriptions:        The rte header file
**
**--------------------------------------------------------------------------------------------------------
** Created by:          DKLai
** Created date:        2023-04-20
** Version:             V1.00
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         DKLai
** Modified date:       2023-04-20
** Version:             V
** Descriptions:        1.00
** Rechecked by:
*********************************************************************************************************/
#include "includeall.h"

/* DKLai20230506 */
static uint16_t __g_rtc_adctempvalue[3] = {0, AD1_BAT_12_0V, AD1_BAT_MAX}; 

/* DKLai20231008 */
const INT8U     DID_ROM_F189_TBL[DID_ROM_SIZE_F189] __attribute__((at(0x0001F400))) = {ECU_VER_VEHSOFT};
const INT8U     DID_ROM_F193_TBL[DID_ROM_SIZE_F193] __attribute__((at(0x0001F420))) = {ECU_VER_SPLHARD};
const INT8U     DID_ROM_F195_TBL[DID_ROM_SIZE_F195] __attribute__((at(0x0001F430))) = {ECU_VER_SPLSOFT};

/**
* \brief   __RTE_UpdateDTC 
*
* \details 故障信息设置函数
* 
* \param[in] dtcnumber, 故障标识符, 最大值为总故障数减1；
* \param[in] errstate，故障状态，0--正常，1--故障
*
* \retval    0--设置成功， 1--设置失败  DKLai20230424
*/
uint8_t __RTE_UpdateDTC(uint8_t dtcnumber, __RTE_DTC_NOR_ERR_ENUM errstate)
{
    return __DiagTask_UpdateDTC(dtcnumber, (uint8_t)errstate);
}

/**
* \brief   __RTE_SendAppMsg 
*
* \details 冰箱反馈报文发送函数
* 
* \param[in] *msg, 待发送的报文缓冲区首地址；
*
* \retval    0--发送成功， 1--发送失败
*
* \note 缓冲区长度必须为8字节，与单帧CAN报文对应 DKLai20230424
*/
uint8_t __RTE_SendAppMsg(uint8_t *msg)
{
    return __DiagTask_SendAppMsg(msg);
}

/**
* \brief   __RTE_RcvTELMsgSt 
*
* \details 接收报文TEL状态
* 
* \param[in] -
*
* \retval    0--没有收到报文， 1--收到TEL报文
*
* \note -
*/
uint8_t __RTE_RcvTELMsgSt(uint8_t *telmsg)
{	
    return __DiagTask_RcvTELCheck(telmsg);		
}

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
uint8_t __RTE_ClrRcvTELMsgSt(void)
{
    return __DiagTask_ClrRcvTELFlag();
}

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
uint8_t __RTE_RcvCDCMsgSt(uint8_t *cdcmsg)
{	
    return __DiagTask_RcvCDCCheck(cdcmsg);
}

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
uint8_t __RTE_ClrRcvCDCMsgSt(void)
{
    return __DiagTask_ClrRcvCDCFlag();
}

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
uint8_t __RTE_2FModeOnSt(uint8_t *rcvbuf, uint8_t *len)
{
    return __DiagTask_Rcv2FCheck(rcvbuf, len);
}

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
uint8_t __RTE_ClrRcv2FMsgSt(void)
{
    return __DiagTask_Clr2FRcvFlag();
}

/**
* \brief   __RTE_ReadVIBData 
*
* \details DID0x1002读取冰箱状态相关信息
* 
* \param[in] databuf，用于存放读到的冰箱数据缓冲区首地址
*
* \retval    0--读取成功 1--读取失败
*
* \note   数据长度必须为8Bytes
*/
uint8_t __RTE_SetDidVIBData(uint8_t *databuf)
{
    __DiagTask_DidVibDataSet(databuf);
	
    return 1;
}

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
uint8_t __RTE_AppEepromWrite(uint32_t address, uint8_t *wbuf, uint8_t len)
{
    return __DiagTask_EEPWrite(address, wbuf, len);
}

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
* \note 2.len最大值为256
*/
uint8_t __RTE_AppEepromRead(uint32_t address, uint8_t *outbuf, uint8_t len)
{
    return __DiagTask_EEPRead(address, outbuf, len);
}

/**
* \brief   __RTE_AppPWADCValue 
*
* \details App电压值传递至诊断模块
* 
* \param[in] -
*
* \retval    0--传递成功 1--传递失败
*
* \note - DKLai20230506
*/
uint8_t __RTE_AppPWADCValue(void)
{
    __g_rtc_adctempvalue[0] = ADtable[2];
	
    return __DiagTask_SetPowerValue(__g_rtc_adctempvalue);
}

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
uint8_t __RTE_AppFillPriodicMsg(uint8_t *sendbuffer)
{
    __DiagTask_UpdatePriodicMsg(sendbuffer);
}

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
uint8_t __RTE_AppRxPriodicMsg(uint16_t msgid, uint8_t *rxbuffer)
{
    return __DiagTask_RxPeriodMsg(msgid, rxbuffer);
}

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
void __RTE_5sAppMsgTriggerByLocalEvent_Start(void)
{
    __DiagTask_5sAppMsg_Start();
}
