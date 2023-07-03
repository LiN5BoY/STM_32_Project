#include "stm32f10x.h"                  // Device header


void Buzzer_Init(void)
{
	//配备时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_Turn(GPIO_TypeDef * g,uint16_t a){
	if(GPIO_ReadOutputDataBit(g,a)==0){
		GPIO_SetBits(g,a);
	}else{
		GPIO_ResetBits(g,a);
	}
}


void Set_Buzzer(GPIO_TypeDef * g,uint16_t a,int x){
	if(x==0){
		//低电平
		GPIO_ResetBits(g,a);
	}else{
		//高电平
		GPIO_SetBits(g,a);
	}
}

