#include "stm32f10x.h"

// Function prototypes
void TIM2_Config(void);
void PWM_SetDutyCycle(uint16_t dutyCycle);
void Delay(uint32_t time);

int main(void) {
    TIM2_Config();

    while (1) {
        // Set servo to 0 degrees
        PWM_SetDutyCycle(1000);  // 1ms pulse width
        Delay(5000);  // 5-second delay

        // Set servo to 90 degrees
        PWM_SetDutyCycle(1500);  // 1.5ms pulse width
        Delay(5000);  // 5-second delay

        // Set servo to 180 degrees
        PWM_SetDutyCycle(2000);  // 2ms pulse width
        Delay(5000);  // 5-second delay
    }
}

void TIM2_Config(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 19999;  // 20ms period (50Hz)
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;  // 72 MHz / 72 = 1 MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetDutyCycle(uint16_t dutyCycle) {
    TIM_SetCompare1(TIM2, dutyCycle);
}

void Delay(uint32_t time) {
    uint32_t i = 0;
    for (i = 0; i < time * 4000; i++);  // Roughly 1ms delay per loop iteration
}
