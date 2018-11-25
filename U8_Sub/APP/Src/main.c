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


void BspInit(void)
{
//    StartDelay();
    LedInit();
    WatchDogInit();             //���Ź���ʼ��
    FeedWatchDog();
	SystickInit();
	SimUartInit();
    DelayMsWithNoneOs(2000);
	UsartInit();                //���ڳ�ʼ��
    TimerConfig(1, 1000);
    SystemResetRecord();
    printf("UsartInit OK!\r\n");
    SC8042B_Init();
    FM175XX_Config();
	

//������ʾ    
    PlayVoice(VOIC_WELCOME);            //��ӭʹ��
    DelayMsWithNoneOs(900);
//    PlayVoice(VOIC_SHARE_CHARGE);       //������
//    DelayMsWithNoneOs(900);
    printf("\r\n BspInit ok\n");
    printf("fw_version = %d, subVersion1 = %d, subVersion2 = %d.\n", (uint8_t)FW_VERSION, (uint8_t)FW_VERSION_SUB1, (uint8_t)FW_VERSION_SUB2);
}


int main(void)
{
	uint32_t NFCardTicks = GetTimeTicks();
	uint32_t HeartBeatTicks = NFCardTicks;
	uint32_t ShakeHandTicks = NFCardTicks;
    uint32_t RedLedTicks = NFCardTicks;
	uint32_t GreenLedTicks = NFCardTicks;
	uint32_t TimeFlagTicks = GetTimeTicks();
	
		
	nvic_vector_table_set(FLASH_BASE, BOOT_SIZE);        	//����Flash��ַƫ��
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);		//����ϵͳ�ж����ȼ�����4	
	
    BspInit();
	
    while(1)
    {
        FeedWatchDog();
		//DelayMsWithNoneOs(50);
		TimeFlagTicks = GetTimeTicks();
        {
        #if 1
            if(((RedLedTicks + 500) <= TimeFlagTicks) || (RedLedTicks > TimeFlagTicks))
            {
                RedLedTicks = TimeFlagTicks;
                RedLed();
            }
			
			if(((GreenLedTicks + 500) <= GetTimeTicks()) || (GreenLedTicks > GetTimeTicks()))
            {
                GreenLedTicks = GetTimeTicks();
                GreenLed();
			//	CL_LOG("SystemCoreClock[%d]\n", SystemCoreClock);
            }
			
			if(((NFCardTicks + 500) <= TimeFlagTicks) || (NFCardTicks > TimeFlagTicks))
            {
                NFCardTicks = TimeFlagTicks;
				
				if(CL_OK == BswDrv_FM175XX_SetPowerDown(0))		//�˳�˯��
				{
					NFCardTask();
				}
                BswDrv_FM175XX_SetPowerDown(1);			//����˯��
                FeedWatchDog();
            }
			
			if(0xa5 != GlobalInfo.ShakeHandState)
			{
				if(((ShakeHandTicks + 5000) <= TimeFlagTicks) || (ShakeHandTicks > TimeFlagTicks))
				{
                    FeedWatchDog();
                    ShakeHandTicks = TimeFlagTicks;
					BasicInfoShakeHand();
				}
			}
            DebugRecvProc();
            ComRecvMainBoardData();
			if(((HeartBeatTicks + 60000) <= TimeFlagTicks) || (HeartBeatTicks > TimeFlagTicks))
			{
                FeedWatchDog();
                HeartBeatTicks = TimeFlagTicks;
				BasicInfoHeartBeat();
				CL_LOG("SystemCoreClock[%d]\n", SystemCoreClock);
			}
		#endif
        }
    }
}





