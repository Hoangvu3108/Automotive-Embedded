#include "delay.h"

static __IO uint32_t usTicks;

void SysTick_Handler()
{	
	if(usTicks !=0)
	{
	usTicks--;
	}
}
void DelayInit()
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000000);	
}
void DelayUs(uint32_t us)
{
	usTicks= us;
	while(usTicks);
	
}
void Delay(uint32_t ms)
{
	while(ms--)
	{
	DelayUs(1000);
		
	}
}