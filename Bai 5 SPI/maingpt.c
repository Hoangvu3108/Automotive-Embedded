#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_spi.h"              // Device:StdPeriph Drivers:SPI

#define SPI1_NSS 	GPIO_Pin_4
#define SPI1_SCK	GPIO_Pin_5
#define SPI1_MISO 	GPIO_Pin_6
#define SPI1_MOSI 	GPIO_Pin_7
#define SPI1_GPIO 	GPIOA

void RCC_Config(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
}

void GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate Function Push-Pull for SPI pins
    GPIO_InitStructure.GPIO_Pin = SPI1_SCK | SPI1_MISO | SPI1_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Output Push-Pull for NSS pin
    GPIO_InitStructure.GPIO_Pin = SPI1_NSS;
    GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);
}

void SPI_Config(){
    SPI_InitTypeDef SPI_InitStruct;

    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft; // Software management for NSS
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    
    SPI_Init(SPI1, &SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);
}

void SPI_Send1Byte(uint8_t data){
    GPIO_ResetBits(SPI1_GPIO, SPI1_NSS); // Pull NSS low
    
    SPI_I2S_SendData(SPI1, data); // Send data
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); // Wait until transmission is complete
    
    GPIO_SetBits(SPI1_GPIO, SPI1_NSS); // Pull NSS high
}
void Delay(uint32_t time){
    for(uint32_t i = 0; i < time*10; i++);
}
int main(void){
    uint8_t array[] = {7, 8, 4, 2};
    
    RCC_Config();
    GPIO_Config();
    SPI_Config();
    
    while(1){
        for(int i = 0; i < sizeof(array); i++){
            SPI_Send1Byte(array[i]); // Send each byte
            Delay(7200000); // Delay of approximately 1 second (assuming 72 MHz clock)
        }
        Delay(7200000); // Additional delay before restarting the loop
    }
}