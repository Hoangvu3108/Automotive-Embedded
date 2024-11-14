#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "lcd.h"
#include "delay.h"

int main()
{
		DelayInit();
	LCD_Init();
		LCD_Gotoxy(0,0);
		LCD_Puts("BOM");
		LCD_Gotoxy(0,1);
		LCD_Puts("Minion");
		DelayMs(500);
}