#include "driver/gpio.h"

#include "esp32renard_gpio_timeout.h"

typedef struct {
	gpio_num_t gpio;
	gpio_int_type_t type;
} timeout_source_t;
static timeout_source_t timeout_sources[5];
static size_t timeout_source_count = 0;

void esp32renard_gpio_timeout_add(gpio_num_t gpio, gpio_int_type_t type)
{
	if (type == GPIO_INTR_HIGH_LEVEL || type == GPIO_INTR_LOW_LEVEL) {
		timeout_sources[timeout_source_count].gpio = gpio;
		timeout_sources[timeout_source_count].type = type;
		++timeout_source_count;
	}
}

void esp32renard_gpio_timeout_continue(void)
{
	for (size_t i = 0; i < timeout_source_count; ++i) {
		gpio_wakeup_enable(timeout_sources[i].gpio, timeout_sources[i].type);
	}
}

bool esp32renard_gpio_timeout_occurred(void)
{
	for (size_t i = 0; i < timeout_source_count; ++i) {
		if (gpio_get_level(timeout_sources[i].gpio) == (timeout_sources[i].type == GPIO_INTR_HIGH_LEVEL))
			return true;
	}

	return false;
}
