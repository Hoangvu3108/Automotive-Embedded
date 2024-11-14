#include "RFID_RC522.h"
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

/* 	Function name : RC522_SPI_Transfer 
		Function : Send a byte and receive a byte using SPI
		Input : data -- Data to write 
		Return L Byte received from RFID module
*/
uint8_t RCC522_SPI_Transfer(uint8_t data)
{
	while(SPI_I2S_GetFlagStatus(MFRC522_SPI, SPI_I2S_FLAG_TXE)== RESET);
	SPI_I2S_SendData(MFRC522_SPI,data);
		
	while(SPI_I2S_GetFlagStatus(MFRC522_SPI, SPI_I2S_FLAG_RXNE) ==RESET);
	return SPI_I2S_ReceiveData(MFRC522_SPI);
}
/* 
	* Function name : Write_MFRC5200
	* Functione : Write a byte to RCC522's regiter
	* Input add-- Adress of register to write data to 
					val-- Data to write 
	*	Return none 
*/
void TM_MFRC522_WriteRegister(uint8_t addr, uint8_t val )
{
		/* CS Low*/
		GPIO_ResetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
		RCC522_SPI_Transfer((addr<< 1) & 0x7E);
		RCC522_SPI_Transfer(val);
	
		/*CS High */
		GPIO_SetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
		
}
/* 
	* Function name : Read_ MFRC522
	* Function: Read a byte to RC522's register 
	* Input : addr-- Address of register to read data
* Return : Data read from register 
*/

void TM_MFRC522_ReadRegister(uint8_t addr)
{
	uchar val;
	GPIO_ResetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
	 
	return val;

}
/* 
* Function name : SetBitMark
*	Function : Set a bit in a RC522's register 
* Input :Reg-- Address of register
					mark-- Value to set
*/
void TM_MFRC522_SetBitMask(uint8_t reg , uint8_t mask)
{
	uchar tmp;
	tmp = TM_MFRC522_ReadRegister(reg);
	
	
	
	
	
}

