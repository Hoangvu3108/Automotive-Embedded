/*******************************************************************************************
	
* @file Lin_GeneralTypes.h
 *  @brief Các d?nh nghia chung cho LIN driver theo chu?n AUTOSAR
 *  @details File này ch?a các ki?u d? li?u và d?nh nghia chung du?c s? d?ng trong LIN driver trên STM32F103.
 *  @version 1.0.1
 *  @date 2024-11-1
 *  @author Hoang Long Vu
 ***************************************
 ***********************************/
 #ifndef LIN_H
 #define LIN_H
#include "stm32f10x.h"                  // Device header
#include " Std_Types.h"
#include "Lin_GeneralTypes.h"

/****************************************************
* @typedef Lin_ConfigType
* @brief The structure o LINdriver
*	@description This is the type of the external data structure containing the overall initialization data for the LIN driver and the SFR settings affecting the LIN channels. A pointer to such a
structure is provided to the LIN driver initialization routine for configuration of the driver, LIN hardware unit and LIN hardware channels.

*****************************************************/
typedef struct(){
 uint32_t Lin_Baudrate;
	GPIOA_TypeDef *Lin_Port;
	uint16_t Lin_TxPin;
	uint16_t Lin_RxPin;
	uint8_t Lin_Channel;
	FunctionalState Lin_WakeupSupport;
	IRQn_Type Lin_IRQn;
	uint32_t Lin_Prescaler; 
	uint32_t Lin_Mode;
	uint8_t	Lin_TimeoutDuration;

} Lin_ConfigType;
/*****************************************************
* @typedef Lin_FramePidType
* @brief Represents all valid protected identifier 
* @details Represents all valid protected identifier used by Lin_SendFrame().

****************************************************/
typedef uint8 Lin_FramePidType;
/*******************************************************
* @typedef Lin_FrameCsModelType
* @brief This type is used to specify the Checksum model 
* @details This type is used to specify the Checksum model to be used for the LIN Frame.

******************************************************/

typedef enum
{ LIN_ENHANCED_CS,
	LIN_CLASSIC_CS,
	LIN_FRAMERESPINE_IGNORE
} Lin_FrameCsModelType;



#endif 