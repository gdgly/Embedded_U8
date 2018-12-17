#include "App_Upgrade.h"




void App_Upgrade_Init(UPGRADE_TYPE type,uint32_t package_num)
{
    OTA_Start(type);
    if (type == UPGRADE_UART || type ==UPGRADE_BLUE )
    {
        upgradeInfo.current_package = 1;
        upgradeInfo.package_num = package_num;
    }
}


/**
 *�̼��·�
 * @return -1:ʧ�� 0-�������У��ɹ� 1-�̼��³ɹ� 2-�������У׼ʧ��  3-�����ļ����� 4-�汾һ��
 **/  
int App_Upgrade_Write(uint8_t *data,uint16_t datalen)
{
    uint8_t index = data[0];
	uint8_t *pData = data+1;
	uint16_t len = datalen - 1;
    // CL_LOG("index=%d len=%d \n",index,len);
    if(upgradeInfo.current_package == 1 && len >= 32)
    {
        uint8_t upgradeType;
        upgradeInfo.lastIndex = index;
        FW_HEAD_STR *pFwHead = (void*)pData;
        if(pFwHead->aa == 0xAA && pFwHead->five == 0x55){
            
            FW_INFO_STR *pFwInfo = (void*)(pData+16);
            if (0 == memcmp("U8M", pFwInfo->name, 3)) {//����
				upgradeType = FW_U8;
            }
            else if (0 == memcmp("U8C", pFwInfo->name, 3)) {//ˢ����
                upgradeType = FW_U8_BAK;
            }
            else{
                CL_LOG("fw name=%s, error,exit upgrade.\r\n",pFwInfo->name);
                return 3;
            }
            if(OAT_Init(upgradeType,0,pFwInfo->size,pFwInfo->checkSum,pFwHead->fwVer1) == CL_FAIL)
            {
                CL_LOG("upgrade fail,exit.\n");
				return 4; //
            }

            OAT_FwWrite(upgradeInfo.upgradeFlag,pData+32,len-32);
            upgradeInfo.current_package++;
        }else
        {
            return CL_FAIL;
        }
    }

    if(upgradeInfo.lastIndex == index){
		CL_LOG("repeat transmate pacakge=%d.\n",index);
		return 1;
	}
    upgradeInfo.lastIndex = index;
    OAT_FwWrite(upgradeInfo.upgradeFlag,pData,len);
    if(upgradeInfo.current_package == upgradeInfo.package_num)
    {
        if(OTA_Check(upgradeInfo.upgradeFlag) == CL_FAIL)
        {
            return 2; //������ɣ�У��ʧ��
        }
        else
        {
            return CL_OK;//������ɡ�У��OK
        }
    }
    else
    {
        upgradeInfo.current_package++;
    }
    return 1;
}

void App_Upgrade_Finish(uint8_t result)
{
    OTA_Finish(result,upgradeInfo.upgradeFlag);
}

