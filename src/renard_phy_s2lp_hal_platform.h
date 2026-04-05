#ifndef _ESP32RENARD_PLATFORM_H
#define _ESP32RENARD_PLATFORM_H

#include <setjmp.h>

#include "driver/gpio.h"

/* Platform-specific, optional renard HAL functionality */
void renard_phy_s2lp_hal_add_timeout_source(gpio_num_t gpio, gpio_int_type_t type);
void renard_phy_s2lp_hal_abort_arm(jmp_buf *abort_env);
void renard_phy_s2lp_hal_abort_disarm(void);

#endif
