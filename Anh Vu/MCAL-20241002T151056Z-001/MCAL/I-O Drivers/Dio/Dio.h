/*
* @file Dio.h
* @brief Header file for the DIO driver according to AUTOSAR Classic.
* @details This file provides the interface for the DIO driver as per AUTOSAR specifications.
* @version 1.0
* @date --/--/--
* @author Phan Minh Thong
*/

#ifndef DIO_H
#define DIO_H

#include "Std_Types.h" // AUTOSAR Standard types

/* DIO module version information */
#define DIO_MODULE_ID             120U
#define DIO_SW_MAJOR_VERSION      1U
#define DIO_SW_MINOR_VERSION      0U
#define DIO_SW_PATCH_VERSION      0U
#define DIO_VENDOR_ID             65535U

/* Dio channel levels */
#define STD_HIGH                  0x01U
#define STD_LOW                   0x00U

/* Dio type definitions */
typedef uint16_t Dio_PortLevelType;
typedef uint8_t  Dio_ChannelType;
typedef uint8_t  Dio_PortType;

/* Dio_ChannelGroupType structure definition */
typedef struct {
    Dio_PortType port;         /**< Port of the group */
    Dio_PortLevelType mask;    /**< Mask defining group bits */
    uint8_t offset;            /**< Bit offset within the port */
} Dio_ChannelGroupType;

/* Function prototypes */

/*
* @brief Returns the level of all channels of the specified port.
* @param PortId ID of the DIO Port.
* @return Dio_PortLevelType Level of all channels of that port.
*/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/*
* @brief Service to set a value of the specified port.
* @param PortId ID of the DIO Port.
* @param Level Value to be written to the port.
*/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/*
* @brief Returns the value of the specified DIO channel.
* @param ChannelId ID of the DIO channel.
* @return Dio_LevelType Level of the channel (STD_HIGH or STD_LOW).
*/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/*
* @brief Service to set a level of a specified channel.
* @param ChannelId ID of the DIO channel.
* @param Level Value to be written (STD_HIGH or STD_LOW).
*/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/*
* @brief Service to set a subset of the adjoining bits of a port to a specified level.
* @param ChannelGroupIdPtr Pointer to the channel group.
* @param Level Value to be written.
*/
void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);

/*
* @brief Reads a subset of adjoining bits of a port.
* @param ChannelGroupIdPtr Pointer to the channel group.
* @return Dio_PortLevelType The level of the subset of adjoining bits.
*/
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);

/*
* @brief Flips the level of a channel and returns the new level.
* @param ChannelId ID of the DIO channel.
* @return Dio_LevelType The new level of the channel after the flip.
*/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);

/*
* @brief Service to set the value of a port with a required mask.
* @param PortId ID of the DIO Port.
* @param Level Value to be written.
* @param Mask Channels to be masked in the port.
*/
void Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask);

/*
* @brief Service to get the version information of the DIO module.
* @param VersionInfo Pointer to store the version information.
*/
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo);

#endif /* DIO_H */
