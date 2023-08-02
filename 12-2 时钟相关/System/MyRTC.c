#include "stm32f10x.h"
#include <time.h>

uint16_t MyRTC_Time[] = {2023,1,1,23,59,55};

void MyRTC_SetTime(void);

void MyRTC_Init(void)
{
    // 使PWR和BKP开启时钟
    // PWR(Power Control) , BKP(Backup Registers)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);

    // 允许对备份区域进行读写操作
    PWR_BackupAccessCmd(ENABLE);

    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5){
        // 重复初始化
        BKP_DeInit(); 
        // 用于配置外部低速时钟（LSE，Low-Speed External）
        RCC_LSEConfig(RCC_LSE_ON);
        // 检测外部低速时钟（LSE，Low-Speed External）是否稳定就绪的状态
        while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
        // 配置RTC（Real-Time Clock，实时时钟）的时钟源
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);

        // 等待同步
        RTC_WaitForSynchro();
        RTC_WaitForLastTask();

        RTC_SetPrescaler(32767);
        RTC_WaitForLastTask();

        MyRTC_SetTime();

        BKP_WriteBackupRegister(BKP_DR1,0XA5A5);
    }
    else{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
    }
}

void MyRTC_SetTime(void){

    time_t time_cnt;
    struct tm time_date;

	time_date.tm_year = MyRTC_Time[0] - 1900;
	time_date.tm_mon = MyRTC_Time[1] - 1;
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_hour = MyRTC_Time[3];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_sec = MyRTC_Time[5];

    time_cnt = mktime(&time_date) - 8 * 60 * 60;

    RTC_SetCounter(time_cnt);
    RTC_WaitForLastTask();

}

void MyRTC_ReadTime(void)
{
	time_t time_cnt;
	struct tm time_date;
	
	time_cnt = RTC_GetCounter() + 8 * 60 * 60;
	
	time_date = *localtime(&time_cnt);
	
	MyRTC_Time[0] = time_date.tm_year + 1900;
	MyRTC_Time[1] = time_date.tm_mon + 1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;
}
