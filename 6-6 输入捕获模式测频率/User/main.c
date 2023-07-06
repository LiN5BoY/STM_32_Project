#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint8_t i;

int main(void){
	
	
	OLED_Init();
	PWM_Init();	
	IC_Init();
	// Freq = 72M / (PSC + 1) / (ARR + 1)
	// PSC寄存器是定时器的预分频器，用于将定时器输入时钟频率进行分频。
	// ARR寄存器是定时器的自动重装载寄存器，用于存储定时器的重装载值。
	PWM_SetPrescaler(720 - 1);
	
	// Duty = CCR / (ARR + 1)
	PWM_SetCompare1(50);

	OLED_ShowString(1,1,"Freq:00000HZ");


	
	while(1){
		
		OLED_ShowNum(1,6,IC_GetFreq(),5);


	}

	
}
 