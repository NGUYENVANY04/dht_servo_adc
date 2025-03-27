#include <stdint.h>
#include <stdio.h>
#include "drivers/log_info.h"
#include "uart.h"
#include "drivers/dht.h"
#include "rcc.h"
#include "systick.h"
/*void test_uart()
{
    USART1->USART_CR1 |= (uint32_t)1 << 13;
    USART1->USART_CR1 |= (uint32_t)0 << 12;
    USART1->USART_CR2 |= (uint32_t)0 << 12;
    USART1->USART_BRR = ((0x1D4 << 4) | 0xC);
    USART1->USART_CR1 |= (uint32_t)1 << 3;
}*/

int main()
{
    enable_clock();
    enable_clock_uart1();

    GPIO_Config_t uart = {
        .pin = 1U << 9,
        .mode = GPIO_MODE_OUTPUT_50MHz,
        .outputType = GPIO_OUTPUT_AF_PUSH_PULL,
        .port = GPIOA,
    };
    GPIO_Config(&uart);
    SysTick_Init();
    init_uart();
    while (1)
    {

        uint8_t data[5] = read_data(13);
        log_info(data[0]);
        delay_us(18);
        log_info(data);
        delay_us(100000);
    }
}

