#include "stm32f10x.h"

// H�m c?u h�nh GPIO cho LED
void LED_Init(void) {
    // B?t Clock cho GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // C?u h�nh ch�n PA5 l�m Output push-pull
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; // T?c d? GPIO
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// H�m b?t LED
void LED_On(void) {
    GPIO_SetBits(GPIOA, GPIO_Pin_5); // �ua ch�n PA5 l�n m?c cao d? b?t LED
}

// H�m t?t LED
void LED_Off(void) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_5); // �ua ch�n PA5 xu?ng m?c th?p d? t?t LED
}

// H�m t?o d? tr? don gi?n
void delay_ms(uint32_t ms) {
    for(uint32_t i = 0; i < ms * 8000; i++); // Nh�n v?i m?t gi� tr? d? l?n d? t?o d? tr? tuong d?i
}

int main(void) {
    // Kh?i t?o LED
    LED_Init();
    
    while (1) {
        // B?t LED v� ch? 500ms
        LED_On();
        delay_ms(500);
        
        // T?t LED v� ch? 500ms
        LED_Off();
        delay_ms(500);
    }
}
