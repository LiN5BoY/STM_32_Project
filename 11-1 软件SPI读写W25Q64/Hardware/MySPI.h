#ifndef  __MYSPI_H
#define __MYSPI_H
void MySPI_Init(void);

void MySPI_Start(void);

void MySPI_Stop(void);

// 交换一个字节（4种模式） 选择实现模式0
uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif // ! __MYSPI_H

