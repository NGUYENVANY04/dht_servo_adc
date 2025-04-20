#include "gpio_config.h"
#include "gpio.h"
void init_pin_log_info(void)
{
    GPIO_Config_t pin_log = {
        .pin = 1U << 9,
        .mode = GPIO_MODE_OUTPUT_50MHz,
        .outputType = GPIO_OUTPUT_AF_PUSH_PULL,
        .port = GPIOA,
    };
    GPIO_Config(&pin_log);
}
/*void init_analog_data(void)
{
    GPIO_Config_t analog_pin = {
        .pin = 1U << 14,
        .mode = GPIO_MODE_INPUT,
        .inputType = GPIO_INPUT_ANALOG,
        .port = GPIOC,
    };
    gpio_config(&analog_pin);
}
*/
