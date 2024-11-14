/*************************************
*@date 10_31_2024
*@author Hoang Long Vu
*************************************/
#include "Can.h"
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

/*****************************************************
*@brief 
*@para Config 
*
*
*****************************************************/

void Can_Init (const Can_ConfigType* Config)
{ 
	CAN_InitTypeDef CAN_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	//Step 1: Kich hoat clock cho CAN1 Va GPIOA
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	// Step 2: Configure the CAN_RD (PA11)
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// Step 3: Configure the CAN_TD (PA12)
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// Step4: Configure the basic parameters for CAN_InitTypeDef 
	CAN_InitStructure.CAN_Prescaler=Config->Can_ConfigType.CAN_Prescaler;
	CAN_InitStructure.CAN_Mode=Config->Can_ConfigType.CAN_Mode;
	CAN_InitStructure.CAN_SJW=Config->Can_ConfigType.CAN_SJW;
	CAN_InitStructure.CAN_BS1=Config->Can_ConfigType.CAN_BS1;
	CAN_InitStructure.CAN_BS2=Config->Can_ConfigType.CAN_BS2;
	
	// STEP 5 : Configure the extension parameters for CAN_InitTypeDef
	CAN_InitStructure.CAN_TTCM=Config->Can_ConfigType.CAN_TTCM;
	CAN_InitStructure.CAN_ABOM=Config->Can_ConfigType.CAN_ABOM;
	CAN_InitStructure.CAN_AWUM=Config->Can_ConfigType.CAN_AWUM;
	CAN_InitStructure.CAN_NART=Config->Can_ConfigType.CAN_NART;
	CAN_InitStructure.CAN_RFLM=Config->Can_ConfigType.CAN_RFLM;
	CAN_InitStructure.CAN_TXFP=Config->Can_ConfigType.TXFP;
	CAN_InitStructure.CAN_Mode=Config->Can_ConfigType.CAN_Mode;
	
	if(CAN_Init(CAN1,&CAN_InitStructure) !=CAN_InitStatus_Success)
	{
	}
	
}
/********************************************************
*@brief Get info version of CAN Driver
*@para versioninfo Pointer to struct to get inforversion
********************************************************/
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
	if(versioninfo != NULL)
	{ versioninfo->vendorID=0x1234;
		versioninfo->moduleID=0x01;
		versioninfo->major_version=1;
		versioninfo->sw_minor_version=0;
		versioninfo->sw_patch_version=0;

	}
	
	
}

void DeInit(void)
{
	
	CAN_Cmd(CAN1,DISABLE);
	CAN_DeInit(CAN1);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0| CAN_IT_TME| CAN_IT_ERR,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,DISABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_12;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

/*****************************************************
*@brief 
*@para
*@detail
*****************************************************/
Std_ReturnType Can_SetBaudrate (uint8 Controller,uint16 BaudRateConfigID)
{
	
	
	
	
	
}
