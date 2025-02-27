// Stopwatch

#include "bsp.h"

#define DEBOUNCE_DELAY 50 // In milliseconds

volatile uint32_t start = 0, end = 0, elapsed = 0;
volatile int button_state = 0; // 0: Released, 1: Pressed, 2: Stopped

void stopwatch() {
  static uint32_t last_press_time = 0;

  if (button_get(0)) { // Button pressed
    if (button_state == 0 && (timer_ticks - last_press_time) > DEBOUNCE_DELAY) {
      if (start == 0) { // First press
        start = timer_ticks;
      } else { // Second press
        end = timer_ticks;
        elapsed = end - start;
        button_state = 2; // Mark as stopped
      }
      last_press_time = timer_ticks;
      button_state = 1; // Mark button as pressed
    }
  } else {
    button_state = 0; // Reset on release
  }
}

void print_stopwatch() {
  if (start != 0 && button_state == 1) {
    printf("\rTime: %f s", (float)(timer_ticks - start) / 1000.0);
  }
  if (button_state == 2) {
    printf("\nElapsed time: %f s\n", (float)elapsed / 1000.0);
  }
}

int main() {
  uart_init(UART_RX, UART_TX);
  timer_init();

  printf("\nStopwatch: Hold button A to start/stop\n\r");

  timer_start(0, 10, stopwatch);
  // Check button every 10ms

  timer_start(1, 100, print_stopwatch);
  // Print every 100ms

  return 0;
}
