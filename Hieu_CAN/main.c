#include "stm32f10x.h"                  // Device header
#include "stm32f10x_can.h"              // Device:StdPeriph Drivers:CAN
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "misc.h"                       // Device:StdPeriph Drivers:Framework
#include <string.h>
#include <stdlib.h>

#define SERVO_PIN GPIO_Pin_1 
#define MOTOR_SPEED_PIN GPIO_Pin_5
#define IN1_PIN GPIO_Pin_6
#define IN2_PIN GPIO_Pin_7


void RCC_Config()
{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_1 | GPIO_Pin_5; // Servo_pin | motor_speed_pin
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,& GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; // GPT la gpio_mode _IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;    // CAN_TX
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz; 
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;   // CAN_RX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, & GPIO_InitStruct);
	
	
}

void CAN_Config()
{
	CAN_InitTypeDef CAN_InitStruct;
	
	CAN_InitStruct.CAN_TTCM = DISABLE;
	CAN_InitStruct.CAN_ABOM =DISABLE;
	CAN_InitStruct.CAN_AWUM= DISABLE;
	CAN_InitStruct.CAN_NART= DISABLE;
	CAN_InitStruct.CAN_RFLM= DISABLE;
	CAN_InitStruct.CAN_TXFP= ENABLE;
	
	CAN_InitStruct.CAN_Mode= CAN_Mode_Normal;
	
	CAN_InitStruct.CAN_Prescaler= 4;
	/*  Cau hinh toc do CAN
				36MHz 
	fCAN= 36 000 000 /4= 9 000 000
	1tq= 1/fCAN= 1/9 000 000
	toc do CAN =1/9tq= 1Mb/s
	*/
	CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
  CAN_InitStruct.CAN_BS1 = CAN_BS1_6tq;
  CAN_InitStruct.CAN_BS2 = CAN_BS2_8tq;
	
	
	 CAN_Init(CAN1, &CAN_InitStruct);
	   // C?u hình b? l?c CAN
		     CAN_FilterInitTypeDef CAN_FilterInitStruct;
    CAN_FilterInitStruct.CAN_FilterNumber = 0;
    CAN_FilterInitStruct.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStruct.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStruct.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStruct.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStruct.CAN_FilterActivation = ENABLE;
	
		CAN_FilterInit(&CAN_FilterInitStruct);
	
		 CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
	
	
}

void PWM_Config()
{
		TIM_TimeBaseInitTypeDef TIM_TimebaseStuct;
    TIM_TimebaseStuct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimebaseStuct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimebaseStuct.TIM_Period = 2000 - 1;
    TIM_TimebaseStuct.TIM_Prescaler = 72 - 1;

    TIM_TimeBaseInit(TIM2, &TIM_TimebaseStuct);

    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 1500;  // Initial 1.5ms pulse width (90 degrees)
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC2Init(TIM2, &TIM_OCInitStruct);  // Servo (PA1)
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);  // Motor speed (PA5)

    TIM_Cmd(TIM2, ENABLE);
	
}
void processCANMessage(CanRxMsg *RxMessage)
{
    if (RxMessage->Data[0] == 'S') {
        // Servo control
        int angle = atoi((const char*)&RxMessage->Data[1]);
        if (angle >= 0 && angle <= 180) {
            int pulseWidth = 1000 + (angle * 1000 / 180);
            TIM_SetCompare2(TIM2, pulseWidth);  // Set the pulse width on TIM2 channel 2 (PA1)
        }
    } else if (RxMessage->Data[0] == 'M') {
        // Motor control
        int speed = atoi((const char*)&RxMessage->Data[1]);
        if (speed >= 0 && speed <= 255) {
            TIM_SetCompare1(TIM2, speed * 78);  // Set PWM duty cycle on TIM2 channel 1 (PA5)
            GPIO_SetBits(GPIOA, IN1_PIN);  // Set motor direction
            GPIO_ResetBits(GPIOA, IN2_PIN);
        }
    }
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET) {
        CanRxMsg RxMessage;
        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
        processCANMessage(&RxMessage);
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
    }
}


int main ()
{
	RCC_Config();
  GPIO_Config();
  CAN_Config();
  PWM_Config();
	
	
	
	while (1)
	{
	}
	
}