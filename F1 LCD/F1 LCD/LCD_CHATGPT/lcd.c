#include "lcd.h"

#define LCD_RS      GPIO_Pin_13
#define LCD_RW      GPIO_Pin_14
#define LCD_EN      GPIO_Pin_15
#define LCD_D4      GPIO_Pin_8
#define LCD_D5      GPIO_Pin_9
#define LCD_D6      GPIO_Pin_10
#define LCD_D7      GPIO_Pin_11

void RCC_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_LCD_InitStruction;

    /* Configure GPIO pin Output Level */
    GPIO_WriteBit(GPIOA, LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7, 0); 
    GPIO_WriteBit(GPIOC, LCD_RS | LCD_RW | LCD_EN, 0); 
    
    GPIO_LCD_InitStruction.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_LCD_InitStruction.GPIO_Pin     = LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;      
    GPIO_LCD_InitStruction.GPIO_Speed   = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_LCD_InitStruction);

    GPIO_LCD_InitStruction.GPIO_Pin =  LCD_EN | LCD_RS | LCD_RW;
    GPIO_Init(GPIOC, &GPIO_LCD_InitStruction);
}

void LCD_Config(void)
{
    GPIO_SetBits(GPIOC, LCD_EN);
    DelayMs(1);
    GPIO_ResetBits(GPIOC, LCD_EN);
    DelayMs(1);
}

void LCD_Send4Bit(unsigned char Data)
{
    GPIO_WriteBit(GPIOA, LCD_D4, Data & 0x01);
    GPIO_WriteBit(GPIOA, LCD_D5, (Data >> 1) & 0x01);
    GPIO_WriteBit(GPIOA, LCD_D6, (Data >> 2) & 0x01);
    GPIO_WriteBit(GPIOA, LCD_D7, (Data >> 3) & 0x01);
}

void LCD_SendCommand(unsigned char command)
{
    LCD_Send4Bit(command >> 4);
    LCD_Config();
    LCD_Send4Bit(command);
    LCD_Config();
}

void LCD_Clear(void)
{
    LCD_SendCommand(0x01);
    DelayUs(10);
}

void LCD_Init(void)
{
    GPIO_Config();
    
    LCD_Send4Bit(0x00);
    GPIO_WriteBit(GPIOC, LCD_RS, 0);
    LCD_Send4Bit(0x03);
    LCD_Config();
    LCD_Config();
    LCD_Config();
    LCD_Send4Bit(0x02);
    LCD_Config();
    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0C);
    LCD_SendCommand(0x06);
    LCD_SendCommand(0x01);
}

void LCD_Gotoxy(unsigned char x, unsigned char y)
{
    unsigned char address;
    if (y == 0) address = (0x80 + x);
    else if (y == 1) address = (0xC0 + x);
    LCD_SendCommand(address);
}

void LCD_PutChar(unsigned char Data)
{
    GPIO_SetBits(GPIOC, LCD_RS);
    LCD_SendCommand(Data);
    GPIO_ResetBits(GPIOC, LCD_RS);
}

void LCD_Puts(char *s)
{
    while (*s)
    {
        LCD_PutChar(*s);
        s++;
    }
}
