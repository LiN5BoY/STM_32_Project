#include "stm32f10x.h"                  // Device header

#include "Delay.h"
#include "Buzzer.h"
#include "LightCensor.h"

int main(void){
	
	Buzzer_Init();
	LightCensor_Init();
	
	while(1){

			if(LightSensor_Get(GPIO_Pin_13)==0){
				Set_Buzzer(GPIOA,GPIO_Pin_12,0);
			}else{
				Set_Buzzer(GPIOA,GPIO_Pin_12,0);
			}
			
	}
	
}
 