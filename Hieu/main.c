#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_usart.h"            // Device:StdPeriph Drivers:USART
#include "misc.h"                       // Device:StdPeriph Drivers:Framework
 #include<string.h>
 #include<stdlib.h>
 
 #define TX_Pin GPIO_Pin_9
 #define RX_Pin GPIO_Pin_10
 
 #define SERVO_PIN GPIO_Pin_1 
 #define MOTOR_SPEED_PIN GPIO_Pin_5
 #define IN1_PIN GPIO_Pin_6
 #define IN2_PIN GPIO_Pin_7
 
 volatile char inputString[200];
 volatile uint8_t stringComplete =0;
 
 void RCC_Config()
 {
	 RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	 
	 
 }
 
 
void GPIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStruct;
		
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=	 GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_1| GPIO_Pin_5; // Servo_pin| motor_speed_pin
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	// CAP XUNG CHO CHAN TX
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	// cap xung cho chan RX
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void USART_Config()
{
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate=115200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode= USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Init(USART1,& USART_InitStruct);
	USART_Cmd(USART1,ENABLE);
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
	TIM_TimeBaseInitTypeDef TIM_TimebaseStuct;
	TIM_TimebaseStuct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimebaseStuct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimebaseStuct.TIM_Period=2000-1;
	TIM_TimebaseStuct.TIM_Prescaler=72-1;
	//TIM_TimebaseStuct.TIM_RepetitionCounter;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimebaseStuct);
	
		TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 1500;  // Initial 1.5ms pulse width (90 degrees)
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM2, &TIM_OCInitStruct);
		TIM_OC1Init(TIM2, &TIM_OCInitStruct);  // Same settings, initially at 0 speed

    // Start TIM2
    TIM_Cmd(TIM2, ENABLE);
}
void processCommand()

{
    if (inputString[0] == 'S') {
        // Servo control
        int angle = atoi((const char*)&inputString[1]);
        if (angle >= 0 && angle <= 180) {
            // Convert angle to PWM value (1ms to 2ms pulse width for 0 to 180 degrees)
            int pulseWidth = 1000 + (angle * 1000 / 180);
            TIM_SetCompare2(TIM2, pulseWidth);  // Set the pulse width on TIM2 channel 2 (PA1)
        }
    } else if (inputString[0] == 'M') {
        // Motor control
      int speed = atoi((const char *)&inputString[1]);   //abort// convert string to int
        if (speed >= 0 && speed <= 255) {
            TIM_SetCompare1(TIM2, speed * 78);  // Set PWM duty cycle on TIM2 channel 1 (PA5)
            GPIO_SetBits(GPIOA, IN1_PIN);  // Set motor direction
            GPIO_ResetBits(GPIOA, IN2_PIN);
        }
    }

    // Clear the input string
memset((char *)inputString, 0, sizeof(inputString));

	
				

			}				
			
	void USART_IRQHandler()
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        static uint8_t idx = 0;
        char receivedChar = USART_ReceiveData(USART1);  // Read the received character

        if (receivedChar == '\n') {
            stringComplete = 1;  // Set flag when newline is received
            inputString[idx] = '\0';  // Null-terminate the string
            idx = 0;  // Reset index
        } else {
            inputString[idx++] = receivedChar;  // Store the received character
        }
    }
}
	
	
	
	
	
 int main ()
{	
	RCC_Config();
	GPIO_Config();
	USART_Config();
	PWM_Config();
	
	USART_SendData(USART1,'R');
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
	
	while (1)
	{
			if(stringComplete){
				processCommand();
				stringComplete =0;
				
			}
		}
		
		
	}
	
	
	
 