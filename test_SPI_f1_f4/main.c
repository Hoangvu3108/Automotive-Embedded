#include "stm32f10x.h"

void SPI_Master_Init(void) {
    // Enable GPIO and SPI clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    // Configure SPI1 SCK, MISO, MOSI (PA5, PA6, PA7)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure SPI1 NSS (PA4)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_4); // NSS high

    // Configure SPI1 as Master
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE); // Enable SPI1
}

uint8_t SPI_Master_Transmit(uint8_t data) {
    GPIO_ResetBits(GPIOA, GPIO_Pin_4); // NSS low

    // Send data
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    GPIO_SetBits(GPIOA, GPIO_Pin_4); // NSS high

    // Return received data
    return SPI_I2S_ReceiveData(SPI1);
}
#include "stm32f10x.h"

void SPI_Master_Init(void);
uint8_t SPI_Master_Transmit(uint8_t data);

int main(void) {
    // Initialize SPI
    SPI_Master_Init();

    uint8_t data_to_send = 0x55; // D? li?u ví d?
    uint8_t received_data;

    while (1) {
        received_data = SPI_Master_Transmit(data_to_send);
        // X? lý d? li?u nh?n du?c t? Slave ? dây...
    }
}

