#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>

void Serial_Init(void);

void Serial_SendByte(uint8_t byte);

void Serial_SendArray(uint8_t *Array,uint16_t Length);

void Serial_SendString(char *String);

void Serial_SendNumber(uint32_t Number,uint8_t Length);

void Serial_Printf(char *format,...);

uint8_t Seral_GetRxFlag(void);

uint8_t Seral_GetRxData(void);

#endif // !__SERIAL_H
