#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "lcd.h"
#include "delay.h"

int main(void)
{
    // Kh?i t?o Delay và LCD
    DelayInit();
    LCD_Init();

    // Hi?n th? dòng ch? "BOM" ? v? trí (0, 0)
    LCD_Gotoxy(0, 0);
    LCD_Puts("BOM");

    // Hi?n th? dòng ch? "Minion" ? v? trí (0, 1)
    LCD_Gotoxy(0, 1);
    LCD_Puts("Minion");

    while (1)
    {
        // Chuong trình s? l?p vô h?n
    }
}
