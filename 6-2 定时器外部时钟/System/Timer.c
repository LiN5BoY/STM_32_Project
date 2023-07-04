#include "stm32f10x.h"                  // Device header
extern uint16_t Num;

void Timer_Init(void){

	//RCC内部时钟 ON
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	//时钟源选择
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x0F);
	
	//配置时机单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1 ;//因为预分频器和计数器都有1个数的偏差，所以这里要再减去一个1
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;/// Tout = （（arr+1）*（psc+1））/Tclk ;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	//配置输出中断控制
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//制特定中断通道的使能状态
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应优先级
	NVIC_Init(&NVIC_InitStructure); 
	
	//启动定时器
	TIM_Cmd(TIM2,ENABLE);
}

uint16_t Timer_GetCount(void){
	return TIM_GetCounter(TIM2);
}

void TIM2_IRQHandler(void) {
		if (TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//获取中断标志位并进行判定
		{
			Num++;
			TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		}

}
