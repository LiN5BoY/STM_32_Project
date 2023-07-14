#include "stm32f10x.h"                  // Device header


//从机选择
void MySPI_W_SS(uint8_t BitValue){
    GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}


void MySPI_Init(void){
	// 配备时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	
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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);


    // SPI代表串行外围接口（Serial Peripheral Interface），
    // 它是一种常见的串行通信协议和接口标准。
    // SPI被广泛用于与外部设备（如传感器、存储器、显示器等）进行高速、全双工的数据交换。
    SPI_InitTypeDef SPI_InitStructure = {
      .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128,// 波特率预分频器
      .SPI_CPHA = SPI_CPHA_1Edge,//第一个边沿开始采样
      .SPI_CPOL = SPI_CPOL_Low,// 时钟极性：低电平
      .SPI_CRCPolynomial = 7,//默认值：7
      .SPI_DataSize = SPI_DataSize_8b,// 8位数据帧
      .SPI_Direction = SPI_Direction_2Lines_FullDuplex,// 双线全双工
      .SPI_FirstBit = SPI_FirstBit_MSB,// 高位先行 
      .SPI_Mode = SPI_Mode_Master,// 选择为主机
      .SPI_NSS = SPI_NSS_Soft
    };
    SPI_Init(SPI1,&SPI_InitStructure);

    SPI_Cmd(SPI1,ENABLE);

    MySPI_W_SS(1);
}

void MySPI_Start(void){
    MySPI_W_SS(0);
}

void MySPI_Stop(void){
    MySPI_W_SS(1);
}

// 交换一个字节（4种模式） 选择实现模式0
uint8_t MySPI_SwapByte(uint8_t ByteSend){
    // Transmit Empty
    // 发送缓冲区是否为空进行循环判断
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) != SET);

    SPI_I2S_SendData(SPI1,ByteSend);

    // Receive Not Empty
    // 用于指示接收缓冲区是否非空。
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) != SET);

    return SPI_I2S_ReceiveData(SPI1);
}
