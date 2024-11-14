#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_tim.h"

void GPIO_Config(void);
void ADC1_Init(void);
void TIM2_Init(void);
void TIM4_ms_Delay(uint32_t delay);
int u;

void GPIO_Config() {
    // Enable GPIOC and GPIOA clocks
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    // PC0 is connected to ADC1 IN10, set PC0 to Analog mode
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    // Configure PA5 as alternate function (TIM2_CH1)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Set PA5 to alternate function TIM2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
}

void ADC1_Config() {
    // Enable ADC1 clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // ADC common initialization
    ADC_CommonInitTypeDef ADC_CommonInitStruct;
    ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStruct);

    // ADC1 initialization
    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &ADC_InitStruct);

    // Configure ADC1 regular channel10 (PC0)
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_144Cycles);

    // Enable ADC1
    ADC_Cmd(ADC1, ENABLE);
}

void TIM2_Config() {
    // Enable TIM2 clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // Time base configuration
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Period = 20000 - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 16 - 1;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // PWM mode configuration for TIM2 channel 1
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 500; // Initial pulse width
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);

    // Enable TIM2
    TIM_Cmd(TIM2, ENABLE);
}

void TIM4_ms_Delay(uint32_t delay) {
    // Enable TIM4 clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    // Time base configuration for TIM4
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Period = delay - 1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 16000 - 1;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);

    // Start TIM4
    TIM_Cmd(TIM4, ENABLE);

    // Wait until TIM4 update event
    while (!TIM_GetFlagStatus(TIM4, TIM_FLAG_Update)) {}

    // Clear TIM4 update flag
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
}

int main(void) {
    GPIO_Config();
    ADC1_Config();
    TIM2_Config();

    while (1) {
        // Start ADC1 conversion
        ADC_SoftwareStartConv(ADC1);

        // Wait until ADC conversion is complete
        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {}

        // Read ADC value
        u = ADC_GetConversionValue(ADC1);

        // Update TIM2 PWM duty cycle based on ADC value
        TIM_SetCompare1(TIM2, (int)(((u / 4095.0) * 2000) + 500));

        // Delay using TIM4
        TIM4_ms_Delay(50);
    }
}
