#include "systick.h"
#include <stdint.h>
void SysTick_Init(void)
{
    SYSTICK->SYST_RVR = 8U - 1U;
    SYSTICK->SYST_CVR = 0;
    SYSTICK->SYST_CSR = (1U << 0) | (1U << 2);
}
void delay_us(uint32_t us)
{
    while (us--)
    {
        while (!(SYSTICK->SYST_CSR & (1U << 16)))
            ;
    }
}
