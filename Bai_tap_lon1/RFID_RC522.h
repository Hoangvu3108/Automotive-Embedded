/* File name : SPI_RCC522.h Library to use STM32F103C8
	*Created by Hoang Long Vu 
	*/
	#ifndef __RFID_RC522_H__
	#define __RFID_RC522_H__
	
#include "stm32f10x.h"                  // Device header
#include "spi.h"
#include "stm32f10x_spi.h"              // Device:StdPeriph Drivers:SPI


#define uchar uint8_t
#define uint 	uint32_t

// chieu dai toi da cua mang 
#define MAX_LEN 16

//Bang ma loi giao tiep va phan hoi lai
#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2

// dinh nghia thanh ghi lenh cho RF522 hay MFRC522
#define PCD_IDLE                    0x00  // No action ; huy bo lenh hien hanh
#define PCD_AUTHENT 								0x0E	// Xac nhan KEY
#define PCD_RECEIVE									0x08	// nhan du lieu
#define PCD_TRANSMIT 								0x04	// ghi du lieu
#define PCD_TRANSCEIVE							0x0C	// gui va nhan du lieu
#define PCD_RESETPHASE 							0x0F	// Reset
#define PCD_CALCCRC									0x03 // Tinh toan CRC
	
// Dinh nghia thanh ghi enh cho Mifare_one
#define PICC_REQIDL									0x26   // find the antenna area does not enter hibernation
#define PICC_REQALL									0x52   // find all the cards antenna area
#define PICC_ANTICOLL								0x93   // anti-collision
#define PICC_SElECTTAG							0x93   // election card
#define PICC_AUTHENT1A							0x60   // authentication key A
#define PICC_AUTHENT1B							0x61   // authentication key B
#define PICC_READ										0x30   // Read Block
#define PICC_WRITE									0xA0   // write block
#define PICC_DECREMENT							0xC0   // debit
#define PICC_INCREMENT							0xC1   // recharge
#define PICC_RESTORE								0xC2   // transfer block data to the buffer
#define PICC_TRANSFER								0xB0   // save the data in the buffer
#define PICC_HALT										0x50   // Sleep
	
	// MFRCC522 Register 
	//Page 0:Command and Status
#define     Reserved00            0x00    
#define     CommandReg            0x01    
#define     CommIEnReg            0x02    
#define     DivlEnReg             0x03    
#define     CommIrqReg            0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     Reserved01            0x0F
//Page 1:Command     
#define     Reserved10            0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     Reserved11            0x1A
#define     Reserved12            0x1B
#define     MifareReg             0x1C
#define     Reserved13            0x1D
#define     Reserved14            0x1E
#define     SerialSpeedReg        0x1F
//Page 2:CFG    
#define     Reserved20            0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     Reserved21            0x23
#define     ModWidthReg           0x24
#define     Reserved22            0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsPReg	          	0x28
#define     ModGsPReg             0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
//Page 3:TestRegister     
#define     Reserved30            0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     Reserved31            0x3C   
#define     Reserved32            0x3D   
#define     Reserved33            0x3E   
#define     Reserved34			  		0x3F
//-----------------------------------------------
// Cac ham su dung
	void MFRC522_Init(void);
void TM_MFRC522_WriteRegister(uint8_t addr, uint8_t val);
void TM_MFRC522_ReadRegister(uint8_t addr);
void TM_MFRC522_SetBitMask(uint8_t reg, uint8_t mask);
void TM_MFRC522_ClearBitMask(uint8_t reg, uint8_t mask);
void TM_MFRC522_AntennaOn(void);
void TM_MFRC522_AntennaOff(void);
void TM_MFRC522_Reset(void);
void TM_MFRC522_Request(uint8_t reqMode, uint8_t* TagType);
void TM_MFRC522_Anticoll(uint8_t* serNum);
void TM_MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen);
void TM_MFRC522_SelectTag(uint8_t* serNum);
void TM_MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum);
void TM_MFRC522_Read(uint8_t blockAddr, uint8_t* recvData);
void TM_MFRC522_Write(uint8_t blockAddr, uint8_t* writeData);

void MFRC522_Halt(void);	
	/* extern khai bao bien toan cuc khi banj cos mot so bien toan cuc duoc dinh nghia trong mot file nhung ban muon su du no o cac file khac ban se 
	khai bao bien do voi extern
	Neu ma su dung trong cac du an: Giup chi chuong trinh thanh nh file nguon ma van co the chia se cac bien or ham giua chung
	*/
	
	#endif