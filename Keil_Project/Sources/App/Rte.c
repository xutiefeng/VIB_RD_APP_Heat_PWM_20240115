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
* \details ������Ϣ���ú���
* 
* \param[in] dtcnumber, ���ϱ�ʶ��, ���ֵΪ�ܹ�������1��
* \param[in] errstate������״̬��0--������1--����
*
* \retval    0--���óɹ��� 1--����ʧ��  DKLai20230424
*/
uint8_t __RTE_UpdateDTC(uint8_t dtcnumber, __RTE_DTC_NOR_ERR_ENUM errstate)
{
    return __DiagTask_UpdateDTC(dtcnumber, (uint8_t)errstate);
}

/**
* \brief   __RTE_SendAppMsg 
*
* \details ���䷴�����ķ��ͺ���
* 
* \param[in] *msg, �����͵ı��Ļ������׵�ַ��
*
* \retval    0--���ͳɹ��� 1--����ʧ��
*
* \note ���������ȱ���Ϊ8�ֽڣ��뵥֡CAN���Ķ�Ӧ DKLai20230424
*/
uint8_t __RTE_SendAppMsg(uint8_t *msg)
{
    return __DiagTask_SendAppMsg(msg);
}

/**
* \brief   __RTE_RcvTELMsgSt 
*
* \details ���ձ���TEL״̬
* 
* \param[in] -
*
* \retval    0--û���յ����ģ� 1--�յ�TEL����
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
* \details ������ձ���TEL״̬
* 
* \param[in] -
*
* \retval    0--���״̬�ɹ� 1--���TEL���Ľ���״̬ʧ��
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
* \details CDC���Ľ���״̬
* 
* \param[in] -
*
* \retval    0--û���յ����ģ� 1--�յ�CDC����
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
* \details ���CDC�����յ�״̬
* 
* \param[in] -
*
* \retval    0--���״̬�ɹ� 1--���CDC�����յ�״̬ʧ��
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
* \details ǿ�����2Fģʽ����״̬
* 
* \param[in] rcvbuf,���յ����Ļ������׵�ַ
* \param[in] len�����յ��ı��ĳ��ȴ�ŵ�ַ
*
* \retval    0--�˳�2Fģʽ�� 1--����2Fģʽ�У�2--����2Fģʽ�У���������������
*
* \note 2Fǿ��������03--ǿ��������ƣ����յ�����Ϊ2�ֽڣ���1�ֽ�Ϊ03��
*       ��2�ֽ�Ϊ���������ֽڣ��ο���ϲ����б���Ϣ
* \note 2Fǿ��������00--ǿ��������ƣ����յ�����Ϊ1�ֽڣ���1�ֽ�Ϊ00
*/
uint8_t __RTE_2FModeOnSt(uint8_t *rcvbuf, uint8_t *len)
{
    return __DiagTask_Rcv2FCheck(rcvbuf, len);
}

/**
* \brief   __RTE_ClrRcv2FMsgSt 
*
* \details ���2F�����յ�״̬
* 
* \param[in] -
*
* \retval    0--���״̬�ɹ� 1--���CDC�����յ�״̬ʧ��
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
* \details DID0x1002��ȡ����״̬�����Ϣ
* 
* \param[in] databuf�����ڴ�Ŷ����ı������ݻ������׵�ַ
*
* \retval    0--��ȡ�ɹ� 1--��ȡʧ��
*
* \note   ���ݳ��ȱ���Ϊ8Bytes
*/
uint8_t __RTE_SetDidVIBData(uint8_t *databuf)
{
    __DiagTask_DidVibDataSet(databuf);
	
    return 1;
}

/**
* \brief   __RTE_AppEepromWrite 
*
* \details дEEPROM����
* 
* \param[in] address,��Ա���Ӧ��ʹ�õ������ƫ����
* \param[in] wbuf,д�����ݻ������׵�ַ
* \param[in] len,д�����ݳ���
*
* \retval    0--д��ɹ� 1--д��ʧ��
*
* \note 1.ƫ�������ֽڳ��ȵĺͣ�address + len<256������С��256
* \note 2.len���ֵΪ256
*/
uint8_t __RTE_AppEepromWrite(uint32_t address, uint8_t *wbuf, uint8_t len)
{
    return __DiagTask_EEPWrite(address, wbuf, len);
}

/**
* \brief   __RTE_AppEepromRead 
*
* \details ��EEPROM����
*
* \param[in] address,��Ա���Ӧ��ʹ�õ������ƫ���� 
* \param[in] oufbuf���������ݴ�ŵĻ������׵�ַ
* \param[in] len���������ݵĳ���
*
* \retval    0--��ȡ�ɹ� 1--��ȡʧ��
*
* \note 1.ƫ�������ֽڳ��ȵĺͣ�address + len<256������С��256
* \note 2.len���ֵΪ256
*/
uint8_t __RTE_AppEepromRead(uint32_t address, uint8_t *outbuf, uint8_t len)
{
    return __DiagTask_EEPRead(address, outbuf, len);
}

/**
* \brief   __RTE_AppPWADCValue 
*
* \details App��ѹֵ���������ģ��
* 
* \param[in] -
*
* \retval    0--���ݳɹ� 1--����ʧ��
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
* \details App ���ڱ���������亯��
* 
* \param[in] -
*
* \retval    0--���ɹ� 1--���ʧ��
*
* \note -    ��2ms���������е��ü��� DKLai20230705
*/
uint8_t __RTE_AppFillPriodicMsg(uint8_t *sendbuffer)
{
    __DiagTask_UpdatePriodicMsg(sendbuffer);
}

/**
* \brief   __RTE_AppRxPriodicMsg 
*
* \details App ��ȡ�������ڱ������ݺ���
* 
* \param[in]  - msgid, �������ڱ���ID��ȡ��Ӧ��������
* \param[out] - rxbuffer, ��Ŷ�ȡ�ı������ݵĻ�����
*
* \retval    0--��ȡʧ�ܣ����Ĵ�����Ķ�ʧ�� 1--��ȡ�ɹ�
*
* \note -    �ɱ���Ӧ�þ�����ʱ��ȡ DKLai20230814
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
