#include "stm32f10x.h"
#include "Delay.h"
#define SCL_PORT GPIOB
#define SCL_PIN GPIO_Pin_10

void MyI2C_W_SCL(uint8_t BitValue){
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
    Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue){
    GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
    Delay_us(10);
}

uint8_t MyI2C_R_SDA(void){
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
    Delay_us(10);
    return BitValue;
}

void MyI2C_Init(void){

    // 软件I2C初始化
    // 1.SCL和SDA都初始化为开漏输出模式
    /* 
        SCL和SDA引脚是用于通信的两个重要引脚
            SCL（Serial Clock）是串行时钟线，用于同步I2C总线上的数据传输。
            它由主设备（通常是微控制器）提供，并用于驱动数据传输的时钟信号。
            SDA（Serial Data）是串行数据线，用于在I2C总线上传输数据。
            所有连接到I2C总线的设备都共享SDA线，因此它是一个双向线路。数据的传输是在SCL的时钟信号下进行的。
        开漏输出模式：需要外部上拉电阻
    */
   // 配备时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;// 开漏输出模式 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
   // 2.SCL和SDL置为高电平
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);


   
}


// 配置六个基本条件
void MyI2C_Start(void){
    // 先都释放SCL与SDA,也就是都置为1
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    // 先拉低SDA,再拉低SCL
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);
}
void MyI2C_Stop(void){
    // 先拉低SDA 再释放SCL 再释放SDA
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t byte){
    // 趁SCL低电平，先将Byte的最高位挂在SDA上
    uint8_t i;
    for (i = 0 ; i < 8 ; i++){
        MyI2C_W_SDA(byte & (0x80 >> i));
        MyI2C_W_SCL(1);
        MyI2C_W_SCL(0);
    }
}
uint8_t MyI2C_ReceiveByte(void){
    uint8_t i,byte = 0x00;
    MyI2C_W_SDA(1);
    for(i = 0 ; i < 8 ; i++){
        MyI2C_W_SCL(1);
        if (MyI2C_R_SDA() == 1)
            byte |= (0x80 >> i); //最高位置为1
        MyI2C_W_SCL(0);   
    }
    return byte;
}

void MyI2C_SendAck(uint8_t AckBit){
    // 趁SCL低电平，先将Byte的最高位挂在SDA上
    MyI2C_W_SDA(AckBit);
    MyI2C_W_SCL(1);
    MyI2C_W_SCL(0);
}
uint8_t MyI2C_ReceiveAck(void){
    uint8_t AckBit;
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    AckBit = MyI2C_R_SDA();
    MyI2C_W_SCL(0);   
    return AckBit;
}

