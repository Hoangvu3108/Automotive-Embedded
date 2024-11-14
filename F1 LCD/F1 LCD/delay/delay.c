#include "delay.h"

void Delay1Ms(void)
{
	TIM_SetCounter(TIM2,0);
	while (TIM_GetCounter(TIM2)<1000){
	}
}

void delay_us(uint32_t delay)
{	
				TIM_SetCounter(TIM2, 0);
				while(TIM_GetCounter(TIM2)< delay){
				}
}
	
void Delay_Ms(uint32_t u32DelayInMs)

{
	while(u32DelayInMs){
			Delay1MS();
		--u32DelayInMs;
	}
	
	
}
void TIM_Config(){
	TIM_TimeBaseInitTypeDef.TIM_TimeBaseInitStructure;
	
	
	TIM_TimeBaseInitStructure.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=20000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM2,ENABLE);
	
}