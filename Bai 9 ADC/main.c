#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Device:StdPeriph Drivers:ADC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "delay.h"
#include "kalman.h"

void Delay1Ms(void)
{
	TIM_SetCounter(TIM2,0);
	while (TIM_GetCounter(TIM2)<1000){
	}
}

void delay_us(uint32_t delay)
{	
				TIM_SetCounter(TIM2, 0);
				while(TIM_GetCounter(TIM2)< delay){
				}
}
	
void Delay_Ms(uint32_t u32DelayInMs)

{
	while(u32DelayInMs){
			Delay1Ms();
		--u32DelayInMs;
	}
}
	
void RCC_Config()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
}

void GPIO_Config(){
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AIN;
		GPIO_InitStruct.GPIO_Pin= GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
		
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void TIM_Config(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	
	TIM_TimeBaseInitStructure.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=20000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM2,ENABLE);
}
void ADC_Config(){
	ADC_InitTypeDef ADC_InitStruct;
	
	
	
		ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStruct.ADC_NbrOfChannel=1;
		ADC_InitStruct.ADC_ScanConvMode= DISABLE;
		ADC_InitStruct.ADC_ExternalTrigConv= ADC_ExternalTrigConv_None;
		ADC_InitStruct.ADC_ContinuousConvMode=ENABLE;
		ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
		
		ADC_Init(ADC1,&ADC_InitStruct);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1,ADC_SampleTime_55Cycles5);
	// cai hinh chp pa0 nen la chon adc channel 0 	
	// ham tren nay cho phep cai dat tham so cho mot kenh
		ADC_Cmd(ADC1,ENABLE);
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

uint16_t sum=0, val=0;
int main(){
	RCC_Config();
	GPIO_Config();
	ADC_Config();
	TIM_Config();
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		while(1){
				for(int i=0;i<10;i++){
				val= ADC_GetConversionValue(ADC1);
					delay_us(100);
					sum+=val;
				
				}
				sum=sum/10;
				Delay_Ms(100);
				sum=0;
		
	//	}
//	while(1){

//			val = ADC_GetConversionValue(ADC1);
//			
//			valupdate = (float)updateEstimate((float)val);
//		Delay_Ms(100);
//	}

//	

			}
}
		