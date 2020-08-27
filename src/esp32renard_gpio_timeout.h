#ifndef _ESP32RENARD_GPIO_TIMEOUT_H
#define _ESP32RENARD_GPIO_TIMEOUT_H

void esp32renard_gpio_timeout_add(gpio_num_t gpio, gpio_int_type_t type);
bool esp32renard_gpio_timeout_continue(void);
bool esp32renard_gpio_timeout_occurred(void);

#endif
