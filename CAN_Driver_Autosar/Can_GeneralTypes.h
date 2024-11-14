
/***************************************************
 *@file CAN_GeneralType.h
 *@brief CAN General Types header File
 *@details This file includes some definition about type and kind of structure in CAN Driver in AUTOSAR
 *@version 1.0
 *@date 10-31-20244
 *@author Hoang Long Vu
 **************************************************/
#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H


#include "Std_Types.h"
#include "ComStack_Types.h"
/***************************************************
*@typedef Can_IdType
*@brief The type stand for CAN ID
*@details Using uint32 to illustrate cho both CAN ID 11 bit and 29 bit
***************************************************/
typedef uint32_t Can_IdType;

/***************************************************
*@typedef Can_HwHandleType
*@brief The type stand for Hardware Handle CAN
*@details Represents the hardware object handles of a CAN hardware unit. For CAN hardware units with
more than 255 HW objects use extended range 
***************************************************/
// uint 16 va uint 8 thi ta se su dung de uinit 16 cho gia tri toi do va ta do phai cau hau lai cho no khi qua 255
typedef uint16 Can_HwHandleType;
/***************************************************
*@typedef Can_PduType
*@brief defines CAN_L_SDU in CAN
***************************************************/
typedef struct
{
	PduIdType swPduIdType;       /**< Pdu ID*/
	uint8 length;
	Can_IdType id;
	const uint8 *sdu;           // tham so b   
} Can_PduType;











#endif