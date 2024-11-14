#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Device:StdPeriph Drivers:SPI
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_dma.h"              // Device:StdPeriph Drivers:DMA

#define SPI1_NSS     GPIO_Pin_4
#define SPI1_SCK 		GPIO_Pin_5
#define SPI1_MISO 		GPIO_Pin_6
#define SPI1_MOSI 		GPIO_Pin_7
#define SPI1_GPIO GPIOA
uint8_t buffer[14];
void RCC_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_SPI1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

}
void GPIO_Config(){
		GPIO_InitTypeDef GPIO_InitStruct;
		
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Pin= SPI1_MISO| SPI1_NSS|SPI1_SCK|SPI1_MOSI;
		GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;

		GPIO_Init(SPI1_GPIO,&GPIO_InitStruct);
}

void SPI_Config(){
	
		SPI_InitTypeDef SPI_InitStruct;
		SPI_InitStruct.SPI_Mode=SPI_Mode_Slave;
		SPI_InitStruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_16;
		SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
		SPI_InitStruct.SPI_CPOL=SPI_CPOL_Low;
		SPI_InitStruct.SPI_CPHA=SPI_CPHA_1Edge;
		SPI_InitStruct.SPI_DataSize=SPI_DataSize_8b;
		SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_LSB;
		SPI_InitStruct.SPI_CRCPolynomial= 7;
		SPI_InitStruct.SPI_NSS=SPI_NSS_Soft;
		
		SPI_Init(SPI1,&SPI_InitStruct);
		SPI_Cmd(SPI1,ENABLE);
}
void DMA_Config(){
			DMA_InitTypeDef DMA_InitStruct;
	
			DMA_InitStruct.DMA_Mode=DMA_Mode_Normal;
			DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)& SPI1-> DR;
			DMA_InitStruct.DMA_DIR= DMA_DIR_PeripheralSRC;
			DMA_InitStruct.DMA_BufferSize=14;
			DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
			DMA_InitStruct.DMA_PeripheralDataSize= DMA_PeripheralDataSize_Byte;
			DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;
			DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
			DMA_InitStruct.DMA_MemoryBaseAddr= (uint32_t)buffer;
			DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
			DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
		
			DMA_Init(DMA1_Channel2, &DMA_InitStruct);
			DMA_Cmd(DMA1_Channel2, ENABLE);
			
			SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE);
}
uint32_t i=0;
int main(){
			RCC_Config();
			GPIO_Config();
			SPI_Config();
			DMA_Config();
			while(1){
			//		
				i++;
			
			
			
			}
}


