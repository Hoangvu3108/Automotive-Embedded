#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

void delay_ms(uint16_t timedelay) {
    TIM_SetCounter(TIM2, 0);
    while(TIM_GetCounter(TIM2) < timedelay * 10) {}
}

void RCC_Config(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable clock for TIM2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Enable clock for GPIOC
}

void GPIO_Config(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // Assuming LED is connected to PC13
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO speed
    GPIO_Init(GPIOC, &GPIO_InitStructure); // Initialize GPIOA
	
}

void TIM_Config() {
    TIM_TimeBaseInitTypeDef Tim_InitStruct;
    
    Tim_InitStruct.TIM_ClockDivision = TIM_CKD_DIV2; // Clock division factor
    Tim_InitStruct.TIM_Prescaler = 35999; // Prescaler value
    Tim_InitStruct.TIM_Period = 0xFFFF; // Auto-reload value
    Tim_InitStruct.TIM_CounterMode = TIM_CounterMode_Up; // Up-counting mode
    
    TIM_TimeBaseInit(TIM2, &Tim_InitStruct); // Initialize TIM2
    TIM_Cmd(TIM2, ENABLE); // Enable TIM2
}

int main() {
    RCC_Config(); // Configure the clock for TIM2 and GPIOC
    GPIO_Config(); // Configure GPIOC for LED
    TIM_Config(); // Configure TIM2

    while (1) {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Turn on LED (assuming LED is active low)
        delay_ms(500); // Delay for 500ms
        GPIO_SetBits(GPIOC, GPIO_Pin_13); // Turn off LED
        delay_ms(500); // Delay for 500ms
    }
}
