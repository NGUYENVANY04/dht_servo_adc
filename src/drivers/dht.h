#ifndef _DHT_H_
#define _DHT_H_
#include <stdint.h>
#include "gpio.h"

int start_signal(GPIO_Config_t pin_config);
uint8_t read_signal(GPIO_Config_t pin_config);
uint32_t read_data(uint8_t pin);
#endif
