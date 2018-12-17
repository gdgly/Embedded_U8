/*
 * @Author: zhoumin 
 * @Date: 2018-11-07 15:45:46 
 * @Last Modified by: zhoumin
 * @Last Modified time: 2018-11-22 20:21:17
 */

#include "BswDrv_Rtc.h"
#include "includes.h"


static int LinuxTickToDay(time_t timestamp, uint8_t *pDay);
 

/*******************************************************
����ԭ��:   int LinuxTickToDay(time_t timestamp, uint8_t *pDay)
��������:   time_t timestamp:Linuxʱ���
            uint8_t *pDay��Linuxʱ���ת�����ʱ��
��������:   ��Linuxʱ���ת��Ϊ��ǰ��ʱ��
����ֵ  :   ��
********************************************************/
int LinuxTickToDay(time_t timestamp, uint8_t *pDay)
{
    struct tm *time_now;

	time_now = localtime(&timestamp);
    pDay[0] = time_now->tm_wday;
    pDay[1] = time_now->tm_year-100;
    pDay[2] = time_now->tm_mon+1;
    pDay[3] = time_now->tm_mday;
    pDay[4] = time_now->tm_hour;
    pDay[5] = time_now->tm_min;
    pDay[6] = time_now->tm_sec;
    return CL_OK;
}



/*******************************************************
����ԭ��:   char* GetCurrentTime(void)
��������:   ��
��������:   �õ���ǰ��ʱ��
����ֵ  :   char *
********************************************************/
static char gTimeStr[32];
char* GetCurrentTime(void)
{
    uint32_t time;
    uint8_t day[8];
	
    time = rtc_counter_get();
    LinuxTickToDay(time,day);

    sprintf(gTimeStr,"%02u-%02u %02u:%02u:%02u", day[2], day[3], day[4], day[5], day[6]);
	
    return gTimeStr;
}


void GetRtcTime(void* pRTCTime)
{
    uint32_t time = 0;
    time = rtc_counter_get();
    LinuxTickToDay(time,pRTCTime);
}



/*******************************************************
����ԭ��:   void SetRtcCount(time_t timestamp)
��������:   time_t timestamp��Linuxʱ���
��������:   ��Linuxʱ���ת��Ϊ��ǰ��ʱ�䲢���õ�RTC�Ĵ���
����ֵ  :
********************************************************/
void SetRtcCount(time_t timestamp)
{
    rtc_lwoff_wait();
    rtc_counter_set(timestamp+8*60*60);
    rtc_lwoff_wait();
}

/*******************************************************
����ԭ��:   time_t GetTimeStamp(void)
��������:   ��
��������:   ��ȡ��ǰ��ʱ���
����ֵ  :   ʱ���
********************************************************/
time_t GetTimeStamp(void)
{
	struct tm *time_now;
	
	uint32_t tick = rtc_counter_get();
	
	time_now = localtime(&tick);
	time_now->tm_hour -= 8;
	
	return mktime(time_now);	
}


void RTC_Configure(void)
{
    rcu_osci_on(RCU_IRC40K);         //ʹ���ڲ�����ʱ��
    rcu_osci_stab_wait(RCU_IRC40K);

    rcu_rtc_clock_config(RCU_RTCSRC_IRC40K);

    rcu_periph_clock_enable(RCU_RTC);
    rtc_register_sync_wait();

    rtc_lwoff_wait();

    rtc_prescaler_set(40000-1);//

    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();
}

void BswDrv_RtcInit(void)
{
    rcu_periph_clock_enable(RCU_BKPI);
    rcu_periph_clock_enable(RCU_PMU);
    pmu_backup_write_enable();
    
   if (bkp_read_data(BKP_DATA_0) != 0xA5A5){        
        bkp_deinit();
        RTC_Configure();
		bkp_write_data(BKP_DATA_0, 0xA5A5);
	}else {
        rcu_osci_on(RCU_IRC40K);         //ʹ���ڲ�����ʱ��
        rcu_osci_stab_wait(RCU_IRC40K);
    }
}

