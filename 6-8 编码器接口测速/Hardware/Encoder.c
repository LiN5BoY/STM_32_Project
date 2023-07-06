#include "stm32f10x.h"                  // Device header

void Encoder_Init(void){

    //配备时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //RCC内部时钟 ON
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);



	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1 ;//因为预分频器和计数器都有1个数的偏差，所以这里要再减去一个1 ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;/// Tout = （（arr+1）*（psc+1））/Tclk ; PSC
    //频率1KHz,占空比50%,分辨率为1%的PWM波形 
    //72M / 10000 / 7200 = 72000000 / 10000 / 7200 = 72000 / 7200 = 10
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);
 
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1,
    TIM_ICInitStructure.TIM_ICFilter = 0XF, //滤波器
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising, // 上升沿触发

    TIM_ICInit(TIM3,&TIM_ICInitStructure);


    
    TIM_ICStructInit(&TIM_ICInitStructure);
 
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2,
    TIM_ICInitStructure.TIM_ICFilter = 0XF, //滤波器
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising, // 上升沿触发

    TIM_ICInit(TIM3,&TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);


    // 开启定时器
    TIM_Cmd(TIM3,ENABLE);
}

int16_t Encoder_Get(void){
    int16_t temp;
    temp = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);
    return temp;
}
