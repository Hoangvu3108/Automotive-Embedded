#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
// do no la ngoai vi vi vay phai cap clock cho no
void delay_ms(uint8_t timedelay){
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2)<timedelay*10) {}
}
// do o day la dem len 36000 lan va clockdivsion la chia 2 nen la 
void RCC_Config(void){
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
}
void TIM_Config(){
	TIM_TimeBaseInitTypeDef Tim_InitStruct;
	
	Tim_InitStruct.TIM_ClockDivision=TIM_CKD_DIV2;// binh thuong neu khong noi gi thi no se la lay 72MHz 
	//72MHz thi hoc thong tin so roi day
	Tim_InitStruct.TIM_Prescaler= 35999;
	// no dem tu 0 len den 35999 thi no se phai tru di 1 gia tri cua 36000
	Tim_InitStruct.TIM_Period= 0xFFFF;//  do muon khong bi ngat nen la cho gia tri nay la max
	Tim_InitStruct.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2,&Tim_InitStruct);
	TIM_Cmd(TIM2, ENABLE);
}
int main(){
	
	 RCC_Config(); // Configure the clock for TIM2
    TIM_Config(); // Configure TIM2

    while (1) {
        // Example: Delay for 500ms
        delay_ms(100);
        // Your main code here (e.g., toggle an LED)
    }
}