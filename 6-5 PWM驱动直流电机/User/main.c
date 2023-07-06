#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"

uint8_t KeyNum;
int8_t Speed;
int main(void){
	
	
	OLED_Init();
	Motor_Init();
	Key_Init();
	
	Motor_SetSpeed(0);
	OLED_ShowString(1,1,"Speed:");
	
	while(1){
		
		KeyNum = Key_GetNum();
		if(KeyNum  == 1){
			Speed += 20;
			Speed = Speed >	 100 ? -100 : Speed;
		}

		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1,7,Speed,3);
	}

	
}
 