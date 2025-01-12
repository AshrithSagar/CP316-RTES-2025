#include "timer.h"
#include <stddef.h>

// define systick registers
#define CSR (*(volatile unsigned long *)0xE000E010)
#define RVR (*(volatile unsigned long *)0xE000E014)
#define CVR (*(volatile unsigned long *)0xE000E018)

struct {
  uint32_t counter;    // ticks once every period
  uint32_t reload;     // initialize the counter when timer is started
                       // counter is inactive when reload = 0
  callback_t callback; // called when counter reaches 0
} software_timers[NUM_TIMERS];

volatile uint32_t timer_ticks;

// gets periodically called with period specified in timer_init
void SysTick_Handler(void) {
  timer_ticks++;

  for (int n = 0; n < NUM_TIMERS; n++) {
    if (software_timers[n].reload != 0) // active?
    {
      software_timers[n].counter--;
      if (software_timers[n].counter == 0) {
        software_timers[n].counter = software_timers[n].reload;
        software_timers[n].callback();
      }
    }
  }
}

void timer_init(void) {
  int n;

  // initialize the timer strucutre
  for (n = 0; n < NUM_TIMERS; n++) {
    software_timers[n].counter = 0;
    software_timers[n].reload = 0; // inactive
    software_timers[n].callback = NULL;
  }

  // initialize systick with the specified period
  CSR = 0;     // disable
  CVR = 0;     // any value
  RVR = 64000; // MHz * 1000 for 1 ms
  CSR = 7;     // internal clock, enable interrupts, enable systick;
               // (1 << 2) | (1 << 1) | (1 << 0)
}

void timer_start(uint32_t n, uint32_t reload_value, callback_t callback) {
  if (n >= NUM_TIMERS)
    return;

  software_timers[n].counter = reload_value;
  software_timers[n].reload = reload_value;
  software_timers[n].callback = callback;
}

void timer_stop(uint32_t n) {
  software_timers[n].counter = 0;
  software_timers[n].reload = 0;
  software_timers[n].callback = NULL;
}

// delay in number of ticks
void timer_delay(uint32_t ticks) {
  int start = timer_ticks;

  while ((timer_ticks - start) < ticks)
    ;
}
