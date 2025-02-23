// Time spent to transmit one character.

#include "bsp.h"

#define SYSTICK_CVR (*(volatile unsigned long *)0xE000E018)

volatile unsigned int counter = 0;
volatile unsigned int ticks_taken = 0;

void transmit() {
  volatile uint32_t start, end;

  start = SYSTICK_CVR;

  uart_putc(' ');
  // Transmit a space character, to keep it clean

  end = SYSTICK_CVR;

  ticks_taken += (start - end);
  // Since decrementing timer

  counter++;
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
  }
}

int main() {
  uart_init(UART_RX, UART_TX);
  timer_init();

  timer_start(0, 1, transmit);
  timer_start(1, 1000, print_average);

  return 0;
}
