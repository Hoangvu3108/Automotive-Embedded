#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_spi.h"              // Device:StdPeriph Drivers:SPI
 
 void delay(uint32_t delaytime){
	 for  (int i=0; i<delaytime; i++);
 }
 
 void RCC_Config(void){
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); 
 }
 
 void GPIO_Config(void){
   GPIO_InitTypeDef GPIO_InitStruct;
	 
	 GPIO_InitStruct.GPIO_Pin= GPIO_Pin_13|GPIO_Pin_5|     GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8;
	 GPIO_InitStruct.GPIO_Mode= GPIO_Mode_Out_PP;
	 GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	 
	 GPIO_Init(GPIOC,&GPIO_InitStruct);
	
 }
//void chaseLed(uint8_t loop){
//	uint16_t Ledval ;
//	for(int j=0; j<loop; j++ ){
//		Ledval = 0x0010;
//		for(int i =0; i<4; i++)
//		{
//			Ledval = Ledval<<1;
//			GPIO_Write(GPIOC, Ledval);
//			delay(10000000);
//		}
//	}
//}


int main(){
	RCC_Config();
	GPIO_Config();
	while(1){
	GPIO_SetBits(GPIOC, GPIO_Pin_13); // Ghi 1 ra PC13
	delay(10000000);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);// Ghi 0 ra PC13
	delay(10000000);
}
// while (1){
// chaseLed(3);
// }
}

