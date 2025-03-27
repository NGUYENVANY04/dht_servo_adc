#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include <stdint.h>

#define SYSTICK_ADDRESS 0xE000E010UL

typedef struct
{
    volatile uint32_t SYST_CSR;
    volatile uint32_t SYST_RVR;
    volatile uint32_t SYST_CVR;
    volatile uint32_t SYST_CALIB;
} systick_t;

#define SYSTICK ((systick_t *)SYSTICK_ADDRESS)

void SysTick_Init(void);
void delay_us(uint32_t us);

#endif

