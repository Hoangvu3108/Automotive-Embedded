#include "stm32f10x.h"                  // Device header
#include "stm32f10x_can.h"              // Device:StdPeriph Drivers:CAN
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

uint16_t id=0x123;
uint32_t ID;
uint8_t TestArray[8];

void RCC_Config()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
}

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,  &GPIO_InitStruct);;
	
	
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void CAN_Config()
{
	CAN_InitTypeDef CAN_InitStruct;
	
	CAN_InitStruct.CAN_TTCM=DISABLE;
	CAN_InitStruct.CAN_ABOM=DISABLE;
	CAN_InitStruct.CAN_AWUM=DISABLE;
	CAN_InitStruct.CAN_NART=DISABLE;
	CAN_InitStruct.CAN_TXFP=DISABLE;
	CAN_InitStruct.CAN_RFLM=DISABLE;
	
	
	CAN_InitStruct.CAN_Mode=CAN_Mode_Normal;
	
	CAN_InitStruct.CAN_Prescaler=4;
	CAN_InitStruct.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStruct.CAN_BS1= CAN_BS1_3tq;
	CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
	
	CAN_Init(CAN1, &CAN_InitStruct);
}
void CAN_Filter_Config(){
			CAN_FilterInitTypeDef CAN_FilterInitStruct;
			CAN_FilterInitStruct.CAN_FilterNumber=0;
			CAN_FilterInitStruct.CAN_FilterMode=CAN_FilterMode_IdMask;
			CAN_FilterInitStruct.CAN_FilterScale= CAN_FilterScale_32bit;
			CAN_FilterInitStruct.CAN_FilterMaskIdHigh= 0xFFE0;
			CAN_FilterInitStruct.CAN_FilterMaskIdLow =0x0000;
			CAN_FilterInitStruct.CAN_FilterIdHigh=0x123<<5;
			CAN_FilterInitStruct.CAN_FilterIdLow=0x0000;
			CAN_FilterInitStruct.CAN_FilterFIFOAssignment= CAN_Filter_FIFO0;
			CAN_FilterInitStruct.CAN_FilterActivation= ENABLE;
	
		CAN_FilterInit(&CAN_FilterInitStruct);

}

void CAN_Receivedata()
{
	CanRxMsg RxMessage;
	while (CAN_MessagePending(CAN1, CAN_FIFO0) <1);
	CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	ID = RxMessage.StdId;
	for(int i=0;i<RxMessage.DLC;i++)
	{
		TestArray[i]=RxMessage.Data[i];
	
	}
	
}
int main()
{
	RCC_Config();
	GPIO_Config();
	CAN_Config();
	CAN_Filter_Config();
	
	while(1)
	{
	CAN_Receivedata();	
	}
	
	
}	