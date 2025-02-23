// Average human reaction-time to click (press and release) a button.

#include "bsp.h"

#define SYSTICK_CVR (*(volatile unsigned long *)0xE000E018)

volatile unsigned int counter = 0;
volatile unsigned int ticks_taken = 0;
volatile uint32_t start, end;
int flag = 0;

void blink() {
  led_on(2, 2);
  start = SYSTICK_CVR;
  flag = 1;
}

void reaction() {
  if (flag && button_get(0)) {
    // Button press detected, so mark endpoint
    end = SYSTICK_CVR;

    flag = 0;
    led_off(2, 2);

    unsigned int difference;
    if (start >= end)
      difference = start - end;
    else
      difference = (0xFFFFFFF + start) - end;

    ticks_taken += difference;
    counter++;
  }
}

void print_average() {
  if (counter > 0) {

    float time_taken = (float)ticks_taken / 64;
    // In microseconds, since 64 MHz clock

    float average_time = (float)time_taken / (float)counter;

    printf("\nAverage: %f microseconds,", average_time);
    printf(" across %d iterations", counter);

    ticks_taken = 0;
    counter = 0;
  } else {
    printf("\nNo reaction detected. Waited for 10 seconds.");
  }
}

int main() {
  uart_init(UART_RX, UART_TX);
  timer_init();

  timer_start(0, 1000, blink);
  // Every 1s, turn the LED on

  timer_start(1, 1, reaction);
  // Every 1ms, check for reaction

  timer_start(2, 10000, print_average);
  // Every 10s, print the average time taken

  return 0;
}
