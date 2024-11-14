#ifndef ___IT_H
#define ___IT_H

/* Define for interrupt numbers */
#define USART2_IRQn   38  // Interrupt number for USART2

/* Define for interrupt priorities */
#define USART2_PRIORITY   1   // Priority level for USART2

/* Define for enabling/disabling interrupts */
#define ENABLE_USART2_INTERRUPT()   NVIC_EnableIRQ(USART2_IRQn)
#define DISABLE_USART2_INTERRUPT()  NVIC_DisableIRQ(USART2_IRQn)


void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART2_IRQHandler(void);



#endif
// cai nay tham khao cua GPT