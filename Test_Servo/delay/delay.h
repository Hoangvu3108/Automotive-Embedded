#ifndef DELAY_H_
#define DELAY_H_

	#include "stm32f10x.h"
	#include "stm32f10x_tim.h"
void Delay1Ms(void);
void delay_us(uint32_t delay);
void Delay_Ms(uint32_t u32DelayInMs);
void TIM_Config();
#endif