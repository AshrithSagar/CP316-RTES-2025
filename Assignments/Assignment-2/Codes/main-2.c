// Stopwatch

#include "bsp.h"

#define SYSTICK_CVR (*(volatile unsigned long *)0xE000E018)
#define DEBOUNCE_DELAY 500 // In milliseconds

volatile unsigned int ticks = 0;
volatile uint32_t start = 0, end = 0;
int button_state = 0; // State (0: released, 1: pressed)

void stopwatch() {
  static uint32_t last_button_press = 0;
  uint32_t current_time = SYSTICK_CVR;

  if (button_get(0)) {
    if (button_state == 0 &&
        (current_time - last_button_press) > DEBOUNCE_DELAY) {
      if (start == 0) {
        start = current_time;
        printf("\nStart!\n");
      } else {
        end = current_time;
        unsigned int diff = 0;
        if (start >= end)
          ticks = start - end;
        else
          ticks = (0xFFFFFFF + start) - end;
        button_state = 2; // Wait for second press
        printf("\nStop!\n");
      }
      last_button_press = current_time;
    }
  } else if (button_state == 1) {
    button_state = 0; // Reset debounce state if button released
  }
}

void print_stopwatch() {
  if (start != 0 && button_state == 0) {
    float elapsed = (float)ticks / 64000.0;
    // In microseconds, since 64 MHz clock

    printf("\rTime: %f seconds", elapsed);
  }
  if (button_state == 2) {
    float elapsed = (float)ticks / 64000.0;
    // In microseconds, since 64 MHz clock

    printf("\nElapsed time: %f seconds\n", elapsed);
  }
}

int main() {
  uart_init(UART_RX, UART_TX);
  timer_init();

  printf("\nStopwatch: Press button A to start/stop\n\n");

  timer_start(0, 1, stopwatch);
  // Every 1ms, check for button press

  timer_start(1, 100, print_stopwatch);
  // Every 100ms (0.1s), print the value

  return 0;
}
