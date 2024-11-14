#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "lcd.h"
#include "delay.h"

int main(void)
{
    // Kh?i t?o Delay v� LCD
    DelayInit();
    LCD_Init();

    // Hi?n th? d�ng ch? "BOM" ? v? tr� (0, 0)
    LCD_Gotoxy(0, 0);
    LCD_Puts("BOM");

    // Hi?n th? d�ng ch? "Minion" ? v? tr� (0, 1)
    LCD_Gotoxy(0, 1);
    LCD_Puts("Minion");

    while (1)
    {
        // Chuong tr�nh s? l?p v� h?n
    }
}
