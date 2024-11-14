#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

#define I2C_SCL GPIO_Pin_6
#define I2C_SDA GPIO_Pin_7

#define I2C_GPIO GPIOB
typedef enum{
	NOT_OK=0,
	OK=1
}	status;
typedef enum{
	NOT_ACK=0,
	ACK=1
} ACK_Bit;


void delay1MS(void)
{	
	TIM_SetCounter(TIM2,0);
	while(TIM_GetCounter(TIM2)<1000){
	}
}

void delay_us(uint32_t timedelay){
		TIM_SetCounter(TIM2,0);
		while(TIM_GetCounter(TIM2)<timedelay){
		}
}



void Delay_Ms(uint32_t u32DelayInMs){
	while(u32DelayInMs){
		delay1MS();
		--u32DelayInMs;
	}
}
void RCC_Config(){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
}
void TIM_Config(){
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
		TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInitStructure.TIM_Period= 0xFFFF;
		TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;
	
			TIM_TimeBaseInit(TIM2, & TIM_TimeBaseInitStructure);
		TIM_Cmd(TIM2,ENABLE);
}
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin= I2C_SDA|I2C_SCL;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;

	GPIO_Init(I2C_GPIO,&GPIO_InitStructure);
	
}
#define WRITE_SDA_0 GPIO_ResetBits(I2C_GPIO, I2C_SDA);
#define WRITE_SDA_1 GPIO_SetBits(I2C_GPIO,I2C_SDA);
#define WRITE_SCL_0 GPIO_ResetBits(I2C_GPIO,I2C_SCL);
#define WRITE_SCL_1 GPIO_SetBits(I2C_GPIO,I2C_SCL);
#define READ_SDA_VAL GPIO_ReadInputDataBit(I2C_GPIO,I2C_SDA)

void I2C_Comfig(){
	WRITE_SDA_1;
	delay_us(1);
	WRITE_SCL_1;
	delay_us(1);
	}

	
	
	void I2C_Start(){
	WRITE_SCL_1;			
	delay_us(3);
	WRITE_SCL_1;
	delay_us(3);
	WRITE_SDA_0;
	delay_us(3);
	WRITE_SCL_0;
			delay_us(3);
	
	}
void I2C_Stop(){
				WRITE_SDA_0;
				delay_us(3);
				WRITE_SCL_0;
				delay_us(3);
				WRITE_SCL_1; // CAI NAY TRONG KIA KHONG CO NHE 
				delay_us(3);
				WRITE_SDA_1;
				delay_us(3);

}
status I2C_Write(uint8_t pData){
				uint8_t i;
				status stRet;
			 for (int i=0;i<8;i++){
				if (pData & 0x80){
						WRITE_SDA_1;
				}
				else {
					WRITE_SDA_0;
				}
				delay_us(3);
				WRITE_SCL_1;
				delay_us(5);
				WRITE_SCL_0;
				delay_us(2);
				pData <<=1;
				

}
		WRITE_SDA_1;	
		delay_us(3);
		WRITE_SCL_1;
		delay_us(3);
		

		if(READ_SDA_VAL){
				stRet= NOT_OK;
		}
		else
		{
			stRet=OK;
		}
			delay_us(2);
			WRITE_SCL_0;
			delay_us(5);
		return stRet;
}
uint8_t I2C_Read(ACK_Bit _ACK){
		uint8_t i;
		uint8_t u8Ret= 0x00;
	
		WRITE_SDA_1;
		delay_us(3);
		
			for(i=0;i<8;++i){
			u8Ret <<=1;
			WRITE_SCL_1;
			delay_us(3);
			if(READ_SDA_VAL){
				u8Ret |=0x01;
			}
			delay_us(2);
			WRITE_SCL_0;
			delay_us(5);
			
			
			
			}
			if (_ACK){
			WRITE_SDA_0;
		
			}
			else
			{
				WRITE_SDA_1;
			}
			delay_us(3);
			WRITE_SCL_1;
			delay_us(5);
			WRITE_SCL_0;
			delay_us(5);
			
			return u8Ret;
}
status EPROM_Read(uint16_t MemAddr, uint8_t SlaveAddress, uint8_t NumByte,uint8_t *pData)
{			uint8_t i;
	
	
			I2C_Start();
			if(I2C_Write(SlaveAddress<< 1 )== NOT_OK){
				I2C_Stop();
				return NOT_OK;
			}
			
			if (I2C_Write(MemAddr>>8)==NOT_OK){
			I2C_Stop();
				return NOT_OK;
				
			}
			
			if(I2C_Write(MemAddr)==NOT_OK){
			I2C_Stop();
			return NOT_OK;
			}
			
			I2C_Start();
		
			if(I2C_Write((SlaveAddress<<1)|1)== NOT_OK) {
			I2C_Stop();
				return NOT_OK;
			}
			for(i=0;i<NumByte-1 ;++i){
			pData[i]= I2C_Read(ACK);
			
			}
			pData[i]=I2C_Read(NOT_ACK);
			I2C_Stop();
			return OK;
		}
status EPROM_Write(uint16_t MemAddr, uint8_t SlaveAddress, uint8_t NumByte,uint8_t *pData)
		{
			uint8_t i;
			for(i =0;i<NumByte;++i){
				I2C_Start();
				if(I2C_Write(SlaveAddress<<1) == NOT_OK){
					
				I2C_Stop();
				return NOT_OK;
			}
				
			
			if (I2C_Write((MemAddr+1)>>8)== NOT_OK){
				I2C_Stop();
				return NOT_OK;
				
			}
			
			if(I2C_Write((pData)[i])==NOT_OK){
				I2C_Stop();
				return NOT_OK;
		}
			I2C_Stop();
			Delay_Ms(10);
	}
			return 1;
}
	uint8_t Data[10]={0x03,0x05,0x10, 0x77, 0xd9, 0x6f, 0x50, 0x00, 0x00, 0xf0};
	uint8_t Rev[10]={0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00,0x00, 0x00, 0x00};

	
	
	int main(){
		RCC_Config();
		TIM_Config();
		GPIO_Config();
		I2C_Comfig();
		
		if(EPROM_Write(0x0045,0x57,10, Data)== NOT_OK){
		while(1){
		}
		}
		
		
		while(1){
		if(EPROM_Read(0x0045,0x57,10, Rev)== NOT_OK){
			while(1){
			}
		}
		}
	}
			
			
