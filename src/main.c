#include <stdbool.h>
#include <stdint.h>
#include "drivers/gpio_config.h"
#include "drivers/log_info.h"
#include "uart.h"
#include "drivers/dht.h"
#include "rcc.h"
#include "systick.h"
#include "adc.h"
#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
#define TIM2_BASE 0x40000000

#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x1C))
#define GPIOA_CRL (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define TIM2_PSC (*(volatile uint32_t *)(TIM2_BASE + 0x28))
#define TIM2_ARR (*(volatile uint32_t *)(TIM2_BASE + 0x2C))
#define TIM2_CCR1 (*(volatile uint32_t *)(TIM2_BASE + 0x34))
#define TIM2_CCMR1 (*(volatile uint32_t *)(TIM2_BASE + 0x18))
#define TIM2_CCER (*(volatile uint32_t *)(TIM2_BASE + 0x20))
#define TIM2_CR1 (*(volatile uint32_t *)(TIM2_BASE + 0x00))

#define SERVO_MIN 200
#define SERVO_MID 300
#define SERVO_MAX 400

uint16_t read_adc_value(void)
{
    while (!(ADC1->ADC_CR2 & (1U << 1)))
        ; // EOC (End Of Conversion)
    return ADC1->ADC_DR;
}

uint32_t get_temperature(void)
{
    uint16_t adc_val = read_adc_value();
    float vsense = (adc_val * 3.3f) / 4095.0f;
    float temp = ((1.43f - vsense) / 0.0043f) + 25.0f;
    return temp;
}

void GPIO_Init(void)
{
    RCC_APB2ENR |= (1 << 2);
    GPIOA_CRL &= ~(0xF << 0);
    GPIOA_CRL |= (0xB << 0);
}

void Timer2_Init(void)
{
    RCC_APB1ENR |= (1 << 0);
    TIM2_PSC = 39;
    TIM2_ARR = 4000;
    TIM2_CCMR1 |= (6 << 4);
    TIM2_CCMR1 |= (1 << 3);
    TIM2_CCER |= (1 << 0);
    TIM2_CCR1 = SERVO_MIN;
    TIM2_CR1 |= (1 << 7);
    TIM2_CR1 |= (1 << 0);
}

void set_servo_angle(uint16_t value) { TIM2_CCR1 = value; }

void PWM_Disable(void) { TIM2_CCER &= ~(1 << 0); }

void PWM_Enable(void) { TIM2_CCER |= (1 << 0); }

int main(void)
{
    SysTick_Init();
    enable_clock();
    GPIO_Init();
    Timer2_Init();

    GPIO_Config_t input_dht = {
        .pin = 1U << 13,
        .mode = GPIO_MODE_INPUT,
        .port = GPIOC,
        .inputType = GPIO_INPUT_PULL_UP_DOWN,
    };
    GPIO_Config(&input_dht);

    GPIO_Config_t input = {
        .pin = 1U << 14,
        .mode = GPIO_MODE_INPUT,
        .port = GPIOC,
        .inputType = GPIO_INPUT_PULL_UP_DOWN,
    };
    GPIO_Config(&input);

    enable_clock_uart1();
    init_pin_log_info();
    init_uart();

    bool flag = false;
    PWM_Disable();
    RCC_APB2ENR |= 1U << 9;
    init_adc();
    start_adc();
    while (1)
    {
        /*   uint8_t temperature = read_data(13);
           bool is_dark = gpio_get_level(&input);

           log_info(temperature);

           if (temperature > 30 && !is_dark && flag)
           {
               flag = false;
               PWM_Enable();
               set_servo_angle(SERVO_MIN);
               for (volatile int i = 0; i < 1000000; i++)
                   ;
               PWM_Disable();
           }
           else if (is_dark && !flag)
           {
               flag = true;
               PWM_Enable();
               set_servo_angle(SERVO_MAX);
               for (volatile int i = 0; i < 1000000; i++)
                   ;
               PWM_Disable();
           }
   */
        log_info(get_temperature());

        delay_us(500000);
    }
}

