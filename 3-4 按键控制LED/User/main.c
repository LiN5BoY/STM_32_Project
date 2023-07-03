#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "Key.h"

uint8_t KeyNum = 3;

int main(void){
	
	LED_Init();
	
	Key_Init();
	
	while(1){
		
		KeyNum = Key_GetNum();
		
		KeyNum == 1 ? LED_Turn(GPIOA,GPIO_Pin_1) : LED_Turn(GPIOA,GPIO_Pin_2);
		
	}

	
}
 