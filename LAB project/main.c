#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_usart.h"            // Device:StdPeriph Drivers:USART
#include "misc.h"                       // Device:StdPeriph Drivers:Framework
#include<stdio.h>
 #include<string.h>
 #include<stdlib.h>
 
 #define TX_Pin GPIO_Pin_9
 #define RX_Pin GPIO_Pin_10

#define SERVO_PIN   GPIO_Pin_4    // Servo on PA9
#define MOTOR_PWM   GPIO_Pin_5    // Motor PWM on PA5
#define IN1_PIN     GPIO_Pin_6    // Motor direction IN1 on PA6
#define IN2_PIN     GPIO_Pin_7    // Motor direction IN2 on PA7

 volatile char inputString[200];
 volatile uint8_t stringComplete =0;

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
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6| GPIO_Pin_7; // In1_pin ;In2 _pin
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_4 | GPIO_Pin_5; // Servo_pin | motor_speed_pin
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,& GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; // GPT la gpio_mode _IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;    // CAN_TX
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz; 
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;   // CAN_RX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, & GPIO_InitStruct);


}
void UART_Config()
{
	USART_InitTypeDef USART_InitStruct;
	
	USART_InitStruct.USART_BaudRate=115200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode= USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART1,& USART_InitStruct);
	USART_Cmd(USART1,ENABLE);
	// Enable USART receive interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	// CAU HINH THAM SO NGAT VA QUAN LY VECTO NGAT
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;

	NVIC_Init(&NVIC_InitStruct);

}
void PWM_Config()
{
	TIM_TimeBaseInitTypeDef TIM_TimebaseStruct;
	
	TIM_TimebaseStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimebaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimebaseStruct.TIM_Period=2000-1;
	TIM_TimebaseStruct.TIM_Prescaler=72-1;
	
	
		TIM_TimeBaseInit(TIM2, &TIM_TimebaseStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 1500;  // Initial 1.5ms pulse width (90 degrees)
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM2, &TIM_OCInitStruct);
		TIM_OC1Init(TIM2, &TIM_OCInitStruct);  // Same settings, initially at 0 speed
		
	// 4 dong sau khong biet dung de lam gi
		// // PWM for Servo (PA9, channel 4)
		TIM_OC4Init(TIM2, &TIM_OCInitStruct);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

    // PWM for Motor (PA5, channel 1)
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
    // Start TIM2
    TIM_Cmd(TIM2, ENABLE);
	
	
	
}
void USART_SendString(USART_TypeDef* USARTx, char* str) {
    while (*str) {
        USART_SendData(USARTx, *str);  // Send each character
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);  // Wait until transmission is complete
        str++;  // Move to the next character
    }
}

/////////////////////////
void processCommand()
{
	
	if (inputString[0] == 'S')  // Servo control
    {
        int angle = atoi((const char*)&inputString[1]);
        if (angle >= 0 && angle <= 180)
        {
            int pulse = (angle * 10) + 1000;  // Convert angle to PWM pulse
            TIM_SetCompare4(TIM2, pulse);     // Set PWM pulse for servo
            char buffer[50];
            sprintf(buffer, "Servo angle set to: %d\n", angle);
            USART_SendString(USART1, buffer);
        }
        else
        {
            USART_SendString(USART1, "Invalid servo angle. Please enter a value between 0 and 180.\n");
        }
    }
    else if (strncmp((const char*)inputString, "M+", 2) == 0)  // Motor forward
    {
        int speed = atoi((const char*)&inputString[2]);
        if (speed >= 0 && speed <= 255)
        {
            TIM_SetCompare1(TIM2, speed * 78);  // Scale 0-255 to 0-19999
            GPIO_SetBits(GPIOA, IN1_PIN);
            GPIO_ResetBits(GPIOA, IN2_PIN);
            char buffer[50];
            sprintf(buffer, "Motor forward, speed set to: %d\n", speed);
            USART_SendString(USART1, buffer);
        }
        else
        {
            USART_SendString(USART1, "Invalid motor speed. Please enter a value between 0 and 255.\n");
        }
    }
    else if (strncmp((const char*)inputString, "M-", 2) == 0)  // Motor reverse
    {
        int speed = atoi((const char*)&inputString[2]);
        if (speed >= 0 && speed <= 255)
        {
            TIM_SetCompare1(TIM2, speed * 78);  // Scale 0-255 to 0-19999
            GPIO_ResetBits(GPIOA, IN1_PIN);
            GPIO_SetBits(GPIOA, IN2_PIN);
            char buffer[50];
            sprintf(buffer, "Motor reverse, speed set to: %d\n", speed);
            USART_SendString(USART1, buffer);
        }
        else
        {
            USART_SendString(USART1, "Invalid motor speed. Please enter a value between 0 and 255.\n");
        }
    }
    else
    {
        USART_SendString(USART1, "Invalid command.\n");
    }

    // Clear input string
    memset((char *)inputString, 0, sizeof(inputString));
}
	
	////
	void UART_IRQHandler()
	{
		
		if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        static uint8_t index = 0;
        char receivedChar = USART_ReceiveData(USART1);

        if (receivedChar != '\n' && index < sizeof(inputString) - 1)
        {
            inputString[index++] = receivedChar;
        }
        else
        {
            inputString[index] = '\0';  // Null-terminate the string
            stringComplete = 1;  // Set flag
            index = 0;  // Reset index for next command
        }
    }
		
		
		
	}
int main ()
{
		RCC_Config();
		UART_Config();
		GPIO_Config();
		
	 USART_SendString(USART1, "Enter command (e.g., S90 for servo, M100 for motor speed):\n");

		while(1)
		{
			if (stringComplete)
        {
            processCommand();
            stringComplete = 0;  // Reset flag
        }
			
			
			
			
		}
	
	
	
	
	
}
