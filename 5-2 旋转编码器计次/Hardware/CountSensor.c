#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count = 0;

void CountSensor_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置AFIO外部中断引脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,	GPIO_PinSource14);
	
	//EXTI（External Interrupt）是一个外部中断控制器。
	//它用于处理外部触发的中断信号，例如按键、传感器或其他外部设备引发的事件。
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC（Nested Vectored Interrupt Controller）用于处理中断请求和分配中断优先级。
	//用来配置中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	
	NVIC_Init(&NVIC_InitStructure);
	
}

uint16_t CountSensor_Count_Get(void){
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void){
		if( EXTI_GetITStatus(EXTI_Line14) == SET){
			CountSensor_Count++;
			// 在Keil MDK（Microcontroller Development Kit）中，
			// EXTI_ClearITPendingBit函数用于清除外部中断线的中断挂起标志位。
			EXTI_ClearITPendingBit(EXTI_Line14);
			
		}
}
