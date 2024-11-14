#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
// Click EXTI de cau hinh cho ngat ngoai
  // neu su dung ngat falling thi nen su dun input pull up 
void RCC_Config()
{		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			
}
void GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
}
// cau hinh xong GPIO roi CAU hinh exti 

// chan pin source 0 xac dinh chan PA0 la chan ngo vao ngat


// cac tin hieu ngat ngoai chia thanh duong ngat ngoai nen la cac PA0-PG0 thanh EXTI0
void EXTI_Config(){
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
				EXTI_InitTypeDef EXTI_InitStruct;
				
				EXTI_InitStruct.EXTI_Line=EXTI_Line0;
				EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
				EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
				EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	
	
				EXTI_Init(&EXTI_InitStruct);
}

// ngat do uu tin se co mot khoi NVIC chiu trach nhiem quan li 
void NVIC_Config()
	{			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
				
				NVIC_InitTypeDef NVIC_InitStruct;
		
		
				NVIC_InitStruct.NVIC_IRQChannel= EXTI0_IRQn;
				NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1 ;// do uu tien chinh	
				NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;					// do uu tien phu
				NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
				
				NVIC_Init(&NVIC_InitStruct);
}
	
uint16_t test=0;
uint16_t cnt=0;
// tiep theo la ham phuc ngat ham nay se la se phuc vu sau khi ngat xay ra
void EXTI0_IRQHandler()
	// phai dat dung cai ten ham nay de thuc hien ham ngat
{			
			// ham hetITstatus kiem tra co ngat
			// ham 
			if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
			{
				// thuc thi cai nay
				
				test++;
			}
				EXTI_ClearITPendingBit(EXTI_Line0);

}


int main(){
			RCC_Config();
			GPIO_Config(); 
			EXTI_Config();
			NVIC_Config();	
		while(1){
 		cnt++;
		
		}
}
