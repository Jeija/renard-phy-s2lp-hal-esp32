#include "driver/gpio.h"
#include "esp_sleep.h"

#include "esp32renard_gpio_timeout.h"

static bool gpio_interrupt_enable = false;
static bool gpio_interrupt_rising = false;

void esp32renard_gpio_interrupt_enable(bool rising)
{
	gpio_interrupt_enable = true;
	gpio_interrupt_rising = rising;
}

void esp32renard_gpio_interrupt_disable(void)
{
	if (gpio_interrupt_enable) {
		gpio_interrupt_enable = false;
		esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_GPIO);
	}
}

void esp32renard_gpio_interrupt_continue(void)
{
	bool have_gpio_timeout = esp32renard_gpio_timeout_continue();

	if (gpio_interrupt_enable) {
		gpio_wakeup_enable(CONFIG_RENARD_S2LP_INT_GPIO,
				gpio_interrupt_rising ? GPIO_INTR_HIGH_LEVEL : GPIO_INTR_LOW_LEVEL);
	} else {
		gpio_wakeup_disable(CONFIG_RENARD_S2LP_INT_GPIO);
	}

	if (have_gpio_timeout || gpio_interrupt_enable)
		esp_sleep_enable_gpio_wakeup();
}
