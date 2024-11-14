#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include  "lcd.h"
#include "delay.h"

int main()
{
	DelayInit();
	LCD_Init();
	
	while (1){
		LCD_Gotoxy(0,0);
		LCD_Puts("Hoang Long Vu");
		LCD_Gotoxy(0,1);
		LCD_Puts("CTTT OTO K66 ");
		DelayMs(500);	
	
	}
	
}