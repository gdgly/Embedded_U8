/*
 * @Author: zhoumin 
 * @Date: 2018-10-12 14:15:14 
 * @Last Modified by: zhoumin
 * @Last Modified time: 2018-11-23 12:03:45
 */
#include "BswSrv_System.h"
#include "BswSrv_RF433.h"
#include "BswDrv_IC_RF433.h"
#include "BswDrv_Rtc.h"
#include "BswSrv_FlashUsr.h"
#include "App_ProductTest.h"


static RFDev_Reg_t RFDev_Reg;


__weak void BswSrv_RF433_EventTimeout(RF_Unit_Typedef *dev)
{
	UNUSED(dev);
}

/**
 *�������ص�����
 *
 */
void RF433_WaringOccurred_CallBack(uint32_t address)
{
	uint16_t bindSize = RFDev_Reg.bandSize;
	
	for(int i = 0; i < bindSize;i++){
		
		if(address == RFDev_Reg.device[i].address)
		{
			RFDev_Reg.device[i].flag = 1;
			RFDev_Reg.device[i].occurTime = osGetTimes();
			break;
		}
	}
	
	if(GlobalInfo.isTest)
	{
		readRF433Addr = address;
		if(TestRF433Addres == address)
		{
			isCheckRF433 = 1;
		}else{
			isCheckRF433 = 2;
		}
	}
}


/**
 *��ȡ�����豸��Ϣ(��Ҫ�������ж�ʱ���ã����ú���ձ�־)
 *
 */
int BswSrv_RF433_GetWaringDevice(RF_Unit_Typedef *rf433Dev)
{
	uint16_t bindSize = RFDev_Reg.bandSize;
	for(int i = 0; i < bindSize;i++){
		
		if(1 == RFDev_Reg.device[i].flag && ((osGetTimes() - RFDev_Reg.device[i].lastUpTime) >= 10*1000))
		{
			RFDev_Reg.device[i].lastUpTime = osGetTimes();
			memcpy((void*)rf433Dev,(void*)&RFDev_Reg.device[i],sizeof(RF_Unit_Typedef));
			return CL_OK;
		}
	}
	
	return CL_FAIL;
}

/**
 * ��ѯ�����¼��Ƿ�ʱ
 */
void BswSrv_RF433_Loop_EventTimeout(void)
{
	uint16_t bindSize = RFDev_Reg.bandSize;
	for(int i = 0; i < bindSize;i++){
		if(1 == RFDev_Reg.device[i].flag)
		{
			if((osGetTimes() - RFDev_Reg.device[i].occurTime) >= 60*1000)
			{
				RFDev_Reg.device[i].flag = 0;
				BswSrv_RF433_EventTimeout(&RFDev_Reg.device[i]);
				continue;
			}
		}
	}
}


/**
 *�����������־
 *
 */
void BswSrv_RF433_ClearFlag(uint32_t address)
{
	uint16_t bindSize = RFDev_Reg.bandSize;
	
	for(int i = 0; i < bindSize;i++){
		
		if(address == RFDev_Reg.device[i].address)
		{
			RFDev_Reg.device[i].flag = 0;
			
			return ;
		}
	}
}


// /**
//  *�豸��
//  *
//  */
// int BswSrv_RF433_BindDevice(uint8_t num,uint32_t address)
// {
// 	uint16_t bindSize = RFDev_Reg.bandSize;
	
// 	if(bindSize >= RF_DEV_MAX)
// 	{
// 		return CL_FAIL;
// 	}
	
// 	for(int i = 0; i < bindSize;i++){
		
// 		if(address == RFDev_Reg.device[i].address)
// 		{
// 			return CL_OK; //�Ѿ��󶨳ɹ�
// 		}
// 	}
	
// 	RFDev_Reg.device[bindSize-1].flag = 0;
// 	RFDev_Reg.device[bindSize-1].num = num;
// 	RFDev_Reg.device[bindSize-1].address = address;
// 	RFDev_Reg.device[bindSize-1].occurTime = 0;
	
// 	RFDev_Reg.bandSize += 1;//�豸��������1
	
// 	//�����豸��Ϣ��flash
// 	SystemInfo.RfDev.Unit[bindSize-1].address = address;
// 	SystemInfo.RfDev.Unit[bindSize-1].num = num;
// 	SystemInfo.RfDev.bandSize++;
// 	FlashWriteSysInfo(&SystemInfo,sizeof(SystemInfo));

// 	return CL_OK;
// }



void BswSrv_RF433_LoadDevInfo(void)
{
	memset(&RFDev_Reg,0,sizeof(RFDev_Reg_t));	
	//�������ļ������̸а���Ϣ
	RFDev_Reg.bandSize = SystemInfo.RfDev.bandSize;

	for(uint16_t i = 0;i<RFDev_Reg.bandSize;i++){

		RFDev_Reg.device[i].address = SystemInfo.RfDev.Unit[i].address;
		RFDev_Reg.device[i].num = SystemInfo.RfDev.Unit[i].num;
		RFDev_Reg.device[i].flag = 0;
		RFDev_Reg.device[i].occurTime = 0;
		RFDev_Reg.device[i].lastUpTime = 0;
	}
	
}
