#include "stm32f10x.h"

uint16_t MyDMA_Size;
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint32_t Size){

    // 初始化
    MyDMA_Size = Size;
    // 1.RCC开启DMA的时钟
    // DMA是隶属于AHB总线的设备，所以用AHB开启时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    // 2.调用Init函数进行初始化参数
    DMA_InitTypeDef DMA_Init_Structure = {
        .DMA_BufferSize = Size,// 缓冲区大小——传输计数器
        .DMA_DIR = DMA_DIR_PeripheralSRC, //指定外设站点是源端还是目的地
        .DMA_M2M = DMA_M2M_Enable,//传输模式（硬件触发还是软件触发）
        .DMA_MemoryBaseAddr = AddrB,
        .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
        .DMA_MemoryInc = DMA_MemoryInc_Enable,
        .DMA_Mode = DMA_Mode_Normal,// 传输模式
        .DMA_PeripheralBaseAddr = AddrA,
        .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,// 外设
        .DMA_PeripheralInc = DMA_PeripheralInc_Enable, // 自增设置
        .DMA_Priority = DMA_Priority_Medium 
    };

    DMA_Init(DMA1_Channel1,&DMA_Init_Structure);
    // 3.开关使能设置
    DMA_Cmd(DMA1_Channel1,DISABLE);
}

void MyDMA_Transfer(void){
    //先让DMA失能
    DMA_Cmd(DMA1_Channel1,DISABLE);
    // 重新给传输计数器赋值
    DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);
    DMA_Cmd(DMA1_Channel1,ENABLE);
    //等待转运完成
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);    
}   
