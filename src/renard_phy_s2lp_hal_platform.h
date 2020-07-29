#include "driver/gpio.h"

#ifndef _ESP32RENARD_PLATFORM_H
#define _ESP32RENARD_PLATFORM_H

/* Platform-specific, optional renard HAL functionality */
void renard_phy_s2lp_hal_add_timeout_source(gpio_num_t gpio, gpio_int_type_t type);

#endif
