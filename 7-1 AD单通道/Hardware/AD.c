#include "stm32f10x.h"                  // Device header



void AD_Init(void){
    // 开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    // 配置ADCCLK
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    // 配置GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);



    ADC_InitTypeDef ADC_InitStructure = {
        .ADC_ContinuousConvMode = DISABLE,//持续扫描转换模式
        .ADC_DataAlign = ADC_DataAlign_Right,//数据数据
        .ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ,//外部触发转换选择——触发控制的触发源
        .ADC_Mode = ADC_Mode_Independent,//数据模式
        .ADC_NbrOfChannel = 1,//通道数目
        .ADC_ScanConvMode = DISABLE//扫描转换模式
    };
    ADC_Init(ADC1,&ADC_InitStructure);

    // 开启电源
    ADC_Cmd(ADC1,ENABLE);

    // 进行校准
    // 1.复位校准
    ADC_GetResetCalibrationStatus(ADC1);
    // 2.等待复位校准完成
    while(ADC_GetResetCalibrationStatus(ADC1) == SET)   ;
    // 3.开始校准
    ADC_StartCalibration(ADC1);
    // 4.等待校准完成
    while(ADC_GetCalibrationStatus(ADC1) == SET);
}


uint16_t AD_GetValue(uint8_t ADC_Channel)
{
    // 选择规则组的输入通道
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);
    // ADC 进行转换
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    // 获取标志位状态
    while( ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET); // 规则组EOC
    //ADC获取转换值
    return ADC_GetConversionValue(ADC1);

}

