#include "stm32f10x.h"                  // Device header

void IC_Init(void){

	//配备时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);

    //RCC内部时钟 ON
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//时钟源选择
	TIM_InternalClockConfig(TIM3);
	
	//配置时基 单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1 ;//因为预分频器和计数器都有1个数的偏差，所以这里要再减去一个1 ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;/// Tout = （（arr+1）*（psc+1））/Tclk ; PSC
    //频率1KHz,占空比50%,分辨率为1%的PWM波形 
    //72M / 10000 / 7200 = 72000000 / 10000 / 7200 = 72000 / 7200 = 10
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);


    TIM_ICInitTypeDef TIM_ICInitStructure = {
        .TIM_Channel = TIM_Channel_1,
        .TIM_ICFilter = 0XF, //滤波器
        .TIM_ICPolarity = TIM_ICPolarity_Rising, // 上升沿触发
        .TIM_ICPrescaler = TIM_ICPSC_DIV1,//分频器
        .TIM_ICSelection = TIM_ICSelection_DirectTI //直连通道
    };

    TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);

    //配置触发源
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    //从模式设置
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);

    TIM_Cmd(TIM3,ENABLE);

}


uint32_t IC_GetFreq(void){

    // 1000000 -> 1Mhz
    // 除以ccr
    return 1000000 / (TIM_GetCapture1(TIM3) + 1);

}


uint32_t IC_GetDuty(void){

    // 占空比
    return (TIM_GetCapture2(TIM3) + 1) * 100  / (TIM_GetCapture1(TIM3) + 1);

}