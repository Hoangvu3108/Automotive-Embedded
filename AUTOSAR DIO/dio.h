	/*
		* @file Dio.h
		* @brief Header file for DIO driver according to AUTOSAR Classic
		* date 3/10/2024
		* Athor: Hoang Long Vu
	
*/
#ifndef DIO_H
#define DIO_H

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

typedef struct {
		uint16_t vendorID;
		uint16_t moduleID;
		uint16_t sw_major_version;
		uint16_t sw_minor_version;
		uint16_t sr_path_version;
}		Std_VersionInfoType;



/*
	* Define all the channels for Autosar
	* Channels will be numbered from 0 to max number of pin
	* For example, ChannelId DIO_CHANNEL 0 to 15 will be the pin from 0 to 15 in GPIOA, 
		and Channel from 16 to 31 will be in GPIOB
*/

#define DIO_CHANNEL_0 (Dio_ChannelType)0  // GPIOA 0x0000000000000000
#define DIO_CHANNEL_1 (Dio_ChannelType)1
#define DIO_CHANNEL_2 (Dio_ChannelType)2
#define DIO_CHANNEL_3 (Dio_ChannelType)3
#define DIO_CHANNEL_4 (Dio_ChannelType)4
#define DIO_CHANNEL_5 (Dio_ChannelType)5
#define DIO_CHANNEL_6 (Dio_ChannelType)6
#define DIO_CHANNEL_7 (Dio_ChannelType)7
#define DIO_CHANNEL_8 (Dio_ChannelType)8
#define DIO_CHANNEL_9 (Dio_ChannelType)9
#define DIO_CHANNEL_10 (Dio_ChannelType)10
#define DIO_CHANNEL_11 (Dio_ChannelType)11
#define DIO_CHANNEL_12 (Dio_ChannelType)12
#define DIO_CHANNEL_13 (Dio_ChannelType)13
#define DIO_CHANNEL_14 (Dio_ChannelType)14
#define DIO_CHANNEL_15 (Dio_ChannelType)15  // GPIOA Pin 15

#define DIO_CHANNEL_16 (Dio_ChannelType)16	// GPIOB Pin 0
#define DIO_CHANNEL_17 (Dio_ChannelType)17
#define DIO_CHANNEL_18 (Dio_ChannelType)18
#define DIO_CHANNEL_19 (Dio_ChannelType)19
#define DIO_CHANNEL_20 (Dio_ChannelType)20
#define DIO_CHANNEL_21 (Dio_ChannelType)21
#define DIO_CHANNEL_22 (Dio_ChannelType)22
#define DIO_CHANNEL_23 (Dio_ChannelType)23
#define DIO_CHANNEL_24 (Dio_ChannelType)24
#define DIO_CHANNEL_25 (Dio_ChannelType)25
#define DIO_CHANNEL_26 (Dio_ChannelType)26
#define DIO_CHANNEL_27 (Dio_ChannelType)27
#define DIO_CHANNEL_28 (Dio_ChannelType)28
#define DIO_CHANNEL_29 (Dio_ChannelType)29
#define DIO_CHANNEL_30 (Dio_ChannelType)30
#define DIO_CHANNEL_31 (Dio_ChannelType)31 // GPIOB PIN15

/* The same to remained Ports
	*   DIO_GET_PORT_FROM_CHANNEL_ID{ _channelId} {_channelID/16}
	* 	GET DIO_PORT
	* 	For example, The result will be 0 if ChannelID in range of 0-15, which means it GPIOA
	
*/
	
	#define DIO_GET_PORT_FROM_CHANNEL_ID(_channelId) (_channelId/16)

	#define Dio_ChannelType 			uint8_t
	#define Dio_PortType 					uint8_t
	#define Dio_PortLevelType			uint16_t
	#define Dio_LevelType 				uint16_t
	#define Dio_PortLevelType 		uint16_t
	#define DIO_GET_BIT_FROM_CHANNEL_ID(_channelId)(1 << (_channelId %16))


//	#define Dio_ChannelGroupType
	#define STD_LOW (uint8_t) 0x00
	#define STD_HIGH (uint8_t) 0x01
	
	/* define your module's version information */
	#define DIO_MODULE_ID (123)  // Example module ID
	#define DIO_VENDOR_ID (456)	// Example venfor ID
	#define DIO_SW_MAJOR_VERSION (1)// Example software major version
	#define DIO_SW_MINOR_VERSION (0)// Example software minor version
	#define DIO_SW_PATCH_VERSION  (0) // Example software patch version
	
	
	// Define the Type for GPIO_TypeDef Pointer 
	typedef GPIO_TypeDef* GPIO_TypeDefPtr;
	
	typedef struct{
				uint16_t mask;
				uint8_t offset;
				Dio_PortType port;
	}	Dio_ChannelGroupType;

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
	
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);


Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

void Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask);

void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo);
	
	
	
	
	
	
#endif /*DIO_H*/