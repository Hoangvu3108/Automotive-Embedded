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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1,ENABLE);
	
}

void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStucture;
	
	GPIO_InitStucture.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_InitStucture.GPIO_Pin= SPI1_SCK|SPI1_MISO|SPI1_MOSI|SPI1_NSS;
	GPIO_InitStucture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(SPI1_GPIO,& GPIO_InitStucture);
}
// toan bo cau hinh cho SPI
void SPI_Config(){
	SPI_InitTypeDef SPI_InitStruct;
	
	SPI_InitStruct.SPI_Mode=SPI_Mode_Master;
 
	SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;

	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStruct.SPI_CPOL= SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA= SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_DataSize= SPI_DataSize_8b;
	SPI_InitStruct.SPI_FirstBit= SPI_FirstBit_MSB; // cai nay là truyen tu trai sang phai
	SPI_InitStruct.SPI_NSS= SPI_NSS_Hard;
	
	SPI_Init(SPI1,&SPI_InitStruct );
	SPI_Cmd(SPI1, ENABLE);
}
void SPI_Send1Byte(uint8_t data){
		GPIO_WriteBit(SPI1_GPIO,SPI1_NSS,Bit_RESET);// Keo cua duong ss xuong 
	
		SPI_I2S_SendData(SPI1, data);// sau do send data
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==0);// cho xem no send xong 
		GPIO_WriteBit(SPI1_GPIO,SPI1_NSS,Bit_SET); // sau khi truyen xong thi no se keo chan SS len lai
		
//}
//uint8_t SPI_Receive1Byte(void){
//    uint8_t temp;
//    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)==1);
//    temp = (uint8_t)SPI_I2S_ReceiveData(SPI1);
//    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==0);
//    return temp;
//}
// TESt truyen nhan 
int main(){
	while(1){
//		while(GPIO_ReadInputDataBit(SPI1_GPIO, SPI1_NSS));
//        if(GPIO_ReadInputDataBit(SPI1_GPIO, SPI1_NSS)==0){
//            for(int i = 0; i<8; i++){
//            data[i] = SPI_Receive1Byte();
//           }
//       }

	}
}