#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "includes.h"

#define ICCID_LEN                       20
#define CHARGER_SN_LEN			        8

enum{
	NETTYPE_WIFI = 0,
	NETTYPE_GPRS = 1,
	NETTYPE_485,
	NETTYPE_24G,
};


enum{
	OTA_NONE  = 0,
	OTA_NET   = 1,
	OTA_BLUE  = 2,
	OTA_UART  = 3,
};

typedef struct{

	uint16_t bandSize;					//�󶨸���
	struct
	{
		uint8_t num;			//���
		uint32_t address;		//�Ѿ��󶨵��豸��ַ
	}Unit[RF_DEV_MAX];

}RFDev_t;

//sizeof(SYSTEM_INFO_T) = 256
typedef struct
{
	uint32_t magic_number;						//
    uint8_t stationId[8];                     	// �豸��bcd, SN=10, 10 byte  0001123456789
	uint8_t idCode[8];							// ע����
	char WifiName[32];							// ssid
	char WifiPasswd[32];						// passwd
	uint8_t netStep;							//�������ȼ� 0-wifi  1-4G
	uint8_t pcbSn[8];							//PCB���
	uint8_t reserved0[7];
	RFDev_t RfDev;								// 433�豸 ���20���豸 ռ��102���ֽ�
	uint8_t resevred1[54];						// Ԥ��
}SYSTEM_INFO_T;


typedef struct
{
	uint8_t isRegister;						//0-δע��  1-��ע��
	uint8_t isLogin;						//0-δ��¼	1-�ѵ�½
	uint8_t card_state;                     //������״̬   0: ��ʾ��ʼ������  1 :��ʾ��ʼ��ok 
	uint8_t WG215InitOK;					//�Ƿ��⵽WG215ģ�� 0-δ��⵽ 1-���OK
	uint8_t BlueInitOk;						//�����Ƿ��ʼ�� 0��δ��ʼ��	1���Ѿ���ʼ��
	uint8_t CBInitOK;						//ˢ�����Ƿ��ʼ���ɹ� 0δ��ʼ�� 1-��ʼ���ɹ�
	uint8_t netType;						//������ʽ	1-����2G/4G 2-485  3-2.4G 4-wifi
	uint8_t modeType;						//ģ���ͺ�
	uint8_t gSimStatus;						//sim��״̬
	uint8_t simSignal;						//sim���ź�ֵ
	uint8_t iccid[ICCID_LEN+1];				//sim����iccid
	uint8_t doorState;						//�Ž�״̬ 0--�ر�  1--��
	uint8_t doorStatePre;					
	uint8_t is_socket_0_ok;					//socket�Ƿ������� 0-δ���� 1-������
	char BlueName[16];						//��������
	uint8_t CBVerson;						//ˢ����汾
	uint32_t lastRecvCBTime;				//�ϴν��յ�ˢ���������ʱ��	
	uint8_t isBlueConnect;					//�Ƿ�����������
	uint8_t isBlueLogin;					//�����Ƿ��½
	char phonesSn[20];						//���������ֻ�����
	uint32_t blueLastOnlineTime;			//��������ʱ��
	uint8_t upgradeFlag;					//0-δ����  ��0�������� 1-��������   2--�������� 3--��������
	uint32_t upgradeTime;					//����ʱ��
	uint8_t isTest;							//�Ƿ�������ģʽ0-δ����  1-�������ģʽ
	void (*readCard_Callback)(uint8_t,uint8_t *);
	uint8_t netStep;						//�������ȼ� 0-wifi  1-4G
}GLOBAL_INFO_T;


void BswSrv_LoadSystemInfo(void);
void BswSrv_SystemResetRecord(void);
int BswSrv_GetHWId(char HWId[]);
int BswSrv_GetCpuTemp(void);
void BswSrv_SystemReboot(void);
void BswSrv_RF433AddrToChar(uint32_t addr,uint8_t ch[]);
uint32_t BswSrv_CharToRF433Addr(uint8_t ch[]);

uint16_t BswSrv_Tool_CheckSum(uint8_t *data,uint16_t len);
int BswSrv_Tool_isArraryEmpty(uint8_t *array,int len);
int BswSrv_Tool_StringToBCD(unsigned char *BCD, const char *str) ;
char *BswSrv_Tool_BCDToString(char *dest, unsigned char *BCD, int bytes) ;

extern SYSTEM_INFO_T	SystemInfo;
extern GLOBAL_INFO_T	GlobalInfo;


#endif


