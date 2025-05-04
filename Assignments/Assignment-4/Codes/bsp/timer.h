#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef void (*pfn_t)(void);

void timer_init(void);
void timer_start(uint32_t n, uint32_t reload_value, pfn_t callback);
void timer_stop(uint32_t n);
void timer_delay(uint32_t ms);
uint32_t timer_now_ms(void);

#endif /* TIMER_H */
