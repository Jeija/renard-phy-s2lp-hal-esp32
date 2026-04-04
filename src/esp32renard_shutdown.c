#include "driver/gpio.h"

void esp32renard_shutdown_init(void)
{
	ESP_ERROR_CHECK(gpio_reset_pin(CONFIG_RENARD_S2LP_SDN_GPIO));
	ESP_ERROR_CHECK(gpio_set_direction(CONFIG_RENARD_S2LP_SDN_GPIO, GPIO_MODE_OUTPUT));
}

void esp32renard_shutdown_set(bool shutdown)
{
	ESP_ERROR_CHECK(gpio_set_level(CONFIG_RENARD_S2LP_SDN_GPIO, shutdown));
}
