#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

#define TX_Pin   			GPIO_Pin_0
#define RX_Pin 				GPIO_Pin_1

#define UART_GPIO 		GPIOA

uint32_t bit_duration = 104 ;

void RCC_Config()
{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

}
void GPIO_Config()
{
			GPIO_InitTypeDef GPIO_InitStruct;
			
			GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
			GPIO_InitStruct.GPIO_Pin=RX_Pin;
			GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
			
			GPIO_Init(GPIOA,&GPIO_InitStruct);
			
			GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Pin=TX_Pin;
			GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
			
			GPIO_Init(GPIOA,&GPIO_InitStruct);
	
}  
void TIM_Config()
{
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_InitStruct.TIM_ClockDivision=TIM_CKD_DIV1; //72MHz
	TIM_InitStruct.TIM_Prescaler =72-1;
	TIM_InitStruct.TIM_Period= 0xFFFF;
	TIM_InitStruct.TIM_CounterMode= TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
	TIM_Cmd(TIM2, ENABLE);
	
}
void delay_us(uint32_t time)
{
	TIM_SetCounter(TIM2,0);
	while(TIM_GetCounter(TIM2)< time);
	
} 
void delay_s(uint32_t time)
{
	for (int i=0;i < time*1000;i++)
	{
		
		delay_us(1000); // delay 1ms
	}
}
void clock()
{
		delay_us (bit_duration);
}

void UARTSofware_Init()
{
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	GPIO_SetBits(UART_GPIO,TX_Pin);
}
void UARTSoftware_Transmit( char c)
{		
		GPIO_SetBits(UART_GPIO, TX_Pin);
		clock();
		
		// truyen cac bit du lieu 
		for (int i=0;i<8;i++)
		{
			if(c & (1<<i))
			{
			GPIO_SetBits(GPIOA,TX_Pin);
			
			}
			else
			{
				GPIO_ResetBits(GPIOA,TX_Pin);
				
			}
			clock();
		}  
		// stop bit
		GPIO_SetBits(GPIOA,TX_Pin);
		clock();
		
}
int main ()
{		
	
	UARTSofware_Init();
	while (1)
	{
		UARTSoftware_Transmit('a');
		delay_s(1);
		UARTSoftware_Transmit('\n');
		delay_s(1);
	}
	
}
	