#include "spi.h"
 #include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_spi.h"              // Device:StdPeriph Drivers:SPI

void SPIRC552_Config(){
		RCC_APB2PeriphClockCmd(MFRC522_SPI_GPIO_RCC | MFRC522_RST_RCC | MFRC522_CS_RCC, ENABLE);
		RCC_APB1PeriphClockCmd(MFRC522_SPI_RCC, ENABLE);
		/* cau hinh GPIO_SPI RCC 522*/
		GPIO_InitTypeDef GPIO_InitStruct;
	
		// Cau hinh chan sckk, mosi, miso
		GPIO_InitStruct.GPIO_Pin= MFRC522_SCK_GPIO | MFRC522_MISO_GPIO |MFRC522_MOSI_GPIO;
		GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
		 
		GPIO_Init(MFRC522_SPI_GPIO, &GPIO_InitStruct);
		// cau hinh chan ss(cs) lam chan output 
		GPIO_InitStruct.GPIO_Pin= MFRC522_CS_PIN;
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(MFRC522_CS_GPIO, &GPIO_InitStruct);
		
		// dat chan nss (cs) len muc cao mac dinh
	
		GPIO_SetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
		
		// cau hinh chan reset lam chan output 
		GPIO_InitStruct.GPIO_Pin = MFRC522_RST_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(MFRC522_RST_GPIO, &GPIO_InitStruct);
		
		GPIO_SetBits(MFRC522_RST_GPIO, MFRC522_RST_PIN);
	
		SPI_InitTypeDef SPI_InitStruct;
		SPI_StructInit(&SPI_InitStruct);
		SPI_InitStruct.SPI_Mode=SPI_Mode_Master;
		SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
		SPI_InitStruct.SPI_DataSize=SPI_DataSize_8b;
		SPI_InitStruct.SPI_CPOL=SPI_CPOL_Low;
		SPI_InitStruct.SPI_CPHA=SPI_CPHA_1Edge;
		SPI_InitStruct.SPI_NSS=SPI_NSS_Soft;
		SPI_InitStruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_32;// chua biet cai nay la gi doc lai tat ca spi di 
		SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_MSB;
			
		// KHOI TAO SPI
			SPI_Init(MFRC522_SPI,&SPI_InitStruct);
			SPI_Cmd(MFRC522_SPI, ENABLE);
		}		
void SPISD_Config(){
	
		 /* cap xung clock cho GPIO, SPIX SD CARD*/
		RCC_APB2PeriphClockCmd(MICROSD_SPI_GPIO_RCC, ENABLE);
		RCC_APB2PeriphClockCmd(MICROSD_SPI_RCC,ENABLE);
		
		/* Cau hinh GPIO_SPIx SDCard*/
		
		GPIO_InitTypeDef 	GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode= MICROSD_SCK_PIN| MICROSD_MISO_PIN | MICROSD_MOSI_PIN ;
		GPIO_InitStruct.GPIO_Pin= GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init (MICROSD_SPI_GPIO, & GPIO_InitStruct );
	
		GPIO_SetBits(MICROSD_SPI_GPIO, MICROSD_CS_PIN);
		
		/* Cau hinh SPIx */
		
		SPI_InitTypeDef SPI_InitStruct;
		SPI_StructInit(&SPI_InitStruct);
		SPI_InitStruct.SPI_Mode= SPI_Mode_Master;
		SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
		SPI_InitStruct.SPI_DataSize= SPI_DataSize_8b;
		SPI_InitStruct.SPI_CPOL=SPI_CPOL_Low;
		SPI_InitStruct.SPI_CPHA= SPI_CPHA_1Edge;
		SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
		SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_MSB;
		
		// Khoi tao SPI
		SPI_Init(MICROSD_SPI, &SPI_InitStruct);
		SPI_Cmd(MICROSD_SPI,ENABLE);
}
uint8_t My_SPI_Exchange(uint8_t u8Data)
{		SPI_I2S_SendData(MICROSD_SPI, u8Data);
		
		while(	(MICROSD_SPI,SPI_I2S_FLAG_BSY)== SET){
		
		
		
		}
		return SPI_I2S_ReceiveData(MICROSD_SPI);


}
 
	

		
