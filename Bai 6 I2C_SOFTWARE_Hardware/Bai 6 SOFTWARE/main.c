#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#define I2C_SCL GPIO_Pin_6
#define I2C_SDA GPIO_Pin_7
#define I2C_GPIO GPIOB

#define WRITE_SDA_0 GPIO_ResetBits(I2C_GPIO, I2C_SDA)
#define WRITE_SDA_1 GPIO_SetBits(I2C_GPIO, I2C_SDA)
#define WRITE_SCL_0 GPIO_ResetBits(I2C_GPIO, I2C_SCL)
#define WRITE_SCL_1 GPIO_SetBits(I2C_GPIO, I2C_SCL)
#define READ_SDA_VAL GPIO_ReadInputDataBit(I2C_GPIO, I2C_SDA)


typedef enum {
	NOT_OK,OK
}status;
	
void delay_ms(uint16_t timedelay)
{		TIM_SetCounter(TIM2,0);
		while(TIM_GetCounter(TIM2)<timedelay*10){}
}
void RCC_Config(){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		
}
void GPIO_Config()
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_OD; 
	GPIO_InitStruct.GPIO_Pin= I2C_SDA|I2C_SCL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(I2C_GPIO,&GPIO_InitStruct);
}
void I2C_Config(){
	WRITE_SDA_1;
	delay_ms(1)
	WRITE_SCL_1;
	delay_ms(1);
}
void I2C_Start(){
	WRITE_SCL_1;
	delay_ms(3);
	WRITE_SDA_1;
	delay_ms(3);
	WRITE_SDA_0;
	delay_ms(3);
	WRITE_SCL_0;
	delay_ms(3);

}

void I2C_Stop(){
	WRITE_SDA_0;
	delay_ms(3);
	WRITE_SCL_0;
	delay_ms(3);
	WRITE_SCL_1;
	delay_ms(3);
	WRITE_SDA_1;
	delay_ms(3);

}
status I2C_WRITE(uint8_t u8data){
		uint8_t i;
		status stRet;// tap ra cai bien de chua gia tri
		for (int i=0;i<8;i++){ // lan luot truyen 8 bit data di 
		if (u8data & 0x80){
					WRITE_SDA_1; // do xung nho xiu nen la minh phai tu viet ra chu khong nen la dua vao clock
		}
			else{
				WRITE_SDA_0;
					}
			delay_ms(3);  // day la delay o muc khong truoc 	
			WRITE_SCL_1;	// cai nay la keo chan len o muc 1
			delay_ms(5);		// delay 1 chut
			WRITE_SCL_0;		// roi lai keo xuong
			delay_ms(2);		//  
			u8data <<=1;
		}
				WRITE_SDA_1; // vi neu khong dung thi cung tu dong up len 1 
				delay_ms(3);
				WRITE_SCL_1;
				delay_ms(3);
		// cho xung thu 9 
		if(READ_SDA_VAL){
			stRet = NOT_OK;
		}	
				else{
				stRet= OK;
				}
				delay_ms(2);
				WRITE_SCL_0;
				delay_ms(5);
				
				return stRet;
}

int main(){
		while (1){
		return 0;
		}
}