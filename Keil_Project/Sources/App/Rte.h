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
       DTC API   ������ӿں���
*   �����������̣�
*   1.��ĳ�����Ϸ����������__RTE_UpdateDTC(),�����ô���״̬__DTC_ERR
*   2.�����ϻָ��������__RTE_UpdateDTC()�����������״̬__RTE_DTC_NOR
 ****************************************************************************/
/****************************************************************************
       DTC number
****************************************************************************/
#define __RTE_DTC_INDX_ERR_COMPRESSOR         0           //ѹ��������
#define __RTE_DTC_INDX_ERR_DISPLAY            1           //��ʾ��ͨ�Ź���
#define __RTE_DTC_INDX_ERR_TEMPERATURE1       2           //�¶ȴ�����1����
#define __RTE_DTC_INDX_ERR_TEMPERATURE2       3           //�¶ȴ�����2����
#define __RTE_DTC_INDX_ERR_OZONE_CTRL         4           //��������������
#define __RTE_DTC_INDX_ERR_HEATING            5           //���ȹ���
#define __RTE_DTC_INDX_ERR_DOOR               6           //�Ź���
#define __RTE_DTC_INDX_ERR_LIGHT              7           //�����ڵƹ���

typedef enum {
    __RTE_DTC_NOR                             = 0,        /* ����                         */
    __DTC_ERR,                                            /* ����                         */
} __RTE_DTC_NOR_ERR_ENUM;


/**
* \brief   __RTE_UpdateDTC 
*
* \details ������Ϣ���ú���
* 
* \param[in] dtcnumber, ���ϱ�ʶ��, ���ֵΪ�ܹ�������1��
* \param[in] errstate������״̬��0--������1--����
*
* \retval    0--���óɹ��� 1--����ʧ��
*/
uint8_t __RTE_UpdateDTC(uint8_t dtcnumber, __RTE_DTC_NOR_ERR_ENUM errstate);


/****************************************************************************
   APP message API ����Ӧ�ñ��ķ��������
*  Ӧ�ñ��Ĵ�����̣�
*  1.���������Բ�ѯ__RTE_RcvTELMsgSt()��__RTE_RcvCDCMsgSt()
*  2.����⵽���յ����ı�־��ͨ��__RTE_ClrRcvTELMsgSt()��__RTE_ClrRcvCDCMsgSt()��
*    �����Ӧ���Ľ��ձ�־ 
*  3.�����Ӧ��־����ִ�н��յ�������
*  4.����ִ����ɺ󣬵���__RTE_SendAppMsg(),�����������Ϣ
*  5.������Ϣ����ֻ��һ�Σ����ܷ�������
 ****************************************************************************/
/**
* \brief   __RTE_SendAppMsg 
*
* \details ���䷴�����ķ��ͺ���
* 
* \param[in] *msg, �����͵ı��Ļ������׵�ַ��
*
* \retval    0--���ͳɹ��� 1--����ʧ��
*
* \note ���������ȱ���Ϊ8�ֽڣ��뵥֡CAN���Ķ�Ӧ
*/
uint8_t __RTE_SendAppMsg(uint8_t *msg);


/**
* \brief   __RTE_RcvTELMsgSt 
*
* \details ���ձ���TEL״̬
* 
* \param[in] -
*
* \retval    0--û���յ����ģ� 1--�յ�TEL����
*
* \note - DKLai20230425 
*/
uint8_t __RTE_RcvTELMsgSt(uint8_t *telmsg);


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
uint8_t __RTE_ClrRcvTELMsgSt(void);


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
uint8_t __RTE_RcvCDCMsgSt(uint8_t *cdcmsg);


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
uint8_t __RTE_ClrRcvCDCMsgSt(void);


/****************************************************************************
*   2F service API ǿ�������������
*   ǿ�����ģʽ�������̣�
*   1.��ѯ����__RTE_2FModeOnSt(),ȷ���Ƿ���ǿ�����ģʽ
*   2.������1������ǿ�����ģʽ������Ҫ�����κβ���
*   3.������2���ȵ��ú���__RTE_ClrRcv2FMsgSt()���2F�յ��������־��
*     Ȼ���ٸ������������������Ӧ����(��������ο���ϲ����б�)
*   4.������0�����Ѿ��˳�ǿ�����ģʽ������Ҫ�κβ���
*****************************************************************************/
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
uint8_t __RTE_2FModeOnSt(uint8_t *rcvbuf, uint8_t *len);


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
uint8_t __RTE_ClrRcv2FMsgSt(void);

