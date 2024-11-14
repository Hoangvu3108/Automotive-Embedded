#include "stm32f10x.h"                  // Device header
#include "stm32f10x_i2c.h"              // Device:StdPeriph Drivers:I2C
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO

#define I2C_SCL GPIO_PIN_6
#define I2C_SDA GPIO_PIN_7
#define I2C1_GPIO GPIOB
void RCC_Config(){
}
void GPIO_Config(){
}
void I2C_Config(){
	I2C_InitTypeDef I2C_InitStruct;
	
	I2C_InitStruct.I2C_ClockSpeed=
	I2C_InitStruct.I2C_Mode= 
}
