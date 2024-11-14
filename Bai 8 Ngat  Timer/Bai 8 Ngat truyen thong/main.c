#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_usart.h"            // Device:StdPeriph Drivers:USART

// Click EXTI de cau hinh cho ngat ngoai
  // neu su dung ngat falling thi nen su dun input pull up 
void RCC_Config()
{		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}
void GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
}



void UART_Config(){
		USART_InitTypeDef UART_InitStruct;
		UART_InitStruct.USART_Mode= USART_Mode_Rx| USART_Mode_Tx;
		UART_InitStruct.USART_BaudRate= 9600;
		UART_InitStruct.USART_HardwareFlowControl= USART_WordLength_8b;
		UART_InitStruct.USART_StopBits= USART_StopBits_1;
		UART_InitStruct.USART_Parity= USART_Parity_No;
		USART_Init(USART1, &UART_InitStruct);
		
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	
	
		USART_Cmd(USART1, ENABLE);
}
// cau hinh xong GPIO roi CAU hinh exti 

// chan pin source 0 xac dinh chan PA0 la chan ngo vao ngat  


// cac tin hieu ngat ngoai chia thanh duong ngat ngoai nen la cac PA0-PG0 thanh EXTI0
 
// ngat do uu tin se co mot khoi NVIC chiu trach nhiem quan li 
void NVIC_Config()
	{			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
				
				NVIC_InitTypeDef NVIC_InitStruct;
		
		
				NVIC_InitStruct.NVIC_IRQChannel= USART1_IRQn;
				NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1 ;// do uu tien chinh	
				NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;					// do uu tien phu
				NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
				
				NVIC_Init(&NVIC_InitStruct);
}
	
// HAM PHUC NGAT CHO UART
void USART1_IRQHandler(){
		if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
		// thuc hien lenh ngat trong nay
		
		
		
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}
int main(){
			RCC_Config();
			GPIO_Config(); 
			UART_Config();
			NVIC_Config();	
		while(1){
 		cnt++;
		
		}
}
