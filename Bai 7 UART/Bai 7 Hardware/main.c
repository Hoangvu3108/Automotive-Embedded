#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_usart.h"            // Device:StdPeriph Drivers:USART
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10
#define UART_GPIO GPIOA 
#define BRateTime 105

void RCC_Config(){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
// cau hinh cho UART
void GPIO_Config(){
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;  
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);

}
// CAU HINH UART
void USART_Config(){
		USART_InitTypeDef USART_InitStruct;
	
	
		USART_InitStruct.USART_BaudRate=9600; // neu su dung 2 con vi dieu khien thi phai cap baudrate cho 2 con giong nhau
		USART_InitStruct.USART_Mode=USART_Mode_Rx| USART_Mode_Tx;
		USART_InitStruct.USART_WordLength=USART_WordLength_8b;						// do dai 1 chuoi co 8 or 9 bit
		USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	// che do mo rong cua urart nhung o day khong dung 
		
		USART_InitStruct.USART_StopBits=USART_StopBits_1;// stop bit cung phai dong bo giong nhau															// neu co thi se co RTS va CTS
		USART_InitStruct.USART_Parity= USART_Parity_No;
	// KHONG SU DUNG PARTITY
	
		USART_Init(USART1, &USART_InitStruct);
		USART_Cmd(USART1,ENABLE);
}
// TRUYEN NHAN 
char USART_ReceiveChar(USART_TypeDef *USARTx){
	USARTx-> DR=0x00;
	char tmp=0x00;
	 tmp= USART_ReceiveData(USARTx);// tao bien dem
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)== RESET);
	
	return tmp;
	 // quan trinh nhan
} 

void USART_SendChar(USART_TypeDef *USARTx, char data){
	USARTx-> DR=0x00;
	USART_SendData(USARTx, data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
	
}
// co TXE co truyen set len 1  neu qua trinh truyen hoan tat
// co truyen gui di tung byte data sau do doi co TXE truyen bat len 
// nha doc data tu bo usart cho co rxne bat len
int main(){
		RCC_Config();
		GPIO_Config();
		USART_Config();
		USART_SendChar(USART1,'h');
		while(1){
		
		
		
		}




}

	