#include "stm32f10x.h"                  // Device header


void PWM_Init(void){

	//配备时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);

    //RCC内部时钟 ON
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//时钟源选择
	TIM_InternalClockConfig(TIM2);
	
	//配置时机单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1 ;//因为预分频器和计数器都有1个数的偏差，所以这里要再减去一个1 ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;/// Tout = （（arr+1）*（psc+1））/Tclk ; PSC
    //频率1KHz,占空比50%,分辨率为1%的PWM波形 
    //72M / 10000 / 7200 = 72000000 / 10000 / 7200 = 72000 / 7200 = 10
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
	TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//设置比较输出模式
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//设置比较的极性
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//设置输出的使能
    TIM_OCInitStruct.TIM_Pulse = 0;//设置CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);

	
	//启动定时器
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare1(uint16_t Compare){
	TIM_SetCompare1(TIM2,Compare);
}


void PWM_SetPrescaler(uint16_t Prescaler){
	//单独写入PSC的函数
	//PSC代表预分频器（Prescaler）。预分频器是定时器模块的一个重要组成部分，用于调整定时器的输入时钟频率。
	TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Immediate);
}