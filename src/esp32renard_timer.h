#ifndef _ESP32RENARD_TIMER_H
#define _ESP32RENARD_TIMER_H

void esp32renard_timer_start(uint32_t milliseconds);
void esp32renard_timer_stop(void);
void esp32renard_timer_continue(void);
uint32_t esp32renard_timer_remaining_ms(void);

#endif
