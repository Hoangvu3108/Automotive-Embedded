#include "dio.h"

static const GPIO_TypeDefPtr GPIO_ports[]= {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF};
/*
*/

Dio_PortLevelType Dio_ReadPort (Dio_PortType PortId){
			Dio_PortLevelType Level =		0x0000;
			Level = GPIO_ReadInputData(GPIO_ports[PortId]);
			return Level;
	
}

/*
		*	Funtion:
		*	Description L Service to seat a value of the port
		* Input:
				PortId - ID of DIO port
				Level - Value to be writen 


*/

void Dio_WritePort (Dio_PortType PortId, Dio_PortLevelType Level)
{
	
			GPIO_Write(GPIO_ports[PortId], Level);
}
/*
					*Function : Dio_ReadChannel
					*Description: 	




*/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType Level;
	Dio_PortLevelType portVal = Dio_ReadPort(DIO_GET_PORT_FROM_CHANNEL_ID(ChannelId));
	Dio_PortLevelType bit=   DIO_GET_BIT_FROM_CHANNEL_ID(ChannelId);
	
	
	if (( portVal & bit ) !=STD_LOW)
	{
		Level =STD_HIGH;
	}
	else 
	{
	Level =STD_LOW;
	
	}
	return Level;
	
}

/*





*/
void Dio_WriteChannel (Dio_ChannelType ChannelId,Dio_LevelType Level)
{
	Dio_PortType port = DIO_GET_PORT_FROM_CHANNEL_ID(ChannelId);
	Dio_ChannelType bit = DIO_GET_BIT_FROM_CHANNEL_ID(ChannelId);
	
	Dio_PortLevelType portVal = Dio_ReadPort(port);
	
	if(Level == STD_HIGH){
	portVal |= bit;
	
	
	}
	 else {
        portVal &= ~bit;
    }
    Dio_WritePort(port, portVal);
	
	
}

/*
*/
void Dio_WriteChannelGroup (const Dio_ChannelGroupType* ChannelGroupIdPtr,Dio_PortLevelType Level )
{
	 Level = (Level << ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask;
    Dio_PortLevelType portVal = Dio_ReadPort(ChannelGroupIdPtr->port) & (~ChannelGroupIdPtr->mask);
    portVal |= Level;
    Dio_WritePort(ChannelGroupIdPtr->port, portVal);
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
	Dio_LevelType Level;
	Level = Dio_ReadPort(ChannelGroupIdPtr->port) &ChannelGroupIdPtr ->mask;
	
	
	// SHIFT DOWN
	Level= Level >> ChannelGroupIdPtr ->offset;
	
	return Level;
	
}
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId)
{
		Dio_LevelType Level;
		
		Level= Dio_ReadChannel (ChannelId);
		
		if(Level == STD_HIGH)
		{ Level= STD_LOW;	
		} else {
		Level =STD_HIGH;
		}
		Dio_WriteChannel (ChannelId, Level);
		return Level;
}
void Dio_MaskedWritePort (Dio_PortType PortId,Dio_PortLevelType Level, Dio_PortLevelType Mask)
{
	Dio_PortLevelType currentValue = Dio_ReadPort(PortId);
	Dio_PortLevelType maskedLevel= (currentValue & -Mask )| (Level & Mask);
		
	Dio_WritePort(PortId, maskedLevel);
	
	
}
void Dio_GetVersionInfo (Std_VersionInfoType* VersionInfo)
{
	if (VersionInfo != 0)
	{
		VersionInfo->moduleID =DIO_MODULE_ID;
		VersionInfo->sr_path_version=DIO_SW_MAJOR_VERSION;
		VersionInfo->vendorID=DIO_VENDOR_ID;
		VersionInfo->sw_major_version= DIO_SW_MAJOR_VERSION;
		VersionInfo->sw_minor_version= DIO_SW_MINOR_VERSION;
		
		
	}
	else {
	// Do nothing if VersionINfor pointer is NULL 
	
	}
	
	
	
	
}



