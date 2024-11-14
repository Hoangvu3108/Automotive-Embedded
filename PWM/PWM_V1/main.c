//#include "stm32f10x.h"                  // Device header
//#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
//#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC

//void RCC_Config()
//{	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//}
//void GPIO_Config()
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
//	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
//}	

//// chu ki xung tao ra voi chu ky la 20ms(50Hz)
//void TIM_Config(){
//		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV2;
//		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
//		TIM_TimeBaseInitStruct.TIM_Period=0xFFF;
//		TIM_TimeBaseInitStruct.TIM_Prescaler=3599;
//		
//	
//		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
//		TIM_Cmd(TIM2,ENABLE);
//	
//		TIM_OCInitTypeDef TIM_OCInitStruct;
//		TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
//		TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
//		TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High; // cuc tinh mong muon no o muc cao
//		TIM_OC1Init(TIM2,&TIM_OCInitStruct);
//		TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
//		TIM_Cmd(TIM2,ENABLE);// CAU hinh timer o che do nap lai
//}
//main(){
//	
//	while(1)
//	{
//	
//	
//	}




//}

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

void RCC_Config()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;       // Alternate function push-pull
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;             // PA0 (TIM2_CH1)
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void TIM_Config()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    // TIM2 configuration
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 19999;        // 20 ms period (50 Hz)
    TIM_TimeBaseInitStruct.TIM_Prescaler = 71;        // 72 MHz / (71+1) = 1 MHz -> 1 us per tick

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // PWM1 Mode configuration: Channel1
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 1500;                // 1.5 ms pulse width (neutral position)
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM2, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // Start TIM2
    TIM_Cmd(TIM2, ENABLE);
}

int main(void)
{
    RCC_Config();
    GPIO_Config();
    TIM_Config();

    while(1)
    {
        // Code to change the servo position can be placed here
        // For example:
        // TIM_SetCompare1(TIM2, 1000); // 1 ms pulse width (0°)
						TIM_SetCompare1(TIM2, 1500); // 1.5 ms pulse width (90°)
        // TIM_SetCompare1(TIM2, 2000); // 2 ms pulse width (180°)
    }
}
