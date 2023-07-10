#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

#include "Serial.h"

uint8_t RxData;

int main(void){
	
	Serial_Init();
		
	OLED_Init();


	while(1){

		// 主循环里不断判断RXNE标志位
		// RXNE（Receive Data Register Not Empty）
		// 是USART中的一个标志位
		// 用于指示接收数据寄存器中是否有可用的接收数据。

		if(Seral_GetRxFlag() == 1){
			RxData = Seral_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1,1,RxData,2);
		}

	}

	
}
   