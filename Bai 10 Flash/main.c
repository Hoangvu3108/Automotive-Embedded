#include "stm32f10x.h"                  // Device header
#include "stm32f10x_flash.h"            // Device:StdPeriph Drivers:Flash
 
 
 
 #define PAGE2ADDR 0x08000800
 void Flash_Erase(uint32_t addresspage){
	FLASH_Unlock();
	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY)==1);// kiem tra flag co dang cho hay khong
	 FLASH_ErasePage(addresspage);  
	 while(FLASH_GetFlagStatus(FLASH_FLAG_BSY)==1); // cho no xoa xong thi khoa no vao 
	 FLASH_Lock();

 }
 
 void Flash_Writeln(uint32_t address, uint16_t value){
	 FLASH_Unlock();  
	 while(FLASH_GetFlagStatus(FLASH_FLAG_BSY)==1);//kiem tra flag co dang cho hay khong
	 FLASH_ProgramHalfWord(address,value);
	 while (FLASH_GetFlagStatus(FLASH_FLAG_BSY)==1);// cho no xoa xong thi khoa no vao 
	 FLASH_Lock();
	
 
 
 
 }
int main(){ 
		
//	Flash_Erase(PAGE2ADDR);
	Flash_Writeln(PAGE2ADDR,0x0011);
		while(1){
		
		
		}
		
}