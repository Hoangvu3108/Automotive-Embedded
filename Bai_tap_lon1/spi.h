#ifndef __SPI_H
#define __SPI_H



#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC

#define MFRC522_CS_GPIO           				GPIOB
#define MFRC522_CS_PIN            				GPIO_Pin_12
#define MFRC522_CS_RCC            				RCC_APB2Periph_GPIOB



#define MFRC522_RST_GPIO         					GPIOB
#define MFRC522_RST_PIN          					GPIO_Pin_11
#define MFRC522_RST_RCC          					GPIO_APB2Periph_GPIOB

#define MFRC522_SPI          							SPI2   				// SPIx
#define MFRC522_SPI_GPIO 									GPIOB
#define MFRC522_SCK_GPIO 									GPIO_Pin_13
#define MFRC522_MISO_GPIO 								GPIO_Pin_14
#define MFRC522_MOSI_GPIO 								GPIO_Pin_15
#define MFRC522_SPI_GPIO_RCC 							RCC_APB2Periph_GPIOB
#define MFRC522_SPI_RCC 									RCC_APB1Periph_SPI2
/////////////////////////////////////////////////////////////////////////////////
//set the pin SD CARD

#define MICROSD_SPI 											SPI1
#define MICROSD_SPI_GPIO 									GPIOA
#define MICROSD_CS_PIN 										GPIO_Pin_4
#define MICROSD_SCK_PIN 									GPIO_Pin_5
#define MICROSD_MISO_PIN 									GPIO_Pin_6
#define MICROSD_MOSI_PIN 									GPIO_Pin_7
#define MICROSD_SPI_GPIO_RCC							RCC_APB2Periph_GPIOA
#define MICROSD_SPI_RCC										RCC_APB2Periph_SPI1
/* Exported functions --------------------------------------------------*/


void SPIRC552_Config(void);
void SPISD_Config(void);
uint8_t My_SPI_Exchange(uint8_t u8Data);
#endif /* __SPI*/