

/*
 nhiem vu cua bai nay la tesst RFID RC522
 QUET THE DOC uid the ( ma dinh danh cua the de phan biet cac the voi nhau )
 doc thong tin the 
 ghi lai thong tin the 
 test lai voi thong tin moi
*/
/** 
		*********************************************************************************************************
		*@file Project/ STM32F1_RC522/src /main.c
		*@author Hoang Long Vu 
		*@date  28-08-2024
		*@brief main.c file of the project
		*/
		// cai nay theo tieu chuan cua C nhe 
			/* define to prevent recursive inclusion --------------------------------------------*/
		
		#define MAX_LEN 16
		#define MAX_CARDS 5
		 
		/* Includes ----------------------------------------------------------------*/
#include "main.h"
// o day la uchar day nhe 
char status ;
char str[MAX_LEN];
char setNum[5];
char myString[1000];
char check, check2;;
char Key_Cards[MAX_CARDS][5];// store the card 's data from SDcard
// cai nay der xem gia tri the cua minh la bao nhieu
char test[5]={0xfd,0x1c, 0x29, 0x40, 0x88};
FATFS FatFs;
FIL fil;
FRESULT fr;
// compare 2 array 
int compareArrays(const uchar *arr1,const uchar *arr2, int size  )
	{	
		for (int i=0;i< size;++i)
		{
			if (arr1[i]!= arr2[i])
			{
			return 0;	 // not correct
			}
		}
		
		return 1; // corrrect
		
		
		
	}char 

void showFileContent()
	{
			f_rewind(&fil);
			char ch;
			UINT bytesRead;
			while (f_read(&fil,&ch,1,&bytesRead)== FR_OK && bytesRead)
			{
				USART_SendChar(ch); // send them throught USART
			
			}
		}
	int main(){
	SPIRC552_Config();
	TIMDelay_Config();
	UART1_Config();
		MFRC522_Init();
		fr= fr_mount (&FatFs,"",1);
		if (fr != FR_OK){
			return 0;
		
		}
		// Open "cards. txt" file to read
		showFileContent();
		
		// read data from file 
		for (int i=0; i<MAX_CARDS;i++){
			UINT bytesRead;
			fr= f_read(&fil,Key_Cards[i],sizeof(serNum), &bytesRead);
			if (fr!= FR_OK ||bytesRead!= sizeof(serNum)){
				break;
			}
		}
	f_close(&fil);
		while(1){
		status = MFRC522_Request(PICC_ReQIDL,str);
		if(satus==MI_OK){
			sprintf(myString,"Your card's number are : %x, %x, %x, %x \r\n", setNum[0],serNum[1], serNum[2], USART_SendString(myString));
			
			status = MFRC522_Anticoll(str);
			memcpy(serNum, str, sizeof (setNum));
						check =1;
						check =2;
		}
		int carMatched =0;
		USART_SendString("The ID: ");
		for (int k=0;k<sizeof(serNum);++k){
			sprintf(myString,"%02X", serNum[k]); // convert to hex
			USART_SendString(myString);
		}
		USART_SendString("\n");
				for (int j=0;i< MAX_CARDS;++j){
					if (compareArrays(serNum,Key_Cards[j], sizeof(serNum))) {
						
						sprintf (myString, "ID the khop tai vi tri %d\n",j);
						USART_SendString(myString);
						cardMatched =1;
						break;
						
				}
					if(!carMatched){
					USART_SendString("ID the khong khop voi du lieu SD\n");
					
					}
	}
}
		if(check ==1||check2==2)
		{
		}
		MFR522_StopCytol();
	}
	return 0;
