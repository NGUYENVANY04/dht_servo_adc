#include "dht.h"
#include "systick.h"
#include "gpio.h"
#include "stdbool.h"
#include <stdint.h>
int start_signal(GPIO_Config_t *pin_config)
{
    bool flag_low = false, flag_high = false;
    // Start signal from MCU
    pin_config->mode = GPIO_MODE_OUTPUT_2MHz;
    pin_config->outputType = GPIO_OUTPUT_PUSH_PULL;

    GPIO_Config(pin_config);

    gpio_set_level(pin_config, 1);
    delay_us(100000); // Start signal from MCU
    gpio_set_level(pin_config, 0);
    delay_us(10 * 1000);
    gpio_set_level(pin_config, 1);
    delay_us(20);

    pin_config->mode = GPIO_MODE_INPUT;
    pin_config->inputType = GPIO_INPUT_PULL_UP_DOWN;

    GPIO_Config(pin_config);
    while (!gpio_get_level(pin_config))
    {
        flag_low = true;
    }
    while (gpio_get_level(pin_config))
    {
        flag_high = true;
    }
    if (!flag_low && !flag_high)
    {
        return -1;
    }

    return 0;
}
uint8_t read_signal(GPIO_Config_t *pin_config)
{
    uint8_t data = 0;
    for (int i = 7; i >= 0; i--)
    {
        while (!gpio_get_level(pin_config))
            ;
        delay_us(15);
        if (gpio_get_level(pin_config))
        {
            data |= 1U << i;
        }
        else
        {
            data |= 0U << i;
        }

        while (gpio_get_level(pin_config))
            ;
    }
    return data;
}

uint8_t read_data(uint8_t pin)
{
    uint8_t data[5] = { 0, 0, 0, 0, 0 };
    GPIO_Config_t pin_config = {
        .pin = 1U << pin,
        .port = GPIOC,
    };
    start_signal(&pin_config);
    data[0] = read_signal(&pin_config);
    data[1] = read_signal(&pin_config);
    data[2] = read_signal(&pin_config);
    data[3] = read_signal(&pin_config);
    data[4] = read_signal(&pin_config);
        return data[2];
}

