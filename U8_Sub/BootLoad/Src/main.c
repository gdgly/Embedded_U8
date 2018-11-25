#include "includes.h"
#include "gd32f3x0.h"
#include "systick.h"
#include <stdio.h>
//#include <task.h>
//#include "wifi.h"
#include "rtc.h"
#include "system.h"
#include "usart.h"
#include "flash.h"
#include "flash_usr.h"
#include "usart.h"
#include "spi.h"
#include "NFCard.h"
#include "GPRS_4G.h"
#include "gd32f3x0_libopt.h"
#include "system.h"
#include "sc8042b.h"
#include "fm175xx.h"
#include "NFCard.h"
#include "sim_uart.h"
#include "ComProto.h"
#include "led.h"




typedef  void (*pFunction)(void);

/**
  * @brief  ���Ƴ�����ת��ָ��λ�ÿ�ʼִ�� ��
  * @param  Addr ����ִ�е�ַ��
  * @retval ������ת״̬��
  */
uint8_t JumpToApplication(uint32_t Addr)
{
    pFunction Jump_To_Application;
    __IO uint32_t JumpAddress; 
	/* Test if user code is programmed starting from address "ApplicationAddress" */
    if (((*(__IO uint32_t*)Addr) & 0x2FFE0000 ) == 0x20000000)
	{ 
        /* Jump to user application */
        JumpAddress = *(__IO uint32_t*) (Addr + 4);
        Jump_To_Application = (pFunction) JumpAddress; 
        /* Initialize user application's Stack Pointer */
        __set_MSP(*(__IO uint32_t*) Addr);
		
        Jump_To_Application();
    }
    
    return 1;
}


void BspInit(void)
{
//    StartDelay();
    WatchDogInit();             //���Ź���ʼ��
    FeedWatchDog();
	SystickInit();
	UsartInit();                //���ڳ�ʼ��
//    printf("into bootload!\r\n");
//    SC8042B_Init();

    //������ʾ    
//    PlayVoice(VOIC_DEVICE_REBOOT);           //�豸����
//    DelayMsWithNoneOs(900);
    CL_LOG("\r\n boot BspInit ok\n");
}

int main(void)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);//����ϵͳ�ж����ȼ�����4	
    
    BspInit();
    
	FlashReadByte((uint32_t)UPGRADE_INFO, (void *)&updateInfo, sizeof(updateInfo));
	if(updateInfo.updateFlag == 0xAA55BCDE)
	{
        printf("��⵽������־![%d], [%#x]\n", updateInfo.size, updateInfo.checkSum);
		if(0 != UpdateFromAppBkp(updateInfo.size, updateInfo.checkSum))
		{
			
		}
	}
	
    if(((*(__IO uint32_t*)(AppFlashAddr+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
    {
        printf("��ת��APPӦ�ó���!\n");
        JumpToApplication(AppFlashAddr);//�Զ������ת��������ת��ַΪ0X0000
    }
    else 
    {
        printf("��APPӦ�ó���,�޷�ִ��!\n");   
    }	
    
    while(1)
    {
        printf("û��app����!\n");
    }
}



