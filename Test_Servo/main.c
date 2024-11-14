#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Device:StdPeriph Drivers:ADC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "delay.h"

void Delay1Ms(void)
{
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < 1000) {
    }
}

void delay_us(uint32_t delay)
{
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < delay) {
    }
}

void Delay_Ms(uint32_t u32DelayInMs)
{
    while (u32DelayInMs) {
        Delay1Ms();
        --u32DelayInMs;
    }
}

void RCC_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // PA0 as Analog input (for ADC)
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // PA1 as Alternate Function Push-Pull (for PWM output to Servo)
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void TIM_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   
    
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;    // 20ms period for PWM
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;    // 1 MHz timer frequency
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    
		TIM_OCInitTypeDef TIM_OCInitStructure;
    
	// Configure PWM mode
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500; // Start with 1.5ms pulse (servo at 90 degrees)
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);
			
    TIM_Cmd(TIM2, ENABLE);
}

void ADC_Config(void)
{
    ADC_InitTypeDef ADC_InitStruct;
    
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_NbrOfChannel = 1;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    
    ADC_Init(ADC1, &ADC_InitStruct);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

int main(void)
{
    uint16_t adc_value = 0;
    uint16_t pwm_value = 0;

    RCC_Config();
    GPIO_Config();
    ADC_Config();
    TIM_Config();
    
    while (1) {
        // Ð?c giá tr? ADC t? bi?n tr?
        adc_value = ADC_GetConversionValue(ADC1);
        
        // Chuy?n d?i giá tr? ADC sang d? r?ng xung PWM
        pwm_value = (adc_value * 2000) / 4095 + 500;  // 500 µs d?n 2500 µs
        
        // C?p nh?t giá tr? PWM cho Servo
        TIM_SetCompare1(TIM2, pwm_value);
        
        Delay_Ms(20);  // Delay nh? d? c?p nh?t PWM
    }
}
