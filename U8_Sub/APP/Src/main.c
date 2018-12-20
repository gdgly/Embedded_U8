/*****************************************************************************
** @Author: quqian  
** @Date: 2018-11-15 14:20:14 
** @File: main.c
** @MCU: GD32F330CBT6   
** @MCU max Speed: 84M
** @MCU Flash: 128K
** @MCU RAM: 16K
** @MCU Package: LQFP48
** @Last Modified by: quqian
** @Last Modified time: 2018-12-10 14:20:14 
*****************************************************************************/
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
#if USE_TIMER1
    TimerConfig(1, 1000);
#endif
	RtcInit();
	LoadSystemInfo();
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
    printf("\n===========================================================\n\n\n");
}


int main(void)
{
	uint32_t NFCardTicks = GetTimeTicks();
	uint32_t HeartBeatTicks = NFCardTicks;
	uint32_t ShakeHandTicks = NFCardTicks;
    uint32_t RedLedTicks = NFCardTicks;
	uint32_t GreenLedTicks = NFCardTicks;
	uint32_t TimeFlagTicks = GetTimeTicks();
//	struct tm TimeTickss;
//    uint32_t timeaaa;
    
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
            if(((RedLedTicks + 5000) <= TimeFlagTicks) || (RedLedTicks > TimeFlagTicks))
            {
                CL_LOG("SystemCoreClock[%d]\n", SystemCoreClock);
                RedLedTicks = TimeFlagTicks;
                RedLed();
            }
			
			if(((GreenLedTicks + 500) <= GetTimeTicks()) || (GreenLedTicks > GetTimeTicks()))
            {
                GreenLedTicks = GetTimeTicks();
                GreenLed();
			//	CL_LOG("SystemCoreClock[%d]\n", SystemCoreClock);
//			#if 0
//				rtc_current_time_get(&GlobalInfo.RtcData);
//				memset(&TimeTickss,0,sizeof(struct tm));
//				TimeTickss.tm_year = GlobalInfo.RtcData.rtc_year + 1992;
//				TimeTickss.tm_mon = GlobalInfo.RtcData.rtc_month + 9;
//				TimeTickss.tm_mday = GlobalInfo.RtcData.rtc_date ;
//				TimeTickss.tm_wday = GlobalInfo.RtcData.rtc_day_of_week;
//				TimeTickss.tm_hour = GlobalInfo.RtcData.rtc_hour;
//				TimeTickss.tm_min = GlobalInfo.RtcData.rtc_minute;
//				TimeTickss.tm_sec = GlobalInfo.RtcData.rtc_second;
//                timeaaa = mktime(&TimeTickss);
//			#endif
//                CL_LOG("ʱ���[%d]\n", timeaaa);
            }
	
            
			if(((NFCardTicks + 500) <= TimeFlagTicks) || (NFCardTicks > TimeFlagTicks))
            {
                NFCardTicks = TimeFlagTicks;
				if(GlobalInfo.UpgradeFlag != 0xa5)
				{
					if(CL_OK == BswDrv_FM175XX_SetPowerDown(0)) 	//�˳�˯��
					{
						NFCardTask();
					}
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
		//		CL_LOG("SystemCoreClock[%d]\n", SystemCoreClock);
			}
		#endif
        }
    }
}