/****************************************************************************
*   DID service API DID��ؽӿں���
*   DID��2Eд��������̣�
*   1.����Ӧ��ͨ�����ڲ�ѯ__RTE_ReadWriteDIDSt()�������ж��Ƿ�������д���־
*   2.����д���־������ͨ������__RTE_ClrWriteDIDSt()���������д�����ݱ�־
*   3.�����־���ٽ�����Ӧ�ı������
*   4.ÿ�β������䶼Ҫ�����־���Է����޲������쳣
*   DID��22������״̬���ݣ�
*   1.ͨ������__RTE_ReadVIBData()��ȡ����״̬���ݣ�����׼�������������������ȱ���Ϊ
*     8�ֽڣ�����ϲ����б�һ�£�����Ϸ���ȥ��ȡ����
 ****************************************************************************/
 /****************************************************************************
       DID number ����Ӧ����ʹ�õ�DID��ʶ��
****************************************************************************/
#define __RTE_DID_0100_NUMBER                 0           //���ù���ģʽ
#define __RTE_DID_0101_NUMBER                 1           //�����¶�
#define __RTE_DID_0102_NUMBER                 2           //������ػ�
#define __RTE_DID_0103_NUMBER                 3           //ͯ������
#define __RTE_DID_0104_NUMBER                 4           //��������

/**
* \brief   __RTE_ReadWriteDIDSt 
*
* \details 2E����д��״̬
* 
* \param[in] didnumber,д���DID��ʶ����������ַ
* \param[in] didbuf,д���DID�������׵�ַ
* \param[in] len,д��DID���ֽڳ��ȵ�ַ
*
* \retval    0--��2E����д�� 1--��2E����д��
*
* \note ����2E����д�룬�տɶ���д�����ݣ���������Ӧ����
*/
uint8_t __RTE_ReadWriteDIDSt(uint8_t *didnumber, uint8_t *didbuf, uint8_t *len);


/**
* \brief   __RTE_ClrWriteDIDSt 
*
* \details ���2E����д��״̬
* 
* \param[in] -
*
* \retval    0--����ɹ� 1--���ʧ��
*
* \note -
*/
uint8_t __RTE_ClrWriteDIDSt(void);

/**
* \brief   __RTE_SetDidVIBData 
*
* \details DID0x1002��ȡ����״̬�����Ϣ
* 
* \param[in] databuf�����ڴ�Ŷ����ı������ݻ������׵�ַ
*
* \retval    0--�ɹ� 1--ʧ��
*
* \note   ���ݳ��ȱ���Ϊ8Bytes DKLai20230425
*/
uint8_t __RTE_SetDidVIBData(uint8_t *databuf);


/****************************************************************************
   EEPROM API EEPROM�ӿں���
   EEPROM�з�����256�ֽ������������Ӧ��ʹ�ã���д�ӿں���������������ڲ���
 ****************************************************************************/
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
uint8_t __RTE_AppEepromWrite(uint32_t address, uint8_t *wbuf, uint8_t len);


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
* \note 2.len���ֵΪ256  DKLai20230425 
*/
uint8_t __RTE_AppEepromRead(uint32_t address, uint8_t *outbuf, uint8_t len);


/****************************************************************************
*     ��Դ��ѹ���
*     ���乤��ģʽ��
*     1.����Ӧ�ü�⺯��__RTE_AppCurPWMode()
*     2.������Ϊ0���������������
*     3.������Ϊ1����ϵͳ���ڵ�Դ�쳣״̬�����䲻����
*     ϵͳ��Դ��⣺
*     1.����Ӧ�õ��ú���__RTE_AppPWADCValue(),�����ģ�鴫�ݵ�ѹ��Ϣ�������ж�
*       ��ǰ�ĵ�Դģʽ
 ****************************************************************************/
/**
* \brief   __RTE_AppCurWorkMode 
*
* \details App��ǰ��Դģʽ
* 
* \param[in] -
*
* \retval    0--����������Χ��9V~16V�� 1--�쳣������Χ��<9V ���� >16V��
*
* \note -
*/
uint8_t __RTE_AppCurPWMode(void);


/**
* \brief   __RTE_AppPWADCValue 
*
* \details App��ѹֵ���������ģ��
* 
* \param[in] -
*
* \retval    0--���ݳɹ� 1--����ʧ��
*
* \note -  
*/
uint8_t __RTE_AppPWADCValue(void);

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
uint8_t __RTE_AppFillPriodicMsg(uint8_t *sendbuffer);

/* APP ���յ������ڱ���ID. DKLai20230814 */
#define __RTE_TIME_MESSAGE_ID      0x35A
#define __RTE_KEY_STATE_MESSAGE_ID 0x318
#define __RTE_MILEAGE_MESSAGE_ID   0x31E
#define __RTE_VCU_VIB_PWR_STATE_ID 0x3F2   /* DKLai20230907 */

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
