#include "esp_sleep.h"
#include "soc/rtc.h"

static uint64_t target_rtc_count = 0;
static bool timer_wakeup_enabled = false;

void esp32renard_timer_start(uint32_t milliseconds)
{
	target_rtc_count = rtc_time_get() + (uint64_t)milliseconds * rtc_clk_slow_freq_get_hz() / 1000;
	timer_wakeup_enabled = false;
}

void esp32renard_timer_stop(void)
{
	if (target_rtc_count != 0) {
		target_rtc_count = 0;
		if (timer_wakeup_enabled) {
			esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
			timer_wakeup_enabled = false;
		}
	}
}

void esp32renard_timer_continue(void)
{
	// If target_rtc_count is in the past for some reason, timer will trigger wakeup after 1us
	uint64_t rtc_count = rtc_time_get();

	if (target_rtc_count != 0) {
		uint64_t delay = target_rtc_count > rtc_count ? (target_rtc_count - rtc_count) : 1;

		esp_sleep_enable_timer_wakeup(delay * 1000000 / rtc_clk_slow_freq_get_hz());
		timer_wakeup_enabled = true;
	}
}

uint32_t esp32renard_timer_remaining_ms(void)
{
	uint64_t rtc_count = rtc_time_get();

	if (target_rtc_count == 0 || target_rtc_count <= rtc_count) {
		return 0;
	}

	uint64_t delay = target_rtc_count - rtc_count;
	uint64_t hz = rtc_clk_slow_freq_get_hz();

	return (uint32_t)((delay * 1000 + hz - 1) / hz);
}
