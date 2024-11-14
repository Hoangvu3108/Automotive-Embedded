#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Device:StdPeriph Drivers:SPI

#define SPI2_NSS    GPIO_Pin_12
#define SPI2_SCK    GPIO_Pin_13
#define SPI2_MISO   GPIO_Pin_14
#define SPI2_MOSI   GPIO_Pin_15
#define SPI2_GPIO   GPIOB

void RCC_Config(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB1Periph_SPI2, ENABLE);
}

void GPIO_Config(){
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = SPI2_SCK | SPI2_MISO | SPI2_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input pull-up for NSS pin
    GPIO_InitStructure.GPIO_Pin = SPI2_NSS;
    GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);
}

void SPI_Config(){
    SPI_InitTypeDef SPI_InitStruct;

    SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Hard; // Hardware management for NSS
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    
    SPI_Init(SPI2, &SPI_InitStruct);
    SPI_Cmd(SPI2, ENABLE);
}

uint8_t SPI_Receive1Byte(void){
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); // Wait until data is received
    return SPI_I2S_ReceiveData(SPI2); // Return received data
}

int main(void){
    uint8_t array[4];
    uint8_t i = 0;

    RCC_Config();
    GPIO_Config();
    SPI_Config();
    
    while(1){
        if(i < 4){
            array[i] = SPI_Receive1Byte(); // Receive data into array
            i++;
        }
        // The received data can be monitored using a debugger's watch window
    }
}