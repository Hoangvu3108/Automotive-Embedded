
/***************************************************
 *@file Can.h
 *@brief CAN General Types header File
 *@details This file includes some definition about type and kind of structure in CAN Driver in AUTOSAR
 *@version 1.0
 *@date 10-31-20244
 *@author Hoang Long Vu
 **************************************************/
 
 #ifdef CAN_H
 #define CAN_H
 
 
#include "Std_Types.h"
#include "Can_GeneralTypes.h"   
#include "Can_Types.h"

/***************************************************
*@typedef Can_ConfigType
*@brief This function configure for CAN driver according to Standard AUTOSAR
*@details This is the type of the external data structure containing the overall initialization data for the CAN
driver and SFR settings affecting all controllers. Furthermore it contains pointers to controller
configuration structures. The contents of the initialization data structure are CAN hardware
specific.

***************************************************/
typedef struct 
{  // Reference by STM's document of PVV
		 // This is  config for transmit time
		uint16 CAN_Prescaler; // Below these some basic function config for CAN 
 
		unit8 CAN_Mode;
 
		uint8 CAN_SJW;
 
		uint8 CAN_BS1;
  
		uint8 CAN_BS2;
   
		// Configure for CAN 
		FunctionalState CAN_TTCM;
		
		FunctionalState CAN_BOM;
				
		FunctionalState CAN_AWUM;

		FunctionalState CAN_NART;
		
		FunctionalState CAN_RFLM; // Decides whether the FIFO will be locked or overwritten if data is not read in time
		
		FunctionalState CAN_TXFX; 


}Can_ConfigType;

#define CAN_VENDOR_ID                (0x123)  // Mã d?nh danh nhà cung c?p
#define CAN_MODULE_ID                (0x01)   // Mã d?nh danh module CAN

// Ð?nh nghia các phiên b?n ph?n m?m (software version)
#define CAN_SW_MAJOR_VERSION         (1)    // Phiên b?n chính (major version)
#define CAN_SW_MINOR_VERSION         (0)    // Phiên b?n ph? (minor version)
#define CAN_SW_PATCH_VERSION         (0)    // Phiên b?n s?a l?i (patch version)

// Prototype c?a hàm Can_GetVersionInfo
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo);



 
 
 
 
 #endif
 
 