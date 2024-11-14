//#include "stm32f4xx.h"                  // Device header

//void delay_ms(uint32_t timedelay){
//	for(uint32_t i=0;i<timedelay*40000;i++){
//	
//	}
//}
//void GPIO_Config(void){
//	__HAL_RCC_GPIOD_CLK_ENABLE();
//	GPIO_InitTypeDef myLEDStruct;
//	myLEDStruct.Mode= GPIO_MODE_OUTPUT_PP;
//	myLEDStruct.Pin= GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
//	HAL_GPIO_Init(GPIOD, &myLEDStruct);
//	
//}

//int main(){
//	//GPIO_Config();
//	while(1)
//	{
//		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
//		delay_ms(1000);
//	}
//	}


#include "stm32f4xx_hal.h"

void configureLEDpins(void);
void msDelay(uint32_t msTime);

int main(void) {
    // 1: Configure LEDs pins
    configureLEDpins();

    // 2: Define a delay function
    //msDelay(uint32_t msTime);

    while (1) {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
        msDelay(1000);
    }
}
void configureLEDpins(void) {
    
		__HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef myLEDConfig;
    myLEDConfig.Mode = GPIO_MODE_OUTPUT_PP;
    myLEDConfig.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD, &myLEDConfig);
}
void msDelay(uint32_t msTime) {
    for(uint32_t i=0;i<msTime*100 ;i++);
}
