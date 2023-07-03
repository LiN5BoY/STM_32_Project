#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"

uint8_t KeyNum;

int main(void){
	
	LED_Init();
	
	Key_Init();
	
	OLED_Init();
	OLED_ShowNum(1,1,KeyNum,1);
	
	while(1){
		
		KeyNum = Key_GetNum();
		
		KeyNum == 1 ? LED_Turn(GPIOA,GPIO_Pin_1) : LED_Turn(GPIOA,GPIO_Pin_2);
	
		Delay_s(1);
		OLED_ShowNum(1,1,KeyNum,1);
	}

	
}
 