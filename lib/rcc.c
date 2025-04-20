#include "rcc.h"
#include <stdio.h>
/*
Bit 4 IOPCEN: IO port C clock enable
Set and cleared by software.
0: IO port C clock disabled
1: IO port C clock enabled
*/
void enable_clock(void)
{
    RCC->RCC_APB2ENR |= (1 << 4); // enable  clock port C
    RCC->RCC_APB2ENR |= (1 << 2); // enable clock port A
    RCC->RCC_CFGR |= 5 << 24; // get clock by MCO bit debug
}
void enable_clock_source(void)
{
    RCC->RCC_CR |= 1U << 16; // use HSE
    while (!(RCC->RCC_CR & 1U << 17)) // wait HSE on
        ;
    RCC->RCC_CR |= 1U << 24; // use PLL

    while (!(RCC->RCC_CR & 1U << 25)) // wait PLL
        ;

    RCC->RCC_CFGR |= 0b10 << 0;
    RCC->RCC_CFGR |= 1U << 16;
    RCC->RCC_CFGR |= 0b1010 << 18;
}
void enable_clock_uart1(void)
{
    RCC->RCC_APB2ENR |= (1U << 14); // enable clock USART1
}
