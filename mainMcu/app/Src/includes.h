#ifndef __INCLUDES_H__
#define __INCLUDES_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#include "gd32f30x.h"
#include "cmsis_os.h"


/**
 * V1:��һ�η���
 * V2:�����ϱ��пո�   Զ�̿���ָ����Ӧ����źͽ��յ���Ų�һ��
 * V3:�޸�bug��WiFi��������ʧ����������
 * V4:�̼������жϰ汾�ţ��汾��һ�²�����    ����λ��ͨ�Ŵ��ڲ����ʸĳ�19200���������豸����һ��   ���ӹ��ܣ�ʹ����λ�������̼�
 * V5: wifi���ع̼������Ż�����ʽ�汾����
 * V6���޸�bug������ˢ����־����   ��ɲ������
 * V7: FM1752�����������ӵ͹���  �����������
 * V8:433�����Ż�  �޸������ˢ����֮���Э��  �Ż�4G����,����ר��
 * V9�����������������״̬���,�޸�ע�������ø�ʽ
 * V10��
 * V11��
 **/


//�������ͬ���汾
#define VERSON_SER						12

//�����汾
#define FW_VERSION                      0
#define FW_VERSION_SUB1                 ((VERSON_SER/10)%10)
#define FW_VERSION_SUB2                 (VERSON_SER%10)

#define 	SPECIAL_NET_CARD			0   //0-����  1-ר��
#define     ID2                         0	//0-�Ǽ���  1-����
#define     ENVI_TYPE                   1 	//0-��ʽ 1-����  2-Ԥ����  3-����

#if SPECIAL_NET_CARD == 0
	#if ENVI_TYPE == 0						//��ʽ����
		#define NET_SERVER_IP                   "access.sharecharger.com"
		#define NET_SERVER_PORT                 10010
		#define REGISTER_CODE                   "016987547845"
	#elif ENVI_TYPE == 1 					//���� 
		#define NET_SERVER_IP                   "test.access.chargerlink.com"
		#define NET_SERVER_PORT                 10010
		#define REGISTER_CODE                   "016987547845"
	#elif ENVI_TYPE == 2					//Ԥ����
		#define NET_SERVER_IP                   "47.97.236.187"
		#define NET_SERVER_PORT                 10010
		#define REGISTER_CODE                   "016987547845"
	#elif ENVI_TYPE == 3					//����
		#define NET_SERVER_IP                   "47.97.238.64"
		#define NET_SERVER_PORT                 10010
		#define REGISTER_CODE                   "016987547845"
	#endif
#elif SPECIAL_NET_CARD == 1
	#if ENVI_TYPE == 0						//��ʽ����
		#define NET_SERVER_IP                   "www.access.com"    //��ʽ����
		#define NET_SERVER_PORT                 10010
		#define REGISTER_CODE                   "016987547845"
	#elif ENVI_TYPE == 1 					//����
		#define NET_SERVER_IP                   "test.access.com"
		#define NET_SERVER_PORT                 10010
		#define REGISTER_CODE                   "016987547845"
	#elif ENVI_TYPE == 2					//Ԥ����
		#define NET_SERVER_IP                   "172.16.0.245"
		#define NET_SERVER_PORT                 10010
		#define REGISTER_CODE                   "016987547845"
	#elif ENVI_TYPE == 3					//����
		#define NET_SERVER_IP                   "172.16.0.228"
		#define NET_SERVER_PORT                 10010
		#define REGISTER_CODE                   "016987547845"
	#endif
#endif

#define DEVICE_TYPE						14	//�豸���� -- U8
#define STATION_MACHINE_TYPE            "U8"


#define FLASH_SIZE                      0x40000     //�豸flash��С256K
#define FLASH_PAGE_SIZE					2048
//0x08000000
#define BOOT_SIZE	                	((uint32_t)0x3000)                  //12K
#define AppFlashAddr	                (FLASH_BASE + BOOT_SIZE)		    //App������ڵ�ַ (100k) 
#define AppUpBkpAddr	                (AppFlashAddr + (uint32_t)0x19000)	//app�������ݴ洢����ַ(132k ����+����) 801C000
#define SystemInfoAddr                  (AppUpBkpAddr + (uint32_t)0x21000)  //ϵͳ������Ϣ(2K)  
#define SysUpInfoAddr	                (SystemInfoAddr + (uint32_t)0x800)  //��������ͷ��Ϣ(2K)
#define OtherInfoAddr                  	(SysUpInfoAddr + (uint32_t)0x800)   //����(8K)

#define APP_FW_SIZE                     (AppUpBkpAddr - AppFlashAddr)


#define CL_OK                           0
#define CL_FAIL                         (-1)
#define CL_TRUE                         1
#define CL_FALSE                        0


#define RF_DEV_MAX						20 //�̸��豸��������

#define TX_FAIL_MAX_CNT	                3

#define osGetTimes                      osKernelSysTick
#define GetRtcCount 	                GetTimeStamp /*(xTaskGetTickCount()*portTICK_PERIOD_MS/1000)*/
#define UNUSED(X) (void)X


extern char* GetCurrentTime(void);
#define CL_LOG(fmt,args...) do {    \
    printf("%s|[U8]:%s (%d)" fmt, GetCurrentTime(), __func__, __LINE__, ##args); \
}while(0)

#define PRINT_LOG(fmt,args...) do \
{    \
    printf("[%s]"fmt,GetCurrentTime(), ##args); \
}while(0)

#endif



