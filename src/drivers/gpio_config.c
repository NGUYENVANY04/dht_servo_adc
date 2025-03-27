#include "gpio_config.h"
void init_pin_dht(void)
{
    GPIO_Config_t pin_config = {
        .pin = 1U << 13,
        .port = GPIOC,
        .mode = GPIO_MODE_OUTPUT_2MHz,
        .outputType = GPIO_OUTPUT_PUSH_PULL,
    };
    GPIO_Config(&pin_config);
}
