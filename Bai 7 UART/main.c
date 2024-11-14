#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "delay.h"


#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10
#define UART_GPIO GPIOA
#define BRateTime 104 // thuc te la 104.17us 



void RCC_Config(){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(){
		GPIO_InitTypeDef GPIO_InitStruct;
		
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; // rx DE NHAN TIN HIEU TU THANG KHAC SE LA INPUT FLOATING
		GPIO_InitStruct.GPIO_Pin=RX_Pin;
		GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin=TX_Pin;           // CHAN NAY LA OUTPUT VA MODE CUA NO LA OUTPUT
		GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		

 // tin hieu stop duoc tao tuong ung so bit stop  
}
void UART_Transmit(uint8_t DataValue)
{	
		GPIO_WriteBit(UART_GPIO,TX_Pin,Bit_RESET);
		delay_us(BRateTime);
		
		for(unsigned char i=0;i<8;i++)
		{ 
			if(((DataValue)&0x01)==0x1) {
						GPIO_WriteBit(UART_GPIO,TX_Pin,Bit_SET);
						}
			else{
				GPIO_WriteBit(UART_GPIO,TX_Pin,Bit_RESET);
			}
				delay_us(BRateTime);
				DataValue= DataValue >>1;
		
		
		}
	
	
}
unsigned char UART_Receive(){
		unsigned char DataValue=0;
		while (GPIO_ReadInputDataBit(UART_GPIO, RX_Pin)==1);
		delay_us(BRateTime);
		delay_us(BRateTime/2);
		for (unsigned char i=0; i<8;i++){
		if (GPIO_ReadInputDataBit(UART_GPIO, RX_Pin)==1){
			DataValue |=(1<<i);
		}
				delay_us(BRateTime); // delay den nua bit stop
			}
		// kiem tra bit stop da xuat hien hay chua 
			// neu 1 la roi -> delay nua bit cuoi cung cua hoan thanh qua trinh nhan 
			// con 0 laf chua
		if (GPIO_ReadInputDataBit(UART_GPIO,RX_Pin)==1)
		{
			delay_us(BRateTime/2);
			return DataValue;  
		}
}
		
int main (){
	


}