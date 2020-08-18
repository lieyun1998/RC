#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f4xx.h"

#define BEEP_TIME 1000 // ���������ʱ�䣨��λ��ms��

void beep_GPIO_init(void);
void beep_control(void);
void beep_turn_on(void);
void beep_turn_off(void);

#endif
