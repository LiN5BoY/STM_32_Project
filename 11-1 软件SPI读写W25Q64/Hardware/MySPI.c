#include "stm32f10x.h"                  // Device header


//从机选择
void MySPI_W_SS(uint8_t BitValue){
    GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}

void MySPI_W_SCK(uint8_t BitValue){
    GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
}

void MySPI_W_MOSI(uint8_t BitValue){
    GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
}

uint8_t MySPI_R_MISO(void){
    return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}

void MySPI_Init(void){
	// 配备时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
    // 输出引脚配置为推挽输出，输入引脚配置为浮空或上拉输入
    /*
        推挽输出：引脚既能提供高电平输出，又能提供低电平输出。
            在这种模式下，引脚可以直接驱动高电平或低电平的外部负载。

        浮空输入：这种输入模式下，引脚没有连接到外部电源或地，处于开路状态。
            当没有外部信号输入时，引脚处于高阻态，没有明确定义的电平。
            浮空输入常用于接收外部信号，并需要外部电路或器件通过外部上拉或下拉电阻来确定引脚的电平状态。

        上拉输入：在这种输入模式下，引脚通过内部上拉电阻连接到电源电压（一般是Vdd）。
            当没有外部信号输入时，引脚通过内部上拉电阻拉高到电源电压，形成逻辑高电平。
            外部信号驱动引脚为低电平时，引脚的电平被拉低。
            上拉输入模式常用于接收外部开关、按键等信号，可以通过外部元件的闭合与断开来改变引脚的电平状态。
    */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);

    MySPI_W_SS(1);// 默认电平置为高电平
    MySPI_W_SCK(0);// SPI模式，低电平 
}

void MySPI_Start(void){
    MySPI_W_SS(0);
}

void MySPI_Stop(void){
    MySPI_W_SS(1);
}

// 交换一个字节（4种模式） 选择实现模式0
uint8_t MySPI_SwapByte(uint8_t ByteSend){
    uint8_t ByteReceive = 0x00,i;
    
    // 实现时序
    // 主机和从机同时移出数据
    // 主机->MOSI 从机->MISO
    for(i = 0 ; i < 8 ;i++){
        MySPI_W_MOSI(ByteSend & (0x80 >> i));
        MySPI_W_SCK(1);
        // 读取的数据是最高位
        if(MySPI_R_MISO() == 1){
            ByteReceive |= (0x80 >> i);
        }
        MySPI_W_SCK(0); // 产生下降沿
    }


    return ByteReceive;
}
