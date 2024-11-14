#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Device:StdPeriph Drivers:SPI

#define SPI1_NSS     GPIO_Pin_4
#define SPI1_SCK 		GPIO_Pin_5
#define SPI1_MISO 		GPIO_Pin_6
#define SPI1_MOSI 		GPIO_Pin_7

#define SPI1_GPIO GPIOA
uint8_t buffer[7]={1,3,4,7,2,4,5};

void RCC_Config(){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1| RCC_APB2Periph_AFIO, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
}
void Delay1Ms(void){
		TIM_SetCounter(TIM2, 0);
		while (TIM_GetCounter(TIM2)<1000){
		}
}


void delay_us(uint32_t delay)
{		
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2)< delay){
	}
}

void Delay_Ms(uint32_t u32DelayInMs)
		{
			while(u32DelayInMs){
				Delay1Ms();
				--u32DelayInMs;
			}
		}
void TIM_Config(){
	
			TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
			
			TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
			TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
			TIM_TimeBaseInitStruct.TIM_Period=0xFFFF;
			
	
			TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
			TIM_Cmd(TIM2,ENABLE);
	

}


void GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStruct;
		
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Mode= SPI1_NSS| SPI1_MISO| SPI1_SCK | SPI1_MOSI;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;

		GPIO_Init(SPI1_GPIO,&GPIO_InitStruct);
}
void SPI_Config(){
		SPI_InitTypeDef SPI_InitStruct;
		
		SPI_InitStruct.SPI_Mode= SPI_Mode_Master;
		SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
		SPI_InitStruct.SPI_BaudRatePrescaler= SPI_BaudRatePrescaler_16;
		SPI_InitStruct.SPI_CPOL=SPI_CPOL_Low;
		SPI_InitStruct.SPI_CPHA=SPI_CPHA_1Edge;
		SPI_InitStruct.SPI_DataSize= SPI_DataSize_8b;
		SPI_InitStruct.SPI_FirstBit= SPI_FirstBit_LSB;
		SPI_InitStruct.SPI_CRCPolynomial=7;
		SPI_InitStruct.SPI_NSS= SPI_NSS_Soft;
	
		SPI_Init(SPI1, &SPI_InitStruct);
		
		SPI_Cmd(SPI1,ENABLE);
}
int main(){
		RCC_Config();
		GPIO_Config();
		SPI_Config();
		TIM_Config();
		
		while(1){
			for(int i=0;i<7;i++){
				SPI_I2S_SendData(SPI1,buffer[i]);
				while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
			}
			Delay_Ms(300);
		}
}