#ifndef __BUZZER_H
#define __BUZZER_H



void Buzzer_Init(void);

void Buzzer_Turn(GPIO_TypeDef * g,uint16_t a);


void Set_Buzzer(GPIO_TypeDef * g,uint16_t a,int x);





#endif