#include <stdint.h>
#include <stdio.h>
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
    GPIO_Config_t pin_config = {
        .pin = 1U << 13,
        .port = GPIOC,
    };
    GPIO_Config(&pin_config);

    // init_uart();
    while (1)
    {

        start_signal(pin_config);
        delay_us(100000);
        // read_data(13);
        //  sent_uart(read_data(13));
        // delay_us(2000);
    }
}

