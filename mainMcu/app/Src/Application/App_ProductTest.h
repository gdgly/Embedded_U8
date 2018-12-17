#ifndef __APP_CONFIGTOOL_H__
#define __APP_CONFIGTOOL_H__

#include <stdint.h>
#include "BswSrv_ProductTest.h"

#define MAC_LEN                         5
#define MAX_TERMINAL_NUM                8

enum{
	DEBUG_CMD_TEST 	= 0x99,
	DEBUG_CMD_KEY 	= 0x01,
	DEBUG_CMD_CARD1  = 0x02,
	DEBUG_CMD_SIM		= 0x04,
	DEBUG_CMD_TRUMPTE = 0x05,
	DEBUG_CMD_RELAY = 0x06,
	DEBUG_CMD_WRITEPCB = 0x07,	
	DEBUG_CMD_SN  = 0x08,
	DEBUG_CMD_BLUE = 0x09,
	DEBUG_CMD_GETSVER = 0x0A,
	DEBUG_CMD_READPCB = 0x0B,
	DEBUG_CMD_ICode = 0x0C,
	DEBUG_CMD_REBOOT = 0x13,
	DEBUG_CMD_ICode2 = 0X14,
	DEBUG_CMD_SETRTC = 0x15,
	DEBUG_CMD_READRTC = 0x16,
	DEBUG_CMD_FLASHTEST = 0x17,
	DEBUG_CMD_LED = 0x1A,
	DEBUG_CMD_SERVER_COM	= 0x1C,
	DEBUG_CMD_GETSN			= 0x1E,
	DEBUG_CMD_GETICODE		= 0x1F,
	DEBUG_CMD_AGE_TEST		= 0x20,				//�����ϻ�����
	DEBUG_CMD_GET_AGE_RESULT = 0x21,			//��ȡ�ϻ����Խ��
	DEBUG_CMD_WIFI_CONFIG = 0x25,					//wifi���ò���
	DEBUG_CMD_DOOR_TEST   = 0x26,					//��������
	DEBUG_CMD_RF433_TEST	= 0x27,					//�̸в���
	DEBUG_CMD_RS232_TEST	= 0x28,					//232����
	DEBUG_CMD_WIFI_SER		= 0x29,					//wifi��������
	DEBUG_CMD_WIFI_CSQ 		= 0x2A,					//wifi�ź�ֵ
	DEBUG_CMD_CARD2 		= 0x2B,					//U8ˢ������
	DEBUG_CMD_DOOR_STATE	= 0x2C,					//�Ž�״̬���
	DEBUG_CMD_FW_UPGRADE = 0xF1,					//�̼�����
	DEBUG_CMD_FW_DOWNLOAD = 0xF2,					//�̼��·�
};

#pragma pack(1)

typedef struct {
    uint8_t  aa;                                    //0.
    uint8_t  five;                                  //1.
    uint8_t  src[5];                                //2. ׮��   Bcd
    uint8_t  dest[5];                               //3.
    uint16_t len;                                   //4.
    uint8_t  ver;                                   //5.
    uint8_t  sn;                                    //6.
    uint8_t  cmd;                                   //7.
}OUT_NET_HEAD_STR;

typedef struct {
    OUT_NET_HEAD_STR head;
    uint8_t  data[CT_FRAME_LEN];
}OUT_PKT_STR;


typedef struct {
    uint8_t  chargerSn[MAC_LEN];
}CHARGER_STR;


typedef struct {
    uint8_t  cnt;                               //x6��Ŀ
    CHARGER_STR chargerInfo[MAX_TERMINAL_NUM];  //X6���
}TERMINAL_STR;

typedef struct{
	uint32_t time;
}DEBUG_RTC_STR;


typedef struct{
	uint32_t     fw_size;
	uint32_t     package_num;                       
	uint16_t     checkSum;
    uint8_t      fw_version;
}DEBUG_DOWN_FW_STR;


typedef struct {
    uint8_t  index;
    uint16_t successCnt;
    uint16_t failCnt;
}TEST_ITEM_STR;

typedef struct {
    uint32_t testFlag;                          //���Ա�־ 0xaa55abcd TEST_FLAG
    uint8_t  testMode;                          //����ģʽ 1.�ϻ�����
    uint8_t  testingItem;                       //����ִ�еĲ���ģʽ
	uint8_t  itemCnt;							//�Ѿ����Ե���
	uint16_t testCnt;                           //�ܲ��Դ���
    uint8_t  failFlag;                          //�Ƿ���ʧ��
    TEST_ITEM_STR item[3];
}TEST_INFO_STR;

#pragma pack()

int App_ProTest_Flash(void);
void App_ProTest_4GTestFinish(uint8_t result);
void App_ProTest_WIFITestFinish(uint8_t result);
int App_ProTest_SendRF433Rst(uint8_t ret,uint32_t address);
int App_ProTest_SendKeyInfo(uint8_t keyValue);
int App_ProTest_SendCardInfo(uint8_t *cardId,uint8_t flag);
int App_ProTest_SendPkt(OUT_PKT_STR *pFrame, uint16_t len);

void App_ProTest_Init(void);

extern uint8_t isCheckRF433 ;
extern uint32_t TestRF433Addres;
extern uint32_t readRF433Addr;

#endif

