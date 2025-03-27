#include "uart.h"
#include <stdint.h>
void init_uart(void)
{
    // USE USART1
    // PA9
    USART1->USART_CR1 = 0x00;
    USART1->USART_CR1 |= 1U << 13;
    USART1->USART_CR1 |= 1U << 12;
    USART1->USART_CR2 |= 0U << 12;
    USART1->USART_BRR = 0x341;
    USART1->USART_CR1 |= 1U << 3;
}
void sent_uart(uint8_t data)
{

    USART1->USART_DR = data; // LOad the Data
    while (!(USART1->USART_SR & (1 << 6)))
        ;
}
