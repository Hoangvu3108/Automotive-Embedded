#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"             // Device:StdPeriph Drivers:EXTI
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

void RCC_Config(){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
}
void GPIO_Config(){
		GPIO_InitTypeDef GPIO_InitStruct;	
	

		GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
		
	
		GPIO_Init(GPIOA,&GPIO_InitStruct)	;
}

void TIM_Config(){
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	
		TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;
		TIM_TimeBaseInitStruct.TIM_Period=10-1; 
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode= TIM_CounterMode_Up;
	
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
		TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);// Chu y TIM_IT_UPDATE
		TIM_Cmd(TIM2, ENABLE);
}
void NVIC_Config()
	{			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
				
				NVIC_InitTypeDef NVIC_InitStruct;
		
		
				NVIC_InitStruct.NVIC_IRQChannel= TIM2_IRQn;
				NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1 ;// do uu tien chinh	
				NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;					// do uu tien phu
				NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
				
				NVIC_Init(&NVIC_InitStruct);
}
	uint16_t count, cnt=0;

void delay_ms(uint16_t time){
	count=0;
	while(count<time){
	}
}
// ham phuc ngat cua timer
// cu sau 1ms la ham phuc vu ngat duoc goi ra 1 lan
void TIM2_IRQHandler(){
		if(TIM_GetITStatus(TIM2,	TIM_IT_Update)){
		// thuc thi ham ngat
			count++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);// co nay no xoa thu cong cho minh nhung ma nen xoa thu cong de cho chac chan rang la da xoa
		}
}

// ung dung 
int main(){
			RCC_Config();
			GPIO_Config();
			TIM_Config();	
			NVIC_Config();
			while(1){
					
				
					delay_ms(1000); // cu sau  giay thi cong len 1 gia tri
				
						cnt++;
	}

}