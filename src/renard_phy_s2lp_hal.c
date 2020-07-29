#include "esp_sleep.h"

#include "esp32renard_gpio_timeout.h"
#include "esp32renard_shutdown.h"
#include "esp32renard_timer.h"
#include "esp32renard_gpio.h"
#include "esp32renard_spi.h"

void renard_phy_s2lp_hal_init(void)
{
	esp32renard_shutdown_init();
	esp32renard_spi_init();
}

/*
 * renard_phy_s2lp_hal_add_timeout_source (platform-specific!) can be used to add GPIO pins as timeout sources when in
 * light-sleep mode, e.g. during a transmission or while waiting for a downlink. Only up to 5 additional timeout
 * sources are permitted.
 */
void renard_phy_s2lp_hal_add_timeout_source(gpio_num_t gpio, gpio_int_type_t type)
{
	esp32renard_gpio_timeout_add(gpio, type);
}

void renard_phy_s2lp_hal_spi(uint8_t length, uint8_t *in, uint8_t *out)
{
	esp32renard_spi_raw(length, in, out);
}

void renard_phy_s2lp_hal_shutdown(bool shutdown)
{
	esp32renard_shutdown_set(shutdown);
}

void renard_phy_s2lp_hal_interrupt_timeout(uint32_t milliseconds)
{
	esp32renard_timer_start(milliseconds);
}

void renard_phy_s2lp_hal_interrupt_gpio(bool risingTrigger)
{
	esp32renard_gpio_interrupt_enable(risingTrigger);
}

void renard_phy_s2lp_hal_interrupt_clear(void)
{
	esp32renard_timer_stop();
	esp32renard_gpio_interrupt_disable();
}

/*
 * renard_phy_s2lp_hal_interrupt_wait
 * returns false for timeout and true if S2-LP GPIO pin caused interrupt
 */
int renard_phy_s2lp_hal_interrupt_wait(void)
{
	esp32renard_timer_continue();
	esp32renard_gpio_interrupt_continue();

	esp_light_sleep_start();

	esp32renard_timer_stop();

	if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO)
		return !esp32renard_gpio_timeout_occurred();

	return false;
}

