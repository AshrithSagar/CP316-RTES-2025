#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef void (*callback_t)(void);

#define NUM_TIMERS 4

void timer_init(void);
void timer_start(uint32_t n, uint32_t reload_value, callback_t callback);
void timer_stop(uint32_t n);
void timer_delay(uint32_t ticks);

extern volatile uint32_t timer_ticks;

#endif /* TIMER_H */
