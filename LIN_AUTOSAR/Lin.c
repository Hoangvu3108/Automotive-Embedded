#include "Lin.h"
#include "Lin_Cfg.h"

/**
 * @brief Kh?i t?o mô-dun LIN.
 * @param Config Con tr? d?n c?u trúc c?u hình LIN.
 */
void Lin_Init(const Lin_ConfigType* Config) {
    // Ki?m tra c?u hình h?p l?
    if (Config == NULL) {
        return; // Tr? v? n?u c?u hình không h?p l?
    }

    // B?t clock cho các port GPIO và UART s? d?ng cho LIN
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    // C?u hình chân Tx (PA9) và Rx (PA10) cho UART s? d?ng cho LIN
    GPIO_InitTypeDef GPIO_InitStructure;

    // Chân Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Chân Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // C?u hình UART cho LIN
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = Config->Lin_BaudRate; // T?c d? truy?n t? c?u hình
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    // ... ti?p t?c c?u hình USART
}