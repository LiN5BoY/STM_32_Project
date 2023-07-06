#include "stm32f10x.h"

#include "PWM.h"



void Motor_Init(void){
    PWM_Init();

    //配备时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //电机方向控制脚初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
    

}

void Motor_SetSpeed(int8_t speed){
    if(speed>=0){
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);
        PWM_SetCompare3(speed);
    }else{
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        PWM_SetCompare3(-speed);    
    }
}