#include "stm32f10x.h"                  // Device header
#include "stm32f10x_can.h"              // Device:StdPeriph Drivers:CAN
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM
// cap xung 
//void RCC_Config()
//{		 RCC_APB2PeriphClockCmd();
//		

//}
// cau hinh chan gpio

void GPIO_Config()
{ 
}
void CAN_Config()
{
	CAN_InitTypeDef CAN_InitStruct;
	CAN_InitStruct.CAN_TTCM=DISABLE; // giao tiep bang tin hieu thoi gian 
	CAN_InitStruct.CAN_ABOM= DISABLE;/*!< Enable or disable the automatic bus-off                    QUAN LY NGAT BUS TU DONG NEU TRONG QUA TIRNH TRUYEN XAY RA LOI THI BUS SE DUOJC NGAT
                                  management. This parameter can be set either 
                                  to ENABLE or DISABLE. */
	CAN_InitStruct.CAN_AWUM= DISABLE   ; //Enable or disable the automatic wake-up mode. 
	CAN_InitStruct.CAN_NART = ENABLE ;  /*Enable or disable the no-automatic                           NGUOI TA BAO LA NEN SET CAI BIT KHI SU DUN CHUNG VOI CAN_TTCM 
                                  retransmission mode.*/
	CAN_InitStruct.CAN_RFLM= DISABLE	 ;// Enable or disable the Receive FIFO Locked mode.                CHE DO KHOA BO DEM KHI DAY FIRST IN FIRST OUT  
	CAN_InitStruct.CAN_TXFP=ENABLE;
	
	
}
int main()
{
	
	while (1){
	
	
	
	}
}