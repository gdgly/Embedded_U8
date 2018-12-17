#ifndef __BSWSRV_RF433_H__
#define __BSWSRV_RF433_H__


#include <stdint.h>
#include <time.h>

/**
 *�̸��豸�������ݽṹ
 */
typedef struct 
{
	uint8_t num;		//���
	uint32_t address;	//�豸��ַ 
	uint8_t flag;		//������־ 0--�ޱ���   1-�б���
	uint32_t occurTime;	//��������ʱ��
	uint32_t lastUpTime;//�ϴα���ʱ��
}RF_Unit_Typedef;



/**
 *
 */
typedef struct
{	
	RF_Unit_Typedef device[20]; 	//���󶨸���
	uint16_t bandSize;						//���豸����
}RFDev_Reg_t;


int BswSrv_RF433_BindDevice(uint8_t num,uint32_t address);
int BswSrv_RF433_GetWaringDevice(RF_Unit_Typedef *rf433Dev);
void BswSrv_RF433_Loop_EventTimeout(void);
void BswSrv_RF433_ClearFlag(uint32_t address);

void BswSrv_RF433_LoadDevInfo(void);


#endif
