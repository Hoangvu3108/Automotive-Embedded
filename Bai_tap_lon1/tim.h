#ifndef __TIM_H__
#define __TIM_H__
/* Includees */

#include "stm32f10x.h"                  // Device header


#define TIMER_DELAY                 TIM1
#define TIMER_DELAY_RCC							RCC_APB2Periph_TIM1
#define TIMER_PWM										TIM2
#define TIMER_PWM_RCC 							RCC_APB1Perph_TIM2
/* Exported funtions---------------------------------*/

void TIMDelay_Config(void);
void Delay_Init(void);
void TIMPWM_Config(void);
void Delay_ms(uint32_t time);
void Delay_us(uint32_t u32DelayInUs);

#endif /*__TIM_H__*/