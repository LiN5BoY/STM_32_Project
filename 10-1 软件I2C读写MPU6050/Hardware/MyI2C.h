#ifndef __MyI2C_H
#define __MyI2C_H

void MyI2C_Init(void);


// 配置六个基本条件
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);


#endif // !__MyI2C_H