#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

#include "Serial.h"

uint8_t KeyNum;

int main(void){
	
	Serial_Init();
		
	OLED_Init();

	// char MyArray[] = "Hello World";

	// Serial_SendString(MyArray);

	//	Serial_SendNumber(12345,5);
	
	Serial_Printf("Num=%d\r\n",666);
	

	while(1){
 
	}

	
}
   